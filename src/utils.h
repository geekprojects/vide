/*
 * Vide - Vi IDE
 * Copyright (C) 2018 Ian Parker <ian@geekprojects.com>
 *
 * This file is part of Vide.
 *
 * Vide is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Vide is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Vide.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __VIDE_UTILS_H_
#define __VIDE_UTILS_H_

#include <string>

class Utils
{
 public:
    static std::string wstring2string(std::wstring str);
    static std::wstring string2wstring(std::string str);
    static std::wstring string2wstring(const char* str);

    static bool fileIsReadable(std::string path);
    static bool fileIsExecutable(std::string path);

    static std::string exec(std::string dir, std::string cmd);

    static std::string mkpath(std::string baseDir, std::string relativePath);
};

#endif
