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

#include <boost/shared_ptr.hpp>

#include "OcCommon.h"
#include "OcError.h"

#include "OcDbDatabase.h"
#include "OcDbDatabase_p.h"

BEGIN_OCTAVARIUM_NS

#define DEFINE_GETTER_SETTER_BY_VAL(TYPE, FUNCTION) \
    TYPE OcDbDatabase::FUNCTION(void) const { return m_pDatabaseImpl->FUNCTION(); } \
    void OcDbDatabase::FUNCTION(TYPE val) { m_pDatabaseImpl->FUNCTION(val); };

#define DEFINE_GETTER_SETTER_BY_REF(TYPE, FUNCTION) \
    const TYPE & OcDbDatabase::FUNCTION(void) const { return m_pDatabaseImpl->FUNCTION(); } \
    void OcDbDatabase::FUNCTION(const TYPE & val) { m_pDatabaseImpl->FUNCTION(val); };


OcDbDatabase::OcDbDatabase(void)
    : m_pDatabaseImpl(new OcDbDatabasePimpl())
{
    m_pDatabaseImpl->m_qPtr = this;
}

OcDbDatabase::~OcDbDatabase(void)
{
    delete m_pDatabaseImpl;
}

OcApp::ErrorStatus OcDbDatabase::Open(const string_t & filename)
{
    return m_pDatabaseImpl->Open(filename);
}


DEFINE_GETTER_SETTER_BY_VAL(double,             angbase);
DEFINE_GETTER_SETTER_BY_VAL(bool,               angdir);
DEFINE_GETTER_SETTER_BY_REF(OcDbObjectId,       appidCtrlId);
DEFINE_GETTER_SETTER_BY_VAL(bool,               attdia);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            attmode);
DEFINE_GETTER_SETTER_BY_VAL(bool,               attreq);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            aunits);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            auprec);

DEFINE_GETTER_SETTER_BY_VAL(bool,               blipmode);
DEFINE_GETTER_SETTER_BY_REF(OcDbObjectId,       block_recordMsId);
DEFINE_GETTER_SETTER_BY_REF(OcDbObjectId,       block_recordPsId);
DEFINE_GETTER_SETTER_BY_REF(OcDbObjectId,       blockCtrlId);

DEFINE_GETTER_SETTER_BY_VAL(bool,               cameradisplay);
DEFINE_GETTER_SETTER_BY_VAL(double,             cameraheight);
DEFINE_GETTER_SETTER_BY_REF(OcCmColor,          cecolor);
DEFINE_GETTER_SETTER_BY_VAL(double,             celtscale);
DEFINE_GETTER_SETTER_BY_REF(OcDbObjectId,       celtype);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            cepsntype);
DEFINE_GETTER_SETTER_BY_VAL(double,             chamfera);
DEFINE_GETTER_SETTER_BY_VAL(double,             chamferb);
DEFINE_GETTER_SETTER_BY_VAL(double,             chamferc);
DEFINE_GETTER_SETTER_BY_VAL(double,             chamferd);
DEFINE_GETTER_SETTER_BY_REF(OcDbObjectId,       clayer);
DEFINE_GETTER_SETTER_BY_REF(OcDbObjectId,       cmaterial);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            cmljust);
DEFINE_GETTER_SETTER_BY_VAL(double,             cmlscale);
DEFINE_GETTER_SETTER_BY_REF(OcDbObjectId,       cmlstyle);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            coords);
DEFINE_GETTER_SETTER_BY_REF(OcDbObjectId,       cpsnid);
DEFINE_GETTER_SETTER_BY_VAL(byte_t,             cshadow);
DEFINE_GETTER_SETTER_BY_REF(OcDbHardOwnershipId,    currentVpId);

