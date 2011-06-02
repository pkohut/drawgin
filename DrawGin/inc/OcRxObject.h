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

#ifndef OcRxObject_h__
#define OcRxObject_h__

#include "ClassMacros.h"
#include "OcConfig.h"

#include "OcApClassFactory.h"

BEGIN_OCTAVARIUM_NS
class OcRxObject;
END_OCTAVARIUM_NS

namespace boost
{
void intrusive_ptr_add_ref(octavarium::OcRxObject * p);
void intrusive_ptr_release(octavarium::OcRxObject * p);
}

BEGIN_OCTAVARIUM_NS

class OcRxObject
{
    OC_DECLARE_BASE_CLASS(OcRxObject);
public:
    typedef OcApClassFactoryBase<OcRxObject> BaseClassFactory;

protected:
    OcRxObject() : m_nReferences(0), m_bAutomaticDelete(true) {
        INIT_OBJECT_NAME_FOR_DEBUG();
#if defined(OC_DEBUG_LIVING_OBJECTS) && !defined(NDEBUG)
        DebugLivingObjects()->insert(this);
#endif
    }
    OcRxObject(const OcRxObject & other)
        : m_sObjectName(other.m_sObjectName),
          m_nReferences(0), m_bAutomaticDelete(true) {
#if defined(OC_DEBUG_LIVING_OBJECTS) && !defined(NDEBUG)
        DebugLivingObjects()->insert(this);
#endif
    }
public:
    virtual ~OcRxObject();

    static int RegisterRx(const std::wstring & className,
        OcRxObject::BaseClassFactory * pCreator);

    OcRxObject & operator=(const OcRxObject & other) {
        m_sObjectName = other.m_sObjectName;
        return *this;
    }

    const std::wstring & ObjectName(void) const {
        return m_sObjectName;
    }
    void SetObjectName(const std::wstring & name) {
        m_sObjectName = name;
    }

    void SetAutomaticDelete(bool bAutomaticDelete) {
        m_bAutomaticDelete = bAutomaticDelete;
    }
    bool AutomaticDelete(void) {
        return m_bAutomaticDelete;
    }
    static void ShutdownObjectTracking(void);

#if defined(OC_DEBUG_LIVING_OBJECTS) && !defined(NDEBUG)
private:
    static std::set< OcRxObject* >* m_debug_LivingObjects;
public:
    static std::set< OcRxObject* >* DebugLivingObjects() {
        if(!m_debug_LivingObjects) {
            m_debug_LivingObjects = new std::set< OcRxObject* >;
        }
        return m_debug_LivingObjects;
    }
#endif

protected:
    std::wstring m_sObjectName;

private:
    long    m_nReferences;
    bool    m_bAutomaticDelete;
    friend void ::boost::intrusive_ptr_add_ref(OcRxObject * p);
    friend void ::boost::intrusive_ptr_release(OcRxObject * p);
};
END_OCTAVARIUM_NS

namespace boost
{
inline void intrusive_ptr_add_ref(octavarium::OcRxObject * p)
{
    // increment reference count of object *p
#if OC_THREAD_SAFE_INTRUSIVE_PTR == 1
    _InterlockedIncrement(&(p->m_nReferences));;
#else
    ++(p->m_nReferences);
#endif
}

inline void intrusive_ptr_release(octavarium::OcRxObject * p)
{
    DLOG_IF(ERROR, !p->m_nReferences)
            << p->ClassName() << " still has pointer references";

    // decrement reference count, and delete object when reference count reaches 0
#if OC_THREAD_SAFE_INTRUSIVE_PTR == 1
    if(_InterlockedDecrement(&(p->m_nReferences)) == 0) {
        delete p;
    }
#else
    if(--(p->m_nReferences) == 0) {
        delete p;
    }
#endif
}
} // namespace boost



#endif // OcRxObject_h__
