/**
 *	@file
 *  @brief Defines OcBsDwgSecondFileHeader class
 *
 *  Used to encode the "second file header" section of drawing files
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

BEGIN_OCTAVARIUM_NS

class OcBsStreamIn;

class OcBsDwgSecondFileHeaders
{
public:
    OcBsDwgSecondFileHeaders() : sectionNumber(0), address(0), size(0) {}
    enum SECTIONS {HEADER = 0, CLASS, OBJECT_MAP, UNKNOWN_SECTION3, DATA_SECTION, };
    byte_t sectionNumber;
    int32_t address;
    int32_t size;
};

class OcBsDwgHandleRecord
{
public:
    enum RECORD_HANDLE
    {
        HANDSEED = 0, BLOCK_CONTROL_OBJ, LAYER_CONTROL_OBJ, SHAPEFILE_CONTROL_OBJ,
        LINETYPE_CONTROL_OBJ, VIEW_CONTROL_OBJ, UCS_CONTROL_OBJ, VPORT_CONTROL_OBJ,
        REGAPP_CONTROL_OBJ, DIMSTYLE_CONTROL_OBJ, VIEWPORT_ENTITY_HEADER_OBJ,
        DICTIONARY_OBJ, MULTILINE_STYLE_OBJ, GROUP_DICTIONARY_OBJ,
    };
    byte_t recordNumber;
    byte_t sizeOfValidChars;
    std::vector<bitcode::RC> sig;
};

class OcBsDwgSecondFileHeader
{
public:
    OcBsDwgSecondFileHeader(void);
    virtual ~OcBsDwgSecondFileHeader(void);

    OcApp::ErrorStatus ReadDwg(OcBsStreamIn & in);
private:
    std::vector<OcBsDwgSecondFileHeaders> m_sectionHeaders;
    std::vector<OcBsDwgHandleRecord> m_handleRecords;


};

END_OCTAVARIUM_NS