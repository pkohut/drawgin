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

#include "OcCommon.h"
#include "OcTypes.h"
#include "OcError.h"
#include "OcDfDwgVersion.h"
#include "OcDbObjectId.h"
#include "OcDbHardOwnershipId.h"
#include "OcGePoint2D.h"
#include "OcGePoint3D.h"

#include "OcCmColor.h"


#include "../OcBs/OcBsStreamIn.h"
#include "../OcBs/DwgInArchive.h"
#include "OcDfDatabaseHeaderVars.h"
#include "../OcBs/OcBsDwgSentinels.h"
#include "../OcDb/OcDbDatabaseHeaderImpl.h"



BEGIN_OCTAVARIUM_NS
using namespace std;

OcDfDatabaseHeaderVars::OcDfDatabaseHeaderVars(OcDbDatabaseHeaderImpl * hdr)
: m_pHdr(hdr)
//:
//unknown1(412148564080.0), unknown2(1.0), unknown3(1.0), unknown4(1.0),
//unknown9(24)
{
    VLOG(4) << "Constructor entered";
}

OcDfDatabaseHeaderVars::~OcDfDatabaseHeaderVars(void)
{
    VLOG(4) << "Destructor entered";
}

OcApp::ErrorStatus OcDfDatabaseHeaderVars::DecodeData(DwgInArchive& in)
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
    //    Archive<bitcode::RL>(in, pHdr->size, "Header variables size");
    int size;
    BS_ARCHIVE(bitcode::RL, in, size, "Header variables size");
    //    }

    size_t startPos = in.FilePosition();

    // common
    BS_ARCHIVE(bitcode::BD, in, m_pHdr->unknown1(),  "unknown1");
    BS_ARCHIVE(bitcode::BD, in, m_pHdr->unknown2(),  "unknown2");
    BS_ARCHIVE(bitcode::BD, in, m_pHdr->unknown3(),  "unknown3");
    BS_ARCHIVE(bitcode::BD, in, m_pHdr->unknown4(),  "unknown4");
    BS_ARCHIVE(bitcode::TV, in, m_pHdr->unknown5(),  "unknown5");
    BS_ARCHIVE(bitcode::TV, in, m_pHdr->unknown6(),  "unknown6");
    BS_ARCHIVE(bitcode::TV, in, m_pHdr->unknown7(),  "unknown7");
    BS_ARCHIVE(bitcode::TV, in, m_pHdr->unknown8(),  "unknown8");
    BS_ARCHIVE(bitcode::BL, in, m_pHdr->unknown9(),  "unknown9");
    BS_ARCHIVE(bitcode::BL, in, m_pHdr->unknown10(), "unknown10");

    if(dwgVersion == R13 || dwgVersion == R14) {
        BS_ARCHIVE(bitcode::BS, in, m_pHdr->unknown11(), "unknown11");
    }

    // common
    BS_ARCHIVE(OcDbObjectId, in, m_pHdr->currentVpId(), "currentvpId");
    BS_ARCHIVE(bitcode::B, in, m_pHdr->dimaso(),        "dimaso");
    BS_ARCHIVE(bitcode::B, in, m_pHdr->dimsho(),        "dimsho");

    if(dwgVersion == R13 || dwgVersion == R14) {
        BS_ARCHIVE(bitcode::B, in, m_pHdr->dimsav(), "dimsav");
    }

    // common
    BS_ARCHIVE(bitcode::B, in, m_pHdr->plinegen(),  "plinegen");
    BS_ARCHIVE(bitcode::B, in, m_pHdr->orthomode(), "orthomode");
    BS_ARCHIVE(bitcode::B, in, m_pHdr->regenmode(), "regenmode");
    BS_ARCHIVE(bitcode::B, in, m_pHdr->fillmode(),  "fillmode");
    BS_ARCHIVE(bitcode::B, in, m_pHdr->qtextmode(), "qtextmode");
    BS_ARCHIVE(bitcode::B, in, m_pHdr->psltscale(), "psltscale");
    BS_ARCHIVE(bitcode::B, in, m_pHdr->limcheck(),  "limcheck");

    if(dwgVersion == R13 || dwgVersion == R14) {
        BS_ARCHIVE(bitcode::B, in, m_pHdr->blipmode(), "blipmode");
    }

    if(dwgVersion >= R2004) {
        BS_ARCHIVE(bitcode::B, in, m_pHdr->undocumented(), "undocumented");
    }

    // common
    BS_ARCHIVE(bitcode::B, in, m_pHdr->usertimer(), "usertimer");
    BS_ARCHIVE(bitcode::B, in, m_pHdr->skpoly(),    "skpoly");
    BS_ARCHIVE(bitcode::B, in, m_pHdr->angdir(),    "angdir");
    BS_ARCHIVE(bitcode::B, in, m_pHdr->splframe(),  "splframe");

    if(dwgVersion == R13 || dwgVersion == R14) {
        BS_ARCHIVE(bitcode::B, in, m_pHdr->attreq(), "attreq");
        BS_ARCHIVE(bitcode::B, in, m_pHdr->attdia(), "attdia");
    }

    // common
    BS_ARCHIVE(bitcode::B, in, m_pHdr->mirrtext(),  "mirrtext");
    BS_ARCHIVE(bitcode::B, in, m_pHdr->worldview(), "worldview");

    if(dwgVersion == R13 || dwgVersion == R14) {
        BS_ARCHIVE(bitcode::B, in, m_pHdr->wireframe(), "wireframe");
    }

    // common
    BS_ARCHIVE(bitcode::B, in, m_pHdr->tilemode(),  "tilemode");
    BS_ARCHIVE(bitcode::B, in, m_pHdr->plimcheck(), "plimcheck");
    BS_ARCHIVE(bitcode::B, in, m_pHdr->visretain(), "visretain");

    if(dwgVersion == R13 || dwgVersion == R14) {
        BS_ARCHIVE(bitcode::B, in, m_pHdr->delobj(), "delobj");
    }

    // common
    BS_ARCHIVE(bitcode::B, in, m_pHdr->dispsilh(),    "dispsilh");
    BS_ARCHIVE(bitcode::B, in, m_pHdr->pellipse(),    "pellispe");
    BS_ARCHIVE(bitcode::BS, in, m_pHdr->saveimages(), "saveimages");

    if(dwgVersion == R13 || dwgVersion == R14) {
        BS_ARCHIVE(bitcode::BS, in, m_pHdr->dimsav(), "dimsav");
    }

    // common
    BS_ARCHIVE(bitcode::BS, in, m_pHdr->treedepth(), "treedepth");
    BS_ARCHIVE(bitcode::BS, in, m_pHdr->lunits(),    "lunits");
    BS_ARCHIVE(bitcode::BS, in, m_pHdr->luprec(),    "luprec");
    BS_ARCHIVE(bitcode::BS, in, m_pHdr->aunits(),    "aunits");
    BS_ARCHIVE(bitcode::BS, in, m_pHdr->auprec(),    "auprec");

    if(dwgVersion == R13 || dwgVersion == R14) {
        BS_ARCHIVE(bitcode::BS, in, m_pHdr->osmode(), "osmode");
    }

    // common
    BS_ARCHIVE(bitcode::BS, in, m_pHdr->attmode(), "attmode");

    if(dwgVersion == R13 || dwgVersion == R14) {
        BS_ARCHIVE(bitcode::BS, in, m_pHdr->coords(), "coords");
    }

    // common
    BS_ARCHIVE(bitcode::BS, in, m_pHdr->pdmode(), "pdmode");

    if(dwgVersion == R13 || dwgVersion == R14) {
        BS_ARCHIVE(bitcode::BS, in, m_pHdr->pickstyle(), "pickstyle");
    }

    if(dwgVersion >= R2004) {
        BS_ARCHIVE(bitcode::BL, in, m_pHdr->unknown12(), "unknown12");
        BS_ARCHIVE(bitcode::BL, in, m_pHdr->unknown13(), "unknown13");
        BS_ARCHIVE(bitcode::BL, in, m_pHdr->unknown14(), "unknown14");
    }

    // common
    BS_ARCHIVE(bitcode::BS, in, m_pHdr->useri1(),       "useri1");
    BS_ARCHIVE(bitcode::BS, in, m_pHdr->useri2(),       "useri2");
    BS_ARCHIVE(bitcode::BS, in, m_pHdr->useri3(),       "useri3");
    BS_ARCHIVE(bitcode::BS, in, m_pHdr->useri4(),       "useri4");
    BS_ARCHIVE(bitcode::BS, in, m_pHdr->useri5(),       "useri5");
    BS_ARCHIVE(bitcode::BS, in, m_pHdr->splinesegs(),   "splinesegs");
    BS_ARCHIVE(bitcode::BS, in, m_pHdr->surfu(),        "surfu");
    BS_ARCHIVE(bitcode::BS, in, m_pHdr->surfv(),        "surfv");
    BS_ARCHIVE(bitcode::BS, in, m_pHdr->surftype(),     "surftype");
    BS_ARCHIVE(bitcode::BS, in, m_pHdr->surftab1(),     "surftab1");
    BS_ARCHIVE(bitcode::BS, in, m_pHdr->surftab2(),     "surftab2");
    BS_ARCHIVE(bitcode::BS, in, m_pHdr->splinetype(),   "splinetype");
    BS_ARCHIVE(bitcode::BS, in, m_pHdr->shadedge(),     "shadedge");
    BS_ARCHIVE(bitcode::BS, in, m_pHdr->shadedif(),     "shadedif");
    BS_ARCHIVE(bitcode::BS, in, m_pHdr->unitmode(),     "unitmode");
    BS_ARCHIVE(bitcode::BS, in, m_pHdr->maxactvp(),     "macactvp");
    BS_ARCHIVE(bitcode::BS, in, m_pHdr->isolines(),     "isolines");
    BS_ARCHIVE(bitcode::BS, in, m_pHdr->cmljust(),      "cmljust");
    BS_ARCHIVE(bitcode::BS, in, m_pHdr->textqlty(),     "textqlty");
    BS_ARCHIVE(bitcode::BD, in, m_pHdr->ltscale(),      "ltscale");
    BS_ARCHIVE(bitcode::BD, in, m_pHdr->textsize(),     "textsize");
    BS_ARCHIVE(bitcode::BD, in, m_pHdr->tracewid(),     "tracewid");
    BS_ARCHIVE(bitcode::BD, in, m_pHdr->sketchinc(),    "sketchinc");
    BS_ARCHIVE(bitcode::BD, in, m_pHdr->filletrad(),    "filletrad");
    BS_ARCHIVE(bitcode::BD, in, m_pHdr->thickness(),    "thickness");
    BS_ARCHIVE(bitcode::BD, in, m_pHdr->angbase(),      "angbase");
    BS_ARCHIVE(bitcode::BD, in, m_pHdr->pdsize(),       "pdsize");
    BS_ARCHIVE(bitcode::BD, in, m_pHdr->plinewid(),     "plinewid");
    BS_ARCHIVE(bitcode::BD, in, m_pHdr->userr1(),       "userr1");
    BS_ARCHIVE(bitcode::BD, in, m_pHdr->userr2(),       "userr2");
    BS_ARCHIVE(bitcode::BD, in, m_pHdr->userr3(),       "userr3");
    BS_ARCHIVE(bitcode::BD, in, m_pHdr->userr4(),       "userr4");
    BS_ARCHIVE(bitcode::BD, in, m_pHdr->userr5(),       "userr5");
    BS_ARCHIVE(bitcode::BD, in, m_pHdr->chamfera(),     "chamfera");
    BS_ARCHIVE(bitcode::BD, in, m_pHdr->chamferb(),     "chamferb");
    BS_ARCHIVE(bitcode::BD, in, m_pHdr->chamferc(),     "chamferc");
    BS_ARCHIVE(bitcode::BD, in, m_pHdr->chamferd(),     "chamferd");
    BS_ARCHIVE(bitcode::BD, in, m_pHdr->facetres(),     "facetres");
    BS_ARCHIVE(bitcode::BD, in, m_pHdr->cmlscale(),     "cmlscale");
    BS_ARCHIVE(bitcode::BD, in, m_pHdr->celtscale(),    "celtscale");
    BS_ARCHIVE(bitcode::TV, in, m_pHdr->menuname(),     "menuname");
    BS_ARCHIVE(bitcode::BL, in, m_pHdr->tdcreate_day(), "tdcreate_day");
    BS_ARCHIVE(bitcode::BL, in, m_pHdr->tdcreate_ms(),  "tdcreate_ms");
    BS_ARCHIVE(bitcode::BL, in, m_pHdr->tdupdate_day(), "tdupdate_day");
    BS_ARCHIVE(bitcode::BL, in, m_pHdr->tdupdate_ms(),  "tdupdate_ms");

    if(dwgVersion >= R2004) {
        BS_ARCHIVE(bitcode::BL, in, m_pHdr->unknown15(), "unknown15");
        BS_ARCHIVE(bitcode::BL, in, m_pHdr->unknown16(), "unknown16");
        BS_ARCHIVE(bitcode::BL, in, m_pHdr->unknown17(), "unknown17");
    }

    // common
    BS_ARCHIVE(bitcode::BL, in, m_pHdr->tdindwg_days(),    "tdindwg_days");
    BS_ARCHIVE(bitcode::BL, in, m_pHdr->tdindwg_ms(),      "tdindwg_ms");
    BS_ARCHIVE(bitcode::BL, in, m_pHdr->tdusrtimer_days(), "tdusrtimer_days");
    BS_ARCHIVE(bitcode::BL, in, m_pHdr->tdusrtimer_ms(),   "tdusrtimer_ms");
    BS_ARCHIVE(bitcode::CMC, in, m_pHdr->cecolor(),        "cecolor");
    BS_ARCHIVE(OcDbObjectId, in, m_pHdr->handseed(),       "handseed");
    BS_ARCHIVE(OcDbObjectId, in, m_pHdr->clayer(),         "clayer");
    BS_ARCHIVE(OcDbObjectId, in, m_pHdr->textstyle(),      "textstyle");
    BS_ARCHIVE(OcDbObjectId, in, m_pHdr->celtype(),        "celtype");

    // R2007+
    if(dwgVersion >= R2007) {
        BS_ARCHIVE(OcDbObjectId, in, m_pHdr->cmaterial(), "cmaterial");
    }

    // commmon
    BS_ARCHIVE(OcDbObjectId, in, m_pHdr->dimstyle(), "dimstyle");
    BS_ARCHIVE(OcDbObjectId, in, m_pHdr->cmlstyle(), "cmlstyle");

    // R2000+ only
    if(dwgVersion >= R2000) {
        BS_ARCHIVE(bitcode::BD, in, m_pHdr->psvpscale(), "psvpscale");
    }

    // common
    VLOG(4) << "****** Begin PS read *****";
    BS_ARCHIVE(bitcode::BD3, in, m_pHdr->pinsbase(),  "pinsbase");
    BS_ARCHIVE(bitcode::BD3, in, m_pHdr->pextmin(),   "pextmin");
    BS_ARCHIVE(bitcode::BD3, in, m_pHdr->pextmax(),   "pextmax");
    BS_ARCHIVE(bitcode::RD2, in, m_pHdr->plimmin(),   "plimmin");
    BS_ARCHIVE(bitcode::RD2, in, m_pHdr->plimmax(),   "plimmax");
    BS_ARCHIVE(bitcode::BD, in, m_pHdr->pelevation(), "pelevation");
    BS_ARCHIVE(bitcode::BD3, in, m_pHdr->pucsorg(),   "pucsorg");
    BS_ARCHIVE(bitcode::BD3, in, m_pHdr->pucsxdir(),  "pucsxdir");
    BS_ARCHIVE(bitcode::BD3, in, m_pHdr->pucsydir(),  "pucsydir");
    BS_ARCHIVE(OcDbObjectId, in, m_pHdr->pucsname(),  "pucsname");

    if(dwgVersion >= R2000) {
        BS_ARCHIVE(OcDbObjectId, in, m_pHdr->pucsbase(),      "pucsbase");
        BS_ARCHIVE(bitcode::BS, in, m_pHdr->pucsorthoview(),  "pucsorthoview");
        BS_ARCHIVE(OcDbObjectId, in, m_pHdr->pucsorthoref(),  "pucsorthoref");
        BS_ARCHIVE(bitcode::BD3, in, m_pHdr->pucsorgtop(),    "pucsorgtop");
        BS_ARCHIVE(bitcode::BD3, in, m_pHdr->pucsorgbottom(), "pucsorgbottom");
        BS_ARCHIVE(bitcode::BD3, in, m_pHdr->pucsorgleft(),   "pucsorgleft");
        BS_ARCHIVE(bitcode::BD3, in, m_pHdr->pucsorgright(),  "pucsorgright");
        BS_ARCHIVE(bitcode::BD3, in, m_pHdr->pucsorgfront(),  "pucsorgfront");
        BS_ARCHIVE(bitcode::BD3, in, m_pHdr->pucsorgback(),   "pucsorgback");
    }


    // common
    VLOG(4) << "****** Begin MS read *****";
    BS_ARCHIVE(bitcode::BD3, in, m_pHdr->insbase(),  "insbase");
    BS_ARCHIVE(bitcode::BD3, in, m_pHdr->extmin(),   "extmin");
    BS_ARCHIVE(bitcode::BD3, in, m_pHdr->extmax(),   "extmax");
    BS_ARCHIVE(bitcode::RD2, in, m_pHdr->limmin(),   "limmin");
    BS_ARCHIVE(bitcode::RD2, in, m_pHdr->limmax(),   "limmax");
    BS_ARCHIVE(bitcode::BD, in, m_pHdr->elevation(), "elevation");
    BS_ARCHIVE(bitcode::BD3, in, m_pHdr->ucsorg(),   "ucsorg");
    BS_ARCHIVE(bitcode::BD3, in, m_pHdr->ucsxdir(),  "ucsxdir");
    BS_ARCHIVE(bitcode::BD3, in, m_pHdr->ucsydir(),  "ucsydir");
    BS_ARCHIVE(OcDbObjectId, in, m_pHdr->ucsname(),  "ucsname");

    if(dwgVersion >= R2000) {
        BS_ARCHIVE(OcDbObjectId, in, m_pHdr->ucsbase(),      "ucsbase");
        BS_ARCHIVE(bitcode::BS, in, m_pHdr->ucsorthoview(),  "ucsorthoview");
        BS_ARCHIVE(OcDbObjectId, in, m_pHdr->ucsorthoref(),  "ucsorthoref");
        BS_ARCHIVE(bitcode::BD3, in, m_pHdr->ucsorgtop(),    "ucsorgtop");
        BS_ARCHIVE(bitcode::BD3, in, m_pHdr->ucsorgbottom(), "ucsorgbottom");
        BS_ARCHIVE(bitcode::BD3, in, m_pHdr->ucsorgleft(),   "ucsorgleft");
        BS_ARCHIVE(bitcode::BD3, in, m_pHdr->ucsorgright(),  "ucsorgright");
        BS_ARCHIVE(bitcode::BD3, in, m_pHdr->ucsorgfront(),  "ucsorgfront");
        BS_ARCHIVE(bitcode::BD3, in, m_pHdr->ucsorgback(),   "ucsorgback");
        BS_ARCHIVE(bitcode::TV, in, m_pHdr->dimpost(),       "dimpost");
        BS_ARCHIVE(bitcode::TV, in, m_pHdr->dimapost(),      "dimapost");
    }

    if(dwgVersion == R13 || dwgVersion == R14) {
        BS_ARCHIVE(bitcode::B, in, m_pHdr->dimtol(),     "dimtol");
        BS_ARCHIVE(bitcode::B, in, m_pHdr->dimlim(),     "dimlim");
        BS_ARCHIVE(bitcode::B, in, m_pHdr->dimtih(),     "dimtih");
        BS_ARCHIVE(bitcode::B, in, m_pHdr->dimtoh(),     "dimtoh");
        BS_ARCHIVE(bitcode::B, in, m_pHdr->dimse1(),     "dimse1");
        BS_ARCHIVE(bitcode::B, in, m_pHdr->dimse2(),     "dimse2");
        BS_ARCHIVE(bitcode::B, in, m_pHdr->dimalt(),     "dimalt");
        BS_ARCHIVE(bitcode::B, in, m_pHdr->dimtofl(),    "dimtofl");
        BS_ARCHIVE(bitcode::B, in, m_pHdr->dimsah(),     "dimsah");
        BS_ARCHIVE(bitcode::B, in, m_pHdr->dimtix(),     "dimtix");
        BS_ARCHIVE(bitcode::B, in, m_pHdr->dimsoxd(),    "dimsoxd");
        BS_ARCHIVE(bitcode::RC, in, m_pHdr->dimaltd(),   "dimaltd");
        BS_ARCHIVE(bitcode::RC, in, m_pHdr->dimzin(),    "dimzin");
        BS_ARCHIVE(bitcode::B, in, m_pHdr->dimsd1(),     "dimsd1");
        BS_ARCHIVE(bitcode::B, in, m_pHdr->dimsd2(),     "dimsd2");
        BS_ARCHIVE(bitcode::RC, in, m_pHdr->dimtolj(),   "dimtolj");
        BS_ARCHIVE(bitcode::RC, in, m_pHdr->dimjust(),   "dimjust");
        BS_ARCHIVE(bitcode::RC, in, m_pHdr->dimfit(),    "dimfit");
        BS_ARCHIVE(bitcode::B, in, m_pHdr->dimupt(),     "dimupt");
        BS_ARCHIVE(bitcode::RC, in, m_pHdr->dimtzin(),   "dimtzin");
        BS_ARCHIVE(bitcode::RC, in, m_pHdr->dimaltz(),   "dimaltz");
        BS_ARCHIVE(bitcode::RC, in, m_pHdr->dimalttz(),  "dimalttz");
        BS_ARCHIVE(bitcode::RC, in, m_pHdr->dimtad(),    "dimtad");
        BS_ARCHIVE(bitcode::BS, in, m_pHdr->dimunit(),   "dimunit");
        BS_ARCHIVE(bitcode::BS, in, m_pHdr->dimaunit(),  "dimaunit");
        BS_ARCHIVE(bitcode::BS, in, m_pHdr->dimdec(),    "dimdec");
        BS_ARCHIVE(bitcode::BS, in, m_pHdr->dimtdec(),   "dimtdec");
        BS_ARCHIVE(bitcode::BS, in, m_pHdr->dimaltu(),   "dimaltu");
        BS_ARCHIVE(bitcode::BS, in, m_pHdr->dimalttd(),  "dimalttd");
        BS_ARCHIVE(OcDbObjectId, in, m_pHdr->dimtxsty(), "dimtxsty");
    }

