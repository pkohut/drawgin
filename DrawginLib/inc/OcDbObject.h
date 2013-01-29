/**
 *	@file
 *  @brief Defines OcDbObject class
 *
 *  Defines the OcDbObject base class found in a drawing file.
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

#include "OcObjectDef.h"
#include "OcGiDrawable.h"

BEGIN_OCTAVARIUM_NS

class OcDbObjectPrivate;
EXPIMP_TEMPLATE template class DRAWGIN_API std::unique_ptr<OcDbObjectPrivate>;

class DRAWGIN_API OcDbObject : public OcGiDrawable
{
    DISABLE_COPY(OcDbObject);
public:
    OcDbObject(void);
    virtual ~OcDbObject(void);

    virtual OcGiDrawable * Drawable(void);
    virtual bool isPersistent(void) const;

protected:
    explicit OcDbObject(std::unique_ptr<OcDbObjectPrivate> d);
    virtual OcDbObjectPrivate * d_func();
    virtual const OcDbObjectPrivate * d_func() const;

protected:
    std::unique_ptr<OcDbObjectPrivate> m_pImpl;


};


END_OCTAVARIUM_NS