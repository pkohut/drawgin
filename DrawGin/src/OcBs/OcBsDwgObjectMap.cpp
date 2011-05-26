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

#include "OcCommon.h"
#include "OcError.h"
#include "OcTypes.h"
#include "OcDbObjectId.h"
#include "OcDbDwgVersion.h"

#include "OcBsStreamIn.h"
#include "OcBsDwgObjectMapItem.h"
#include "OcBsDwgObjectMap.h"

BEGIN_OCTAVARIUM_NS

#define ASSERT_ARCHIVE_NOT_LOADING assert(ar.ArchiveFlag() \
    == DwgInArchive::LOADING)

OcBsDwgObjectMap::OcBsDwgObjectMap(int32_t objMapFilePos, int32_t objMapSize)
: m_objMapFilePos(objMapFilePos), m_objMapSize(objMapSize)
{
}

OcBsDwgObjectMap::~OcBsDwgObjectMap(void)
{
}



OcApp::ErrorStatus OcBsDwgObjectMap::DecodeData(DwgInArchive& ar)
{
    ASSERT_ARCHIVE_NOT_LOADING;
    VLOG(3) << "DecodeObjectMap entered";
    // do some sanity checks before trying to read the object map
    if(m_objMapFilePos == 0) {
        LOG(ERROR) << "Invalid file offset position for Object Map";
        return OcApp::eInvalidObjectMapOffset;
    }

    // set file position to the Object Map offset
    ar.Seek(m_objMapFilePos);
    if(ar.Error() != OcApp::eOk) {
        LOG(ERROR) << "Error setting file position";
        return ar.Error();
    }

    int32_t lastHandle = 0, lastOffset = 0;

    // Until I've seen some files which have more than one
    // section, not really sure how the data is coded.
    // Does lastOffset need to be reset to 0 for each section?
    int sectionNumber = 0;

    // section size and crc are values stored in big endian format
    // on disk.
    while(1) {
        // reset calced crc to 0xc0c1 for each section
        ar.SetCalcedCRC(0xc0c1);
        // read section size and convert to little endian format.
        int16_t sectionSize;
        ar >> (bitcode::RC&)sectionSize;
        sectionSize <<= 8;
        ar >> (bitcode::RC&)sectionSize;
        VLOG(4) << "Section size = " << sectionSize;

        // only 2 bytes for this section, they are the final crc
        // which is calced below outside of this loop.
        if(sectionSize <= 2) {
            break;
        }

        // Until I've seen some files which have more than one
        // section, not really sure how the data is coded.
        // Does lastOffset need to be reset to 0 for each section?
        CHECK(sectionNumber == 0) << "Check file offsets for object addresses";

        // endSection includes the 2 byte crc for this section, so
        // exclude 2 bytes when doing the loop.
        int32_t endSection = ar.FilePosition() + sectionSize;
        while(ar.FilePosition() < endSection - 2) {
            int32_t offsetLastH;
            int32_t offsetLoc;
            BS_ARCHIVE(bitcode::MC,  ar, offsetLastH, "offset last handle");
            BS_ARCHIVE(bitcode::MC , ar, offsetLoc,   "offset loc");
            lastHandle += offsetLastH;
            lastOffset += offsetLoc;
            m_objMapItems.push_back(OcBsDwgObjectMapItem(lastHandle, 
                lastOffset));
        }
        // calc section crc
        uint16_t crc, calcedCrc = ar.CalcedCRC(true); 
        ar.ReadCRC(crc);
        if(crc != calcedCrc) {
            LOG(ERROR) << "Data section CRC for Object Map is incorrect";
            return OcApp::eInvalidCRCInObjectMap;
        }
        sectionNumber++;
    }
    // calc final crc
    uint16_t crc, calcedCrc = ar.CalcedCRC(true);
    ar.ReadCRC(crc);
    if(crc != calcedCrc) {
        LOG(ERROR) << "CRC for Object Map is incorrect";
        return OcApp::eInvalidCRCInObjectMap;
    }

    VLOG(3) << "Successfully decoded Object map";
    return OcApp::eOk;
}

DwgInArchive& operator>>(DwgInArchive& ar, OcBsDwgObjectMap & hdr)
{
    ASSERT_ARCHIVE_NOT_LOADING;
    ar.SetError(hdr.DecodeData(ar));
    return ar;
}


END_OCTAVARIUM_NS