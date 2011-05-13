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

#ifndef OcDbHeaderVars_h__
#define OcDbHeaderVars_h__

BEGIN_OCTAVARIUM_NS

class OcDbObjectId;

class OcDbHeaderVars
{
public:
    OcDbHeaderVars(void);
    virtual ~OcDbHeaderVars(void);

private:
    OcApp::ErrorStatus DecodeData(DwgInArchive& in);
    friend DwgInArchive& operator>>(DwgInArchive& in,
                                    OcDbHeaderVars & dwgVars);

private: // header variables
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
    // R13 - R14 only
    int16_t m_unknown11;
    // Pre-2004 only
    OcDbHardOwnershipId m_currentVpId;


    // common
    bool m_dimaso;
    bool m_dimsho;
    // R13 - R14 only
    bool m_dimsav;
    // common
    bool m_plinegen;
    bool m_orthomode;
    bool m_regenmode;
    bool m_fillmode;
    bool m_qtextmode;
    bool m_psltscale;
    bool m_limcheck;
    // R13 - R14 only
    bool m_blipmode;

    // R2004+
    bool m_undocumented;
    // common
    bool m_usertimer;
    bool m_skpoly;
    bool m_angdir;
    bool m_splframe;
    // R13 - R14 only
    bool m_attreq;
    bool m_attdia;
    // common
    bool m_mirrtext;
    bool m_worldview;
    // R13 - R14 only
    bool m_wireframe;
    // common
    bool m_tilemode;
    bool m_plimcheck;
    bool m_visretain;
    // R13 - R14 only
    bool m_delobj;
    // common
    bool m_dispsilh;
    bool m_pellipse;
    int16_t m_saveimages; // proxygraphics R14 - R2000)
    // R13 - R14 only
    int16_t m_dragmode;
    //common
    int16_t m_treedepth;
    int16_t m_lunits;
    int16_t m_luprec;
    int16_t m_aunits;
    int16_t m_auprec;
    // R13 - R14 only
    int16_t m_osmode;
    // common
    int16_t m_attmode;
    // R13 - R14 only
    int16_t m_coords;
    // common
    int16_t m_pdmode;
    // R13 - R14 only
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

    // R2000+ only
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


    // R2000+ only
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

    // R2000+ only
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

    // common
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
    byte_t m_dimaltd;
    byte_t m_dimzin;
    bool m_dimsd1;
    bool m_dimsd2;
    byte_t m_dimtolj;
    byte_t m_dimjust;
    byte_t m_dimfit;
    bool m_dimupt;
    byte_t m_dimtzin;
    byte_t m_dimaltz;
    byte_t m_dimalttz;
    byte_t m_dimtad;
    int16_t m_dimunit;
    int16_t m_dimaunit;
    int16_t m_dimdec;
    int16_t m_dimtdec;
    int16_t m_dimaltu;
    int16_t m_dimalttd;
    OcDbObjectId m_dimtxsty;
};

END_OCTAVARIUM_NS


#endif // OcDbHeaderVars_h__
