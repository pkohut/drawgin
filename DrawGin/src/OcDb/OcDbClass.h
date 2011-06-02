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

#ifndef OCDBCLASS_H
#define OCDBCLASS_H

BEGIN_OCTAVARIUM_NS

class OcDbClass
{
public:
	OcDbClass();
	virtual ~OcDbClass();

    std::wstring DxfClassName(void) const;
    std::wstring CppClassName(void) const;

private:
private:
    OcApp::ErrorStatus DecodeData(DwgInArchive& in);
    friend DwgInArchive& operator>>(DwgInArchive& in,
        OcDbClass & dwgClass);


private:
    // common
    int16_t m_classNum;
    // R13 - R2004 
    int16_t m_version;  // in R14, becomes a flag indicating whether objects
                        // can be moved, edited, etc.
    // R2007+
    int16_t m_proxyFlags;
    // common
    std::wstring m_appName;
    std::wstring m_cppClassName;
    std::wstring m_dxfClassName;
    bool m_wasAZombie;
    int16_t m_itemClassId;
    // R2004+
    int32_t m_numObjects;
    int32_t m_dwgVersion;   // stored as int16_t for R2004
    int32_t m_maintVersion; // stored as int16_t for R2004
    int32_t m_unknown1;
    int32_t m_unknown2;
};

END_OCTAVARIUM_NS

#endif // OCDBCLASS_H
