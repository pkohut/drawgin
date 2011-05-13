#include "stdafx.h"
#include "OcCommon.h"
#include "OcTypes.h"
#include "OcError.h"
#include "OcGePoint3D.h"

BEGIN_OCTAVARIUM_NS

OcGePoint3D::OcGePoint3D()
    : x(0.0), y(0.0), z(0.0)
{
}

OcGePoint3D::OcGePoint3D(double xx, double yy, double zz)
    : x(xx), y(yy), z(zz)
{
}

std::ostream& operator <<(std::ostream& out, const OcGePoint3D & pt)
{
    out << "x: = " << pt.x << ", "
        << "y: = " << pt.y << ", "
        << "z: = " << pt.z;
    return out;
}


END_OCTAVARIUM_NS