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
#include "OcBsStream.h"

#ifndef S_ISDIR
#define S_ISDIR(mode) (((mode) & S_IFMT) == S_IFDIR)
#endif

#ifndef S_ISREG
#define S_ISREG(mode) (((mode) & S_IFMT) == S_IFREG)
#endif

using namespace std;

BEGIN_OCTAVARIUM_NS

// BUFSIZE should be a power of 2 so the compiler
// can perform any optimizations.
//const int OcBsStream::BUFSIZE = 4096;


OcBsStream::OcBsStream()
    : m_filePosition(0), m_fileLength(0), m_bitPosition(0),
      m_indexSize(0), m_crc(0), m_version(NONE), m_convertCodepage(false),
      m_bSeekedOnBufferBoundary(false), m_streamError(OcApp::eOk)
{
    VLOG_FUNC_NAME;
}


OcBsStream::~OcBsStream()
{
    VLOG_FUNC_NAME;
}


void OcBsStream::Close()
{
    VLOG_FUNC_NAME;
    m_fileLength = m_filePosition = m_indexSize = 0;
    m_bitPosition = 0;
    m_cache = 0;
}


uint8_t OcBsStream::Get(int nBits)
{
    VLOG_FUNC_NAME;
    std::streamsize pos = m_filePosition % BUFSIZE;

    if(pos == 0 && !m_bSeekedOnBufferBoundary)
    {
        m_fs.read((char *) &m_buffer, BUFSIZE);
        m_indexSize = std::min(m_fs.gcount(), m_fileLength
                               - (std::streamsize)m_filePosition);
    }

    m_filePosition += nBits / CHAR_BIT;
    m_bitPosition = (m_bitPosition + nBits) % CHAR_BIT;
    return m_buffer[(size_t)pos];
}

uint8_t OcBsStream::Get()
{
    VLOG_FUNC_NAME;
    std::streamsize pos = m_filePosition % BUFSIZE;

    if(pos == 0 && !m_bSeekedOnBufferBoundary)
    {
        m_fs.read((char *) &m_buffer, BUFSIZE);
        m_indexSize = std::min(m_fs.gcount(), m_fileLength
                               - (std::streamsize) m_filePosition);
    }

    return m_buffer[(size_t)pos];
}

uint8_t OcBsStream::PeekAhead()
{
    VLOG_FUNC_NAME;
    m_filePosition++;
    uint8_t byte = Get();
    m_filePosition--;
    return byte;
}


bitcode::T OcBsStream::ConvertToCodepage(bitcode::T & t)
{
    VLOG_FUNC_NAME;
    LOG(ERROR) << "OcBsString::ConvertToCodepage not implemented, returning original string";
    return t;
}

std::streamoff OcBsStream::FilePosition() const
{
    VLOG_FUNC_NAME;
    return m_filePosition;
}

const int OcBsStream::BufferSize()
{
    VLOG_FUNC_NAME;
    return BUFSIZE;
}

OcBsStream::operator void*() const
{
    VLOG_FUNC_NAME;
    return (Fail() || Bad()) ? (void*)0 : (void*)this;
}

octavarium::DWG_VERSION OcBsStream::Version() const
{
    VLOG_FUNC_NAME;
    return m_version;
}

void OcBsStream::SetVersion(DWG_VERSION version)
{
    VLOG_FUNC_NAME;
    m_version = version;
}

uint16_t OcBsStream::CalcedCRC(bool bRetResultInMSB /*= false*/) const
{
    VLOG_FUNC_NAME;
    // when bRetResultInMSB is true then some bit twiddling is done
    // that expects m_crc to be a 16 bit integer. Assert if not.
    DCHECK(sizeof(m_crc) == sizeof(uint16_t))
            << "size of m_crc must be a 16 bit integer";

    if(bRetResultInMSB)
    {
        uint16_t crc = m_crc;
        byte_t * pCrc = (byte_t *) &crc;
        // XOR byte swap
        (pCrc[0] ^= pCrc[1]), (pCrc[1] ^= pCrc[0]), (pCrc[0] ^= pCrc[1]);
        return crc;
    }

    return m_crc;
}

void OcBsStream::SetCalcedCRC(uint16_t crc)
{
    VLOG_FUNC_NAME;
    m_crc = crc;
}

void OcBsStream::Open(const std::string & filename, int mode)
{
    VLOG_FUNC_NAME;

    if(m_fs.is_open())
    {
        Close();
    }

    struct stat fileStat;

    if(stat(filename.c_str(), &fileStat) == -1)
    {
        LOG(ERROR) << "Invalid file name or invalid permissions.";
        m_fs.setstate(ios_base::badbit);
        return;
    }

    if(S_ISDIR(fileStat.st_mode))
    {
        LOG(ERROR) << "Invalid filetype, input file name is a directory.";
        m_fs.setstate(ios_base::badbit);
        return;
    }

    m_fs.open(filename.c_str(), (ios_base::openmode) mode);

    if(Good())
    {
        m_fs.seekg(0, ios::end);
        m_fileLength = m_fs.tellg();
        m_fs.seekg(0, ios::beg);
        m_cache = 0;
    }
}

OcApp::ErrorStatus OcBsStream::Error(void)
{
    VLOG_FUNC_NAME;
    return m_streamError;
}

void OcBsStream::ClearError()
{
    VLOG_FUNC_NAME;
    m_streamError = OcApp::eOk;
}

void OcBsStream::SetError(OcApp::ErrorStatus es)
{
    VLOG_FUNC_NAME;
    m_streamError = es;
}

END_OCTAVARIUM_NS