/****************************************************************************
**
** This file is part of DrawGin library. A C++ framework to read and
** write .dwg files formats.
**
** Copyright (C) 2011, 2012, 2013 Paul Kohut.
** All rights reserved.
** Author: Paul Kohut (pkohut2@gmail.com)
**
** DrawGin library is free software; you can redistribute it and/or
** modify it under the terms of either:
**
**   * the GNU Lesser General Public License as published by the Free
**     Software Foundation; either version 3 of the License, or (at your
**     option) any later version.
**
**   * the GNU General Public License as published by the free
**     Software Foundation; either version 2 of the License, or (at your
**     option) any later version.
**
** or both in parallel, as here.
**
** DrawGin library is distributed in the hope that it will be useful,
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
#include "OcDbDatabase.h"
#include "../OcDb/OcDbDatabase_p.h"

#include "../OcBs/OcBsStreamIn.h"
#include "../OcBs/DwgInArchive.h"
#include "OcDfDatabaseHeaderVars.h"
#include "../OcBs/OcBsDwgSentinels.h"




BEGIN_OCTAVARIUM_NS
using namespace std;

OcDfDatabaseHeaderVars::OcDfDatabaseHeaderVars(OcDbDatabasePimpl *& pDb)
    : m_pDb(pDb)
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

    if(!CompareSentinels(sentinelHeaderVarsStart, sentinelData))
    {
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
    BS_ARCHIVE(bitcode::BD, in, m_pDb->unknown1(),  "unknown1");
    BS_ARCHIVE(bitcode::BD, in, m_pDb->unknown2(),  "unknown2");
    BS_ARCHIVE(bitcode::BD, in, m_pDb->unknown3(),  "unknown3");
    BS_ARCHIVE(bitcode::BD, in, m_pDb->unknown4(),  "unknown4");
    BS_ARCHIVE(bitcode::TV, in, m_pDb->unknown5(),  "unknown5");
    BS_ARCHIVE(bitcode::TV, in, m_pDb->unknown6(),  "unknown6");
    BS_ARCHIVE(bitcode::TV, in, m_pDb->unknown7(),  "unknown7");
    BS_ARCHIVE(bitcode::TV, in, m_pDb->unknown8(),  "unknown8");
    BS_ARCHIVE(bitcode::BL, in, m_pDb->unknown9(),  "unknown9");
    BS_ARCHIVE(bitcode::BL, in, m_pDb->unknown10(), "unknown10");

    if(dwgVersion == R13 || dwgVersion == R14)
    {
        BS_ARCHIVE(bitcode::BS, in, m_pDb->unknown11(), "unknown11");
    }

    // common
    BS_ARCHIVE(OcDbObjectId, in, m_pDb->currentVpId(), "currentvpId");
    BS_ARCHIVE(bitcode::B, in, m_pDb->dimaso(),        "dimaso");
    BS_ARCHIVE(bitcode::B, in, m_pDb->dimsho(),        "dimsho");

    if(dwgVersion == R13 || dwgVersion == R14)
    {
        BS_ARCHIVE(bitcode::B, in, m_pDb->dimsav(), "dimsav");
    }

    // common
    BS_ARCHIVE(bitcode::B, in, m_pDb->plinegen(),  "plinegen");
    BS_ARCHIVE(bitcode::B, in, m_pDb->orthomode(), "orthomode");
    BS_ARCHIVE(bitcode::B, in, m_pDb->regenmode(), "regenmode");
    BS_ARCHIVE(bitcode::B, in, m_pDb->fillmode(),  "fillmode");
    BS_ARCHIVE(bitcode::B, in, m_pDb->qtextmode(), "qtextmode");
    BS_ARCHIVE(bitcode::B, in, m_pDb->psltscale(), "psltscale");
    BS_ARCHIVE(bitcode::B, in, m_pDb->limcheck(),  "limcheck");

    if(dwgVersion == R13 || dwgVersion == R14)
    {
        BS_ARCHIVE(bitcode::B, in, m_pDb->blipmode(), "blipmode");
    }

    if(dwgVersion >= R2004)
    {
        BS_ARCHIVE(bitcode::B, in, m_pDb->undocumented(), "undocumented");
    }

    // common
    BS_ARCHIVE(bitcode::B, in, m_pDb->usertimer(), "usertimer");
    BS_ARCHIVE(bitcode::B, in, m_pDb->skpoly(),    "skpoly");
    BS_ARCHIVE(bitcode::B, in, m_pDb->angdir(),    "angdir");
    BS_ARCHIVE(bitcode::B, in, m_pDb->splframe(),  "splframe");

    if(dwgVersion == R13 || dwgVersion == R14)
    {
        BS_ARCHIVE(bitcode::B, in, m_pDb->attreq(), "attreq");
        BS_ARCHIVE(bitcode::B, in, m_pDb->attdia(), "attdia");
    }

    // common
    BS_ARCHIVE(bitcode::B, in, m_pDb->mirrtext(),  "mirrtext");
    BS_ARCHIVE(bitcode::B, in, m_pDb->worldview(), "worldview");

    if(dwgVersion == R13 || dwgVersion == R14)
    {
        BS_ARCHIVE(bitcode::B, in, m_pDb->wireframe(), "wireframe");
    }

    // common
    BS_ARCHIVE(bitcode::B, in, m_pDb->tilemode(),  "tilemode");
    BS_ARCHIVE(bitcode::B, in, m_pDb->plimcheck(), "plimcheck");
    BS_ARCHIVE(bitcode::B, in, m_pDb->visretain(), "visretain");

    if(dwgVersion == R13 || dwgVersion == R14)
    {
        BS_ARCHIVE(bitcode::B, in, m_pDb->delobj(), "delobj");
    }

    // common
    BS_ARCHIVE(bitcode::B, in, m_pDb->dispsilh(),    "dispsilh");
    BS_ARCHIVE(bitcode::B, in, m_pDb->pellipse(),    "pellispe");
    BS_ARCHIVE(bitcode::BS, in, m_pDb->saveimages(), "saveimages");

    if(dwgVersion == R13 || dwgVersion == R14)
    {
        BS_ARCHIVE(bitcode::BS, in, m_pDb->dimsav(), "dimsav");
    }

    // common
    BS_ARCHIVE(bitcode::BS, in, m_pDb->treedepth(), "treedepth");
    BS_ARCHIVE(bitcode::BS, in, m_pDb->lunits(),    "lunits");
    BS_ARCHIVE(bitcode::BS, in, m_pDb->luprec(),    "luprec");
    BS_ARCHIVE(bitcode::BS, in, m_pDb->aunits(),    "aunits");
    BS_ARCHIVE(bitcode::BS, in, m_pDb->auprec(),    "auprec");

    if(dwgVersion == R13 || dwgVersion == R14)
    {
        BS_ARCHIVE(bitcode::BS, in, m_pDb->osmode(), "osmode");
    }

    // common
    BS_ARCHIVE(bitcode::BS, in, m_pDb->attmode(), "attmode");

    if(dwgVersion == R13 || dwgVersion == R14)
    {
        BS_ARCHIVE(bitcode::BS, in, m_pDb->coords(), "coords");
    }

    // common
    BS_ARCHIVE(bitcode::BS, in, m_pDb->pdmode(), "pdmode");

    if(dwgVersion == R13 || dwgVersion == R14)
    {
        BS_ARCHIVE(bitcode::BS, in, m_pDb->pickstyle(), "pickstyle");
    }

    if(dwgVersion >= R2004)
    {
        BS_ARCHIVE(bitcode::BL, in, m_pDb->unknown12(), "unknown12");
        BS_ARCHIVE(bitcode::BL, in, m_pDb->unknown13(), "unknown13");
        BS_ARCHIVE(bitcode::BL, in, m_pDb->unknown14(), "unknown14");
    }

    // common
    BS_ARCHIVE(bitcode::BS, in, m_pDb->useri1(),       "useri1");
    BS_ARCHIVE(bitcode::BS, in, m_pDb->useri2(),       "useri2");
    BS_ARCHIVE(bitcode::BS, in, m_pDb->useri3(),       "useri3");
    BS_ARCHIVE(bitcode::BS, in, m_pDb->useri4(),       "useri4");
    BS_ARCHIVE(bitcode::BS, in, m_pDb->useri5(),       "useri5");
    BS_ARCHIVE(bitcode::BS, in, m_pDb->splinesegs(),   "splinesegs");
    BS_ARCHIVE(bitcode::BS, in, m_pDb->surfu(),        "surfu");
    BS_ARCHIVE(bitcode::BS, in, m_pDb->surfv(),        "surfv");
    BS_ARCHIVE(bitcode::BS, in, m_pDb->surftype(),     "surftype");
    BS_ARCHIVE(bitcode::BS, in, m_pDb->surftab1(),     "surftab1");
    BS_ARCHIVE(bitcode::BS, in, m_pDb->surftab2(),     "surftab2");
    BS_ARCHIVE(bitcode::BS, in, m_pDb->splinetype(),   "splinetype");
    BS_ARCHIVE(bitcode::BS, in, m_pDb->shadedge(),     "shadedge");
    BS_ARCHIVE(bitcode::BS, in, m_pDb->shadedif(),     "shadedif");
    BS_ARCHIVE(bitcode::BS, in, m_pDb->unitmode(),     "unitmode");
    BS_ARCHIVE(bitcode::BS, in, m_pDb->maxactvp(),     "macactvp");
    BS_ARCHIVE(bitcode::BS, in, m_pDb->isolines(),     "isolines");
    BS_ARCHIVE(bitcode::BS, in, m_pDb->cmljust(),      "cmljust");
    BS_ARCHIVE(bitcode::BS, in, m_pDb->textqlty(),     "textqlty");
    BS_ARCHIVE(bitcode::BD, in, m_pDb->ltscale(),      "ltscale");
    BS_ARCHIVE(bitcode::BD, in, m_pDb->textsize(),     "textsize");
    BS_ARCHIVE(bitcode::BD, in, m_pDb->tracewid(),     "tracewid");
    BS_ARCHIVE(bitcode::BD, in, m_pDb->sketchinc(),    "sketchinc");
    BS_ARCHIVE(bitcode::BD, in, m_pDb->filletrad(),    "filletrad");
    BS_ARCHIVE(bitcode::BD, in, m_pDb->thickness(),    "thickness");
    BS_ARCHIVE(bitcode::BD, in, m_pDb->angbase(),      "angbase");
    BS_ARCHIVE(bitcode::BD, in, m_pDb->pdsize(),       "pdsize");
    BS_ARCHIVE(bitcode::BD, in, m_pDb->plinewid(),     "plinewid");
    BS_ARCHIVE(bitcode::BD, in, m_pDb->userr1(),       "userr1");
    BS_ARCHIVE(bitcode::BD, in, m_pDb->userr2(),       "userr2");
    BS_ARCHIVE(bitcode::BD, in, m_pDb->userr3(),       "userr3");
    BS_ARCHIVE(bitcode::BD, in, m_pDb->userr4(),       "userr4");
    BS_ARCHIVE(bitcode::BD, in, m_pDb->userr5(),       "userr5");
    BS_ARCHIVE(bitcode::BD, in, m_pDb->chamfera(),     "chamfera");
    BS_ARCHIVE(bitcode::BD, in, m_pDb->chamferb(),     "chamferb");
    BS_ARCHIVE(bitcode::BD, in, m_pDb->chamferc(),     "chamferc");
    BS_ARCHIVE(bitcode::BD, in, m_pDb->chamferd(),     "chamferd");
    BS_ARCHIVE(bitcode::BD, in, m_pDb->facetres(),     "facetres");
    BS_ARCHIVE(bitcode::BD, in, m_pDb->cmlscale(),     "cmlscale");
    BS_ARCHIVE(bitcode::BD, in, m_pDb->celtscale(),    "celtscale");
    BS_ARCHIVE(bitcode::TV, in, m_pDb->menuname(),     "menuname");
    BS_ARCHIVE(bitcode::BL, in, m_pDb->tdcreate_day(), "tdcreate_day");
    BS_ARCHIVE(bitcode::BL, in, m_pDb->tdcreate_ms(),  "tdcreate_ms");
    BS_ARCHIVE(bitcode::BL, in, m_pDb->tdupdate_day(), "tdupdate_day");
    BS_ARCHIVE(bitcode::BL, in, m_pDb->tdupdate_ms(),  "tdupdate_ms");

    if(dwgVersion >= R2004)
    {
        BS_ARCHIVE(bitcode::BL, in, m_pDb->unknown15(), "unknown15");
        BS_ARCHIVE(bitcode::BL, in, m_pDb->unknown16(), "unknown16");
        BS_ARCHIVE(bitcode::BL, in, m_pDb->unknown17(), "unknown17");
    }

    // common
    BS_ARCHIVE(bitcode::BL, in, m_pDb->tdindwg_days(),    "tdindwg_days");
    BS_ARCHIVE(bitcode::BL, in, m_pDb->tdindwg_ms(),      "tdindwg_ms");
    BS_ARCHIVE(bitcode::BL, in, m_pDb->tdusrtimer_days(), "tdusrtimer_days");
    BS_ARCHIVE(bitcode::BL, in, m_pDb->tdusrtimer_ms(),   "tdusrtimer_ms");
    BS_ARCHIVE(bitcode::CMC, in, m_pDb->cecolor(),        "cecolor");
    BS_ARCHIVE(OcDbObjectId, in, m_pDb->handseed(),       "handseed");
    BS_ARCHIVE(OcDbObjectId, in, m_pDb->clayer(),         "clayer");
    BS_ARCHIVE(OcDbObjectId, in, m_pDb->textstyle(),      "textstyle");
    BS_ARCHIVE(OcDbObjectId, in, m_pDb->celtype(),        "celtype");

    // R2007+
    if(dwgVersion >= R2007)
    {
        BS_ARCHIVE(OcDbObjectId, in, m_pDb->cmaterial(), "cmaterial");
    }

    // commmon
    BS_ARCHIVE(OcDbObjectId, in, m_pDb->dimstyle(), "dimstyle");
    BS_ARCHIVE(OcDbObjectId, in, m_pDb->cmlstyle(), "cmlstyle");

    // R2000+ only
    if(dwgVersion >= R2000)
    {
        BS_ARCHIVE(bitcode::BD, in, m_pDb->psvpscale(), "psvpscale");
    }

    // common
    VLOG(4) << "****** Begin PS read *****";
    BS_ARCHIVE(bitcode::BD3, in, m_pDb->pinsbase(),  "pinsbase");
    BS_ARCHIVE(bitcode::BD3, in, m_pDb->pextmin(),   "pextmin");
    BS_ARCHIVE(bitcode::BD3, in, m_pDb->pextmax(),   "pextmax");
    BS_ARCHIVE(bitcode::RD2, in, m_pDb->plimmin(),   "plimmin");
    BS_ARCHIVE(bitcode::RD2, in, m_pDb->plimmax(),   "plimmax");
    BS_ARCHIVE(bitcode::BD, in, m_pDb->pelevation(), "pelevation");
    BS_ARCHIVE(bitcode::BD3, in, m_pDb->pucsorg(),   "pucsorg");
    BS_ARCHIVE(bitcode::BD3, in, m_pDb->pucsxdir(),  "pucsxdir");
    BS_ARCHIVE(bitcode::BD3, in, m_pDb->pucsydir(),  "pucsydir");
    BS_ARCHIVE(OcDbObjectId, in, m_pDb->pucsname(),  "pucsname");

    if(dwgVersion >= R2000)
    {
        BS_ARCHIVE(OcDbObjectId, in, m_pDb->pucsbase(),      "pucsbase");
        BS_ARCHIVE(bitcode::BS, in, m_pDb->pucsorthoview(),  "pucsorthoview");
        BS_ARCHIVE(OcDbObjectId, in, m_pDb->pucsorthoref(),  "pucsorthoref");
        BS_ARCHIVE(bitcode::BD3, in, m_pDb->pucsorgtop(),    "pucsorgtop");
        BS_ARCHIVE(bitcode::BD3, in, m_pDb->pucsorgbottom(), "pucsorgbottom");
        BS_ARCHIVE(bitcode::BD3, in, m_pDb->pucsorgleft(),   "pucsorgleft");
        BS_ARCHIVE(bitcode::BD3, in, m_pDb->pucsorgright(),  "pucsorgright");
        BS_ARCHIVE(bitcode::BD3, in, m_pDb->pucsorgfront(),  "pucsorgfront");
        BS_ARCHIVE(bitcode::BD3, in, m_pDb->pucsorgback(),   "pucsorgback");
    }

    // common
    VLOG(4) << "****** Begin MS read *****";
    BS_ARCHIVE(bitcode::BD3, in, m_pDb->insbase(),  "insbase");
    BS_ARCHIVE(bitcode::BD3, in, m_pDb->extmin(),   "extmin");
    BS_ARCHIVE(bitcode::BD3, in, m_pDb->extmax(),   "extmax");
    BS_ARCHIVE(bitcode::RD2, in, m_pDb->limmin(),   "limmin");
    BS_ARCHIVE(bitcode::RD2, in, m_pDb->limmax(),   "limmax");
    BS_ARCHIVE(bitcode::BD, in, m_pDb->elevation(), "elevation");
    BS_ARCHIVE(bitcode::BD3, in, m_pDb->ucsorg(),   "ucsorg");
    BS_ARCHIVE(bitcode::BD3, in, m_pDb->ucsxdir(),  "ucsxdir");
    BS_ARCHIVE(bitcode::BD3, in, m_pDb->ucsydir(),  "ucsydir");
    BS_ARCHIVE(OcDbObjectId, in, m_pDb->ucsname(),  "ucsname");

    if(dwgVersion >= R2000)
    {
        BS_ARCHIVE(OcDbObjectId, in, m_pDb->ucsbase(),      "ucsbase");
        BS_ARCHIVE(bitcode::BS, in, m_pDb->ucsorthoview(),  "ucsorthoview");
        BS_ARCHIVE(OcDbObjectId, in, m_pDb->ucsorthoref(),  "ucsorthoref");
        BS_ARCHIVE(bitcode::BD3, in, m_pDb->ucsorgtop(),    "ucsorgtop");
        BS_ARCHIVE(bitcode::BD3, in, m_pDb->ucsorgbottom(), "ucsorgbottom");
        BS_ARCHIVE(bitcode::BD3, in, m_pDb->ucsorgleft(),   "ucsorgleft");
        BS_ARCHIVE(bitcode::BD3, in, m_pDb->ucsorgright(),  "ucsorgright");
        BS_ARCHIVE(bitcode::BD3, in, m_pDb->ucsorgfront(),  "ucsorgfront");
        BS_ARCHIVE(bitcode::BD3, in, m_pDb->ucsorgback(),   "ucsorgback");
        BS_ARCHIVE(bitcode::TV, in, m_pDb->dimpost(),       "dimpost");
        BS_ARCHIVE(bitcode::TV, in, m_pDb->dimapost(),      "dimapost");
    }

    if(dwgVersion == R13 || dwgVersion == R14)
    {
        BS_ARCHIVE(bitcode::B, in, m_pDb->dimtol(),     "dimtol");
        BS_ARCHIVE(bitcode::B, in, m_pDb->dimlim(),     "dimlim");
        BS_ARCHIVE(bitcode::B, in, m_pDb->dimtih(),     "dimtih");
        BS_ARCHIVE(bitcode::B, in, m_pDb->dimtoh(),     "dimtoh");
        BS_ARCHIVE(bitcode::B, in, m_pDb->dimse1(),     "dimse1");
        BS_ARCHIVE(bitcode::B, in, m_pDb->dimse2(),     "dimse2");
        BS_ARCHIVE(bitcode::B, in, m_pDb->dimalt(),     "dimalt");
        BS_ARCHIVE(bitcode::B, in, m_pDb->dimtofl(),    "dimtofl");
        BS_ARCHIVE(bitcode::B, in, m_pDb->dimsah(),     "dimsah");
        BS_ARCHIVE(bitcode::B, in, m_pDb->dimtix(),     "dimtix");
        BS_ARCHIVE(bitcode::B, in, m_pDb->dimsoxd(),    "dimsoxd");
        BS_ARCHIVE(bitcode::RC, in, m_pDb->dimaltd(),   "dimaltd");
        BS_ARCHIVE(bitcode::RC, in, m_pDb->dimzin(),    "dimzin");
        BS_ARCHIVE(bitcode::B, in, m_pDb->dimsd1(),     "dimsd1");
        BS_ARCHIVE(bitcode::B, in, m_pDb->dimsd2(),     "dimsd2");
        BS_ARCHIVE(bitcode::RC, in, m_pDb->dimtolj(),   "dimtolj");
        BS_ARCHIVE(bitcode::RC, in, m_pDb->dimjust(),   "dimjust");
        BS_ARCHIVE(bitcode::RC, in, m_pDb->dimfit(),    "dimfit");
        BS_ARCHIVE(bitcode::B, in, m_pDb->dimupt(),     "dimupt");
        BS_ARCHIVE(bitcode::RC, in, m_pDb->dimtzin(),   "dimtzin");
        BS_ARCHIVE(bitcode::RC, in, m_pDb->dimaltz(),   "dimaltz");
        BS_ARCHIVE(bitcode::RC, in, m_pDb->dimalttz(),  "dimalttz");
        BS_ARCHIVE(bitcode::RC, in, m_pDb->dimtad(),    "dimtad");
        BS_ARCHIVE(bitcode::BS, in, m_pDb->dimunit(),   "dimunit");
        BS_ARCHIVE(bitcode::BS, in, m_pDb->dimaunit(),  "dimaunit");
        BS_ARCHIVE(bitcode::BS, in, m_pDb->dimdec(),    "dimdec");
        BS_ARCHIVE(bitcode::BS, in, m_pDb->dimtdec(),   "dimtdec");
        BS_ARCHIVE(bitcode::BS, in, m_pDb->dimaltu(),   "dimaltu");
        BS_ARCHIVE(bitcode::BS, in, m_pDb->dimalttd(),  "dimalttd");
        BS_ARCHIVE(OcDbObjectId, in, m_pDb->dimtxsty(), "dimtxsty");
    }

////////////////////////////////////////////////////////////////////////////
// common
    BS_ARCHIVE(bitcode::BD, in, m_pDb->dimscale(), "dimscale")
    BS_ARCHIVE(bitcode::BD, in, m_pDb->dimasz(),   "dimasz");
    BS_ARCHIVE(bitcode::BD, in, m_pDb->dimexo(),   "dimexo");
    BS_ARCHIVE(bitcode::BD, in, m_pDb->dimdli(),   "dimdli");
    BS_ARCHIVE(bitcode::BD, in, m_pDb->dimexe(),   "dimexe");
    BS_ARCHIVE(bitcode::BD, in, m_pDb->dimrnd(),   "dimrnd");
    BS_ARCHIVE(bitcode::BD, in, m_pDb->dimdle(),   "dimdle");
    BS_ARCHIVE(bitcode::BD, in, m_pDb->dimtp(),    "dimtp");
    BS_ARCHIVE(bitcode::BD, in, m_pDb->dimtm(),    "dimtm");

// R2007+
    if(dwgVersion >= R2007)
    {
        BS_ARCHIVE(bitcode::BD, in, m_pDb-> dimfxl(),      "dimfxl");
        BS_ARCHIVE(bitcode::BD, in, m_pDb-> dimjogang(),   "dimjogang");
        BS_ARCHIVE(bitcode::BS, in, m_pDb-> dimtfill(),    "dimtfill");
        BS_ARCHIVE(bitcode::CMC, in, m_pDb->dimtfillclr(), "dimtfillclr");
    }

// R2000+
    if(dwgVersion >= R2000)
    {
        BS_ARCHIVE(bitcode::B, in, m_pDb-> dimtol(),  "dimtol");
        BS_ARCHIVE(bitcode::B, in, m_pDb-> dimlim(),  "dimlim");
        BS_ARCHIVE(bitcode::B, in, m_pDb-> dimtih(),  "dimtih");
        BS_ARCHIVE(bitcode::B, in, m_pDb-> dimtoh(),  "dimtoh");
        BS_ARCHIVE(bitcode::B, in, m_pDb-> dimse1(),  "dimse1");
        BS_ARCHIVE(bitcode::B, in, m_pDb-> dimse2(),  "dimse2");
        BS_ARCHIVE(bitcode::BS, in, m_pDb->dimtad(),  "dimtad");
        BS_ARCHIVE(bitcode::BS, in, m_pDb->dimzin(),  "dimzin");
        BS_ARCHIVE(bitcode::BS, in, m_pDb->dimazin(), "dimazin");
    }

// R2007+
    if(dwgVersion >= R2007)
    {
        BS_ARCHIVE(bitcode::BS, in, m_pDb->dimarcsym(), "dimarcsym");
    }

// common
    BS_ARCHIVE(bitcode::BD, in, m_pDb->dimtxt(),  "dimtxt");
    BS_ARCHIVE(bitcode::BD, in, m_pDb->dimcen(),  "dimcen");
    BS_ARCHIVE(bitcode::BD, in, m_pDb->dimtsz(),  "dimtsz");
    BS_ARCHIVE(bitcode::BD, in, m_pDb->dimaltf(), "dimaltf");
    BS_ARCHIVE(bitcode::BD, in, m_pDb->dimlfac(), "dimlfac");
    BS_ARCHIVE(bitcode::BD, in, m_pDb->dimtvp(),  "dimtvp");
    BS_ARCHIVE(bitcode::BD, in, m_pDb->dimtfac(), "dimtfac");
    BS_ARCHIVE(bitcode::BD, in, m_pDb->dimgap(),  "dimgap");

// R13-R14
    if(dwgVersion == R13 || dwgVersion == R14)
    {
        BS_ARCHIVE(bitcode::T, in, m_pDb->dimpost(),  "dimpost");
        BS_ARCHIVE(bitcode::T, in, m_pDb->dimapost(), "dimapost");
        BS_ARCHIVE(bitcode::T, in, m_pDb->dimblk(),   "dimblk");
        BS_ARCHIVE(bitcode::T, in, m_pDb->dimblk1(),  "dimblk1");
        BS_ARCHIVE(bitcode::T, in, m_pDb->dimblk2(),  "dimblk2");
    }

// R2000+
    if(dwgVersion >= R2000)
    {
        BS_ARCHIVE(bitcode::BD, in, m_pDb->dimaltrnd(), "dimaltrnd");
        BS_ARCHIVE(bitcode::B,  in, m_pDb->dimalt(),    "dimalt");
        BS_ARCHIVE(bitcode::BS, in, m_pDb->dimaltd(),   "dimaltd");
        BS_ARCHIVE(bitcode::B,  in, m_pDb->dimtofl(),   "dimtofl");
        BS_ARCHIVE(bitcode::B,  in, m_pDb->dimsah(),    "dimsah");
        BS_ARCHIVE(bitcode::B,  in, m_pDb->dimtix(),    "dimtix");
        BS_ARCHIVE(bitcode::B,  in, m_pDb->dimsoxd(),   "dimsoxd");
    }

// common
    BS_ARCHIVE(bitcode::CMC, in, m_pDb->dimclrd(), "dimclrd");
    BS_ARCHIVE(bitcode::CMC, in, m_pDb->dimclre(), "dimclre");
    BS_ARCHIVE(bitcode::CMC, in, m_pDb->dimclrt(), "dimclrt");

// R2000+
    if(dwgVersion >= R2000)
    {
        BS_ARCHIVE(bitcode::BS, in, m_pDb->dimadec(),  "dimadec");
        BS_ARCHIVE(bitcode::BS, in, m_pDb->dimdec(),   "dimdec");
        BS_ARCHIVE(bitcode::BS, in, m_pDb->dimtdec(),  "dimtdec");
        BS_ARCHIVE(bitcode::BS, in, m_pDb->dimaltu(),  "dimaltu");
        BS_ARCHIVE(bitcode::BS, in, m_pDb->dimalttd(), "dimalttd");
        BS_ARCHIVE(bitcode::BS, in, m_pDb->dimaunit(), "dimaunit");
        BS_ARCHIVE(bitcode::BS, in, m_pDb->dimfrac(),  "dimfrac");
        BS_ARCHIVE(bitcode::BS, in, m_pDb->dimlunit(), "dimlunit");
        BS_ARCHIVE(bitcode::BS, in, m_pDb->dimdsep(),  "dimdsep");
        BS_ARCHIVE(bitcode::BS, in, m_pDb->dimtmove(), "dimtmove");
        BS_ARCHIVE(bitcode::BS, in, m_pDb->dimjust(),  "dimjust");
        BS_ARCHIVE(bitcode::B,  in, m_pDb->dimsd1(),   "dimsd1");
        BS_ARCHIVE(bitcode::B,  in, m_pDb->dimsd2(),   "dimsd2");
        BS_ARCHIVE(bitcode::BS, in, m_pDb->dimtolj(),  "dimtolj");
        BS_ARCHIVE(bitcode::BS, in, m_pDb->dimtzin(),  "dimtzin");
        BS_ARCHIVE(bitcode::BS, in, m_pDb->dimaltz(),  "dimaltz");
        BS_ARCHIVE(bitcode::BS, in, m_pDb->dimalttz(), "dimalttz");
        BS_ARCHIVE(bitcode::B,  in, m_pDb->dimupt(),   "dimupt");
        BS_ARCHIVE(bitcode::BS, in, m_pDb->dimatfit(), "dimatfit");
    }

// R2007+
    if(dwgVersion >= R2007)
    {
        BS_ARCHIVE(bitcode::B, in, m_pDb->dimfxlon(), "dimfxlog");
    }

    if(dwgVersion >= R2010)
    {
//        BS_ARCHIVE(bitcode::B,  in, pHdr->dimtxtdirection(), "dimtxtdirection");
//        BS_ARCHIVE(bitcode::BD, in, pHdr->dimaltmzf(),       "dimaltmzf");
//        BS_ARCHIVE(bitcode::T,  in, pHdr->dimaltmzs(),       "dimaltmzs");
//        BS_ARCHIVE(bitcode::BD, in, pHdr->dimmzf(),          "dimmzf");
//        BS_ARCHIVE(bitcode::T,  in, pHdr->dimmzs(),          "dimmzs");
    }

// R2000+
    if(dwgVersion >= R2000)
    {
        BS_ARCHIVE(OcDbObjectId, in, m_pDb->dimtxsty(),  "dimtxsty");
        BS_ARCHIVE(OcDbObjectId, in, m_pDb->dimldrblk(), "dimldrblk");
        BS_ARCHIVE(OcDbObjectId, in, m_pDb->dimblkId(),  "dimblkId");
        BS_ARCHIVE(OcDbObjectId, in, m_pDb->dimblk1Id(), "dimblk1Id");
        BS_ARCHIVE(OcDbObjectId, in, m_pDb->dimblk2Id(), "dimblk2Id");
    }

// R2007+
    if(dwgVersion >= R2007)
    {
        BS_ARCHIVE(OcDbObjectId, in, m_pDb->dimltype(),  "dimltype");
        BS_ARCHIVE(OcDbObjectId, in, m_pDb->dimltex1(),  "dimltex1");
        BS_ARCHIVE(OcDbObjectId, in, m_pDb->dimltex2(),  "dimltex2");
    }

// R2000+
    if(dwgVersion >= R2000)
    {
        BS_ARCHIVE(bitcode::BS, in, m_pDb->dimlwd(), "dimlwd");
        BS_ARCHIVE(bitcode::BS, in, m_pDb->dimlwe(), "dimlwe");
    }

// common
    BS_ARCHIVE(OcDbObjectId, in, m_pDb->blockCtrlId(),    "blockCtrlId");  // CONTROL OBJECT
    BS_ARCHIVE(OcDbObjectId, in, m_pDb->layerCtrlId(),    "layerCtrlId");    // CONTROL OBJECT
    BS_ARCHIVE(OcDbObjectId, in, m_pDb->styleCtrlId(),    "styleCtrlId");    // CONTROL OBJECT
    BS_ARCHIVE(OcDbObjectId, in, m_pDb->linetypeCtrlId(), "linetypeCtrlId"); // CONTROL OBJECT
    BS_ARCHIVE(OcDbObjectId, in, m_pDb->viewCtrlId(),     "viewCtrlId");     // CONTROL OBJECT
    BS_ARCHIVE(OcDbObjectId, in, m_pDb->ucsCtrlId(),      "ucsCtrlId");      // CONTROL OBJECT
    BS_ARCHIVE(OcDbObjectId, in, m_pDb->vportCtrlId(),    "vportCtrlId");    // CONTROL OBJECT
    BS_ARCHIVE(OcDbObjectId, in, m_pDb->appidCtrlId(),    "appidCtrlId");    // CONTROL OBJECT
    BS_ARCHIVE(OcDbObjectId, in, m_pDb->dimstyleCtrlId(), "dimstyleCtrlId"); // CONTROL OBJECT

// R13-R15
    if(dwgVersion == R13 || dwgVersion == R14 || dwgVersion == R2000)
    {
        BS_ARCHIVE(OcDbObjectId, in, m_pDb->viewport(), "viewport"); // ENTITY HEADER CONTROL OBJECT
    }

// common
    BS_ARCHIVE(OcDbObjectId, in, m_pDb->dictionaryGroupId(),      "group dictionary Id");
    BS_ARCHIVE(OcDbObjectId, in, m_pDb->dictionaryMLineStyleId(), "mline style dict Id");
    BS_ARCHIVE(OcDbObjectId, in, m_pDb->dictionaryNamedObjsId(),  "named objects dict Id");

// R2000+
    if(dwgVersion >= R2000)
    {
        BS_ARCHIVE(bitcode::BS, in, m_pDb->tstackalign(),   "tstackalign");
        BS_ARCHIVE(bitcode::BS, in, m_pDb->tstacksize(),    "tstacksize");
        BS_ARCHIVE(bitcode::TV, in, m_pDb->hyperlinkbase(), "hyperlinkbase");
        BS_ARCHIVE(bitcode::TV, in, m_pDb->stylesheet(),    "stylesheet")
        BS_ARCHIVE(OcDbObjectId, in, m_pDb->dictionaryLayoutsId(),      "layouts dict Id");       // (LAYOUTS)
        BS_ARCHIVE(OcDbObjectId, in, m_pDb->dictionaryPlotSettingsId(), "plot settings dict Id"); // (PLOTSETTINGS)
        BS_ARCHIVE(OcDbObjectId, in, m_pDb->dictionaryPlotStylesId(),   "plot styles dict Id");        // (PLOTSTYLES)
    }

// R2004+
    if(dwgVersion >= R2004)
    {
        BS_ARCHIVE(OcDbObjectId, in, m_pDb->dictionaryMaterialsId(), "materials dict Id");     // (MATERIALS)
        BS_ARCHIVE(OcDbObjectId, in, m_pDb->dictionaryColorsId(), "colors dict Id");        // (COLORS)
    }

// R2007+
    if(dwgVersion >= R2007)
    {
        BS_ARCHIVE(OcDbObjectId, in, m_pDb->dictionaryVisualStyleId(), "visual style dict Id");  // (VISUALSTYLE)
    }

// R2000+
    if(dwgVersion >= R2000)
    {
        BS_ARCHIVE(bitcode::BL, in, m_pDb->flags(), "flags");
        //                      CELWEIGHT       Flags & 0x001F
        //                      ENDCAPS         Flags & 0x0060
        //                      JOINSTYLE       Flags & 0x0180
        //                      LWDISPLAY       !(Flags & 0x0200)
        //                      XEDIT           !(Flags & 0x0400)
        //                      EXTNAMES        Flags & 0x0800
        //                      PSTYLEMODE      Flags & 0x2000
        //                      OLESTARTUP      Flags & 0x4000
        BS_ARCHIVE(bitcode::BS, in, m_pDb->insunits(),  "insunits");
        BS_ARCHIVE(bitcode::BS, in, m_pDb->cepsntype(), "cepsntype");

        if(m_pDb->cepsntype() == 3)
        {
            // cpsnid only present if m_cepsntype == 3
            BS_ARCHIVE(OcDbObjectId, in, m_pDb->cpsnid(), "cpsnid");
        }

        BS_ARCHIVE(bitcode::TV, in, m_pDb->fingerprintguid(), "fingerprintguid");
        BS_ARCHIVE(bitcode::TV, in, m_pDb->versionguid(), "versionguid");
    }

// R2004+
    if(dwgVersion >= R2004)
    {
        BS_ARCHIVE(bitcode::RC, in, m_pDb->sortents(),          "sortents");
        BS_ARCHIVE(bitcode::RC, in, m_pDb->indexctl(),          "indexctl");
        BS_ARCHIVE(bitcode::RC, in, m_pDb->hidetext(),          "hidetext");
        BS_ARCHIVE(bitcode::RC, in, m_pDb->xclipframe(),        "xclipframe");
        BS_ARCHIVE(bitcode::RC, in, m_pDb->dimassoc(),          "dimassoc");
        BS_ARCHIVE(bitcode::RC, in, m_pDb->halogap(),           "halogap");
        BS_ARCHIVE(bitcode::BS, in, m_pDb->obscuredcolor(),     "obscuredcolor");
        BS_ARCHIVE(bitcode::BS, in, m_pDb->intersectioncolor(), "intersectioncolor");
        BS_ARCHIVE(bitcode::RC, in, m_pDb->obscuredltype(),     "obscuredltype");
        BS_ARCHIVE(bitcode::RC, in, m_pDb->intersectiondisplay(), "intersectiondisplay")
        BS_ARCHIVE(bitcode::TV, in, m_pDb->projectname(),       "projectname");
    }

// common
    BS_ARCHIVE(OcDbObjectId, in, m_pDb->block_recordPsId(), "ps block record Id");  // (*PAPER_SPACE)
    BS_ARCHIVE(OcDbObjectId, in, m_pDb->block_recordMsId(), "ms block record Id");  // (*MODEL_SPACE)
    BS_ARCHIVE(OcDbObjectId, in, m_pDb->ltypeByLayerId(),   "ltype bylayer id");         // (BYLAYER)
    BS_ARCHIVE(OcDbObjectId, in, m_pDb->ltypeByBlockId(),   "ltype byblock id");         // (BYBLOCK)
    BS_ARCHIVE(OcDbObjectId, in, m_pDb->ltypeContinuousId(), "ltype continuous LT id");         // (CONTINUOUS)

// R2007+
    if(dwgVersion >= R2007)
    {
        BS_ARCHIVE(bitcode::B,  in, m_pDb->cameradisplay(),     "cameradisplay");
        BS_ARCHIVE(bitcode::BL, in, m_pDb->unknown21(),         "unknown21");
        BS_ARCHIVE(bitcode::BL, in, m_pDb->unknown22(),         "unknown22");
        BS_ARCHIVE(bitcode::BD, in, m_pDb->unknown23(),         "unknown23");
        BS_ARCHIVE(bitcode::BD, in, m_pDb->stepspersec(),       "stepspersec");
        BS_ARCHIVE(bitcode::BD, in, m_pDb->stepsize(),          "stepsize");
        BS_ARCHIVE(bitcode::BD, in, m_pDb->dwfprec3d(),         "dwfprec3d");
        BS_ARCHIVE(bitcode::BD, in, m_pDb->lenslength(),        "lenslength");
        BS_ARCHIVE(bitcode::BD, in, m_pDb->cameraheight(),      "cameraheight");
        BS_ARCHIVE(bitcode::RC, in, m_pDb->solidhist(),         "solidhist");
        BS_ARCHIVE(bitcode::RC, in, m_pDb->showhist(),          "showhist");
        BS_ARCHIVE(bitcode::BD, in, m_pDb->psolwidth(),         "psolwidth");
        BS_ARCHIVE(bitcode::BD, in, m_pDb->psolheight(),        "psolheight");
        BS_ARCHIVE(bitcode::BD, in, m_pDb->loftang1(),          "loftang1");
        BS_ARCHIVE(bitcode::BD, in, m_pDb->loftang2(),          "loftang2");
        BS_ARCHIVE(bitcode::BD, in, m_pDb->loftmag1(),          "loftmag1");
        BS_ARCHIVE(bitcode::BD, in, m_pDb->logtmag2(),          "loftmag2");
        BS_ARCHIVE(bitcode::BS, in, m_pDb->loftparam(),         "loftparam");
        BS_ARCHIVE(bitcode::RC, in, m_pDb->loftnormals(),       "loftnormals");
        BS_ARCHIVE(bitcode::BD, in, m_pDb->latitude(),          "latitude");
        BS_ARCHIVE(bitcode::BD, in, m_pDb->longitude(),         "longitude");
        BS_ARCHIVE(bitcode::BD, in, m_pDb->northdirection(),    "northdirection");
        BS_ARCHIVE(bitcode::BL, in, m_pDb->timezone(),          "timezone");
        BS_ARCHIVE(bitcode::RC, in, m_pDb->lightglyphdisplay(), "lightglyphdisplay");
        BS_ARCHIVE(bitcode::RC, in, m_pDb->tilemodelightsynch(), "tilemodelightsynch");
        BS_ARCHIVE(bitcode::RC, in, m_pDb->dwfframe(),          "dwfframe");
        BS_ARCHIVE(bitcode::RC, in, m_pDb->dgnframe(),          "dgnframe");
        BS_ARCHIVE(bitcode::B,  in, m_pDb->unknown47(),         "unknown47");
        BS_ARCHIVE(bitcode::CMC, in, m_pDb->interferecolor(),   "interferecolor");
        BS_ARCHIVE(OcDbObjectId, in, m_pDb->interfereobjvsId(), "interfereobjvsId");
        BS_ARCHIVE(OcDbObjectId, in, m_pDb->interferevpvsId(),  "interferevpvsId");
        BS_ARCHIVE(OcDbObjectId, in, m_pDb->dragvsId(),         "dragvsId");
        BS_ARCHIVE(bitcode::RC, in, m_pDb->cshadow(),           "cshadow");
        BS_ARCHIVE(bitcode::BD, in, m_pDb->unknown53(),         "unknown53");
    }

// R14+
    if(dwgVersion >= R14)
    {
        BS_ARCHIVE(bitcode::BS, in, m_pDb->unknown54(), "unknown54");  // short(type 5 / 6 only)  these do not seem to be required,
        BS_ARCHIVE(bitcode::BS, in, m_pDb->unknown55(), "unknown55");  // short(type 5 / 6 only)  even for type 5.
        BS_ARCHIVE(bitcode::BS, in, m_pDb->unknown56(), "unknown56");  // short(type 5 / 6 only)
        BS_ARCHIVE(bitcode::BS, in, m_pDb->unknown57(), "unknown57");  // short(type 5 / 6 only)
    }

    in.AdvanceToByteBoundary();

    if(size != in.FilePosition() - startPos)
    {
        LOG(ERROR) << "File position should be "
                   << startPos + size << " instead of "
                   << in.FilePosition();
    }

    uint16_t fileCRC, calcedCRC = in.CalcedCRC();
    in.ReadCRC(fileCRC); //  >> (bitcode::RS&) crc1;

    if(calcedCRC != fileCRC)
    {
        LOG(ERROR) << "file section and calced CRC do not match";
        LOG(ERROR) << "Header varibles CRC = " << hex << showbase << fileCRC;
        LOG(ERROR) << "Calced CRC          = " << hex << showbase << calcedCRC;
    }
    else
    {
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
    if(!CompareSentinels(sentinelHeaderVarsEnd, sentinelData))
    {
        std::stringstream ss;

        for(int i =0; i < 16; ++i)
        {
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
