/**
 *	@file
 *  @brief Defines OcBsStreamIn class
 *
 *  Support to read drawing files
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
#include "OcBsStream.h"
#include "OcDbObjectId.h"

BEGIN_OCTAVARIUM_NS

class OcBsStreamIn : public OcBsStream
{
public:
    OcBsStreamIn(void);
    explicit OcBsStreamIn(const std::string & filename);

    virtual ~OcBsStreamIn(void);

    virtual void Open(const std::string & filename);

    virtual bool Good(void) const;
    virtual bool Eof(void) const;
    virtual bool Fail(void) const;
    virtual bool Bad(void) const;
    std::array<uint8_t, BUFSIZE> & Buffer(void)
    {
        return OcBsStream::Buffer();
    }
    virtual OcBsStreamIn & Seek(std::streamoff nPos, int nBit = 0);
    OcBsStreamIn & ReadHandle(OcDbObjectId & objId);
    OcBsStreamIn & ReadCRC(uint16_t & crc, bool bSkipCrcTracking = true);
    OcBsStreamIn & ReadRC(bitcode::RC * pRc, size_t size, bool bSkipCrcTracking = false);
    OcBsStreamIn & ReadRC(std::vector<bitcode::RC> & rc, size_t size, bool bSkipCrcTracking = false);
    OcBsStreamIn & ReadRC(std::string & rc, size_t size, bool bSkipCrcTracking = false);

    void AdvanceToByteBoundary(void);

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


// helper template function to ensure T is dereferenced before
// calling stream in.
template<typename BC, typename T>
OcBsStreamIn& StreamIn(OcBsStreamIn & stream, const T & t)
{
    stream >> (BC&) t;
    return stream;
}


template<typename BC, typename T>
OcBsStreamIn& StreamIn(OcBsStreamIn & stream, const T & t, const char * pStr)
{
    StreamIn<BC, T>(stream, t);
    VLOG(4) << pStr << ": " << t;
    return stream;
}

// handle when t is a char and print t as an int
template<typename BC>
OcBsStreamIn& StreamIn(OcBsStreamIn & stream, const int8_t & t, const char * pStr)
{
    StreamIn<BC>(stream, t);
    VLOG(4) << pStr << ": " << (int) t;
    return stream;
}

template<typename BC>
OcBsStreamIn& StreamIn(OcBsStreamIn & stream, const bool & t, const char * pStr)
{
    StreamIn<BC>(stream, t);
    VLOG(4) << pStr << ": " << (t == true ? "true" : "false");
    return stream;
}

template<typename BC>
OcBsStreamIn& StreamIn(OcBsStreamIn & stream, const byte_t & t, const char * pStr)
{
    StreamIn<BC>(stream, t);
    VLOG(4) << pStr << ": " << (int) t;
    return stream;
}

template<typename BC>
OcBsStreamIn& StreamIn(OcBsStreamIn & stream, const bitcode::CMC & t, const char * pStr)
{
    StreamIn<BC>(stream, t);
    VLOG(4) << pStr << ": " << (bitcode::BCCMC&)t;
    return stream;
}

template<typename BC>
OcBsStreamIn& StreamIn(OcBsStreamIn & stream, const std::wstring & t, const char * pStr)
{
    // need to figure out why wstring and wchar_t can not be streamed directly.
    // If it is streamed directly right now it prints the hex address of
    // the string.
    // Prior to adding the OcGePoint2d class this worked fined, and did not
    // require this template specialization.
    if(typeid(BC).name() == typeid(bitcode::T).name()
            || (typeid(BC).name() == typeid(bitcode::TV).name()
                && stream.Version() <= R2004))
    {
        //        if(ar.Version() <= R2004) {
        StreamIn<bitcode::T>(stream, t);
        VLOG(4) << pStr << ": \"" << WStringToString(t.c_str()).c_str() << "\"";
    }
    else
    {
        StreamIn<bitcode::TU>(stream, t);
        VLOG(4) << pStr << ": U\"" << WStringToString(t.c_str()).c_str() << "\"";
    }

    //    StreamIn<BC>(ar, t);
    //    VLOG(4) << pStr << ": \"" << WStringToString(t.c_str()).c_str() << "\"";
    return stream;
}

template<typename BC>
OcBsStreamIn& StreamIn(OcBsStreamIn & stream, const wchar_t * t, const char * pStr)
{
    StreamIn<BC>(stream, t);
    VLOG(4) << pStr << ": \"" << t << "\"";
    return stream;
}

template<typename BC>
OcBsStreamIn& StreamIn(OcBsStreamIn & stream, const double & t, const char * pStr)
{
    StreamIn<BC>(stream, t);
    VLOG(4) << std::showpoint << pStr << ": " << t;
    return stream;
}

template<typename BC>
OcBsStreamIn& StreamIn(OcBsStreamIn & stream, const OcDbObjectId & t, const char * pStr)
{
    StreamIn<BC>(stream, t);
    VLOG(4) << std::showpoint << pStr << ": " << t;
    return stream;
}

std::string RC2Hex(const std::vector<bitcode::RC> &bytes);

// Help with dead string stripping for the StreamIn template, without this
// DSS only occurred with gcc compiler setting of -O3
#if GOOGLE_STRIP_LOG > 0
// have compiler strip away STR from code
#  define BS_STREAMIN(BC, STREAM, T, STR) StreamIn<BC>(STREAM, T, "");
#else
#  define BS_STREAMIN(BC, STREAM, T, STR) StreamIn<BC>(STREAM, T, #STR);
#endif

END_OCTAVARIUM_NS
