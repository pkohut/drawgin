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

#ifndef OcApApplication_h__
#define OcApApplication_h__
BEGIN_OCTAVARIUM_NS

OcApApplicationPtr Application(void);
//void ShutdownApplication(void);

class OcDbDatabase;

class OcApApplication : public OcRxObject
{
protected:
    OcApApplication(void);
public:
    virtual ~OcApApplication(void);

    OcDbDatabasePtr WorkingDatabase(void);
    void SetWorkingDatabase(OcDbDatabasePtr database);

    // Factory class to create the singleton of this class.
    // m_pApplication points back to this class, so do not manually
    // delete it, just set it to NULL in the destructor.
    static OcApApplicationPtr Create(void);

    // Returns a smart pointer of the single OcApApplication raw pointer.
    // This is the preferred method to get this instance.
    // Note: although it would be tempting to check if if m_pApplication
    // is NULL and then return a new pointer, don't do it.
    // The proper way to create the singleton is by calling the
    // OcApApplication::Create function with the application.
    static OcApApplicationPtr Application(void);

    // Function only has purpose in debug mode and with
    // OC_DEBUG_LIVING_OBJECTS defined.
    // Let OcRxObject do final object check of managed objects to ensure
    // they have been released property.
    // This function should be called right before the application exits.
    // Not calling it will produce memory leaks.
    // If OC_DEBUG_LIVING_OBJECTS is not defined, then no need to call
    // the function.
    static void Shutdown(void);

private:
    OcDbDatabasePtr m_database;

    // A singleton object, managed by OcApApplication and created by
    // the OcApApplication::Create class factory. The object simply
    // points to the single instance of this class. Functions should
    // never return the raw pointer, also wrap it in a smart pointer.
    // In the destructor simply set to the pointer to NULL, never
    // delete it.
    static OcApApplication * m_pApplication;

};

END_OCTAVARIUM_NS

#endif // OcApApplication_h__
