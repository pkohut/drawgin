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

#include "OcCommon.h"
#include "OcTypes.h"
#include "OcError.h"
#include "OcDfDwgVersion.h"
#include "OcDbObjectId.h"
#include "OcDbHardOwnershipId.h"
#include "OcGePoint2D.h"
#include "OcGePoint3D.h"

#include "../OcBs/OcBsStreamIn.h"
#include "../OcBs/DwgInArchive.h"
#include "OcDfHeaderVars.h"
#include "../OcBs/OcBsDwgSentinels.h"



BEGIN_OCTAVARIUM_NS
using namespace std;

OcDfHeaderVars::OcDfHeaderVars(void)
:
m_unknown1(0.0), m_unknown2(0.0), m_unknown3(0.0), m_unknown4(0.0),
m_unknown9(0), m_unknown10(0), m_unknown11(0), m_dimaso(false),
m_dimsho(false), m_dimsav(false), m_plinegen(false), m_orthomode(false),
m_regenmode(false), m_fillmode(false), m_qtextmode(false),
m_psltscale(false), m_limcheck(false), m_blipmode(false),
m_undocumented(false), m_usertimer(false), m_skpoly(false),
m_angdir(false), m_splframe(false), m_attreq(false), m_attdia(false),
m_mirrtext(false), m_worldview(false), m_wireframe(false),
m_tilemode(false), m_plimcheck(false), m_visretain(false), m_delobj(false),
m_dispsilh(false), m_pellipse(false),
m_saveimages(0), m_dragmode(0), m_treedepth(0), m_lunits(0), m_luprec(0),
m_aunits(0), m_auprec(0), m_osmode(0), m_attmode(0), m_coords(0),
m_pdmode(0), m_pickstyle(0), m_unknown12(0), m_unknown13(0),m_unknown14(0),
m_useri1(0), m_useri2(0), m_useri3(0), m_useri4(0), m_useri5(0),
m_splinesegs(0), m_surfu(0), m_surfv(0), m_surftype(0), m_surftab1(0),
m_surftab2(0), m_splinetype(0), m_shadedge(0), m_shadedif(0),
m_unitmode(0), m_maxactvp(0), m_isolines(0), m_cmljust(0), m_textqlty(0),
m_ltscale(0.0), m_textsize(0.0), m_tracewid(0.0), m_sketchinc(0.0),
m_filletrad(0.0), m_thickness(0.0), m_angbase(0.0), m_pdsize(0.0),
m_plinewid(0.0), m_userr1(0.0), m_userr2(0.0), m_userr3(0.0),
m_userr4(0.0), m_userr5(0.0), m_chamfera(0.0), m_chamferb(0.0),
m_chamferc(0.0), m_chamferd(0.0), m_facetres(0.0), m_cmlscale(0.0),
m_celtscale(0.0), m_tdcreate_day(0), m_tdcreate_ms(0), m_tdupdate_day(0),
m_tdupdate_ms(0), m_unknown15(0), m_unknown16(0), m_unknown17(0),
m_tdindwg_days(0), m_tdindwg_ms(0), m_tdusrtimer_days(0), m_tdusrtimer_ms(0),
m_psvpscale(0.0), m_pelevation(0.0), m_pucsorthoview(0), m_elevation(0.0),
m_ucsorthoview(0),
m_dimtol(false), m_dimlim(false), m_dimtih(false), m_dimtoh(false),
m_dimse1(false), m_dimse2(false), m_dimalt(false), m_dimtofl(false),
m_dimsah(false), m_dimtix(false), m_dimsoxd(false),
m_dimaltd(0), m_dimzin(0), m_dimsd1(false), m_dimsd2(false),
m_dimtolj(0), m_dimjust(0), m_dimfit(0), m_dimupt(false), m_dimtzin(0),
m_dimaltz(0), m_dimalttz(0), m_dimtad(0), m_dimunit(0), m_dimaunit(0),
m_dimdec(0), m_dimtdec(0), m_dimaltu(0), m_dimalttd(0),
m_dimscale(0.0), m_dimasz(0.0), m_dimexo(0.0), m_dimdli(0.0),
m_dimexe(0.0), m_dimrnd(0.0), m_dimdle(0.0), m_dimtp(0.0),
m_dimtm(0.0), m_dimfxl(0.0), m_dimjogang(0.0), m_dimtfill(0),
m_dimazin(0), m_dimarcsym(0),
m_dimtxt(0.0), m_dimcen(0.0), m_dimtsz(0.0), m_dimaltf(0.0),
m_dimlfac(0.0), m_dimtvp(0.0), m_dimtfac(0.0), m_dimgap(0.0),
m_dimaltrnd(0.0), m_dimadec(0), m_dimfrac(0), m_dimlunit(0),
m_dimdsep(0), m_dimtmove(0), m_dimatfit(0), m_dimfxlon(false),
m_dimlwd(0), m_dimlwe(0), m_tstackalign(0), m_tstacksize(0),
m_flags(0), m_insunits(0), m_cepsntype(0),
m_sortents(0), m_indexctl(0), m_hidetext(0), m_xclipframe(0),
m_dimassoc(0), m_halogap(0), m_obscuredcolor(0), m_intersectioncolor(0),
m_obscuredltype(0), m_intersectiondisplay(0),
m_cameradisplay(false), m_unknown21(0), m_unknown22(0),
m_unknown23(0.0), m_stepspersec(0.0), m_stepsize(0.0), m_3ddwfprec(0.0),
m_lenslength(0.0), m_cameraheight(0.0), m_solidhist(0), m_showhist(0),
m_psolwidth(0.0), m_psolheight(0.0), m_loftang1(0.0), m_loftang2(0.0),
m_loftmag1(0.0), m_logtmag2(0.0), m_loftparam(0), m_loftnormals(0),
m_latitude(0.0), m_longitude(0.0), m_northdirection(0.0),
m_timezone(0), m_lightglyphdisplay(0), m_tilemodelightsynch(0),
m_dwfframe(0), m_dgnframe(0), m_unknown47(false), m_cshadow(0),
m_unknown53(0.0), m_unknown54(0), m_unknown55(0),
m_unknown56(0), m_unknown57(0), m_crc(0)

