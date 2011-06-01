#ifndef OcRxClass_h__
#define OcRxClass_h__

BEGIN_OCTAVARIUM_NS

class OcRxObject;

class OcRxClass : public OcRxObject
{
    OC_DECLARE_CLASS(OcRxClass, OcRxObject);
public:
    OcRxClass(void);
    virtual ~OcRxClass(void);
};

END_OCTAVARIUM_NS
#endif // OcRxClass_h__
