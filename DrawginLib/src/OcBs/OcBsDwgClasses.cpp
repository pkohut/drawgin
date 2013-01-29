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
#include "OcBsStreamIn.h"
#include "OcBsDwgClasses.h"
#include "OcBsDwgSentinels.h"
#include "OcBsStreamIn.h"

BEGIN_OCTAVARIUM_NS
using namespace std;

OcBsDwgClasses::OcBsDwgClasses(void)
{
    VLOG_FUNC_NAME;
}


OcBsDwgClasses::~OcBsDwgClasses(void)
{
    VLOG_FUNC_NAME;
}

const OcBsDwgClass & OcBsDwgClasses::ClassAt(size_t index) const
{
    VLOG_FUNC_NAME;
    return m_classes.at(index);
}

bool OcBsDwgClasses::Has(const std::wstring & className) const
{
    VLOG_FUNC_NAME;
    return m_classes.end() != std::find_if(m_classes.begin(), m_classes.end(),
                                           [&](const OcBsDwgClass & c)
    {
        return c.CppClassName() == className;
    });
}

OcApp::ErrorStatus OcBsDwgClasses::ReadDwg(OcBsStreamIn & in)
{
    VLOG_FUNC_NAME;
    VLOG(4) << "OcBsDwgClasses::ReadDwg entered";
    bitcode::RC sentinelData[16];
    in.ReadRC(sentinelData, 16);
    if(!CompareSentinels(sentinelClassesSectionStart, sentinelData))
    {
        return OcApp::eInvalidClassesDataSentinel;
    }

    in.SetCalcedCRC(0xc0c1);
    int size;
    BS_STREAMIN(bitcode::RL, in, size, "classes section size");
    auto endSection = in.FilePosition() + size - 1;

    if(in.Version() >= R2004)
    {
        // read the RS value - maximum class number
        // read the RC value -
        // read the RC value -
        // read the  B value -
    }

    if(in.Version() >= R2007)
    {
        //   : Class Data
        // X : String stream data
        // B : bool value (true if string stream is present)
    }

    while(in.FilePosition() < endSection)
    {
        OcBsDwgClass cls;
        cls.ReadDwg(in);
        //in >> cls;
        m_classes.push_back(cls);
    }

    if(in.FilePosition() != endSection)
    {
        LOG(ERROR) << "File position should be "
                   << endSection << " instead of "
                   << in.FilePosition();
    }

    // Check and log CRC
    uint16_t calcedCRC = in.CalcedCRC();
    uint16_t sectionCRC;
    in.ReadCRC(sectionCRC);

    if(calcedCRC != sectionCRC)
    {
        LOG(ERROR) << "file section and calced CRC's do not match";
        LOG(ERROR) << "Classes section CRC = " << hex << showbase << sectionCRC;
        LOG(ERROR) << "Calced CRC          = " << hex << showbase << calcedCRC;
    }
    else
    {
        VLOG(4) << "CRC for Classes Section = " << hex << showbase << sectionCRC;
    }

    // match classes section end sentinel
    in.ReadRC(sentinelData, 16);

    if(!CompareSentinels(sentinelClassesSectionEnd, sentinelData))
    {
        return OcApp::eInvalidImageDataSentinel;
    }

    VLOG(4) << "Successfully decoded Classes Section";
    return OcApp::eOk;
}

END_OCTAVARIUM_NS