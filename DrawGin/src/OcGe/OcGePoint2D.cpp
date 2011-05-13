#include "stdafx.h"
#include "OcCommon.h"
#include "OcTypes.h"
#include "OcError.h"
#include "OcGePoint2D.h"


BEGIN_OCTAVARIUM_NS

OcGePoint2D::OcGePoint2D()
    : x(0.0), y(.00)
{
}

OcGePoint2D::OcGePoint2D(double xx, double yy)
    : x(xx), y(yy)
{
}

std::ostream& operator <<(std::ostream& out, const OcGePoint2D & pt)
{
    out << "x: = " << pt.x << ", "
        << "y: = " << pt.Y();
    return out;
}



END_OCTAVARIUM_NS
