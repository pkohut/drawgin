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

#ifndef OcDfDwgVersion_h__
#define OcDfDwgVersion_h__

BEGIN_OCTAVARIUM_NS

enum DWG_VERSION { NONE = 0, R13, R14, R2000, R2004, R2007, R2010, };

class OcDfDwgVersion
{
public:
    typedef std::pair<std::string, DWG_VERSION> Pair;
//    typedef std::vector<Pair> Pairs;

    static DWG_VERSION GetVersionId(const std::string & sVersion);
    static const std::string & GetVersionId(DWG_VERSION nVersionId);
    static int size(void)
    {
        return m_numberOfElements;
    }

private:
    OcDfDwgVersion();
    virtual ~OcDfDwgVersion();
    static const int m_numberOfElements;
//    static const Pairs m_versions;
};

END_OCTAVARIUM_NS


#endif // OcDfDwgVersion_h__
