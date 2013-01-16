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

#ifndef OcDfDwgObjectMap_h__
#define OcDfDwgObjectMap_h__

BEGIN_OCTAVARIUM_NS

class OcDbDatabasePimpl;
class DwgInArchive;
class OcDfDwgClasses;
class OcDbObject;

class OcDfDwgObjectMap
{
public:
    OcDfDwgObjectMap(int32_t objMapFilePos, int32_t objMapSize);
    virtual ~OcDfDwgObjectMap(void);

    OcApp::ErrorStatus DecodeObjects(DwgInArchive& ar, OcDbDatabasePimpl *& pDb,
                                     const OcDfDwgClasses & classes);

private:
    typedef std::pair<int32_t, int32_t> MapItem;
    friend DwgInArchive& operator>>(DwgInArchive& ar, OcDfDwgObjectMap & imgData);
    OcApp::ErrorStatus DecodeData(DwgInArchive& ar);

    // pair::first = handle, pair::second = fileposition
    std::vector<std::pair<int32_t, int32_t> > m_objMapItems;

    int32_t m_objMapFilePos;
    int32_t m_objMapSize;

    
};

END_OCTAVARIUM_NS

#endif // OcDfDwgObjectMap_h__
