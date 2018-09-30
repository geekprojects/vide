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

#ifndef __VIDE_BUFFER_H_
#define __VIDE_BUFFER_H_

#include <vector>
#include <string>
#include <wchar.h>

struct LineToken
{
    std::wstring text;
    uint32_t colour;
};

struct Line
{
    std::wstring text;
    std::wstring lineEnding;

    std::vector<LineToken*> tokens;

    Line()
    {
        text = L"";
        lineEnding = L"";
    }

    ~Line()
    {
        clearTokens();
    }

    void clearTokens();
};

class Buffer
{
 private:
    std::vector<Line*> m_lines;

 public:
    Buffer();
    ~Buffer();

    size_t getLineCount() { return m_lines.size(); }
    size_t getLineLength(unsigned int line)
    {
        if (line >= m_lines.size())
        {
            return -1;
        }
        return m_lines.at(line)->text.length();
    }

    std::vector<Line*>& getLines() { return m_lines; }
    Line* getLine(int y) { return m_lines.at(y); }

    void dump();

    static Buffer* loadFile(const char* filename);
};

#endif

