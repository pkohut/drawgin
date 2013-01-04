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
#include "OcDbObjectId.h"

BEGIN_OCTAVARIUM_NS

OcDbObjectId::OcDbObjectId(void)
: m_handle(0)
{
}

OcDbObjectId::~OcDbObjectId(void)
{
}

std::wstring OcDbObjectId::ToString() const
{
    return L"Function not implemented";
}

void OcDbObjectId::Handle( const int64_t handle )
{
    m_handle = handle;
}

const int64_t & OcDbObjectId::Handle( void ) const
{
    return m_handle;
}




std::ostream& operator <<(std::ostream& out, const OcDbObjectId& objId)
{
//    return LogWString(out, objId.ToString());
    out << std::hex << std::showbase << objId.Handle();
    return out;
}




END_OCTAVARIUM_NS

