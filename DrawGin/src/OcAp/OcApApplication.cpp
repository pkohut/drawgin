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

OC_DEFINE_CLASS(OcApApplication, OcRxObject)

OcApApplication * OcApApplication::m_pApplication = NULL;
boost::shared_ptr<OcApApplication::RegClasses >OcApApplication::m_classes;


OcApApplicationPtr Application(void)
{
    return OcApApplication::Application();
}

OcApApplication::OcApApplication(void)
{
    INIT_OBJECT_NAME_FOR_DEBUG();
}

OcApApplication::~OcApApplication(void)
{
    // Do not delete m_pApplication, just set it to NULL.
    m_pApplication = NULL;
    m_classes.reset();
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
    OcRxObject::ShutdownObjectTracking();
}

int OcApApplication::RegisterRxClass(const std::wstring & className, OcRxObject::BaseClassFactory * pCreator)
{
    if(!m_classes)
        m_classes.reset(new OcApApplication::RegClasses);
    m_classes->insert(OcApApplication::RegClass(className, pCreator));
    return 0;
}

octavarium::OcRxObjectPtr OcApApplication::NewRxClass(const std::wstring & className)
{
    if(m_classes->find(className) != (*m_classes).end()) {
        return (*m_classes)[className]->createInstance();
//        OcRxObject::BaseClassFactory * f = (*m_classes)[className];
//        return f->createInstance();

    }
    return NULL;
}

END_OCTAVARIUM_NS