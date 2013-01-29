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
#include "OcBsDwgSecondFileHeader.h"
#include "OcBsDwgSentinels.h"


#include <iomanip>

BEGIN_OCTAVARIUM_NS
using namespace std;

extern const std::string & HeaderSectionName(int i);

const std::array<std::string, 14> _sHandles  =
{
    "HANDSEED", "BLOCK_CONTROL_OBJ", "LAYER_CONTROL_OBJ",
    "SHAPEFILE_CONTROL_OBJ", "LINETYPE_CONTROL_OBJ",
    "VIEW_CONTROL_OBJ", "UCS_CONTROL_OBJ", "VPORT_CONTROL_OBJ",
    "REGAPP_CONTROL_OBJ", "DIMSTYLE_CONTROL_OBJ",
    "VIEWPORT_ENTITY_HEADER_OBJ", "DICTIONARY_OBJ",
    "MULTILINE_STYLE_OBJ", "GROUP_DICTIONARY_OBJ",
};



OcBsDwgSecondFileHeader::OcBsDwgSecondFileHeader(void)
{
    VLOG_FUNC_NAME;
}


OcBsDwgSecondFileHeader::~OcBsDwgSecondFileHeader(void)
{
    VLOG_FUNC_NAME;
}

OcApp::ErrorStatus OcBsDwgSecondFileHeader::ReadDwg(OcBsStreamIn & in)
{
    VLOG_FUNC_NAME;

    auto fp = in.FilePosition();
    // match second file header section start sentinel
    bitcode::RC sentinelData[16];
    in.ReadRC(sentinelData, 16);

    if(!CompareSentinels(sentinelSecondFileHeaderBegin, sentinelData))
    {
        return OcApp::eInvalidSecondHeaderSentinel;
    }

    in.SetCalcedCRC(0xc0c1);

    int32_t hdrSize;
    BS_STREAMIN(bitcode::RL, in, hdrSize, "second file header size");

    auto endSection = in.FilePosition() + hdrSize - 1;
    int32_t filePosition;
    BS_STREAMIN(bitcode::BL, in, filePosition, "file position of this header");

    // Section 23.1, "AC1012" for R13 and "AC1014" for R14
    bitcode::RC versionSignature[6];
    in.ReadRC(versionSignature, 6);
    VLOG(4) << "version signature: " << std::string(versionSignature, versionSignature + 6);

    // Section 23.1, state this is 6 bytes of 0's. Doesn't seem correct.
    bitcode::RC unknownPurpose[8];
    in.ReadRC(unknownPurpose, 8);
    std::vector<bitcode::RC> vv(unknownPurpose, unknownPurpose + 8);
    VLOG(4) << "unknown purpose: " << RC2Hex(vv);

    // // Section 23.1, state 4 bits. Ok.
    byte_t fourBits[4];

    for(int i = 0; i < 4; i++)
    {
        BS_STREAMIN(bitcode::B, in, fourBits[i], "4 bits of 0");
    }

    // Section 23.1, states 4 bytes,
    // 0x18, 0x78, 0x01, 0x04 for R13 and 0x18, 0x78, 0x01, 0x05 for R14
    // In the sample file, byte 0 is reading 0x64.
    bitcode::RC hexSignature[4];
    in.ReadRC(hexSignature, 4);
    VLOG(4) << "hex signature: " << RC2Hex(std::vector<bitcode::RC>(hexSignature, hexSignature + 4));
    VLOG(4) << "   spec states: R13 = 0x18 0x78 0x01 0x04";
    VLOG(4) << "                R14 = 0x18 0x78 0x01 0x05";

    // Section 23.1, states this is 4 sets of values, however, it's 5 with my
    // sample R14 drawing.
    OcBsDwgSecondFileHeaders header;
    for(int i = 0; i < 5; i++)
    {
        VLOG(4) << "-------- " << HeaderSectionName(i);
        BS_STREAMIN(bitcode::RC, in, header.sectionNumber, "section number");
        BS_STREAMIN(bitcode::BL, in, header.address, "section address");
        BS_STREAMIN(bitcode::BL, in, header.size, "section size");
        m_sectionHeaders.push_back(header);
    }

    // Section 23.1, states there should be 14 table entries.
    int16_t numberOfHandleRecords;
    BS_STREAMIN(bitcode::BS, in, numberOfHandleRecords, "number of handle records to follow");
    CHECK(numberOfHandleRecords <= 14);

    OcBsDwgHandleRecord handle;
    for(int i = 0; i < (int16_t)numberOfHandleRecords; i++)
    {
        VLOG(4) << "-------- ("<< i << ")" << _sHandles[i];
        BS_STREAMIN(bitcode::RC, in, handle.sizeOfValidChars, "size of valid chars");
        BS_STREAMIN(bitcode::RC, in, handle.recordNumber, "record number");
        in.ReadRC(handle.sig, handle.sizeOfValidChars);
        VLOG(4) << _sHandles[i] << ":" << RC2Hex(handle.sig);
        m_handleRecords.push_back(handle);
    }

    // calc section crc, LSB order
    uint16_t crc, calcedCrc = in.CalcedCRC();
    in.ReadCRC(crc);
    if(crc != calcedCrc)
    {
        LOG(ERROR) << "Second file header CRC is incorrect";
        return OcApp::eInvalidCRCInSecondFileHeader;
    }

    // Read 8 bytes of junk data for R14
    if(in.Version() == R14)
    {
        bitcode::RC junkData[8];
        in.ReadRC(junkData, 8);
    }

    in.ReadRC(sentinelData, 16);
    if(!CompareSentinels(sentinelSecondFileHeaderEnd, sentinelData))
    {
        return OcApp::eInvalidSecondHeaderSentinel;
    }

    fp = in.FilePosition();
    return OcApp::eOk;
}

END_OCTAVARIUM_NS