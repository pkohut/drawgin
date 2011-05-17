#ifndef OCDBCLASSES_H
#define OCDBCLASSES_H

BEGIN_OCTAVARIUM_NS

class OcDbClasses {

public:
	OcDbClasses();
	virtual ~OcDbClasses();

private:
    OcApp::ErrorStatus DecodeData(DwgInArchive& in);
    friend DwgInArchive& operator>>(DwgInArchive& in,
                                    OcDbClasses & dwgClasses);

    std::vector<OcDbClass> m_classes;
};

END_OCTAVARIUM_NS

#endif // OCDBCLASSES_H
