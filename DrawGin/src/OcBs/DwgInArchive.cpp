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

#include <assert.h>
#include <fstream>
#include <string>
#include <vector>
#include "OcCommon.h"
#include "OcError.h"
#include "OcDbObjectId.h"
#include "OcDbDwgVersion.h"
#include "OcBsTypes.h"
#include "OcBsStreamIn.h"
#include "DwgInArchive.h"

BEGIN_OCTAVARIUM_NS
#define ASSERT_NOT_LOADING assert(ArchiveFlag() == DwgInArchive::LOADING)

DwgInArchive::DwgInArchive(OcBsStreamIn & in)
    : m_stream(in), m_archiveFlag(NOT_SET), m_archiveError(OcApp::eOk)
{
    if(in)
        m_archiveFlag = LOADING;
}

DwgInArchive::~DwgInArchive(void)
{
}

bool DwgInArchive::IsLoading()
{
    return m_archiveFlag == LOADING;
}

bool DwgInArchive::IsSaving()
{
    return m_archiveFlag == SAVING;
}


void DwgInArchive::Close()
{
    m_archiveFlag = NOT_SET;
}


DwgInArchive::ARCHIVE_FLAG DwgInArchive::ArchiveFlag(void)
{
    return m_archiveFlag;
}

OcApp::ErrorStatus DwgInArchive::Error(void)
{
    return m_archiveError;
}

void DwgInArchive::SetError(OcApp::ErrorStatus es)
{
    m_archiveError = es;
}


void DwgInArchive::ClearError(void)
{
    m_archiveError = OcApp::eOk;
}


DwgInArchive::operator void*(void) const
{
    return (m_stream.Bad() || m_stream.Fail()) ? (void *)0 : (void*) this;
}


DwgInArchive & DwgInArchive::operator>>(bitcode::B & b)
{
    ASSERT_NOT_LOADING;
    m_stream >> b;
    return *this;
}

DwgInArchive & DwgInArchive::operator>>(bitcode::BB & bb)
{
    ASSERT_NOT_LOADING;
    m_stream >> bb;
    return *this;
}

DwgInArchive & DwgInArchive::operator>>(bitcode::BBBB & bbbb)
{
    ASSERT_NOT_LOADING;
    m_stream >> bbbb;
    return *this;
}

DwgInArchive & DwgInArchive::operator>>(bitcode::RC & rc)
{
    ASSERT_NOT_LOADING;
    m_stream >> rc;
    return *this;
}

DwgInArchive & DwgInArchive::operator>>(bitcode::RS & rs)
{
    ASSERT_NOT_LOADING;
    m_stream >> rs;
    return *this;
}

DwgInArchive & DwgInArchive::operator>>(bitcode::RL & rl)
{
    ASSERT_NOT_LOADING;
    m_stream >> rl;
    return *this;
}

DwgInArchive & DwgInArchive::operator>>(bitcode::RD & rd)
{
    ASSERT_NOT_LOADING;
    m_stream >> rd;
    return *this;
}

DwgInArchive & DwgInArchive::operator>>(bitcode::RD2 & rd2)
{
    ASSERT_NOT_LOADING;
    m_stream >> rd2;
    return *this;
}

DwgInArchive & DwgInArchive::operator>>(bitcode::RD3 & rd3)
{
    ASSERT_NOT_LOADING;
    m_stream >> rd3;
    return *this;
}

DwgInArchive & DwgInArchive::operator>>(bitcode::BS & bs)
{
    ASSERT_NOT_LOADING;
    m_stream >> bs;
    return *this;
}

DwgInArchive & DwgInArchive::operator>>(bitcode::BL & bl)
{
    ASSERT_NOT_LOADING;
    m_stream >> bl;
    return *this;
}

DwgInArchive & DwgInArchive::operator>>(bitcode::BD & bd)
{
    ASSERT_NOT_LOADING;
    m_stream >> bd;
    return *this;
}

DwgInArchive & DwgInArchive::operator>>(bitcode::BD2 & bd2)
{
    ASSERT_NOT_LOADING;
    m_stream >> bd2;
    return *this;
}

DwgInArchive & DwgInArchive::operator>>(bitcode::BD3 & bd3)
{
    ASSERT_NOT_LOADING;
    m_stream >> bd3;
    return *this;
}

DwgInArchive & DwgInArchive::operator>>(bitcode::MC & mc)
{
    ASSERT_NOT_LOADING;
    m_stream >> mc;
    return *this;
}

