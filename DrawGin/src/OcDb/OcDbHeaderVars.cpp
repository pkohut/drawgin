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

    // common
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

    // common
    BS_ARCHIVE(crc, OcDbObjectId, in, m_currentVpId, "currentvpId");
    BS_ARCHIVE(crc, bitcode::B, in, m_dimaso, "dimaso");
    BS_ARCHIVE(crc, bitcode::B, in, m_dimsho, "dimsho");

    if(dwgVersion == R13 || dwgVersion == R14) {
        BS_ARCHIVE(crc, bitcode::B, in, m_dimsav, "dimsav");
    }

    // common
    BS_ARCHIVE(crc, bitcode::B, in, m_plinegen, "plinegen");
    BS_ARCHIVE(crc, bitcode::B, in, m_orthomode, "orthomode");
    BS_ARCHIVE(crc, bitcode::B, in, m_regenmode, "regenmode");
    BS_ARCHIVE(crc, bitcode::B, in, m_fillmode, "fillmode");
    BS_ARCHIVE(crc, bitcode::B, in, m_qtextmode, "qtextmode");
    BS_ARCHIVE(crc, bitcode::B, in, m_psltscale, "psltscale");
    BS_ARCHIVE(crc, bitcode::B, in, m_limcheck, "limcheck");

    if(dwgVersion == R13 || dwgVersion == R14) {
        BS_ARCHIVE(crc, bitcode::B, in, m_blipmode, "blipmode");
    }

    if(dwgVersion >= R2004) {
        BS_ARCHIVE(crc, bitcode::B, in, m_undocumented, "undocumented");
    }

    // common
    BS_ARCHIVE(crc, bitcode::B, in, m_usertimer, "usertimer");
    BS_ARCHIVE(crc, bitcode::B, in, m_skpoly, "skpoly");
    BS_ARCHIVE(crc, bitcode::B, in, m_angdir, "angdir");
    BS_ARCHIVE(crc, bitcode::B, in, m_splframe, "splframe");

    if(dwgVersion == R13 || dwgVersion == R14) {
        BS_ARCHIVE(crc, bitcode::B, in, m_attreq, "attreq");
        BS_ARCHIVE(crc, bitcode::B, in, m_attdia, "attdia");
    }

    // common
    BS_ARCHIVE(crc, bitcode::B, in, m_mirrtext, "mirrtext");
    BS_ARCHIVE(crc, bitcode::B, in, m_worldview, "worldview");

    if(dwgVersion == R13 || dwgVersion == R14) {
        BS_ARCHIVE(crc, bitcode::B, in, m_wireframe, "wireframe");
    }

    // common
    BS_ARCHIVE(crc, bitcode::B, in, m_tilemode, "tilemode");
    BS_ARCHIVE(crc, bitcode::B, in, m_plimcheck, "plimcheck");
    BS_ARCHIVE(crc, bitcode::B, in, m_visretain, "visretain");

    if(dwgVersion == R13 || dwgVersion == R14) {
        BS_ARCHIVE(crc, bitcode::B, in, m_delobj, "delobj");
    }

    // common
    BS_ARCHIVE(crc, bitcode::B, in, m_dispsilh, "dispsilh");
    BS_ARCHIVE(crc, bitcode::B, in, m_pellipse, "pellispe");
    BS_ARCHIVE(crc, bitcode::BS, in, m_saveimages, "saveimages");

    if(dwgVersion == R13 || dwgVersion == R14) {
        BS_ARCHIVE(crc, bitcode::BS, in, m_dimsav, "dimsav");
    }
    
    // common
    BS_ARCHIVE(crc, bitcode::BS, in, m_treedepth, "treedepth");
    BS_ARCHIVE(crc, bitcode::BS, in, m_lunits, "lunits");
    BS_ARCHIVE(crc, bitcode::BS, in, m_luprec, "luprec");
    BS_ARCHIVE(crc, bitcode::BS, in, m_aunits, "aunits");
    BS_ARCHIVE(crc, bitcode::BS, in, m_auprec, "auprec");

    if(dwgVersion == R13 || dwgVersion == R14) {
        BS_ARCHIVE(crc, bitcode::BS, in, m_osmode, "osmode");
    }

    // common
    BS_ARCHIVE(crc, bitcode::BS, in, m_attmode, "attmode");

    if(dwgVersion == R13 || dwgVersion == R14) {
        BS_ARCHIVE(crc, bitcode::BS, in, m_coords, "coords");
    }

    // common
    BS_ARCHIVE(crc, bitcode::BS, in, m_pdmode, "pdmode");

    if(dwgVersion == R13 || dwgVersion == R14) {
        BS_ARCHIVE(crc, bitcode::BS, in, m_pickstyle, "pickstyle");
    }

    if(dwgVersion >= R2004) {
        BS_ARCHIVE(crc, bitcode::BL, in, m_unknown12, "unknown12");
        BS_ARCHIVE(crc, bitcode::BL, in, m_unknown13, "unknown13");
        BS_ARCHIVE(crc, bitcode::BL, in, m_unknown14, "unknown14");
    }

    // common
    BS_ARCHIVE(crc, bitcode::BS, in, m_useri1, "useri1");
    BS_ARCHIVE(crc, bitcode::BS, in, m_useri2, "useri2");
    BS_ARCHIVE(crc, bitcode::BS, in, m_useri3, "useri3");
    BS_ARCHIVE(crc, bitcode::BS, in, m_useri4, "useri4");
    BS_ARCHIVE(crc, bitcode::BS, in, m_useri5, "useri5");
    BS_ARCHIVE(crc, bitcode::BS, in, m_splinesegs, "splinesegs");
    BS_ARCHIVE(crc, bitcode::BS, in, m_surfu, "surfu");
    BS_ARCHIVE(crc, bitcode::BS, in, m_surfv, "surfv");
    BS_ARCHIVE(crc, bitcode::BS, in, m_surftype, "surftype");
    BS_ARCHIVE(crc, bitcode::BS, in, m_surftab1, "surftab1");
    BS_ARCHIVE(crc, bitcode::BS, in, m_surftab2, "surftab2");
    BS_ARCHIVE(crc, bitcode::BS, in, m_splinetype, "splinetype");
    BS_ARCHIVE(crc, bitcode::BS, in, m_shadedge, "shadedge");
    BS_ARCHIVE(crc, bitcode::BS, in, m_shadedif, "shadedif");
    BS_ARCHIVE(crc, bitcode::BS, in, m_unitmode, "unitmode");
    BS_ARCHIVE(crc, bitcode::BS, in, m_maxactvp, "macactvp");
    BS_ARCHIVE(crc, bitcode::BS, in, m_isolines, "isolines");
    BS_ARCHIVE(crc, bitcode::BS, in, m_cmljust, "cmljust");
    BS_ARCHIVE(crc, bitcode::BS, in, m_textqlty, "textqlty");
    BS_ARCHIVE(crc, bitcode::BD, in, m_ltscale, "ltscale");
    BS_ARCHIVE(crc, bitcode::BD, in, m_textsize, "textsize");
    BS_ARCHIVE(crc, bitcode::BD, in, m_tracewid, "tracewid");
    BS_ARCHIVE(crc, bitcode::BD, in, m_sketchinc, "sketchinc");
    BS_ARCHIVE(crc, bitcode::BD, in, m_filletrad, "filletrad");
    BS_ARCHIVE(crc, bitcode::BD, in, m_thickness, "thickness");
    BS_ARCHIVE(crc, bitcode::BD, in, m_angbase, "angbase");
    BS_ARCHIVE(crc, bitcode::BD, in, m_pdsize, "pdsize");
    BS_ARCHIVE(crc, bitcode::BD, in, m_plinewid, "plinewid");
    BS_ARCHIVE(crc, bitcode::BD, in, m_userr1, "userr1");
    BS_ARCHIVE(crc, bitcode::BD, in, m_userr2, "userr2");
    BS_ARCHIVE(crc, bitcode::BD, in, m_userr3, "userr3");
    BS_ARCHIVE(crc, bitcode::BD, in, m_userr4, "userr4");
    BS_ARCHIVE(crc, bitcode::BD, in, m_userr5, "userr5");
    BS_ARCHIVE(crc, bitcode::BD, in, m_chamfera, "chamfera");
    BS_ARCHIVE(crc, bitcode::BD, in, m_chamferb, "chamferb");
    BS_ARCHIVE(crc, bitcode::BD, in, m_chamferc, "chamferc");
    BS_ARCHIVE(crc, bitcode::BD, in, m_chamferd, "chamferd");
    BS_ARCHIVE(crc, bitcode::BD, in, m_facetres, "facetres");
    BS_ARCHIVE(crc, bitcode::BD, in, m_cmlscale, "cmlscale");
    BS_ARCHIVE(crc, bitcode::BD, in, m_celtscale, "celtscale");
    BS_ARCHIVE(crc, bitcode::TV, in, m_menuname, "menuname");
    BS_ARCHIVE(crc, bitcode::BL, in, m_tdcreate_day, "tdcreate_day");
    BS_ARCHIVE(crc, bitcode::BL, in, m_tdcreate_ms, "tdcreate_ms");
    BS_ARCHIVE(crc, bitcode::BL, in, m_tdupdate_day, "tdupdate_day");
    BS_ARCHIVE(crc, bitcode::BL, in, m_tdupdate_ms, "tdupdate_ms");

    if(dwgVersion >= R2004) {
        BS_ARCHIVE(crc, bitcode::BL, in, m_unknown15, "unknown15");
        BS_ARCHIVE(crc, bitcode::BL, in, m_unknown16, "unknown16");
        BS_ARCHIVE(crc, bitcode::BL, in, m_unknown17, "unknown17");
    }

    // common
    BS_ARCHIVE(crc, bitcode::BL, in, m_tdindwg_days, "tdindwg_days");
    BS_ARCHIVE(crc, bitcode::BL, in, m_tdindwg_ms, "tdindwg_ms");
    BS_ARCHIVE(crc, bitcode::BL, in, m_tdusrtimer_days, "tdusrtimer_days");
    BS_ARCHIVE(crc, bitcode::BL, in, m_tdusrtimer_ms, "tdusrtimer_ms");
    BS_ARCHIVE(crc, bitcode::CMC, in, m_cecolor, "cecolor");
    BS_ARCHIVE(crc, OcDbObjectId, in, m_handseed, "handseed");
    BS_ARCHIVE(crc, OcDbObjectId, in, m_clayer, "clayer");
    BS_ARCHIVE(crc, OcDbObjectId, in, m_textstyle, "textstyle");
    BS_ARCHIVE(crc, OcDbObjectId, in, m_celtype, "celtype");

    // R2007+
    if(dwgVersion >= R2007) {
        BS_ARCHIVE(crc, OcDbObjectId, in, m_cmaterial, "cmaterial");
    }

    // commmon
    BS_ARCHIVE(crc, OcDbObjectId, in, m_dimstyle, "dimstyle");
    BS_ARCHIVE(crc, OcDbObjectId, in, m_cmlstyle, "cmlstyle");

    // R2000+ only
    if(dwgVersion >= R2000) {
        BS_ARCHIVE(crc, bitcode::BD, in, m_psvpscale, "psvpscale");
    }

    // common
    VLOG(4) << "****** Begin PS read *****";
    BS_ARCHIVE(crc, bitcode::BD3, in, m_pinsbase, "pinsbase");
    BS_ARCHIVE(crc, bitcode::BD3, in, m_pextmin, "pextmin");
    BS_ARCHIVE(crc, bitcode::BD3, in, m_pextmax, "pextmax");
    BS_ARCHIVE(crc, bitcode::RD2, in, m_plimmin, "plimmin");
    BS_ARCHIVE(crc, bitcode::RD2, in, m_plimmax, "plimmax");
    BS_ARCHIVE(crc, bitcode::BD, in, m_pelevation, "pelevation");
    BS_ARCHIVE(crc, bitcode::BD3, in, m_pucsorg, "pucsorg");
    BS_ARCHIVE(crc, bitcode::BD3, in, m_pucsxdir, "pucsxdir");
    BS_ARCHIVE(crc, bitcode::BD3, in, m_pucsydir, "pucsydir");
    BS_ARCHIVE(crc, OcDbObjectId, in, m_pucsname, "pucsname");

    if(dwgVersion >= R2000) {
        BS_ARCHIVE(crc, OcDbObjectId, in, m_pucsbase, "pucsbase");
        BS_ARCHIVE(crc, bitcode::BS, in, m_pucsorthoview, "pucsorthoview");
        BS_ARCHIVE(crc, OcDbObjectId, in, m_pucsorthoref, "pucsorthoref");
        BS_ARCHIVE(crc, bitcode::BD3, in, m_pucsorgtop, "pucsorgtop");
        BS_ARCHIVE(crc, bitcode::BD3, in, m_pucsorgbottom, "pucsorgbottom");
        BS_ARCHIVE(crc, bitcode::BD3, in, m_pucsorgleft, "pucsorgleft");
        BS_ARCHIVE(crc, bitcode::BD3, in, m_pucsorgright, "pucsorgright");
        BS_ARCHIVE(crc, bitcode::BD3, in, m_pucsorgfront, "pucsorgfront");
        BS_ARCHIVE(crc, bitcode::BD3, in, m_pucsorgback, "pucsorgback");
    }


    // common
    VLOG(4) << "****** Begin MS read *****";
    BS_ARCHIVE(crc, bitcode::BD3, in, m_insbase, "insbase");
    BS_ARCHIVE(crc, bitcode::BD3, in, m_extmin, "extmin");
    BS_ARCHIVE(crc, bitcode::BD3, in, m_extmax, "extmax");
    BS_ARCHIVE(crc, bitcode::RD2, in, m_limmin, "limmin");
    BS_ARCHIVE(crc, bitcode::RD2, in, m_limmax, "limmax");
    BS_ARCHIVE(crc, bitcode::BD, in, m_elevation, "elevation");
    BS_ARCHIVE(crc, bitcode::BD3, in, m_ucsorg, "ucsorg");
    BS_ARCHIVE(crc, bitcode::BD3, in, m_ucsxdir, "ucsxdir");
    BS_ARCHIVE(crc, bitcode::BD3, in, m_ucsydir, "ucsydir");
    BS_ARCHIVE(crc, OcDbObjectId, in, m_ucsname, "ucsname");

    if(dwgVersion >= R2000) {
        BS_ARCHIVE(crc, OcDbObjectId, in, m_ucsbase, "ucsbase");
        BS_ARCHIVE(crc, bitcode::BS, in, m_ucsorthoview, "ucsorthoview");
        BS_ARCHIVE(crc, OcDbObjectId, in, m_ucsorthoref, "ucsorthoref");
        BS_ARCHIVE(crc, bitcode::BD3, in, m_ucsorgtop, "ucsorgtop");
        BS_ARCHIVE(crc, bitcode::BD3, in, m_ucsorgbottom, "ucsorgbottom");
        BS_ARCHIVE(crc, bitcode::BD3, in, m_ucsorgleft, "ucsorgleft");
        BS_ARCHIVE(crc, bitcode::BD3, in, m_ucsorgright, "ucsorgright");
        BS_ARCHIVE(crc, bitcode::BD3, in, m_ucsorgfront, "ucsorgfront");
        BS_ARCHIVE(crc, bitcode::BD3, in, m_ucsorgback, "ucsorgback");
        BS_ARCHIVE(crc, bitcode::TV, in, m_dimpost, "dimpost");
        BS_ARCHIVE(crc, bitcode::TV, in, m_dimapost, "dimapost");
    }

    // common
    BS_ARCHIVE(crc, bitcode::B, in, m_dimtol, "dimtol");
    BS_ARCHIVE(crc, bitcode::B, in, m_dimlim, "dimlim");
    BS_ARCHIVE(crc, bitcode::B, in, m_dimtih, "dimtih");
    BS_ARCHIVE(crc, bitcode::B, in, m_dimtoh, "dimtoh");
    BS_ARCHIVE(crc, bitcode::B, in, m_dimse1, "dimse1");
    BS_ARCHIVE(crc, bitcode::B, in, m_dimse2, "dimse2");
    BS_ARCHIVE(crc, bitcode::B, in, m_dimalt, "dimalt");
    BS_ARCHIVE(crc, bitcode::B, in, m_dimtofl, "dimtofl");
    BS_ARCHIVE(crc, bitcode::B, in, m_dimsah, "dimsah");
    BS_ARCHIVE(crc, bitcode::B, in, m_dimtix, "dimtix");
    BS_ARCHIVE(crc, bitcode::B, in, m_dimsoxd, "dimsoxd");
    BS_ARCHIVE(crc, bitcode::RC, in, m_dimaltd, "dimaltd");
    BS_ARCHIVE(crc, bitcode::RC, in, m_dimzin, "dimzin");
    BS_ARCHIVE(crc, bitcode::B, in, m_dimsd1, "dimsd1");
    BS_ARCHIVE(crc, bitcode::B, in, m_dimsd2, "dimsd2");
    BS_ARCHIVE(crc, bitcode::RC, in, m_dimtolj, "dimtolj");
    BS_ARCHIVE(crc, bitcode::RC, in, m_dimjust, "dimjust");
    BS_ARCHIVE(crc, bitcode::RC, in, m_dimfit, "dimfit");
    BS_ARCHIVE(crc, bitcode::B, in, m_dimupt, "dimupt");
    BS_ARCHIVE(crc, bitcode::RC, in, m_dimtzin, "dimtzin");
    BS_ARCHIVE(crc, bitcode::RC, in, m_dimaltz, "dimaltz");
    BS_ARCHIVE(crc, bitcode::RC, in, m_dimalttz, "dimalttz");
    BS_ARCHIVE(crc, bitcode::RC, in, m_dimtad, "dimtad");
    BS_ARCHIVE(crc, bitcode::BS, in, m_dimunit, "dimunit");
    BS_ARCHIVE(crc, bitcode::BS, in, m_dimaunit, "dimaunit");
    BS_ARCHIVE(crc, bitcode::BS, in, m_dimdec, "dimdec");
    BS_ARCHIVE(crc, bitcode::BS, in, m_dimtdec, "dimtdec");
    BS_ARCHIVE(crc, bitcode::BS, in, m_dimaltu, "dimaltu");
    BS_ARCHIVE(crc, bitcode::BS, in, m_dimalttd, "dimalttd");
    BS_ARCHIVE(crc, OcDbObjectId, in, m_dimtxsty, "dimtxsty");



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
