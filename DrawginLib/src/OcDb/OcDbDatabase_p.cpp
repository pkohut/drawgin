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
#include "OcDbDatabase_p.h"
#include "..\OcBs\OcBsStreamIn.h"
#include "..\OcBs\OcBsDwgFileHeader.h"
#include "..\OcBs\OcBsDwgPreviewImage.h"
#include "..\OcBs\OcBsDatabaseHeaderVars.h"
#include "..\OcBs\OcBsDwgClasses.h"
#include "..\OcBs\OcBsDwgObjectMap.h"
#include "..\OcBs\OcBsDwgSecondFileHeader.h"
#include "..\OcBs\OcBsDwgDataSection.h"

BEGIN_OCTAVARIUM_NS

OcDbDatabasePrivate::OcDbDatabasePrivate(void)
{
    VLOG_FUNC_NAME;
}

OcDbDatabasePrivate::OcDbDatabasePrivate(OcDbDatabase * q)
    : OcObjectPrivate(q)
{
    VLOG_FUNC_NAME;
}


OcDbDatabasePrivate::~OcDbDatabasePrivate(void)
{
    VLOG_FUNC_NAME;
    m_qPtr = nullptr;
}

OcApp::ErrorStatus OcDbDatabasePrivate::ReadDwg(const std::string & sFilename)
{
    VLOG_FUNC_NAME;
    VLOG(4) << "OcDbDatabasePrivate::ReadDwg entered";

    OcBsStreamIn in;
    in.Open(sFilename);
    if(!in)
    {
        return OcApp::eOpeningFile;
    }

    OcBsDwgFileHeader dwgHdr;
    OcApp::ErrorStatus es;
    es = dwgHdr.ReadDwg(in);
    if(es != OcApp::eOk)
    {
        LOG(ERROR) << "Error processing drawing file header";
        return es;
    }

    if(dwgHdr.IsR13c3OrHigher())
    {
        // file position should match offset value in the IMAGE SEEKER
        CHECK(dwgHdr.ImageSeeker() == in.FilePosition())
                << "IMAGE SEEKER offset does not match current file position";
        OcBsDwgPreviewImage imgData;
        es = imgData.ReadDwg(in);
        if(es != OcApp::eOk)
        {
            LOG(ERROR) << "Error processing image data";
            return es;
        }

        // current file position should match the offset stored in the
        // section locator record 0, which is the "drawing variables"
        CHECK(dwgHdr.Record(0).seeker == in.FilePosition())
                << "Section locator record 0 offset does not match current file position";

        OcDbDatabasePrivate * pThis = this;
        OcBsDatabaseHeaderVars hdrVars;
        es = hdrVars.ReadDwg(in, pThis);
        if(es != OcApp::eOk)
        {
            LOG(ERROR) << "Error processing drawing header variables";
            return es;
        }

        // current file position should match the offset stored in the
        // section locator record 1, which is the "classes section"
        CHECK(dwgHdr.Record(1).seeker == in.FilePosition())
                << "Section locator record 1 offset does not match current file position";

        OcBsDwgClasses dwgClasses;
        es = dwgClasses.ReadDwg(in);
        if(es != OcApp::eOk)
        {
            LOG(ERROR) << "Error processing classes section";
            return es;
        }

        // The AcRxObject base type should not be in the drawing,
        // but need to know for sure. Log these other types too, to
        // see if they ever show up. Don't think they will.
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

        auto filePos = in.FilePosition();
        // Read the Object Map portion from the file. When
        // done, OcDfDwgObjectMap will have a collection
        // that tells where in the dwg file objects are located.
        OcBsDwgObjectMap dwgObjMap(dwgHdr.Record(2).seeker,
                                   dwgHdr.Record(2).size);
        es = dwgObjMap.ReadDwg(in);
        if(es != OcApp::eOk)
        {
            LOG(ERROR) << "Error processing object map section";
            return es;
        }

        if(in.Version() == R13 || in.Version() == R14)
        {
            // Read the second file header section. Note, this sections is
            // located immediately after the OcDfDgObjectMap
            OcBsDwgSecondFileHeader dwgSecondHeader;
            es = dwgSecondHeader.ReadDwg(in);
        }

        OcBsDwgDataSection dwgDataSection(dwgHdr.Record(4).seeker, dwgHdr.Record(4).size);
        es = dwgDataSection.ReadDwg(in);
        if(es != OcApp::eOk)
        {
            LOG(ERROR) << "Error processing data section";
            return es;
        }
        // Add code to read the Spec section 20, AcDb::Template.
        //
        // Add code to read the Spec section 21, Data section AcDb::Handles(object map)
        //
        // Decode all of the objects that are in the object map
        // collection.
        es = dwgObjMap.DecodeObjects(in, dwgClasses);
        if(es != OcApp::eOk)
        {
            LOG(ERROR) << "Error processing objects";
            return es;
        }
    }

    return OcApp::eOk;
}

END_OCTAVARIUM_NS
