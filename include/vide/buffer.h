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

#include <sigc++/sigc++.h>

#include <frontier/utils.h>
#include <geek/core-thread.h>

#include <vide/tokeniser.h>
#include <vide/projectdefs.h>

class ProjectFile;

struct Position
{
    unsigned int line;
    unsigned int column;

    Position()
    {
        set(0, 0);
    }

    Position(unsigned int l, unsigned int c)
    {
        set(l, c);
    }

    void set(unsigned int l, unsigned int c)
    {
        line = l;
        column = c;
    }

    bool operator < (Position& rhs)
    {
        if (line < rhs.line)
        {
            return true;
        }
        else if (line > rhs.line)
        {
            return false;
        }
        else
        {
            return (column < rhs.column);
        }
    }

    bool operator > (Position& rhs)
    {
        if (line > rhs.line)
        {
            return true;
        }
        else if (line < rhs.line)
        {
            return false;
        }
        else
        {
            return (column > rhs.column);
        }
    }

    bool operator >= (Position& rhs)
    {
        return !((*this) < rhs);
    }

    bool operator == (Position& rhs)
    {
        return (line == rhs.line && column == rhs.column);
    }

    bool operator != (Position& rhs)
    {
        return (line != rhs.line || column != rhs.column);
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
    //unsigned int column;
    std::wstring text;
    TokenType type;
    ProjectDefinitionType definitionType;
    bool isSpace;
    Frontier::Rect drawRect;

    std::vector<TokenMessage> messages;
};

struct TokenAt
{
    unsigned int tokenColumn;
    LineToken* token;
    std::vector<LineToken*>::iterator it;
};

struct Line
{
    std::wstring text;
    std::string lineEnding;

    std::vector<LineToken*> tokens;

    bool dirty;

    Line()
    {
        text = L"";
        lineEnding = "";
        dirty = true;
    }

    ~Line()
    {
        clearTokens();
    }

    TokenAt tokenAt(unsigned int column, bool ignoreSpace);

    void clearTokens();
};

class Buffer
{
 private:
    std::string m_filename;
    ProjectFile* m_projectFile;
    std::vector<Line*> m_lines;
    bool m_dirty;
    std::string m_lineEnding;

    uint64_t m_timestamp;
    Geek::Mutex* m_mutex;

    sigc::signal<void> m_tokeniseCompleteSignal;

 public:
    Buffer(std::string filename);
    ~Buffer();

    std::string getFilename() { return m_filename; }

    void setProjectFile(ProjectFile* pf) { m_projectFile = pf; }
    ProjectFile* getProjectFile() { return m_projectFile; }

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
    Line* getLine(int y)
    {
        if (y >= 0 && y < (int)m_lines.size())
        {
            return m_lines.at(y);
        }
        else
        {
            return NULL;
        }
    }
    TokenAt getToken(Position position);

    void insertLine(int asLine, Line* line);
    void deleteLine(int line);
    bool isDirty() { return m_dirty; }
    void setDirtyLine(Line* line);
    void clearDirty();

    uint64_t getTimestamp() { return m_timestamp; }
    void lock();
    void unlock();

    bool save();
    char* writeToMem(uint32_t& size);

    sigc::signal<void> tokeniseCompleteSignal() { return m_tokeniseCompleteSignal; }

    void dump();

    static Buffer* loadFile(const char* filename);
    static Buffer* loadMem(const char* filename, const char* start, const char* end);
    static Buffer* loadString(const char* filename, std::string text);
};

#endif