{
    VLOG(3) << "Constructor entered";
}

OcDfHeaderVars::~OcDfHeaderVars(void)
{
    VLOG(3) << "Destructor entered";
}

OcApp::ErrorStatus OcDfHeaderVars::DecodeData(DwgInArchive& in)
{
    VLOG(3) << "DecodeData entered";
    ASSERT_ARCHIVE_NOT_LOADING(in);

    // match dwg header variables start sentinel
    bitcode::RC sentinelData[16];
    in.ReadRC(sentinelData, 16);
    if(!CompareSentinels(sentinelHeaderVarsStart, sentinelData)) {
        return OcApp::eInvalidImageDataSentinel;
    }

    const DWG_VERSION dwgVersion = in.Version();

    // per spec, set initial CRC value to 0xc0c1
    in.SetCalcedCRC(0xc0c1);

    // spec says this is a R2007 variable only and is the size in "bits",
    // but that doesn't totally correct.
    // At least for the R2008 drawing down converted to R14, this value
    // appears to be the size of the header in "bytes".
    //   if(dwgVersion == R2007) {
    //    Archive<bitcode::RL>(in, size, "Header variables size");
    int size;
    BS_ARCHIVE(bitcode::RL, in, size, "Header variables size");
    //    }

    size_t startPos = in.FilePosition();

    // common
    BS_ARCHIVE(bitcode::BD, in, m_unknown1,  "unknown1");
    BS_ARCHIVE(bitcode::BD, in, m_unknown2,  "unknown2");
    BS_ARCHIVE(bitcode::BD, in, m_unknown3,  "unknown3");
    BS_ARCHIVE(bitcode::BD, in, m_unknown4,  "unknown4");
    BS_ARCHIVE(bitcode::TV, in, m_unknown5,  "unknown5");
    BS_ARCHIVE(bitcode::TV, in, m_unknown6,  "unknown6");
    BS_ARCHIVE(bitcode::TV, in, m_unknown7,  "unknown7");
    BS_ARCHIVE(bitcode::TV, in, m_unknown8,  "unknown8");
    BS_ARCHIVE(bitcode::BL, in, m_unknown9,  "unknown9");
    BS_ARCHIVE(bitcode::BL, in, m_unknown10, "unknown10");

    if(dwgVersion == R13 || dwgVersion == R14) {
        BS_ARCHIVE(bitcode::BS, in, m_unknown11, "unknown11");
    }

    // common
    BS_ARCHIVE(OcDbObjectId, in, m_currentVpId, "currentvpId");
    BS_ARCHIVE(bitcode::B, in, m_dimaso,        "dimaso");
    BS_ARCHIVE(bitcode::B, in, m_dimsho,        "dimsho");

    if(dwgVersion == R13 || dwgVersion == R14) {
        BS_ARCHIVE(bitcode::B, in, m_dimsav, "dimsav");
    }

    // common
    BS_ARCHIVE(bitcode::B, in, m_plinegen,  "plinegen");
    BS_ARCHIVE(bitcode::B, in, m_orthomode, "orthomode");
    BS_ARCHIVE(bitcode::B, in, m_regenmode, "regenmode");
    BS_ARCHIVE(bitcode::B, in, m_fillmode,  "fillmode");
    BS_ARCHIVE(bitcode::B, in, m_qtextmode, "qtextmode");
    BS_ARCHIVE(bitcode::B, in, m_psltscale, "psltscale");
    BS_ARCHIVE(bitcode::B, in, m_limcheck,  "limcheck");

    if(dwgVersion == R13 || dwgVersion == R14) {
        BS_ARCHIVE(bitcode::B, in, m_blipmode, "blipmode");
    }

    if(dwgVersion >= R2004) {
        BS_ARCHIVE(bitcode::B, in, m_undocumented, "undocumented");
    }

    // common
    BS_ARCHIVE(bitcode::B, in, m_usertimer, "usertimer");
    BS_ARCHIVE(bitcode::B, in, m_skpoly,    "skpoly");
    BS_ARCHIVE(bitcode::B, in, m_angdir,    "angdir");
    BS_ARCHIVE(bitcode::B, in, m_splframe,  "splframe");

    if(dwgVersion == R13 || dwgVersion == R14) {
        BS_ARCHIVE(bitcode::B, in, m_attreq, "attreq");
        BS_ARCHIVE(bitcode::B, in, m_attdia, "attdia");
    }

    // common
    BS_ARCHIVE(bitcode::B, in, m_mirrtext,  "mirrtext");
    BS_ARCHIVE(bitcode::B, in, m_worldview, "worldview");

    if(dwgVersion == R13 || dwgVersion == R14) {
        BS_ARCHIVE(bitcode::B, in, m_wireframe, "wireframe");
    }

    // common
    BS_ARCHIVE(bitcode::B, in, m_tilemode,  "tilemode");
    BS_ARCHIVE(bitcode::B, in, m_plimcheck, "plimcheck");
    BS_ARCHIVE(bitcode::B, in, m_visretain, "visretain");

    if(dwgVersion == R13 || dwgVersion == R14) {
        BS_ARCHIVE(bitcode::B, in, m_delobj, "delobj");
    }

    // common
    BS_ARCHIVE(bitcode::B, in, m_dispsilh,    "dispsilh");
    BS_ARCHIVE(bitcode::B, in, m_pellipse,    "pellispe");
    BS_ARCHIVE(bitcode::BS, in, m_saveimages, "saveimages");

    if(dwgVersion == R13 || dwgVersion == R14) {
        BS_ARCHIVE(bitcode::BS, in, m_dimsav, "dimsav");
    }

    // common
    BS_ARCHIVE(bitcode::BS, in, m_treedepth, "treedepth");
    BS_ARCHIVE(bitcode::BS, in, m_lunits,    "lunits");
    BS_ARCHIVE(bitcode::BS, in, m_luprec,    "luprec");
    BS_ARCHIVE(bitcode::BS, in, m_aunits,    "aunits");
    BS_ARCHIVE(bitcode::BS, in, m_auprec,    "auprec");

    if(dwgVersion == R13 || dwgVersion == R14) {
        BS_ARCHIVE(bitcode::BS, in, m_osmode, "osmode");
    }

    // common
    BS_ARCHIVE(bitcode::BS, in, m_attmode, "attmode");

    if(dwgVersion == R13 || dwgVersion == R14) {
        BS_ARCHIVE(bitcode::BS, in, m_coords, "coords");
    }

    // common
    BS_ARCHIVE(bitcode::BS, in, m_pdmode, "pdmode");

    if(dwgVersion == R13 || dwgVersion == R14) {
        BS_ARCHIVE(bitcode::BS, in, m_pickstyle, "pickstyle");
    }

    if(dwgVersion >= R2004) {
        BS_ARCHIVE(bitcode::BL, in, m_unknown12, "unknown12");
        BS_ARCHIVE(bitcode::BL, in, m_unknown13, "unknown13");
        BS_ARCHIVE(bitcode::BL, in, m_unknown14, "unknown14");
    }

    // common
    BS_ARCHIVE(bitcode::BS, in, m_useri1,       "useri1");
    BS_ARCHIVE(bitcode::BS, in, m_useri2,       "useri2");
    BS_ARCHIVE(bitcode::BS, in, m_useri3,       "useri3");
    BS_ARCHIVE(bitcode::BS, in, m_useri4,       "useri4");
    BS_ARCHIVE(bitcode::BS, in, m_useri5,       "useri5");
    BS_ARCHIVE(bitcode::BS, in, m_splinesegs,   "splinesegs");
    BS_ARCHIVE(bitcode::BS, in, m_surfu,        "surfu");
    BS_ARCHIVE(bitcode::BS, in, m_surfv,        "surfv");
    BS_ARCHIVE(bitcode::BS, in, m_surftype,     "surftype");
    BS_ARCHIVE(bitcode::BS, in, m_surftab1,     "surftab1");
    BS_ARCHIVE(bitcode::BS, in, m_surftab2,     "surftab2");
    BS_ARCHIVE(bitcode::BS, in, m_splinetype,   "splinetype");
    BS_ARCHIVE(bitcode::BS, in, m_shadedge,     "shadedge");
    BS_ARCHIVE(bitcode::BS, in, m_shadedif,     "shadedif");
    BS_ARCHIVE(bitcode::BS, in, m_unitmode,     "unitmode");
    BS_ARCHIVE(bitcode::BS, in, m_maxactvp,     "macactvp");
    BS_ARCHIVE(bitcode::BS, in, m_isolines,     "isolines");
    BS_ARCHIVE(bitcode::BS, in, m_cmljust,      "cmljust");
    BS_ARCHIVE(bitcode::BS, in, m_textqlty,     "textqlty");
    BS_ARCHIVE(bitcode::BD, in, m_ltscale,      "ltscale");
    BS_ARCHIVE(bitcode::BD, in, m_textsize,     "textsize");
    BS_ARCHIVE(bitcode::BD, in, m_tracewid,     "tracewid");
    BS_ARCHIVE(bitcode::BD, in, m_sketchinc,    "sketchinc");
    BS_ARCHIVE(bitcode::BD, in, m_filletrad,    "filletrad");
    BS_ARCHIVE(bitcode::BD, in, m_thickness,    "thickness");
    BS_ARCHIVE(bitcode::BD, in, m_angbase,      "angbase");
    BS_ARCHIVE(bitcode::BD, in, m_pdsize,       "pdsize");
    BS_ARCHIVE(bitcode::BD, in, m_plinewid,     "plinewid");
    BS_ARCHIVE(bitcode::BD, in, m_userr1,       "userr1");
    BS_ARCHIVE(bitcode::BD, in, m_userr2,       "userr2");
    BS_ARCHIVE(bitcode::BD, in, m_userr3,       "userr3");
    BS_ARCHIVE(bitcode::BD, in, m_userr4,       "userr4");
    BS_ARCHIVE(bitcode::BD, in, m_userr5,       "userr5");
    BS_ARCHIVE(bitcode::BD, in, m_chamfera,     "chamfera");
    BS_ARCHIVE(bitcode::BD, in, m_chamferb,     "chamferb");
    BS_ARCHIVE(bitcode::BD, in, m_chamferc,     "chamferc");
    BS_ARCHIVE(bitcode::BD, in, m_chamferd,     "chamferd");
    BS_ARCHIVE(bitcode::BD, in, m_facetres,     "facetres");
    BS_ARCHIVE(bitcode::BD, in, m_cmlscale,     "cmlscale");
    BS_ARCHIVE(bitcode::BD, in, m_celtscale,    "celtscale");
    BS_ARCHIVE(bitcode::TV, in, m_menuname,     "menuname");
    BS_ARCHIVE(bitcode::BL, in, m_tdcreate_day, "tdcreate_day");
    BS_ARCHIVE(bitcode::BL, in, m_tdcreate_ms,  "tdcreate_ms");
    BS_ARCHIVE(bitcode::BL, in, m_tdupdate_day, "tdupdate_day");
    BS_ARCHIVE(bitcode::BL, in, m_tdupdate_ms,  "tdupdate_ms");

    if(dwgVersion >= R2004) {
        BS_ARCHIVE(bitcode::BL, in, m_unknown15, "unknown15");
        BS_ARCHIVE(bitcode::BL, in, m_unknown16, "unknown16");
        BS_ARCHIVE(bitcode::BL, in, m_unknown17, "unknown17");
    }

    // common
    BS_ARCHIVE(bitcode::BL, in, m_tdindwg_days,    "tdindwg_days");
    BS_ARCHIVE(bitcode::BL, in, m_tdindwg_ms,      "tdindwg_ms");
    BS_ARCHIVE(bitcode::BL, in, m_tdusrtimer_days, "tdusrtimer_days");
    BS_ARCHIVE(bitcode::BL, in, m_tdusrtimer_ms,   "tdusrtimer_ms");
    BS_ARCHIVE(bitcode::CMC, in, m_cecolor,        "cecolor");
    BS_ARCHIVE(OcDbObjectId, in, m_handseed,       "handseed");
    BS_ARCHIVE(OcDbObjectId, in, m_clayer,         "clayer");
    BS_ARCHIVE(OcDbObjectId, in, m_textstyle,      "textstyle");
    BS_ARCHIVE(OcDbObjectId, in, m_celtype,        "celtype");

    // R2007+
    if(dwgVersion >= R2007) {
        BS_ARCHIVE(OcDbObjectId, in, m_cmaterial, "cmaterial");
    }

    // commmon
    BS_ARCHIVE(OcDbObjectId, in, m_dimstyle, "dimstyle");
    BS_ARCHIVE(OcDbObjectId, in, m_cmlstyle, "cmlstyle");

    // R2000+ only
    if(dwgVersion >= R2000) {
        BS_ARCHIVE(bitcode::BD, in, m_psvpscale, "psvpscale");
    }

    // common
    VLOG(4) << "****** Begin PS read *****";
    BS_ARCHIVE(bitcode::BD3, in, m_pinsbase,  "pinsbase");
    BS_ARCHIVE(bitcode::BD3, in, m_pextmin,   "pextmin");
    BS_ARCHIVE(bitcode::BD3, in, m_pextmax,   "pextmax");
    BS_ARCHIVE(bitcode::RD2, in, m_plimmin,   "plimmin");
    BS_ARCHIVE(bitcode::RD2, in, m_plimmax,   "plimmax");
    BS_ARCHIVE(bitcode::BD, in, m_pelevation, "pelevation");
    BS_ARCHIVE(bitcode::BD3, in, m_pucsorg,   "pucsorg");
    BS_ARCHIVE(bitcode::BD3, in, m_pucsxdir,  "pucsxdir");
    BS_ARCHIVE(bitcode::BD3, in, m_pucsydir,  "pucsydir");
    BS_ARCHIVE(OcDbObjectId, in, m_pucsname,  "pucsname");

    if(dwgVersion >= R2000) {
        BS_ARCHIVE(OcDbObjectId, in, m_pucsbase,      "pucsbase");
        BS_ARCHIVE(bitcode::BS, in, m_pucsorthoview,  "pucsorthoview");
        BS_ARCHIVE(OcDbObjectId, in, m_pucsorthoref,  "pucsorthoref");
        BS_ARCHIVE(bitcode::BD3, in, m_pucsorgtop,    "pucsorgtop");
        BS_ARCHIVE(bitcode::BD3, in, m_pucsorgbottom, "pucsorgbottom");
        BS_ARCHIVE(bitcode::BD3, in, m_pucsorgleft,   "pucsorgleft");
        BS_ARCHIVE(bitcode::BD3, in, m_pucsorgright,  "pucsorgright");
        BS_ARCHIVE(bitcode::BD3, in, m_pucsorgfront,  "pucsorgfront");
        BS_ARCHIVE(bitcode::BD3, in, m_pucsorgback,   "pucsorgback");
    }


    // common
    VLOG(4) << "****** Begin MS read *****";
    BS_ARCHIVE(bitcode::BD3, in, m_insbase,  "insbase");
    BS_ARCHIVE(bitcode::BD3, in, m_extmin,   "extmin");
    BS_ARCHIVE(bitcode::BD3, in, m_extmax,   "extmax");
    BS_ARCHIVE(bitcode::RD2, in, m_limmin,   "limmin");
    BS_ARCHIVE(bitcode::RD2, in, m_limmax,   "limmax");
    BS_ARCHIVE(bitcode::BD, in, m_elevation, "elevation");
    BS_ARCHIVE(bitcode::BD3, in, m_ucsorg,   "ucsorg");
    BS_ARCHIVE(bitcode::BD3, in, m_ucsxdir,  "ucsxdir");
    BS_ARCHIVE(bitcode::BD3, in, m_ucsydir,  "ucsydir");
    BS_ARCHIVE(OcDbObjectId, in, m_ucsname,  "ucsname");

    if(dwgVersion >= R2000) {
        BS_ARCHIVE(OcDbObjectId, in, m_ucsbase,      "ucsbase");
        BS_ARCHIVE(bitcode::BS, in, m_ucsorthoview,  "ucsorthoview");
        BS_ARCHIVE(OcDbObjectId, in, m_ucsorthoref,  "ucsorthoref");
        BS_ARCHIVE(bitcode::BD3, in, m_ucsorgtop,    "ucsorgtop");
        BS_ARCHIVE(bitcode::BD3, in, m_ucsorgbottom, "ucsorgbottom");
        BS_ARCHIVE(bitcode::BD3, in, m_ucsorgleft,   "ucsorgleft");
        BS_ARCHIVE(bitcode::BD3, in, m_ucsorgright,  "ucsorgright");
        BS_ARCHIVE(bitcode::BD3, in, m_ucsorgfront,  "ucsorgfront");
        BS_ARCHIVE(bitcode::BD3, in, m_ucsorgback,   "ucsorgback");
        BS_ARCHIVE(bitcode::TV, in, m_dimpost,       "dimpost");
        BS_ARCHIVE(bitcode::TV, in, m_dimapost,      "dimapost");
    }

    if(dwgVersion == R13 || dwgVersion == R14) {
        BS_ARCHIVE(bitcode::B, in, m_dimtol,     "dimtol");
        BS_ARCHIVE(bitcode::B, in, m_dimlim,     "dimlim");
        BS_ARCHIVE(bitcode::B, in, m_dimtih,     "dimtih");
        BS_ARCHIVE(bitcode::B, in, m_dimtoh,     "dimtoh");
        BS_ARCHIVE(bitcode::B, in, m_dimse1,     "dimse1");
        BS_ARCHIVE(bitcode::B, in, m_dimse2,     "dimse2");
        BS_ARCHIVE(bitcode::B, in, m_dimalt,     "dimalt");
        BS_ARCHIVE(bitcode::B, in, m_dimtofl,    "dimtofl");
        BS_ARCHIVE(bitcode::B, in, m_dimsah,     "dimsah");
        BS_ARCHIVE(bitcode::B, in, m_dimtix,     "dimtix");
        BS_ARCHIVE(bitcode::B, in, m_dimsoxd,    "dimsoxd");
        BS_ARCHIVE(bitcode::RC, in, m_dimaltd,   "dimaltd");
        BS_ARCHIVE(bitcode::RC, in, m_dimzin,    "dimzin");
        BS_ARCHIVE(bitcode::B, in, m_dimsd1,     "dimsd1");
        BS_ARCHIVE(bitcode::B, in, m_dimsd2,     "dimsd2");
        BS_ARCHIVE(bitcode::RC, in, m_dimtolj,   "dimtolj");
        BS_ARCHIVE(bitcode::RC, in, m_dimjust,   "dimjust");
        BS_ARCHIVE(bitcode::RC, in, m_dimfit,    "dimfit");
        BS_ARCHIVE(bitcode::B, in, m_dimupt,     "dimupt");
        BS_ARCHIVE(bitcode::RC, in, m_dimtzin,   "dimtzin");
        BS_ARCHIVE(bitcode::RC, in, m_dimaltz,   "dimaltz");
        BS_ARCHIVE(bitcode::RC, in, m_dimalttz,  "dimalttz");
        BS_ARCHIVE(bitcode::RC, in, m_dimtad,    "dimtad");
        BS_ARCHIVE(bitcode::BS, in, m_dimunit,   "dimunit");
        BS_ARCHIVE(bitcode::BS, in, m_dimaunit,  "dimaunit");
        BS_ARCHIVE(bitcode::BS, in, m_dimdec,    "dimdec");
        BS_ARCHIVE(bitcode::BS, in, m_dimtdec,   "dimtdec");
        BS_ARCHIVE(bitcode::BS, in, m_dimaltu,   "dimaltu");
        BS_ARCHIVE(bitcode::BS, in, m_dimalttd,  "dimalttd");
        BS_ARCHIVE(OcDbObjectId, in, m_dimtxsty, "dimtxsty");
    }

////////////////////////////////////////////////////////////////////////////
// common
    BS_ARCHIVE(bitcode::BD, in, m_dimscale, "dimscale")
    BS_ARCHIVE(bitcode::BD, in, m_dimasz,   "dimasz");
    BS_ARCHIVE(bitcode::BD, in, m_dimexo,   "dimexo");
    BS_ARCHIVE(bitcode::BD, in, m_dimdli,   "dimdli");
    BS_ARCHIVE(bitcode::BD, in, m_dimexe,   "dimexe");
    BS_ARCHIVE(bitcode::BD, in, m_dimrnd,   "dimrnd");
    BS_ARCHIVE(bitcode::BD, in, m_dimdle,   "dimdle");
    BS_ARCHIVE(bitcode::BD, in, m_dimtp,    "dimtp");
    BS_ARCHIVE(bitcode::BD, in, m_dimtm,    "dimtm");

// R2007+
    if(dwgVersion >= R2007) {
        BS_ARCHIVE(bitcode::BD, in,  m_dimfxl,      "dimfxl");
        BS_ARCHIVE(bitcode::BD, in,  m_dimjogang,   "dimjogang");
        BS_ARCHIVE(bitcode::BS, in,  m_dimtfill,    "dimtfill");
        BS_ARCHIVE(bitcode::CMC, in, m_dimtfillclr, "dimtfillclr");
    }

// R2000+
    if(dwgVersion >= R2000) {
        BS_ARCHIVE(bitcode::B, in,  m_dimtol,  "dimtol");
        BS_ARCHIVE(bitcode::B, in,  m_dimlim,  "dimlim");
        BS_ARCHIVE(bitcode::B, in,  m_dimtih,  "dimtih");
        BS_ARCHIVE(bitcode::B, in,  m_dimtoh,  "dimtoh");
        BS_ARCHIVE(bitcode::B, in,  m_dimse1,  "dimse1");
        BS_ARCHIVE(bitcode::B, in,  m_dimse2,  "dimse2");
        BS_ARCHIVE(bitcode::BS, in, m_dimtad,  "dimtad");
        BS_ARCHIVE(bitcode::BS, in, m_dimzin,  "dimzin");
        BS_ARCHIVE(bitcode::BS, in, m_dimazin, "dimazin");
    }

// R2007+
    if(dwgVersion >= R2007) {
        BS_ARCHIVE(bitcode::BS, in, m_dimarcsym, "dimarcsym");
    }

// common
    BS_ARCHIVE(bitcode::BD, in, m_dimtxt,  "dimtxt");
    BS_ARCHIVE(bitcode::BD, in, m_dimcen,  "dimcen");
    BS_ARCHIVE(bitcode::BD, in, m_dimtsz,  "dimtsz");
    BS_ARCHIVE(bitcode::BD, in, m_dimaltf, "dimaltf");
    BS_ARCHIVE(bitcode::BD, in, m_dimlfac, "dimlfac");
    BS_ARCHIVE(bitcode::BD, in, m_dimtvp,  "dimtvp");
    BS_ARCHIVE(bitcode::BD, in, m_dimtfac, "dimtfac");
    BS_ARCHIVE(bitcode::BD, in, m_dimgap,  "dimgap");

// R13-R14
    if(dwgVersion == R13 || dwgVersion == R14) {
        BS_ARCHIVE(bitcode::T, in, m_dimpost,  "dimpost");
        BS_ARCHIVE(bitcode::T, in, m_dimapost, "dimapost");
        BS_ARCHIVE(bitcode::T, in, m_dimblk,   "dimblk");
        BS_ARCHIVE(bitcode::T, in, m_dimblk1,  "dimblk1");
        BS_ARCHIVE(bitcode::T, in, m_dimblk2,  "dimblk2");
    }

// R2000+
    if(dwgVersion >= R2000) {
        BS_ARCHIVE(bitcode::BD, in, m_dimaltrnd, "dimaltrnd");
        BS_ARCHIVE(bitcode::B,  in, m_dimalt,    "dimalt");
        BS_ARCHIVE(bitcode::BS, in, m_dimaltd,   "dimaltd");
        BS_ARCHIVE(bitcode::B,  in, m_dimtofl,   "dimtofl");
        BS_ARCHIVE(bitcode::B,  in, m_dimsah,    "dimsah");
        BS_ARCHIVE(bitcode::B,  in, m_dimtix,    "dimtix");
        BS_ARCHIVE(bitcode::B,  in, m_dimsoxd,   "dimsoxd");
    }

// common
    BS_ARCHIVE(bitcode::CMC, in, m_dimclrd, "dimclrd");
    BS_ARCHIVE(bitcode::CMC, in, m_dimclre, "dimclre");
    BS_ARCHIVE(bitcode::CMC, in, m_dimclrt, "dimclrt");

// R2000+
    if(dwgVersion >= R2000) {
        BS_ARCHIVE(bitcode::BS, in, m_dimadec,  "dimadec");
        BS_ARCHIVE(bitcode::BS, in, m_dimdec,   "dimdec");
        BS_ARCHIVE(bitcode::BS, in, m_dimtdec,  "dimtdec");
        BS_ARCHIVE(bitcode::BS, in, m_dimaltu,  "dimaltu");
        BS_ARCHIVE(bitcode::BS, in, m_dimalttd, "dimalttd");
        BS_ARCHIVE(bitcode::BS, in, m_dimaunit, "dimaunit");
        BS_ARCHIVE(bitcode::BS, in, m_dimfrac,  "dimfrac");
        BS_ARCHIVE(bitcode::BS, in, m_dimlunit, "dimlunit");
        BS_ARCHIVE(bitcode::BS, in, m_dimdsep,  "dimdsep");
        BS_ARCHIVE(bitcode::BS, in, m_dimtmove, "dimtmove");
        BS_ARCHIVE(bitcode::BS, in, m_dimjust,  "dimjust");
        BS_ARCHIVE(bitcode::B,  in, m_dimsd1,   "dimsd1");
        BS_ARCHIVE(bitcode::B,  in, m_dimsd2,   "dimsd2");
        BS_ARCHIVE(bitcode::BS, in, m_dimtolj,  "dimtolj");
        BS_ARCHIVE(bitcode::BS, in, m_dimtzin,  "dimtzin");
        BS_ARCHIVE(bitcode::BS, in, m_dimaltz,  "dimaltz");
        BS_ARCHIVE(bitcode::BS, in, m_dimalttz, "dimalttz");
        BS_ARCHIVE(bitcode::B,  in, m_dimupt,   "dimupt");
        BS_ARCHIVE(bitcode::BS, in, m_dimatfit, "dimatfit");
    }

// R2007+
    if(dwgVersion >= R2007) {
        BS_ARCHIVE(bitcode::B, in, m_dimfxlon, "dimfxlog");
    }

    if(dwgVersion >= R2010) {
//        BS_ARCHIVE(bitcode::B,  in, m_dimtxtdirection, "dimtxtdirection");
//        BS_ARCHIVE(bitcode::BD, in, m_dimaltmzf,       "dimaltmzf");
//        BS_ARCHIVE(bitcode::T,  in, m_dimaltmzs,       "dimaltmzs");
//        BS_ARCHIVE(bitcode::BD, in, m_dimmzf,          "dimmzf");
//        BS_ARCHIVE(bitcode::T,  in, m_dimmzs,          "dimmzs");
    }

// R2000+
    if(dwgVersion >= R2000) {
        BS_ARCHIVE(OcDbObjectId, in, m_dimtxsty,  "dimtxsty");
        BS_ARCHIVE(OcDbObjectId, in, m_dimldrblk, "dimldrblk");
        BS_ARCHIVE(OcDbObjectId, in, m_dimblkId,  "dimblkId");
        BS_ARCHIVE(OcDbObjectId, in, m_dimblk1Id, "dimblk1Id");
        BS_ARCHIVE(OcDbObjectId, in, m_dimblk2Id, "dimblk2Id");
    }

// R2007+
    if(dwgVersion >= R2007) {
        BS_ARCHIVE(OcDbObjectId, in, m_dimltype,  "dimltype");
        BS_ARCHIVE(OcDbObjectId, in, m_dimltex1,  "dimltex1");
        BS_ARCHIVE(OcDbObjectId, in, m_dimltex2,  "dimltex2");
    }

// R2000+
    if(dwgVersion >= R2000) {
        BS_ARCHIVE(bitcode::BS, in, m_dimlwd, "dimlwd");
        BS_ARCHIVE(bitcode::BS, in, m_dimlwe, "dimlwe");
    }

// common
    BS_ARCHIVE(OcDbObjectId, in, m_blockCtrlId,    "blockCtrlId");  // CONTROL OBJECT
    BS_ARCHIVE(OcDbObjectId, in, m_layerCtrlId,    "layerCtrlId");    // CONTROL OBJECT
    BS_ARCHIVE(OcDbObjectId, in, m_styleCtrlId,    "styleCtrlId");    // CONTROL OBJECT
    BS_ARCHIVE(OcDbObjectId, in, m_linetypeCtrlId, "linetypeCtrlId"); // CONTROL OBJECT
    BS_ARCHIVE(OcDbObjectId, in, m_viewCtrlId,     "viewCtrlId");     // CONTROL OBJECT
    BS_ARCHIVE(OcDbObjectId, in, m_ucsCtrlId,      "ucsCtrlId");      // CONTROL OBJECT
    BS_ARCHIVE(OcDbObjectId, in, m_vportCtrlId,    "vportCtrlId");    // CONTROL OBJECT
    BS_ARCHIVE(OcDbObjectId, in, m_appidCtrlId,    "appidCtrlId");    // CONTROL OBJECT
    BS_ARCHIVE(OcDbObjectId, in, m_dimstyleCtrlId, "dimstyleCtrlId"); // CONTROL OBJECT

// R13-R15
    if(dwgVersion == R13 || dwgVersion == R14 || dwgVersion == R2000) {
        BS_ARCHIVE(OcDbObjectId, in, m_viewport, "viewport"); // ENTITY HEADER CONTROL OBJECT
    }

// common
    BS_ARCHIVE(OcDbObjectId, in, m_dictionaryGroupId,      "group dictionary Id");
    BS_ARCHIVE(OcDbObjectId, in, m_dictionaryMLineStyleId, "mline style dict Id");
    BS_ARCHIVE(OcDbObjectId, in, m_dictionaryNamedObjsId,  "named objects dict Id");

// R2000+
    if(dwgVersion >= R2000) {
        BS_ARCHIVE(bitcode::BS, in, m_tstackalign,   "tstackalign");
        BS_ARCHIVE(bitcode::BS, in, m_tstacksize,    "tstacksize");
        BS_ARCHIVE(bitcode::TV, in, m_hyperlinkbase, "hyperlinkbase");
        BS_ARCHIVE(bitcode::TV, in, m_stylesheet,    "stylesheet")
        BS_ARCHIVE(OcDbObjectId, in, m_dictionaryLayoutsId,      "layouts dict Id");       // (LAYOUTS)
        BS_ARCHIVE(OcDbObjectId, in, m_dictionaryPlotSettingsId, "plot settings dict Id"); // (PLOTSETTINGS)
        BS_ARCHIVE(OcDbObjectId, in, m_dictionaryPlotStylesId,   "plot styles dict Id");        // (PLOTSTYLES)
    }

// R2004+
    if(dwgVersion >= R2004) {
        BS_ARCHIVE(OcDbObjectId, in, m_dictionaryMaterialsId, "materials dict Id");     // (MATERIALS)
        BS_ARCHIVE(OcDbObjectId, in, m_dictionaryColorsId, "colors dict Id");        // (COLORS)
    }

// R2007+
    if(dwgVersion >= R2007) {
        BS_ARCHIVE(OcDbObjectId, in, m_dictionaryVisualStyleId, "visual style dict Id");  // (VISUALSTYLE)
    }

// R2000+
    if(dwgVersion >= R2000) {
        BS_ARCHIVE(bitcode::BL, in, m_flags, "flags");
        //                      CELWEIGHT       Flags & 0x001F
        //                      ENDCAPS         Flags & 0x0060
        //                      JOINSTYLE       Flags & 0x0180
        //                      LWDISPLAY       !(Flags & 0x0200)
        //                      XEDIT           !(Flags & 0x0400)
        //                      EXTNAMES        Flags & 0x0800
        //                      PSTYLEMODE      Flags & 0x2000
        //                      OLESTARTUP      Flags & 0x4000
        BS_ARCHIVE(bitcode::BS, in, m_insunits,  "insunits");
        BS_ARCHIVE(bitcode::BS, in, m_cepsntype, "cepsntype");
        if(m_cepsntype == 3) {
            // m_cpsnid only present if m_cepsntype == 3
            BS_ARCHIVE(OcDbObjectId, in, m_cpsnid, "cpsnid");
        }
        BS_ARCHIVE(bitcode::TV, in, m_fingerprintguid, "fingerprintguid");
        BS_ARCHIVE(bitcode::TV, in, m_versionguid, "versionguid");
    }

// R2004+
    if(dwgVersion >= R2004) {
        BS_ARCHIVE(bitcode::RC, in, m_sortents,          "sortents");
        BS_ARCHIVE(bitcode::RC, in, m_indexctl,          "indexctl");
        BS_ARCHIVE(bitcode::RC, in, m_hidetext,          "hidetext");
        BS_ARCHIVE(bitcode::RC, in, m_xclipframe,        "xclipframe");
        BS_ARCHIVE(bitcode::RC, in, m_dimassoc,          "dimassoc");
        BS_ARCHIVE(bitcode::RC, in, m_halogap,           "halogap");
        BS_ARCHIVE(bitcode::BS, in, m_obscuredcolor,     "obscuredcolor");
        BS_ARCHIVE(bitcode::BS, in, m_intersectioncolor, "intersectioncolor");
        BS_ARCHIVE(bitcode::RC, in, m_obscuredltype,     "obscuredltype");
        BS_ARCHIVE(bitcode::RC, in, m_intersectiondisplay, "intersectiondisplay")
        BS_ARCHIVE(bitcode::TV, in, m_projectname,       "projectname");
    }

// common
    BS_ARCHIVE(OcDbObjectId, in, m_block_recordPsId, "ps block record Id");  // (*PAPER_SPACE)
    BS_ARCHIVE(OcDbObjectId, in, m_block_recordMsId, "ms block record Id");  // (*MODEL_SPACE)
    BS_ARCHIVE(OcDbObjectId, in, m_ltypeByLayerId,   "ltype bylayer id");         // (BYLAYER)
    BS_ARCHIVE(OcDbObjectId, in, m_ltypeByBlockId,   "ltype byblock id");         // (BYBLOCK)
    BS_ARCHIVE(OcDbObjectId, in, m_ltypeContinuousId, "ltype continuous LT id");         // (CONTINUOUS)

// R2007+
    if(dwgVersion >= R2007) {
        BS_ARCHIVE(bitcode::B,  in, m_cameradisplay,     "cameradisplay");
        BS_ARCHIVE(bitcode::BL, in, m_unknown21,         "unknown21");
        BS_ARCHIVE(bitcode::BL, in, m_unknown22,         "unknown22");
        BS_ARCHIVE(bitcode::BD, in, m_unknown23,         "unknown23");
        BS_ARCHIVE(bitcode::BD, in, m_stepspersec,       "stepspersec");
        BS_ARCHIVE(bitcode::BD, in, m_stepsize,          "stepsize");
        BS_ARCHIVE(bitcode::BD, in, m_3ddwfprec,         "3ddwfprec");
        BS_ARCHIVE(bitcode::BD, in, m_lenslength,        "lenslength");
        BS_ARCHIVE(bitcode::BD, in, m_cameraheight,      "cameraheight");
        BS_ARCHIVE(bitcode::RC, in, m_solidhist,         "solidhist");
        BS_ARCHIVE(bitcode::RC, in, m_showhist,          "showhist");
        BS_ARCHIVE(bitcode::BD, in, m_psolwidth,         "psolwidth");
        BS_ARCHIVE(bitcode::BD, in, m_psolheight,        "psolheight");
        BS_ARCHIVE(bitcode::BD, in, m_loftang1,          "loftang1");
        BS_ARCHIVE(bitcode::BD, in, m_loftang2,          "loftang2");
        BS_ARCHIVE(bitcode::BD, in, m_loftmag1,          "loftmag1");
        BS_ARCHIVE(bitcode::BD, in, m_logtmag2,          "loftmag2");
        BS_ARCHIVE(bitcode::BS, in, m_loftparam,         "loftparam");
        BS_ARCHIVE(bitcode::RC, in, m_loftnormals,       "loftnormals");
        BS_ARCHIVE(bitcode::BD, in, m_latitude,          "latitude");
        BS_ARCHIVE(bitcode::BD, in, m_longitude,         "longitude");
        BS_ARCHIVE(bitcode::BD, in, m_northdirection,    "northdirection");
        BS_ARCHIVE(bitcode::BL, in, m_timezone,          "timezone");
        BS_ARCHIVE(bitcode::RC, in, m_lightglyphdisplay, "lightglyphdisplay");
        BS_ARCHIVE(bitcode::RC, in, m_tilemodelightsynch, "tilemodelightsynch");
        BS_ARCHIVE(bitcode::RC, in, m_dwfframe,          "dwfframe");
        BS_ARCHIVE(bitcode::RC, in, m_dgnframe,          "dgnframe");
        BS_ARCHIVE(bitcode::B,  in, m_unknown47,         "unknown47");
        BS_ARCHIVE(bitcode::CMC, in, m_interferecolor,   "interferecolor");
        BS_ARCHIVE(OcDbObjectId, in, m_interfereobjvsId, "interfereobjvsId");
        BS_ARCHIVE(OcDbObjectId, in, m_interferevpvsId,  "interferevpvsId");
        BS_ARCHIVE(OcDbObjectId, in, m_dragvsId,         "dragvsId");
        BS_ARCHIVE(bitcode::RC, in, m_cshadow,           "cshadow");
        BS_ARCHIVE(bitcode::BD, in, m_unknown53,         "unknown53");
    }

// R14+
    if(dwgVersion >= R14) {
        BS_ARCHIVE(bitcode::BS, in, m_unknown54, "unknown54");  // short(type 5 / 6 only)  these do not seem to be required,
        BS_ARCHIVE(bitcode::BS, in, m_unknown55, "unknown55");  // short(type 5 / 6 only)  even for type 5.
        BS_ARCHIVE(bitcode::BS, in, m_unknown56, "unknown56");  // short(type 5 / 6 only)
        BS_ARCHIVE(bitcode::BS, in, m_unknown57, "unknown57");  // short(type 5 / 6 only)
    }

    in.AdvanceToByteBoundary();
    if(size != in.FilePosition() - startPos) {
        LOG(ERROR) << "File position should be "
            << startPos + size << " instead of "
            << in.FilePosition();
    }

    uint16_t fileCRC, calcedCRC = in.CalcedCRC();
    in.ReadCRC(fileCRC); //  >> (bitcode::RS&) crc1;
    if(calcedCRC != fileCRC) {
        LOG(ERROR) << "file section and calced CRC do not match";
        LOG(ERROR) << "Header varibles CRC = " << hex << showbase << fileCRC;
        LOG(ERROR) << "Calced CRC          = " << hex << showbase << calcedCRC;
    } else {
        VLOG(4) << "CRC for Header variables section = "
            << hex << showbase << fileCRC;
    }

// common
//    BS_ARCHIVE(bitcode::RS, in, m_crc, "crc"); // for the data section, starting after the
    // sentinel. Use 0xC0C1 for the initial value.

////////////////////////////////////////////////////////////////////////////



    // match dwg header variables end sentinel
    //bitcode::RC sentinelData[16];
    in.ReadRC(sentinelData, 16);
    //for(int j = 0; j < 5; j++) {
    //    in.ReadRC(sentinelData, 16);
    //    std::stringstream ss;
    //    for(int i = 0; i < 16; ++i) {
    //        ss << hex << showbase << (int)sentinelData[i] << " ";
    //    }
    //    VLOG(4) << ss.str();
    //}
    if(!CompareSentinels(sentinelHeaderVarsEnd, sentinelData)) {
        std::stringstream ss;
        for(int i =0; i < 16; ++i) {
            ss << hex << showbase << (int)sentinelData[i] << " ";
        }
        VLOG(4) << ss.str();
        return OcApp::eInvalidImageDataSentinel;
    }

    VLOG(3) << "Successfully decoded drawing header variables";
    return OcApp::eOk;
}

DwgInArchive& operator>>(DwgInArchive& in, OcDfHeaderVars & dwgVars)
{
    ASSERT_ARCHIVE_NOT_LOADING(in);
    in.SetError(dwgVars.DecodeData(in));
    return in;
}

END_OCTAVARIUM_NS