DEFINE_GETTER_SETTER_BY_VAL(bool,               delobj);
DEFINE_GETTER_SETTER_BY_VAL(byte_t,             dgnframe);
DEFINE_GETTER_SETTER_BY_REF(OcDbObjectId,       dictionaryColorsId);
DEFINE_GETTER_SETTER_BY_REF(OcDbObjectId,       dictionaryGroupId);
DEFINE_GETTER_SETTER_BY_REF(OcDbObjectId,       dictionaryLayoutsId);
DEFINE_GETTER_SETTER_BY_REF(OcDbObjectId,       dictionaryMaterialsId);
DEFINE_GETTER_SETTER_BY_REF(OcDbObjectId,       dictionaryMLineStyleId);
DEFINE_GETTER_SETTER_BY_REF(OcDbObjectId,       dictionaryNamedObjsId);
DEFINE_GETTER_SETTER_BY_REF(OcDbObjectId,       dictionaryPlotSettingsId);
DEFINE_GETTER_SETTER_BY_REF(OcDbObjectId,       dictionaryPlotStylesId);
DEFINE_GETTER_SETTER_BY_REF(OcDbObjectId,       dictionaryVisualStyleId);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            dimadec);
DEFINE_GETTER_SETTER_BY_VAL(bool,               dimalt);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            dimaltd);
DEFINE_GETTER_SETTER_BY_VAL(double,             dimaltf);
DEFINE_GETTER_SETTER_BY_VAL(double,             dimaltrnd);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            dimalttd);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            dimalttz);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            dimaltu);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            dimaltz);
DEFINE_GETTER_SETTER_BY_REF(std::wstring,       dimapost);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            dimarcsym);
DEFINE_GETTER_SETTER_BY_VAL(bool,               dimaso);
DEFINE_GETTER_SETTER_BY_VAL(byte_t,             dimassoc);
DEFINE_GETTER_SETTER_BY_VAL(double,             dimasz);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            dimatfit);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            dimaunit);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            dimazin);
DEFINE_GETTER_SETTER_BY_REF(std::wstring,       dimblk);
DEFINE_GETTER_SETTER_BY_REF(std::wstring,       dimblk1);
DEFINE_GETTER_SETTER_BY_REF(OcDbObjectId,       dimblk1Id);
DEFINE_GETTER_SETTER_BY_REF(std::wstring,       dimblk2);
DEFINE_GETTER_SETTER_BY_REF(OcDbObjectId,       dimblk2Id);
DEFINE_GETTER_SETTER_BY_REF(OcDbObjectId,       dimblkId);
DEFINE_GETTER_SETTER_BY_VAL(double,             dimcen);
DEFINE_GETTER_SETTER_BY_REF(OcCmColor,          dimclrd);
DEFINE_GETTER_SETTER_BY_REF(OcCmColor,          dimclre);
DEFINE_GETTER_SETTER_BY_REF(OcCmColor,          dimclrt);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            dimdec);
DEFINE_GETTER_SETTER_BY_VAL(double,             dimdle);
DEFINE_GETTER_SETTER_BY_VAL(double,             dimdli);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            dimdsep);
DEFINE_GETTER_SETTER_BY_VAL(double,             dimexe);
DEFINE_GETTER_SETTER_BY_VAL(double,             dimexo);
DEFINE_GETTER_SETTER_BY_VAL(byte_t,             dimfit);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            dimfrac);
DEFINE_GETTER_SETTER_BY_VAL(double,             dimfxl);
DEFINE_GETTER_SETTER_BY_VAL(bool,               dimfxlon);
DEFINE_GETTER_SETTER_BY_VAL(double,             dimgap);
DEFINE_GETTER_SETTER_BY_VAL(double,             dimjogang);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            dimjust);
DEFINE_GETTER_SETTER_BY_REF(OcDbObjectId,       dimldrblk);
DEFINE_GETTER_SETTER_BY_VAL(double,             dimlfac);
DEFINE_GETTER_SETTER_BY_VAL(bool,               dimlim);
DEFINE_GETTER_SETTER_BY_REF(OcDbObjectId,       dimltex1);
DEFINE_GETTER_SETTER_BY_REF(OcDbObjectId,       dimltex2);
DEFINE_GETTER_SETTER_BY_REF(OcDbObjectId,       dimltype);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            dimlunit);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            dimlwd);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            dimlwe);
DEFINE_GETTER_SETTER_BY_REF(std::wstring,       dimpost);
DEFINE_GETTER_SETTER_BY_VAL(double,             dimrnd);
DEFINE_GETTER_SETTER_BY_VAL(bool,               dimsah);
DEFINE_GETTER_SETTER_BY_VAL(bool,               dimsav);
DEFINE_GETTER_SETTER_BY_VAL(double,             dimscale);
DEFINE_GETTER_SETTER_BY_VAL(bool,               dimsd1);
DEFINE_GETTER_SETTER_BY_VAL(bool,               dimsd2);
DEFINE_GETTER_SETTER_BY_VAL(bool,               dimse1);
DEFINE_GETTER_SETTER_BY_VAL(bool,               dimse2);
DEFINE_GETTER_SETTER_BY_VAL(bool,               dimsho);
DEFINE_GETTER_SETTER_BY_VAL(bool,               dimsoxd);
DEFINE_GETTER_SETTER_BY_REF(OcDbObjectId,       dimstyle);
DEFINE_GETTER_SETTER_BY_REF(OcDbObjectId,       dimstyleCtrlId);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            dimtad);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            dimtdec);
DEFINE_GETTER_SETTER_BY_VAL(double,             dimtfac);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            dimtfill);
DEFINE_GETTER_SETTER_BY_REF(OcCmColor,          dimtfillclr);
DEFINE_GETTER_SETTER_BY_VAL(bool,               dimtih);
DEFINE_GETTER_SETTER_BY_VAL(bool,               dimtix);
DEFINE_GETTER_SETTER_BY_VAL(double,             dimtm);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            dimtmove);
DEFINE_GETTER_SETTER_BY_VAL(bool,               dimtofl);
DEFINE_GETTER_SETTER_BY_VAL(bool,               dimtoh);
DEFINE_GETTER_SETTER_BY_VAL(bool,               dimtol);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            dimtolj);
DEFINE_GETTER_SETTER_BY_VAL(double,             dimtp);
DEFINE_GETTER_SETTER_BY_VAL(double,             dimtsz);
DEFINE_GETTER_SETTER_BY_VAL(double,             dimtvp);
DEFINE_GETTER_SETTER_BY_REF(OcDbObjectId,       dimtxsty);
DEFINE_GETTER_SETTER_BY_VAL(double,             dimtxt);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            dimtzin);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            dimunit);
DEFINE_GETTER_SETTER_BY_VAL(bool,               dimupt);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            dimzin);
DEFINE_GETTER_SETTER_BY_VAL(bool,               dispsilh);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            dragmode);
DEFINE_GETTER_SETTER_BY_REF(OcDbObjectId,       dragvsId);
DEFINE_GETTER_SETTER_BY_VAL(byte_t,             dwfframe);
DEFINE_GETTER_SETTER_BY_VAL(double,             dwfprec3d);

