// DrawGin.cpp : Defines the entry point for the console application.
//

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

#include "stdafx.h"

#include "OcCommon.h"
#include "OcError.h"
#include "OcRxObject.h"
#include "OcDbDatabase.h"
#include "OcDbSmartPtrs.h"


using namespace octavarium;
using namespace google;

void ProcessDrawing(const string_t & filename)
{
    OcDbDatabasePtr pDb = new OcDbDatabase;
    OcApp::ErrorStatus es = pDb->Open(filename);
    LOG_IF(ERROR, es != OcApp::eOk) << "Error processing drawing.";
}

int main(int argc, char* argv[])
{
    InitGoogleLogging(argv[0]);
    //ProcessDrawing(_OC("C:\\VS9_Project\\Metropolis\\TestDwgs\\EmptyR14.dwg"));
    //ProcessDrawing(_OC("C:\\VS9_Project\\Metropolis\\TestDwgs\\OneLayerR14.dwg"));
    //ProcessDrawing(_OC("C:\\VS9_Project\\Metropolis\\TestDwgs\\OneLayerR14.dwg"));
    ProcessDrawing(_OC("/home/paul/Documents/TestDwgs/OneLayerR14.dwg"));

    OcRxObject::ShutDown();
    return 0;
}
