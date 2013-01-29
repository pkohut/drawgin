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

#include "stdafx.h"
#include "OcCommon.h"
#include "ProgramOptions.h"

using namespace google;
using namespace std;

BEGIN_OCTAVARIUM_NS

ProgramOptions::ProgramOptions()
{

}

ProgramOptions::~ProgramOptions()
{

}

std::string ProgramOptions::GetAppName(std::string sFilepath)
{
    size_t pos = sFilepath.find_last_of("/\\");
    if(pos != string::npos)
    {
        sFilepath = sFilepath.substr(++pos);
    }

    pos = sFilepath.find_last_of(".");
    if(pos != string::npos)
    {
        sFilepath = sFilepath.substr(0, pos);
    }
    return sFilepath;
}

void ProgramOptions::ShowHelp()
{
    cout << " Options:" << endl;
    cout << "  --help                  display this help and exit." << endl;
    cout << "  --logtostderr=bool      log messages to stderr instead of log files." << endl;
    cout << "                          Defaults to 0" << endl;
    cout << "  --alsologtostderr=bool  log messages to stderr in addition to log files." << endl;
    cout << "                          Defaults to 0" << endl;
    cout << "  --stderrthreshold=int   log messages at or above this level are copied to" << endl;
    cout << "                          stderr in addition to log files." << endl;
    cout << "                          Defaults to 2 (INFO = 0 WARNING = 1" << endl;
    cout << "                                         ERROR = 2 FATAL = 3" << endl;
    cout << "                                         NUM_SEVERITIES = 4" << endl;
    cout << "  --log_prefix=bool       Prepend the log prefix to the start of each log line." << endl;
    cout << "                          Defaults to 1" << endl;
    cout << "  --minloglevel=int       Messages logged at a lower level than this don't" << endl;
    cout << "                          actually get logged anywhere." << endl;
    cout << "                          Defaults to 0" << endl;
    cout << "  --logbuflevel=int       Buffer log messages logged at this level or lower" << endl;
    cout << "                           (-1 means don't buffer; 0 means buffer INFO only;" << endl;
    cout << "                            ...)." << endl;
    cout << "                          Defaults to 0" << endl;
    cout << "  --logbufsecs=int        Buffer log messages for at most this many seconds." << endl;
    cout << "                          Defaults to 30" << endl;
    cout << "  --log_dir=string        If specified, log files are written into this" << endl;
    cout << "                          directory instead of the default logging directory." << endl;
    cout << "                          Defaults to " << DefaultLogDir() << endl;
    cout << "  --log_link=string       Put additional links to the log files in this" << endl;
    cout << "                          directory." << endl;
    cout << "                          Defaults to \"\"" << endl;
    cout << "  --max_log_size=int      Approx. maximum log file size (in MB). A value of 0" << endl;
    cout << "                          will be silently overridden to 1." << endl;
    cout << "                          Defaults to 1800" << endl;
    cout << "  --stop_logging_if_full_disk=bool Stop attempting to log to disk if the disk" << endl;
    cout << "                                   is full." << endl;
    cout << "                                   Defaults to 0" << endl;
    cout << "  --v=int                 Gives the default maximal active V-logging level." << endl;
    cout << "                          Defaults to 0" << endl;
    cout << "  --drawing=string        Input drawing file name (fullpath) to process." << endl;
    cout << "  --version               Display version of this application." << endl;
}