DEFINE_GETTER_SETTER_BY_VAL(double,             elevation);
DEFINE_GETTER_SETTER_BY_REF(OcGePoint3D,        extmax);
DEFINE_GETTER_SETTER_BY_REF(OcGePoint3D,        extmin);

DEFINE_GETTER_SETTER_BY_VAL(double,             facetres);
DEFINE_GETTER_SETTER_BY_VAL(double,             filletrad);
DEFINE_GETTER_SETTER_BY_VAL(bool,               fillmode);
DEFINE_GETTER_SETTER_BY_REF(std::wstring,       fingerprintguid);
DEFINE_GETTER_SETTER_BY_VAL(int32_t,            flags);

DEFINE_GETTER_SETTER_BY_VAL(byte_t,             halogap);
DEFINE_GETTER_SETTER_BY_REF(OcDbObjectId,       handseed);
DEFINE_GETTER_SETTER_BY_VAL(byte_t,             hidetext);
DEFINE_GETTER_SETTER_BY_REF(std::wstring,       hyperlinkbase);

DEFINE_GETTER_SETTER_BY_VAL(byte_t,             indexctl);
DEFINE_GETTER_SETTER_BY_REF(OcGePoint3D,        insbase);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            insunits);
DEFINE_GETTER_SETTER_BY_REF(OcCmColor,          interferecolor);
DEFINE_GETTER_SETTER_BY_REF(OcDbObjectId,       interfereobjvsId);
DEFINE_GETTER_SETTER_BY_REF(OcDbObjectId,       interferevpvsId);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            intersectioncolor);
DEFINE_GETTER_SETTER_BY_VAL(byte_t,             intersectiondisplay);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            isolines);

