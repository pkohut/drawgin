/****************************************************************************
**
** This file is part of DrawGin library. A C++ framework to read and
** write .dwg files formats.
**
** Copyright (C) 2011, 2012, 2013 Paul Kohut.
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
#include "OcCmColor.h"
#include "OcGePoint2D.h"
#include "OcGePoint3D.h"
#include "OcDbHardOwnershipId.h"

#include "OcDbDatabase.h"
#include "OcDbDatabase_p.h"

#include "../OcBs/OcBsStreamIn.h"
#include "../OcBs/DwgInArchive.h"
#include "../OcBs/OcBsDwgFileHeader.h"
#include "../OcBs/OcBsDwgPreviewImage.h"

#include "../OcDf/OcDfDatabaseHeaderVars.h"
#include "../OcDf/OcDfDwgClass.h"
#include "../OcDf/OcDfDwgClasses.h"
#include "../OcDf/OcDfDwgObjectMap.h"
#include "../OcDf/OcDfDwgSecondFileHeader.h"
#include "../OcDf/OcDfDwgDataSection.h"


BEGIN_OCTAVARIUM_NS


OcDbDatabasePimpl::OcDbDatabasePimpl( void )
//    :m_pHeaderImpl(new OcDbDatabaseHeaderImpl())
: unknown1(412148564080.0), unknown2(1.0), unknown3(1.0), unknown4(1.0),
unknown9(24)

{
}

OcDbDatabasePimpl::~OcDbDatabasePimpl(void)
{
    VLOG(4) << "Destructor entered";
    //delete m_pHeaderImpl;
}

OcApp::ErrorStatus OcDbDatabasePimpl::Open(const string_t & filename)
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
        // section locater record 0, which is the "drawing variables"
        CHECK(dwgHdr.Record(0).seeker == ar.FilePosition())
            << "Section locator record 0 offset does not "
            "match current file position";

        OcDbDatabasePimpl * pThis = this;
        OcDfDatabaseHeaderVars hdrVars(pThis);
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
        OcDfDwgClasses dwgClasses;
        ar >> dwgClasses;
        if(ar.Error() != OcApp::eOk) {
            LOG(ERROR) << "Error processing classes section";
            return ar.Error();
        }
        // The AcRxObject base type should not be in the drawing,
        // but need to know for sure. Log these other types too, to
        // see if they ever show up. Don't think they will.
        bool bFound = false;
        CHECK(!dwgClasses.Has(L"AcRxObject")) <<
            "Found suspicious class AcRxObject";
        CHECK(!dwgClasses.Has(L"AcRxClass")) <<
            "Found suspicious class AcRxClass";
        CHECK(!dwgClasses.Has(L"AcDbObject")) <<
            "Found suspicious class AcDbObject";
        CHECK(!dwgClasses.Has(L"AcObjectId")) <<
            "Found suspicious class AcObjectId";
        CHECK(!dwgClasses.Has(L"AcDbHandle")) <<
            "Found suspicious class AcDbHandle";
        int32_t filePos = ar.FilePosition();
        // Read the Object Map portion from the file. When
        // done, OcDfDwgObjectMap will have a collection
        // that tells where in the dwg file objects are located.
        OcDfDwgObjectMap dwgObjMap(dwgHdr.Record(2).seeker,
            dwgHdr.Record(2).size);
        ar >> dwgObjMap;
        if(ar.Error() != OcApp::eOk) {
            LOG(ERROR) << "Error processing object map section";
            return ar.Error();
        }
        if(ar.Version() == R13 || ar.Version() == R14)
        {
            // Read the second file header section. Note, this sections is
            // located immediately after the OcDfDgObjectMap
            OcDfDwgSecondFileHeader dwgSecondHeader;
            ar >> dwgSecondHeader;
        }
        OcDfDwgDataSection dwgDataSection(dwgHdr.Record(4).seeker, dwgHdr.Record(4).size);
        ar >> dwgDataSection;
        if(ar.Error() != OcApp::eOk) {
            LOG(ERROR) << "Error processing data section";
            return ar.Error();
        }
        // Add code to read the Spec section 20, AcDb::Template.
        //
        // Add code to read the Spec section 21, Data section AcDb::Handles(object map)
        //
        // Decode all of the objects that are in the object map
        // collection.
        dwgObjMap.DecodeObjects(ar, pThis, dwgClasses);
        if(ar.Error() != OcApp::eOk) {
            LOG(ERROR) << "Error processing objects";
            return ar.Error();
        }
    }
    return OcApp::eOk;
}

END_OCTAVARIUM_NS