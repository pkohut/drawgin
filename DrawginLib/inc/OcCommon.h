/**
 *	@file
 *  @brief Common macros, headers, etc.
 *
 *  Usually the first file included all the cpp files.
 *  Defines common macros, headers, and configurations
 *  definitions which is used application wide.
 *
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

#if defined(_WIN32)
// Enable CRT deubbing on Windows. Will report false positives for things
// like static or global instances of some types of objects.
// For example, static member variables that are std::map will report
// a memory leak, these can be ignored.
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

#include <algorithm>
#include <assert.h>
#include <fstream>
#include <functional>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <typeinfo>
#include <utility>
#include <vector>

#include <sys/types.h>
#include <sys/stat.h>


#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>


// When GOOGLE_STRIP_LOG a VALUE is defined, the strings log strings below
// the logging level of VALUE are removed from the compiled application.
#ifdef NDEBUG
//#define GOOGLE_STRIP_LOG 1
#endif

#if defined(WIN32)
#include <tchar.h>
#endif

// Google's logging library.
#include <glog/logging.h>

// Add wstring and wchar_t support to GLog.
#include "wchar_logging.h"

/**
 *	Macro that can be used in place of the ++ namespace keyword.<br>
 *  Source code formatting programs will not add extra indentation because
 *  they will not see the opening bracket.
 *  @note Must be paired with the END_OCTAVARIUM_NS macro
 */
#define BEGIN_OCTAVARIUM_NS namespace octavarium {

/**
 *	Macro that defines the closing bracket for the BEGIN_OCTAVARIUM_NS
 *  macro.<br>
 *  Source code formatting programs will not add extra indentation because
 *  they will not see the closing bracket. Also makes the namespace self
 *  documenting.
 */
#define END_OCTAVARIUM_NS }

/**
 *	Macro that can be used in place of the using namespace keywords.
 *  Especially nice since I can't seem to spell octavarium correctly
 *  most of the time.
 */
#define USING_OCTAVARIUM_NS using namespace octavarium;

#include "OcTypes.h"
#include "OcRxObject.h"

#include "OcConfig.h"

#endif // OcCommon_h__
