/**
 *	@file
 */

/****************************************************************************
**
** This file is part of DrawGin library. A C++ framework to read and
** write .dwg files formats.
**
** Copyright (C) 2011, 2012, 2013 Paul Kohut.
** All rights reserved.
** Author: Paul Kohut (pkohut2@gmail.com)
**
** DrawGin library is free software; you can redistribute it and/or
** modify it under the terms of either:
**
**   * the GNU Lesser General Public License as published by the Free
**     Software Foundation; either version 3 of the License, or (at your
**     option) any later version.
**
**   * the GNU General Public License as published by the free
**     Software Foundation; either version 2 of the License, or (at your
**     option) any later version.
**
** or both in parallel, as here.
**
** DrawGin library is distributed in the hope that it will be useful,
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

#include "OcCommon.h"
#include "OcError.h"
#include "OcBsStreamIn.h"
#include "OcBsDwgFileHeader.h"
#include "OcBsDwgVersion.h"
#include "OcBsDwgSentinels.h"
#include "OcBsDwgCrc.h"

BEGIN_OCTAVARIUM_NS

const static std::array<std::string, 6> dwgSections = {"HEADER", "CLASS", "OBJECT_MAP", "UNKNOWN_SECTION3", "DATA_SECTION", "UNKNOWN", };

const static int NumSections()
{
    VLOG_FUNC_NAME;
    return dwgSections.size();
}

const std::string & HeaderSectionName(int i)
{
    VLOG_FUNC_NAME;

    if(i < NumSections())
    {
        return dwgSections[i];
    }

    const static std::string msg("Section number outside of known range");
    LOG(ERROR) << msg;
    return msg;
}

#define CRC8_CALC(crcIn, x) crc8(crcIn, (const char *)&x, sizeof(x))



OcBsDwgFileHeader::OcBsDwgFileHeader(void)
    : m_dwgVersion(NONE)
{
    VLOG_FUNC_NAME;
}


OcBsDwgFileHeader::~OcBsDwgFileHeader(void)
{
    VLOG_FUNC_NAME;
}

OcApp::ErrorStatus OcBsDwgFileHeader::ReadDwg(OcBsStreamIn & in)
{
    VLOG_FUNC_NAME;
    VLOG(4) << "OcBsDwgFileHeader::ReadDwg entered";

    m_dwgVersion = DecodeVersionData(in);
    in.SetVersion(DwgVersion());

    if(DwgVersion() == NONE)
    {
        in.SetError(OcApp::eInvalidVersion);
    }
    else if(DwgVersion() == R13 || DwgVersion() == R14 || DwgVersion() == R2000)
    {
        in.SetError(DecodeR13_R2000Header(in));
    }
    else
    {
        in.SetError(OcApp::eUnsupportedVersion);
    }

    return in.Error();
}

octavarium::DWG_VERSION OcBsDwgFileHeader::DwgVersion(void) const
{
    VLOG_FUNC_NAME;
    return m_dwgVersion;
}

bool OcBsDwgFileHeader::IsPreR13c3(void) const
{
    VLOG_FUNC_NAME;
    return !IsR13c3OrHigher();
}

bool OcBsDwgFileHeader::IsR13c3OrHigher(void) const
{
    VLOG_FUNC_NAME;
    return m_headerSections.size() > 3;
}

int32_t OcBsDwgFileHeader::ImageSeeker(void) const
{
    VLOG_FUNC_NAME;
    return m_imageSeeker;
}

int OcBsDwgFileHeader::NumSectionRecords(void) const
{
    VLOG_FUNC_NAME;
    return m_nSections;
}

const OcBsDwgFileHeaderSection& OcBsDwgFileHeader::Record(int nRecord) const
{
    VLOG_FUNC_NAME;
    assert(nRecord < m_nSections);
    return m_headerSections[nRecord];
}

octavarium::DWG_VERSION OcBsDwgFileHeader::DecodeVersionData(OcBsStreamIn & in)
{
    VLOG_FUNC_NAME;
    std::string sVersion;
    in.ReadRC(sVersion, 6);
    return OcBsDwgVersion::GetVersionId(sVersion);
}

OcApp::ErrorStatus OcBsDwgFileHeader::DecodeR13_R2000Header(OcBsStreamIn & in)
{
    VLOG_FUNC_NAME;
    using namespace bitcode;

    VLOG(4) << "*** Begin reading file header ***";

    std::string sVersion = OcBsDwgVersion::GetVersionId(m_dwgVersion);
    in.SetCalcedCRC(crc8(0, sVersion.c_str(), 6));
    VLOG(4) << "File ID = " << sVersion;

    // more version ID, 3.2.1
    BS_STREAMIN(RL, in, m_unknown_offset_0x06, "unknown_offset_0x06");
    BS_STREAMIN(RC, in, m_unknown_offset_0x0a, "unknown_offset_0x0a");
    BS_STREAMIN(RC, in, m_acadMaintVer, "acadMainVer");
    BS_STREAMIN(RC, in, m_unknown_offset_0x0c, "unknown_offset_0x0c");

    // image seeker, 3.2.2
    BS_STREAMIN(RL, in, m_imageSeeker, "imageSeeker");

    // unknown section, 3.2.3
    BS_STREAMIN(RS, in, m_unknown_offset_0x11, "unknown_offset_0x11");

    // dwg codepage, 3.2.4
    BS_STREAMIN(RS, in, m_codePage, "codepage");

    // section loader records, 3.2.5
    BS_STREAMIN(RL, in, m_nSections, "Selection Locator Records");

    for(int i = 0; i < m_nSections; ++i)
    {
        VLOG(4) << "--------";
        OcBsDwgFileHeaderSection section;
        BS_STREAMIN(RC, in, section.recordNumber, "section record");
        VLOG(4) << "section name: " << HeaderSectionName(i);
        BS_STREAMIN(RL, in, section.seeker,       "    section seeker");
        BS_STREAMIN(RL, in, section.size,         "    section size");
        m_headerSections.push_back(section);
    }

    uint16_t runningCrc = in.CalcedCRC();
    int16_t headerCrc;
    in >> (RS&) headerCrc;
    uint16_t crcCheck = runningCrc ^ headerCrc;
    VLOG(4) << "Header CRC = " << std::hex << std::showbase << crcCheck;

    if(crcCheck != 0xa598 && crcCheck != 0x8101
            && crcCheck != 0x3cc4 && crcCheck != 0x8461)
    {
        return OcApp::eInvalidCRCInFileHeader;
    }

    RC sentinelData[16];
    in.ReadRC(sentinelData, 16);
    if(!CompareSentinels(sentinelR13_R2000, sentinelData))
    {
        return OcApp::eInvalidHeaderSentinal;
    }

    VLOG(4) << "*** Finished reading file header ***";
    return OcApp::eOk;
}

END_OCTAVARIUM_NS
