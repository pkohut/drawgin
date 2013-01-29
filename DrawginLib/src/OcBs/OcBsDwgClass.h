/**
 *	@file
 *  @brief Defines OcBsDwgClass class
 *
 *  Used to encode the "class" section of drawing files
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
#include "templates\accessors.h"
#include "templates\bounded.h"

BEGIN_OCTAVARIUM_NS

class OcBsStreamIn;

class OcBsDwgClass
{
public:
    OcBsDwgClass(void);
    virtual ~OcBsDwgClass(void);

    OcApp::ErrorStatus ReadDwg(OcBsStreamIn & in);

    /*-------------------- Common --------------------*/

    /**
     *	Sets or gets the class number.<br>
     *  The class numbers are >= 500 and used when AcDbObject and
     *  AcDbEntity derived objects are being serialized.<br>
     *  The class number associated with a certain class is probably
     *  per drawing dependent.
     *  @acversion common
     */
    //accessors<int16_t> ClassNumber;
    int16_t ClassNumber() const
    {
        return m_classNumber;
    }
    void ClassNumber(int16_t val)
    {
        m_classNumber = val;
    }


    /*------------------ R13 - R2004 -----------------*/

    /**
     *	Sets or gets the version value of the object.<br>
     *  In R14, the .dwg specs say this value is used as a flag to
     *  indicate the object can be moved or edited, etc.
     *  @return the value
     *  @acversion R13 - R2004
     *  @investigate to determine what the actual flag values are.
     */
    //accessors<int16_t> Version;
    int16_t Version() const
    {
        return m_version;
    }
    void Version(int16_t val)
    {
        m_version = val;
    }

    /*-------------------- R2007+ --------------------*/

    /**
     *  Sets or gets the proxy flag(s).<br>
     *  @acversion 2007+
     *  @investigate to determine the proxy flag(s) meaning.
     */
    //accessors<int16_t> ProxyFlags;
    int16_t ProxyFlags() const
    {
        return m_proxyFlags;
    }
    void ProxyFlags(int16_t val)
    {
        m_proxyFlags = val;
    }

    /**
     *  Sets or gets the application name associated with the defined
     *  class type.<br>
     *  associated with.<br>
     *  @acversion common
     *  @investigate the names used for built in ARX classes
     */
    //accessors<std::wstring> AppName;
    const std::wstring & AppName() const
    {
        return m_appName;
    }
    void AppName(const std::wstring & val)
    {
        m_appName = val;
    }

    /**
     *	The DXF name for the class. The name can be empty for classes
     *  not derived from AcDbObject. When filing the class use NULL
     *  for empty strings.
     *  @return The DXF class name.
     *  @acversion common
     */
    //accessors<std::wstring> DxfClassName;
    const std::wstring & DxfClassName() const
    {
        return m_dxfClassName;
    }
    void DxfClassName(const std::wstring & val)
    {
        m_dxfClassName = val;
    }

    /**
     *	The C++ name for the class (the ARX class)
     *  @acversion common
     */
    //accessors<std::wstring> CppClassName;
    const std::wstring & CppClassName() const
    {
        return m_cppClassName;
    }
    void CppClassName(const std::wstring & val)
    {
        m_cppClassName = val;
    }

    /**
     *  Gets or sets a bool flag to indicate this object is a proxy object.
     *	@acversion common
     */
    //accessors<bool> WasAZombie;
    bool WasAZombie() const
    {
        return m_bWasAZombie;
    }
    void WasAZombie(bool val)
    {
        m_bWasAZombie = val;
    }

    /**
     *  Flag indicating object or entity type class.<br>
     *  Valid values are:<br>
     *      0x1F2 for entity classes<br>
     *      0x1F3 for object classes
     *  @acversion common
     */
    //bounded<int, 0x1F2, 0x1F3> ItemClassId;
    int ItemClassId() const
    {
        return m_itemClassId;
    }
    void ItemClassId(int val)
    {
        CHECK(val >= 0x1f2 && val <= 0x1f3) << "out of range.";
        m_itemClassId = val;
    }


    /*--------------------- R2004+ -------------------*/

    /**
     *   Returns the number of objects of this type in the drawing database.
     *   @acversion R2004+
     */
    //accessors<int32_t> NumberOfObjects;
    int32_t NumberOfObjects() const
    {
        return m_numberOfObjects;
    }
    void NumberOfObjects(int32_t val)
    {
        m_numberOfObjects = val;
    }

    /**
     *	The AC release that was current when the class was introduced.
     *  acversion 2004+
     */
    //accessors<int32_t> DwgVersion;
    int32_t DwgVersion() const
    {
        return m_dwgVersion;
    }
    void DwgVersion(int32_t val)
    {
        m_dwgVersion = val;
    }

    /**
     *	Maintenance value, can be set to any value for custom classes.
     *  Built in AC ARX classes have the value set to 0 when the drawing
     *  version changes.
     *  acversion 2004+
     */
    //accessors<int32_t> MaintenanceVersion;
    int32_t MaintenanceVersion() const
    {
        return m_maintenanceVersion;
    }
    void MaintenanceVersion(int32_t val)
    {
        m_maintenanceVersion = val;
    }

    /**
     *	Unknown value
     *  @acversion 2004+
     *  @investigate
     */
    //accessors<int32_t> Unknown1;
    int32_t Unknown1() const
    {
        return m_unknown1;
    }
    void Unknown1(int32_t val)
    {
        m_unknown1 = val;
    }

    /**
     *	Unknown value
     *  @return .dwg specs say normally 0L
     *  @acversion 2004+
     *  @investigate
     */
    //accessors<int32_t> Unknown2;
    int32_t Unknown2() const
    {
        return m_unknown2;
    }
    void Unknown2(int32_t val)
    {
        m_unknown2 = val;
    }

private:
    int16_t m_classNumber;

    int16_t m_version;

    int16_t m_proxyFlags;

    std::wstring m_appName;

    std::wstring m_dxfClassName;

    std::wstring m_cppClassName;

    bool m_bWasAZombie;

    int m_itemClassId;

    int32_t m_numberOfObjects;

    int32_t m_dwgVersion;

    int32_t m_maintenanceVersion;

    int32_t m_unknown1;

    int32_t m_unknown2;

};

END_OCTAVARIUM_NS