DwgInArchive & DwgInArchive::operator>>(bitcode::MS & ms)
{
    ASSERT_NOT_LOADING;
    m_stream >> ms;
    return *this;
}

DwgInArchive & DwgInArchive::operator>>(bitcode::BE & be)
{
    ASSERT_NOT_LOADING;
    m_stream >> be;
    return *this;
}

DwgInArchive & DwgInArchive::operator>>(bitcode::BT & bt)
{
    ASSERT_NOT_LOADING;
    m_stream >> bt;
    return *this;
}

DwgInArchive & DwgInArchive::operator>>(bitcode::CMC & cmc)
{
    ASSERT_NOT_LOADING;
    m_stream >> cmc;
    return *this;
}

DwgInArchive & DwgInArchive::operator>>(bitcode::TV & tv)
{
    ASSERT_NOT_LOADING;
    m_stream >> tv;
    return *this;
}

DwgInArchive & DwgInArchive::operator>>(bitcode::T & t)
{
    ASSERT_NOT_LOADING;
    m_stream >> t;
    return *this;
}

DwgInArchive & DwgInArchive::operator>>(bitcode::TU & tu)
{
    ASSERT_NOT_LOADING;
    m_stream >> tu;
    return *this;
}

DwgInArchive & DwgInArchive::operator>>(bitcode::RC rc[])
{
    ASSERT_NOT_LOADING;
    m_stream >> rc;
    return *this;
}

DwgInArchive & DwgInArchive::ReadRC(bitcode::RC * pRc, size_t size, bool bSkipCrcTracking)
{
    ASSERT_NOT_LOADING;
    uint16_t currentCrc = m_stream.CalcedCRC();
    for(size_t i = 0; i < size; ++i) {
        m_stream >> pRc[i];
    }
    if(bSkipCrcTracking == true)
        m_stream.SetCalcedCRC(currentCrc);
    return *this;
}

DwgInArchive & DwgInArchive::ReadRC(std::vector<bitcode::RC> & rc, size_t size, bool bSkipCrcTracking)
{
    ASSERT_NOT_LOADING;
    uint16_t currentCrc = m_stream.CalcedCRC();
    rc.resize(size);
    for(size_t i = 0; i < size; ++i) {
        m_stream >> rc[i];
    }
    if(bSkipCrcTracking == true)
        m_stream.SetCalcedCRC(currentCrc);
    return *this;
}

DwgInArchive & DwgInArchive::ReadRC(std::string & rc, size_t size, bool bSkipCrcTracking)
{
    ASSERT_NOT_LOADING;
    uint16_t currentCrc = m_stream.CalcedCRC();
    rc.resize(size);
    for(size_t i = 0; i < size; ++i) {
        m_stream >> (bitcode::RC*)&rc[i];
    }
    if(bSkipCrcTracking == true)
        m_stream.SetCalcedCRC(currentCrc);
    return *this;
}

DwgInArchive & DwgInArchive::Seek(std::streamoff nPos)
{
    m_stream.Seek(nPos);
    return *this;
}

std::streamoff DwgInArchive::FilePosition(void) const
{
    return m_stream.FilePosition();
}

octavarium::DWG_VERSION DwgInArchive::Version(void) const
{
    return m_stream.Version();
}

void DwgInArchive::SetVersion(DWG_VERSION version)
{
    m_stream.SetVersion(version);
}

DwgInArchive & DwgInArchive::ReadHandle(OcDbObjectId & objId)
{
    ASSERT_NOT_LOADING;
    m_stream.ReadHandle(objId);
    return *this;
}

DwgInArchive & DwgInArchive::operator>>(OcDbObjectId & objId)
{
    ASSERT_NOT_LOADING;
    m_stream >> objId;
    return *this;
}


DwgInArchive & DwgInArchive::ReadCRC( uint16_t & crc, bool bSkipCrcTracking)
{
    ASSERT_NOT_LOADING;
    m_stream.ReadCRC(crc, bSkipCrcTracking);
    return *this;
}

octavarium::uint16_t DwgInArchive::CalcedCRC(bool bRetResultInMSB) const
{
    return m_stream.CalcedCRC(bRetResultInMSB);
}

void DwgInArchive::SetCalcedCRC( uint16_t crc )
{
    m_stream.SetCalcedCRC(crc);
}

void DwgInArchive::AdvanceToByteBoundary( void )
{
    m_stream.AdvanceToByteBoundary();
}



//} // namespace archive

END_OCTAVARIUM_NS
