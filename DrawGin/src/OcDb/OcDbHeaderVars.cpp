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

#include "stdafx.h"

#include "OcCommon.h"
#include "OcTypes.h"
#include "OcError.h"
#include "OcDbDwgVersion.h"
#include "OcDbObjectId.h"
#include "OcDbHardOwnershipId.h"
#include "OcGePoint2D.h"
#include "OcGePoint3D.h"

#include "../OcBs/DwgInArchive.h"
#include "OcDbHeaderVars.h"
#include "../OcBs/OcBsDwgSentinels.h"



BEGIN_OCTAVARIUM_NS
using namespace std;

#define ASSERT_ARCHIVE_NOT_LOADING assert(in.ArchiveFlag() == DwgInArchive::LOADING)


OcDbHeaderVars::OcDbHeaderVars(void)
{
    VLOG(3) << "Constructor entered";
}

OcDbHeaderVars::~OcDbHeaderVars(void)
{
    VLOG(3) << "Destructor entered";
}

OcApp::ErrorStatus OcDbHeaderVars::DecodeData(DwgInArchive& in)
{
    VLOG(3) << "DecodeData entered";
    ASSERT_ARCHIVE_NOT_LOADING;

    // match dwg header variables start sentinel
    bitcode::RC sentinelData[16];
    in.ReadRC(sentinelData, 16);
    if(!CompareSentinels(sentinelHeaderVarsStart, sentinelData)) {
        return OcApp::eInvalidImageDataSentinel;
    }

    const DWG_VERSION dwgVersion = in.Version();
    int size;
    uint16_t crc = 0;

    // spec says this is a R2007 variable only, but that doesn't
    // seem to be correct, at least for the R2008 drawing down converted
    // to R14.
    //   if(dwgVersion == R2007) {
    //    Archive<bitcode::RL>(in, size, "Header variables size");
    BS_ARCHIVE(crc, bitcode::RL, in, size, "Header variables size");
    //    }

    BS_ARCHIVE(crc, bitcode::BD, in, m_unknown1, "unknown1");
    BS_ARCHIVE(crc, bitcode::BD, in, m_unknown2, "unknown2");
    BS_ARCHIVE(crc, bitcode::BD, in, m_unknown3, "unknown3");
    BS_ARCHIVE(crc, bitcode::BD, in, m_unknown4, "unknown4");
    BS_ARCHIVE(crc, bitcode::TV, in, m_unknown5, "unknown5");

    BS_ARCHIVE(crc, bitcode::TV, in, m_unknown6, "unknown6");
    BS_ARCHIVE(crc, bitcode::TV, in, m_unknown7, "unknown7");
    BS_ARCHIVE(crc, bitcode::TV, in, m_unknown8, "unknown8");
    BS_ARCHIVE(crc, bitcode::BL, in, m_unknown9, "unknown9");
    BS_ARCHIVE(crc, bitcode::BL, in, m_unknown10, "unknown10");

    if(dwgVersion == R13 || dwgVersion == R14) {
        BS_ARCHIVE(crc, bitcode::BS, in, m_unknown11, "unknown11");
    }

    BS_ARCHIVE(crc, OcDbObjectId, in, m_currentVpId, "currentvpId");

    BS_ARCHIVE(crc, bitcode::B, in, m_dimaso, "dimaso");

    BS_ARCHIVE(crc, bitcode::B, in, m_dimsho, "dimsho");

    if(dwgVersion == R13 || dwgVersion == R14) {
        BS_ARCHIVE(crc, bitcode::B, in, m_dimsav, "dimsav");
    }

//    in >> (bitcode::B&) m_plinegen;
//    VLOG(4) << "plinegen = " << m_plinegen;
    BS_ARCHIVE(crc, bitcode::B, in, m_plinegen, "plinegen");

//    in >> (bitcode::B&) m_orthomode;
//    VLOG(4) << "orthomode = " << m_orthomode;
    BS_ARCHIVE(crc, bitcode::B, in, m_orthomode, "orthomode");

//    in >> (bitcode::B&) m_regenmode;
//    VLOG(4) << "regenmode = " << m_regenmode;
    BS_ARCHIVE(crc, bitcode::B, in, m_regenmode, "regenmode");

//    in >> (bitcode::B&) m_fillmode;
//    VLOG(4) << "fillmode = " << m_fillmode;
    BS_ARCHIVE(crc, bitcode::B, in, m_fillmode, "fillmode");

//    in >> (bitcode::B&) m_qtextmode;
//    VLOG(4) << "qtextmode = " << m_qtextmode;
    BS_ARCHIVE(crc, bitcode::B, in, m_qtextmode, "qtextmode");

//    in >> (bitcode::B&) m_psltscale;
//    VLOG(4) << "psltscale = " << m_psltscale;
    BS_ARCHIVE(crc, bitcode::B, in, m_psltscale, "psltscale");

//    in >> (bitcode::B&) m_limcheck;
//    VLOG(4) << "limcheck = " << m_limcheck;
    BS_ARCHIVE(crc, bitcode::B, in, m_limcheck, "limcheck");

    if(dwgVersion == R13 || dwgVersion == R14) {
//        in >> (bitcode::B&) m_blipmode;
//        VLOG(4) << "blipmode = " << m_blipmode;
        BS_ARCHIVE(crc, bitcode::B, in, m_blipmode, "blipmode");
    }

    if(dwgVersion >= R2004) {
//        in >> (bitcode::B&) m_undocumented;
//        VLOG(4) << "undocumented = " << m_undocumented;
        BS_ARCHIVE(crc, bitcode::B, in, m_undocumented, "undocumented");
    }

//    in >> (bitcode::B&) m_usertimer;
//    VLOG(4) << "usertimer = " << m_usertimer;
    BS_ARCHIVE(crc, bitcode::B, in, m_usertimer, "usertimer");

//    in >> (bitcode::B&) m_skpoly;
//    VLOG(4) << "skpoly = " << m_skpoly;
    BS_ARCHIVE(crc, bitcode::B, in, m_skpoly, "skpoly");

//    in >> (bitcode::B&) m_angdir;
//    VLOG(4) << "angdir = " << m_angdir;
    BS_ARCHIVE(crc, bitcode::B, in, m_angdir, "angdir");

//    in >> (bitcode::B&) m_splframe;
//    VLOG(4) << "splframe = " << m_splframe;
    BS_ARCHIVE(crc, bitcode::B, in, m_splframe, "splframe");

    if(dwgVersion == R13 || dwgVersion == R14) {
//        in >> (bitcode::B&) m_attreq;
//        in >> (bitcode::B&) m_attdia;
//        VLOG(4) << "attreq = " << m_attreq;
//        VLOG(4) << "attdia = " << m_attdia;
        BS_ARCHIVE(crc, bitcode::B, in, m_attreq, "attreq");
        BS_ARCHIVE(crc, bitcode::B, in, m_attdia, "attdia");
    }

//    in >> (bitcode::B&) m_mirrtext;
    BS_ARCHIVE(crc, bitcode::B, in, m_mirrtext, "mirrtext");

//    in >> (bitcode::B&) m_worldview;
    BS_ARCHIVE(crc, bitcode::B, in, m_worldview, "worldview");

    if(dwgVersion == R13 || dwgVersion == R14) {
//        in >> (bitcode::B&) m_wireframe;
        BS_ARCHIVE(crc, bitcode::B, in, m_wireframe, "wireframe");
    }

//    in >> (bitcode::B&) m_tilemode;
    BS_ARCHIVE(crc, bitcode::B, in, m_tilemode, "tilemode");

//    in >> (bitcode::B&) m_plimcheck;
    BS_ARCHIVE(crc, bitcode::B, in, m_plimcheck, "plimcheck");

//    in >> (bitcode::B&) m_visretain;
    BS_ARCHIVE(crc, bitcode::B, in, m_visretain, "visretain");

    if(dwgVersion == R13 || dwgVersion == R14) {
//        in >> (bitcode::B&) m_delobj;
        BS_ARCHIVE(crc, bitcode::B, in, m_delobj, "delobj");
    }

//    in >> (bitcode::B&) m_dispsilh;
    BS_ARCHIVE(crc, bitcode::B, in, m_dispsilh, "dispsilh");

//    in >> (bitcode::B&) m_pellipse;
    BS_ARCHIVE(crc, bitcode::B, in, m_pellipse, "pellispe");

//    in >> (bitcode::BS&) m_saveimages;
    BS_ARCHIVE(crc, bitcode::BS, in, m_saveimages, "saveimages");

    if(dwgVersion == R13 || dwgVersion == R14) {
//        in >> (bitcode::BS&) m_dragmode;
        BS_ARCHIVE(crc, bitcode::BS, in, m_dimsav, "dimsav");
    }

//    in >> (bitcode::BS&) m_treedepth;
    BS_ARCHIVE(crc, bitcode::BS, in, m_treedepth, "treedepth");

//    in >> (bitcode::BS&) m_lunits;
    BS_ARCHIVE(crc, bitcode::BS, in, m_lunits, "lunits");

//    in >> (bitcode::BS&) m_luprec;
    BS_ARCHIVE(crc, bitcode::BS, in, m_luprec, "luprec");

//    in >> (bitcode::BS&) m_aunits;
    BS_ARCHIVE(crc, bitcode::BS, in, m_aunits, "aunits");

//    in >> (bitcode::BS&) m_auprec;
    BS_ARCHIVE(crc, bitcode::BS, in, m_auprec, "auprec");

    if(dwgVersion == R13 || dwgVersion == R14) {
//        in >> (bitcode::BS&) m_osmode;
        BS_ARCHIVE(crc, bitcode::BS, in, m_osmode, "osmode");
    }

//    in >> (bitcode::BS&) m_attmode;
    BS_ARCHIVE(crc, bitcode::BS, in, m_attmode, "attmode");

    if(dwgVersion == R13 || dwgVersion == R14) {
//        in >> (bitcode::BS&) m_coords;
        BS_ARCHIVE(crc, bitcode::BS, in, m_coords, "coords");
    }

//    in >> (bitcode::BS&) m_pdmode;
    BS_ARCHIVE(crc, bitcode::BS, in, m_pdmode, "pdmode");

    if(dwgVersion == R13 || dwgVersion == R14) {
//        in >> (bitcode::BS&) m_pickstyle;
        BS_ARCHIVE(crc, bitcode::BS, in, m_pickstyle, "pickstyle");
    }

    if(dwgVersion >= R2004) {
//        in >> (bitcode::BL&) m_unknown12;
//        in >> (bitcode::BL&) m_unknown13;
//        in >> (bitcode::BL&) m_unknown14;
        BS_ARCHIVE(crc, bitcode::BL, in, m_unknown12, "unknown12");
        BS_ARCHIVE(crc, bitcode::BL, in, m_unknown13, "unknown13");
        BS_ARCHIVE(crc, bitcode::BL, in, m_unknown14, "unknown14");
    }

//    in >> (bitcode::BS&) m_useri1;
    BS_ARCHIVE(crc, bitcode::BS, in, m_useri1, "useri1");

//    in >> (bitcode::BS&) m_useri2;
    BS_ARCHIVE(crc, bitcode::BS, in, m_useri2, "useri2");

//    in >> (bitcode::BS&) m_useri3;
    BS_ARCHIVE(crc, bitcode::BS, in, m_useri3, "useri3");

//    in >> (bitcode::BS&) m_useri4;
    BS_ARCHIVE(crc, bitcode::BS, in, m_useri4, "useri4");

//    in >> (bitcode::BS&) m_useri5;
    BS_ARCHIVE(crc, bitcode::BS, in, m_useri5, "useri5");

//    in >> (bitcode::BS&) m_splinesegs;
    BS_ARCHIVE(crc, bitcode::BS, in, m_splinesegs, "splinesegs");

//    in >> (bitcode::BS&) m_surfu;
    BS_ARCHIVE(crc, bitcode::BS, in, m_surfu, "surfu");

//    in >> (bitcode::BS&) m_surfv;
    BS_ARCHIVE(crc, bitcode::BS, in, m_surfv, "surfv");

//    in >> (bitcode::BS&) m_surftype;
    BS_ARCHIVE(crc, bitcode::BS, in, m_surftype, "surftype");

//    in >> (bitcode::BS&) m_surftab1;
    BS_ARCHIVE(crc, bitcode::BS, in, m_surftab1, "surftab1");

//    in >> (bitcode::BS&) m_surftab2;
    BS_ARCHIVE(crc, bitcode::BS, in, m_surftab2, "surftab2");

//    in >> (bitcode::BS&) m_splinetype;
    BS_ARCHIVE(crc, bitcode::BS, in, m_splinetype, "splinetype");

//    in >> (bitcode::BS&) m_shadedge;
    BS_ARCHIVE(crc, bitcode::BS, in, m_shadedge, "shadedge");

//    in >> (bitcode::BS&) m_shadedif;
    BS_ARCHIVE(crc, bitcode::BS, in, m_shadedif, "shadedif");

//    in >> (bitcode::BS&) m_unitmode;
    BS_ARCHIVE(crc, bitcode::BS, in, m_unitmode, "unitmode");

//    in >> (bitcode::BS&) m_maxactvp;
    BS_ARCHIVE(crc, bitcode::BS, in, m_maxactvp, "macactvp");

//    in >> (bitcode::BS&) m_isolines;
    BS_ARCHIVE(crc, bitcode::BS, in, m_isolines, "isolines");

//    in >> (bitcode::BS&) m_cmljust;
    BS_ARCHIVE(crc, bitcode::BS, in, m_cmljust, "cmljust");

//    in >> (bitcode::BS&) m_textqlty;
    BS_ARCHIVE(crc, bitcode::BS, in, m_textqlty, "textqlty");

//    in >> (bitcode::BD&) m_ltscale;
    BS_ARCHIVE(crc, bitcode::BD, in, m_ltscale, "ltscale");

//    in >> (bitcode::BD&) m_textsize;
    BS_ARCHIVE(crc, bitcode::BD, in, m_textsize, "textsize");

//    in >> (bitcode::BD&) m_tracewid;
    BS_ARCHIVE(crc, bitcode::BD, in, m_tracewid, "tracewid");

//    in >> (bitcode::BD&) m_sketchinc;
    BS_ARCHIVE(crc, bitcode::BD, in, m_sketchinc, "sketchinc");

//    in >> (bitcode::BD&) m_filletrad;
    BS_ARCHIVE(crc, bitcode::BD, in, m_filletrad, "filletrad");

//    in >> (bitcode::BD&) m_thickness;
    BS_ARCHIVE(crc, bitcode::BD, in, m_thickness, "thickness");

//    in >> (bitcode::BD&) m_angbase;
    BS_ARCHIVE(crc, bitcode::BD, in, m_angbase, "angbase");

//    in >> (bitcode::BD&) m_pdsize;
    BS_ARCHIVE(crc, bitcode::BD, in, m_pdsize, "pdsize");

//    in >> (bitcode::BD&) m_plinewid;
    BS_ARCHIVE(crc, bitcode::BD, in, m_plinewid, "plinewid");

//    in >> (bitcode::BD&) m_userr1;
    BS_ARCHIVE(crc, bitcode::BD, in, m_userr1, "userr1");

//    in >> (bitcode::BD&) m_userr2;
    BS_ARCHIVE(crc, bitcode::BD, in, m_userr2, "userr2");

//    in >> (bitcode::BD&) m_userr3;
    BS_ARCHIVE(crc, bitcode::BD, in, m_userr3, "userr3");

//    in >> (bitcode::BD&) m_userr4;
    BS_ARCHIVE(crc, bitcode::BD, in, m_userr4, "userr4");

//    in >> (bitcode::BD&) m_userr5;
    BS_ARCHIVE(crc, bitcode::BD, in, m_userr5, "userr5");


//    in >> (bitcode::BD&) m_chamfera;
    BS_ARCHIVE(crc, bitcode::BD, in, m_chamfera, "chamfera");

//    in >> (bitcode::BD&) m_chamferb;
    BS_ARCHIVE(crc, bitcode::BD, in, m_chamferb, "chamferb");

//    in >> (bitcode::BD&) m_chamferc;
    BS_ARCHIVE(crc, bitcode::BD, in, m_chamferc, "chamferc");

//    in >> (bitcode::BD&) m_chamferd;
    BS_ARCHIVE(crc, bitcode::BD, in, m_chamferd, "chamferd");

//    in >> (bitcode::BD&) m_facetres;
    BS_ARCHIVE(crc, bitcode::BD, in, m_facetres, "facetres");

//    in >> (bitcode::BD&) m_cmlscale;
    BS_ARCHIVE(crc, bitcode::BD, in, m_cmlscale, "cmlscale");

//    in >> (bitcode::BD&) m_celtscale;
    BS_ARCHIVE(crc, bitcode::BD, in, m_celtscale, "celtscale");

//    in >> (bitcode::TV&) m_menuname;
    BS_ARCHIVE(crc, bitcode::TV, in, m_menuname, "menuname");

//    in >> (bitcode::BL&) m_tdcreate_day;
    BS_ARCHIVE(crc, bitcode::BL, in, m_tdcreate_day, "tdcreate_day");

//    in >> (bitcode::BL&) m_tdcreate_ms;
    BS_ARCHIVE(crc, bitcode::BL, in, m_tdcreate_ms, "tdcreate_ms");

//    in >> (bitcode::BL&) m_tdupdate_day;
    BS_ARCHIVE(crc, bitcode::BL, in, m_tdupdate_day, "tdupdate_day");

//    in >> (bitcode::BL&) m_tdupdate_ms;
    BS_ARCHIVE(crc, bitcode::BL, in, m_tdupdate_ms, "tdupdate_ms");

    if(dwgVersion >= R2004) {
//        in >> (bitcode::BL&) m_unknown15;
//        in >> (bitcode::BL&) m_unknown16;
//        in >> (bitcode::BL&) m_unknown17;
        BS_ARCHIVE(crc, bitcode::BL, in, m_unknown15, "unknown15");
        BS_ARCHIVE(crc, bitcode::BL, in, m_unknown16, "unknown16");
        BS_ARCHIVE(crc, bitcode::BL, in, m_unknown17, "unknown17");
    }

//    in >> (bitcode::BL&) m_tdindwg_days;
    BS_ARCHIVE(crc, bitcode::BL, in, m_tdindwg_days, "tdindwg_days");

//    in >> (bitcode::BL&) m_tdindwg_ms;
    BS_ARCHIVE(crc, bitcode::BL, in, m_tdindwg_ms, "tdindwg_ms");

//    in >> (bitcode::BL&) m_tdusrtimer_days;
    BS_ARCHIVE(crc, bitcode::BL, in, m_tdusrtimer_days, "tdusrtimer_days");

//    in >> (bitcode::BL&) m_tdusrtimer_ms;
    BS_ARCHIVE(crc, bitcode::BL, in, m_tdusrtimer_ms, "tdusrtimer_ms");

//    in >> (bitcode::CMC&) m_cecolor;
////    BS_ARCHIVE(crc, bitcode::CMC, in, m_cecolor, "cecolor");

//    in.ReadHandle(m_handseed);
    BS_ARCHIVE(crc, OcDbObjectId, in, m_handseed, "handseed");

//    in.ReadHandle(m_clayer);
    BS_ARCHIVE(crc, OcDbObjectId, in, m_clayer, "clayer");

//    in.ReadHandle(m_textstyle);
    BS_ARCHIVE(crc, OcDbObjectId, in, m_textstyle, "textstyle");

//    in.ReadHandle(m_celtype);
    BS_ARCHIVE(crc, OcDbObjectId, in, m_celtype, "celtype");

    // R2007+
    if(dwgVersion >= R2007) {
//        in.ReadHandle(m_cmaterial);
        BS_ARCHIVE(crc, OcDbObjectId, in, m_cmaterial, "cmaterial");
    }

    // commmon
//    in.ReadHandle(m_dimstyle);
    BS_ARCHIVE(crc, OcDbObjectId, in, m_dimstyle, "dimstyle");

//    in.ReadHandle(m_cmlstyle);
    BS_ARCHIVE(crc, OcDbObjectId, in, m_cmlstyle, "cmlstyle");

    // R2000+ only
    if(dwgVersion >= R2000) {
//        in >> (bitcode::BD&) m_psvpscale;
        BS_ARCHIVE(crc, bitcode::BD, in, m_psvpscale, "psvpscale");
    }

//    in >> (bitcode::BD3&) m_insbase;
    BS_ARCHIVE(crc, bitcode::BD3, in, m_insbase, "insbase");

//    in >> (bitcode::BD3&) m_extmin;
    BS_ARCHIVE(crc, bitcode::BD3, in, m_extmin, "extmin");

//    in >> (bitcode::BD3&) m_extmax;
    BS_ARCHIVE(crc, bitcode::BD3, in, m_extmax, "extmax");

//    in >> (bitcode::RD2&) m_limmin;
    BS_ARCHIVE(crc, bitcode::RD2, in, m_limmin, "limmin");

//    in >> (bitcode::RD2&) m_limmax;
    BS_ARCHIVE(crc, bitcode::RD2, in, m_limmax, "limmax");

//    in >> (bitcode::BD&) m_elevation;
    BS_ARCHIVE(crc, bitcode::BD, in, m_elevation, "elevation");

//    in >> (bitcode::BD3&) m_ucsorg;
    BS_ARCHIVE(crc, bitcode::BD3, in, m_ucsorg, "ucsorg");

//    in >> (bitcode::BD3&) m_ucsxdir;
    BS_ARCHIVE(crc, bitcode::BD3, in, m_ucsxdir, "ucsxdir");

//    in >> (bitcode::BD3&) m_ucsydir;
    BS_ARCHIVE(crc, bitcode::BD3, in, m_ucsydir, "ucsydir");

//    in.ReadHandle(m_ucsname);
    BS_ARCHIVE(crc, OcDbObjectId, in, m_ucsname, "ucsname");



    LOG(INFO) << "Drawing header variables decoding routine not "
              "fully implemented yet";
//    return OcApp::eOk;
    return OcApp::eNotImplemented;
}

DwgInArchive& operator>>(DwgInArchive& in, OcDbHeaderVars & dwgVars)
{
    ASSERT_ARCHIVE_NOT_LOADING;
    in.SetError(dwgVars.DecodeData(in));
    return in;
}

END_OCTAVARIUM_NS
