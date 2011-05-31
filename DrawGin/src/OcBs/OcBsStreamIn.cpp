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

#include <limits>

#include "OcCommon.h"
#include "OcDbObjectId.h"
#include "OcDbDwgVersion.h"
#include "OcBsStreamIn.h"
#include "OcBsDwgCrc.h"

BEGIN_OCTAVARIUM_NS

using namespace std;

OcBsStreamIn::OcBsStreamIn(void)
{
}

#if defined(WIN32) && defined(_UNICODE)
OcBsStreamIn::OcBsStreamIn(const std::wstring & filename)
#else
OcBsStreamIn::OcBsStreamIn(const std::string & filename)
#endif
{
    Open(filename);
}

OcBsStreamIn::~OcBsStreamIn(void)
{
}

#if defined(WIN32) && defined(_UNICODE)
void OcBsStreamIn::Open(const std::wstring & filename)
#else
void OcBsStreamIn::Open(const std::string & filename)
#endif
{
    OcBsStream::Open(filename, fstream::in | fstream::binary);
}

OcBsStreamIn & OcBsStreamIn::Seek(std::streamoff nPos, int nBit)
{
    m_filePosition = nPos + (nBit / CHAR_BIT);
    std::streamoff pos = m_filePosition / BufferSize() * BufferSize();
    if(m_fs.eof())
        m_fs.clear();
    m_fs.seekg(pos, ios::beg);
    m_fs.read((char *) m_pBuffer, BufferSize());

    m_indexSize = std::min(m_fs.gcount(), m_fileLength
                           - (std::streamsize)m_filePosition);
    m_bitPosition = nBit % CHAR_BIT;
    return *this;
}


bool OcBsStreamIn::Good(void) const
{
    if(m_fs.good()) {
        return true;
    }
    return Eof();
}

bool OcBsStreamIn::Eof(void) const
{
    if(m_fs.eof() && m_filePosition < m_fileLength) {
        return true;
    }
    return false;
}

bool OcBsStreamIn::Fail(void) const
{
    return m_fs.fail();
}

bool OcBsStreamIn::Bad(void) const
{
    return m_fs.bad();
}

OcBsStreamIn & OcBsStreamIn::ReadHandle(OcDbObjectId & objId)
{
    bitcode::BBBB code;
    bitcode::BBBB counter;
    *this >> code;
    *this >> counter;
    bitcode::RC rc;
    int64_t val = 0;
    for(int i = (int) counter - 1; i >= 0; --i) {
        *this >> rc;
        val |= (uint8_t)rc << (i * CHAR_BIT);
    }
    objId.Handle(val);
    return *this;
}

OcBsStreamIn & OcBsStreamIn::ReadCRC(uint16_t & crc, bool bSkipCrcTracking)
{
    uint16_t currentCrc = CalcedCRC();
    // CRC are located on byte boundaries within the file.
    // if m_bitPosition is not 0 then "advance" to next
    // byte boundary. This is simply accomplished by setting
    // m_bitPosition to 0, then the next stream operation
    // will read the next byte into m_cache. See Get()
    // function this class.
    AdvanceToByteBoundary();
    //if(m_bitPosition != 0) {
    //    m_bitPosition = 0;
    //    m_filePosition++;
    //}

    *this >> (bitcode::RS&) crc;
    if(bSkipCrcTracking == true)
        SetCalcedCRC(currentCrc);
    return *this;
}


void OcBsStreamIn::AdvanceToByteBoundary( void )
{
    if(m_bitPosition) {
        m_bitPosition = 0;
        m_filePosition++;
    }
}


//////////////////////////////////////////////////////////////////////////

OcBsStreamIn & OcBsStreamIn::operator>>(OcDbObjectId & objId)
{
    return ReadHandle(objId);
}

OcBsStreamIn & OcBsStreamIn::operator>>(bitcode::B & b)
{
    b = 0;
    if(m_bitPosition == 0) {
        m_cache = Get();
        m_crc = crc8(m_crc, (const char *) &m_cache, sizeof(byte_t));
    }
    b = (m_cache & (0x80 >> m_bitPosition)) >> (7 - m_bitPosition);    
    m_filePosition += (m_bitPosition + 1) / 8;
    m_bitPosition = (m_bitPosition + 1) % CHAR_BIT;    
    return *this;
}

OcBsStreamIn & OcBsStreamIn::operator>>(bitcode::BB & bb)
{
    bitcode::B b;
    *this >> b;
    bb = b << 1;
    *this >> b;
    bb |= b;
    return *this;
}

