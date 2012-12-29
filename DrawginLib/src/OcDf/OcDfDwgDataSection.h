#ifndef OcDfDataSection_h__
#define OcDfDataSection_h__

BEGIN_OCTAVARIUM_NS

class OcDfDwgDataSection
{
public:
    OcDfDwgDataSection(int32_t dataSectionFilePosition, int32_t dataSectionSize);
    virtual ~OcDfDwgDataSection(void);

    std::string TemplateDescription(void);

    uint16_t Measurement(void);



private:
    friend DwgInArchive& operator>>(DwgInArchive& ar, OcDfDwgDataSection & dataSection);
    OcApp::ErrorStatus DecodeData(DwgInArchive& ar);

    int32_t m_dataSectionFilePosition, m_dataSectionSize;
    std::string m_encodedString;
    uint16_t m_measurment;
};

END_OCTAVARIUM_NS

#endif // OcDfDataSection_h__
