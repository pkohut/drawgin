#include "OcCommon.h"
#include "OcError.h"
#include "OcDfDwgVersion.h"
#include "OcTypes.h"
#include "OcDbObjectId.h"
#include "OcDbObject.h"

#include "../OcBs/OcBsStreamIn.h"
#include "../OcBs/DwgInArchive.h"
#include "../OcBs/OcBsDwgSentinels.h"
#include "OcDfDwgDataSection.h"

BEGIN_OCTAVARIUM_NS

OcDfDwgDataSection::OcDfDwgDataSection(int32_t dataSectionFilePosition, int32_t dataSectionSize)
: m_dataSectionFilePosition(dataSectionFilePosition), m_dataSectionSize(dataSectionSize)
{
}

OcDfDwgDataSection::~OcDfDwgDataSection(void)
{
}

OcApp::ErrorStatus OcDfDwgDataSection::DecodeData( DwgInArchive& ar )
{
    ASSERT_ARCHIVE_NOT_LOADING(ar);
    VLOG(4) << "OcDfDwgDataSection DecodeData entered";
    // do some sanity checks before trying to read the object map
    if(m_dataSectionFilePosition == 0) {
        LOG(ERROR) << "Invalid file offset position for Data Section";
        return OcApp::eInvalidDataSectionOffset;
    }

    // set file position to the Object Map offset
    ar.Seek(m_dataSectionFilePosition);
    if(ar.Error() != OcApp::eOk) {
        LOG(ERROR) << "Error setting file position";
        return ar.Error();
    }


    int16_t templateStringLength;
    BS_ARCHIVE(bitcode::BS, ar, templateStringLength, "template string length");
    if(templateStringLength)
    {
        // Spec section 20, Data section: AcDbTemplate
        // Encoded string bytes of the template description, use the
        // drawing's code page to encode the bytes);        
        ar.ReadRC(m_encodedString, templateStringLength);
        VLOG(4) << "template string (needs codepage encoding)" << m_encodedString;
    }

    uint16_t measurement;
    BS_ARCHIVE(bitcode::BS, ar, measurement, "measurement system variable");

    return OcApp::eOk;
}

std::string OcDfDwgDataSection::TemplateDescription( void )
{
    return m_encodedString;
}

uint16_t OcDfDwgDataSection::Measurement( void )
{
    return m_measurment;
}


DwgInArchive& operator>>( DwgInArchive& ar, OcDfDwgDataSection & dataSection )
{
    ASSERT_ARCHIVE_NOT_LOADING(ar);
    ar.SetError(dataSection.DecodeData(ar));
    return ar;
}

END_OCTAVARIUM_NS