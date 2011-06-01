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

#include "OcCommon.h"
#include "OcError.h"
#include "OcDbSmartPtrs.h"
#include "OcRxObject.h"
#include "OcDbDatabase.h"



#include "OcApApplication.h"

BEGIN_OCTAVARIUM_NS

// A singleton object, managed by OcApApplication and created by
// the OcApApplication::Create class factory. The object is under
// control a smart pointer and should never be deleted manually.
// Simply NULL g_pOcApplication in OcApApplication's destructor.
OcApApplication * g_pOcApplication = NULL;

// Returns a smart pointer of the single OcApApplication instance.
// This is the preferred method to get the instance.
OcApApplicationPtr Application(void)
{
    DLOG_IF(ERROR, !g_pOcApplication) << "OcApApplication instance is NULL.";
    return g_pOcApplication;
}

// Function only has purpose in debug mode and with
// OC_DEBUG_LIVING_OBJECTS defined.
// Let OcRxObject do final object check of managed objects to ensure
// they have been released property.
// This function should be called right before the application exits.
// Not calling it will produce memory leaks.
// If OC_DEBUG_LIVING_OBJECTS is not defined, then no need to call
// the function.
void ShutdownApplication(void)
{
    OcRxObject::ShutDown();
}

OcApApplication::OcApApplication(void)
{
    INIT_OBJECT_NAME_FOR_DEBUG();
}

OcApApplication::~OcApApplication(void)
{
    // Don't delete g_pOcApplication, just set it to NULL.
    g_pOcApplication = NULL;
}

OcDbDatabasePtr OcApApplication::WorkingDatabase(void)
{
    return m_database;
}

void OcApApplication::SetWorkingDatabase(OcDbDatabasePtr database)
{
    m_database = database;
}

// Factory class. Returns a shared pointer to the singleton
// instance of g_pOcApplication.
// Do not manually delete g_pOcApplication.
octavarium::OcApApplicationPtr OcApApplication::Create(void)
{
    if(!g_pOcApplication) {
        g_pOcApplication = new OcApApplication;
    }
    return g_pOcApplication;
}

END_OCTAVARIUM_NS