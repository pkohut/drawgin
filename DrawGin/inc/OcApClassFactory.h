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

#ifndef OcApClassFactory_h__
#define OcApClassFactory_h__

BEGIN_OCTAVARIUM_NS

class OcRxObject;

// See OcApApplication::NewRxClass for an example of how to
// create an instance of a class based on the class name

template<class RootBase>
class OcApClassFactoryBase
{
public:
    OcApClassFactoryBase(const wchar_t * key) {
        // register the key name and the factory
        RootBase::RegisterRx(key, this);
    }
    virtual ~OcApClassFactoryBase() {}
    virtual RootBase * createInstance() = 0;
};

template<class Derived, class RootBase>
class OcApClassFactory : public OcApClassFactoryBase<RootBase>
{
public:
    OcApClassFactory(const wchar_t * key)
        : OcApClassFactoryBase(key)
    {}
    virtual ~OcApClassFactory() {}

    // Create an instance of the object, returning its root base
    virtual RootBase * createInstance() {
        return new Derived;
    }
};


// Helper function so the OcRx based classes can self register
// themselves. The function is not meant to be used directly
// by application code because the second parameter is not
// type safe.
// For normal application code, use the type safe function
// OcApApplication::RegisterRxClass instead.
int __Register_Rx_Class__(const std::wstring & className,
                          void * pCreator);

END_OCTAVARIUM_NS

#endif // OcApClassFactory_h__
