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
#include "OcTypes.h"
#include "OcError.h"
#include "OcDbDwgVersion.h"
#include "OcDbObjectId.h"
#include "../OcBs/OcBsStreamIn.h"
#include "../OcBs/DwgInArchive.h"
#include "OcDbClass.h"
#include "../OcBs/OcBsDwgSentinels.h"

BEGIN_OCTAVARIUM_NS
using namespace std;


OcDbClass::OcDbClass()
    : m_classNum(0), m_version(0), m_proxyFlags(0), m_wasAZombie(false),
      m_itemClassId(0), m_numObjects(0), m_dwgVersion(0), m_maintVersion(0),
      m_unknown1(0), m_unknown2(0)
{
    VLOG(3) << "Constructor entered";
}

OcDbClass::~OcDbClass()
{
    VLOG(3) << "Destructor entered";
}

OcApp::ErrorStatus OcDbClass::DecodeData( DwgInArchive& in )
{
    VLOG(3) << "DecodeData entered";

    BS_ARCHIVE(bitcode::BS, in, m_classNum, "class number");

    if(in.Version() <= R2004)
        BS_ARCHIVE(bitcode::BS, in, m_version, "version");

    if(in.Version() >= R2007)
        BS_ARCHIVE(bitcode::BS, in, m_proxyFlags, "proxy flags");

    if(in.Version() <= R2004) {
        BS_ARCHIVE(bitcode::TV, in, m_appName, "app name");
        BS_ARCHIVE(bitcode::TV, in, m_cppClassName, "cpp ClassName");
        BS_ARCHIVE(bitcode::TV, in, m_dxfClassName, "class DXF name");
    } else {
        BS_ARCHIVE(bitcode::TU, in, m_appName, "app name");
        BS_ARCHIVE(bitcode::TU, in, m_cppClassName, "cpp ClassName");
        BS_ARCHIVE(bitcode::TU, in, m_dxfClassName, "class DXF name");
    }

    BS_ARCHIVE(bitcode::B,  in, m_wasAZombie, "was a zombie");
    BS_ARCHIVE(bitcode::BS, in, m_itemClassId, "item class id");

    if(in.Version() >= R2004) {
        BS_ARCHIVE(bitcode::BL, in, m_numObjects, "number of objects");
        if(in.Version() == R2004) {
            BS_ARCHIVE(bitcode::BS, in, m_dwgVersion, "dwg version");
            BS_ARCHIVE(bitcode::BS, in, m_maintVersion, "maintenance version");
        } else {
            BS_ARCHIVE(bitcode::BL, in, m_dwgVersion, "dwg version");
            BS_ARCHIVE(bitcode::BL, in, m_maintVersion, "maintenance version");
        }
        BS_ARCHIVE(bitcode::BL, in, m_unknown1, "unknown1");
        BS_ARCHIVE(bitcode::BL, in, m_unknown2, "unknown2");
    }
    
    VLOG(3) << "Successfully decoded Class";
    return OcApp::eOk;
}

DwgInArchive& operator>>(DwgInArchive& in, OcDbClass & dwgClass)
{
    ASSERT_ARCHIVE_NOT_LOADING(in);
    in.SetError(dwgClass.DecodeData(in));
    return in;
}

std::wstring OcDbClass::DxfClassName( void ) const
{
    return m_dxfClassName;
}

std::wstring OcDbClass::CppClassName( void ) const
{
    return m_cppClassName;
}




END_OCTAVARIUM_NS