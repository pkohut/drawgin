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

#ifndef OcBsStreamIn_h__
#define OcBsStreamIn_h__

#include "OcBsStream.h"

BEGIN_OCTAVARIUM_NS

class OcBsStreamIn : public OcBsStream
{
public:
    OcBsStreamIn(void);
#if defined(WIN32) && (_UNICODE)
    explicit OcBsStreamIn(const std::wstring & filename);
#else
    explicit OcBsStreamIn(const std::string & filename);
#endif
    virtual ~OcBsStreamIn(void);

#if defined(WIN32) && (_UNICODE)
    virtual void Open(const std::wstring & filename);
#else
    virtual void Open(const std::string & filename);
#endif
    virtual bool Good(void) const;
    virtual bool Eof(void) const;
    virtual bool Fail(void) const;
    virtual bool Bad(void) const;
    byte_t * Buffer(void) {
        return OcBsStream::Buffer();
    }
    virtual OcBsStreamIn & Seek(std::streamoff nPos, int nBit = 0);
    OcBsStreamIn & ReadHandle(OcDbObjectId & objId);
    OcBsStreamIn & ReadCRC(uint16_t & crc, bool bSkipCrcTracking = true);

    virtual OcBsStreamIn & operator>>(OcDbObjectId & objId);
    virtual OcBsStreamIn & operator>>(bitcode::B & b);
    virtual OcBsStreamIn & operator>>(bitcode::BB & bb);
    virtual OcBsStreamIn & operator>>(bitcode::BBBB & bbbb);
    virtual OcBsStreamIn & operator>>(bitcode::BD & bd);
    virtual OcBsStreamIn & operator>>(bitcode::BD2 & bd);
    virtual OcBsStreamIn & operator>>(bitcode::BD3 & bd);
    virtual OcBsStreamIn & operator>>(bitcode::BE & be);
    virtual OcBsStreamIn & operator>>(bitcode::BL & bl);
    virtual OcBsStreamIn & operator>>(bitcode::BS & bs);
    virtual OcBsStreamIn & operator>>(bitcode::BT & bt);
    virtual OcBsStreamIn & operator>>(bitcode::CMC & cmc);
    virtual OcBsStreamIn & operator>>(bitcode::MC & mc);
    virtual OcBsStreamIn & operator>>(bitcode::MS & ms);
    virtual OcBsStreamIn & operator>>(bitcode::RC & rc);
    virtual OcBsStreamIn & operator>>(bitcode::RC   rc[]);
    virtual OcBsStreamIn & operator>>(bitcode::RD & rd);
    virtual OcBsStreamIn & operator>>(bitcode::RD2 & rd2);
    virtual OcBsStreamIn & operator>>(bitcode::RD3 & rd3);
    virtual OcBsStreamIn & operator>>(bitcode::RL & rl);
    virtual OcBsStreamIn & operator>>(bitcode::RS & rs);
    virtual OcBsStreamIn & operator>>(bitcode::TV & tv);
    virtual OcBsStreamIn & operator>>(bitcode::T & t);
    virtual OcBsStreamIn & operator>>(bitcode::TU & tu);

};

END_OCTAVARIUM_NS

#endif // OcBsStreamIn_h__
