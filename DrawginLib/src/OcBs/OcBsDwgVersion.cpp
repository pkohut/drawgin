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
#include "OcBsDwgVersion.h"

using namespace std;
BEGIN_OCTAVARIUM_NS

const static std::array<OcBsDwgVersion::Pair, 7> pairs =
{
    OcBsDwgVersion::Pair("", NONE),
    OcBsDwgVersion::Pair("AC1012", R13),
    OcBsDwgVersion::Pair("AC1014", R14),
    OcBsDwgVersion::Pair("AC1015", R2000),
    OcBsDwgVersion::Pair("AC1018", R2004),
    OcBsDwgVersion::Pair("AC1021", R2007),
    OcBsDwgVersion::Pair("AC1024", R2010),
};


OcBsDwgVersion::OcBsDwgVersion(void)
{
    VLOG_FUNC_NAME;
}


OcBsDwgVersion::~OcBsDwgVersion(void)
{
    VLOG_FUNC_NAME;
}

DWG_VERSION OcBsDwgVersion::GetVersionId(const std::string & sVersion)
{
    VLOG_FUNC_NAME;

for(auto & it : pairs)
    {
        if(sVersion == it.first)
        {
            return it.second;
        }
    }

    return NONE;
}

const std::string & OcBsDwgVersion::GetVersionId(DWG_VERSION nVersionId)
{
    VLOG_FUNC_NAME;

for(auto & it : pairs)
    {
        if(nVersionId == it.second)
        {
            return it.first;
        }
    }

    return pairs[NONE].first;
}

size_t OcBsDwgVersion::Size()
{
    VLOG_FUNC_NAME;
    return pairs.size();
}

END_OCTAVARIUM_NS