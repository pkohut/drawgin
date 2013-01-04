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
#include "OcError.h"
#include "OcTypes.h"
#include "OcDbObjectId.h"
#include "../OcDf/OcDfDwgVersion.h"

#include "OcBsStreamIn.h"
#include "DwgInArchive.h"
#include "OcBsDwgPreviewImage.h"
#include "OcBsDwgSentinels.h"

BEGIN_OCTAVARIUM_NS

OcBsDwgPreviewImage::OcBsDwgPreviewImage(void)
{
}

OcBsDwgPreviewImage::~OcBsDwgPreviewImage(void)
{
}

const std::vector<byte_t> & OcBsDwgPreviewImage::HeaderData(void) const
{
    return m_hdrData;
}

const std::vector<byte_t> & OcBsDwgPreviewImage::BmpData(void) const
{
    return m_bmpData;
}

const std::vector<byte_t> & OcBsDwgPreviewImage::WmfData(void) const
{
    return m_wmfData;
}

OcApp::ErrorStatus OcBsDwgPreviewImage::DecodeData(DwgInArchive& in)
{
    ASSERT_ARCHIVE_NOT_LOADING(in);
    bitcode::RC sentinelData[16];
    in.ReadRC(sentinelData, 16);
    if(!CompareSentinels(sentinelImageDataStart, sentinelData)) {
        return OcApp::eInvalidImageDataSentinel;
    }

    int32_t overallSize;
    char imagesPresent;
    in >> ((bitcode::RL&) overallSize);
    int32_t nextSentinel = in.FilePosition() + overallSize;
    in >> ((bitcode::RC&) imagesPresent);
    int32_t headerDataBegin = 0, bmpDataBegin = 0, wmfDataBegin = 0;

    for(int i = 0; i < imagesPresent; ++i) {
        char code;
        int32_t dataSize;
        in >> ((bitcode::RC&) code);
        if(code == 1) {
            in >> ((bitcode::RL&) headerDataBegin);
            in >> ((bitcode::RL&) dataSize);
            m_hdrData.resize(dataSize);
        } else if(code == 2) {
            in >> ((bitcode::RL&) bmpDataBegin);
            in >> ((bitcode::RL&) dataSize);
            m_bmpData.resize(dataSize);
        } else if(code == 3) {
            in >> ((bitcode::RL&) wmfDataBegin);
            in >> ((bitcode::RL&) dataSize);
            m_wmfData.resize(dataSize);
        } else {
            return OcApp::eInvalidImageDataCode;
        }
    }

    if(m_hdrData.size()) {
        if(in.FilePosition() != headerDataBegin) {
            return OcApp::eMismatchedFilePosition;
        }
        in.ReadRC((bitcode::RC*)&m_hdrData[0], m_hdrData.size());
        if(!IsHeadDataAllNULL(m_hdrData)) {
            return OcApp::eUnknownHeaderDataValues;
        }
    }

    if(m_bmpData.size()) {
        if(in.FilePosition() != bmpDataBegin) {
            return OcApp::eMismatchedFilePosition;
        }
        in.ReadRC((bitcode::RC*)&m_bmpData[0], m_bmpData.size());
    }

    if(m_wmfData.size()) {
        if(in.FilePosition() != wmfDataBegin) {
            return OcApp::eMismatchedFilePosition;
        }
        in.ReadRC((bitcode::RC*)&m_wmfData[0], m_wmfData.size());
    }

    if(nextSentinel != in.FilePosition()) {
        return OcApp::eMismatchedFilePosition;
    }
    in.ReadRC(sentinelData, 16);
    if(!CompareSentinels(sentinelImageDataEnd, sentinelData)) {
        return OcApp::eInvalidImageDataSentinel;
    }

    return OcApp::eOk;
}

bool OcBsDwgPreviewImage::IsHeadDataAllNULL(const std::vector<byte_t>& data) const
{
    std::not_equal_to<int> comparator;
    if(data.end() != std::find_if(data.begin(), data.end(),
                                  boost::bind(comparator, _1, 0))) {
        return false;
    }
    return true;
}

DwgInArchive& operator>>(DwgInArchive& in, OcBsDwgPreviewImage & imgData)
{
    ASSERT_ARCHIVE_NOT_LOADING(in);
    in.SetError(imgData.DecodeData(in));
    return in;
}

END_OCTAVARIUM_NS