////////////////////////////////////////////////////////////////////////////
// common
    BS_ARCHIVE(bitcode::BD, in, m_pHdr->dimscale(), "dimscale")
    BS_ARCHIVE(bitcode::BD, in, m_pHdr->dimasz(),   "dimasz");
    BS_ARCHIVE(bitcode::BD, in, m_pHdr->dimexo(),   "dimexo");
    BS_ARCHIVE(bitcode::BD, in, m_pHdr->dimdli(),   "dimdli");
    BS_ARCHIVE(bitcode::BD, in, m_pHdr->dimexe(),   "dimexe");
    BS_ARCHIVE(bitcode::BD, in, m_pHdr->dimrnd(),   "dimrnd");
    BS_ARCHIVE(bitcode::BD, in, m_pHdr->dimdle(),   "dimdle");
    BS_ARCHIVE(bitcode::BD, in, m_pHdr->dimtp(),    "dimtp");
    BS_ARCHIVE(bitcode::BD, in, m_pHdr->dimtm(),    "dimtm");

// R2007+
    if(dwgVersion >= R2007) {
        BS_ARCHIVE(bitcode::BD, in, m_pHdr-> dimfxl(),      "dimfxl");
        BS_ARCHIVE(bitcode::BD, in, m_pHdr-> dimjogang(),   "dimjogang");
        BS_ARCHIVE(bitcode::BS, in, m_pHdr-> dimtfill(),    "dimtfill");
        BS_ARCHIVE(bitcode::CMC, in, m_pHdr->dimtfillclr(), "dimtfillclr");
    }

