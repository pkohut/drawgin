/**
 *	@file
 *  @brief Logging library
 *
 *  A wrapper around the glog library.
 *
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

#pragma once

#include <glog/logging.h>
#include "OcCommon.h"
#include "wchar_logging.h"

BEGIN_OCTAVARIUM_NS

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

    static void Init()
    {
#if !defined(NDEBUG)
        // These global strings in GLOG are initially reserved with a small
        // amount of storage space. Resizing the string larger than its
        // initial size can be reported as a memory leak, which it is not.
        // So for debug builds, where memory leak checking is performed,
        // reserve a large enough space so the string will not be resized.
        // For these variables, _MAX_PATH should be fine.
        FLAGS_log_dir.reserve(_MAX_PATH);
        FLAGS_log_link.reserve(_MAX_PATH);
#endif
    }

    // (V)erbose logging level
    static void SetVLOGLevel(int vLogLevel)
    {
        FLAGS_v = vLogLevel;
    }
    static int  VLOGLevel(void)
    {
        return FLAGS_v;
    }

    // If specified, logfiles are written into this directory instead of the
    // default logging directory.
    static void         SetLogDirectory(const std::string logDir)
    {
        FLAGS_log_dir = logDir;
    }
    static std::string  LogDirectory(void)
    {
        return FLAGS_log_dir;
    }

    // Sets the path of the directory into which to put additional links
    // to the log files.
    static void         SetLogLink(const std::string logLink)
    {
        FLAGS_log_link = logLink;
    }
    static std::string  LogLink(void)
    {
        return FLAGS_log_link;
    }

    // Set whether log messages go to stderr instead of logfiles
    static void         SetLogToStdError(bool val = true)
    {
        FLAGS_logtostderr = val;
    }
    static bool         LogToStdError(void)
    {
        return FLAGS_logtostderr;
    }

    // Set whether log messages go to stderr in addition to logfiles.
    static void         SetAlsoLogToStdError(bool val = true)
    {
        FLAGS_alsologtostderr = val;
    }
    static bool         AlsoLogToStdError(void)
    {
        return FLAGS_alsologtostderr;
    }

    // Log messages at or above this level are copied to stderr in addition to log files.
    // Defaults to 2 (INFO = 0 WARNING = 1 ERROR = 2 FATAL = 3 Num_SEVERITIES = 4)
    static void         SetStdErrorThreshold(int serverity = 2)
    {
        FLAGS_stderrthreshold = serverity;
    }
    static int          StdErrorThreshold(void)
    {
        return FLAGS_stderrthreshold;
    }

    // Prepend the log prefix to the start of each log line
    static void         SetLogPrefix(bool val = true)
    {
        FLAGS_log_prefix = val;
    }
    static bool         LogPrefix(void)
    {
        return FLAGS_log_prefix;
    }

    // Messages logged at a lower level than this don't actually get logged anywhere
    static void         SetMinLogLevel(int minLevel = 0)
    {
        FLAGS_minloglevel = minLevel;
    }
    static int          MinLogLevel(void)
    {
        return FLAGS_minloglevel;
    }

    // Buffer log messages logged at this level or lower
    // (-1 means don't buffer; 0 means buffer INFO only ...)
    static void         SetLogBufferLevel(int level = 0)
    {
        FLAGS_logbuflevel = level;
    }
    static int          LogBufferLevel(void)
    {
        return FLAGS_logbuflevel;
    }

    // Buffer log messages for at most this many seconds
    static void         SetLogBufferSeconds(int seconds = 30)
    {
        FLAGS_logbufsecs = seconds;
    }
    static int          LogBufferSeconds(void)
    {
        return FLAGS_logbufsecs;
    }


    // approx. maximum log file size (in MB). A value of 0 will be silently
    // overridden to 1.
    static void         SetMaxLogSize(int logSize = 1800)
    {
        FLAGS_max_log_size = logSize;
    }
    static int          MaxLogSize(void)
    {
        return FLAGS_max_log_size;
    }

    // Stop attempting to log to disk if the disk is full.
    static void         SetStopLoggingIfFullDisk(bool val = true)
    {
        FLAGS_stop_logging_if_full_disk = val;
    }
    static bool         StopLoggingIfFullDisk(void)
    {
        return FLAGS_stop_logging_if_full_disk;
    }

};


END_OCTAVARIUM_NS