/**
 *	@file
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

#include "OcCommon.h"
#include "OcError.h"
#include "OcBsDwgClasses.h"
#include "OcBsDwgObjectMap.h"
#include "OcBsStreamIn.h"
#include <iomanip>

BEGIN_OCTAVARIUM_NS
using namespace std;
class SUB_CLASS_ID
{
public:
    SUB_CLASS_ID(int _id, const char * pcszSubClassName)
        : m_id(_id), m_subClassName(pcszSubClassName) {}
    int Id() const
    {
        return m_id;
    }
    const std::string & SubClassName() const
    {
        return m_subClassName;
    }
private:
    int m_id;
    //const char * subClassName;
    const std::string m_subClassName;
};

std::array<SUB_CLASS_ID, 82> _subClasses =
{

    SUB_CLASS_ID(0x00, ""),                         // unused
    SUB_CLASS_ID(0x01, "AcDbText"),                 // text
    SUB_CLASS_ID(0x02, "AcDbAttribute"),            // attrib
    SUB_CLASS_ID(0x03, "AcDbAttributeDefinition"),  // attdef
    SUB_CLASS_ID(0x04, "AcDbBlockBegin"),           // block
    SUB_CLASS_ID(0x05, "AcDbBlockEnd"),             // endblk
    SUB_CLASS_ID(0x06, "AcDbSequenceEnd"),          // seqend
    SUB_CLASS_ID(0x07, "AcDbBlockReference"),       // insert
    SUB_CLASS_ID(0x08, "AcDbMInsertBlock"),         // minsert
    SUB_CLASS_ID(0x09, "0x09"),                     // unknown
    SUB_CLASS_ID(0x0A, "AcDb2dVertex"),             // vertex (2d)
    SUB_CLASS_ID(0x0B, "AcDb3dVertex"),             // vertex (3d)
    SUB_CLASS_ID(0x0C, "0x0c"),	                    // vertex (mesh)
    SUB_CLASS_ID(0x0D, "0x0d"),                     // vertex (pface)
    SUB_CLASS_ID(0x0E, "0x0e"),                     // vertex (pface face)
    SUB_CLASS_ID(0x0F, "AcDb2dPolyline"),           // polyline (2d)
    SUB_CLASS_ID(0x10, "AcDb3dPolyline"),           // polyline (3d)
    SUB_CLASS_ID(0x11, "AcDbArc"),                  // arc
    SUB_CLASS_ID(0x12, "AcDbCircle"),               // circle
    SUB_CLASS_ID(0x13, "AcDbLine"),                 // line
    SUB_CLASS_ID(0x14, "0x14"),                     // dimension (ordinate)
    SUB_CLASS_ID(0x15, "0x15"),                     // dimension (linear)
    SUB_CLASS_ID(0x16, "0x16"),                     // dimension (aligned)
    SUB_CLASS_ID(0x17, "0x17"),                     // dimension (ang 3-pt)
    SUB_CLASS_ID(0x18, "0x18"),                     // dimension (ang 2-ln)
    SUB_CLASS_ID(0x19, "0x19"),                     // dimension (radius)
    SUB_CLASS_ID(0x1A, "0x1a"),                     // dimension (diameter)
    SUB_CLASS_ID(0x1B, "AcDbPoint"),                // point
    SUB_CLASS_ID(0x1C, "AcDbFace"),                 // 3dface
    SUB_CLASS_ID(0x1D, "0x1d"),                     // polyline (pface)
    SUB_CLASS_ID(0x1E, "0x1e"),                     // polyline (mesh)
    SUB_CLASS_ID(0x1F, "AcDbSolid"),                // solid
    SUB_CLASS_ID(0x20, "AcDbTrace"),                // trace
    SUB_CLASS_ID(0x21, "AcDbShape"),                // shape
    SUB_CLASS_ID(0x22, "AcDbViewport"),             // viewport
    SUB_CLASS_ID(0x23, "AcDbEllipse"),              // ellipse
    SUB_CLASS_ID(0x24, "AcDbSpline"),               // spline
    SUB_CLASS_ID(0x25, "AcDbRegion"),               // region
    SUB_CLASS_ID(0x26, "AcDb3dSolid"),              // 3dsolid
    SUB_CLASS_ID(0x27, "AcDbBody"),                 // body
    SUB_CLASS_ID(0x28, "AcDbRay"),                  // ray
    SUB_CLASS_ID(0x29, "AcDbXline"),                // xline
    SUB_CLASS_ID(0x2A, "AcDbDictionary"),           // dictionary
    SUB_CLASS_ID(0x2B, "0x2b"),                     // unknown
    SUB_CLASS_ID(0x2C, "AcDbMText"),                // mtext
    SUB_CLASS_ID(0x2D, "AcDbLeader"),               // leader
    SUB_CLASS_ID(0x2E, "AcDbFcf"),                  // tolerance
    SUB_CLASS_ID(0x2F, "AcDbMline"),                // mline
    SUB_CLASS_ID(0x30, "0x30"),                     // block control obj
    SUB_CLASS_ID(0x31, "0x31"),                     // block header
    SUB_CLASS_ID(0x32, "0x32"),                     // layer control obj
    SUB_CLASS_ID(0x33, "0x33"),                     // layer
    SUB_CLASS_ID(0x34, "0x34"),                     // style control obj
    SUB_CLASS_ID(0x35, "0x35"),                     // style
    SUB_CLASS_ID(0x36, "0x36"),                     // unknown
    SUB_CLASS_ID(0x37, "0x37"),                     // unknown
    SUB_CLASS_ID(0x38, "0x38"),                     // ltype contorl obj
    SUB_CLASS_ID(0x39, "0x39"),                     // ltype
    SUB_CLASS_ID(0x3A, "0x3a"),                     // unknown
    SUB_CLASS_ID(0x3B, "0x3b"),                     // unknown
    SUB_CLASS_ID(0x3C, "0x3c"),                     // view control obj
    SUB_CLASS_ID(0x3D, "0x3d"),                     // view
    SUB_CLASS_ID(0x3E, "0x3e"),                     // ucs control obj
    SUB_CLASS_ID(0x3F, "0xef"),                     // ucs
    SUB_CLASS_ID(0x40, "0x40"),                     // vport control obj
    SUB_CLASS_ID(0x41, "0x41"),                     // vport
    SUB_CLASS_ID(0x42, "0x42"),                     // appid control obj
    SUB_CLASS_ID(0x43, "AcDbRegAppTableRecord"),    // appid
    SUB_CLASS_ID(0x44, "0x44"),                     // dimstyle control obj
    SUB_CLASS_ID(0x45, "0x45"),                     // dimstyle
    SUB_CLASS_ID(0x46, "0x46"),                     // vp ent hdr ctrl obj
    SUB_CLASS_ID(0x47, "0x47"),                     // vp ent hdr
    SUB_CLASS_ID(0x48, "AcDbGroup"),                // group
    SUB_CLASS_ID(0x49, "AcDbMlineStyle"),           // mlinestyle
    SUB_CLASS_ID(0x4A, "0x4a"),                     // ole2frame
    SUB_CLASS_ID(0x4B, "0x4b"),                     // dummy
    SUB_CLASS_ID(0x4C, "0x4c"),                     // long transaction
    SUB_CLASS_ID(0x4D, "0x4d"),                     // lwpolyline
    SUB_CLASS_ID(0x4E, "0x4e"),                     // hatch
    SUB_CLASS_ID(0x4F, "0x4f"),                     // xrecord
    SUB_CLASS_ID(0x50, "0x50"),                     // AcDbPlaceHolder
    SUB_CLASS_ID(0x51, "0x51"),                     // VBA_Project
};

OcBsDwgObjectMap::OcBsDwgObjectMap(int32_t objMapFilePos, int32_t objMapSize)
    : m_objMapFilePos(objMapFilePos), m_objMapSize(objMapSize)
{
    VLOG_FUNC_NAME;
}


OcBsDwgObjectMap::~OcBsDwgObjectMap(void)
{
    VLOG_FUNC_NAME;
}

OcApp::ErrorStatus OcBsDwgObjectMap::ReadDwg(OcBsStreamIn & in)
{
    VLOG_FUNC_NAME;
    VLOG(4) << "OcBsDwgObjectMap::ReadDwg entered";

    // do some sanity checks before trying to read the object map
    if(m_objMapFilePos == 0)
    {
        LOG(ERROR) << "Invalid file offset position for Object Map";
        return OcApp::eInvalidObjectMapOffset;
    }

    // set file position to the Object Map offset
    in.Seek(m_objMapFilePos);

    if(in.Error() != OcApp::eOk)
    {
        LOG(ERROR) << "Error setting file position";
        return in.Error();
    }

    int32_t lastHandle = 0, lastOffset = 0;
    // 6/2/2011 - seems to work.
    // Until I've seen some files which have more than one
    // section, not really sure how the data is coded.
    // Does lastOffset need to be reset to 0 for each section?
    int sectionNumber = 0;

    // section size and crc are values stored in big endian format
    // on disk.
    while(1)
    {
        // reset calced crc to 0xc0c1 for each section
        in.SetCalcedCRC(0xc0c1);
        // read section size and convert to little endian format.
        int16_t sectionSize;
        in >> (bitcode::RC&)sectionSize;
        sectionSize <<= 8;
        in >> (bitcode::RC&)sectionSize;
        VLOG(4) << "Section size = " << sectionSize;

        // only 2 bytes for this section, they are the final crc
        // which is calced below outside of this loop.
        if(sectionSize <= 2)
        {
            break;
        }

        // 12/26/2012 - Examined a sample drawing with multiple sections, and determined
        // that indeed, lastOffset and lastHandle must be set to 0 at the beginning
        // of each section to be read.
        lastOffset = 0;
        lastHandle = 0;
        // endSection includes the 2 byte crc for this section, so
        // exclude 2 bytes when doing the loop.
        auto endSection = in.FilePosition() + sectionSize;

        while(in.FilePosition() < endSection - 2)
        {
            int32_t offsetLastH;
            int32_t offsetLoc;
            VLOG(4) << "---------------";
            BS_STREAMIN(bitcode::MC,  in, offsetLastH, "File offset last handle");
            BS_STREAMIN(bitcode::MC , in, offsetLoc,   "File offset loc");
            lastHandle += offsetLastH;
            lastOffset += offsetLoc;
            VLOG(4) << "Object handle = " << lastHandle;
            VLOG(4) << "File position = " << lastOffset;
            m_objMapItems.push_back(MapItem(lastHandle, lastOffset));
        }

        // calc section crc
        uint16_t crc, calcedCrc = in.CalcedCRC(true);
        in.ReadCRC(crc);

        if(crc != calcedCrc)
        {
            LOG(ERROR) << "Data section CRC for Object Map is incorrect";
            return OcApp::eInvalidCRCInObjectMap;
        }

        sectionNumber++;
    }

    // calc final crc
    uint16_t crc, calcedCrc = in.CalcedCRC(true);
    in.ReadCRC(crc);

    if(crc != calcedCrc)
    {
        LOG(ERROR) << "CRC for Object Map is incorrect";
        return OcApp::eInvalidCRCInObjectMap;
    }

    VLOG(4) << "Successfully decoded Object map";
    return OcApp::eOk;
}

OcApp::ErrorStatus OcBsDwgObjectMap::DecodeObjects(OcBsStreamIn & in, const OcBsDwgClasses & classes)
{
    //std::vector<SUB_CLASS_ID> subClasses(&_subClasses[0],
    //    &_subClasses[ELEMENTS(_subClasses)]);
    //BOOST_FOREACH(const MapItem &  item, m_objMapItems)
for(auto item : m_objMapItems)
    {
        VLOG(4) << "--------------------";
        in.Seek(item.second);
        VLOG(4) << "Object Handle = " << item.first;
        VLOG(4) << "Seeking file position = " << item.second;

        if(in.Error() != OcApp::eOk)
        {
            return in.Error();
        }

        uint32_t objSize = 0;
        uint16_t objType = 0;
        BS_STREAMIN(bitcode::MS, in, objSize, "Object size = ");
        BS_STREAMIN(bitcode::BS, in, objType, "Object type = ");

        if(objType > _subClasses.size() - 1 && objType < 500)
        {
            LOG(ERROR) << "Object type outside of known range";
            LOG(ERROR) << "Sub type = " << hex << showbase << objType;
            return OcApp::eOutsideOfClassMapRange;
        }
        else
        {
            if(objType >= 500)
            {
                const OcBsDwgClass & className = classes.ClassAt(objType - 500);
                VLOG(4) << "Class name = " <<
                        WStringToString(className.CppClassName());
            }
            else
            {
                SUB_CLASS_ID subClass = _subClasses.at(objType);
                VLOG(4) << "Sub class name = " << subClass.SubClassName();
            }
        }
    }
    return OcApp::eOk;

}

END_OCTAVARIUM_NS
