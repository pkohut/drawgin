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
unknown1(412148564080.0), unknown2(1.0), unknown3(1.0), unknown4(1.0),
unknown9(24)
{
    VLOG(4) << "Constructor entered";
}

OcDfHeaderVars::~OcDfHeaderVars(void)
{
    VLOG(4) << "Destructor entered";
}

OcApp::ErrorStatus OcDfHeaderVars::DecodeData(DwgInArchive& in)
{
    VLOG(4) << "DecodeData entered";
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
    BS_ARCHIVE(bitcode::BD, in, unknown1(),  "unknown1");
    BS_ARCHIVE(bitcode::BD, in, unknown2(),  "unknown2");
    BS_ARCHIVE(bitcode::BD, in, unknown3(),  "unknown3");
    BS_ARCHIVE(bitcode::BD, in, unknown4(),  "unknown4");
    BS_ARCHIVE(bitcode::TV, in, unknown5(),  "unknown5");
    BS_ARCHIVE(bitcode::TV, in, unknown6(),  "unknown6");
    BS_ARCHIVE(bitcode::TV, in, unknown7(),  "unknown7");
    BS_ARCHIVE(bitcode::TV, in, unknown8(),  "unknown8");
    BS_ARCHIVE(bitcode::BL, in, unknown9(),  "unknown9");
    BS_ARCHIVE(bitcode::BL, in, unknown10(), "unknown10");

    if(dwgVersion == R13 || dwgVersion == R14) {
        BS_ARCHIVE(bitcode::BS, in, unknown11(), "unknown11");
    }

    // common
    BS_ARCHIVE(OcDbObjectId, in, currentVpId(), "currentvpId");
    BS_ARCHIVE(bitcode::B, in, dimaso(),        "dimaso");
    BS_ARCHIVE(bitcode::B, in, dimsho(),        "dimsho");

    if(dwgVersion == R13 || dwgVersion == R14) {
        BS_ARCHIVE(bitcode::B, in, dimsav(), "dimsav");
    }

    // common
    BS_ARCHIVE(bitcode::B, in, plinegen(),  "plinegen");
    BS_ARCHIVE(bitcode::B, in, orthomode(), "orthomode");
    BS_ARCHIVE(bitcode::B, in, regenmode(), "regenmode");
    BS_ARCHIVE(bitcode::B, in, fillmode(),  "fillmode");
    BS_ARCHIVE(bitcode::B, in, qtextmode(), "qtextmode");
    BS_ARCHIVE(bitcode::B, in, psltscale(), "psltscale");
    BS_ARCHIVE(bitcode::B, in, limcheck(),  "limcheck");

    if(dwgVersion == R13 || dwgVersion == R14) {
        BS_ARCHIVE(bitcode::B, in, blipmode(), "blipmode");
    }

    if(dwgVersion >= R2004) {
        BS_ARCHIVE(bitcode::B, in, undocumented(), "undocumented");
    }

    // common
    BS_ARCHIVE(bitcode::B, in, usertimer(), "usertimer");
    BS_ARCHIVE(bitcode::B, in, skpoly(),    "skpoly");
    BS_ARCHIVE(bitcode::B, in, angdir(),    "angdir");
    BS_ARCHIVE(bitcode::B, in, splframe(),  "splframe");

    if(dwgVersion == R13 || dwgVersion == R14) {
        BS_ARCHIVE(bitcode::B, in, attreq(), "attreq");
        BS_ARCHIVE(bitcode::B, in, attdia(), "attdia");
    }

    // common
    BS_ARCHIVE(bitcode::B, in, mirrtext(),  "mirrtext");
    BS_ARCHIVE(bitcode::B, in, worldview(), "worldview");

    if(dwgVersion == R13 || dwgVersion == R14) {
        BS_ARCHIVE(bitcode::B, in, wireframe(), "wireframe");
    }

    // common
    BS_ARCHIVE(bitcode::B, in, tilemode(),  "tilemode");
    BS_ARCHIVE(bitcode::B, in, plimcheck(), "plimcheck");
    BS_ARCHIVE(bitcode::B, in, visretain(), "visretain");

    if(dwgVersion == R13 || dwgVersion == R14) {
        BS_ARCHIVE(bitcode::B, in, delobj(), "delobj");
    }

    // common
    BS_ARCHIVE(bitcode::B, in, dispsilh(),    "dispsilh");
    BS_ARCHIVE(bitcode::B, in, pellipse(),    "pellispe");
    BS_ARCHIVE(bitcode::BS, in, saveimages(), "saveimages");

    if(dwgVersion == R13 || dwgVersion == R14) {
        BS_ARCHIVE(bitcode::BS, in, dimsav(), "dimsav");
    }

    // common
    BS_ARCHIVE(bitcode::BS, in, treedepth(), "treedepth");
    BS_ARCHIVE(bitcode::BS, in, lunits(),    "lunits");
    BS_ARCHIVE(bitcode::BS, in, luprec(),    "luprec");
    BS_ARCHIVE(bitcode::BS, in, aunits(),    "aunits");
    BS_ARCHIVE(bitcode::BS, in, auprec(),    "auprec");

    if(dwgVersion == R13 || dwgVersion == R14) {
        BS_ARCHIVE(bitcode::BS, in, osmode(), "osmode");
    }

    // common
    BS_ARCHIVE(bitcode::BS, in, attmode(), "attmode");

    if(dwgVersion == R13 || dwgVersion == R14) {
        BS_ARCHIVE(bitcode::BS, in, coords(), "coords");
    }

    // common
    BS_ARCHIVE(bitcode::BS, in, pdmode(), "pdmode");

    if(dwgVersion == R13 || dwgVersion == R14) {
        BS_ARCHIVE(bitcode::BS, in, pickstyle(), "pickstyle");
    }

    if(dwgVersion >= R2004) {
        BS_ARCHIVE(bitcode::BL, in, unknown12(), "unknown12");
        BS_ARCHIVE(bitcode::BL, in, unknown13(), "unknown13");
        BS_ARCHIVE(bitcode::BL, in, unknown14(), "unknown14");
    }

    // common
    BS_ARCHIVE(bitcode::BS, in, useri1(),       "useri1");
    BS_ARCHIVE(bitcode::BS, in, useri2(),       "useri2");
    BS_ARCHIVE(bitcode::BS, in, useri3(),       "useri3");
    BS_ARCHIVE(bitcode::BS, in, useri4(),       "useri4");
    BS_ARCHIVE(bitcode::BS, in, useri5(),       "useri5");
    BS_ARCHIVE(bitcode::BS, in, splinesegs(),   "splinesegs");
    BS_ARCHIVE(bitcode::BS, in, surfu(),        "surfu");
    BS_ARCHIVE(bitcode::BS, in, surfv(),        "surfv");
    BS_ARCHIVE(bitcode::BS, in, surftype(),     "surftype");
    BS_ARCHIVE(bitcode::BS, in, surftab1(),     "surftab1");
    BS_ARCHIVE(bitcode::BS, in, surftab2(),     "surftab2");
    BS_ARCHIVE(bitcode::BS, in, splinetype(),   "splinetype");
    BS_ARCHIVE(bitcode::BS, in, shadedge(),     "shadedge");
    BS_ARCHIVE(bitcode::BS, in, shadedif(),     "shadedif");
    BS_ARCHIVE(bitcode::BS, in, unitmode(),     "unitmode");
    BS_ARCHIVE(bitcode::BS, in, maxactvp(),     "macactvp");
    BS_ARCHIVE(bitcode::BS, in, isolines(),     "isolines");
    BS_ARCHIVE(bitcode::BS, in, cmljust(),      "cmljust");
    BS_ARCHIVE(bitcode::BS, in, textqlty(),     "textqlty");
    BS_ARCHIVE(bitcode::BD, in, ltscale(),      "ltscale");
    BS_ARCHIVE(bitcode::BD, in, textsize(),     "textsize");
    BS_ARCHIVE(bitcode::BD, in, tracewid(),     "tracewid");
    BS_ARCHIVE(bitcode::BD, in, sketchinc(),    "sketchinc");
    BS_ARCHIVE(bitcode::BD, in, filletrad(),    "filletrad");
    BS_ARCHIVE(bitcode::BD, in, thickness(),    "thickness");
    BS_ARCHIVE(bitcode::BD, in, angbase(),      "angbase");
    BS_ARCHIVE(bitcode::BD, in, pdsize(),       "pdsize");
    BS_ARCHIVE(bitcode::BD, in, plinewid(),     "plinewid");
    BS_ARCHIVE(bitcode::BD, in, userr1(),       "userr1");
    BS_ARCHIVE(bitcode::BD, in, userr2(),       "userr2");
    BS_ARCHIVE(bitcode::BD, in, userr3(),       "userr3");
    BS_ARCHIVE(bitcode::BD, in, userr4(),       "userr4");
    BS_ARCHIVE(bitcode::BD, in, userr5(),       "userr5");
    BS_ARCHIVE(bitcode::BD, in, chamfera(),     "chamfera");
    BS_ARCHIVE(bitcode::BD, in, chamferb(),     "chamferb");
    BS_ARCHIVE(bitcode::BD, in, chamferc(),     "chamferc");
    BS_ARCHIVE(bitcode::BD, in, chamferd(),     "chamferd");
    BS_ARCHIVE(bitcode::BD, in, facetres(),     "facetres");
    BS_ARCHIVE(bitcode::BD, in, cmlscale(),     "cmlscale");
    BS_ARCHIVE(bitcode::BD, in, celtscale(),    "celtscale");
    BS_ARCHIVE(bitcode::TV, in, menuname(),     "menuname");
    BS_ARCHIVE(bitcode::BL, in, tdcreate_day(), "tdcreate_day");
    BS_ARCHIVE(bitcode::BL, in, tdcreate_ms(),  "tdcreate_ms");
    BS_ARCHIVE(bitcode::BL, in, tdupdate_day(), "tdupdate_day");
    BS_ARCHIVE(bitcode::BL, in, tdupdate_ms(),  "tdupdate_ms");

    if(dwgVersion >= R2004) {
        BS_ARCHIVE(bitcode::BL, in, unknown15(), "unknown15");
        BS_ARCHIVE(bitcode::BL, in, unknown16(), "unknown16");
        BS_ARCHIVE(bitcode::BL, in, unknown17(), "unknown17");
    }

    // common
    BS_ARCHIVE(bitcode::BL, in, tdindwg_days(),    "tdindwg_days");
    BS_ARCHIVE(bitcode::BL, in, tdindwg_ms(),      "tdindwg_ms");
    BS_ARCHIVE(bitcode::BL, in, tdusrtimer_days(), "tdusrtimer_days");
    BS_ARCHIVE(bitcode::BL, in, tdusrtimer_ms(),   "tdusrtimer_ms");
    BS_ARCHIVE(bitcode::CMC, in, cecolor(),        "cecolor");
    BS_ARCHIVE(OcDbObjectId, in, handseed(),       "handseed");
    BS_ARCHIVE(OcDbObjectId, in, clayer(),         "clayer");
    BS_ARCHIVE(OcDbObjectId, in, textstyle(),      "textstyle");
    BS_ARCHIVE(OcDbObjectId, in, celtype(),        "celtype");

    // R2007+
    if(dwgVersion >= R2007) {
        BS_ARCHIVE(OcDbObjectId, in, cmaterial(), "cmaterial");
    }

    // commmon
    BS_ARCHIVE(OcDbObjectId, in, dimstyle(), "dimstyle");
    BS_ARCHIVE(OcDbObjectId, in, cmlstyle(), "cmlstyle");

    // R2000+ only
    if(dwgVersion >= R2000) {
        BS_ARCHIVE(bitcode::BD, in, psvpscale(), "psvpscale");
    }

    // common
    VLOG(4) << "****** Begin PS read *****";
    BS_ARCHIVE(bitcode::BD3, in, pinsbase(),  "pinsbase");
    BS_ARCHIVE(bitcode::BD3, in, pextmin(),   "pextmin");
    BS_ARCHIVE(bitcode::BD3, in, pextmax(),   "pextmax");
    BS_ARCHIVE(bitcode::RD2, in, plimmin(),   "plimmin");
    BS_ARCHIVE(bitcode::RD2, in, plimmax(),   "plimmax");
    BS_ARCHIVE(bitcode::BD, in, pelevation(), "pelevation");
    BS_ARCHIVE(bitcode::BD3, in, pucsorg(),   "pucsorg");
    BS_ARCHIVE(bitcode::BD3, in, pucsxdir(),  "pucsxdir");
    BS_ARCHIVE(bitcode::BD3, in, pucsydir(),  "pucsydir");
    BS_ARCHIVE(OcDbObjectId, in, pucsname(),  "pucsname");

    if(dwgVersion >= R2000) {
        BS_ARCHIVE(OcDbObjectId, in, pucsbase(),      "pucsbase");
        BS_ARCHIVE(bitcode::BS, in, pucsorthoview(),  "pucsorthoview");
        BS_ARCHIVE(OcDbObjectId, in, pucsorthoref(),  "pucsorthoref");
        BS_ARCHIVE(bitcode::BD3, in, pucsorgtop(),    "pucsorgtop");
        BS_ARCHIVE(bitcode::BD3, in, pucsorgbottom(), "pucsorgbottom");
        BS_ARCHIVE(bitcode::BD3, in, pucsorgleft(),   "pucsorgleft");
        BS_ARCHIVE(bitcode::BD3, in, pucsorgright(),  "pucsorgright");
        BS_ARCHIVE(bitcode::BD3, in, pucsorgfront(),  "pucsorgfront");
        BS_ARCHIVE(bitcode::BD3, in, pucsorgback(),   "pucsorgback");
    }


    // common
    VLOG(4) << "****** Begin MS read *****";
    BS_ARCHIVE(bitcode::BD3, in, insbase(),  "insbase");
    BS_ARCHIVE(bitcode::BD3, in, extmin(),   "extmin");
    BS_ARCHIVE(bitcode::BD3, in, extmax(),   "extmax");
    BS_ARCHIVE(bitcode::RD2, in, limmin(),   "limmin");
    BS_ARCHIVE(bitcode::RD2, in, limmax(),   "limmax");
    BS_ARCHIVE(bitcode::BD, in, elevation(), "elevation");
    BS_ARCHIVE(bitcode::BD3, in, ucsorg(),   "ucsorg");
    BS_ARCHIVE(bitcode::BD3, in, ucsxdir(),  "ucsxdir");
    BS_ARCHIVE(bitcode::BD3, in, ucsydir(),  "ucsydir");
    BS_ARCHIVE(OcDbObjectId, in, ucsname(),  "ucsname");

    if(dwgVersion >= R2000) {
        BS_ARCHIVE(OcDbObjectId, in, ucsbase(),      "ucsbase");
        BS_ARCHIVE(bitcode::BS, in, ucsorthoview(),  "ucsorthoview");
        BS_ARCHIVE(OcDbObjectId, in, ucsorthoref(),  "ucsorthoref");
        BS_ARCHIVE(bitcode::BD3, in, ucsorgtop(),    "ucsorgtop");
        BS_ARCHIVE(bitcode::BD3, in, ucsorgbottom(), "ucsorgbottom");
        BS_ARCHIVE(bitcode::BD3, in, ucsorgleft(),   "ucsorgleft");
        BS_ARCHIVE(bitcode::BD3, in, ucsorgright(),  "ucsorgright");
        BS_ARCHIVE(bitcode::BD3, in, ucsorgfront(),  "ucsorgfront");
        BS_ARCHIVE(bitcode::BD3, in, ucsorgback(),   "ucsorgback");
        BS_ARCHIVE(bitcode::TV, in, dimpost(),       "dimpost");
        BS_ARCHIVE(bitcode::TV, in, dimapost(),      "dimapost");
    }

    if(dwgVersion == R13 || dwgVersion == R14) {
        BS_ARCHIVE(bitcode::B, in, dimtol(),     "dimtol");
        BS_ARCHIVE(bitcode::B, in, dimlim(),     "dimlim");
        BS_ARCHIVE(bitcode::B, in, dimtih(),     "dimtih");
        BS_ARCHIVE(bitcode::B, in, dimtoh(),     "dimtoh");
        BS_ARCHIVE(bitcode::B, in, dimse1(),     "dimse1");
        BS_ARCHIVE(bitcode::B, in, dimse2(),     "dimse2");
        BS_ARCHIVE(bitcode::B, in, dimalt(),     "dimalt");
        BS_ARCHIVE(bitcode::B, in, dimtofl(),    "dimtofl");
        BS_ARCHIVE(bitcode::B, in, dimsah(),     "dimsah");
        BS_ARCHIVE(bitcode::B, in, dimtix(),     "dimtix");
        BS_ARCHIVE(bitcode::B, in, dimsoxd(),    "dimsoxd");
        BS_ARCHIVE(bitcode::RC, in, dimaltd(),   "dimaltd");
        BS_ARCHIVE(bitcode::RC, in, dimzin(),    "dimzin");
        BS_ARCHIVE(bitcode::B, in, dimsd1(),     "dimsd1");
        BS_ARCHIVE(bitcode::B, in, dimsd2(),     "dimsd2");
        BS_ARCHIVE(bitcode::RC, in, dimtolj(),   "dimtolj");
        BS_ARCHIVE(bitcode::RC, in, dimjust(),   "dimjust");
        BS_ARCHIVE(bitcode::RC, in, dimfit(),    "dimfit");
        BS_ARCHIVE(bitcode::B, in, dimupt(),     "dimupt");
        BS_ARCHIVE(bitcode::RC, in, dimtzin(),   "dimtzin");
        BS_ARCHIVE(bitcode::RC, in, dimaltz(),   "dimaltz");
        BS_ARCHIVE(bitcode::RC, in, dimalttz(),  "dimalttz");
        BS_ARCHIVE(bitcode::RC, in, dimtad(),    "dimtad");
        BS_ARCHIVE(bitcode::BS, in, dimunit(),   "dimunit");
        BS_ARCHIVE(bitcode::BS, in, dimaunit(),  "dimaunit");
        BS_ARCHIVE(bitcode::BS, in, dimdec(),    "dimdec");
        BS_ARCHIVE(bitcode::BS, in, dimtdec(),   "dimtdec");
        BS_ARCHIVE(bitcode::BS, in, dimaltu(),   "dimaltu");
        BS_ARCHIVE(bitcode::BS, in, dimalttd(),  "dimalttd");
        BS_ARCHIVE(OcDbObjectId, in, dimtxsty(), "dimtxsty");
    }

////////////////////////////////////////////////////////////////////////////
// common
    BS_ARCHIVE(bitcode::BD, in, dimscale(), "dimscale")
    BS_ARCHIVE(bitcode::BD, in, dimasz(),   "dimasz");
    BS_ARCHIVE(bitcode::BD, in, dimexo(),   "dimexo");
    BS_ARCHIVE(bitcode::BD, in, dimdli(),   "dimdli");
    BS_ARCHIVE(bitcode::BD, in, dimexe(),   "dimexe");
    BS_ARCHIVE(bitcode::BD, in, dimrnd(),   "dimrnd");
    BS_ARCHIVE(bitcode::BD, in, dimdle(),   "dimdle");
    BS_ARCHIVE(bitcode::BD, in, dimtp(),    "dimtp");
    BS_ARCHIVE(bitcode::BD, in, dimtm(),    "dimtm");

// R2007+
    if(dwgVersion >= R2007) {
        BS_ARCHIVE(bitcode::BD, in,  dimfxl(),      "dimfxl");
        BS_ARCHIVE(bitcode::BD, in,  dimjogang(),   "dimjogang");
        BS_ARCHIVE(bitcode::BS, in,  dimtfill(),    "dimtfill");
        BS_ARCHIVE(bitcode::CMC, in, dimtfillclr(), "dimtfillclr");
    }

// R2000+
    if(dwgVersion >= R2000) {
        BS_ARCHIVE(bitcode::B, in,  dimtol(),  "dimtol");
        BS_ARCHIVE(bitcode::B, in,  dimlim(),  "dimlim");
        BS_ARCHIVE(bitcode::B, in,  dimtih(),  "dimtih");
        BS_ARCHIVE(bitcode::B, in,  dimtoh(),  "dimtoh");
        BS_ARCHIVE(bitcode::B, in,  dimse1(),  "dimse1");
        BS_ARCHIVE(bitcode::B, in,  dimse2(),  "dimse2");
        BS_ARCHIVE(bitcode::BS, in, dimtad(),  "dimtad");
        BS_ARCHIVE(bitcode::BS, in, dimzin(),  "dimzin");
        BS_ARCHIVE(bitcode::BS, in, dimazin(), "dimazin");
    }

// R2007+
    if(dwgVersion >= R2007) {
        BS_ARCHIVE(bitcode::BS, in, dimarcsym(), "dimarcsym");
    }

// common
    BS_ARCHIVE(bitcode::BD, in, dimtxt(),  "dimtxt");
    BS_ARCHIVE(bitcode::BD, in, dimcen(),  "dimcen");
    BS_ARCHIVE(bitcode::BD, in, dimtsz(),  "dimtsz");
    BS_ARCHIVE(bitcode::BD, in, dimaltf(), "dimaltf");
    BS_ARCHIVE(bitcode::BD, in, dimlfac(), "dimlfac");
    BS_ARCHIVE(bitcode::BD, in, dimtvp(),  "dimtvp");
    BS_ARCHIVE(bitcode::BD, in, dimtfac(), "dimtfac");
    BS_ARCHIVE(bitcode::BD, in, dimgap(),  "dimgap");

// R13-R14
    if(dwgVersion == R13 || dwgVersion == R14) {
        BS_ARCHIVE(bitcode::T, in, dimpost(),  "dimpost");
        BS_ARCHIVE(bitcode::T, in, dimapost(), "dimapost");
        BS_ARCHIVE(bitcode::T, in, dimblk(),   "dimblk");
        BS_ARCHIVE(bitcode::T, in, dimblk1(),  "dimblk1");
        BS_ARCHIVE(bitcode::T, in, dimblk2(),  "dimblk2");
    }

// R2000+
    if(dwgVersion >= R2000) {
        BS_ARCHIVE(bitcode::BD, in, dimaltrnd(), "dimaltrnd");
        BS_ARCHIVE(bitcode::B,  in, dimalt(),    "dimalt");
        BS_ARCHIVE(bitcode::BS, in, dimaltd(),   "dimaltd");
        BS_ARCHIVE(bitcode::B,  in, dimtofl(),   "dimtofl");
        BS_ARCHIVE(bitcode::B,  in, dimsah(),    "dimsah");
        BS_ARCHIVE(bitcode::B,  in, dimtix(),    "dimtix");
        BS_ARCHIVE(bitcode::B,  in, dimsoxd(),   "dimsoxd");
    }

// common
    BS_ARCHIVE(bitcode::CMC, in, dimclrd(), "dimclrd");
    BS_ARCHIVE(bitcode::CMC, in, dimclre(), "dimclre");
    BS_ARCHIVE(bitcode::CMC, in, dimclrt(), "dimclrt");

// R2000+
    if(dwgVersion >= R2000) {
        BS_ARCHIVE(bitcode::BS, in, dimadec(),  "dimadec");
        BS_ARCHIVE(bitcode::BS, in, dimdec(),   "dimdec");
        BS_ARCHIVE(bitcode::BS, in, dimtdec(),  "dimtdec");
        BS_ARCHIVE(bitcode::BS, in, dimaltu(),  "dimaltu");
        BS_ARCHIVE(bitcode::BS, in, dimalttd(), "dimalttd");
        BS_ARCHIVE(bitcode::BS, in, dimaunit(), "dimaunit");
        BS_ARCHIVE(bitcode::BS, in, dimfrac(),  "dimfrac");
        BS_ARCHIVE(bitcode::BS, in, dimlunit(), "dimlunit");
        BS_ARCHIVE(bitcode::BS, in, dimdsep(),  "dimdsep");
        BS_ARCHIVE(bitcode::BS, in, dimtmove(), "dimtmove");
        BS_ARCHIVE(bitcode::BS, in, dimjust(),  "dimjust");
        BS_ARCHIVE(bitcode::B,  in, dimsd1(),   "dimsd1");
        BS_ARCHIVE(bitcode::B,  in, dimsd2(),   "dimsd2");
        BS_ARCHIVE(bitcode::BS, in, dimtolj(),  "dimtolj");
        BS_ARCHIVE(bitcode::BS, in, dimtzin(),  "dimtzin");
        BS_ARCHIVE(bitcode::BS, in, dimaltz(),  "dimaltz");
        BS_ARCHIVE(bitcode::BS, in, dimalttz(), "dimalttz");
        BS_ARCHIVE(bitcode::B,  in, dimupt(),   "dimupt");
        BS_ARCHIVE(bitcode::BS, in, dimatfit(), "dimatfit");
    }

// R2007+
    if(dwgVersion >= R2007) {
        BS_ARCHIVE(bitcode::B, in, dimfxlon(), "dimfxlog");
    }

    if(dwgVersion >= R2010) {
//        BS_ARCHIVE(bitcode::B,  in, dimtxtdirection(), "dimtxtdirection");
//        BS_ARCHIVE(bitcode::BD, in, dimaltmzf(),       "dimaltmzf");
//        BS_ARCHIVE(bitcode::T,  in, dimaltmzs(),       "dimaltmzs");
//        BS_ARCHIVE(bitcode::BD, in, dimmzf(),          "dimmzf");
//        BS_ARCHIVE(bitcode::T,  in, dimmzs(),          "dimmzs");
    }

// R2000+
    if(dwgVersion >= R2000) {
        BS_ARCHIVE(OcDbObjectId, in, dimtxsty(),  "dimtxsty");
        BS_ARCHIVE(OcDbObjectId, in, dimldrblk(), "dimldrblk");
        BS_ARCHIVE(OcDbObjectId, in, dimblkId(),  "dimblkId");
        BS_ARCHIVE(OcDbObjectId, in, dimblk1Id(), "dimblk1Id");
        BS_ARCHIVE(OcDbObjectId, in, dimblk2Id(), "dimblk2Id");
    }

// R2007+
    if(dwgVersion >= R2007) {
        BS_ARCHIVE(OcDbObjectId, in, dimltype(),  "dimltype");
        BS_ARCHIVE(OcDbObjectId, in, dimltex1(),  "dimltex1");
        BS_ARCHIVE(OcDbObjectId, in, dimltex2(),  "dimltex2");
    }

// R2000+
    if(dwgVersion >= R2000) {
        BS_ARCHIVE(bitcode::BS, in, dimlwd(), "dimlwd");
        BS_ARCHIVE(bitcode::BS, in, dimlwe(), "dimlwe");
    }

// common
    BS_ARCHIVE(OcDbObjectId, in, blockCtrlId(),    "blockCtrlId");  // CONTROL OBJECT
    BS_ARCHIVE(OcDbObjectId, in, layerCtrlId(),    "layerCtrlId");    // CONTROL OBJECT
    BS_ARCHIVE(OcDbObjectId, in, styleCtrlId(),    "styleCtrlId");    // CONTROL OBJECT
    BS_ARCHIVE(OcDbObjectId, in, linetypeCtrlId(), "linetypeCtrlId"); // CONTROL OBJECT
    BS_ARCHIVE(OcDbObjectId, in, viewCtrlId(),     "viewCtrlId");     // CONTROL OBJECT
    BS_ARCHIVE(OcDbObjectId, in, ucsCtrlId(),      "ucsCtrlId");      // CONTROL OBJECT
    BS_ARCHIVE(OcDbObjectId, in, vportCtrlId(),    "vportCtrlId");    // CONTROL OBJECT
    BS_ARCHIVE(OcDbObjectId, in, appidCtrlId(),    "appidCtrlId");    // CONTROL OBJECT
    BS_ARCHIVE(OcDbObjectId, in, dimstyleCtrlId(), "dimstyleCtrlId"); // CONTROL OBJECT

// R13-R15
    if(dwgVersion == R13 || dwgVersion == R14 || dwgVersion == R2000) {
        BS_ARCHIVE(OcDbObjectId, in, viewport(), "viewport"); // ENTITY HEADER CONTROL OBJECT
    }

// common
    BS_ARCHIVE(OcDbObjectId, in, dictionaryGroupId(),      "group dictionary Id");
    BS_ARCHIVE(OcDbObjectId, in, dictionaryMLineStyleId(), "mline style dict Id");
    BS_ARCHIVE(OcDbObjectId, in, dictionaryNamedObjsId(),  "named objects dict Id");

// R2000+
    if(dwgVersion >= R2000) {
        BS_ARCHIVE(bitcode::BS, in, tstackalign(),   "tstackalign");
        BS_ARCHIVE(bitcode::BS, in, tstacksize(),    "tstacksize");
        BS_ARCHIVE(bitcode::TV, in, hyperlinkbase(), "hyperlinkbase");
        BS_ARCHIVE(bitcode::TV, in, stylesheet(),    "stylesheet")
        BS_ARCHIVE(OcDbObjectId, in, dictionaryLayoutsId(),      "layouts dict Id");       // (LAYOUTS)
        BS_ARCHIVE(OcDbObjectId, in, dictionaryPlotSettingsId(), "plot settings dict Id"); // (PLOTSETTINGS)
        BS_ARCHIVE(OcDbObjectId, in, dictionaryPlotStylesId(),   "plot styles dict Id");        // (PLOTSTYLES)
    }

// R2004+
    if(dwgVersion >= R2004) {
        BS_ARCHIVE(OcDbObjectId, in, dictionaryMaterialsId(), "materials dict Id");     // (MATERIALS)
        BS_ARCHIVE(OcDbObjectId, in, dictionaryColorsId(), "colors dict Id");        // (COLORS)
    }

// R2007+
    if(dwgVersion >= R2007) {
        BS_ARCHIVE(OcDbObjectId, in, dictionaryVisualStyleId(), "visual style dict Id");  // (VISUALSTYLE)
    }

// R2000+
    if(dwgVersion >= R2000) {
        BS_ARCHIVE(bitcode::BL, in, flags(), "flags");
        //                      CELWEIGHT       Flags & 0x001F
        //                      ENDCAPS         Flags & 0x0060
        //                      JOINSTYLE       Flags & 0x0180
        //                      LWDISPLAY       !(Flags & 0x0200)
        //                      XEDIT           !(Flags & 0x0400)
        //                      EXTNAMES        Flags & 0x0800
        //                      PSTYLEMODE      Flags & 0x2000
        //                      OLESTARTUP      Flags & 0x4000
        BS_ARCHIVE(bitcode::BS, in, insunits(),  "insunits");
        BS_ARCHIVE(bitcode::BS, in, cepsntype(), "cepsntype");
        if(cepsntype() == 3) {
            // cpsnid only present if m_cepsntype == 3
            BS_ARCHIVE(OcDbObjectId, in, cpsnid(), "cpsnid");
        }
        BS_ARCHIVE(bitcode::TV, in, fingerprintguid(), "fingerprintguid");
        BS_ARCHIVE(bitcode::TV, in, versionguid(), "versionguid");
    }

// R2004+
    if(dwgVersion >= R2004) {
        BS_ARCHIVE(bitcode::RC, in, sortents(),          "sortents");
        BS_ARCHIVE(bitcode::RC, in, indexctl(),          "indexctl");
        BS_ARCHIVE(bitcode::RC, in, hidetext(),          "hidetext");
        BS_ARCHIVE(bitcode::RC, in, xclipframe(),        "xclipframe");
        BS_ARCHIVE(bitcode::RC, in, dimassoc(),          "dimassoc");
        BS_ARCHIVE(bitcode::RC, in, halogap(),           "halogap");
        BS_ARCHIVE(bitcode::BS, in, obscuredcolor(),     "obscuredcolor");
        BS_ARCHIVE(bitcode::BS, in, intersectioncolor(), "intersectioncolor");
        BS_ARCHIVE(bitcode::RC, in, obscuredltype(),     "obscuredltype");
        BS_ARCHIVE(bitcode::RC, in, intersectiondisplay(), "intersectiondisplay")
        BS_ARCHIVE(bitcode::TV, in, projectname(),       "projectname");
    }

// common
    BS_ARCHIVE(OcDbObjectId, in, block_recordPsId(), "ps block record Id");  // (*PAPER_SPACE)
    BS_ARCHIVE(OcDbObjectId, in, block_recordMsId(), "ms block record Id");  // (*MODEL_SPACE)
    BS_ARCHIVE(OcDbObjectId, in, ltypeByLayerId(),   "ltype bylayer id");         // (BYLAYER)
    BS_ARCHIVE(OcDbObjectId, in, ltypeByBlockId(),   "ltype byblock id");         // (BYBLOCK)
    BS_ARCHIVE(OcDbObjectId, in, ltypeContinuousId(), "ltype continuous LT id");         // (CONTINUOUS)

// R2007+
    if(dwgVersion >= R2007) {
        BS_ARCHIVE(bitcode::B,  in, cameradisplay(),     "cameradisplay");
        BS_ARCHIVE(bitcode::BL, in, unknown21(),         "unknown21");
        BS_ARCHIVE(bitcode::BL, in, unknown22(),         "unknown22");
        BS_ARCHIVE(bitcode::BD, in, unknown23(),         "unknown23");
        BS_ARCHIVE(bitcode::BD, in, stepspersec(),       "stepspersec");
        BS_ARCHIVE(bitcode::BD, in, stepsize(),          "stepsize");
        BS_ARCHIVE(bitcode::BD, in, dwfprec3d(),         "dwfprec3d");
        BS_ARCHIVE(bitcode::BD, in, lenslength(),        "lenslength");
        BS_ARCHIVE(bitcode::BD, in, cameraheight(),      "cameraheight");
        BS_ARCHIVE(bitcode::RC, in, solidhist(),         "solidhist");
        BS_ARCHIVE(bitcode::RC, in, showhist(),          "showhist");
        BS_ARCHIVE(bitcode::BD, in, psolwidth(),         "psolwidth");
        BS_ARCHIVE(bitcode::BD, in, psolheight(),        "psolheight");
        BS_ARCHIVE(bitcode::BD, in, loftang1(),          "loftang1");
        BS_ARCHIVE(bitcode::BD, in, loftang2(),          "loftang2");
        BS_ARCHIVE(bitcode::BD, in, loftmag1(),          "loftmag1");
        BS_ARCHIVE(bitcode::BD, in, logtmag2(),          "loftmag2");
        BS_ARCHIVE(bitcode::BS, in, loftparam(),         "loftparam");
        BS_ARCHIVE(bitcode::RC, in, loftnormals(),       "loftnormals");
        BS_ARCHIVE(bitcode::BD, in, latitude(),          "latitude");
        BS_ARCHIVE(bitcode::BD, in, longitude(),         "longitude");
        BS_ARCHIVE(bitcode::BD, in, northdirection(),    "northdirection");
        BS_ARCHIVE(bitcode::BL, in, timezone(),          "timezone");
        BS_ARCHIVE(bitcode::RC, in, lightglyphdisplay(), "lightglyphdisplay");
        BS_ARCHIVE(bitcode::RC, in, tilemodelightsynch(), "tilemodelightsynch");
        BS_ARCHIVE(bitcode::RC, in, dwfframe(),          "dwfframe");
        BS_ARCHIVE(bitcode::RC, in, dgnframe(),          "dgnframe");
        BS_ARCHIVE(bitcode::B,  in, unknown47(),         "unknown47");
        BS_ARCHIVE(bitcode::CMC, in, interferecolor(),   "interferecolor");
        BS_ARCHIVE(OcDbObjectId, in, interfereobjvsId(), "interfereobjvsId");
        BS_ARCHIVE(OcDbObjectId, in, interferevpvsId(),  "interferevpvsId");
        BS_ARCHIVE(OcDbObjectId, in, dragvsId(),         "dragvsId");
        BS_ARCHIVE(bitcode::RC, in, cshadow(),           "cshadow");
        BS_ARCHIVE(bitcode::BD, in, unknown53(),         "unknown53");
    }

// R14+
    if(dwgVersion >= R14) {
        BS_ARCHIVE(bitcode::BS, in, unknown54(), "unknown54");  // short(type 5 / 6 only)  these do not seem to be required,
        BS_ARCHIVE(bitcode::BS, in, unknown55(), "unknown55");  // short(type 5 / 6 only)  even for type 5.
        BS_ARCHIVE(bitcode::BS, in, unknown56(), "unknown56");  // short(type 5 / 6 only)
        BS_ARCHIVE(bitcode::BS, in, unknown57(), "unknown57");  // short(type 5 / 6 only)
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
//    BS_ARCHIVE(bitcode::RS, in, crc(), "crc"); // for the data section, starting after the
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

    VLOG(4) << "Successfully decoded drawing header variables";
    return OcApp::eOk;
}

DwgInArchive& operator>>(DwgInArchive& in, OcDfHeaderVars & dwgVars)
{
    ASSERT_ARCHIVE_NOT_LOADING(in);
    in.SetError(dwgVars.DecodeData(in));
    return in;
}

END_OCTAVARIUM_NS