OcBsStreamIn & OcBsStreamIn::operator>>(bitcode::BBBB & bbbb)
{
    bitcode::BB bb;
    *this >> bb;
    bbbb = bb << 2;
    *this >> bb;
    bbbb |= bb;
    return *this;
}

OcBsStreamIn & OcBsStreamIn::operator>>(bitcode::BD & bd)
{
    bitcode::BB bb;
    *this >> bb;
    switch(bb.t) {
    case 0:
        *this >> (bitcode::RD&)bd;
        break;
    case 1:
        bd = 1.0;
        break;
    case 2:
        bd = 0.0;
        break;
    default:
        //bd = _Nan._Double;
        bd = std::numeric_limits<double>::quiet_NaN();
        break;
    }
    return *this;
}

OcBsStreamIn & OcBsStreamIn::operator>>(bitcode::BD2 & bd)
{
    bitcode::BD * pBD2 = (bitcode::BD*)&bd;
    *this >> pBD2[0];
    *this >> pBD2[1];
    return *this;
}

OcBsStreamIn & OcBsStreamIn::operator>>(bitcode::BD3 & bd)
{
    bitcode::BD * pBD3 = (bitcode::BD*)&bd;
    *this >> pBD3[0];
    *this >> pBD3[1];
    *this >> pBD3[2];
    return *this;
}

OcBsStreamIn & OcBsStreamIn::operator>>(bitcode::BE & be)
{
    if(m_version >= R2000) {
        be.t.set(0.0, 0.0, 1.0);
    } else {
        bitcode::BD * pbd = (bitcode::BD*)&be;
        *this >> pbd[0] >> pbd[1] >> pbd[2];
    }
    return *this;
}

OcBsStreamIn & OcBsStreamIn::operator>>(bitcode::BL & bl)
{
    bitcode::BB bb;
    *this >> bb;
    switch(bb.t) {
    case 0:
        *this >> (bitcode::RL&)bl;
        break;
    case 1:
        bl = 0;
        *this >> (bitcode::RC&)bl;
        break;
    case 2:
        bl = 0;
        break;
    default:
        bl = INT_MIN;
        break;
    }
    return *this;
}

OcBsStreamIn & OcBsStreamIn::operator>>(bitcode::BS & bs)
{
    bitcode::BB bb;
    *this >> bb;
    switch(bb.t) {
    case 0:
        *this >> (bitcode::RS&)bs;
        break;
    case 1:
        bs = 0; // 0 out since type RC is smaller than RS
        *this >> (bitcode::RC&)bs;
        break;
    case 2:
        bs = 0;
        break;
    default:
        bs = 256;
        break;
    }
    return *this;
}

OcBsStreamIn & OcBsStreamIn::operator>>(bitcode::BT & bt)
{
    int flag = false;
    if(m_version >= R2000) {
        *this >> (bitcode::B&)flag;
    }

    if(flag) {
        bt = 0.0;
    } else {
        bitcode::BD bd;
        *this >> bd;
        bt = bd;
    }
    return *this;
}

OcBsStreamIn & OcBsStreamIn::operator>>(bitcode::CMC & cmc)
{
    *this >> (bitcode::BS&)cmc.t.index;
    if(m_version >= R2004) {
        *this >> (bitcode::BL&)cmc.t.rgb >> (bitcode::RC&)cmc.t.colorByte;
        if(cmc.t.colorByte & 1) {
            *this >> (bitcode::TV&)cmc.t.name;
        }
        if(cmc.t.colorByte & 2) {
            *this >> (bitcode::TV&)cmc.t.bookName;
        }
    }
    return *this;
}

OcBsStreamIn & OcBsStreamIn::operator>>(bitcode::MC & mc)
{
    mc = 0;
    bitcode::RC rc[4] = {
        (bitcode::RC)0, (bitcode::RC)0,
        (bitcode::RC)0 ,(bitcode::RC)0,
    };
    for(int i = 3, j = 0; i >= 0; --i, j += 7) {
        *this >> rc[i];
        if(rc[i] & 0x80) {
            rc[i] &= 0x7f;
        } else {
            int bNeg = false;
            if(rc[i] & 0x40) {
                bNeg = true;
                rc[i] &= 0xbf;
            }
            mc |= ((bitcode::MC)rc[i] << j);
            mc = ((bitcode::MC)mc ^ -bNeg) + bNeg;
            return *this;
        }
        mc |= ((bitcode::MC)rc[i] << j);
    }
    // error parsing if it gets here.
    mc = INT_MIN;
    return *this;
}

