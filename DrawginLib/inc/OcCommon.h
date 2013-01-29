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

#ifdef _WIN32
// Enable CRT debugging on Windows. Will report false positives for things
// like static or global instances of some types of objects.
// For example, static member variables that are std::map will report
// a memory leak, these can be ignored.
#    define _CRTDBG_MAP_ALLOC
#    include <stdlib.h>
#    include <crtdbg.h>
#    include <SDKDDKVer.h>
#endif

#include <algorithm>
#include <array>
#include <assert.h>
#include <memory>
//#include <set>
#include <sstream>

#include <stdio.h>
#include <tchar.h>

#if defined(DRAWGINLIB_EXPORTS)
#  define DRAWGIN_API __declspec(dllexport)
#  define EXPIMP_TEMPLATE
#else
#  define DRAWGIN_API __declspec(dllimport)
#  define EXPIMP_TEMPLATE extern
#endif

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

// When GOOGLE_STRIP_LOG a VALUE is defined, the strings log strings below
// the logging level of VALUE are removed from the compiled application.
#ifdef NDEBUG
#    define GOOGLE_STRIP_LOG 1
#endif

#include "OcObjectDef.h"
#include "OcLogger.h"

//#define  __FUNC__NAME__SIG__
#ifdef _WIN32
#    if (_MSC_VER <= 1700)
#        ifdef __FUNC__NAME__SIG__
#            define __FUNC__NAME__ __FUNCSIG__
#        else
#            define __FUNC__NAME__ __FUNCTION__
#        endif
#    endif
#endif


#ifndef NDEBUG
#    define VLOG_FUNC_NAME VLOG(5) << __FUNC__NAME__
#else
#    define VLOG_FUNC_NAME
#endif



#include "OcTypes.h"
