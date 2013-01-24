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
#include "OcDbObject.h"
#include "OcDbEntity.h"

#include "../OcDf/OcDfDwgVersion.h"
#include "../OcBs/OcBsStreamIn.h"
#include "../OcBs/DwgInArchive.h"


BEGIN_OCTAVARIUM_NS

OcDbEntity::OcDbEntity(void)
{
}

OcDbEntity::~OcDbEntity(void)
{
}

OcApp::ErrorStatus OcDbEntity::DecodeData(DwgInArchive& ar)
{
    // common
    //     MS	:	Size of object, not including the CRC
    //     BS	:	Object type
    // R2000+ Only:
    //     RL	:	Size of object data in bits
    // Common:
    //     H	:	Object’s handle
    //     BS	:	Size of extended object data, if any
    //     X	:	Extended object data, if any
    //     B	:	Flag indicating presence of graphic image.
    //              if (graphicimageflag is 1) {
    //                  RL: Size of graphic image in bytes
    //                  X: The graphic image
    //              }
    // R13-R14 Only:
    //     RL	:	Size of object data in bits
    //     6B	:	Flags
    //     6B	:	Common parameters
    // R2000+ Only:
    //     B	:	0 if the previous and next linkers are present; 1 if they are BOTH defaults (1 back and 1 forward).
    //     BS	:	Entity color
    //     BD	:	Linetype Scale
    //     BB	:	Line type flags
    //          00 – BYLAYER linetype
    //          01 – BYBLOCK linetype
    //          10 – CONTINUOUS linetype
    //          11 – Indicates that a linetype handle will be stored in the handles section of the entity.
    //     BB	:	Plotstyle flags:
    //          00 – BYLAYER plotstyle
    //          01 – BYBLOCK plotstyle
    //          10 – CONTINUOUS plotstyle
    //          11 – Indicates that a plotstyle handle will be stored in the handles section of the entity.
    // R2007+:
    //     BB	:	Material flags:
    //          00 – BYLAYER material
    //          01 – BYBLOCK material
    //          10 – global material?
    //          11 – Indicates that a material handle will be stored in the handles section of the entity.
    //     RC	:	Shadow flags
    // R2000+:
    //     BS	:	Invisible flag
    //     RC	:	Entity lineweight flag
    // Common:
    //     X	:	Object data (varies by type of object)
    //     X	:	Handles associated with this object
    //     RS	:	CRC
    return OcApp::eNotImplemented;
}

DwgInArchive& operator>>(DwgInArchive& ar, OcDbEntity & data)
{
    ASSERT_ARCHIVE_NOT_LOADING(ar);
    ar.SetError(data.DecodeData(ar));
    return ar;
}

END_OCTAVARIUM_NS