OcBsStreamIn & OcBsStreamIn::operator>>(bitcode::MS & ms)
{
    ms = 0;
    bitcode::RS rs[2] = {(bitcode::RS) 0, (bitcode::RS)0} ;
    for(int i = 1, j = 0; i >= 0; --i, j += 15) {
        *this >> rs[i];
        if(rs[i] & 0x8000) {
            rs[i] &= 0x7fff;
        } else {
            ms |= ((uint16_t)rs[i] << j);
            return *this;
        }
        ms |= ((uint16_t)rs[i] << j);
    }
    // error parsing if it gets here.
    ms = INT_MIN;
    return *this;
}

OcBsStreamIn & OcBsStreamIn::operator>>(bitcode::RC & rc)
{
    rc = 0;
    if(m_bitPosition == 0) {
        rc = m_cache = Get();
        m_crc = crc8(m_crc, (const char *) &m_cache, sizeof(byte_t));
    } else {
        rc = m_cache << m_bitPosition;
        if(m_filePosition < m_fileLength - 1) {
            m_cache = PeekAhead();
            m_crc = crc8(m_crc, (const char *) &m_cache, sizeof(byte_t));
            rc |= m_cache >> (8 - m_bitPosition);
        }
    }
    m_filePosition += (m_bitPosition + 8) / 8;
    m_bitPosition = (m_bitPosition + 8) % CHAR_BIT;
    return *this;
}

OcBsStreamIn & OcBsStreamIn::operator>>(bitcode::RC  rc[])
{
    return *this >> *rc;
}

OcBsStreamIn & OcBsStreamIn::operator>>(bitcode::RD & rd)
{
    bitcode::RC rc;
    byte_t * rVal = (byte_t*)&rd;
    for(int i = 0; i < 8; ++i) {
        *this >> rc;
        rVal[i] = rc;
    }
    return *this;
}

OcBsStreamIn & OcBsStreamIn::operator>>(bitcode::RD2 & rd2)
{
    bitcode::RD * prd2 = (bitcode::RD*)&rd2;
    *this >> prd2[0];
    *this >> prd2[1];
    return *this;
}

OcBsStreamIn & OcBsStreamIn::operator>>(bitcode::RD3 & rd3)
{
    bitcode::RD * prd3 = (bitcode::RD*)&rd3;
    *this >> prd3[0];
    *this >> prd3[1];
    *this >> prd3[2];
    return *this;
}

OcBsStreamIn & OcBsStreamIn::operator>>(bitcode::RL & rl)
{
    bitcode::RS rs;
    *this >> rs;
    rl = (uint16_t)rs;
    *this >> rs;
    rl |= ((uint16_t)rs << 16);
    return *this;
}

OcBsStreamIn & OcBsStreamIn::operator>>(bitcode::RS & rs)
{
    bitcode::RC rc;
    *this >> rc;
    rs = (uint8_t)rc;
    *this >> rc;
    rs |= ((uint8_t)rc << 8);
    return *this;
}

OcBsStreamIn & OcBsStreamIn::operator>>(bitcode::TV & tv)
{
    if(m_version < R2007) {
        *this >> (bitcode::T&) tv;
    } else {
        *this >> (bitcode::TU&) tv;
    }

    return *this;
}

OcBsStreamIn & OcBsStreamIn::operator>>(bitcode::T & t)
{
    t.t.clear();
    bitcode::BS length;
    *this >> length;

    for(int i = 0; i < length.t; ++i) {
        bitcode::RC rc;
        *this >> rc;
        if(rc == 0 && i == length - 1) {
            // don't push trailing null ('\0')
        } else {
            t.t.push_back(rc);
        }
    }

    for(size_t i = 0; i < t.t.size(); ++i) {
        // check if NULL is embedded in the string space.
        // If there is, then the string space may represent
        // a string array. Will need to investigate and
        // code appropriately.
        // For now just debug assert.
        assert(t.t[i] != L'\0');
    }

    if(m_convertCodepage) {
        ConvertToCodepage(t);
    }

    return *this;
}

OcBsStreamIn & OcBsStreamIn::operator>>(bitcode::TU & tu)
{
    tu.t.clear();
    bitcode::BS length;
    *this >> length;

    for(int i = 0; i < length.t; ++i) {
        bitcode::RS rs;
        *this >> rs;
        if(rs == 0 && i == length - 1) {
            // don't push trailing null ('\0')
        } else {
            tu.t.push_back(rs);
        }
    }
    for(size_t i = 0; i < tu.t.size(); ++i) {
        // check if NULL is embedded in the string space.
        // If there is, then the string space may represent
        // a string array. Will need to investigate and
        // code appropriately.
        // For now just debug assert.
        assert(tu.t[i] != L'\0');
    }
    return *this;
}



END_OCTAVARIUM_NS
