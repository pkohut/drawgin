/**
 *	@file
 *  @brief Defines OcBsStream abstract class
 *
 *  Abstract base class to support streaming of drawing files
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

#pragma once

#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>

#include "OcBsTypes.h"
#include "OcBsDwgVersion.h"

BEGIN_OCTAVARIUM_NS

class OcBsStream
{
protected:
    // BUFSIZE should be a power of 2 so the compiler
    // can perform any optimizations.
    const static int BUFSIZE = 4096;

public:
    OcBsStream();
    virtual ~OcBsStream();

    virtual void Close();



    std::array<uint8_t, BUFSIZE> & Buffer()
    {
        return m_buffer;
    }

    uint8_t Get(int nBits);
    uint8_t Get();
    uint8_t PeekAhead();
    virtual OcBsStream & Seek(std::streamoff nPos, int nBits = 0) = 0;
    virtual std::streamoff FilePosition() const;
    const static int BufferSize();

    virtual bool Good() const = 0;
    virtual bool Eof() const = 0;
    virtual bool Fail() const = 0;
    virtual bool Bad() const = 0;
    bitcode::T ConvertToCodepage(bitcode::T & t);

    operator void*() const;

    DWG_VERSION Version() const;
    void SetVersion(DWG_VERSION version);

    uint16_t CalcedCRC(bool bRetResultInMSB = false) const;
    void SetCalcedCRC(uint16_t crc);

    virtual OcApp::ErrorStatus Error(void);
    virtual void ClearError();
    virtual void SetError(OcApp::ErrorStatus es);

protected:
    virtual void Open(const std::string & filename, int mode);



protected:
    std::array<uint8_t, BUFSIZE> m_buffer;
    std::streamoff m_filePosition;
    std::streamsize m_fileLength;
    int m_bitPosition;
    std::streamsize m_indexSize;
    uint16_t m_crc;
    uint8_t m_cache;

    std::fstream m_fs;
    DWG_VERSION m_version;
    bool m_convertCodepage;
    bool m_bSeekedOnBufferBoundary;
    OcApp::ErrorStatus m_streamError;
};

END_OCTAVARIUM_NS