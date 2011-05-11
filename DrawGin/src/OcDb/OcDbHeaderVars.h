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
    double m_insbase[3];
    double m_extmin[3];
    double m_extmax[3];
    double m_limmin[2];
    double m_limmax[2];

    double m_elevation;
    double m_ucsorg[3];
    double m_ucsxdir[3];
    double m_ucsydir[3];
    OcDbObjectId m_ucsname;



};

END_OCTAVARIUM_NS


#endif // OcDbHeaderVars_h__
