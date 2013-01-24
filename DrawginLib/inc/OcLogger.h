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

#ifndef OcLogger_h__
#define OcLogger_h__

#include <glog/logging.h>

class OcNullLogger : public google::base::Logger
{
public:
    virtual void Write(bool should_flush, time_t timestamp, const char * message, int length)
    {
    }
    virtual void Flush() {}
    virtual google::uint32 LogSize()
    {
        return 0;
    }
};

class OcLogger
{
    OcLogger() {}
    OcLogger(const OcLogger &) {}
    OcLogger & operator=(const OcLogger&) {}
    google::base::Logger * SetLoggerToNullLogger(int severity)
    {
        google::base::Logger * pOldLogger = google::base::GetLogger(severity);
        google::base::SetLogger(severity, &m_nullLogger);
        google::FlushLogFiles(severity);
        return pOldLogger;
    }

    OcNullLogger m_nullLogger;
public:
    OcLogger(const char * pArg)
    {
        google::InitGoogleLogging(pArg);
        SetLoggerToNullLogger(google::WARNING);
        SetLoggerToNullLogger(google::ERROR);
        SetLoggerToNullLogger(google::FATAL);
        google::SetLogFilenameExtension(".log.");
    }
    virtual ~OcLogger()
    {
        google::ShutdownGoogleLogging();
    }
};

#endif // OcLogger_h__
