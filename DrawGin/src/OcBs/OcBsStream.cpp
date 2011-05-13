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


#include "stdafx.h"
#include <sys/types.h>
#include <sys/stat.h>

#include "OcCommon.h"
#include "OcDbDwgVersion.h"
#include "OcBsStream.h"

#ifndef S_ISDIR
#define S_ISDIR(mode) (((mode) & S_IFMT) == S_IFDIR)
#endif

#ifndef S_ISREG
#define S_ISREG(mode) (((mode) & S_IFMT) == S_IFREG)
#endif

BEGIN_OCTAVARIUM_NS
using namespace std;

// BUFSIZE should be a power of 2 so the compiler
// can perform any optimizations.
const int BUFSIZE = 4096;


//extern boost::uint8_t mask8(unsigned int param);

OcBsStream::OcBsStream(void)
    : m_pBuffer(NULL), m_filePosition(0), m_fileLength(0), m_bitPosition(0),
      m_indexSize(0), m_version(NONE), m_convertCodepage(false)
{
}

//OcBsStream::OcBsStream(const std::wstring & filename)
//    : m_pBuffer(NULL), m_filePosition(0), m_fileLength(0), m_bitPosition(0),
//      m_indexSize(0), m_version(000), m_convertCodepage(false)
//{
//    open(filename);
//}

OcBsStream::~OcBsStream(void)
{
    Close();
}

#if defined(WIN32) && defined(_UNICODE)
void OcBsStream::Open(const std::wstring & filename, int mode)
#else
void OcBsStream::Open(const std::string & filename, int mode)
#endif
{
    //    m_fs.open(filename.c_str(), fstream::in | fstream::binary);
    if(m_fs.is_open()) {
        Close();
    }

#if defined(WIN32)
    struct _stat fileStat;
    if(_tstat(filename.c_str(), &fileStat) == -1) {
#else
    struct stat fileStat;
    if(stat(filename.c_str(), &fileStat) == -1) {
#endif
        LOG(ERROR) << "Invalid file name or invalid permissions.";
        m_fs.setstate(ios_base::badbit);
        return;
    }

    if(S_ISDIR(fileStat.st_mode)) {
        LOG(ERROR) << "Invalid filetype, input file name is a directory.";
        m_fs.setstate(ios_base::badbit);
        return;
    }

    m_fs.open(filename.c_str(), (ios_base::openmode) mode);
    if(Good()) {
        m_fs.seekg(0, ios::end);
        m_fileLength = m_fs.tellg();
        m_fs.seekg(0, ios::beg);
        m_pBuffer = new byte_t[BUFSIZE];
        m_cache = 0;
    }
}

void OcBsStream::Close()
{
    m_fs.close();
    delete [] m_pBuffer;
    m_pBuffer = NULL;
    m_fileLength = m_filePosition = 0;
    m_bitPosition = m_indexSize = 0;
    m_cache = 0;
}

byte_t OcBsStream::Get(int nBits)
{
    std::streamsize pos = m_filePosition % BUFSIZE;
    if(pos == 0) {
        m_fs.read((char *) m_pBuffer, BUFSIZE);
        m_indexSize = std::min(m_fs.gcount(), m_fileLength
                               - (std::streamsize)m_filePosition);
    }
    m_filePosition += nBits / CHAR_BIT;
    m_bitPosition = (m_bitPosition + nBits) % CHAR_BIT;
    return m_pBuffer[pos];
}

byte_t OcBsStream::Get()
{
    std::streamsize pos = m_filePosition % BUFSIZE;
    if(pos == 0) {
        m_fs.read((char *) m_pBuffer, BUFSIZE);
        m_indexSize = std::min(m_fs.gcount(), m_fileLength
                               - (std::streamsize) m_filePosition);
    }
    m_filePosition++;
    return m_pBuffer[pos];
}

bitcode::TV & OcBsStream::ConvertToCodepage(bitcode::TV & tv)
{
    return tv;
}

OcBsStream::operator void*(void) const
{
    return (Fail() || Bad()) ? (void*)0 : (void*)this;
}

int OcBsStream::BufferSize(void) const
{
    return BUFSIZE;
}

std::streamoff OcBsStream::FilePosition(void) const
{
    return m_filePosition;
}

DWG_VERSION OcBsStream::Version(void) const
{
    return m_version;
}

void OcBsStream::SetVersion(DWG_VERSION version)
{
    m_version = version;
}

END_OCTAVARIUM_NS
