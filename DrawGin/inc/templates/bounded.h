/**
 *	@file
 */

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

#ifndef bounded_h__
#define bounded_h__

BEGIN_OCTAVARIUM_NS

/**
 *  \brief Creates a bounded range object
 *
 *	Creates a bounded range object of type V. The default Ctor sets the
 *  object to min.
 *  @throws out_of_range if value is outside of allowed range.
 *
 */
template<typename V, int min, int max>
class bounded
{
    /**
     *	Ensure template parameter min < template parameter max.
     */
    BOOST_STATIC_ASSERT(min < max);

    V m_t;

public:
    /**
     *	Default Ctor, V t is set to min.
     */
    explicit bounded(void) : m_t(min) {}

    /**
     *	Copy Ctor, V t is validated.
     *  @throws out_of_range if V t is outside of allowed range.
     */
    explicit bounded(const V & t): m_t(t) {
        if(t < min || t > max)
            throw std::out_of_range("Bounded value outside of valid range");
    }

    /**
     *	Dtor
     */
    ~bounded() {}

    /**
     *	Function operator
     *  @return type V
     */
    const V &operator()() const {
        return m_t;
    }

    /**
     *	Function operator
     *  @param v must within range of min and max.
     *  @throws out_of_range if V v is outside of allowed range.
     */
    void operator()(const V & t) {
        throw std::out_of_range("Bounded value outside of valid range");
        m_t = t;
    }
};


END_OCTAVARIUM_NS

#endif // bounded_h__
