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

#include <boost/foreach.hpp>

#include "OcCommon.h"
#include "OcError.h"
#include "OcDfDwgVersion.h"
#include "OcTypes.h"
#include "OcDbObjectId.h"
#include "OcDbObject.h"
#include "OcDfDwgObjectMap.h"

#include "OcDfDwgClass.h"
#include "OcDfDwgClasses.h"

#include "OcDfDwgVersion.h"
#include "../OcBs/OcBsStreamIn.h"
#include "../OcBs/DwgInArchive.h"

BEGIN_OCTAVARIUM_NS
using namespace std;

struct SUB_CLASS_ID {
    int id;
    const char * subClassName;
};

SUB_CLASS_ID _subClasses[] = {
    {0x00, ""},                         // unused
    {0x01, "AcDbText"},                 // text
    {0x02, "AcDbAttribute"},            // attrib
    {0x03, "AcDbAttributeDefinition"},  // attdef
    {0x04, "AcDbBlockBegin"},           // block
    {0x05, "AcDbBlockEnd"},             // endblk
    {0x06, "AcDbSequenceEnd"},          // seqend
    {0x07, "AcDbBlockReference"},       // insert
    {0x08, "AcDbMInsertBlock"},         // minsert
    {0x09, "0x09"},                     // unknown
    {0x0A, "AcDb2dVertex"},             // vertex (2d)
    {0x0B, "AcDb3dVertex"},             // vertex (3d)
    {0x0C, "0x0c"},	                    // vertex (mesh)
    {0x0D, "0x0d"},                     // vertex (pface)
    {0x0E, "0x0e"},                     // vertex (pface face)
    {0x0F, "AcDb2dPolyline"},           // polyline (2d)
    {0x10, "AcDb3dPolyline"},           // polyline (3d)
    {0x11, "AcDbArc"},                  // arc
    {0x12, "AcDbCircle"},               // circle
    {0x13, "AcDbLine"},                 // line
    {0x14, "0x14"},                     // dimension (ordinate)
    {0x15, "0x15"},                     // dimension (linear)
    {0x16, "0x16"},                     // dimension (aligned)
    {0x17, "0x17"},                     // dimension (ang 3-pt)
    {0x18, "0x18"},                     // dimension (ang 2-ln)
    {0x19, "0x19"},                     // dimension (radius)
    {0x1A, "0x1a"},                     // dimension (diameter)
    {0x1B, "AcDbPoint"},                // point
    {0x1C, "AcDbFace"},                 // 3dface
    {0x1D, "0x1d"},                     // polyline (pface)
    {0x1E, "0x1e"},                     // polyline (mesh)
    {0x1F, "AcDbSolid"},                // solid
    {0x20, "AcDbTrace"},                // trace
    {0x21, "AcDbShape"},                // shape
    {0x22, "AcDbViewport"},             // viewport
    {0x23, "AcDbEllipse"},              // ellipse
    {0x24, "AcDbSpline"},               // spline
    {0x25, "AcDbRegion"},               // region
    {0x26, "AcDb3dSolid"},              // 3dsolid
    {0x27, "AcDbBody"},                 // body
    {0x28, "AcDbRay"},                  // ray
    {0x29, "AcDbXline"},                // xline
    {0x2A, "AcDbDictionary"},           // dictionary
    {0x2B, "0x2b"},                     // unknown
    {0x2C, "AcDbMText"},                // mtext
    {0x2D, "AcDbLeader"},               // leader
    {0x2E, "AcDbFcf"},                  // tolerance
    {0x2F, "AcDbMline"},                // mline
    {0x30, "0x30"},                     // block control obj
    {0x31, "0x31"},                     // block header
    {0x32, "0x32"},                     // layer control obj
    {0x33, "0x33"},                     // layer
    {0x34, "0x34"},                     // style control obj
    {0x35, "0x35"},                     // style
    {0x36, "0x36"},                     // unknown
    {0x37, "0x37"},                     // unknown
    {0x38, "0x38"},                     // ltype contorl obj
    {0x39, "0x39"},                     // ltype
    {0x3A, "0x3a"},                     // unknown
    {0x3B, "0x3b"},                     // unknown
    {0x3C, "0x3c"},                     // view control obj
    {0x3D, "0x3d"},                     // view
    {0x3E, "0x3e"},                     // ucs control obj
    {0x3F, "0xef"},                     // ucs
    {0x40, "0x40"},                     // vport control obj
    {0x41, "0x41"},                     // vport
    {0x42, "0x42"},                     // appid control obj
    {0x43, "AcDbRegAppTableRecord"},    // appid
    {0x44, "0x44"},                     // dimstyle control obj
    {0x45, "0x45"},                     // dimstyle
    {0x46, "0x46"},                     // vp ent hdr ctrl obj
    {0x47, "0x47"},                     // vp ent hdr
    {0x48, "AcDbGroup"},                // group
    {0x49, "AcDbMlineStyle"},           // mlinestyle
    {0x4A, "0x4a"},                     // ole2frame
    {0x4B, "0x4b"},                     // dummy
    {0x4C, "0x4c"},                     // long transaction
    {0x4D, "0x4d"},                     // lwpolyline
    {0x4E, "0x4e"},                     // hatch
    {0x4F, "0x4f"},                     // xrecord
    {0x50, "0x50"},                     // AcDbPlaceHolder
    {0x51, "0x51"},                     // VBA_Project
};


#define ELEMENTS(x) sizeof(x)/sizeof(x[0])