DEFINE_GETTER_SETTER_BY_VAL(double,             latitude);
DEFINE_GETTER_SETTER_BY_REF(OcDbObjectId,       layerCtrlId);
DEFINE_GETTER_SETTER_BY_VAL(double,             lenslength);
DEFINE_GETTER_SETTER_BY_VAL(byte_t,             lightglyphdisplay);
DEFINE_GETTER_SETTER_BY_VAL(bool,               limcheck);
DEFINE_GETTER_SETTER_BY_REF(OcGePoint2D,        limmax);
DEFINE_GETTER_SETTER_BY_REF(OcGePoint2D,        limmin);
DEFINE_GETTER_SETTER_BY_REF(OcDbObjectId,       linetypeCtrlId);
DEFINE_GETTER_SETTER_BY_VAL(double,             loftang1);
DEFINE_GETTER_SETTER_BY_VAL(double,             loftang2);
DEFINE_GETTER_SETTER_BY_VAL(double,             loftmag1);
DEFINE_GETTER_SETTER_BY_VAL(byte_t,             loftnormals);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            loftparam);
DEFINE_GETTER_SETTER_BY_VAL(double,             logtmag2);
DEFINE_GETTER_SETTER_BY_VAL(double,             longitude);
DEFINE_GETTER_SETTER_BY_VAL(double,             ltscale);
DEFINE_GETTER_SETTER_BY_REF(OcDbObjectId,       ltypeByBlockId);
DEFINE_GETTER_SETTER_BY_REF(OcDbObjectId,       ltypeByLayerId);
DEFINE_GETTER_SETTER_BY_REF(OcDbObjectId,       ltypeContinuousId);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            lunits);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            luprec);

DEFINE_GETTER_SETTER_BY_VAL(int16_t,            maxactvp);
DEFINE_GETTER_SETTER_BY_REF(std::wstring,       menuname);
DEFINE_GETTER_SETTER_BY_VAL(bool,               mirrtext);

DEFINE_GETTER_SETTER_BY_VAL(double,             northdirection);

DEFINE_GETTER_SETTER_BY_VAL(int16_t,            obscuredcolor);
DEFINE_GETTER_SETTER_BY_VAL(byte_t,             obscuredltype);
DEFINE_GETTER_SETTER_BY_VAL(bool,               orthomode);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            osmode);

DEFINE_GETTER_SETTER_BY_VAL(int16_t,            pdmode);
DEFINE_GETTER_SETTER_BY_VAL(double,             pdsize);
DEFINE_GETTER_SETTER_BY_VAL(double,             pelevation);
DEFINE_GETTER_SETTER_BY_VAL(bool,               pellipse);
DEFINE_GETTER_SETTER_BY_REF(OcGePoint3D,        pextmax);
DEFINE_GETTER_SETTER_BY_REF(OcGePoint3D,        pextmin);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            pickstyle);
DEFINE_GETTER_SETTER_BY_REF(OcGePoint3D,        pinsbase);
DEFINE_GETTER_SETTER_BY_VAL(bool,               plimcheck);
DEFINE_GETTER_SETTER_BY_REF(OcGePoint2D,        plimmax);
DEFINE_GETTER_SETTER_BY_REF(OcGePoint2D,        plimmin);
DEFINE_GETTER_SETTER_BY_VAL(bool,               plinegen);
DEFINE_GETTER_SETTER_BY_VAL(double,             plinewid);
DEFINE_GETTER_SETTER_BY_REF(std::wstring,       projectname);
DEFINE_GETTER_SETTER_BY_VAL(bool,               psltscale);
DEFINE_GETTER_SETTER_BY_VAL(double,             psolheight);
DEFINE_GETTER_SETTER_BY_VAL(double,             psolwidth);
DEFINE_GETTER_SETTER_BY_VAL(double,             psvpscale);
DEFINE_GETTER_SETTER_BY_REF(OcDbObjectId,       pucsbase);
DEFINE_GETTER_SETTER_BY_REF(OcDbObjectId,       pucsname);
DEFINE_GETTER_SETTER_BY_REF(OcGePoint3D,        pucsorg);
DEFINE_GETTER_SETTER_BY_REF(OcGePoint3D,        pucsorgback);
DEFINE_GETTER_SETTER_BY_REF(OcGePoint3D,        pucsorgbottom);
DEFINE_GETTER_SETTER_BY_REF(OcGePoint3D,        pucsorgfront);
DEFINE_GETTER_SETTER_BY_REF(OcGePoint3D,        pucsorgleft);
DEFINE_GETTER_SETTER_BY_REF(OcGePoint3D,        pucsorgright);
DEFINE_GETTER_SETTER_BY_REF(OcGePoint3D,        pucsorgtop);
DEFINE_GETTER_SETTER_BY_REF(OcDbObjectId,       pucsorthoref);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            pucsorthoview);
DEFINE_GETTER_SETTER_BY_REF(OcGePoint3D,        pucsxdir);
DEFINE_GETTER_SETTER_BY_REF(OcGePoint3D,        pucsydir);

