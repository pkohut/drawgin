/**
 *	@file
 */

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
#include "OcError.h"
#include "OcBsStreamIn.h"
//#include "OcBsDwgVersion.h"
#include "OcBsDwgPreviewImage.h"
#include "OcBsDwgSentinels.h"

BEGIN_OCTAVARIUM_NS

OcBsDwgPreviewImage::OcBsDwgPreviewImage(void)
{
    VLOG_FUNC_NAME;
}


OcBsDwgPreviewImage::~OcBsDwgPreviewImage(void)
{
    VLOG_FUNC_NAME;
}

const std::vector<byte_t> & OcBsDwgPreviewImage::HeaderData() const
{
    VLOG_FUNC_NAME;
    return m_hdrData;
}

const std::vector<byte_t> & OcBsDwgPreviewImage::BmpData() const
{
    VLOG_FUNC_NAME;
    return m_bmpData;
}

const std::vector<byte_t> & OcBsDwgPreviewImage::WmfData() const
{
    VLOG_FUNC_NAME;
    return m_wmfData;
}

OcApp::ErrorStatus OcBsDwgPreviewImage::ReadDwg(OcBsStreamIn & in)
{
    VLOG_FUNC_NAME;
    VLOG(4) << "OcBsDwgPreviewImage::ReadDwg entered";

    bitcode::RC sentinelData[16];
    in.ReadRC(sentinelData, 16);

    if(!CompareSentinels(sentinelImageDataStart, sentinelData))
    {
        return OcApp::eInvalidImageDataSentinel;
    }

    size_t overallSize;
    char imagesPresent;
    in >> ((bitcode::RL&) overallSize);
    std::streamoff nextSentinel = in.FilePosition() + overallSize;
    in >> ((bitcode::RC&) imagesPresent);
    std::streamoff headerDataBegin = 0, bmpDataBegin = 0, wmfDataBegin = 0;

    for(auto i = 0; i < imagesPresent; ++i)
    {
        char code;
        int32_t dataSize;
        in >> ((bitcode::RC&) code);

        if(code == 1)
        {
            in >> ((bitcode::RL&) headerDataBegin);
            in >> ((bitcode::RL&) dataSize);
            m_hdrData.resize(dataSize);
        }
        else if(code == 2)
        {
            in >> ((bitcode::RL&) bmpDataBegin);
            in >> ((bitcode::RL&) dataSize);
            m_bmpData.resize(dataSize);
        }
        else if(code == 3)
        {
            in >> ((bitcode::RL&) wmfDataBegin);
            in >> ((bitcode::RL&) dataSize);
            m_wmfData.resize(dataSize);
        }
        else
        {
            return OcApp::eInvalidImageDataCode;
        }
    }

    if(m_hdrData.size())
    {
        if(in.FilePosition() != headerDataBegin)
        {
            return OcApp::eMismatchedFilePosition;
        }

        in.ReadRC((bitcode::RC*)&m_hdrData[0], m_hdrData.size());
        if(!IsHeaderDataAllNULL(m_hdrData))
        {
            return OcApp::eUnknownHeaderDataValues;
        }
    }

    if(m_bmpData.size())
    {
        if(in.FilePosition() != bmpDataBegin)
        {
            return OcApp::eMismatchedFilePosition;
        }
        in.ReadRC((bitcode::RC*)&m_bmpData[0], m_bmpData.size());
    }

    if(m_wmfData.size())
    {
        if(in.FilePosition() != wmfDataBegin)
        {
            return OcApp::eMismatchedFilePosition;
        }
        in.ReadRC((bitcode::RC*)&m_bmpData[0], m_wmfData.size());
    }

    if(nextSentinel != in.FilePosition())
    {
        return OcApp::eMismatchedFilePosition;
    }

    in.ReadRC(sentinelData, 16);
    if(!CompareSentinels(sentinelImageDataEnd, sentinelData))
    {
        return OcApp::eInvalidImageDataSentinel;
    }
    return OcApp::eOk;
}

bool OcBsDwgPreviewImage::IsHeaderDataAllNULL(const std::vector<byte_t>& data) const
{
    VLOG_FUNC_NAME;
    return data.end() != std::find_if(data.begin(), data.end(),
                                      [](int x)
    {
        return x == 0;
    });
}


END_OCTAVARIUM_NS
