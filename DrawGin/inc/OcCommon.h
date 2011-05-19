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

#ifndef OcCommon_h__
#define OcCommon_h__

#include <algorithm>
#include <assert.h>
#include <fstream>
#include <functional>
#include <set>
#include <sstream>
#include <string>
#include <typeinfo>
#include <utility>
#include <vector>

#ifdef NDEBUG
//#define GOOGLE_STRIP_LOG 1
#endif

#include <glog/logging.h>
#include "wchar_logging.h"

#define BEGIN_OCTAVARIUM_NS namespace octavarium {
#define END_OCTAVARIUM_NS }

#define USING_OCTAVARIUM_NS using namespace octavarium;

#include "OcTypes.h"
#include "OcRxObject.h"

#endif // OcCommon_h__
