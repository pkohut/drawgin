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
#include "OcTypes.h"
#include "OcError.h"
#include "OcDfDwgVersion.h"
#include "OcDbObjectId.h"
#include "../OcBs/OcBsStreamIn.h"
#include "../OcBs/DwgInArchive.h"
#include "OcDfDwgClass.h"
#include "../OcBs/OcBsDwgSentinels.h"

BEGIN_OCTAVARIUM_NS
using namespace std;


OcDfDwgClass::OcDfDwgClass()
{
    VLOG(4) << "Constructor entered";
}

OcDfDwgClass::~OcDfDwgClass()
{
    VLOG(4) << "Destructor entered";
}

OcApp::ErrorStatus OcDfDwgClass::DecodeData(DwgInArchive& in)
{
    VLOG(4) << "DecodeData entered";

    BS_ARCHIVE(bitcode::BS, in, ClassNumber(), "class number");
    if(ClassNumber() < 500) {
        int y =0;
        y++;
    }

    if(in.Version() <= R2004)
        BS_ARCHIVE(bitcode::BS, in, Version(), "version");

    if(in.Version() >= R2007)
        BS_ARCHIVE(bitcode::BS, in, ProxyFlags(), "proxy flags");

    if(in.Version() <= R2004) {
        BS_ARCHIVE(bitcode::TV, in, AppName(), "app name");
        BS_ARCHIVE(bitcode::TV, in, CppClassName(), "cpp ClassName");
        BS_ARCHIVE(bitcode::TV, in, DxfClassName(), "class DXF name");
    } else {
        BS_ARCHIVE(bitcode::TU, in, AppName(), "app name");
        BS_ARCHIVE(bitcode::TU, in, CppClassName(), "cpp ClassName");
        BS_ARCHIVE(bitcode::TU, in, DxfClassName(), "class DXF name");
    }

    BS_ARCHIVE(bitcode::B,  in, WasAZombie(), "was a zombie");
    BS_ARCHIVE(bitcode::BS, in, ItemClassId(), "item class id");

    if(in.Version() >= R2004) {
        BS_ARCHIVE(bitcode::BL, in, NumberOfObjects(), "number of objects");
        if(in.Version() == R2004) {
            BS_ARCHIVE(bitcode::BS, in, DwgVersion(), "dwg version");
            BS_ARCHIVE(bitcode::BS, in, MaintenanceVersion(),
                       "maintenance version");
        } else {
            BS_ARCHIVE(bitcode::BL, in, DwgVersion(), "dwg version");
            BS_ARCHIVE(bitcode::BL, in, MaintenanceVersion(),
                       "maintenance version");
        }
        BS_ARCHIVE(bitcode::BL, in, Unknown1(), "unknown1");
        BS_ARCHIVE(bitcode::BL, in, Unknown2(), "unknown2");
    }

    VLOG(4) << "Successfully decoded Class";
    return OcApp::eOk;
}

DwgInArchive& operator>>(DwgInArchive& in, OcDfDwgClass & dwgClass)
{
    ASSERT_ARCHIVE_NOT_LOADING(in);
    in.SetError(dwgClass.DecodeData(in));
    return in;
}


END_OCTAVARIUM_NS