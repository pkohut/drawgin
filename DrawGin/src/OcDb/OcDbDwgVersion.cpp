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

#include <algorithm>
#include <functional>
#include <boost/bind.hpp>


#include "OcCommon.h"
#include "OcDbDwgVersion.h"

BEGIN_OCTAVARIUM_NS
using namespace std;

OcDbDwgVersion::Pair pairs[] = { OcDbDwgVersion::Pair("", NONE),
                                 OcDbDwgVersion::Pair("AC1012", R13),
                                 OcDbDwgVersion::Pair("AC1014", R14),
                                 OcDbDwgVersion::Pair("AC1015", R2000),
                                 OcDbDwgVersion::Pair("AC1018", R2004),
                                 OcDbDwgVersion::Pair("AC1021", R2007),
                                 OcDbDwgVersion::Pair("AC1024", R2010),
                               };

const int OcDbDwgVersion::m_numberOfElements =
    sizeof(pairs) / sizeof(pairs[0]);

OcDbDwgVersion::OcDbDwgVersion(void)
{
}

OcDbDwgVersion::~OcDbDwgVersion(void)
{
}


DWG_VERSION OcDbDwgVersion::GetVersionId(const std::string & sVersion)
{
    for(int i = 0; i < size(); ++i) {
        if(sVersion == pairs[i].first)
            return pairs[i].second;
    }

    return NONE;
}

const std::string & OcDbDwgVersion::GetVersionId(DWG_VERSION nVersionId)
{
    for(int i = 0; i < size(); ++i) {
        if(nVersionId == pairs[i].second)
            return pairs[i].first;
    }
    return pairs[NONE].first;
}

END_OCTAVARIUM_NS
