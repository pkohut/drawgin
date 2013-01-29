/**
 *	@file
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

#include "OcCommon.h"
#include "OcError.h"
#include "OcDbDatabase_p.h"
#include "OcDbDatabase.h"

BEGIN_OCTAVARIUM_NS

OcDbDatabase::OcDbDatabase(bool buildDefaultDrawing, bool noDocument)
    : m_pImpl(new OcDbDatabasePrivate())
{
    VLOG_FUNC_NAME;
    m_pImpl->m_qPtr = this;
}

OcDbDatabase::OcDbDatabase(std::unique_ptr<OcDbDatabasePrivate> & d)
    : m_pImpl(std::move(d))
{
    VLOG_FUNC_NAME;
}

OcDbDatabase::~OcDbDatabase(void)
{
    VLOG_FUNC_NAME;
}

OcDbDatabasePrivate * OcDbDatabase::d_func()
{
    VLOG_FUNC_NAME;
    return m_pImpl.get();
}

const OcDbDatabasePrivate * OcDbDatabase::d_func() const
{
    VLOG_FUNC_NAME;
    return m_pImpl.get();
}

OcApp::ErrorStatus OcDbDatabase::ReadDwg(const std::string & sFilename)
{
    VLOG_FUNC_NAME;
    VLOG(4) << "OcDbDatabase::ReadDwg entered";
    OcApp::ErrorStatus es = m_pImpl->ReadDwg(sFilename);
    if(es == OcApp::eOk)
    {
        LOG(INFO) << "Reading drawing file successful";
    }
    else
    {
        LOG(ERROR) << "Reading drawing file failed";
    }
    return es;
}

END_OCTAVARIUM_NS