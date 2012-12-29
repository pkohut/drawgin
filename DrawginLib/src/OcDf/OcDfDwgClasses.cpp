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
#include "OcTypes.h"
#include "OcError.h"
#include "OcDfDwgVersion.h"
#include "OcDbObjectId.h"

#include "../OcBs/OcBsStreamIn.h"
#include "../OcBs/DwgInArchive.h"
#include "OcDfDwgClass.h"
#include "OcDfDwgClasses.h"
#include "../OcBs/OcBsDwgSentinels.h"

BEGIN_OCTAVARIUM_NS
using namespace std;

OcDfDwgClasses::OcDfDwgClasses()
{
    VLOG(4) << "Constructor entered";
}

OcDfDwgClasses::~OcDfDwgClasses()
{
    VLOG(4) << "Destructor entered";
}

OcApp::ErrorStatus OcDfDwgClasses::DecodeData(DwgInArchive& in)
{
    VLOG(4) << "DecodeData entered";
    ASSERT_ARCHIVE_NOT_LOADING(in);

    // match classes section start sentinel
    bitcode::RC sentinelData[16];
    in.ReadRC(sentinelData, 16);
    if(!CompareSentinels(sentinelClassesSectionStart, sentinelData)) {
        return OcApp::eInvalidImageDataSentinel;
    }

    in.SetCalcedCRC(0xc0c1);

    int size;
    BS_ARCHIVE(bitcode::RL, in, size, "classes section size");
    int endSection = in.FilePosition() + size - 1;

    if(in.Version() >= R2004) {
        // read the RS value - maximum class number
        // read the RC value -
        // read the RC value -
        // read the  B value -
    }

    if(in.Version() >= R2007) {
        //   : Class Data
        // X : String stream data
        // B : bool value (true if string stream is present)
    }

    while(in.FilePosition() < endSection) {
        OcDfDwgClass cls;
        in >> cls;
        m_classes.push_back(cls);
    }

    if(in.FilePosition() != endSection) {
        LOG(ERROR) << "File position should be "
            << endSection << " instead of "
            << in.FilePosition();
    }

    // Check and log CRC
    uint16_t calcedCRC = in.CalcedCRC();
    uint16_t sectionCRC;
    in.ReadCRC(sectionCRC);
    if(calcedCRC != sectionCRC) {
        LOG(ERROR) << "file section and calced CRC's do not match";
        LOG(ERROR) << "Classes section CRC = " << hex << showbase << sectionCRC;
        LOG(ERROR) << "Calced CRC          = " << hex << showbase << calcedCRC;
    } else {
        VLOG(4) << "CRC for Classes Section = " << hex << showbase << sectionCRC;
    }

    // match classes section end sentinel
    in.ReadRC(sentinelData, 16);
    if(!CompareSentinels(sentinelClassesSectionEnd, sentinelData)) {
        return OcApp::eInvalidImageDataSentinel;
    }

    VLOG(4) << "Successfully decoded Classes Section";

    return OcApp::eOk;
}

DwgInArchive& operator>>(DwgInArchive& in, OcDfDwgClasses & dwgClasses)
{
    ASSERT_ARCHIVE_NOT_LOADING(in);
    in.SetError(dwgClasses.DecodeData(in));
    return in;
}

const OcDfDwgClass & OcDfDwgClasses::ClassAt(size_t index) const
{
    return m_classes.at(index);
}

bool OcDfDwgClasses::Has( const std::wstring & className ) const
{
    BOOST_FOREACH(const OcDfDwgClass & obj, m_classes) {
        if(obj.CppClassName() == className)
            return true;
    }
    return false;
}


END_OCTAVARIUM_NS