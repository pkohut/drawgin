/****************************************************************************
**
** This file is part of DrawGin library. A C++ framework to read and
** write .dwg files formats.
**
** Copyright (C) 2011, 2012, 2013 Paul Kohut.
** All rights reserved.
** Author: Paul Kohut (pkohut2@gmail.com)
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License as published by the Free Software Foundation; either
** version 3 of the License, or (at your option) any later version.
**
** This library is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
** Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public
** License along with this library; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
**
** DrawGin project hosted at: http://code.google.com/p/drawgin/
**
** Authors:
**      pk          Paul Kohut <pkohut2@gmail.com>
**
****************************************************************************/

#ifndef OcDfHeaderVars_h__
#define OcDfHeaderVars_h__
#include "templates/accessors.h"

BEGIN_OCTAVARIUM_NS
class OcDbDatabaseHeaderImpl;

//OcApp::ErrorStatus DecodeOcDbDatabaseHeader(DwgInArchive& in, OcDbDatabaseHeaderImpl * pHdr);

//class OcDbObjectId;
//
class OcDfDatabaseHeaderVars
{
public:
    OcDfDatabaseHeaderVars(OcDbDatabaseHeaderImpl * hdr);
    virtual ~OcDfDatabaseHeaderVars(void);

private:
    OcApp::ErrorStatus DecodeData(DwgInArchive& in);
    friend DwgInArchive& operator>>(DwgInArchive& in,
                                    OcDfDatabaseHeaderVars & dwgVars);
    OcDbDatabaseHeaderImpl * m_pHdr;
};
    //
