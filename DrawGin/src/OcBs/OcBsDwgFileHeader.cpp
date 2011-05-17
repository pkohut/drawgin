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

#include "OcBsStreamIn.h"
#include "OcBsDwgFileHeader.h"
#include "OcBsDwgSentinels.h"
#include "OcBsDwgCrc.h"

BEGIN_OCTAVARIUM_NS

#define ASSERT_ARCHIVE_NOT_LOADING assert(in.ArchiveFlag() == DwgInArchive::LOADING)
#define CRC8_CALC(crcIn, x) crc8(crcIn, (const char*)&x, sizeof(x))

OcBsDwgFileHeader::OcBsDwgFileHeader(void)
    : m_dwgVersion(NONE)
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
    using namespace bitcode;
    VLOG(4) << "*** Begin reading file header ***";
    const char * pcszVersion =
        OcDbDwgVersion::GetVersionId(m_dwgVersion).c_str();

    in.SetCalcedCRC(crc8(0, pcszVersion, 6));
    VLOG(4) << "File ID = " << pcszVersion;

    // more version ID, 3.2.1
    BS_ARCHIVE(RL, in, m_unknown_offset_0x06, "unknown_offset_0x06");

    BS_ARCHIVE(RC, in, m_unknown_offset_0x0a, "unknown_offset_0x0a");

    BS_ARCHIVE(RC, in, m_acadMaintVer, "acadMainVer");

    BS_ARCHIVE(RC, in, m_unknown_offset_0x0c, "unknown_offset_0x0c");

    // image seeker, 3.2.2
    BS_ARCHIVE(RL, in, m_imageSeeker, "imageSeeker");

    // unknown section, 3.2.3
    BS_ARCHIVE(RS, in, m_unknown_offset_0x11, "unknown_offset_0x11");

    // dwg codepage, 3.2.4
    BS_ARCHIVE(RS, in, m_codePage, "codepage");

    // section loader records, 3.2.5
    BS_ARCHIVE(RL, in, m_nSections, "Selection Locator Records");

    for(int i = 0; i < m_nSections; ++i) {
        OcBsDwgFileHeaderSection section;
        BS_ARCHIVE(RC, in, section.recordNumber, "section record");

        BS_ARCHIVE(RL, in, section.seeker,       "    section seeker");

        BS_ARCHIVE(RL, in, section.size,         "    section size");
        m_headerSections.push_back(section);
    }

    uint16_t runningCrc = in.CalcedCRC();
    int16_t headerCrc;
    in >> (RS&) headerCrc;
    uint16_t crcCheck = runningCrc ^ headerCrc;
    VLOG(4) << "Header CRC = " << std::hex << std::showbase << crcCheck;

    if(crcCheck != 0xa598 && crcCheck != 0x8101
            && crcCheck != 0x3cc4 && crcCheck != 0x8461) {
        return OcApp::eInvalidCRCInFileHeader;
    }

    RC sentinelData[16];
    in.ReadRC(sentinelData, 16);
    if(!CompareSentinels(sentinelR13_R2000, sentinelData)) {
        return OcApp::eInvalidHeaderSentinal;
    }
    VLOG(4) << "*** Finished reading file header ***";


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
