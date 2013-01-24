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

#ifndef OcDbDatabase_h__
#define OcDbDatabase_h__
#include "templates/accessors.h"

#include "OcCmColor.h"
#include "OcDbHardOwnershipId.h"
#include "OcGePoint2D.h"
#include "OcGePoint3D.h"



BEGIN_OCTAVARIUM_NS
//class OcDbDatabase;
class OcDbDatabasePimpl;

class OcDbDatabase : public OcRxObject
{
public:

    OcDbDatabase(void);
    virtual ~OcDbDatabase(void);

    OcApp::ErrorStatus Open(const string_t & filename);

    DECLARE_GETTER_SETTER_BY_VAL(double,            angbase);
    DECLARE_GETTER_SETTER_BY_VAL(bool,              angdir);
    DECLARE_GETTER_SETTER_BY_REF(OcDbObjectId,      appidCtrlId);
    DECLARE_GETTER_SETTER_BY_VAL(bool,              attdia);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           attmode);
    DECLARE_GETTER_SETTER_BY_VAL(bool,              attreq);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           aunits);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           auprec);

    DECLARE_GETTER_SETTER_BY_VAL(bool,              blipmode);
    DECLARE_GETTER_SETTER_BY_REF(OcDbObjectId,      block_recordMsId);
    DECLARE_GETTER_SETTER_BY_REF(OcDbObjectId,      block_recordPsId);
    DECLARE_GETTER_SETTER_BY_REF(OcDbObjectId,      blockCtrlId);

    DECLARE_GETTER_SETTER_BY_VAL(bool,              cameradisplay);
    DECLARE_GETTER_SETTER_BY_VAL(double,            cameraheight);
    DECLARE_GETTER_SETTER_BY_REF(OcCmColor,         cecolor);
    DECLARE_GETTER_SETTER_BY_VAL(double,            celtscale);
    DECLARE_GETTER_SETTER_BY_REF(OcDbObjectId,      celtype);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           cepsntype);
    DECLARE_GETTER_SETTER_BY_VAL(double,            chamfera);
    DECLARE_GETTER_SETTER_BY_VAL(double,            chamferb);
    DECLARE_GETTER_SETTER_BY_VAL(double,            chamferc);
    DECLARE_GETTER_SETTER_BY_VAL(double,            chamferd);
    DECLARE_GETTER_SETTER_BY_REF(OcDbObjectId,      clayer);
    DECLARE_GETTER_SETTER_BY_REF(OcDbObjectId,      cmaterial);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           cmljust);
    DECLARE_GETTER_SETTER_BY_VAL(double,            cmlscale);
    DECLARE_GETTER_SETTER_BY_REF(OcDbObjectId,      cmlstyle);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           coords);
    DECLARE_GETTER_SETTER_BY_REF(OcDbObjectId,      cpsnid);
    DECLARE_GETTER_SETTER_BY_VAL(byte_t,            cshadow);
    DECLARE_GETTER_SETTER_BY_REF(OcDbHardOwnershipId,   currentVpId);

    DECLARE_GETTER_SETTER_BY_VAL(bool,              delobj);
    DECLARE_GETTER_SETTER_BY_VAL(byte_t,            dgnframe);
    DECLARE_GETTER_SETTER_BY_REF(OcDbObjectId,      dictionaryColorsId);
    DECLARE_GETTER_SETTER_BY_REF(OcDbObjectId,      dictionaryGroupId);
    DECLARE_GETTER_SETTER_BY_REF(OcDbObjectId,      dictionaryLayoutsId);
    DECLARE_GETTER_SETTER_BY_REF(OcDbObjectId,      dictionaryMaterialsId);
    DECLARE_GETTER_SETTER_BY_REF(OcDbObjectId,      dictionaryMLineStyleId);
    DECLARE_GETTER_SETTER_BY_REF(OcDbObjectId,      dictionaryNamedObjsId);
    DECLARE_GETTER_SETTER_BY_REF(OcDbObjectId,      dictionaryPlotSettingsId);
    DECLARE_GETTER_SETTER_BY_REF(OcDbObjectId,      dictionaryPlotStylesId);
    DECLARE_GETTER_SETTER_BY_REF(OcDbObjectId,      dictionaryVisualStyleId);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           dimadec);
    DECLARE_GETTER_SETTER_BY_VAL(bool,              dimalt);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           dimaltd);
    DECLARE_GETTER_SETTER_BY_VAL(double,            dimaltf);
    DECLARE_GETTER_SETTER_BY_VAL(double,            dimaltrnd);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           dimalttd);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           dimalttz);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           dimaltu);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           dimaltz);
    DECLARE_GETTER_SETTER_BY_REF(std::wstring,      dimapost);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           dimarcsym);
    DECLARE_GETTER_SETTER_BY_VAL(bool,              dimaso);
    DECLARE_GETTER_SETTER_BY_VAL(byte_t,            dimassoc);
    DECLARE_GETTER_SETTER_BY_VAL(double,            dimasz);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           dimatfit);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           dimaunit);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           dimazin);
    DECLARE_GETTER_SETTER_BY_REF(std::wstring,      dimblk);
    DECLARE_GETTER_SETTER_BY_REF(std::wstring,      dimblk1);
    DECLARE_GETTER_SETTER_BY_REF(OcDbObjectId,      dimblk1Id);
    DECLARE_GETTER_SETTER_BY_REF(std::wstring,      dimblk2);
    DECLARE_GETTER_SETTER_BY_REF(OcDbObjectId,      dimblk2Id);
    DECLARE_GETTER_SETTER_BY_REF(OcDbObjectId,      dimblkId);
    DECLARE_GETTER_SETTER_BY_VAL(double,            dimcen);
    DECLARE_GETTER_SETTER_BY_REF(OcCmColor,         dimclrd);
    DECLARE_GETTER_SETTER_BY_REF(OcCmColor,         dimclre);
    DECLARE_GETTER_SETTER_BY_REF(OcCmColor,         dimclrt);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           dimdec);
    DECLARE_GETTER_SETTER_BY_VAL(double,            dimdle);
    DECLARE_GETTER_SETTER_BY_VAL(double,            dimdli);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           dimdsep);
    DECLARE_GETTER_SETTER_BY_VAL(double,            dimexe);
    DECLARE_GETTER_SETTER_BY_VAL(double,            dimexo);
    DECLARE_GETTER_SETTER_BY_VAL(byte_t,            dimfit);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           dimfrac);
    DECLARE_GETTER_SETTER_BY_VAL(double,            dimfxl);
    DECLARE_GETTER_SETTER_BY_VAL(bool,              dimfxlon);
    DECLARE_GETTER_SETTER_BY_VAL(double,            dimgap);
    DECLARE_GETTER_SETTER_BY_VAL(double,            dimjogang);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           dimjust);
    DECLARE_GETTER_SETTER_BY_REF(OcDbObjectId,      dimldrblk);
    DECLARE_GETTER_SETTER_BY_VAL(double,            dimlfac);
    DECLARE_GETTER_SETTER_BY_VAL(bool,              dimlim);
    DECLARE_GETTER_SETTER_BY_REF(OcDbObjectId,      dimltex1);
    DECLARE_GETTER_SETTER_BY_REF(OcDbObjectId,      dimltex2);
    DECLARE_GETTER_SETTER_BY_REF(OcDbObjectId,      dimltype);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           dimlunit);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           dimlwd);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           dimlwe);
    DECLARE_GETTER_SETTER_BY_REF(std::wstring,      dimpost);
    DECLARE_GETTER_SETTER_BY_VAL(double,            dimrnd);
    DECLARE_GETTER_SETTER_BY_VAL(bool,              dimsah);
    DECLARE_GETTER_SETTER_BY_VAL(bool,              dimsav);
    DECLARE_GETTER_SETTER_BY_VAL(double,            dimscale);
    DECLARE_GETTER_SETTER_BY_VAL(bool,              dimsd1);
    DECLARE_GETTER_SETTER_BY_VAL(bool,              dimsd2);
    DECLARE_GETTER_SETTER_BY_VAL(bool,              dimse1);
    DECLARE_GETTER_SETTER_BY_VAL(bool,              dimse2);
    DECLARE_GETTER_SETTER_BY_VAL(bool,              dimsho);
    DECLARE_GETTER_SETTER_BY_VAL(bool,              dimsoxd);
    DECLARE_GETTER_SETTER_BY_REF(OcDbObjectId,      dimstyle);
    DECLARE_GETTER_SETTER_BY_REF(OcDbObjectId,      dimstyleCtrlId);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           dimtad);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           dimtdec);
    DECLARE_GETTER_SETTER_BY_VAL(double,            dimtfac);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           dimtfill);
    DECLARE_GETTER_SETTER_BY_REF(OcCmColor,         dimtfillclr);
    DECLARE_GETTER_SETTER_BY_VAL(bool,              dimtih);
    DECLARE_GETTER_SETTER_BY_VAL(bool,              dimtix);
    DECLARE_GETTER_SETTER_BY_VAL(double,            dimtm);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           dimtmove);
    DECLARE_GETTER_SETTER_BY_VAL(bool,              dimtofl);
    DECLARE_GETTER_SETTER_BY_VAL(bool,              dimtoh);
    DECLARE_GETTER_SETTER_BY_VAL(bool,              dimtol);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           dimtolj);
    DECLARE_GETTER_SETTER_BY_VAL(double,            dimtp);
    DECLARE_GETTER_SETTER_BY_VAL(double,            dimtsz);
    DECLARE_GETTER_SETTER_BY_VAL(double,            dimtvp);
    DECLARE_GETTER_SETTER_BY_REF(OcDbObjectId,      dimtxsty);
    DECLARE_GETTER_SETTER_BY_VAL(double,            dimtxt);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           dimtzin);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           dimunit);
    DECLARE_GETTER_SETTER_BY_VAL(bool,              dimupt);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           dimzin);
    DECLARE_GETTER_SETTER_BY_VAL(bool,              dispsilh);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           dragmode);
    DECLARE_GETTER_SETTER_BY_REF(OcDbObjectId,      dragvsId);
    DECLARE_GETTER_SETTER_BY_VAL(byte_t,            dwfframe);
    DECLARE_GETTER_SETTER_BY_VAL(double,            dwfprec3d);

    DECLARE_GETTER_SETTER_BY_VAL(double,            elevation);
    DECLARE_GETTER_SETTER_BY_REF(OcGePoint3D,       extmax);
    DECLARE_GETTER_SETTER_BY_REF(OcGePoint3D,       extmin);

    DECLARE_GETTER_SETTER_BY_VAL(double,            facetres);
    DECLARE_GETTER_SETTER_BY_VAL(double,            filletrad);
    DECLARE_GETTER_SETTER_BY_VAL(bool,              fillmode);
    DECLARE_GETTER_SETTER_BY_REF(std::wstring,      fingerprintguid);
    DECLARE_GETTER_SETTER_BY_VAL(int32_t,           flags);

    DECLARE_GETTER_SETTER_BY_VAL(byte_t,            halogap);
    DECLARE_GETTER_SETTER_BY_REF(OcDbObjectId,      handseed);
    DECLARE_GETTER_SETTER_BY_VAL(byte_t,            hidetext);
    DECLARE_GETTER_SETTER_BY_REF(std::wstring,      hyperlinkbase);

    DECLARE_GETTER_SETTER_BY_VAL(byte_t,            indexctl);
    DECLARE_GETTER_SETTER_BY_REF(OcGePoint3D,       insbase);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           insunits);
    DECLARE_GETTER_SETTER_BY_REF(OcCmColor,         interferecolor);
    DECLARE_GETTER_SETTER_BY_REF(OcDbObjectId,      interfereobjvsId);
    DECLARE_GETTER_SETTER_BY_REF(OcDbObjectId,      interferevpvsId);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           intersectioncolor);
    DECLARE_GETTER_SETTER_BY_VAL(byte_t,            intersectiondisplay);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           isolines);

    DECLARE_GETTER_SETTER_BY_VAL(double,            latitude);
    DECLARE_GETTER_SETTER_BY_REF(OcDbObjectId,      layerCtrlId);
    DECLARE_GETTER_SETTER_BY_VAL(double,            lenslength);
    DECLARE_GETTER_SETTER_BY_VAL(byte_t,            lightglyphdisplay);
    DECLARE_GETTER_SETTER_BY_VAL(bool,              limcheck);
    DECLARE_GETTER_SETTER_BY_REF(OcGePoint2D,       limmax);
    DECLARE_GETTER_SETTER_BY_REF(OcGePoint2D,       limmin);
    DECLARE_GETTER_SETTER_BY_REF(OcDbObjectId,      linetypeCtrlId);
    DECLARE_GETTER_SETTER_BY_VAL(double,            loftang1);
    DECLARE_GETTER_SETTER_BY_VAL(double,            loftang2);
    DECLARE_GETTER_SETTER_BY_VAL(double,            loftmag1);
    DECLARE_GETTER_SETTER_BY_VAL(byte_t,            loftnormals);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           loftparam);
    DECLARE_GETTER_SETTER_BY_VAL(double,            logtmag2);
    DECLARE_GETTER_SETTER_BY_VAL(double,            longitude);
    DECLARE_GETTER_SETTER_BY_VAL(double,            ltscale);
    DECLARE_GETTER_SETTER_BY_REF(OcDbObjectId,      ltypeByBlockId);
    DECLARE_GETTER_SETTER_BY_REF(OcDbObjectId,      ltypeByLayerId);
    DECLARE_GETTER_SETTER_BY_REF(OcDbObjectId,      ltypeContinuousId);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           lunits);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           luprec);

    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           maxactvp);
    DECLARE_GETTER_SETTER_BY_REF(std::wstring,      menuname);
    DECLARE_GETTER_SETTER_BY_VAL(bool,              mirrtext);

    DECLARE_GETTER_SETTER_BY_VAL(double,            northdirection);

    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           obscuredcolor);
    DECLARE_GETTER_SETTER_BY_VAL(byte_t,            obscuredltype);
    DECLARE_GETTER_SETTER_BY_VAL(bool,              orthomode);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           osmode);

    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           pdmode);
    DECLARE_GETTER_SETTER_BY_VAL(double,            pdsize);
    DECLARE_GETTER_SETTER_BY_VAL(double,            pelevation);
    DECLARE_GETTER_SETTER_BY_VAL(bool,              pellipse);
    DECLARE_GETTER_SETTER_BY_REF(OcGePoint3D,       pextmax);
    DECLARE_GETTER_SETTER_BY_REF(OcGePoint3D,       pextmin);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           pickstyle);
    DECLARE_GETTER_SETTER_BY_REF(OcGePoint3D,       pinsbase);
    DECLARE_GETTER_SETTER_BY_VAL(bool,              plimcheck);
    DECLARE_GETTER_SETTER_BY_REF(OcGePoint2D,       plimmax);
    DECLARE_GETTER_SETTER_BY_REF(OcGePoint2D,       plimmin);
    DECLARE_GETTER_SETTER_BY_VAL(bool,              plinegen);
    DECLARE_GETTER_SETTER_BY_VAL(double,            plinewid);
    DECLARE_GETTER_SETTER_BY_REF(std::wstring,      projectname);
    DECLARE_GETTER_SETTER_BY_VAL(bool,              psltscale);
    DECLARE_GETTER_SETTER_BY_VAL(double,            psolheight);
    DECLARE_GETTER_SETTER_BY_VAL(double,            psolwidth);
    DECLARE_GETTER_SETTER_BY_VAL(double,            psvpscale);
    DECLARE_GETTER_SETTER_BY_REF(OcDbObjectId,      pucsbase);
    DECLARE_GETTER_SETTER_BY_REF(OcDbObjectId,      pucsname);
    DECLARE_GETTER_SETTER_BY_REF(OcGePoint3D,       pucsorg);
    DECLARE_GETTER_SETTER_BY_REF(OcGePoint3D,       pucsorgback);
    DECLARE_GETTER_SETTER_BY_REF(OcGePoint3D,       pucsorgbottom);
    DECLARE_GETTER_SETTER_BY_REF(OcGePoint3D,       pucsorgfront);
    DECLARE_GETTER_SETTER_BY_REF(OcGePoint3D,       pucsorgleft);
    DECLARE_GETTER_SETTER_BY_REF(OcGePoint3D,       pucsorgright);
    DECLARE_GETTER_SETTER_BY_REF(OcGePoint3D,       pucsorgtop);
    DECLARE_GETTER_SETTER_BY_REF(OcDbObjectId,      pucsorthoref);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           pucsorthoview);
    DECLARE_GETTER_SETTER_BY_REF(OcGePoint3D,       pucsxdir);
    DECLARE_GETTER_SETTER_BY_REF(OcGePoint3D,       pucsydir);

    DECLARE_GETTER_SETTER_BY_VAL(bool,              qtextmode);

    DECLARE_GETTER_SETTER_BY_VAL(bool,              regenmode);

    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           saveimages);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           shadedge);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           shadedif);
    DECLARE_GETTER_SETTER_BY_VAL(byte_t,            showhist);
    DECLARE_GETTER_SETTER_BY_VAL(double,            sketchinc);
    DECLARE_GETTER_SETTER_BY_VAL(bool,              skpoly);
    DECLARE_GETTER_SETTER_BY_VAL(byte_t,            solidhist);
    DECLARE_GETTER_SETTER_BY_VAL(byte_t,            sortents);
    DECLARE_GETTER_SETTER_BY_VAL(bool,              splframe);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           splinesegs);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           splinetype);
    DECLARE_GETTER_SETTER_BY_VAL(double,            stepsize);
    DECLARE_GETTER_SETTER_BY_VAL(double,            stepspersec);
    DECLARE_GETTER_SETTER_BY_REF(OcDbObjectId,      styleCtrlId);
    DECLARE_GETTER_SETTER_BY_REF(std::wstring,      stylesheet);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           surftab1);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           surftab2);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           surftype);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           surfu);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           surfv);

    DECLARE_GETTER_SETTER_BY_VAL(int32_t,           tdcreate_day);
    DECLARE_GETTER_SETTER_BY_VAL(int32_t,           tdcreate_ms);
    DECLARE_GETTER_SETTER_BY_VAL(int32_t,           tdindwg_days);
    DECLARE_GETTER_SETTER_BY_VAL(int32_t,           tdindwg_ms);
    DECLARE_GETTER_SETTER_BY_VAL(int32_t,           tdupdate_day);
    DECLARE_GETTER_SETTER_BY_VAL(int32_t,           tdupdate_ms);
    DECLARE_GETTER_SETTER_BY_VAL(int32_t,           tdusrtimer_days);
    DECLARE_GETTER_SETTER_BY_VAL(int32_t,           tdusrtimer_ms);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           textqlty);
    DECLARE_GETTER_SETTER_BY_VAL(double,            textsize);
    DECLARE_GETTER_SETTER_BY_REF(OcDbObjectId,      textstyle);
    DECLARE_GETTER_SETTER_BY_VAL(double,            thickness);
    DECLARE_GETTER_SETTER_BY_VAL(bool,              tilemode);
    DECLARE_GETTER_SETTER_BY_VAL(byte_t,            tilemodelightsynch);
    DECLARE_GETTER_SETTER_BY_VAL(int32_t,           timezone);
    DECLARE_GETTER_SETTER_BY_VAL(double,            tracewid);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           treedepth);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           tstackalign);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           tstacksize);

    DECLARE_GETTER_SETTER_BY_REF(OcDbObjectId,      ucsbase);
    DECLARE_GETTER_SETTER_BY_REF(OcDbObjectId,      ucsCtrlId);
    DECLARE_GETTER_SETTER_BY_REF(OcDbObjectId,      ucsname);
    DECLARE_GETTER_SETTER_BY_REF(OcGePoint3D,       ucsorg);
    DECLARE_GETTER_SETTER_BY_REF(OcGePoint3D,       ucsorgback);
    DECLARE_GETTER_SETTER_BY_REF(OcGePoint3D,       ucsorgbottom);
    DECLARE_GETTER_SETTER_BY_REF(OcGePoint3D,       ucsorgfront);
    DECLARE_GETTER_SETTER_BY_REF(OcGePoint3D,       ucsorgleft);
    DECLARE_GETTER_SETTER_BY_REF(OcGePoint3D,       ucsorgright);
    DECLARE_GETTER_SETTER_BY_REF(OcGePoint3D,       ucsorgtop);
    DECLARE_GETTER_SETTER_BY_REF(OcDbObjectId,      ucsorthoref);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           ucsorthoview);
    DECLARE_GETTER_SETTER_BY_REF(OcGePoint3D,       ucsxdir);
    DECLARE_GETTER_SETTER_BY_REF(OcGePoint3D,       ucsydir);
    DECLARE_GETTER_SETTER_BY_VAL(bool,              undocumented);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           unitmode);
    DECLARE_GETTER_SETTER_BY_VAL(double,            unknown1);
    DECLARE_GETTER_SETTER_BY_VAL(double,            unknown2);
    DECLARE_GETTER_SETTER_BY_VAL(double,            unknown3);
    DECLARE_GETTER_SETTER_BY_VAL(double,            unknown4);
    DECLARE_GETTER_SETTER_BY_REF(std::wstring,      unknown5);
    DECLARE_GETTER_SETTER_BY_REF(std::wstring,      unknown6);
    DECLARE_GETTER_SETTER_BY_REF(std::wstring,      unknown7);
    DECLARE_GETTER_SETTER_BY_REF(std::wstring,      unknown8);
    DECLARE_GETTER_SETTER_BY_VAL(int32_t,           unknown9);
    DECLARE_GETTER_SETTER_BY_VAL(int32_t,           unknown10);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           unknown11);
    DECLARE_GETTER_SETTER_BY_VAL(int32_t,           unknown12);
    DECLARE_GETTER_SETTER_BY_VAL(int32_t,           unknown13);
    DECLARE_GETTER_SETTER_BY_VAL(int32_t,           unknown14);
    DECLARE_GETTER_SETTER_BY_VAL(int32_t,           unknown15);
    DECLARE_GETTER_SETTER_BY_VAL(int32_t,           unknown16);
    DECLARE_GETTER_SETTER_BY_VAL(int32_t,           unknown17);
    DECLARE_GETTER_SETTER_BY_VAL(int32_t,           unknown21);
    DECLARE_GETTER_SETTER_BY_VAL(int32_t,           unknown22);
    DECLARE_GETTER_SETTER_BY_VAL(double,            unknown23);
    DECLARE_GETTER_SETTER_BY_VAL(bool,              unknown47);
    DECLARE_GETTER_SETTER_BY_VAL(double,            unknown53);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           unknown54);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           unknown55);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           unknown56);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           unknown57);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           useri1);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           useri2);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           useri3);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           useri4);
    DECLARE_GETTER_SETTER_BY_VAL(int16_t,           useri5);
    DECLARE_GETTER_SETTER_BY_VAL(double,            userr1);
    DECLARE_GETTER_SETTER_BY_VAL(double,            userr2);
    DECLARE_GETTER_SETTER_BY_VAL(double,            userr3);
    DECLARE_GETTER_SETTER_BY_VAL(double,            userr4);
    DECLARE_GETTER_SETTER_BY_VAL(double,            userr5);
    DECLARE_GETTER_SETTER_BY_VAL(bool,              usertimer);

    DECLARE_GETTER_SETTER_BY_REF(std::wstring,      versionguid);
    DECLARE_GETTER_SETTER_BY_REF(OcDbObjectId,      viewCtrlId);
    DECLARE_GETTER_SETTER_BY_REF(OcDbObjectId,      viewport);
    DECLARE_GETTER_SETTER_BY_VAL(bool,              visretain);
    DECLARE_GETTER_SETTER_BY_REF(OcDbObjectId,      vportCtrlId);

    DECLARE_GETTER_SETTER_BY_VAL(bool,              wireframe);
    DECLARE_GETTER_SETTER_BY_VAL(bool,              worldview);

    DECLARE_GETTER_SETTER_BY_VAL(byte_t,            xclipframe);



private:
    OcDbDatabasePimpl * m_pDatabaseImpl;
};


END_OCTAVARIUM_NS

#endif // OcDbDatabase_h__
