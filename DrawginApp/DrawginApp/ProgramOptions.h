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

#pragma once

extern const int major_version;
extern const int minor_version;
extern const int patch_version;
extern const char* DefaultLogDir();

BEGIN_OCTAVARIUM_NS

class ProgramOptions
{
public:
    ProgramOptions();
    ~ProgramOptions();

    std::string GetAppName(std::string sFilepath);
    void ShowHelp();
    int Set(int argc, char * argv[]);

    bool logtostderr(void);
    void logtostderr(bool val);

    bool alsologtostderr(void);
    void alsologtostderr(bool val);

    int stderrthreshold(void);
    void stderrthreshold(int val);

    bool log_prefix(void);
    void log_prefix(bool val);

    int minloglevel(void);
    void minloglevel(int val);

    int logbuflevel(void);
    void logbuflevel(int val);

    int logbufsecs(void);
    void logbufsecs(int val);

    std::string log_dir(void);
    void log_dir(const std::string & val);

    std::string log_link(void);
    void log_link(const std::string & val);

    int max_log_size(void);
    void max_log_size(int val);

    bool stop_logging_if_full_disk(void);
    void stop_logging_if_full_disk(bool val);

    int v(void);
    void v(int val);

    std::string version(void);

    std::string drawing(void);
    void drawing(const std::string & val);

private:
    std::string m_sDrawing;

};

END_OCTAVARIUM_NS
