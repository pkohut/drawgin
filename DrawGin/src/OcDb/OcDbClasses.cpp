#include "stdafx.h"

#include "OcCommon.h"
#include "OcTypes.h"
#include "OcError.h"
#include "OcDbDwgVersion.h"
#include "OcDbObjectId.h"

#include "../OcBs/OcBsStreamIn.h"
#include "../OcBs/DwgInArchive.h"
#include "OcDbClass.h"
#include "OcDbClasses.h"
#include "../OcBs/OcBsDwgSentinels.h"

BEGIN_OCTAVARIUM_NS
using namespace std;

#define ASSERT_ARCHIVE_NOT_LOADING \
    assert(in.ArchiveFlag() == DwgInArchive::LOADING)

OcDbClasses::OcDbClasses()
{
    VLOG(3) << "Constructor entered";
}

OcDbClasses::~OcDbClasses()
{
    VLOG(3) << "Destructor entered";
}

OcApp::ErrorStatus OcDbClasses::DecodeData(DwgInArchive& in)
{
    VLOG(3) << "DecodeData entered";
    ASSERT_ARCHIVE_NOT_LOADING;

    // match dwg header variables start sentinel
    bitcode::RC sentinelData[16];
    in.ReadRC(sentinelData, 16);
    if(!CompareSentinels(sentinelClassesSectionStart, sentinelData)) {
        return OcApp::eInvalidImageDataSentinel;
    }

    int size;
    BS_ARCHIVE(bitcode::RL, in, size, "classes section size");
    int16_t nClasses;
    byte_t val1, val2;
    bool bVal;

    BS_ARCHIVE(bitcode::BS, in, nClasses, "Maximum class number");
    BS_ARCHIVE(bitcode::RC, in, val1, "val1");
    BS_ARCHIVE(bitcode::RC, in, val2, "val2");
    BS_ARCHIVE(bitcode::B,  in, bVal, "bVal");

    int16_t classNum;
    int16_t version;
    wstring appName;
    wstring cppClassName;
    wstring classDxfName;
    bool wasAZombie;
    int16_t itemClassId;
    int32_t numObjects;
    int16_t dwgVersion;
    int16_t maintVersion;
    int32_t unknown1;
    int32_t unknown2;

    BS_ARCHIVE(bitcode::BS, in, classNum, "class number");
    BS_ARCHIVE(bitcode::BS, in, version, "version");
    BS_ARCHIVE(bitcode::TV, in, appName, "app name");
    BS_ARCHIVE(bitcode::TV, in, cppClassName, "cpp ClassName");
    BS_ARCHIVE(bitcode::TV, in, classDxfName, "class DXF name");
    BS_ARCHIVE(bitcode::B,  in, wasAZombie, "was a zombie");
    BS_ARCHIVE(bitcode::BS, in, itemClassId, "item class id");
    BS_ARCHIVE(bitcode::BL, in, numObjects, "number of objects");
    BS_ARCHIVE(bitcode::BS, in, dwgVersion, "dwg version");
    BS_ARCHIVE(bitcode::BS, in, maintVersion, "maintenance version");
    BS_ARCHIVE(bitcode::BL, in, unknown1, "unknown1");
    BS_ARCHIVE(bitcode::BL, in, unknown2, "unknown2");



    return OcApp::eNotImplemented;
}

DwgInArchive& operator>>(DwgInArchive& in, OcDbClasses & dwgClasses)
{
    ASSERT_ARCHIVE_NOT_LOADING;
    in.SetError(dwgClasses.DecodeData(in));
    return in;
}

END_OCTAVARIUM_NS