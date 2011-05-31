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

#ifndef OcBsDwgFileHeader_h__
#define OcBsDwgFileHeader_h__

//#include "DwgInArchive.h"

BEGIN_OCTAVARIUM_NS
class DwgInArchive;
struct OcApp;

class OcBsDwgFileHeaderSection
{
public:
    OcBsDwgFileHeaderSection() : recordNumber(0), seeker(0), size(0) {}
    ~OcBsDwgFileHeaderSection() {}
    int8_t recordNumber;
    int32_t seeker;
    int32_t size;
};

class OcBsDwgFileHeader
{
public:
    OcBsDwgFileHeader(void);
    virtual ~OcBsDwgFileHeader(void);

    DWG_VERSION DwgVersion(void) const;
    bool IsPreR13c3(void) const;
    bool IsR13c3OrHigher(void) const;

    int32_t ImageSeeker(void) const;
    int NumSectionRecords(void) const;
    const OcBsDwgFileHeaderSection& Record(int nRecord) const;
private:
    friend DwgInArchive& operator>>(DwgInArchive& in, OcBsDwgFileHeader & hdr);
    DWG_VERSION DecodeVersionData(DwgInArchive& in);
    OcApp::ErrorStatus DecodeR13_R2000Header(DwgInArchive& in);

private:
    DWG_VERSION m_dwgVersion;
    int32_t m_unknown_offset_0x06;
    int8_t m_unknown_offset_0x0a;
    int8_t m_acadMaintVer;
    int8_t m_unknown_offset_0x0c;
    int32_t m_imageSeeker;
    int16_t m_unknown_offset_0x11;
    int16_t m_codePage;
    int32_t m_nSections;

    std::vector<OcBsDwgFileHeaderSection> m_headerSections;
};

END_OCTAVARIUM_NS

#endif // OcBsDwgFileHeader_h__
