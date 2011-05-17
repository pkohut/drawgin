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

#ifndef OcBsDwgCrc_h__
#define OcBsDwgCrc_h__

BEGIN_OCTAVARIUM_NS
uint16_t crc8(uint16_t dx, const char * p, long n);
//uint16_t crc8(uint16_t dx, const OcDbObjectId & objId);






//BOOST_STRONG_TYPEDEF(byte_t, B);
//BOOST_STRONG_TYPEDEF(byte_t, BB);
//BOOST_STRONG_TYPEDEF(byte_t, BBBB);
//BOOST_STRONG_TYPEDEF(int16_t, BS);
//BOOST_STRONG_TYPEDEF(int32_t, BL);
//BOOST_STRONG_TYPEDEF(double, BD);
//BOOST_STRONG_TYPEDEF(BC2D, BD2);
//BOOST_STRONG_TYPEDEF(BC3D, BD3);
//
//BOOST_STRONG_TYPEDEF(byte_t, RC);
//BOOST_STRONG_TYPEDEF(int16_t, RS);
//BOOST_STRONG_TYPEDEF(int32_t, RL);
//BOOST_STRONG_TYPEDEF(double, RD);
//BOOST_STRONG_TYPEDEF(BC2D, RD2);
//BOOST_STRONG_TYPEDEF(BC3D, RD3);
//
//BOOST_STRONG_TYPEDEF(int32_t, MC);
//BOOST_STRONG_TYPEDEF(int32_t, MS);
//
//BOOST_STRONG_TYPEDEF(BC3D, BE);
//BOOST_STRONG_TYPEDEF(double, DD);
//BOOST_STRONG_TYPEDEF(double, BT);
//
//BOOST_STRONG_TYPEDEF(BCCMC, CMC);
//BOOST_STRONG_TYPEDEF(std::wstring, TV);
//BOOST_STRONG_TYPEDEF(std::wstring, T);




template<typename T>
inline uint16_t CalcCRC(uint16_t & crc, T & t)
{
    return crc8(crc, (const char *)&t, sizeof(T));
}

template<>
inline uint16_t CalcCRC(uint16_t & crc, bitcode::BD2 & t)
{
    crc = crc8(crc, (const char *)&t.t.x, sizeof(t.t.x));
    crc = crc8(crc, (const char *)&t.t.y, sizeof(t.t.y));
    return crc;
}

template<>
inline uint16_t CalcCRC(uint16_t & crc, bitcode::BD3 & t)
{
    crc = crc8(crc, (const char *)&t.t.x, sizeof(t.t.x));
    crc = crc8(crc, (const char *)&t.t.y, sizeof(t.t.y));
    crc = crc8(crc, (const char *)&t.t.z, sizeof(t.t.z));
    return crc;
}

template<>
inline uint16_t CalcCRC(uint16_t & crc, bitcode::RD2 & t)
{
    crc = crc8(crc, (const char *)&t.t.x, sizeof(t.t.x));
    crc = crc8(crc, (const char *)&t.t.y, sizeof(t.t.y));
    return crc;
}

template<>
inline uint16_t CalcCRC(uint16_t & crc, bitcode::RD3 & t)
{
    crc = crc8(crc, (const char *)&t.t.x, sizeof(t.t.x));
    crc = crc8(crc, (const char *)&t.t.y, sizeof(t.t.y));
    crc = crc8(crc, (const char *)&t.t.z, sizeof(t.t.z));
    return crc;
}

template<>
inline uint16_t CalcCRC(uint16_t & crc, bitcode::CMC & t)
{
    crc = crc8(crc, (const char *)&t.t.index, sizeof(t.t.index));
    return crc;
}

template<>
inline uint16_t CalcCRC(uint16_t & crc, bitcode::TV & t)
{
    // Assert if this function is called.
    // This function cannot determine if TV is T or TU
    // so it should not be called directly.
    assert(0);
    return crc;
}

template<>
inline uint16_t CalcCRC(uint16_t & crc, bitcode::T & t)
{
    std::string s = WStringToString(t.t.c_str());
    return crc8(crc, (const char *) s.c_str(), s.size());
}

template<>
inline uint16_t CalcCRC(uint16_t & crc, bitcode::TU & t)
{
    LOG(ERROR) << "CalcCRC called with Unicode string, no calcs done";
    return crc;
}

template<>
inline uint16_t CalcCRC(uint16_t & crc, OcDbObjectId & t)
{
    return crc8(crc, (const char *)&t.Handle(), sizeof(t.Handle()));
}


//template<>
//inline uint16_t CalcCRC(bitcode::B & t)
//{
//    return 0;
//}
//
//template<>
//inline uint16_t CalcCRC(bitcode::RL & t)
//{
//    return crc8(0, (const char *)&t, sizeof(bitcode::RL));
//}
//
//template<>
//inline uint16_t CalcCRC(bitcode::RL & t)
//{
//    return crc8(0, (const char *)&t, sizeof(bitcode::RL));
//}

END_OCTAVARIUM_NS

#endif // OcBsDwgCrc_h__
