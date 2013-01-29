/**
 *	@file
 *  @brief Defines bit stream types
 *
 *  Defines bit stream types used to encode drawing files
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

#ifndef STRONG_TYPEDEF
#define STRONG_TYPEDEF(T, D)                                    \
struct D                                                        \
    {                                                           \
    T t;                                                        \
    explicit D(const T t_) : t(t_) {};                          \
    D(){};                                                      \
    D(const D & t_) : t(t_.t){}                                 \
    D & operator=(const D & rhs) { t = rhs.t; return *this;}    \
    D & operator=(const T & rhs) { t = rhs; return *this;}      \
    operator const T & () const {return t; }                    \
    operator T & () { return t; }                               \
    bool operator==(const D & rhs) const { return t == rhs.t; } \
    bool operator<(const D & rhs) const { return t < rhs.t; }   \
    };
#endif

BEGIN_OCTAVARIUM_NS

namespace bitcode
{

struct BC2D
{
    double x, y;
    BC2D() : x(0.0), y(0.0) {}
    BC2D(double _x, double _y) : x(_x), y(_y) {}
    void set(double _x, double _y)
    {
        x = _x;
        y = _y;
    }
    bool operator==(const BC2D & other) const
    {
        return x == other.x && y == other.y;
    }
    bool operator<(const BC2D & other) const
    {
        return x < other.x && y < other.y;
    }

    friend std::ostream& operator <<(std::ostream& out, const bitcode::BC2D& pt)
    {
        out << "index: " << pt.x << pt.y;
        return out;
    }
};

struct BC3D
{
    double x, y, z;
    BC3D() : x(0.0), y(0.0), z(0.0) {}
    BC3D(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}
    void set(double _x, double _y, double _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }
    bool operator==(const BC3D & other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }
    bool operator<(const BC3D & other) const
    {
        return x < other.x && y < other.y && z < other.z;
    }

};

struct BCCMC
{
    //    BCCMC() : index(0), rgb(0), colorByte(0) {}
    //    int16_t index;
    //    int32_t rgb;
    //    uint8_t colorByte;
    //    std::wstring name;
    //    std::wstring bookName;
    BCCMC() : rgb(0), index(0), colorByte(0) {}
    std::wstring name;
    std::wstring bookName;
    int32_t rgb;
    int16_t index;
    uint8_t colorByte;
    bool operator==(const BCCMC & other) const
    {
        return index == other.index && rgb == other.rgb &&
               colorByte == other.colorByte && name == other.name &&
               bookName == bookName;
    }
    bool operator<(const BCCMC & other) const
    {
        return index < other.index;
    }
    friend std::ostream& operator <<(std::ostream& out, const bitcode::BCCMC& cmc)
    {
        out << "index: " << cmc.index << ", "
            << "rgb: " << cmc.rgb << ", "
            << "colorByte: " << (unsigned int) cmc.colorByte << ", "
            << "colorName: " << cmc.name.c_str() << ", "
            << "colorBook: " << cmc.bookName.c_str();
        return out;
    }
};



STRONG_TYPEDEF(uint8_t, B);
STRONG_TYPEDEF(uint8_t, BB);
STRONG_TYPEDEF(uint8_t, BBBB);
STRONG_TYPEDEF(int16_t, BS);
STRONG_TYPEDEF(int32_t, BL);
STRONG_TYPEDEF(double, BD);
STRONG_TYPEDEF(BC2D, BD2);
STRONG_TYPEDEF(BC3D, BD3);

STRONG_TYPEDEF(uint8_t, RC);
STRONG_TYPEDEF(int16_t, RS);
STRONG_TYPEDEF(int32_t, RL);
STRONG_TYPEDEF(double, RD);
STRONG_TYPEDEF(BC2D, RD2);
STRONG_TYPEDEF(BC3D, RD3);

STRONG_TYPEDEF(uint32_t, MC);
STRONG_TYPEDEF(uint32_t, MS);

STRONG_TYPEDEF(BC3D, BE);
STRONG_TYPEDEF(double, DD);
STRONG_TYPEDEF(double, BT);

STRONG_TYPEDEF(BCCMC, CMC);
STRONG_TYPEDEF(std::wstring, TV);
STRONG_TYPEDEF(std::wstring, T);
STRONG_TYPEDEF(std::wstring, TU);


} // bitcode

END_OCTAVARIUM_NS