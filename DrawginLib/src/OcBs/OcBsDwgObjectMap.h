/**
 *	@file
 *  @brief Defines OcBsDwgObjectMap class
 *
 *  Used to encode the "object map" section of drawing files
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

#pragma once

BEGIN_OCTAVARIUM_NS

class OcBsStreamIn;
class OcBsDwgClasses;

class OcBsDwgObjectMap
{
public:
    OcBsDwgObjectMap(int32_t objMapFilePos, int32_t objMapSize);
    virtual ~OcBsDwgObjectMap(void);

    OcApp::ErrorStatus ReadDwg(OcBsStreamIn & in);
    OcApp::ErrorStatus DecodeObjects(OcBsStreamIn & in, const OcBsDwgClasses & classes);

private:
    int32_t m_objMapFilePos;
    int32_t m_objMapSize;

    typedef std::pair<int32_t, int32_t> MapItem;
    std::vector<std::pair<int32_t, int32_t> > m_objMapItems;
};

END_OCTAVARIUM_NS