DEFINE_GETTER_SETTER_BY_VAL(bool,               qtextmode);

DEFINE_GETTER_SETTER_BY_VAL(bool,               regenmode);

DEFINE_GETTER_SETTER_BY_VAL(int16_t,            saveimages);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            shadedge);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            shadedif);
DEFINE_GETTER_SETTER_BY_VAL(byte_t,             showhist);
DEFINE_GETTER_SETTER_BY_VAL(double,             sketchinc);
DEFINE_GETTER_SETTER_BY_VAL(bool,               skpoly);
DEFINE_GETTER_SETTER_BY_VAL(byte_t,             solidhist);
DEFINE_GETTER_SETTER_BY_VAL(byte_t,             sortents);
DEFINE_GETTER_SETTER_BY_VAL(bool,               splframe);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            splinesegs);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            splinetype);
DEFINE_GETTER_SETTER_BY_VAL(double,             stepsize);
DEFINE_GETTER_SETTER_BY_VAL(double,             stepspersec);
DEFINE_GETTER_SETTER_BY_REF(OcDbObjectId,       styleCtrlId);
DEFINE_GETTER_SETTER_BY_REF(std::wstring,       stylesheet);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            surftab1);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            surftab2);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            surftype);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            surfu);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            surfv);

DEFINE_GETTER_SETTER_BY_VAL(int32_t,            tdcreate_day);
DEFINE_GETTER_SETTER_BY_VAL(int32_t,            tdcreate_ms);
DEFINE_GETTER_SETTER_BY_VAL(int32_t,            tdindwg_days);
DEFINE_GETTER_SETTER_BY_VAL(int32_t,            tdindwg_ms);
DEFINE_GETTER_SETTER_BY_VAL(int32_t,            tdupdate_day);
DEFINE_GETTER_SETTER_BY_VAL(int32_t,            tdupdate_ms);
DEFINE_GETTER_SETTER_BY_VAL(int32_t,            tdusrtimer_days);
DEFINE_GETTER_SETTER_BY_VAL(int32_t,            tdusrtimer_ms);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            textqlty);
DEFINE_GETTER_SETTER_BY_VAL(double,             textsize);
DEFINE_GETTER_SETTER_BY_REF(OcDbObjectId,       textstyle);
DEFINE_GETTER_SETTER_BY_VAL(double,             thickness);
DEFINE_GETTER_SETTER_BY_VAL(bool,               tilemode);
DEFINE_GETTER_SETTER_BY_VAL(byte_t,             tilemodelightsynch);
DEFINE_GETTER_SETTER_BY_VAL(int32_t,            timezone);
DEFINE_GETTER_SETTER_BY_VAL(double,             tracewid);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            treedepth);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            tstackalign);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            tstacksize);