// R2000+
    if(dwgVersion >= R2000) {
        BS_ARCHIVE(bitcode::B, in, m_pHdr-> dimtol(),  "dimtol");
        BS_ARCHIVE(bitcode::B, in, m_pHdr-> dimlim(),  "dimlim");
        BS_ARCHIVE(bitcode::B, in, m_pHdr-> dimtih(),  "dimtih");
        BS_ARCHIVE(bitcode::B, in, m_pHdr-> dimtoh(),  "dimtoh");
        BS_ARCHIVE(bitcode::B, in, m_pHdr-> dimse1(),  "dimse1");
        BS_ARCHIVE(bitcode::B, in, m_pHdr-> dimse2(),  "dimse2");
        BS_ARCHIVE(bitcode::BS, in, m_pHdr->dimtad(),  "dimtad");
        BS_ARCHIVE(bitcode::BS, in, m_pHdr->dimzin(),  "dimzin");
        BS_ARCHIVE(bitcode::BS, in, m_pHdr->dimazin(), "dimazin");
    }

// R2007+
    if(dwgVersion >= R2007) {
        BS_ARCHIVE(bitcode::BS, in, m_pHdr->dimarcsym(), "dimarcsym");
    }

// common
    BS_ARCHIVE(bitcode::BD, in, m_pHdr->dimtxt(),  "dimtxt");
    BS_ARCHIVE(bitcode::BD, in, m_pHdr->dimcen(),  "dimcen");
    BS_ARCHIVE(bitcode::BD, in, m_pHdr->dimtsz(),  "dimtsz");
    BS_ARCHIVE(bitcode::BD, in, m_pHdr->dimaltf(), "dimaltf");
    BS_ARCHIVE(bitcode::BD, in, m_pHdr->dimlfac(), "dimlfac");
    BS_ARCHIVE(bitcode::BD, in, m_pHdr->dimtvp(),  "dimtvp");
    BS_ARCHIVE(bitcode::BD, in, m_pHdr->dimtfac(), "dimtfac");
    BS_ARCHIVE(bitcode::BD, in, m_pHdr->dimgap(),  "dimgap");

