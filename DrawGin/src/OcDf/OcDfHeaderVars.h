/****************************************************************************
**
** This file is part of DrawGin library. A C++ framework to read and
** write .dwg files formats.
**
** Copyright (C) 2011 Paul Kohut.
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

BEGIN_OCTAVARIUM_NS

class OcDbObjectId;

class OcDfHeaderVars
{
public:
    OcDfHeaderVars(void);
    virtual ~OcDfHeaderVars(void);

private:
    OcApp::ErrorStatus DecodeData(DwgInArchive& in);
    friend DwgInArchive& operator>>(DwgInArchive& in,
                                    OcDfHeaderVars & dwgVars);

private: // header variables
    /*********************************************************************
     * As this class is to be reusable for all drawing versions, the
     * listed order of the variables below is not necssarily in the
     * sequence found in the drawing file. See the decoder section for
     * the proper loading and saving sequence and file storage data types.
     *
     * Some of the declared variables are a different size on disk
     * depending on the drawing file being loaded or saved. The larger
     * data size will always be declared in this file, with the decoder
     * or encoder being responsible for serializing the proper data
     * size.
     *********************************************************************/
    //
    // common
    double m_unknown1;
    double m_unknown2;
    double m_unknown3;
    double m_unknown4;
    std::wstring m_unknown5;
    std::wstring m_unknown6;
    std::wstring m_unknown7;
    std::wstring m_unknown8;
    int32_t m_unknown9;
    int32_t m_unknown10;
    // R13 - R14
    int16_t m_unknown11;
    // Pre-2004
    OcDbHardOwnershipId m_currentVpId;


    // common
    bool m_dimaso;
    bool m_dimsho;
    // R13 - R14
    bool m_dimsav;
    // common
    bool m_plinegen;
    bool m_orthomode;
    bool m_regenmode;
    bool m_fillmode;
    bool m_qtextmode;
    bool m_psltscale;
    bool m_limcheck;
    // R13 - R14
    bool m_blipmode;

    // R2004+
    bool m_undocumented;
    // common
    bool m_usertimer;
    bool m_skpoly;
    bool m_angdir;
    bool m_splframe;
    // R13 - R14
    bool m_attreq;
    bool m_attdia;
    // common
    bool m_mirrtext;
    bool m_worldview;
    // R13 - R14
    bool m_wireframe;
    // common
    bool m_tilemode;
    bool m_plimcheck;
    bool m_visretain;
    // R13 - R14
    bool m_delobj;
    // common
    bool m_dispsilh;
    bool m_pellipse;
    int16_t m_saveimages; // proxygraphics R14 - R2000)
    // R13 - R14
    int16_t m_dragmode;
    //common
    int16_t m_treedepth;
    int16_t m_lunits;
    int16_t m_luprec;
    int16_t m_aunits;
    int16_t m_auprec;
    // R13 - R14
    int16_t m_osmode;
    // common
    int16_t m_attmode;
    // R13 - R14
    int16_t m_coords;
    // common
    int16_t m_pdmode;
    // R13 - R14
    int16_t m_pickstyle;
    // R2004+
    int32_t m_unknown12;
    int32_t m_unknown13;
    int32_t m_unknown14;
    // common
    int16_t m_useri1;
    int16_t m_useri2;
    int16_t m_useri3;
    int16_t m_useri4;
    int16_t m_useri5;
    int16_t m_splinesegs;
    int16_t m_surfu;
    int16_t m_surfv;
    int16_t m_surftype;
    int16_t m_surftab1;
    int16_t m_surftab2;
    int16_t m_splinetype;
    int16_t m_shadedge;
    int16_t m_shadedif;
    int16_t m_unitmode;
    int16_t m_maxactvp;
    int16_t m_isolines;
    int16_t m_cmljust;
    int16_t m_textqlty;
    double m_ltscale;
    double m_textsize;
    double m_tracewid;
    double m_sketchinc;
    double m_filletrad;
    double m_thickness;
    double m_angbase;
    double m_pdsize;
    double m_plinewid;
    double m_userr1;
    double m_userr2;
    double m_userr3;
    double m_userr4;
    double m_userr5;

    double m_chamfera;
    double m_chamferb;
    double m_chamferc;
    double m_chamferd;
    double m_facetres;
    double m_cmlscale;
    double m_celtscale;
    std::wstring m_menuname;
    int32_t m_tdcreate_day;
    int32_t m_tdcreate_ms;
    int32_t m_tdupdate_day;
    int32_t m_tdupdate_ms;
    // R2004+
    int32_t m_unknown15;
    int32_t m_unknown16;
    int32_t m_unknown17;
    // common
    int32_t m_tdindwg_days;
    int32_t m_tdindwg_ms;
    int32_t m_tdusrtimer_days;
    int32_t m_tdusrtimer_ms;
    bitcode::CMC m_cecolor;
    OcDbObjectId m_handseed;
    OcDbObjectId m_clayer;
    OcDbObjectId m_textstyle;
    OcDbObjectId m_celtype;

    // R2007+
    OcDbObjectId m_cmaterial;

    // common
    OcDbObjectId m_dimstyle;
    OcDbObjectId m_cmlstyle;

    // R2000+
    double m_psvpscale;

    // common