OcDfDwgObjectMap::OcDfDwgObjectMap(int32_t objMapFilePos, int32_t objMapSize)
    : m_objMapFilePos(objMapFilePos), m_objMapSize(objMapSize)
{
}

OcDfDwgObjectMap::~OcDfDwgObjectMap(void)
{
}

OcApp::ErrorStatus OcDfDwgObjectMap::DecodeData(DwgInArchive& ar)
{
    ASSERT_ARCHIVE_NOT_LOADING(ar);
    VLOG(4) << "DecodeObjectMap entered";
    // do some sanity checks before trying to read the object map
    if(m_objMapFilePos == 0) {
        LOG(ERROR) << "Invalid file offset position for Object Map";
        return OcApp::eInvalidObjectMapOffset;
    }

    // set file position to the Object Map offset
    ar.Seek(m_objMapFilePos);
    if(ar.Error() != OcApp::eOk) {
        LOG(ERROR) << "Error setting file position";
        return ar.Error();
    }

    int32_t lastHandle = 0, lastOffset = 0;

    // 6/2/2011 - seems to work.
    // Until I've seen some files which have more than one
    // section, not really sure how the data is coded.
    // Does lastOffset need to be reset to 0 for each section?
    int sectionNumber = 0;

    // section size and crc are values stored in big endian format
    // on disk.
    while(1) {
        // reset calced crc to 0xc0c1 for each section
        ar.SetCalcedCRC(0xc0c1);
        // read section size and convert to little endian format.
        int16_t sectionSize;
        ar >> (bitcode::RC&)sectionSize;
        sectionSize <<= 8;
        ar >> (bitcode::RC&)sectionSize;
        VLOG(4) << "Section size = " << sectionSize;

        // only 2 bytes for this section, they are the final crc
        // which is calced below outside of this loop.
        if(sectionSize <= 2) {
            break;
        }

        // 12/26/2012 - Examined a sample drawing with multiple sections, and determined
        // that indeed, lastOffset and lastHandle must be set to 0 at the beginning
        // of each section to be read.
        lastOffset = 0;
        lastHandle = 0;

        // endSection includes the 2 byte crc for this section, so
        // exclude 2 bytes when doing the loop.
        int32_t endSection = ar.FilePosition() + sectionSize;
        while(ar.FilePosition() < endSection - 2) {
            int32_t offsetLastH;
            int32_t offsetLoc;
            VLOG(4) << "---------------";
            BS_ARCHIVE(bitcode::MC,  ar, offsetLastH, "File offset last handle");
            BS_ARCHIVE(bitcode::MC , ar, offsetLoc,   "File offset loc");
            lastHandle += offsetLastH;
            lastOffset += offsetLoc;
            VLOG(4) << "Object handle = " << lastHandle;
            VLOG(4) << "File position = " << lastOffset;
            m_objMapItems.push_back(MapItem(lastHandle, lastOffset));
        }
        // calc section crc
        uint16_t crc, calcedCrc = ar.CalcedCRC(true);
        ar.ReadCRC(crc);
        if(crc != calcedCrc) {
            LOG(ERROR) << "Data section CRC for Object Map is incorrect";
            return OcApp::eInvalidCRCInObjectMap;
        }
        sectionNumber++;
    }
    // calc final crc
    uint16_t crc, calcedCrc = ar.CalcedCRC(true);
    ar.ReadCRC(crc);
    if(crc != calcedCrc) {
        LOG(ERROR) << "CRC for Object Map is incorrect";
        return OcApp::eInvalidCRCInObjectMap;
    }

    VLOG(4) << "Successfully decoded Object map";
    return OcApp::eOk;
}

OcApp::ErrorStatus OcDfDwgObjectMap::DecodeObjects(DwgInArchive& ar,
        OcDbDatabaseImpl *& pDb,
        const OcDfDwgClasses & classes)
{
    std::vector<SUB_CLASS_ID> subClasses(&_subClasses[0],
                                         &_subClasses[ELEMENTS(_subClasses)]);
    BOOST_FOREACH(const MapItem &  item, m_objMapItems) {
        VLOG(4) << "--------------------";
        ar.Seek(item.second);
        VLOG(4) << "Object Handle = " << item.first;
        VLOG(4) << "Seeking file position = " << item.second; 
        if(ar.Error() != OcApp::eOk)
            return ar.Error();

        uint32_t objSize = 0;
        uint16_t objType = 0;

        BS_ARCHIVE(bitcode::MS, ar, objSize, "Object size = ");
        BS_ARCHIVE(bitcode::BS, ar, objType, "Object type = ");

        if(objType > subClasses.size() - 1 && objType < 500) {
            LOG(ERROR) << "Object type outside of known range";
            LOG(ERROR) << "Sub type = " << hex << showbase << objType;
            return OcApp::eOutsideOfClassMapRange;
        } else {
            if(objType >= 500) {
                const OcDfDwgClass & className = classes.ClassAt(objType - 500);
                VLOG(4) << "Classname = " <<
                        WStringToString(className.CppClassName());
            } else {
                SUB_CLASS_ID subClass = subClasses.at(objType);
                VLOG(4) << "Sub class name = " << subClass.subClassName;
            }
        }
    }
    return OcApp::eOk;
}

DwgInArchive& operator>>(DwgInArchive& ar, OcDfDwgObjectMap & hdr)
{
    ASSERT_ARCHIVE_NOT_LOADING(ar);
    ar.SetError(hdr.DecodeData(ar));
    return ar;
}

END_OCTAVARIUM_NS