// R13-R14
    if(dwgVersion == R13 || dwgVersion == R14) {
        BS_ARCHIVE(bitcode::T, in, m_pHdr->dimpost(),  "dimpost");
        BS_ARCHIVE(bitcode::T, in, m_pHdr->dimapost(), "dimapost");
        BS_ARCHIVE(bitcode::T, in, m_pHdr->dimblk(),   "dimblk");
        BS_ARCHIVE(bitcode::T, in, m_pHdr->dimblk1(),  "dimblk1");
        BS_ARCHIVE(bitcode::T, in, m_pHdr->dimblk2(),  "dimblk2");
    }

// R2000+
    if(dwgVersion >= R2000) {
        BS_ARCHIVE(bitcode::BD, in, m_pHdr->dimaltrnd(), "dimaltrnd");
        BS_ARCHIVE(bitcode::B,  in, m_pHdr->dimalt(),    "dimalt");
        BS_ARCHIVE(bitcode::BS, in, m_pHdr->dimaltd(),   "dimaltd");
        BS_ARCHIVE(bitcode::B,  in, m_pHdr->dimtofl(),   "dimtofl");
        BS_ARCHIVE(bitcode::B,  in, m_pHdr->dimsah(),    "dimsah");
        BS_ARCHIVE(bitcode::B,  in, m_pHdr->dimtix(),    "dimtix");
        BS_ARCHIVE(bitcode::B,  in, m_pHdr->dimsoxd(),   "dimsoxd");
    }

