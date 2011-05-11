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

#include "OcRxObject.h"
#include "OcDbHardOwnershipId.h"
#include "OcDbDatabase.h"

#include "../OcBs/OcBsStreamIn.h"
#include "../OcBs/DwgInArchive.h"
#include "../OcBs/OcBsDwgFileHeader.h"
#include "../OcBs/OcBsDwgPreviewImage.h"

#include "OcDbHeaderVars.h"

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
        return OcApp::eOpeningFile;
    }

    DwgInArchive ar(in);
    if(!ar) {
        return ar.Error();
    }

    OcBsDwgFileHeader dwgHdr;
    ar >> dwgHdr;
    if(ar.Error() != OcApp::eOk) {
        return ar.Error();
    }
    if(dwgHdr.IsR13c3OrHigher()) {
        if(dwgHdr.NumSectionRecords() == 6) {
            if(dwgHdr.Record(6).seeker == ar.FilePosition()) {
                // records are zero based
                std::vector<byte_t> section6(dwgHdr.Record(5).size);
                ar.ReadRC((bitcode::RC*) &section6[0], section6.size());
            } else {
                return OcApp::eMismatchedFilePosition;
            }
        }
        assert(dwgHdr.ImageSeeker() == ar.FilePosition());
        OcBsDwgPreviewImage imgData;
        ar >> imgData;
        if(ar.Error() != OcApp::eOk) {
            return ar.Error();
        }
        assert(dwgHdr.Record(0).seeker == ar.FilePosition());
        OcDbHeaderVars hdrVars;
        ar >> hdrVars;
        if(ar.Error() != OcApp::eOk) {
            return ar.Error();
        }

        byte_t sentinel[16];
        ar.ReadRC((bitcode::RC*) sentinel, 16);
        int x = 0;
        x++;

    }

    return OcApp::eOk;
}


END_OCTAVARIUM_NS