int ProgramOptions::Set( int argc, char * argv[] )
{
    for(int i = 1; i < argc; ++i)
    {
        string str(argv[i]);
        size_t pos = str.find('=');
        if(pos == string::npos)
        {
            if(str == "--version")
            {
                cout << "version " << version() << endl;
                continue;
            }
            else if(str == "--help")
            {
                cout << "Usage: " << GetAppName(argv[0]) << " [options...]" << endl;
                ShowHelp();
                return 1;
            }
            else
            {                    
                cout << "the required argument for option '" << str << "' is missing" << endl;
                return 1;
            }
        }

        if(pos == str.length() - 1)
        {
            cout << "the argument for option '" << str.substr(0, pos) << "' should follow immediately after the equal sign" << endl;
            return 1;
        }

        string s1 = str.substr(0, pos);
        string s2 = str.substr(pos + 1);
        try
        {
            if(s1 == "--logtostderr")
            {
                logtostderr(!!stoi(s2));
                continue;
            }
            if(s1 == "--alsologtostderr")
            {
                alsologtostderr(!!stoi(s2));
                continue;
            }
            if(s1 == "--stderrthreshold")
            {
                stderrthreshold(stoi(s2));
                continue;
            }
            if(s1 == "--log_prefix")
            {
                log_prefix(!!stoi(s2));
                continue;
            }
            if(s1 == "--minloglevel")
            {
                minloglevel(stoi(s2));
                continue;
            }
            if(s1 == "--logbuflevel")
            {
                logbuflevel(stoi(s2));
                continue;
            }
            if(s1 == "--logbufsecs")
            {
                logbufsecs(stoi(s2));
                continue;
            }
            if(s1 == "--log_dir")
            {
                log_dir(s2);
                continue;
            }
            if(s1 == "--log_link")
            {
                log_link(s2);
                continue;
            }
            if(s1 == "--max_log_size")
            {
                max_log_size(stoi(s2));
                continue;
            }
            if(s1 == "--stop_logging_if_full_disk")
            {
                stop_logging_if_full_disk(!!stoi(s2));
                continue;
            }
            if(s1 == "--v")
            {
                v(stoi(s2));
                continue;
            }
            if(s1 == "--drawing")
            {
                drawing(s2);
                continue;
            }

            cout << str << endl;
            cout << "unrecognised option '" << str << "'" << endl;
            return 1;
        }
        catch (...)
        {
            cout << "the argument ('" << s2 << "') for option '" << s1 << "' is invalid" << endl;
            return 1;
        }
    }

    if(drawing().empty()) 
    {
        cout << "Drawing file not specified" << endl;
        cout << "Use --help for available options." << endl;
        return 1;
    }

    return 0;
}

bool ProgramOptions::logtostderr( void )
{
    return OcLogger::LogToStdError();
}

void ProgramOptions::logtostderr( bool val )
{
    OcLogger::SetLogToStdError(val);
}

bool ProgramOptions::alsologtostderr( void )
{
    return OcLogger::AlsoLogToStdError();
}

void ProgramOptions::alsologtostderr( bool val )
{
    OcLogger::SetAlsoLogToStdError(val);
}

int ProgramOptions::stderrthreshold( void )
{
    return OcLogger::StdErrorThreshold();
}

void ProgramOptions::stderrthreshold( int val )
{
    OcLogger::SetStdErrorThreshold(val);
}

bool ProgramOptions::log_prefix( void )
{
    return OcLogger::LogPrefix();
}

void ProgramOptions::log_prefix( bool val )
{
    OcLogger::SetLogPrefix(val);
}

int ProgramOptions::minloglevel( void )
{
    return OcLogger::MinLogLevel();
}

void ProgramOptions::minloglevel( int val )
{
    OcLogger::SetMinLogLevel(val);
}

int ProgramOptions::logbuflevel( void )
{
    return OcLogger::LogBufferLevel();
}

void ProgramOptions::logbuflevel( int val )
{
    OcLogger::SetLogBufferLevel(val);
}

int ProgramOptions::logbufsecs( void )
{
    return OcLogger::LogBufferSeconds();
}

void ProgramOptions::logbufsecs( int val )
{
    OcLogger::SetLogBufferSeconds(val);
}

std::string ProgramOptions::log_dir( void )
{
    return OcLogger::LogDirectory();
}

void ProgramOptions::log_dir( const std::string & val )
{
    OcLogger::SetLogDirectory(val);
}

std::string ProgramOptions::log_link( void )
{
    return OcLogger::LogLink();
}

void ProgramOptions::log_link( const std::string & val )
{
    OcLogger::SetLogLink(val);
}

int ProgramOptions::max_log_size( void )
{
    return OcLogger::MaxLogSize();
}

void ProgramOptions::max_log_size( int val )
{
    OcLogger::SetMaxLogSize(val);
}

bool ProgramOptions::stop_logging_if_full_disk( void )
{
    return OcLogger::StopLoggingIfFullDisk();
}

void ProgramOptions::stop_logging_if_full_disk( bool val )
{
    OcLogger::SetStopLoggingIfFullDisk(val);
}

int ProgramOptions::v( void )
{
    return OcLogger::VLOGLevel();
}

void ProgramOptions::v( int val )
{
    OcLogger::SetVLOGLevel(val);
}

std::string ProgramOptions::version( void )
{
    stringstream ss;
    ss << major_version << "."
        << minor_version << "."
        << patch_version;
    return ss.str();
}

std::string ProgramOptions::drawing( void )
{
    return m_sDrawing;
}

void ProgramOptions::drawing( const std::string & val )
{
    m_sDrawing = val;
}

END_OCTAVARIUM_NS