// common
    BS_ARCHIVE(bitcode::CMC, in, m_pHdr->dimclrd(), "dimclrd");
    BS_ARCHIVE(bitcode::CMC, in, m_pHdr->dimclre(), "dimclre");
    BS_ARCHIVE(bitcode::CMC, in, m_pHdr->dimclrt(), "dimclrt");

// R2000+
    if(dwgVersion >= R2000) {
        BS_ARCHIVE(bitcode::BS, in, m_pHdr->dimadec(),  "dimadec");
        BS_ARCHIVE(bitcode::BS, in, m_pHdr->dimdec(),   "dimdec");
        BS_ARCHIVE(bitcode::BS, in, m_pHdr->dimtdec(),  "dimtdec");
        BS_ARCHIVE(bitcode::BS, in, m_pHdr->dimaltu(),  "dimaltu");
        BS_ARCHIVE(bitcode::BS, in, m_pHdr->dimalttd(), "dimalttd");
        BS_ARCHIVE(bitcode::BS, in, m_pHdr->dimaunit(), "dimaunit");
        BS_ARCHIVE(bitcode::BS, in, m_pHdr->dimfrac(),  "dimfrac");
        BS_ARCHIVE(bitcode::BS, in, m_pHdr->dimlunit(), "dimlunit");
        BS_ARCHIVE(bitcode::BS, in, m_pHdr->dimdsep(),  "dimdsep");
        BS_ARCHIVE(bitcode::BS, in, m_pHdr->dimtmove(), "dimtmove");
        BS_ARCHIVE(bitcode::BS, in, m_pHdr->dimjust(),  "dimjust");
        BS_ARCHIVE(bitcode::B,  in, m_pHdr->dimsd1(),   "dimsd1");
        BS_ARCHIVE(bitcode::B,  in, m_pHdr->dimsd2(),   "dimsd2");
        BS_ARCHIVE(bitcode::BS, in, m_pHdr->dimtolj(),  "dimtolj");
        BS_ARCHIVE(bitcode::BS, in, m_pHdr->dimtzin(),  "dimtzin");
        BS_ARCHIVE(bitcode::BS, in, m_pHdr->dimaltz(),  "dimaltz");
        BS_ARCHIVE(bitcode::BS, in, m_pHdr->dimalttz(), "dimalttz");
        BS_ARCHIVE(bitcode::B,  in, m_pHdr->dimupt(),   "dimupt");
        BS_ARCHIVE(bitcode::BS, in, m_pHdr->dimatfit(), "dimatfit");
    }

