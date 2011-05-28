#ifndef OcDbDwgObjectMap_h__
#define OcDbDwgObjectMap_h__

#include "../OcBs/DwgInArchive.h"

BEGIN_OCTAVARIUM_NS
class OcDbDatabase;

class OcDbDwgObjectMap
{
public:
    OcDbDwgObjectMap(int32_t objMapFilePos, int32_t objMapSize);
    virtual ~OcDbDwgObjectMap(void);

    OcApp::ErrorStatus DecodeObjects(DwgInArchive& ar, OcDbDatabase *& pDb);

private:
    typedef std::pair<int32_t, int32_t> MapItem;
    friend DwgInArchive& operator>>(DwgInArchive& ar, OcDbDwgObjectMap & imgData);
    OcApp::ErrorStatus DecodeData(DwgInArchive& ar);

    // pair::first = handle, pair::second = fileposition
    std::vector<std::pair<int32_t, int32_t>> m_objMapItems;

    int32_t m_objMapFilePos;
    int32_t m_objMapSize;
};

END_OCTAVARIUM_NS

#endif // OcDbDwgObjectMap_h__