//public: // header variables
//    /*********************************************************************
//     * As this class is to be reusable for all drawing versions, the
//     * listed order of the variables below is not necssarily in the
//     * sequence found in the drawing file. See the decoder section for
//     * the proper loading and saving sequence and file storage data types.
//     *
//     * Some of the declared variables are a different size on disk
//     * depending on the drawing file being loaded or saved. The larger
//     * data size will always be declared in this file, with the decoder
//     * or encoder being responsible for serializing the proper data
//     * size.
//     *********************************************************************/
//    //
//    // common
//    /*-------------------- Common --------------------*/
//    
//    accessors<double> unknown1;
//    accessors<double> unknown2;
//    accessors<double> unknown3;
//    accessors<double> unknown4;
//    accessors<std::wstring> unknown5;
//    accessors<std::wstring> unknown6;
//    accessors<std::wstring> unknown7;
//    accessors<std::wstring> unknown8;
//    accessors<int32_t> unknown9;
//    accessors<int32_t> unknown10;
//    // R13 - R14
//    /*------------------- R13 - R14 ------------------*/
//    
//    accessors<int16_t> unknown11;
//    // Pre-2004
//    /*-------------------- Pre-2004 ------------------*/
//    accessors<OcDbHardOwnershipId> currentVpId;
//
//
//    // common
//    /*-------------------- Common --------------------*/
//    accessors<bool> dimaso;
//    accessors<bool> dimsho;
//    // R13 - R14
//    /*------------------- R13 - R14 ------------------*/
//    accessors<bool> dimsav;
//    // common
//    /*-------------------- Common --------------------*/    
//    accessors<bool> plinegen;
//    accessors<bool> orthomode;
//    accessors<bool> regenmode;
//    accessors<bool> fillmode;
//    accessors<bool> qtextmode;
//    accessors<bool> psltscale;
//    accessors<bool> limcheck;
//    // R13 - R14
//    /*------------------- R13 - R14 ------------------*/
//    accessors<bool> blipmode;
//
//    // R2004+
//    /*-------------------- R2004+ --------------------*/
//    accessors<bool> undocumented;
//
//    // common
//    /*-------------------- Common --------------------*/    
//    accessors<bool> usertimer;
//    accessors<bool> skpoly;
//    accessors<bool> angdir;
//    accessors<bool> splframe;
//    // R13 - R14
//    /*------------------- R13 - R14 ------------------*/
//    accessors<bool> attreq;
//    accessors<bool> attdia;
//
//    // common
//    /*-------------------- Common --------------------*/    
//    accessors<bool> mirrtext;
//    accessors<bool> worldview;
//
//    // R13 - R14
//    /*------------------- R13 - R14 ------------------*/
//    accessors<bool> wireframe;
//
//    // common
//    /*-------------------- Common --------------------*/    
//    accessors<bool> tilemode;
//    accessors<bool> plimcheck;
//    accessors<bool> visretain;
//
//    // R13 - R14
//    /*------------------- R13 - R14 ------------------*/
//    accessors<bool> delobj;
//
//    // common
//    /*-------------------- Common --------------------*/    
//    accessors<bool> dispsilh;
//    accessors<bool> pellipse;
//    accessors<int16_t> saveimages; // proxygraphics R14 - R2000)
//
//    // R13 - R14
//    /*------------------- R13 - R14 ------------------*/
//    accessors<int16_t> dragmode;
//
//    //common
//    /*-------------------- Common --------------------*/    
//    accessors<int16_t> treedepth;
//    accessors<int16_t> lunits;
//    accessors<int16_t> luprec;
//    accessors<int16_t> aunits;
//    accessors<int16_t> auprec;
//
//    // R13 - R14
//    /*------------------- R13 - R14 ------------------*/
//    accessors<int16_t> osmode;
//
//    // common
//    /*-------------------- Common --------------------*/    
//    accessors<int16_t> attmode;
//
//    // R13 - R14
//    /*------------------- R13 - R14 ------------------*/
//    accessors<int16_t> coords;
//
//    // common
//    /*-------------------- Common --------------------*/    
//    accessors<int16_t> pdmode;
//
//    // R13 - R14
//    /*------------------- R13 - R14 ------------------*/
//    accessors<int16_t> pickstyle;
//
//    // R2004+
//    /*-------------------- R2004+ --------------------*/
//    accessors<int32_t> unknown12;
//    accessors<int32_t> unknown13;
//    accessors<int32_t> unknown14;
//
//    // common
//    /*-------------------- Common --------------------*/    
//    accessors<int16_t> useri1;
//    accessors<int16_t> useri2;
//    accessors<int16_t> useri3;
//    accessors<int16_t> useri4;
//    accessors<int16_t> useri5;
//    accessors<int16_t> splinesegs;
//    accessors<int16_t> surfu;
//    accessors<int16_t> surfv;
//    accessors<int16_t> surftype;
//    accessors<int16_t> surftab1;
//    accessors<int16_t> surftab2;
//    accessors<int16_t> splinetype;
//    accessors<int16_t> shadedge;
//    accessors<int16_t> shadedif;
//    accessors<int16_t> unitmode;
//    accessors<int16_t> maxactvp;
//    accessors<int16_t> isolines;
//    accessors<int16_t> cmljust;
//    accessors<int16_t> textqlty;
//    accessors<double> ltscale;
//    accessors<double> textsize;
//    accessors<double> tracewid;
//    accessors<double> sketchinc;
//    accessors<double> filletrad;
//    accessors<double> thickness;
//    accessors<double> angbase;
//    accessors<double> pdsize;
//    accessors<double> plinewid;
//    accessors<double> userr1;
//    accessors<double> userr2;
//    accessors<double> userr3;
//    accessors<double> userr4;
//    accessors<double> userr5;
//
//    accessors<double> chamfera;
//    accessors<double> chamferb;
//    accessors<double> chamferc;
//    accessors<double> chamferd;
//    accessors<double> facetres;
//    accessors<double> cmlscale;
//    accessors<double> celtscale;
//    accessors<std::wstring> menuname;
//    accessors<int32_t> tdcreate_day;
//    accessors<int32_t> tdcreate_ms;
//    accessors<int32_t> tdupdate_day;
//    accessors<int32_t> tdupdate_ms;
//
//    // R2004+
//    /*-------------------- R2004+ --------------------*/
//    accessors<int32_t> unknown15;
//    accessors<int32_t> unknown16;
//    accessors<int32_t> unknown17;
//
//    // common
//     /*-------------------- Common --------------------*/
//    accessors<int32_t> tdindwg_days;
//    accessors<int32_t> tdindwg_ms;
//    accessors<int32_t> tdusrtimer_days;
//    accessors<int32_t> tdusrtimer_ms;
//    accessors<bitcode::CMC> cecolor;
//    accessors<OcDbObjectId> handseed;
//    accessors<OcDbObjectId> clayer;
//    accessors<OcDbObjectId> textstyle;
//    accessors<OcDbObjectId> celtype;
//
//    // R2007+
//    /*-------------------- R2007+ --------------------*/
//    accessors<OcDbObjectId> cmaterial;
//
//    // common
//     /*-------------------- Common --------------------*/
//    accessors<OcDbObjectId> dimstyle;
//    accessors<OcDbObjectId> cmlstyle;
//
//    // R2000+
//    /*-------------------- R2000+ --------------------*/
//    accessors<double> psvpscale;
//
//    // common
//     /*-------------------- Common --------------------*/
////    accessors<double> insbase[3];
//    accessors<OcGePoint3D> pinsbase;
////    accessors<double> extmin[3];
//    accessors<OcGePoint3D> pextmin;
////    accessors<double> extmax[3];
//    accessors<OcGePoint3D> pextmax;
////    accessors<double> limmin[2];
//    accessors<OcGePoint2D> plimmin;
////    accessors<double> limmax[2];
//    accessors<OcGePoint2D> plimmax;
//
//    accessors<double> pelevation;
////   accessors<double> ucsorg[3];
//    accessors<OcGePoint3D> pucsorg;
////    accessors<double> ucsxdir[3];
//    accessors<OcGePoint3D> pucsxdir;
////    accessors<double> ucsydir[3];
//    accessors<OcGePoint3D> pucsydir;
//    accessors<OcDbObjectId> pucsname;
//
//
//    // R2000+
//    /*-------------------- R2000+ --------------------*/
//    accessors<OcDbObjectId> pucsbase;
//    accessors<int16_t> pucsorthoview;
//    accessors<OcDbObjectId> pucsorthoref;
//    accessors<OcGePoint3D> pucsorgtop;
//    accessors<OcGePoint3D> pucsorgbottom;
//    accessors<OcGePoint3D> pucsorgleft;
//    accessors<OcGePoint3D> pucsorgright;
//    accessors<OcGePoint3D> pucsorgfront;
//    accessors<OcGePoint3D> pucsorgback;
//
//    // common
//     /*-------------------- Common --------------------*/
//    //    accessors<double> insbase[3];
//    accessors<OcGePoint3D> insbase;
//    //    accessors<double> extmin[3];
//    accessors<OcGePoint3D> extmin;
//    //    accessors<double> extmax[3];
//    accessors<OcGePoint3D> extmax;
//    //    accessors<double> limmin[2];
//    accessors<OcGePoint2D> limmin;
//    //    accessors<double> limmax[2];
//    accessors<OcGePoint2D> limmax;
//
//    accessors<double> elevation;
//    //   accessors<double> ucsorg[3];
//    accessors<OcGePoint3D> ucsorg;
//    //    accessors<double> ucsxdir[3];
//    accessors<OcGePoint3D> ucsxdir;
//    //    accessors<double> ucsydir[3];
//    accessors<OcGePoint3D> ucsydir;
//    accessors<OcDbObjectId> ucsname;
//
//    // R2000+
//    /*-------------------- R2000+ --------------------*/
//    accessors<OcDbObjectId> ucsbase;
//    accessors<int16_t> ucsorthoview;
//    accessors<OcDbObjectId> ucsorthoref;
//    accessors<OcGePoint3D> ucsorgtop;
//    accessors<OcGePoint3D> ucsorgbottom;
//    accessors<OcGePoint3D> ucsorgleft;
//    accessors<OcGePoint3D> ucsorgright;
//    accessors<OcGePoint3D> ucsorgfront;
//    accessors<OcGePoint3D> ucsorgback;
//    accessors<std::wstring> dimpost;
//    accessors<std::wstring> dimapost;
//
//    // R13 - R14
//    /*------------------- R13 - R14 ------------------*/
//    //////////////////////////////////////////////////////////////////////////
//    accessors<bool> dimtol;
//    accessors<bool> dimlim;
//    accessors<bool> dimtih;
//    accessors<bool> dimtoh;
//    accessors<bool> dimse1;
//    accessors<bool> dimse2;
//    accessors<bool> dimalt;
//    accessors<bool> dimtofl;
//    accessors<bool> dimsah;
//    accessors<bool> dimtix;
//    accessors<bool> dimsoxd;
//
//    accessors<int16_t> dimaltd; // RC in R13-R14
//    accessors<int16_t> dimzin; // RC in R13-R14
//    accessors<bool> dimsd1;
//    accessors<bool> dimsd2;
//    accessors<int16_t> dimtolj; // RC in R13-R14
//    accessors<int16_t> dimjust; // RC in R13-R14
//    accessors<byte_t> dimfit;
//    accessors<bool> dimupt;
//    accessors<int16_t> dimtzin; // RC in R13-R14
//    accessors<int16_t> dimaltz; // RC in R13-R14
//    accessors<int16_t> dimalttz; // RC in R13-R14
//    accessors<int16_t> dimtad; // RC in R13-R14
//    accessors<int16_t> dimunit;
//    accessors<int16_t> dimaunit;
//    accessors<int16_t> dimdec;
//    accessors<int16_t> dimtdec;
//    accessors<int16_t> dimaltu;
//    accessors<int16_t> dimalttd;
//    accessors<OcDbObjectId> dimtxsty;
//
//    ///////////////////////////////////////////////////////////////////////
//    ///////////////////////////////////////////////////////////////////////
//    ///////////////////////////////////////////////////////////////////////
//    ///////////////////////////////////////////////////////////////////////
//    ///////////////////////////////////////////////////////////////////////
//    ///////////////////////////////////////////////////////////////////////
//
//// common
//     /*-------------------- Common --------------------*/
//    accessors<double>          dimscale;
//    accessors<double>          dimasz;
//    accessors<double>          dimexo;
//    accessors<double>          dimdli;
//    accessors<double>          dimexe;
//    accessors<double>          dimrnd;
//    accessors<double>          dimdle;
//    accessors<double>          dimtp;
//    accessors<double>          dimtm;
//
//// R2007+
//    /*-------------------- R2007+ --------------------*/
//    accessors<double>          dimfxl;
//    accessors<double>          dimjogang;
//    accessors<int16_t>         dimtfill;
//    accessors<bitcode::CMC>    dimtfillclr;
//
//// R2000+
//    /*-------------------- R2000+ --------------------*/
////    accessors<bool>            dimtol;
////    accessors<bool>            dimlim;
////    accessors<bool>            dimtih;
////    accessors<bool>            dimtoh;
////    accessors<bool>            dimse1;
////    accessors<bool>            dimse2;
////    accessors<int16_t>         dimtad;
////    accessors<int16_t>         dimzin;
//    accessors<int16_t>         dimazin;
//
//// R2007+
//    /*-------------------- R2007+ --------------------*/
//    accessors<int16_t>         dimarcsym;
//
//// common
//     /*-------------------- Common --------------------*/
//    accessors<double>          dimtxt;
//    accessors<double>          dimcen;
//    accessors<double>          dimtsz;
//    accessors<double>          dimaltf;
//    accessors<double>          dimlfac;
//    accessors<double>          dimtvp;
//    accessors<double>          dimtfac;
//    accessors<double>          dimgap;
//
//// R13-R14
//    /*------------------- R13 - R14 ------------------*/
//    // accessors<std::wstring>    dimpost;
//    // accessors<std::wstring>    dimapost;
//    accessors<std::wstring>    dimblk;
//    accessors<std::wstring>    dimblk1;
//    accessors<std::wstring>    dimblk2;
//
//// R2000+
//    /*-------------------- R2000+ --------------------*/
//    accessors<double>          dimaltrnd;
//    // accessors<bool>            dimalt;
//    // accessors<int16_t>         dimaltd;
//    // accessors<bool>            dimtofl;
//    // accessors<bool>            dimsah;
//    // accessors<bool>            dimtix;
//    // accessors<bool>            dimsoxd;
//
//// common
//     /*-------------------- Common --------------------*/
//    accessors<bitcode::CMC>    dimclrd;
//    accessors<bitcode::CMC>    dimclre;
//    accessors<bitcode::CMC>    dimclrt;
//
//// R2000+
//    /*-------------------- R2000+ --------------------*/
//    accessors<int16_t>         dimadec;
//    // accessors<int16_t>         dimdec;
//    // accessors<int16_t>         dimtdec;
//    // accessors<int16_t>         dimaltu;
//    // accessors<int16_t>         dimalttd;
//    // accessors<int16_t>         dimaunit;
//    accessors<int16_t>         dimfrac;
//    accessors<int16_t>         dimlunit;
//    accessors<int16_t>         dimdsep;
//    accessors<int16_t>         dimtmove;
//    // accessors<int16_t>         dimjust;
//    // accessors<bool>            dimsd1;
//    // accessors<bool>            dimsd2;
//    // accessors<int16_t>         dimtolj;
//    // accessors<int16_t>         dimtzin;
//    // accessors<int16_t>         dimaltz;
//    // accessors<int16_t>         dimalttz;
//    // accessors<bool>            dimupt;
//    accessors<int16_t>         dimatfit;
//
//// R2007+
//    /*-------------------- R2007+ --------------------*/
//    accessors<bool>            dimfxlon;
//
//// R2000+
//    /*-------------------- R2000+ --------------------*/
//    // accessors<OcDbObjectId>    dimtxtsty;
//    accessors<OcDbObjectId>    dimldrblk;
//    accessors<OcDbObjectId>    dimblkId;
//    accessors<OcDbObjectId>    dimblk1Id;
//    accessors<OcDbObjectId>    dimblk2Id;
//
//// R2007+
//    /*-------------------- R2007+ --------------------*/
//    accessors<OcDbObjectId>    dimltype;
//    accessors<OcDbObjectId>    dimltex1;
//    accessors<OcDbObjectId>    dimltex2;
//
//// R2000+
//    /*-------------------- R2000+ --------------------*/
//    accessors<int16_t>         dimlwd;
//    accessors<int16_t>         dimlwe;
//
//// common
//     /*-------------------- Common --------------------*/
//    accessors<OcDbObjectId>    blockCtrlId;    // CONTROL OBJECT
//    accessors<OcDbObjectId>    layerCtrlId;    // CONTROL OBJECT
//    accessors<OcDbObjectId>    styleCtrlId;    // CONTROL OBJECT
//    accessors<OcDbObjectId>    linetypeCtrlId; // CONTROL OBJECT
//    accessors<OcDbObjectId>    viewCtrlId;     // CONTROL OBJECT
//    accessors<OcDbObjectId>    ucsCtrlId;      // CONTROL OBJECT
//    accessors<OcDbObjectId>    vportCtrlId;    // CONTROL OBJECT
//    accessors<OcDbObjectId>    appidCtrlId;    // CONTROL OBJECT
//    accessors<OcDbObjectId>    dimstyleCtrlId; // CONTROL OBJECT
//
//// R13-R15
//    /*------------------- R13 - R15 ------------------*/
//    accessors<OcDbObjectId>    viewport; // ENTITY HEADER CONTROL OBJECT
//
//// common
//     /*-------------------- Common --------------------*/
//    accessors<OcDbObjectId>    dictionaryGroupId;      // (ACAD_GROUP)
//    accessors<OcDbObjectId>    dictionaryMLineStyleId; // (ACAD_MLINESTYLE)
//    accessors<OcDbObjectId>    dictionaryNamedObjsId;   // (NAMED OBJECTS)
//
//// R2000+
//    /*-------------------- R2000+ --------------------*/
//    accessors<int16_t>         tstackalign;
//    accessors<int16_t>         tstacksize;
//    accessors<std::wstring>    hyperlinkbase;
//    accessors<std::wstring>    stylesheet;
//    accessors<OcDbObjectId>    dictionaryLayoutsId;   // (LAYOUTS)
//    accessors<OcDbObjectId>    dictionaryPlotSettingsId;   // (PLOTSETTINGS)
//    accessors<OcDbObjectId>    dictionaryPlotStylesId;   // (PLOTSTYLES)
//
//// R2004+
//    /*-------------------- R2004+ --------------------*/
//    accessors<OcDbObjectId>    dictionaryMaterialsId;   // (MATERIALS)
//    accessors<OcDbObjectId>    dictionaryColorsId;   // (COLORS)
//
//// R2007+
//    /*-------------------- R2007+ --------------------*/
//    accessors<OcDbObjectId>    dictionaryVisualStyleId;   // (VISUALSTYLE)
//
//// R2000+
//    /*-------------------- R2000+ --------------------*/
//    accessors<int32_t>         flags;
////                      CELWEIGHT       Flags & 0x001F
////                      ENDCAPS         Flags & 0x0060
////                      JOINSTYLE       Flags & 0x0180
////                      LWDISPLAY       !(Flags & 0x0200)
////                      XEDIT           !(Flags & 0x0400)
////                      EXTNAMES        Flags & 0x0800
////                      PSTYLEMODE      Flags & 0x2000
////                      OLESTARTUP      Flags & 0x4000
//    accessors<int16_t>         insunits;
//    accessors<int16_t>         cepsntype;
//    accessors<OcDbObjectId>    cpsnid;       // (present only if CEPSNTYPE == 3)
//    accessors<std::wstring>    fingerprintguid;
//    accessors<std::wstring>    versionguid;
//
//// R2004+
//    /*-------------------- R2004+ --------------------*/
//    accessors<byte_t>          sortents;
//    accessors<byte_t>          indexctl;
//    accessors<byte_t>          hidetext;
//    accessors<byte_t>          xclipframe;
//    accessors<byte_t>          dimassoc;
//    accessors<byte_t>          halogap;
//    accessors<int16_t>         obscuredcolor;
//    accessors<int16_t>         intersectioncolor;
//    accessors<byte_t>          obscuredltype;
//    accessors<byte_t>          intersectiondisplay;
//    accessors<std::wstring>    projectname;
//
//// common
//     /*-------------------- Common --------------------*/
//    accessors<OcDbObjectId>    block_recordPsId;  // (*PAPER_SPACE)
//    accessors<OcDbObjectId>    block_recordMsId;  // (*MODEL_SPACE)
//    accessors<OcDbObjectId>    ltypeByLayerId;         // (BYLAYER)
//    accessors<OcDbObjectId>    ltypeByBlockId;         // (BYBLOCK)
//    accessors<OcDbObjectId>    ltypeContinuousId;         // (CONTINUOUS)
//
//// R2007+
//    /*-------------------- R2007+ --------------------*/
//    accessors<bool>            cameradisplay;
//    accessors<int32_t>         unknown21;
//    accessors<int32_t>         unknown22;
//    accessors<double>          unknown23;
//    accessors<double>          stepspersec;
//    accessors<double>          stepsize;
//    accessors<double>          dwfprec3d;
//    accessors<double>          lenslength;
//    accessors<double>          cameraheight;
//    accessors<byte_t>          solidhist;
//    accessors<byte_t>          showhist;
//    accessors<double>          psolwidth;
//    accessors<double>          psolheight;
//    accessors<double>          loftang1;
//    accessors<double>          loftang2;
//    accessors<double>          loftmag1;
//    accessors<double>          logtmag2;
//    accessors<int16_t>         loftparam;
//    accessors<byte_t>          loftnormals;
//    accessors<double>          latitude;
//    accessors<double>          longitude;
//    accessors<double>          northdirection;
//    accessors<int32_t>         timezone;
//    accessors<byte_t>          lightglyphdisplay;
//    accessors<byte_t>          tilemodelightsynch;
//    accessors<byte_t>          dwfframe;
//    accessors<byte_t>          dgnframe;
//    accessors<bool>            unknown47;
//    accessors<bitcode::CMC>    interferecolor;
//    accessors<OcDbObjectId>    interfereobjvsId;
//    accessors<OcDbObjectId>    interferevpvsId;
//    accessors<OcDbObjectId>    dragvsId;
//    accessors<byte_t>          cshadow;
//    accessors<double>          unknown53;
//
//// R14+
//    /*---------------------- R14+ ---------------------*/
//    accessors<int16_t>         unknown54;  // short(type 5 / 6 only)  these do not seem to be required,
//    accessors<int16_t>         unknown55;  // short(type 5 / 6 only)  even for type 5.
//    accessors<int16_t>         unknown56;  // short(type 5 / 6 only)
//    accessors<int16_t>         unknown57;  // short(type 5 / 6 only)
//
//// common
//     /*-------------------- Common --------------------*/
//    accessors<uint16_t>        crc;      // for the data section, starting after the
//    // sentinel. Use 0xC0C1 for the initial value.
//
//
//
//};

END_OCTAVARIUM_NS


#endif // OcDfHeaderVars_h__

