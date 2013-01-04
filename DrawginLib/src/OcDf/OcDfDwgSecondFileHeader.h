/****************************************************************************
**
** This file is part of DrawGin library. A C++ framework to read and
** write .dwg files formats.
**
** Copyright (C) 2011, 2012, 2013 Paul Kohut.
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

#ifndef OcBsDwgSecondFileHeader_h__
#define OcBsDwgSecondFileHeader_h__

BEGIN_OCTAVARIUM_NS

class DwgInArchive;
struct OcApp;

class OcDfSecondFileHeaders
{
public:
    enum SECTIONS {HEADER = 0, CLASS, OBJECT_MAP, UNKNOWN_SECTION3, DATA_SECTION, };
    byte_t sectionNumber;
    int32_t address;
    int32_t size;
};

class OcDfHandleRecord
{
public:
    enum RECORD_HANDLE {
        HANDSEED = 0, BLOCK_CONTROL_OBJ, LAYER_CONTROL_OBJ, SHAPEFILE_CONTROL_OBJ,
        LINETYPE_CONTROL_OBJ, VIEW_CONTROL_OBJ, UCS_CONTROL_OBJ, VPORT_CONTROL_OBJ,
        REGAPP_CONTROL_OBJ, DIMSTYLE_CONTROL_OBJ, VIEWPORT_ENTITY_HEADER_OBJ,
        DICTIONARY_OBJ, MULTILINE_STYLE_OBJ, GROUP_DICTIONARY_OBJ,
    };
    byte_t recordNumber;
    byte_t sizeOfValidChars;
    std::vector<bitcode::RC> sig;
};

class OcDfDwgSecondFileHeader
{
public:
    OcDfDwgSecondFileHeader(void);
    virtual ~OcDfDwgSecondFileHeader(void);

    friend DwgInArchive& operator>>(DwgInArchive& in, OcDfDwgSecondFileHeader & hdrData);
    OcApp::ErrorStatus DecodeData(DwgInArchive& in);
//    bool IsHeadDataAllNULL(const std::vector<byte_t>& data) const;

private:
    std::vector<OcDfSecondFileHeaders> m_sectionHeaders;
    std::vector<OcDfHandleRecord> m_handleRecords;

    
};

END_OCTAVARIUM_NS

#endif // OcBsDwgSecondFileHeader_h__
