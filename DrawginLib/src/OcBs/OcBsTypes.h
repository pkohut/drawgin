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



#ifndef OcBsTypes_h__
#define OcBsTypes_h__

#include <boost/strong_typedef.hpp>

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
//    byte_t colorByte;
//    std::wstring name;
//    std::wstring bookName;
    BCCMC() : rgb(0), index(0), colorByte(0) {}
    std::wstring name;
    std::wstring bookName;
    int32_t rgb;
    int16_t index;
    byte_t colorByte;
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



BOOST_STRONG_TYPEDEF(byte_t, B);
BOOST_STRONG_TYPEDEF(byte_t, BB);
BOOST_STRONG_TYPEDEF(byte_t, BBBB);
BOOST_STRONG_TYPEDEF(int16_t, BS);
BOOST_STRONG_TYPEDEF(int32_t, BL);
BOOST_STRONG_TYPEDEF(double, BD);
BOOST_STRONG_TYPEDEF(BC2D, BD2);
BOOST_STRONG_TYPEDEF(BC3D, BD3);

BOOST_STRONG_TYPEDEF(byte_t, RC);
BOOST_STRONG_TYPEDEF(int16_t, RS);
BOOST_STRONG_TYPEDEF(int32_t, RL);
BOOST_STRONG_TYPEDEF(double, RD);
BOOST_STRONG_TYPEDEF(BC2D, RD2);
BOOST_STRONG_TYPEDEF(BC3D, RD3);

BOOST_STRONG_TYPEDEF(uint32_t, MC);
BOOST_STRONG_TYPEDEF(uint32_t, MS);

BOOST_STRONG_TYPEDEF(BC3D, BE);
BOOST_STRONG_TYPEDEF(double, DD);
BOOST_STRONG_TYPEDEF(double, BT);

BOOST_STRONG_TYPEDEF(BCCMC, CMC);
BOOST_STRONG_TYPEDEF(std::wstring, TV);
BOOST_STRONG_TYPEDEF(std::wstring, T);
BOOST_STRONG_TYPEDEF(std::wstring, TU);


} // bitcode

END_OCTAVARIUM_NS

#endif // OcBsTypes_h__
