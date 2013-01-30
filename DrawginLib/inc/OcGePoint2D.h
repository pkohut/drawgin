/**
 *	@file
 *  @brief Defines OcGePoint2D class
 *
 *  Defines the OcGePoint2D class.
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

// Note: OcGePoint2D is a stub class and not fully implemented. It is
// provided to support reading the drawing header section in OcBsDatabaseHeaderVars.


BEGIN_OCTAVARIUM_NS

class DRAWGIN_API OcGePoint2D
{
    //DISABLE_COPY(OcGePoint2D);
public:
    OcGePoint2D();
    OcGePoint2D(double xx, double yy);

    /** Returns the value of the x coordinate of the 2d point. */
    double X(void) const
    {
        return x;
    }

    /** Returns a reference to the x coordinate of the 2d point. */
    double & X(void)
    {
        return x;
    }

    /**	Returns the value of the y coordinate of the 2d point. */
    double Y(void) const
    {
        return y;
    }

    /**	Returns a reference to the y coordinate of the 2d point. */
    double & Y(void)
    {
        return y;
    }

    friend std::ostream& operator <<(std::ostream& out, const OcGePoint2D & pt);


private:
    double x, y;
};

END_OCTAVARIUM_NS