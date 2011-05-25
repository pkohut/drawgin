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



//#include "stdafx.h"
#include "OcCommon.h"
#include "OcError.h"
#include "OcDbDwgVersion.h"

#include "OcGePoint2D.h"
#include "OcGePoint3D.h"

#include "OcRxObject.h"
#include "OcDbHardOwnershipId.h"
#include "OcDbDatabase.h"

#include "../OcBs/OcBsStreamIn.h"
#include "../OcBs/DwgInArchive.h"
#include "../OcBs/OcBsDwgFileHeader.h"
#include "../OcBs/OcBsDwgPreviewImage.h"

#include "OcDbHeaderVars.h"
#include "OcDbClass.h"
#include "OcDbClasses.h"

BEGIN_OCTAVARIUM_NS


OcDbDatabase::OcDbDatabase(void)
{
    INIT_OBJECT_NAME_FOR_DEBUG();
}

OcDbDatabase::~OcDbDatabase(void)
{
}

OcApp::ErrorStatus OcDbDatabase::Open(const string_t & filename)
{
    OcBsStreamIn in;
    in.Open(filename);
    if(!in) {
        // OcBsStreamIn::Open will log any errors
        return OcApp::eOpeningFile;
    }

    DwgInArchive ar(in);
    if(!ar) {
        LOG(ERROR) << "Error opening archive stream";
        return ar.Error();
    }

    // parse the dwgHdr
    OcBsDwgFileHeader dwgHdr;
    ar >> dwgHdr;
    if(ar.Error() != OcApp::eOk) {
        LOG(ERROR) << "Error processing drawing file header";
        return ar.Error();
    }

    // Read R13c3 or higher file formats
    if(dwgHdr.IsR13c3OrHigher()) {
        // file position should match offset value stored in the IMAGE SEEKER
        CHECK(dwgHdr.ImageSeeker() == ar.FilePosition())
                << "IMAGE SEEKER offset does not match current file position";

        OcBsDwgPreviewImage imgData;
        ar >> imgData;
        if(ar.Error() != OcApp::eOk) {
            LOG(ERROR) << "Error processing data";
            return ar.Error();
        }

        // current file position should match the offset stored in the
        // section locator record 0, which is the "drawing variables"
        CHECK(dwgHdr.Record(0).seeker == ar.FilePosition())
                << "Section locator record 0 offset does not "
                "match current file position";

        OcDbHeaderVars hdrVars;
        ar >> hdrVars;
        if(ar.Error() != OcApp::eOk) {
            LOG(ERROR) << "Error processing drawing header variables";
            return ar.Error();
        }

        // current file position should match the offset stored in the
        // section locater record 1, which is the "classes section"
        CHECK(dwgHdr.Record(1).seeker == ar.FilePosition())
                << "Section locater record 1 offset does not "
                "match current file position";

        OcDbClasses dwgClasses;
        ar >> dwgClasses;
        if(ar.Error() != OcApp::eOk) {
            LOG(ERROR) << "Error processing classes section";
            return ar.Error();
        }

        OcApp::ErrorStatus es;
        if( (es = DecodeObjectMap(ar,
                                  dwgHdr.Record(2).seeker,
                                  dwgHdr.Record(2).size))
                != OcApp::eOk) {
            return es;
        }
    }

    return OcApp::eOk;
}

OcApp::ErrorStatus OcDbDatabase::DecodeObjectMap(DwgInArchive & ar, int32_t fileOffset,
        int32_t dataSize)
{
    VLOG(3) << "DecodeObjectMap entered";
    // do some sanity checks before trying to read the object map
    if(fileOffset == 0) {
        LOG(ERROR) << "Invalid file offset position for Object Map";
        return OcApp::eInvalidObjectMapOffset;
    }

    // set file position to the Object Map offset
    ar.Seek(fileOffset);
    if(ar.Error() != OcApp::eOk) {
        LOG(ERROR) << "Error setting file position";
        return ar.Error();
    }

    // section size and crc are stored in big endian format.
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

        // endSection includes the 2 byte crc for this section, so
        // exclude 2 bytes when doing the loop.
        int32_t endSection = ar.FilePosition() + sectionSize;
        while(ar.FilePosition() < endSection - 2) {
            int32_t offsetLastH;
            int32_t offsetLoc;
            BS_ARCHIVE(bitcode::MC,  ar, offsetLastH, "offset last handle");
            BS_ARCHIVE(bitcode::MC , ar, offsetLoc,   "offset loc");
        }
        // calc section crc
        uint16_t crc, calcedCrc = ar.CalcedCRC(true); 
        ar.ReadCRC(crc);
        if(crc != calcedCrc) {
            LOG(ERROR) << "Data section CRC for Object Map is incorrect";
            return OcApp::eInvalidCRCInObjectMap;
        }
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

END_OCTAVARIUM_NS
