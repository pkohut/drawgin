#include <boost/foreach.hpp>

#include "OcCommon.h"
#include "OcError.h"
#include "OcDbDwgVersion.h"
#include "OcTypes.h"
#include "OcDbObjectId.h"
#include "OcDbDwgVersion.h"

#include "../OcBs/OcBsStreamIn.h"
#include "OcDbDwgObjectMap.h"

BEGIN_OCTAVARIUM_NS
using namespace std;

#define ASSERT_ARCHIVE_NOT_LOADING assert(ar.ArchiveFlag() \
    == DwgInArchive::LOADING)

OcDbDwgObjectMap::OcDbDwgObjectMap(int32_t objMapFilePos, int32_t objMapSize)
: m_objMapFilePos(objMapFilePos), m_objMapSize(objMapSize)
{
}

OcDbDwgObjectMap::~OcDbDwgObjectMap(void)
{
}



OcApp::ErrorStatus OcDbDwgObjectMap::DecodeData(DwgInArchive& ar)
{
    ASSERT_ARCHIVE_NOT_LOADING;
    VLOG(3) << "DecodeObjectMap entered";
    // do some sanity checks before trying to read the object map
    if(m_objMapFilePos == 0) {
        LOG(ERROR) << "Invalid file offset position for Object Map";
        return OcApp::eInvalidObjectMapOffset;
    }

    // set file position to the Object Map offset
    ar.Seek(m_objMapFilePos);
    if(ar.Error() != OcApp::eOk) {
        LOG(ERROR) << "Error setting file position";
        return ar.Error();
    }

    int32_t lastHandle = 0, lastOffset = 0;

    // Until I've seen some files which have more than one
    // section, not really sure how the data is coded.
    // Does lastOffset need to be reset to 0 for each section?
    int sectionNumber = 0;

    // section size and crc are values stored in big endian format
    // on disk.
    while(1) {
        // reset calced crc to 0xc0c1 for each section
        ar.SetCalcedCRC(0xc0c1);
        // read section size and convert to little endian format.
        int16_t sectionSize;
        ar >> (bitcode::RC&)sectionSize;
        sectionSize <<= 8;
        ar >> (bitcode::RC&)sectionSize;
        VLOG(4) << "Section size = " << sectionSize;

        // only 2 bytes for this section, they are the final crc
        // which is calced below outside of this loop.
        if(sectionSize <= 2) {
            break;
        }

        // Until I've seen some files which have more than one
        // section, not really sure how the data is coded.
        // Does lastOffset need to be reset to 0 for each section?
        CHECK(sectionNumber == 0) << "Check file offsets for object addresses";

        // endSection includes the 2 byte crc for this section, so
        // exclude 2 bytes when doing the loop.
        int32_t endSection = ar.FilePosition() + sectionSize;
        while(ar.FilePosition() < endSection - 2) {
            int32_t offsetLastH;
            int32_t offsetLoc;
            BS_ARCHIVE(bitcode::MC,  ar, offsetLastH, "offset last handle");
            BS_ARCHIVE(bitcode::MC , ar, offsetLoc,   "offset loc");
            lastHandle += offsetLastH;
            lastOffset += offsetLoc;
            m_objMapItems.push_back(MapItem(lastHandle, lastOffset));
        }
        // calc section crc
        uint16_t crc, calcedCrc = ar.CalcedCRC(true);
        ar.ReadCRC(crc);
        if(crc != calcedCrc) {
            LOG(ERROR) << "Data section CRC for Object Map is incorrect";
            return OcApp::eInvalidCRCInObjectMap;
        }
        sectionNumber++;
    }
    // calc final crc
    uint16_t crc, calcedCrc = ar.CalcedCRC(true);
    ar.ReadCRC(crc);
    if(crc != calcedCrc) {
        LOG(ERROR) << "CRC for Object Map is incorrect";
        return OcApp::eInvalidCRCInObjectMap;
    }

    VLOG(3) << "Successfully decoded Object map";
    return OcApp::eOk;
}

OcApp::ErrorStatus OcDbDwgObjectMap::DecodeObjects(DwgInArchive& ar, OcDbDatabase *& pDb)
{
    BOOST_FOREACH(const MapItem &  item, m_objMapItems) {
        ar.Seek(item.second);
        if(ar.Error() != OcApp::eOk)
            return ar.Error();

        const DWG_VERSION dwgVersion = ar.Version();
        uint32_t objSize = 0;
        uint32_t objSizeBits = 0;
        uint16_t objType = 0;
        OcDbObjectId objId;
        uint16_t extendedObjSize = 0;
        bool hasGraphicsImage;


        BS_ARCHIVE(bitcode::MS, ar, objSize, "Object size = ");
        BS_ARCHIVE(bitcode::BS, ar, objType, "Object type = ");
        if(dwgVersion >= R2000) {
            BS_ARCHIVE(bitcode::RL, ar, objSizeBits, "Object size in bits = ");
        }
        BS_ARCHIVE(OcDbObjectId, ar, objId, "Object handle = ");
        BS_ARCHIVE(bitcode::BS, ar, extendedObjSize, "extended object data size = ");
        if(extendedObjSize) {

        }
        //BS_ARCHIVE(bitcode::B, ar, hasGraphicsImage, "has graphics data = ");
        //if(hasGraphicsImage) {
        //    uint32_t imageDataSize;
        //    BS_ARCHIVE(bitcode::RL, ar, imageDataSize, "graphics data size = ");
        //    // read the graphics data
        //}

        if(dwgVersion == R13 || dwgVersion == R14) {
            BS_ARCHIVE(bitcode::RL, ar, objSizeBits, "Object size in bits = ");
        }

        // read object data

        if(dwgVersion >= R2007) {
            // read string data
            // get string stream data
        }




    }
    return OcApp::eOk;
}

DwgInArchive& operator>>(DwgInArchive& ar, OcDbDwgObjectMap & hdr)
{
    ASSERT_ARCHIVE_NOT_LOADING;
    ar.SetError(hdr.DecodeData(ar));
    return ar;
}

END_OCTAVARIUM_NS