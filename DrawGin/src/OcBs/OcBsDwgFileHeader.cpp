/****************************************************************************
**
** This file is part of DrawGin library. A C++ framework to read and
** write .dwg files formats.
**
** Copyright (C) 2011 Paul Kohut.
** All rights reserved.
** Author: Paul Kohut (pkohut2@gmail.com)
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License as published by the Free Software Foundation; either
** version 3 of the License, or (at your option) any later version.
**
** This library is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
** Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public
** License along with this library; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
**
** DrawGin project hosted at: http://code.google.com/p/drawgin/
**
** Authors:
**      pk          Paul Kohut <pkohut2@gmail.com>
**
****************************************************************************/

#include "stdafx.h"
#include "OcCommon.h"
#include "OcError.h"
#include "OcTypes.h"
#include "OcDbObjectId.h"
#include "OcDbDwgVersion.h"
#include "OcBsDwgCrc.h"
#include "OcBsDwgFileHeader.h"
#include "OcBsDwgSentinels.h"

BEGIN_OCTAVARIUM_NS

#define ASSERT_ARCHIVE_NOT_LOADING assert(in.ArchiveFlag() == DwgInArchive::LOADING)
#define CRC8_CALC(crcIn, x) crc8(crcIn, (const char*)&x, sizeof(x))

OcBsDwgFileHeader::OcBsDwgFileHeader(void)
    : m_dwgVersion(NONE), m_crc(0)
{
}

OcBsDwgFileHeader::~OcBsDwgFileHeader(void)
{
}

DWG_VERSION OcBsDwgFileHeader::DwgVersion(void) const
{
    return m_dwgVersion;
}

bool OcBsDwgFileHeader::IsPreR13c3(void) const
{
    return !IsR13c3OrHigher();
}

bool OcBsDwgFileHeader::IsR13c3OrHigher(void) const
{
    return m_headerSections.size() > 3;
}

int32_t OcBsDwgFileHeader::ImageSeeker(void) const
{
    return m_imageSeeker;
}

DWG_VERSION OcBsDwgFileHeader::DecodeVersionData(DwgInArchive& in)
{
    std::string sVersion;
    in.ReadRC(sVersion, 6);
    return OcDbDwgVersion::GetVersionId(sVersion);
}

OcApp::ErrorStatus OcBsDwgFileHeader::DecodeR13_R2000Header(DwgInArchive& in)
{
    const char * pcszVersion =
        OcDbDwgVersion::GetVersionId(m_dwgVersion).c_str();
    m_crc = crc8(0, pcszVersion, 6);

    // more version ID, 3.2.1
    in >> (bitcode::RL&) m_unknown_offset_0x06;
    m_crc = CRC8_CALC(m_crc, m_unknown_offset_0x06);

    in >> (bitcode::RC&) m_unknown_offset_0x0a;
    m_crc = CRC8_CALC(m_crc, m_unknown_offset_0x0a);

    in >> (bitcode::RC&) m_acadMaintVer;
    m_crc = CRC8_CALC(m_crc, m_acadMaintVer);

    in >> (bitcode::RC&) m_unknown_offset_0x0c;
    m_crc = CRC8_CALC(m_crc, m_unknown_offset_0x0c);

    // image seeker, 3.2.2
    in >> (bitcode::RL&) m_imageSeeker;
    m_crc = CRC8_CALC(m_crc, m_imageSeeker);

    // unknown section, 3.2.3
    in >> (bitcode::RS&) m_unknown_offset_0x11;
    m_crc = CRC8_CALC(m_crc, m_unknown_offset_0x11);

    // dwg codepage, 3.2.4
    in >> (bitcode::RS&) m_codePage;
    m_crc = CRC8_CALC(m_crc, m_codePage);

    // section loader records, 3.2.5
    in >> (bitcode::RL&) m_nSections;
    m_crc = CRC8_CALC(m_crc, m_nSections);
    // uint16_t crc = crc8(0, (const char *)in.Buffer(), in.FilePosition());
    for(int i = 0; i < m_nSections; ++i) {
        OcBsDwgFileHeaderSection section;
        in >> (bitcode::RC&) section.recordNumber;
        m_crc = CRC8_CALC(m_crc, section.recordNumber);
        in >> (bitcode::RL&) section.seeker;
        m_crc = CRC8_CALC(m_crc, section.seeker);
        in >> (bitcode::RL&) section.size;
        m_crc = CRC8_CALC(m_crc, section.size);
        m_headerSections.push_back(section);
        // crc = crc8(0, (const char *)in.Buffer(), in.FilePosition());
    }
    // crc = crc8(0, (const char *)in.Buffer(), in.FilePosition());
    int16_t headerCrc;
    in >> (bitcode::RS&) headerCrc;
    uint16_t crcCheck = m_crc ^ headerCrc;
    // int16_t crcCheck1 = crc ^ headerCrc;

    if(crcCheck != 0xa598 && crcCheck != 0x8101
            && crcCheck != 0x3cc4 && crcCheck != 0x8461) {
        return OcApp::eInvalidCRCInFileHeader;
    }

    bitcode::RC sentinelData[16];
    in.ReadRC(sentinelData, 16);
    if(!CompareSentinels(sentinelR13_R2000, sentinelData)) {
        return OcApp::eInvalidHeaderSentinal;
    }


    return OcApp::eOk;
}

int OcBsDwgFileHeader::NumSectionRecords(void) const
{
    return m_nSections;
}

const OcBsDwgFileHeaderSection& OcBsDwgFileHeader::Record(int nRecord) const
{
    assert(nRecord < m_nSections);
    return m_headerSections[nRecord];
}

DwgInArchive& operator>>(DwgInArchive& in, OcBsDwgFileHeader & hdr)
{
    ASSERT_ARCHIVE_NOT_LOADING;
    // version ID, 3.2.1
    hdr.m_dwgVersion = hdr.DecodeVersionData(in);
    in.SetVersion(hdr.DwgVersion());
    if(hdr.DwgVersion() == NONE) {
        in.SetError(OcApp::eInvalidVersion);
    } else if(hdr.DwgVersion() == R13
              || hdr.DwgVersion() == R14
              || hdr.DwgVersion() == R2000) {
        in.SetError(hdr.DecodeR13_R2000Header(in));
    } else {
        in.SetError(OcApp::eUnsupportedVersion);
    }
    return in;
}

END_OCTAVARIUM_NS