// R2007+
    if(dwgVersion >= R2007) {
        BS_ARCHIVE(bitcode::B, in, m_pHdr->dimfxlon(), "dimfxlog");
    }

    if(dwgVersion >= R2010) {
//        BS_ARCHIVE(bitcode::B,  in, pHdr->dimtxtdirection(), "dimtxtdirection");
//        BS_ARCHIVE(bitcode::BD, in, pHdr->dimaltmzf(),       "dimaltmzf");
//        BS_ARCHIVE(bitcode::T,  in, pHdr->dimaltmzs(),       "dimaltmzs");
//        BS_ARCHIVE(bitcode::BD, in, pHdr->dimmzf(),          "dimmzf");
//        BS_ARCHIVE(bitcode::T,  in, pHdr->dimmzs(),          "dimmzs");
    }

// R2000+
    if(dwgVersion >= R2000) {
        BS_ARCHIVE(OcDbObjectId, in, m_pHdr->dimtxsty(),  "dimtxsty");
        BS_ARCHIVE(OcDbObjectId, in, m_pHdr->dimldrblk(), "dimldrblk");
        BS_ARCHIVE(OcDbObjectId, in, m_pHdr->dimblkId(),  "dimblkId");
        BS_ARCHIVE(OcDbObjectId, in, m_pHdr->dimblk1Id(), "dimblk1Id");
        BS_ARCHIVE(OcDbObjectId, in, m_pHdr->dimblk2Id(), "dimblk2Id");
    }

// R2007+
    if(dwgVersion >= R2007) {
        BS_ARCHIVE(OcDbObjectId, in, m_pHdr->dimltype(),  "dimltype");
        BS_ARCHIVE(OcDbObjectId, in, m_pHdr->dimltex1(),  "dimltex1");
        BS_ARCHIVE(OcDbObjectId, in, m_pHdr->dimltex2(),  "dimltex2");
    }

// R2000+
    if(dwgVersion >= R2000) {
        BS_ARCHIVE(bitcode::BS, in, m_pHdr->dimlwd(), "dimlwd");
        BS_ARCHIVE(bitcode::BS, in, m_pHdr->dimlwe(), "dimlwe");
    }

// common
    BS_ARCHIVE(OcDbObjectId, in, m_pHdr->blockCtrlId(),    "blockCtrlId");  // CONTROL OBJECT
    BS_ARCHIVE(OcDbObjectId, in, m_pHdr->layerCtrlId(),    "layerCtrlId");    // CONTROL OBJECT
    BS_ARCHIVE(OcDbObjectId, in, m_pHdr->styleCtrlId(),    "styleCtrlId");    // CONTROL OBJECT
    BS_ARCHIVE(OcDbObjectId, in, m_pHdr->linetypeCtrlId(), "linetypeCtrlId"); // CONTROL OBJECT
    BS_ARCHIVE(OcDbObjectId, in, m_pHdr->viewCtrlId(),     "viewCtrlId");     // CONTROL OBJECT
    BS_ARCHIVE(OcDbObjectId, in, m_pHdr->ucsCtrlId(),      "ucsCtrlId");      // CONTROL OBJECT
    BS_ARCHIVE(OcDbObjectId, in, m_pHdr->vportCtrlId(),    "vportCtrlId");    // CONTROL OBJECT
    BS_ARCHIVE(OcDbObjectId, in, m_pHdr->appidCtrlId(),    "appidCtrlId");    // CONTROL OBJECT
    BS_ARCHIVE(OcDbObjectId, in, m_pHdr->dimstyleCtrlId(), "dimstyleCtrlId"); // CONTROL OBJECT

