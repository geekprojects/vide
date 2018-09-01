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

#include <wchar.h>

using namespace std;

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