DEFINE_GETTER_SETTER_BY_REF(OcDbObjectId,       ucsbase);
DEFINE_GETTER_SETTER_BY_REF(OcDbObjectId,       ucsCtrlId);
DEFINE_GETTER_SETTER_BY_REF(OcDbObjectId,       ucsname);
DEFINE_GETTER_SETTER_BY_REF(OcGePoint3D,        ucsorg);
DEFINE_GETTER_SETTER_BY_REF(OcGePoint3D,        ucsorgback);
DEFINE_GETTER_SETTER_BY_REF(OcGePoint3D,        ucsorgbottom);
DEFINE_GETTER_SETTER_BY_REF(OcGePoint3D,        ucsorgfront);
DEFINE_GETTER_SETTER_BY_REF(OcGePoint3D,        ucsorgleft);
DEFINE_GETTER_SETTER_BY_REF(OcGePoint3D,        ucsorgright);
DEFINE_GETTER_SETTER_BY_REF(OcGePoint3D,        ucsorgtop);
DEFINE_GETTER_SETTER_BY_REF(OcDbObjectId,       ucsorthoref);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            ucsorthoview);
DEFINE_GETTER_SETTER_BY_REF(OcGePoint3D,        ucsxdir);
DEFINE_GETTER_SETTER_BY_REF(OcGePoint3D,        ucsydir);
DEFINE_GETTER_SETTER_BY_VAL(bool,               undocumented);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            unitmode);
DEFINE_GETTER_SETTER_BY_VAL(double,             unknown1);
DEFINE_GETTER_SETTER_BY_VAL(double,             unknown2);
DEFINE_GETTER_SETTER_BY_VAL(double,             unknown3);
DEFINE_GETTER_SETTER_BY_VAL(double,             unknown4);
DEFINE_GETTER_SETTER_BY_REF(std::wstring,       unknown5);
DEFINE_GETTER_SETTER_BY_REF(std::wstring,       unknown6);
DEFINE_GETTER_SETTER_BY_REF(std::wstring,       unknown7);
DEFINE_GETTER_SETTER_BY_REF(std::wstring,       unknown8);
DEFINE_GETTER_SETTER_BY_VAL(int32_t,            unknown9);
DEFINE_GETTER_SETTER_BY_VAL(int32_t,            unknown10);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            unknown11);
DEFINE_GETTER_SETTER_BY_VAL(int32_t,            unknown12);
DEFINE_GETTER_SETTER_BY_VAL(int32_t,            unknown13);
DEFINE_GETTER_SETTER_BY_VAL(int32_t,            unknown14);
DEFINE_GETTER_SETTER_BY_VAL(int32_t,            unknown15);
DEFINE_GETTER_SETTER_BY_VAL(int32_t,            unknown16);
DEFINE_GETTER_SETTER_BY_VAL(int32_t,            unknown17);
DEFINE_GETTER_SETTER_BY_VAL(int32_t,            unknown21);
DEFINE_GETTER_SETTER_BY_VAL(int32_t,            unknown22);
DEFINE_GETTER_SETTER_BY_VAL(double,             unknown23);
DEFINE_GETTER_SETTER_BY_VAL(bool,               unknown47);
DEFINE_GETTER_SETTER_BY_VAL(double,             unknown53);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            unknown54);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            unknown55);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            unknown56);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            unknown57);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            useri1);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            useri2);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            useri3);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            useri4);
DEFINE_GETTER_SETTER_BY_VAL(int16_t,            useri5);
DEFINE_GETTER_SETTER_BY_VAL(double,             userr1);
DEFINE_GETTER_SETTER_BY_VAL(double,             userr2);
DEFINE_GETTER_SETTER_BY_VAL(double,             userr3);
DEFINE_GETTER_SETTER_BY_VAL(double,             userr4);
DEFINE_GETTER_SETTER_BY_VAL(double,             userr5);
DEFINE_GETTER_SETTER_BY_VAL(bool,               usertimer);

DEFINE_GETTER_SETTER_BY_REF(std::wstring,       versionguid);
DEFINE_GETTER_SETTER_BY_REF(OcDbObjectId,       viewCtrlId);
DEFINE_GETTER_SETTER_BY_REF(OcDbObjectId,       viewport);
DEFINE_GETTER_SETTER_BY_VAL(bool,               visretain);
DEFINE_GETTER_SETTER_BY_REF(OcDbObjectId,       vportCtrlId);

DEFINE_GETTER_SETTER_BY_VAL(bool,               wireframe);
DEFINE_GETTER_SETTER_BY_VAL(bool,               worldview);

DEFINE_GETTER_SETTER_BY_VAL(byte_t,             xclipframe);


END_OCTAVARIUM_NS
