#include "stdafx.h"

#include "OcCommon.h"
#include "OcTypes.h"
#include "OcError.h"
#include "OcDbDwgVersion.h"
#include "OcDbObjectId.h"
#include "OcDbClass.h"

BEGIN_OCTAVARIUM_NS

OcDbClass::OcDbClass()
{
    VLOG(3) << "Constructor entered";
}

OcDbClass::~OcDbClass()
{
    VLOG(3) << "Destructor entered";
}

END_OCTAVARIUM_NS