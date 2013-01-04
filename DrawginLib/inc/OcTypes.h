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

#ifndef OcTypes_h__
#define OcTypes_h__

#include <string>
#include <boost/cstdint.hpp>

BEGIN_OCTAVARIUM_NS

//typedef char                oc_char;
//typedef short               oc_short;
//typedef int                 oc_int;
//typedef long                oc_long;

typedef boost::int8_t       int8_t;
typedef boost::int16_t      int16_t;
typedef boost::int32_t      int32_t;
typedef boost::int64_t      int64_t;

typedef unsigned char       uchar_t;
typedef unsigned char       byte_t;
typedef unsigned short      ushort_t;
typedef unsigned int        uint_t;
typedef unsigned long       ulong_t;

typedef boost::uint8_t      uint8_t;
typedef boost::uint16_t     uint16_t;
typedef boost::uint32_t     uint32_t;
typedef boost::uint64_t     uint64_t;

//typedef intptr_t            oc_intptr;
//typedef uintptr_t           oc_uintptr;

typedef boost::intmax_t     intmax_t;
typedef boost::uintmax_t    uintmax_t;


#if defined(_UNICODE)
typedef std::wstring string_t;
#define _OC(x) L ## x
#else
typedef std::string string_t;
#define _OC
#endif


END_OCTAVARIUM_NS

#endif // OcTypes_h__
