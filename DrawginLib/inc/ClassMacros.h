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

#ifndef ClassMacros_h__
#define ClassMacros_h__

#define DECLARE_GETTER_SETTER_BY_VAL(TYPE, FUNCTION) \
    TYPE FUNCTION(void) const; \
    void FUNCTION(TYPE);

#define DECLARE_GETTER_SETTER_BY_REF(TYPE, FUNCTION) \
    const TYPE & FUNCTION(void) const; \
    void FUNCTION(const TYPE &);


//#define OcPtr boost::intrusive_ptr
template<typename T>
struct OcPtr {
    typedef boost::intrusive_ptr<T> value_type;
};


#endif // ClassMacros_h__
