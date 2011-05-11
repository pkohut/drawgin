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
#include "../OcBs/DwgInArchive.h"
#include "OcDbHeaderVars.h"
#include "../OcBs/OcBsDwgSentinels.h"


BEGIN_OCTAVARIUM_NS
#define ASSERT_ARCHIVE_NOT_LOADING assert(in.ArchiveFlag() == DwgInArchive::LOADING)

OcDbHeaderVars::OcDbHeaderVars(void)
{
}

OcDbHeaderVars::~OcDbHeaderVars(void)
{
}

OcApp::ErrorStatus OcDbHeaderVars::DecodeData(DwgInArchive& in)
{
    ASSERT_ARCHIVE_NOT_LOADING;
    bitcode::RC sentinelData[16];
    in.ReadRC(sentinelData, 16);
    if(!CompareSentinels(sentinelHeaderVarsStart, sentinelData)) {
        return OcApp::eInvalidImageDataSentinel;
    }
    const DWG_VERSION dwgVersion = in.Version();
    int size;
    //if(dwgVersion == R2007) {
    in >> ((bitcode::RL&)size);
    //}

    in >> (bitcode::BD&) m_unknown1;
    in >> (bitcode::BD&) m_unknown2;
    in >> (bitcode::BD&) m_unknown3;
    in >> (bitcode::BD&) m_unknown4;

    in >> (bitcode::TV&) m_unknown5;
    in >> (bitcode::TV&) m_unknown6;
    in >> (bitcode::TV&) m_unknown7;
    in >> (bitcode::TV&) m_unknown8;

    in >> (bitcode::BL&) m_unknown9;
    in >> (bitcode::BL&) m_unknown10;

    if(dwgVersion == R13 || dwgVersion == R14) {
        in >> (bitcode::BS&) m_unknown11;
    }

    in.ReadHandle(m_currentVpId);

    in >> (bitcode::B&) m_dimaso;
    in >> (bitcode::B&) m_dimsho;

    if(dwgVersion == R13 || dwgVersion == R14) {
        in >> (bitcode::B&) m_dimsav;
    }
    in >> (bitcode::B&) m_plinegen;
    in >> (bitcode::B&) m_orthomode;
    in >> (bitcode::B&) m_regenmode;
    in >> (bitcode::B&) m_fillmode;
    in >> (bitcode::B&) m_qtextmode;
    in >> (bitcode::B&) m_psltscale;
    in >> (bitcode::B&) m_limcheck;
    if(dwgVersion == R13 || dwgVersion == R14) {
        in >> (bitcode::B&) m_blipmode;
    }

    if(dwgVersion >= R2004) {
        in >> (bitcode::B&) m_undocumented;
    }

    in >> (bitcode::B&) m_usertimer;
    in >> (bitcode::B&) m_skpoly;
    in >> (bitcode::B&) m_angdir;
    in >> (bitcode::B&) m_splframe;
    if(dwgVersion == R13 || dwgVersion == R14) {
        in >> (bitcode::B&) m_attreq;
        in >> (bitcode::B&) m_attdia;
    }
    in >> (bitcode::B&) m_mirrtext;
    in >> (bitcode::B&) m_worldview;

    if(dwgVersion == R13 || dwgVersion == R14) {
        in >> (bitcode::B&) m_wireframe;
    }

    in >> (bitcode::B&) m_tilemode;
    in >> (bitcode::B&) m_plimcheck;
    in >> (bitcode::B&) m_visretain;
    if(dwgVersion == R13 || dwgVersion == R14) {
        in >> (bitcode::B&) m_delobj;
    }
    in >> (bitcode::B&) m_dispsilh;
    in >> (bitcode::B&) m_pellipse;
    in >> (bitcode::BS&) m_saveimages;
    if(dwgVersion == R13 || dwgVersion == R14) {
        in >> (bitcode::BS&) m_dragmode;
    }
    in >> (bitcode::BS&) m_treedepth;

    in >> (bitcode::BS&) m_lunits;
    in >> (bitcode::BS&) m_luprec;
    in >> (bitcode::BS&) m_aunits;
    in >> (bitcode::BS&) m_auprec;

    if(dwgVersion == R13 || dwgVersion == R14) {
        in >> (bitcode::BS&) m_osmode;
    }
    in >> (bitcode::BS&) m_attmode;
    if(dwgVersion == R13 || dwgVersion == R14) {
        in >> (bitcode::BS&) m_coords;
    }
    in >> (bitcode::BS&) m_pdmode;
    if(dwgVersion == R13 || dwgVersion == R14) {
        in >> (bitcode::BS&) m_pickstyle;
    }
    if(dwgVersion >= R2004) {
        in >> (bitcode::BL&) m_unknown12;
        in >> (bitcode::BL&) m_unknown13;
        in >> (bitcode::BL&) m_unknown14;
    }
    in >> (bitcode::BS&) m_useri1;

    in >> (bitcode::BS&) m_useri2;
    in >> (bitcode::BS&) m_useri3;
    in >> (bitcode::BS&) m_useri4;
    in >> (bitcode::BS&) m_useri5;
    in >> (bitcode::BS&) m_splinesegs;
    in >> (bitcode::BS&) m_surfu;
    in >> (bitcode::BS&) m_surfv;
    in >> (bitcode::BS&) m_surftype;
    in >> (bitcode::BS&) m_surftab1;
    in >> (bitcode::BS&) m_surftab2;
    in >> (bitcode::BS&) m_splinetype;
    in >> (bitcode::BS&) m_shadedge;
    in >> (bitcode::BS&) m_shadedif;
    in >> (bitcode::BS&) m_unitmode;
    in >> (bitcode::BS&) m_maxactvp;
    in >> (bitcode::BS&) m_isolines;
    in >> (bitcode::BS&) m_cmljust;
    in >> (bitcode::BS&) m_textqlty;

    in >> (bitcode::BD&) m_ltscale;
    in >> (bitcode::BD&) m_textsize;
    in >> (bitcode::BD&) m_tracewid;
    in >> (bitcode::BD&) m_sketchinc;
    in >> (bitcode::BD&) m_filletrad;
    in >> (bitcode::BD&) m_thickness;
    in >> (bitcode::BD&) m_angbase;
    in >> (bitcode::BD&) m_pdsize;
    in >> (bitcode::BD&) m_plinewid;
    in >> (bitcode::BD&) m_userr1;
    in >> (bitcode::BD&) m_userr2;
    in >> (bitcode::BD&) m_userr3;
    in >> (bitcode::BD&) m_userr4;
    in >> (bitcode::BD&) m_userr5;

    in >> (bitcode::BD&) m_chamfera;
    in >> (bitcode::BD&) m_chamferb;
    in >> (bitcode::BD&) m_chamferc;
    in >> (bitcode::BD&) m_chamferd;
    in >> (bitcode::BD&) m_facetres;
    in >> (bitcode::BD&) m_cmlscale;
    in >> (bitcode::BD&) m_celtscale;
    in >> (bitcode::TV&) m_menuname;
    in >> (bitcode::BL&) m_tdcreate_day;
    in >> (bitcode::BL&) m_tdcreate_ms;
    in >> (bitcode::BL&) m_tdupdate_day;
    in >> (bitcode::BL&) m_tdupdate_ms;

    if(dwgVersion >= R2004) {
        in >> (bitcode::BL&) m_unknown15;
        in >> (bitcode::BL&) m_unknown16;
        in >> (bitcode::BL&) m_unknown17;
    }

    in >> (bitcode::BL&) m_tdindwg_days;
    in >> (bitcode::BL&) m_tdindwg_ms;
    in >> (bitcode::BL&) m_tdusrtimer_days;
    in >> (bitcode::BL&) m_tdusrtimer_ms;
    in >> (bitcode::CMC&) m_cecolor;

    in.ReadHandle(m_handseed);
    in.ReadHandle(m_clayer);
    in.ReadHandle(m_textstyle);
    in.ReadHandle(m_celtype);

    // R2007+
    if(dwgVersion >= R2007) {
        in.ReadHandle(m_cmaterial);
    }

    // commmon
    in.ReadHandle(m_dimstyle);
    in.ReadHandle(m_cmlstyle);

    // R2000+ only
    if(dwgVersion >= R2000) {
        in >> (bitcode::BD&) m_psvpscale;
    }

    in >> (bitcode::BD3&) m_insbase;
    in >> (bitcode::BD3&) m_extmin;
    in >> (bitcode::BD3&) m_extmax;
    in >> (bitcode::RD2&) m_limmin;
    in >> (bitcode::RD2&) m_limmax;
    in >> (bitcode::BD&) m_elevation;
    in >> (bitcode::BD3&) m_ucsorg;
    in >> (bitcode::BD3&) m_ucsxdir;
    in >> (bitcode::BD3&) m_ucsydir;
    in.ReadHandle(m_ucsname);


    return OcApp::eOk;
//    return OcApp::eNotImplemented;
}

DwgInArchive& operator>>(DwgInArchive& in, OcDbHeaderVars & dwgVars)
{
    ASSERT_ARCHIVE_NOT_LOADING;
    in.SetError(dwgVars.DecodeData(in));
    return in;
}

END_OCTAVARIUM_NS
