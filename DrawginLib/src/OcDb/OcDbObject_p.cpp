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
#include "OcTypes.h"
#include "OcDbObjectId.h"
#include "OcDbObject_p.h"
#include "OcDbObject.h"


#include "../OcDf/OcDfDwgVersion.h"
#include "../OcBs/OcBsStreamIn.h"
#include "../OcBs/DwgInArchive.h"


BEGIN_OCTAVARIUM_NS
using namespace std;

OcDbObjectImpl::OcDbObjectImpl(void)
    :m_qPtr(NULL)
{
}

OcDbObjectImpl::~OcDbObjectImpl(void)
{
    m_qPtr = NULL;
}

OcApp::ErrorStatus OcDbObjectImpl::DecodeData(DwgInArchive& ar)
{
    //     MS size of object, not including the CRC
    //     BS object type
    // R2000+
    //     RL size of object in bits
    // common
    //     H object handle
    //     BS size of extended object data
    //     X extended object data
    // R13-R14
    //     RL size of object data in bits
    // common
    //     X Object data
    // R2007+
    //     X string data (optional)
    //     B string stream present bit
    // common
    //     X handles associated with this object
    //     RS crc
    int32_t objSize;
    BS_ARCHIVE(bitcode::MS, ar, objSize, "Object size = ");
    int16_t objType;
    BS_ARCHIVE(bitcode::BS, ar, objType, "Object type = ");
    int32_t objSizeInBits;

    if(ar.Version() >= R2000)
    {
        BS_ARCHIVE(bitcode::RL, ar, objSizeInBits, "Object size in bits = ");
    }

    OcDbObjectId objId;
    BS_ARCHIVE(OcDbObjectId, ar, objId, "Object handle = ");
    int16_t extendedObjSize;
    BS_ARCHIVE(bitcode::BS, ar, extendedObjSize, "extended object data size = ");

    if(extendedObjSize)
    {
    }

    if(ar.Version() == R13 || ar.Version() == R14)
    {
        BS_ARCHIVE(bitcode::RL, ar, objSizeInBits, "Object size in bits = ");
    }

    // read object data

    if(ar.Version() >= R2007)
    {
        // read string data
        // get string stream data
    }

    vector<OcDbObjectId> objHandles;
    uint16_t crc = 0;
    return OcApp::eNotImplemented;
}

octavarium::OcDbObjectId OcDbObjectImpl::ObjectId(void) const
{
    return m_objectId;
}

DwgInArchive& operator>>(DwgInArchive& ar, OcDbObjectImpl & data)
{
    ASSERT_ARCHIVE_NOT_LOADING(ar);
    ar.SetError(data.DecodeData(ar));
    return ar;
}


END_OCTAVARIUM_NS