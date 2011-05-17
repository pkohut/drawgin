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


#ifndef OcBsStream_h__
#define OcBsStream_h__


#include "OcTypes.h"
#include "OcBsTypes.h"

BEGIN_OCTAVARIUM_NS

class OcBsStream
{
public:
    OcBsStream(void);
    //explicit OcBsStream(const std::wstring & filename);
    virtual ~OcBsStream(void);

    virtual void Close();
    byte_t * Buffer(void) {
        return m_pBuffer;
    }

    byte_t Get(int nBits);
    byte_t Get(void);
    virtual OcBsStream & Seek(std::streamoff nPos, int nBit = 0) = 0;
    virtual std::streamoff FilePosition(void) const;
    int BufferSize(void) const;




    virtual bool Good(void) const = 0;
    virtual bool Eof(void) const = 0;
    virtual bool Fail(void) const = 0;
    virtual bool Bad(void) const = 0;
    bitcode::T & ConvertToCodepage(bitcode::T & t);
    operator void*(void) const;

    DWG_VERSION Version(void) const;
    void SetVersion(DWG_VERSION version);

    uint16_t CalcedCRC(void) const;
    void SetCalcedCRC(uint16_t crc);

protected:
#if defined(WIN32) && defined(_UNICODE)
    virtual void Open(const std::wstring & filename, int mode);
#else
    virtual void Open(const std::string & filename, int mode);
#endif
protected:
    byte_t         *m_pBuffer;
    std::streamoff  m_filePosition;
    std::streamsize m_fileLength;
    int             m_bitPosition;
    std::streamsize m_indexSize;
    uint16_t        m_crc;
    byte_t          m_cache;
    std::fstream    m_fs;
    DWG_VERSION     m_version;
    bool            m_convertCodepage;

};

END_OCTAVARIUM_NS

#endif // OcBsStream_h__