//    double m_insbase[3];
    OcGePoint3D m_pinsbase;
//    double m_extmin[3];
    OcGePoint3D m_pextmin;
//    double m_extmax[3];
    OcGePoint3D m_pextmax;
//    double m_limmin[2];
    OcGePoint2D m_plimmin;
//    double m_limmax[2];
    OcGePoint2D m_plimmax;

    double m_pelevation;
//   double m_ucsorg[3];
    OcGePoint3D m_pucsorg;
//    double m_ucsxdir[3];
    OcGePoint3D m_pucsxdir;
//    double m_ucsydir[3];
    OcGePoint3D m_pucsydir;
    OcDbObjectId m_pucsname;


    // R2000+
    OcDbObjectId m_pucsbase;
    int16_t m_pucsorthoview;
    OcDbObjectId m_pucsorthoref;
    OcGePoint3D m_pucsorgtop;
    OcGePoint3D m_pucsorgbottom;
    OcGePoint3D m_pucsorgleft;
    OcGePoint3D m_pucsorgright;
    OcGePoint3D m_pucsorgfront;
    OcGePoint3D m_pucsorgback;

    // common
    //    double m_insbase[3];
    OcGePoint3D m_insbase;
    //    double m_extmin[3];
    OcGePoint3D m_extmin;
    //    double m_extmax[3];
    OcGePoint3D m_extmax;
    //    double m_limmin[2];
    OcGePoint2D m_limmin;
    //    double m_limmax[2];
    OcGePoint2D m_limmax;

    double m_elevation;
    //   double m_ucsorg[3];
    OcGePoint3D m_ucsorg;
    //    double m_ucsxdir[3];
    OcGePoint3D m_ucsxdir;
    //    double m_ucsydir[3];
    OcGePoint3D m_ucsydir;
    OcDbObjectId m_ucsname;

    // R2000+
    OcDbObjectId m_ucsbase;
    int16_t m_ucsorthoview;
    OcDbObjectId m_ucsorthoref;
    OcGePoint3D m_ucsorgtop;
    OcGePoint3D m_ucsorgbottom;
    OcGePoint3D m_ucsorgleft;
    OcGePoint3D m_ucsorgright;
    OcGePoint3D m_ucsorgfront;
    OcGePoint3D m_ucsorgback;
    std::wstring m_dimpost;
    std::wstring m_dimapost;

    // R13 - R14
    //////////////////////////////////////////////////////////////////////////
    bool m_dimtol;
    bool m_dimlim;
    bool m_dimtih;
    bool m_dimtoh;
    bool m_dimse1;
    bool m_dimse2;
    bool m_dimalt;
    bool m_dimtofl;
    bool m_dimsah;
    bool m_dimtix;
    bool m_dimsoxd;

    int16_t m_dimaltd; // RC in R13-R14
    int16_t m_dimzin; // RC in R13-R14
    bool m_dimsd1;
    bool m_dimsd2;
    int16_t m_dimtolj; // RC in R13-R14
    int16_t m_dimjust; // RC in R13-R14
    byte_t m_dimfit;
    bool m_dimupt;
    int16_t m_dimtzin; // RC in R13-R14
    int16_t m_dimaltz; // RC in R13-R14
    int16_t m_dimalttz; // RC in R13-R14
    int16_t m_dimtad; // RC in R13-R14
    int16_t m_dimunit;
    int16_t m_dimaunit;
    int16_t m_dimdec;
    int16_t m_dimtdec;
    int16_t m_dimaltu;
    int16_t m_dimalttd;
    OcDbObjectId m_dimtxsty;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////

