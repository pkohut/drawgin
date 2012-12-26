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

#ifndef OcDbSmartPtrs_h__
#define OcDbSmartPtrs_h__

BEGIN_OCTAVARIUM_NS

class OcApApplication;
class OcRxObject;
class OcDbObject;
class OcDbDatabase;
class OcDbEntity;

typedef OcPtr<OcApApplication>::value_type OcApApplicationPtr;
typedef OcPtr<OcRxObject>::value_type OcRxObjectPtr;
typedef OcPtr<OcDbObject>::value_type OcDbObjectPtr;
typedef OcPtr<OcDbDatabase>::value_type OcDbDatabasePtr;
typedef OcPtr<OcDbEntity>::value_type OcDbEntityPtr;

END_OCTAVARIUM_NS

#endif // OcDbSmartPtrs_h__