// R13-R15
    if(dwgVersion == R13 || dwgVersion == R14 || dwgVersion == R2000) {
        BS_ARCHIVE(OcDbObjectId, in, m_pHdr->viewport(), "viewport"); // ENTITY HEADER CONTROL OBJECT
    }

// common
    BS_ARCHIVE(OcDbObjectId, in, m_pHdr->dictionaryGroupId(),      "group dictionary Id");
    BS_ARCHIVE(OcDbObjectId, in, m_pHdr->dictionaryMLineStyleId(), "mline style dict Id");
    BS_ARCHIVE(OcDbObjectId, in, m_pHdr->dictionaryNamedObjsId(),  "named objects dict Id");

// R2000+
    if(dwgVersion >= R2000) {
        BS_ARCHIVE(bitcode::BS, in, m_pHdr->tstackalign(),   "tstackalign");
        BS_ARCHIVE(bitcode::BS, in, m_pHdr->tstacksize(),    "tstacksize");
        BS_ARCHIVE(bitcode::TV, in, m_pHdr->hyperlinkbase(), "hyperlinkbase");
        BS_ARCHIVE(bitcode::TV, in, m_pHdr->stylesheet(),    "stylesheet")
        BS_ARCHIVE(OcDbObjectId, in, m_pHdr->dictionaryLayoutsId(),      "layouts dict Id");       // (LAYOUTS)
        BS_ARCHIVE(OcDbObjectId, in, m_pHdr->dictionaryPlotSettingsId(), "plot settings dict Id"); // (PLOTSETTINGS)
        BS_ARCHIVE(OcDbObjectId, in, m_pHdr->dictionaryPlotStylesId(),   "plot styles dict Id");        // (PLOTSTYLES)
    }

// R2004+
    if(dwgVersion >= R2004) {
        BS_ARCHIVE(OcDbObjectId, in, m_pHdr->dictionaryMaterialsId(), "materials dict Id");     // (MATERIALS)
        BS_ARCHIVE(OcDbObjectId, in, m_pHdr->dictionaryColorsId(), "colors dict Id");        // (COLORS)
    }

// R2007+
    if(dwgVersion >= R2007) {
        BS_ARCHIVE(OcDbObjectId, in, m_pHdr->dictionaryVisualStyleId(), "visual style dict Id");  // (VISUALSTYLE)
    }

// R2000+
    if(dwgVersion >= R2000) {
        BS_ARCHIVE(bitcode::BL, in, m_pHdr->flags(), "flags");
        //                      CELWEIGHT       Flags & 0x001F
        //                      ENDCAPS         Flags & 0x0060
        //                      JOINSTYLE       Flags & 0x0180
        //                      LWDISPLAY       !(Flags & 0x0200)
        //                      XEDIT           !(Flags & 0x0400)
        //                      EXTNAMES        Flags & 0x0800
        //                      PSTYLEMODE      Flags & 0x2000
        //                      OLESTARTUP      Flags & 0x4000
        BS_ARCHIVE(bitcode::BS, in, m_pHdr->insunits(),  "insunits");
        BS_ARCHIVE(bitcode::BS, in, m_pHdr->cepsntype(), "cepsntype");
        if(m_pHdr->cepsntype() == 3) {
            // cpsnid only present if m_cepsntype == 3
            BS_ARCHIVE(OcDbObjectId, in, m_pHdr->cpsnid(), "cpsnid");
        }
        BS_ARCHIVE(bitcode::TV, in, m_pHdr->fingerprintguid(), "fingerprintguid");
        BS_ARCHIVE(bitcode::TV, in, m_pHdr->versionguid(), "versionguid");
    }

// R2004+
    if(dwgVersion >= R2004) {
        BS_ARCHIVE(bitcode::RC, in, m_pHdr->sortents(),          "sortents");
        BS_ARCHIVE(bitcode::RC, in, m_pHdr->indexctl(),          "indexctl");
        BS_ARCHIVE(bitcode::RC, in, m_pHdr->hidetext(),          "hidetext");
        BS_ARCHIVE(bitcode::RC, in, m_pHdr->xclipframe(),        "xclipframe");
        BS_ARCHIVE(bitcode::RC, in, m_pHdr->dimassoc(),          "dimassoc");
        BS_ARCHIVE(bitcode::RC, in, m_pHdr->halogap(),           "halogap");
        BS_ARCHIVE(bitcode::BS, in, m_pHdr->obscuredcolor(),     "obscuredcolor");
        BS_ARCHIVE(bitcode::BS, in, m_pHdr->intersectioncolor(), "intersectioncolor");
        BS_ARCHIVE(bitcode::RC, in, m_pHdr->obscuredltype(),     "obscuredltype");
        BS_ARCHIVE(bitcode::RC, in, m_pHdr->intersectiondisplay(), "intersectiondisplay")
        BS_ARCHIVE(bitcode::TV, in, m_pHdr->projectname(),       "projectname");
    }

