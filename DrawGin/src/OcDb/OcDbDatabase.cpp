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
        // section locator record 1, which is the "classes section"
        CHECK(dwgHdr.Record(1).seeker == ar.FilePosition())
                << "Section locator record 1 offset does not "
                "match current file position";

        OcDbClasses dwgClasses;
        ar >> dwgClasses;
        if(ar.Error() != OcApp::eOk) {
            LOG(ERROR) << "Error processing classes section";
            return ar.Error();
        }


        // read the object map


    }

    return OcApp::eOk;
}


END_OCTAVARIUM_NS