// common
    double          m_dimscale;
    double          m_dimasz;
    double          m_dimexo;
    double          m_dimdli;
    double          m_dimexe;
    double          m_dimrnd;
    double          m_dimdle;
    double          m_dimtp;
    double          m_dimtm;

// R2007+
    double          m_dimfxl;
    double          m_dimjogang;
    int16_t         m_dimtfill;
    bitcode::CMC    m_dimtfillclr;

// R2000+
//    bool            m_dimtol;
//    bool            m_dimlim;
//    bool            m_dimtih;
//    bool            m_dimtoh;
//    bool            m_dimse1;
//    bool            m_dimse2;
//    int16_t         m_dimtad;
//    int16_t         m_dimzin;
    int16_t         m_dimazin;

// R2007+
    int16_t         m_dimarcsym;

// common
    double          m_dimtxt;
    double          m_dimcen;
    double          m_dimtsz;
    double          m_dimaltf;
    double          m_dimlfac;
    double          m_dimtvp;
    double          m_dimtfac;
    double          m_dimgap;

// R13-R14
    // std::wstring    m_dimpost;
    // std::wstring    m_dimapost;
    std::wstring    m_dimblk;
    std::wstring    m_dimblk1;
    std::wstring    m_dimblk2;

// R2000+
    double          m_dimaltrnd;
    // bool            m_dimalt;
    // int16_t         m_dimaltd;
    // bool            m_dimtofl;
    // bool            m_dimsah;
    // bool            m_dimtix;
    // bool            m_dimsoxd;

// common
    bitcode::CMC    m_dimclrd;
    bitcode::CMC    m_dimclre;
    bitcode::CMC    m_dimclrt;

// R2000+
    int16_t         m_dimadec;
    // int16_t         m_dimdec;
    // int16_t         m_dimtdec;
    // int16_t         m_dimaltu;
    // int16_t         m_dimalttd;
    // int16_t         m_dimaunit;
    int16_t         m_dimfrac;
    int16_t         m_dimlunit;
    int16_t         m_dimdsep;
    int16_t         m_dimtmove;
    // int16_t         m_dimjust;
    // bool            m_dimsd1;
    // bool            m_dimsd2;
    // int16_t         m_dimtolj;
    // int16_t         m_dimtzin;
    // int16_t         m_dimaltz;
    // int16_t         m_dimalttz;
    // bool            m_dimupt;
    int16_t         m_dimatfit;

// R2007+
    bool            m_dimfxlon;

// R2000+
    // OcDbObjectId    m_dimtxtsty;
    OcDbObjectId    m_dimldrblk;
    OcDbObjectId    m_dimblkId;
    OcDbObjectId    m_dimblk1Id;
    OcDbObjectId    m_dimblk2Id;

// R2007+
    OcDbObjectId    m_dimltype;
    OcDbObjectId    m_dimltex1;
    OcDbObjectId    m_dimltex2;

// R2000+
    int16_t         m_dimlwd;
    int16_t         m_dimlwe;

// common
    OcDbObjectId    m_blockCtrlId;    // CONTROL OBJECT
    OcDbObjectId    m_layerCtrlId;    // CONTROL OBJECT
    OcDbObjectId    m_styleCtrlId;    // CONTROL OBJECT
    OcDbObjectId    m_linetypeCtrlId; // CONTROL OBJECT
    OcDbObjectId    m_viewCtrlId;     // CONTROL OBJECT
    OcDbObjectId    m_ucsCtrlId;      // CONTROL OBJECT
    OcDbObjectId    m_vportCtrlId;    // CONTROL OBJECT
    OcDbObjectId    m_appidCtrlId;    // CONTROL OBJECT
    OcDbObjectId    m_dimstyleCtrlId; // CONTROL OBJECT

