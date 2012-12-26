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



/**************************************************************************/
/*  Portions of code from the Visualization Library                       */
/*  which used the "New BSD" license, see "COPYING" for full license      */
/*  notice http://www.visualizationlibrary.com                            */
/*                                                                        */
/*  Copyright (c) 2005-2010, Michele Bosi                                 */
/*  All rights reserved.                                                  */
/**************************************************************************/

#include "OcCommon.h"
#include "OcError.h"
#include "OcRxObject.h"

BEGIN_OCTAVARIUM_NS


OcRxObject::OcRxObject() : m_nReferences(0)
{
}

OcRxObject::OcRxObject( const OcRxObject & other ) : m_nReferences(0)
{
}

OcRxObject::~OcRxObject(void)
{
    DLOG_IF(ERROR, m_nReferences)
            << "Object " << typeid(*this).name() << "is being deleted having still "
            << m_nReferences << "references. Possible causes:\n"
            << "- illegal use of the 'delete' operator on an object.h Use OcPtr<> instead.\n"
            << "- explicit call to Object::incReference().\n\n";
}

int OcRxObject::RegisterRx(const std::string & className,
                           const std::string & acClassName,
                           BaseClassFactory * pCreator)
{
    OcApp::ErrorStatus es = (OcApp::ErrorStatus)
                            __Register_Rx_Class__(className, pCreator);
    if(es == OcApp::eOk) {
        es = (OcApp::ErrorStatus)
             __Register_AcToOc_Pair__(acClassName, className);
    }
    return es;
}

OcRxObject & OcRxObject::operator=( const OcRxObject & other )
{
    return *this;
}


END_OCTAVARIUM_NS
