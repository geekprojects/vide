/*
 *  b0rk - The b0rk Embeddable Runtime Environment
 *  Copyright (C) 2015, 2016 GeekProjects.com
 *
 *  This file is part of b0rk.
 *
 *  b0rk is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  b0rk is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with b0rk.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "utils.h"

#include <unistd.h>
#include <wchar.h>
#include <sys/time.h>

#include <geek/core-string.h>

using namespace std;
using namespace Geek::Core;

string Utils::wstring2string(wstring str)
{
    string out;
    unsigned int i;
    for (i = 0; i < str.length(); i++)
    {
        out += str[i];
    }
    return out;
}

wstring Utils::string2wstring(string str)
{
    wstring out;
    unsigned int i;
    for (i = 0; i < str.length(); i++)
    {
        out += (char)str[i];
    }
    return out;
}

wstring Utils::string2wstring(const char* str)
{
    wstring out;
    unsigned int i;
    for (i = 0; str[i] != 0; i++)
    {
        out += str[i];
    }
    return out;
}

bool Utils::fileIsReadable(std::string path)
{
    int res;
    res = access(path.c_str(), R_OK);
    return res == 0;
}

bool Utils::fileIsExecutable(std::string path)
{
    int res;
    res = access(path.c_str(), X_OK | R_OK);
    return res == 0;
}

string Utils::exec(string dir, string cmd)
{
    FILE *fp;

    char* cwd = getcwd(NULL, 0);

    chdir(dir.c_str());

    printf("Utils::exec: cmd: %s\n", cmd.c_str());
    fp = popen(cmd.c_str(), "r");
    if (fp == NULL)
    {
        chdir(cwd);
        free(cwd);
        return "";
    }

    char buffer[1024];
    string result = "";
    while (true)
    {
        int res;
        res = fread(buffer, 1, 1024, fp);
        if (res <= 0)
        {
            break;
        }

        result += string(buffer, res);
    }

    pclose(fp);

    chdir(cwd);
    free(cwd);

    return result;
}

string Utils::mkpath(string baseDir, string relativePath)
{
    printf("Utils::mkpath: baseDir=%s, relativePath=%s\n", baseDir.c_str(), relativePath.c_str());
    if (relativePath.length() == 0)
    {
        return "";
    }
    if (relativePath.at(0) == '/')
    {
        // Relative is actually absolute
        return relativePath;
    }

    vector<string> baseParts = splitString(baseDir, '/');
    vector<string> relParts = splitString(relativePath, '/');

    for (string part : relParts)
    {
        if (part == ".")
        {
            continue;
        }
        else if (part == "..")
        {
            if (!baseParts.empty())
            {
                baseParts.pop_back();
            }
        }
        else
        {
            baseParts.push_back(part);
        }
    }

    string result = "";
    for (string part: baseParts)
    {
        result += "/" + part;
    }

    return result;
}

uint64_t Utils::getTimestamp()
{
    timeval tv;
    gettimeofday(&tv, NULL);
    uint64_t millis;
    millis = tv.tv_sec * 1000l;
    millis += tv.tv_usec / 1000l;

    return millis;
}

