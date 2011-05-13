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



/**************************************************************************/
/*  Portions of code from the Visualization Library                       */
/*  which used the "New BSD" license, see "COPYING" for full license      */
/*  notice http://www.visualizationlibrary.com                            */
/*                                                                        */
/*  Copyright (c) 2005-2010, Michele Bosi                                 */
/*  All rights reserved.                                                  */
/**************************************************************************/


#include "stdafx.h"
#include "OcCommon.h"
#include "OcRxObject.h"

BEGIN_OCTAVARIUM_NS


#if OC_DEBUG_LIVING_OBJECTS && !defined(NDEBUG)
std::set<OcRxObject *> *OcRxObject::m_debug_LivingObjects = NULL;
#endif

OcRxObject::~OcRxObject(void)
{
    DLOG_IF(ERROR, m_nReferences && !AutomaticDelete())
            << "Object " << m_sObjectName << "is being deleted having still "
            << m_nReferences << "references. Possible causes:\n"
            << "- illegal use of the 'delete' operator on an object.h Use OcPtr<> instead.\n"
            << "- explicit call to Object::incReference().\n\n";

#if OC_DEBUG_LIVING_OBJECTS && !defined(NDEBUG)
    DebugLivingObjects()->erase(this);
#endif
}

void OcRxObject::ShutDown(void)
{
#if OC_DEBUG_LIVING_OBJECTS && !defined(NDEBUG)
    DLOG_IF(ERROR, DebugLivingObjects()->size())
            << "m_debug_LivingObject still has "
            << DebugLivingObjects()->size() << " live items.\n";

    OcRxObject::m_debug_LivingObjects->clear();
    delete OcRxObject::m_debug_LivingObjects;
    OcRxObject::m_debug_LivingObjects = NULL;
#endif
}

END_OCTAVARIUM_NS
