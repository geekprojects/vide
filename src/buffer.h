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

#include "tokeniser.h"

struct Position
{
    unsigned int line;
    unsigned int column;

    Position()
    {
        line = 0;
        column = 0;
    }

    Position(unsigned int l, unsigned int c)
    {
        line = l;
        column = c;
    }
};

enum MessageType
{
    MESSAGE_INFO = 0,
    MESSAGE_WARNING = 1,
    MESSAGE_ERROR = 2,
};

struct TokenMessage
{
    MessageType type;
    std::string text;
};

struct LineToken
{
    unsigned int column;
    std::wstring text;
    TokenType type;
    bool isSpace;

    std::vector<TokenMessage> messages;
};

struct Line
{
    std::wstring text;
    std::string lineEnding;

    std::vector<LineToken*> tokens;

    Line()
    {
        text = L"";
        lineEnding = "";
    }

    ~Line()
    {
        clearTokens();
    }

    std::vector<LineToken*>::iterator tokenAt(unsigned int column, bool ignoreSpace);

    void clearTokens();
};

class Buffer
{
 private:
    std::string m_filename;
    std::vector<Line*> m_lines;

 public:
    Buffer(std::string filename);
    ~Buffer();

    std::string getFilename() { return m_filename; }

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
    LineToken* getToken(Position position);

    void insertLine(int asLine, Line* line);
    void deleteLine(int line);

    bool save();
    char* writeToMem(uint32_t& size);

    void dump();

    static Buffer* loadFile(const char* filename);
};

#endif

