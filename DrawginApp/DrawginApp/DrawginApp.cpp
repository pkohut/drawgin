// DrawginApp.cpp : Defines the entry point for the console application.
//

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

#include "stdafx.h"
#include <stdio.h>
#include "OcCommon.h"
#include "ProgramOptions.h"
#include "OcDbDatabase.h"


using namespace google;
using namespace std;
using namespace octavarium;

const static int major_version = 0;
const static int minor_version = 2;
const static int patch_version = 1;


// From GLOG, logging.cc,
// Compute the default value for --log_dir
const char* DefaultLogDir()
{
    const char* env;
    env = getenv("GOOGLE_LOG_DIR");

    if(env != NULL && env[0] != '\0')
    {
        return env;
    }

    env = getenv("TEST_TMPDIR");

    if(env != NULL && env[0] != '\0')
    {
        return env;
    }

    return "";
}

int main(int argc, char * argv[])
{
    OcLogger::Init();
#if defined(_WIN32) && !defined(NDEBUG)
    // Enable memory dump from within VS.
    _CrtMemState memState;
    _CrtMemCheckpoint(&memState);
#endif
    {
        OcLogger logger(argv[0]);

        // --v=4 --alsologtostderr=1 --log_dir=$(OutDir)\logs --drawing=C:\Users\Paul\Documents\TestDwgs\EmptyR14.dwg
        ProgramOptions po;
        if(po.Set(argc, argv))
        {
            return 1;
        }

        OcDbDatabase db;
        db.ReadDwg(po.drawing());
    }
#if defined(_WIN32) && !defined(NDEBUG)
    // Check for memory leaks in debug builds.
    _CrtMemDumpAllObjectsSince(&memState);
#endif
    return 0;
}