// R13-R15
    OcDbObjectId    m_viewport; // ENTITY HEADER CONTROL OBJECT

// common
    OcDbObjectId    m_dictionaryGroupId;      // (ACAD_GROUP)
    OcDbObjectId    m_dictionaryMLineStyleId; // (ACAD_MLINESTYLE)
    OcDbObjectId    m_dictionaryNamedObjsId;   // (NAMED OBJECTS)

// R2000+
    int16_t         m_tstackalign;
    int16_t         m_tstacksize;
    std::wstring    m_hyperlinkbase;
    std::wstring    m_stylesheet;
    OcDbObjectId    m_dictionaryLayoutsId;   // (LAYOUTS)
    OcDbObjectId    m_dictionaryPlotSettingsId;   // (PLOTSETTINGS)
    OcDbObjectId    m_dictionaryPlotStylesId;   // (PLOTSTYLES)

// R2004+
    OcDbObjectId    m_dictionaryMaterialsId;   // (MATERIALS)
    OcDbObjectId    m_dictionaryColorsId;   // (COLORS)

// R2007+
    OcDbObjectId    m_dictionaryVisualStyleId;   // (VISUALSTYLE)

// R2000+
    int32_t         m_flags;
//                      CELWEIGHT       Flags & 0x001F
//                      ENDCAPS         Flags & 0x0060
//                      JOINSTYLE       Flags & 0x0180
//                      LWDISPLAY       !(Flags & 0x0200)
//                      XEDIT           !(Flags & 0x0400)
//                      EXTNAMES        Flags & 0x0800
//                      PSTYLEMODE      Flags & 0x2000
//                      OLESTARTUP      Flags & 0x4000
    int16_t         m_insunits;
    int16_t         m_cepsntype;
    OcDbObjectId    m_cpsnid;       // (present only if CEPSNTYPE == 3)
    std::wstring    m_fingerprintguid;
    std::wstring    m_versionguid;

// R2004+
    byte_t          m_sortents;
    byte_t          m_indexctl;
    byte_t          m_hidetext;
    byte_t          m_xclipframe;
    byte_t          m_dimassoc;
    byte_t          m_halogap;
    int16_t         m_obscuredcolor;
    int16_t         m_intersectioncolor;
    byte_t          m_obscuredltype;
    byte_t          m_intersectiondisplay;
    std::wstring    m_projectname;

// common
    OcDbObjectId    m_block_recordPsId;  // (*PAPER_SPACE)
    OcDbObjectId    m_block_recordMsId;  // (*MODEL_SPACE)
    OcDbObjectId    m_ltypeByLayerId;         // (BYLAYER)
    OcDbObjectId    m_ltypeByBlockId;         // (BYBLOCK)
    OcDbObjectId    m_ltypeContinuousId;         // (CONTINUOUS)

// R2007+
    bool            m_cameradisplay;
    int32_t         m_unknown21;
    int32_t         m_unknown22;
    double          m_unknown23;
    double          m_stepspersec;
    double          m_stepsize;
    double          m_3ddwfprec;
    double          m_lenslength;
    double          m_cameraheight;
    byte_t          m_solidhist;
    byte_t          m_showhist;
    double          m_psolwidth;
    double          m_psolheight;
    double          m_loftang1;
    double          m_loftang2;
    double          m_loftmag1;
    double          m_logtmag2;
    int16_t         m_loftparam;
    byte_t          m_loftnormals;
    double          m_latitude;
    double          m_longitude;
    double          m_northdirection;
    int32_t         m_timezone;
    byte_t          m_lightglyphdisplay;
    byte_t          m_tilemodelightsynch;
    byte_t          m_dwfframe;
    byte_t          m_dgnframe;
    bool            m_unknown47;
    bitcode::CMC    m_interferecolor;
    OcDbObjectId    m_interfereobjvsId;
    OcDbObjectId    m_interferevpvsId;
    OcDbObjectId    m_dragvsId;
    byte_t          m_cshadow;
    double          m_unknown53;

// R14+
    int16_t         m_unknown54;  // short(type 5 / 6 only)  these do not seem to be required,
    int16_t         m_unknown55;  // short(type 5 / 6 only)  even for type 5.
    int16_t         m_unknown56;  // short(type 5 / 6 only)
    int16_t         m_unknown57;  // short(type 5 / 6 only)

