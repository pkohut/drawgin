// DrawginApp.cpp : Defines the entry point for the console application.
//

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
#include <boost/program_options.hpp>
#include "OcCommon.h"
#include "OcError.h"
#include "OcDbSmartPtrs.h"
#include "OcRxObject.h"

#include "OcDbDatabase.h"
#include "OcApApplication.h"
#include "OcDbObject.h"
#include "OcRxClass.h"
#include "OcDbEntity.h"

#include "OcLogger.h"

using namespace std;
using namespace google;
using namespace octavarium;

namespace po = boost::program_options;

const static int major_version = 0;
const static int minor_version = 1;
const static int patch_version = 1;

string VersionString(void)
{
    stringstream ss;
    ss << major_version << "."
        << minor_version << "."
        << patch_version;
    return ss.str();
}

// From GLOG, logging.cc,
// Compute the default value for --log_dir
static const char* DefaultLogDir()
{
    const char* env;
    env = getenv("GOOGLE_LOG_DIR");
    if(env != NULL && env[0] != '\0') {
        return env;
    }
    env = getenv("TEST_TMPDIR");
    if(env != NULL && env[0] != '\0') {
        return env;
    }
    return "";
}

int SetProgramOptionsDesc(po::options_description & desc)
{
    try {
        // predefine dynamic string
        string sLogFiles = "If specified, log files are written into this "
            "directory instead of the default logging "
            "directory.\n"
            "Defaults to ";
        sLogFiles += DefaultLogDir();

        desc.add_options()
            ("help", "produce help message")

            ("logtostderr", po::value<bool>(&FLAGS_logtostderr),
            "Log messages go to stderr instead of log files.\n"
            "Defaults to 0")

            ("alsologtostderr", po::value<bool>(&FLAGS_alsologtostderr),
            "log messages go to stderr in addition to log files.\n"
            "Defaults to 0")

            ("stderrthreshold", po::value<int>(&FLAGS_stderrthreshold),
            "log messages at or above this level are copied to stderr in "
            "addition to log files.\n"
            "Defaults to 2 (INFO = 0 WARNING = 1\n"
            "               ERROR = 2 FATAL = 3\n"
            "               NUM_SEVERITIES = 4)")

            ("log_prefix", po::value<bool>(&FLAGS_log_prefix),
            "Prepend the log prefix to the start of each log line\n"
            "Defaults to 1")

            ("minloglevel", po::value<int>(&FLAGS_minloglevel),
            "Messages logged at a lower level than this don't "
            "actually get logged anywhere\n"
            "Defaults to 0")

            ("logbuflevel", po::value<int>(&FLAGS_logbuflevel),
            "Buffer log messages logged at this level or lower"
            " (-1 means don't buffer; 0 means buffer INFO only;"
            " ...)\n"
            "Defaults to 0")

            ("logbufsecs", po::value<int>(&FLAGS_logbufsecs),
            "Buffer log messages for at most this many seconds\n"
            "Defaults to 30")

            ("log_dir", po::value<string>(&FLAGS_log_dir),
            sLogFiles.c_str())

            ("log_link", po::value<string>(&FLAGS_log_link),
            "Put additional links to the log "
            "files in this directory\n"
            "Defaults to \"\"")

            ("max_log_size", po::value<int>(&FLAGS_max_log_size),
            "approx. maximum log file size (in MB). A value of 0 will "
            "be silently overridden to 1.\n"
            "Defaults to 1800")

            ("stop_logging_if_full_disk",
            po::value<bool>(&FLAGS_stop_logging_if_full_disk),
            "Stop attempting to log to disk if the disk is full.\n"
            "Defaults to 0")

            ("v", po::value<int>(&FLAGS_v),
            "Gives the default maximal active V-logging level:"
            "0 is the default.\n"
            "Defaults to 0")

            ("version", "Print version info")

            ("drawing", po::value<string>(),
            "Input drawing file to process")
            ;
    } catch(exception & e) {
        cerr << e.what() << endl;
        return 1;
    } catch(...) {
        cerr << "unknown exception occurred" << endl;
        return 1;
    }
    return 0;
}

void ProcessDrawing(const string_t & filename)
{
    OcDbDatabasePtr pDb = new OcDbDatabase;
    OcApp::ErrorStatus es = pDb->Open(filename);
    LOG_IF(ERROR, es != OcApp::eOk) << "Error processing drawing.";
    //    app.SetWorkingDatabase(pDb);
    Application()->SetWorkingDatabase(pDb);
}
int main(int argc, char * argv[])
{
    // Command line options:
    // --v=4 --log_dir=$(OutDir)\logs --drawing=C:\Users\Paul\Documents\TestDwgs\EmptyR14.dwg

#if defined(_WIN32)
    // Enable memory dump from within VS.
    _CrtMemState memState;
    _CrtMemCheckpoint(&memState);
#endif

    try
    {
        // Must create the singleton object of OcApApplicationPtr
        OcApApplicationPtr app(OcApApplication::Create());

        po::options_description desc("Allowed options");
        if(SetProgramOptionsDesc(desc))
        {
            return 1;
        }

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if(vm.count("help"))
        {
            cout << "DrawginApp, version " << VersionString() << endl;
            return 1;
        }

        string_t filename;
        if(vm.count("drawing"))
        {
#ifdef _UNICODE
            // GLOG string are stored as std::strings
            string temp = vm["drawing"].as<string>();
            filename.assign(temp.begin(), temp.end());
#else
            filename = vm["drawing"].as<string>();
#endif
        } else {
            cerr << "Drawing file not specified" << endl;
            cerr << "Use --help for available options." << endl;
            return 1;
        }

        OcLogger logger(argv[0]);
        LOG(INFO) << "Begin decoding file: " << filename;
        ProcessDrawing(filename);
    }
    catch(exception & e) {
        cerr << e.what() << endl;
        return 1;
    } catch(...) {
        cerr << "unknown exception occurred" << endl;
        return 1;
    }

    // In debug mode and with OC_DEBUG_LIVING_OBJECTS defined, let
    // OcRxObject do final object check of managed objects to ensure
    // they have been released property.
    OcApApplication::Shutdown();

#if defined(_WIN32)
    // Check for memory leaks in debug builds.
    _CrtMemDumpAllObjectsSince(&memState);
#endif
    return 0;
}