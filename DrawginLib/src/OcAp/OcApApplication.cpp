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

#include <boost/shared_ptr.hpp>

#include "OcCommon.h"
#include "OcError.h"
#include "OcDbSmartPtrs.h"
#include "OcRxObject.h"
#include "OcDbDatabase.h"

#include "OcApApplication.h"

BEGIN_OCTAVARIUM_NS
using namespace std;
using namespace boost;

OcApApplication * OcApApplication::m_pApplication = NULL;

OcApApplicationPtr Application(void)
{
    return OcApApplication::Application();
}

OcApApplication::OcApApplication(void)
{
}

OcApApplication::~OcApApplication(void)
{
    // Do not delete m_pApplication, just set it to NULL.
    m_pApplication = NULL;
}

OcDbDatabasePtr OcApApplication::WorkingDatabase(void)
{
    return m_database;
}

void OcApApplication::SetWorkingDatabase(OcDbDatabasePtr database)
{
    m_database = database;
}

octavarium::OcApApplicationPtr OcApApplication::Create(void)
{
    if(!m_pApplication) {
        m_pApplication = new OcApApplication;
    }
    return m_pApplication;
}

octavarium::OcApApplicationPtr OcApApplication::Application(void)
{
    // Don't call Create if m_pApplication is NULL, it returns a smart pointer
    // and will go out of scope when this function ends.
    DLOG_IF(ERROR, !m_pApplication) << "OcApApplication instance is NULL.";
    return m_pApplication;
}

void OcApApplication::Shutdown(void)
{

}

END_OCTAVARIUM_NS