// common
    uint16_t        m_crc;      // for the data section, starting after the
    // sentinel. Use 0xC0C1 for the initial value.



};

END_OCTAVARIUM_NS


#endif // OcDfHeaderVars_h__

///////////////////////////////////////////////////////////////////////////
//// DWG Header Variables, in sequence order as found in drawing files ////
////                As shown in DwgFormatSpec13-2007.rtf               ////
///////////////////////////////////////////////////////////////////////////
//// common
//    double m_unknown1;
//    double m_unknown2;
//    double m_unknown3;
//    double m_unknown4;
//    std::wstring m_unknown5;
//    std::wstring m_unknown6;
//    std::wstring m_unknown7;
//    std::wstring m_unknown8;
//    int32_t m_unknown9;
//    int32_t m_unknown10;
//// R13 - R14
//    int16_t m_unknown11;
//// Pre-2004
//    OcDbHardOwnershipId m_currentVpId;
//
//
//// common
//    bool m_dimaso;
//    bool m_dimsho;
//// R13 - R14
//    bool m_dimsav;
//// common
//    bool m_plinegen;
//    bool m_orthomode;
//    bool m_regenmode;
//    bool m_fillmode;
//    bool m_qtextmode;
//    bool m_psltscale;
//    bool m_limcheck;
//// R13 - R14
//    bool m_blipmode;
//
//// R2004+
//    bool m_undocumented;
//// common
//    bool m_usertimer;
//    bool m_skpoly;
//    bool m_angdir;
//    bool m_splframe;
//// R13 - R14
//    bool m_attreq;
//    bool m_attdia;
//// common
//    bool m_mirrtext;
//    bool m_worldview;
//// R13 - R14
//    bool m_wireframe;
//// common
//    bool m_tilemode;
//    bool m_plimcheck;
//    bool m_visretain;
//// R13 - R14
//    bool m_delobj;
//// common
//    bool m_dispsilh;
//    bool m_pellipse;
//    int16_t m_saveimages; // proxygraphics R14 - R2000)
//// R13 - R14
//    int16_t m_dragmode;
////common
//    int16_t m_treedepth;
//    int16_t m_lunits;
//    int16_t m_luprec;
//    int16_t m_aunits;
//    int16_t m_auprec;
//// R13 - R14
//    int16_t m_osmode;
//// common
//    int16_t m_attmode;
//// R13 - R14
//    int16_t m_coords;
//// common
//    int16_t m_pdmode;
//// R13 - R14
//    int16_t m_pickstyle;
//// R2004+
//    int32_t m_unknown12;
//    int32_t m_unknown13;
//    int32_t m_unknown14;
//// common
//    int16_t m_useri1;
//    int16_t m_useri2;
//    int16_t m_useri3;
//    int16_t m_useri4;
//    int16_t m_useri5;
//    int16_t m_splinesegs;
//    int16_t m_surfu;
//    int16_t m_surfv;
//    int16_t m_surftype;
//    int16_t m_surftab1;
//    int16_t m_surftab2;
//    int16_t m_splinetype;
//    int16_t m_shadedge;
//    int16_t m_shadedif;
//    int16_t m_unitmode;
//    int16_t m_maxactvp;
//    int16_t m_isolines;
//    int16_t m_cmljust;
//    int16_t m_textqlty;
//    double m_ltscale;
//    double m_textsize;
//    double m_tracewid;
//    double m_sketchinc;
//    double m_filletrad;
//    double m_thickness;
//    double m_angbase;
//    double m_pdsize;
//    double m_plinewid;
//    double m_userr1;
//    double m_userr2;
//    double m_userr3;
//    double m_userr4;
//    double m_userr5;
//
//    double m_chamfera;
//    double m_chamferb;
//    double m_chamferc;
//    double m_chamferd;
//    double m_facetres;
//    double m_cmlscale;
//    double m_celtscale;
//    std::wstring m_menuname;
//    int32_t m_tdcreate_day;
//    int32_t m_tdcreate_ms;
//    int32_t m_tdupdate_day;
//    int32_t m_tdupdate_ms;
//// R2004+
//    int32_t m_unknown15;
//    int32_t m_unknown16;
//    int32_t m_unknown17;
//// common
//    int32_t m_tdindwg_days;
//    int32_t m_tdindwg_ms;
//    int32_t m_tdusrtimer_days;
//    int32_t m_tdusrtimer_ms;
//    bitcode::CMC m_cecolor;
//    OcDbObjectId m_handseed;
//    OcDbObjectId m_clayer;
//    OcDbObjectId m_textstyle;
//    OcDbObjectId m_celtype;
//
//// R2007+
//    OcDbObjectId m_cmaterial;
//
//// common
//    OcDbObjectId m_dimstyle;
//    OcDbObjectId m_cmlstyle;
//
//// R2000+
//    double m_psvpscale;
//
//// common
////    double m_insbase[3];
//    OcGePoint3D m_pinsbase;
////    double m_extmin[3];
//    OcGePoint3D m_pextmin;
////    double m_extmax[3];
//    OcGePoint3D m_pextmax;
////    double m_limmin[2];
//    OcGePoint2D m_plimmin;
////    double m_limmax[2];
//    OcGePoint2D m_plimmax;
//
//    double m_pelevation;
////   double m_ucsorg[3];
//    OcGePoint3D m_pucsorg;
////    double m_ucsxdir[3];
//    OcGePoint3D m_pucsxdir;
////    double m_ucsydir[3];
//    OcGePoint3D m_pucsydir;
//    OcDbObjectId m_pucsname;
//
//
//// R2000+
//    OcDbObjectId m_pucsbase;
//    int16_t m_pucsorthoview;
//    OcDbObjectId m_pucsorthoref;
//    OcGePoint3D m_pucsorgtop;
//    OcGePoint3D m_pucsorgbottom;
//    OcGePoint3D m_pucsorgleft;
//    OcGePoint3D m_pucsorgright;
//    OcGePoint3D m_pucsorgfront;
//    OcGePoint3D m_pucsorgback;
//
//// common
//    //    double m_insbase[3];
//    OcGePoint3D m_insbase;
//    //    double m_extmin[3];
//    OcGePoint3D m_extmin;
//    //    double m_extmax[3];
//    OcGePoint3D m_extmax;
//    //    double m_limmin[2];
//    OcGePoint2D m_limmin;
//    //    double m_limmax[2];
//    OcGePoint2D m_limmax;
//
//    double m_elevation;
//    //   double m_ucsorg[3];
//    OcGePoint3D m_ucsorg;
//    //    double m_ucsxdir[3];
//    OcGePoint3D m_ucsxdir;
//    //    double m_ucsydir[3];
//    OcGePoint3D m_ucsydir;
//    OcDbObjectId m_ucsname;
//
//// R2000+
//    OcDbObjectId m_ucsbase;
//    int16_t m_ucsorthoview;
//    OcDbObjectId m_ucsorthoref;
//    OcGePoint3D m_ucsorgtop;
//    OcGePoint3D m_ucsorgbottom;
//    OcGePoint3D m_ucsorgleft;
//    OcGePoint3D m_ucsorgright;
//    OcGePoint3D m_ucsorgfront;
//    OcGePoint3D m_ucsorgback;
//    std::wstring m_dimpost;
//    std::wstring m_dimapost;
//
//// R13 - R14
//    //////////////////////////////////////////////////////////////////////////
//    bool m_dimtol;
//    bool m_dimlim;
//    bool m_dimtih;
//    bool m_dimtoh;
//    bool m_dimse1;
//    bool m_dimse2;
//    bool m_dimalt;
//    bool m_dimtofl;
//    bool m_dimsah;
//    bool m_dimtix;
//    bool m_dimsoxd;
//    byte_t m_dimaltd;
//    byte_t m_dimzin;
//    bool m_dimsd1;
//    bool m_dimsd2;
//    byte_t m_dimtolj;
//    byte_t m_dimjust;
//    byte_t m_dimfit;
//    bool m_dimupt;
//    byte_t m_dimtzin;
//    byte_t m_dimaltz;
//    byte_t m_dimalttz;
//    byte_t m_dimtad;
//    int16_t m_dimunit;
//    int16_t m_dimaunit;
//    int16_t m_dimdec;
//    int16_t m_dimtdec;
//    int16_t m_dimaltu;
//    int16_t m_dimalttd;
//    OcDbObjectId m_dimtxsty;



