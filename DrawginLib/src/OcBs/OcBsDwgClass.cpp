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
#include "OcBsDwgClass.h"
#include "OcBsStreamIn.h"

BEGIN_OCTAVARIUM_NS

OcBsDwgClass::OcBsDwgClass(void)
{
    VLOG_FUNC_NAME;
}


OcBsDwgClass::~OcBsDwgClass(void)
{
    VLOG_FUNC_NAME;
}

OcApp::ErrorStatus OcBsDwgClass::ReadDwg(OcBsStreamIn & in)
{
    VLOG_FUNC_NAME;
    VLOG(4) << "OcBsDwgClass::ReadDwg entered";
    BS_STREAMIN(bitcode::BS, in, ClassNumber(), "class number");

    if(ClassNumber() < 500)
    {
        int y =0;
        y++;
    }

    if(in.Version() <= R2004)
    {
        BS_STREAMIN(bitcode::BS, in, Version(), "version");
    }

    if(in.Version() >= R2007)
    {
        BS_STREAMIN(bitcode::BS, in, ProxyFlags(), "proxy flags");
    }

    if(in.Version() <= R2004)
    {
        BS_STREAMIN(bitcode::TV, in, AppName(), "app name");
        BS_STREAMIN(bitcode::TV, in, CppClassName(), "cpp ClassName");
        BS_STREAMIN(bitcode::TV, in, DxfClassName(), "class DXF name");
    }
    else
    {
        BS_STREAMIN(bitcode::TU, in, AppName(), "app name");
        BS_STREAMIN(bitcode::TU, in, CppClassName(), "cpp ClassName");
        BS_STREAMIN(bitcode::TU, in, DxfClassName(), "class DXF name");
    }

    BS_STREAMIN(bitcode::B,  in, WasAZombie(), "was a zombie");
    BS_STREAMIN(bitcode::BS, in, ItemClassId(), "item class id");

    if(in.Version() >= R2004)
    {
        BS_STREAMIN(bitcode::BL, in, NumberOfObjects(), "number of objects");

        if(in.Version() == R2004)
        {
            BS_STREAMIN(bitcode::BS, in, DwgVersion(), "dwg version");
            BS_STREAMIN(bitcode::BS, in, MaintenanceVersion(),
                        "maintenance version");
        }
        else
        {
            BS_STREAMIN(bitcode::BL, in, DwgVersion(), "dwg version");
            BS_STREAMIN(bitcode::BL, in, MaintenanceVersion(),
                        "maintenance version");
        }

        BS_STREAMIN(bitcode::BL, in, Unknown1(), "unknown1");
        BS_STREAMIN(bitcode::BL, in, Unknown2(), "unknown2");
    }

    VLOG(4) << "Successfully decoded Class";
    return OcApp::eOk;
}

END_OCTAVARIUM_NS