// common
    BS_ARCHIVE(OcDbObjectId, in, m_pHdr->block_recordPsId(), "ps block record Id");  // (*PAPER_SPACE)
    BS_ARCHIVE(OcDbObjectId, in, m_pHdr->block_recordMsId(), "ms block record Id");  // (*MODEL_SPACE)
    BS_ARCHIVE(OcDbObjectId, in, m_pHdr->ltypeByLayerId(),   "ltype bylayer id");         // (BYLAYER)
    BS_ARCHIVE(OcDbObjectId, in, m_pHdr->ltypeByBlockId(),   "ltype byblock id");         // (BYBLOCK)
    BS_ARCHIVE(OcDbObjectId, in, m_pHdr->ltypeContinuousId(), "ltype continuous LT id");         // (CONTINUOUS)

// R2007+
    if(dwgVersion >= R2007) {
        BS_ARCHIVE(bitcode::B,  in, m_pHdr->cameradisplay(),     "cameradisplay");
        BS_ARCHIVE(bitcode::BL, in, m_pHdr->unknown21(),         "unknown21");
        BS_ARCHIVE(bitcode::BL, in, m_pHdr->unknown22(),         "unknown22");
        BS_ARCHIVE(bitcode::BD, in, m_pHdr->unknown23(),         "unknown23");
        BS_ARCHIVE(bitcode::BD, in, m_pHdr->stepspersec(),       "stepspersec");
        BS_ARCHIVE(bitcode::BD, in, m_pHdr->stepsize(),          "stepsize");
        BS_ARCHIVE(bitcode::BD, in, m_pHdr->dwfprec3d(),         "dwfprec3d");
        BS_ARCHIVE(bitcode::BD, in, m_pHdr->lenslength(),        "lenslength");
        BS_ARCHIVE(bitcode::BD, in, m_pHdr->cameraheight(),      "cameraheight");
        BS_ARCHIVE(bitcode::RC, in, m_pHdr->solidhist(),         "solidhist");
        BS_ARCHIVE(bitcode::RC, in, m_pHdr->showhist(),          "showhist");
        BS_ARCHIVE(bitcode::BD, in, m_pHdr->psolwidth(),         "psolwidth");
        BS_ARCHIVE(bitcode::BD, in, m_pHdr->psolheight(),        "psolheight");
        BS_ARCHIVE(bitcode::BD, in, m_pHdr->loftang1(),          "loftang1");
        BS_ARCHIVE(bitcode::BD, in, m_pHdr->loftang2(),          "loftang2");
        BS_ARCHIVE(bitcode::BD, in, m_pHdr->loftmag1(),          "loftmag1");
        BS_ARCHIVE(bitcode::BD, in, m_pHdr->logtmag2(),          "loftmag2");
        BS_ARCHIVE(bitcode::BS, in, m_pHdr->loftparam(),         "loftparam");
        BS_ARCHIVE(bitcode::RC, in, m_pHdr->loftnormals(),       "loftnormals");
        BS_ARCHIVE(bitcode::BD, in, m_pHdr->latitude(),          "latitude");
        BS_ARCHIVE(bitcode::BD, in, m_pHdr->longitude(),         "longitude");
        BS_ARCHIVE(bitcode::BD, in, m_pHdr->northdirection(),    "northdirection");
        BS_ARCHIVE(bitcode::BL, in, m_pHdr->timezone(),          "timezone");
        BS_ARCHIVE(bitcode::RC, in, m_pHdr->lightglyphdisplay(), "lightglyphdisplay");
        BS_ARCHIVE(bitcode::RC, in, m_pHdr->tilemodelightsynch(), "tilemodelightsynch");
        BS_ARCHIVE(bitcode::RC, in, m_pHdr->dwfframe(),          "dwfframe");
        BS_ARCHIVE(bitcode::RC, in, m_pHdr->dgnframe(),          "dgnframe");
        BS_ARCHIVE(bitcode::B,  in, m_pHdr->unknown47(),         "unknown47");
        BS_ARCHIVE(bitcode::CMC, in, m_pHdr->interferecolor(),   "interferecolor");
        BS_ARCHIVE(OcDbObjectId, in, m_pHdr->interfereobjvsId(), "interfereobjvsId");
        BS_ARCHIVE(OcDbObjectId, in, m_pHdr->interferevpvsId(),  "interferevpvsId");
        BS_ARCHIVE(OcDbObjectId, in, m_pHdr->dragvsId(),         "dragvsId");
        BS_ARCHIVE(bitcode::RC, in, m_pHdr->cshadow(),           "cshadow");
        BS_ARCHIVE(bitcode::BD, in, m_pHdr->unknown53(),         "unknown53");
    }

// R14+
    if(dwgVersion >= R14) {
        BS_ARCHIVE(bitcode::BS, in, m_pHdr->unknown54(), "unknown54");  // short(type 5 / 6 only)  these do not seem to be required,
        BS_ARCHIVE(bitcode::BS, in, m_pHdr->unknown55(), "unknown55");  // short(type 5 / 6 only)  even for type 5.
        BS_ARCHIVE(bitcode::BS, in, m_pHdr->unknown56(), "unknown56");  // short(type 5 / 6 only)
        BS_ARCHIVE(bitcode::BS, in, m_pHdr->unknown57(), "unknown57");  // short(type 5 / 6 only)
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
//    BS_ARCHIVE(bitcode::RS, in, pHdr->crc(), "crc"); // for the data section, starting after the
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

DwgInArchive& operator>>(DwgInArchive& in, OcDfDatabaseHeaderVars & dwgVars)
{
    ASSERT_ARCHIVE_NOT_LOADING(in);
    in.SetError(dwgVars.DecodeData(in));
    return in;
}

END_OCTAVARIUM_NS