//// common
//    double          m_dimscale;
//    double          m_dimasz;
//    double          m_dimexo;
//    double          m_dimdli;
//    double          m_dimexe;
//    double          m_dimrnd;
//    double          m_dimdle;
//    double          m_dimtp;
//    double          m_dimtm;
//
//// R2007+
//    double          m_dimfxl;
//    double          m_dimjogang;
//    int16_t         m_dimtfill;
//    bitcode::CMC    m_dimtfillclr;
//
//// R2000+
//    bool            m_dimtol;
//    bool            m_dimlim;
//    bool            m_dimtih;
//    bool            m_dimtoh;
//    bool            m_dimse1;
//    bool            m_dimse2;
//    int16_t         m_dimtad;
//    int16_t         m_dimzin;
//    int16_t         m_dimazin;
//
//// R2007+
//    int16_t         m_dimarcsym;
//
//// common
//    double          m_dimtxt;
//    double          m_dimcen;
//    double          m_dimtsz;
//    double          m_dimaltf;
//    double          m_dimlfac;
//    double          m_dimtvp;
//    double          m_dimtfac;
//    double          m_dimgap;
//
//// R13-R14
//    std::wstring    m_dimpost;
//    std::wstring    m_dimapost;
//    std::wstring    m_dimblk;
//    std::wstring    m_dimblk1;
//    std::wstring    m_dimblk2;
//
//// R2000+
//    double          m_dimaltrnd;
//    bool            m_dimalt;
//    int16_t         m_dimaltd;
//    bool            m_dimtofl;
//    bool            m_dimsah;
//    bool            m_dimtix;
//    bool            m_dimsoxd;
//
//// common
//    bitcode::CMC    m_dimclrd;
//    bitcode::CMC    m_dimclre;
//    bitcode::CMC    m_dimclrt;
//
//// R2000+
//    int16_t         m_dimadec;
//    int16_t         m_dimdec;
//    int16_t         m_dimtdec;
//    int16_t         m_dimaltu;
//    int16_t         m_dimalttd;
//    int16_t         m_dimaunit;
//    int16_t         m_dimfrac;
//    int16_t         m_dimlunit;
//    int16_t         m_dimdsep;
//    int16_t         m_dimtmove;
//    int16_t         m_dimjust;
//    bool            m_dimsd1;
//    bool            m_dimsd2;
//    int16_t         m_dimtolj;
//    int16_t         m_dimtzin;
//    int16_t         m_dimaltz;
//    int16_t         m_dimalttz;
//    bool            m_dimupt;
//    int16_t         m_dimatfit;
//
//// R2007+
//    bool            m_dimfxlon;
//
//// R2000+
//    OcDbObjectId    m_dimtxtsty;
//    OcDbObjectId    m_dimldrblk;
//    OcDbObjectId    m_dimblk;
//    OcDbObjectId    m_dimblk1;
//    OcDbObjectId    m_dimblk2;
//
//// R2007+
//    OcDbObjectId    m_dimltype;
//    OcDbObjectId    m_dimltex1;
//    OcDbObjectId    m_dimltex2;
//
//// R2000+
//    int16_t         m_dimlwd;
//    int16_t         m_dimlwe;
//
//// common
//    OcDbObjectId    m_block;    // CONTROL OBJECT
//    OcDbObjectId    m_layer;    // CONTROL OBJECT
//    OcDbObjectId    m_style;    // CONTROL OBJECT
//    OcDbObjectId    m_linetype; // CONTROL OBJECT
//    OcDbObjectId    m_view;     // CONTROL OBJECT
//    OcDbObjectId    m_ucs;      // CONTROL OBJECT
//    OcDbObjectId    m_vport;    // CONTROL OBJECT
//    OcDbObjectId    m_appid;    // CONTROL OBJECT
//    OcDbObjectId    m_dimstyle; // CONTROL OBJECT
//
//// R13-R15
//    OcDbObjectId    m_viewport; // ENTITY HEADER CONTROL OBJECT
//
//// common
//    OcDbObjectId    m_dictionary;   // (ACAD_GROUP)
//    OcDbObjectId    m_dictionary;   // (ACAD_MLINESTYLE)
//    OcDbObjectId    m_dictionary;   // (NAMED OBJECTS)
//
//// R2000+
//    int16_t         m_unknown;
//    int16_t         m_unknown;
//    std::wstring    m_hyperlinkbase;
//    std::wstring    m_stylesheet;
//    OcDbObjectId    m_dictionary;   // (LAYOUTS)
//    OcDbObjectId    m_dictionary;   // (PLOTSETTINGS)
//    OcDbObjectId    m_dictionary;   // (PLOTSTYLES)
//
//// R2004+
//    OcDbObjectId    m_dictionary;   // (MATERIALS)
//    OcDbObjectId    m_dictionary;   // (COLORS)
//
//// R2007+
//    OcDbObjectId    m_dictionary;   // (VISUALSTYLE)
//
//// R2000+
//    int32_t         m_flags;
////                      CELWEIGHT       Flags & 0x001F
////                      ENDCAPS         Flags & 0x0060
////                      JOINSTYLE       Flags & 0x0180
////                      LWDISPLAY       !(Flags & 0x0200)
////                      XEDIT           !(Flags & 0x0400)
////                      EXTNAMES        Flags & 0x0800
////                      PSTYLEMODE      Flags & 0x2000
////                      OLESTARTUP      Flags & 0x4000
//    int16_t         m_insunits;
//    int16_t         m_cepsntype;
//    OcDbObjectId    m_cpsnid;       // (present only if CEPSNTYPE == 3)
//    std::wstring    m_fingerprintguid;
//    std::wstring    m_versionguid;
//
//// R2004+
//    byte_t          m_sortents;
//    byte_t          m_indexctl;
//    byte_t          m_hidetext;
//    byte_t          m_xclipframe;
//    byte_t          m_dimassoc;
//    byte_t          m_halogap;
//    int16_t         m_obscuredcolor;
//    int16_t         m_intersectioncolor;
//    byte_t          m_obscuredltype;
//    byte_t          m_intersectiondisplay;
//    std::wstring    m_projectname;
//
//// common
//    OcDbObjectId    m_block_record;  // (*PAPER_SPACE)
//    OcDbObjectId    m_block_record;  // (*MODEL_SPACE)
//    OcDbObjectId    m_ltype;         // (BYLAYER)
//    OcDbObjectId    m_ltype;         // (BYBLOCK)
//    OcDbObjectId    m_ltype;         // (CONTINUOUS)
//
//// R2007+
//    bool            m_unknown;
//    int32_t         m_unknown;
//    int32_t         m_unknown;
//    double          m_unknown;
//    double          m_unknown;
//    double          m_unknown;
//    double          m_unknown;
//    double          m_unknown;
//    double          m_unknown;
//    byte_t          m_unknown;
//    byte_t          m_unknown;
//    double          m_unknown;
//    double          m_unknown;
//    double          m_unknown;
//    double          m_unknown;
//    double          m_unknown;
//    double          m_unknown;
//    int16_t         m_unknown;
//    byte_t          m_unknown;
//    double          m_unknown;
//    double          m_unknown;
//    double          m_unknown;
//    int32_t         m_unknown;
//    byte_t          m_unknown;
//    byte_t          m_unknown;
//    byte_t          m_unknown;
//    byte_t          m_unknown;
//    bool            m_unknown;
//    bitcode::CMC    m_unknown;
//    OcDbObjectId    m_unknown;
//    OcDbObjectId    m_unknown;
//    OcDbObjectId    m_unknown;
//    byte_t          m_unknown;
//    double          m_unknown;
//
//// R14+
//    int16_t         m_unknown;  // short(type 5 / 6 only)  these do not seem to be required,
//    int16_t         m_unknown;  // short(type 5 / 6 only)  even for type 5.
//    int16_t         m_unknown;  // short(type 5 / 6 only)
//    int16_t         m_unknown;  // short(type 5 / 6 only)
//
//// common
//    uint16_t        m_crc;      // for the data section, starting after the
//                                // sentinel. Use 0xC0C1 for the initial value.
//
//
