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

#ifndef OcDbClassFactory_h__
#define OcDbClassFactory_h__

BEGIN_OCTAVARIUM_NS

template<class Base>
Base * NewObject(const std::wstring&);

template<class Base> class OcDbClassFactory
{
    OcDbClassFactory() {}
    OcDbClassFactory& operator=(const OcDbClassFactory&);
    ~OcDbClassFactory()
    {
        int x = 0;
        x++;
        // delete everything
    }

public:
    Base * Create(const std::wstring& nm) const
    {
        return (creators.contains(nm) ? creators[nm]->create() : NULL);   
    }

    bool Exists(const std::wstring& nm) const
    {
        return creators.contains(nm);
    }

    friend Base * NewObject<>(const std::wstring&);

    class Creator
    {
    public:
        virtual ~Creator() {}
        virtual Base * Create() const = 0;
    };
    static OcDbClassFactory & Instance()
    {
        static OcDbClassFactory pInstance;
        return pInstance;
    }

    void unregisterCreator(const std::wstring &nm)
    {
        if(creators.find(nm) != creators.end()) {
            delete creators[nm];
            creators.erase(nm);
        }
    }

    void registerCreator(const std::wstring & nm, const Creator * c)
    {
        unregisterCreator(nm);
        creators.insert(std::pair<std::wstring, const Creator*>(nm, c));
    }
private:
    std::map<std::wstring, const Creator*> creators;
};


template<class Base>
Base * NewObject(const std::wstring & nm)
{
    return OcDbClassFactory<Base>::Instance().Create(nm);
}

template<class Derived, class Base> class Register
{
    typedef Derived* (*CreateFn)();
    class Creator : public OcDbClassFactory<Base>::Creator
    {
    public:
        Creator(CreateFn fn) : createFn(fn) {}
        virtual Derived * Create() const
        {
            return (createFn ? createFn() : new Derived(NULL));
        }
        CreateFn createFn;
    };
public:
    Register(const std::wstring & nm, CreateFn fn = NULL)
    {
        OcDbClassFactory<Base>::Instance().registerCreator(nm, new Creator(fn));
    }
};

END_OCTAVARIUM_NS

#endif // OcDbClassFactory_h__
