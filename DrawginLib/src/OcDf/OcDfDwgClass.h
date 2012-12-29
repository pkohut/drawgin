/**
 *	@file
 *  @brief Defines class types found in the drawing
 *
 *  Defines the classes found in a drawing file.
 */

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

#ifndef OCDFDWGCLASS_H
#define OCDFDWGCLASS_H

#include "templates/accessors.h"
#include "templates/bounded.h"

BEGIN_OCTAVARIUM_NS

/**
 *	\brief Class information within the .dwg file
 *
 *  Dynamic class information defined in the drawing file. Instances of
 *  the OcDfDwgClass are kept in OcDbClasses for future lookup.
 */
class OcDfDwgClass
{
public:
    /**
     *	Ctor
     */
    OcDfDwgClass();

    /**
     *	Dtor
     */
    virtual ~OcDfDwgClass();

    /*-------------------- Common --------------------*/

    /**
     *	Sets or gets the class number.<br>
     *  The class numbers are >= 500 and used when AcDbObject and
     *  AcDbEntity derived objects are being serialized.<br>
     *  The class number associated with a certain class is probably
     *  per drawing dependent.
     *  @acversion common
     */
    accessors<int16_t> ClassNumber;

    /*------------------ R13 - R2004 -----------------*/

    /**
     *	Sets or gets the version value of the object.<br>
     *  In R14, the .dwg specs say this value is used as a flag to
     *  indicate the object can be moved or edited, etc.
     *  @return the value
     *  @acversion R13 - R2004
     *  @investigate to determine what the actual flag values are.
     */
    accessors<int16_t> Version;

    /*-------------------- R2007+ --------------------*/

    /**
     *  Sets or gets the proxy flag(s).<br>
     *  @acversion 2007+
     *  @investigate to determine the proxy flag(s) meaning.
     */
    accessors<int16_t> ProxyFlags;


    /**
     *  Sets or gets the application name associated with the defined
     *  class type.<br>
     *  associated with.<br>
     *  @acversion common
     *  @investigate the names used for built in ARX classes
     */
    accessors<std::wstring> AppName;

    /**
     *	The DXF name for the class. The name can be empty for classes
     *  not derived from AcDbObject. When filing the class use NULL
     *  for empty strings.
     *  @return The DXF class name.
     *  @acversion common
     */
    accessors<std::wstring> DxfClassName;

    /**
     *	The C++ name for the class (the ARX class)
     *  @acversion common
     */
    accessors<std::wstring> CppClassName;

    /**
     *  Gets or sets a bool flag to indicate this object is a proxy object.
     *	@acversion common
     */
    accessors<bool> WasAZombie;

    /**
     *  Flag indicating object or entity type class.<br>
     *  Valid values are:<br>
     *      0x1F2 for entity classes<br>
     *      0x1F3 for object classes
     *  @acversion common
     */
    bounded<int, 0x1F2, 0x1F3> ItemClassId;



    /*--------------------- R2004+ -------------------*/

    /**
     *   Returns the number of objects of this type in the drawing database.
     *   @acversion R2004+
     */
    accessors<int32_t> NumberOfObjects;


    /**
     *	The AC release that was current when the class was introduced.
     *  acversion 2004+
     */
    accessors<int32_t> DwgVersion;

    /**
     *	Maintenance value, can be set to any value for custom classes.
     *  Built in AC ARX classes have the value set to 0 when the drawing
     *  version changes.
     *  acversion 2004+
     */
    accessors<int32_t> MaintenanceVersion;


    /**
     *	Unknown value
     *  @acversion 2004+
     *  @investigate
     */
    accessors<int32_t> Unknown1;

    /**
     *	Unknown value
     *  @return .dwg specs say normally 0L
     *  @acversion 2004+
     *  @investigate
     */
    accessors<int32_t> Unknown2;


private:
    OcApp::ErrorStatus DecodeData(DwgInArchive& in);
    friend DwgInArchive& operator>>(DwgInArchive& in,
                                    OcDfDwgClass & dwgClass);
};

END_OCTAVARIUM_NS

#endif // OCDFDWGCLASS_H
