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


#include <vide/buffer.h>
#include <vide/utils.h>

#include "../utf8.h"

#include <string.h>

using namespace std;
using namespace Geek;

Buffer::Buffer(string filename)
{
    m_filename = filename;
    m_dirty = true;

    m_mutex = Thread::createMutex();
}

Buffer::~Buffer()
{
}

TokenAt Buffer::getToken(Position pos)
{
    TokenAt at;
    if (pos.line >= m_lines.size())
    {
        at.token = NULL;
        at.tokenColumn = 0;
        return at;
    }

    Line* line = m_lines.at(pos.line);
    if (pos.column >= line->text.length())
    {
        pos.column = line->text.length() - 1;
    }
    return line->tokenAt(pos.column, false);
}

void Buffer::insertLine(int asLine, Line* line)
{
    vector<Line*>::iterator it;
    int i;
    for (it = m_lines.begin(), i = 0; i < asLine && it != m_lines.end(); it++, i++)
    {
    }
    m_lines.insert(it, line);

    line->dirty = true;
    m_dirty = true;
}

void Buffer::deleteLine(int line)
{
    vector<Line*>::iterator it;
    int i;
    for (it = m_lines.begin(), i = 0; i < line && it != m_lines.end(); it++, i++)
    {
    }
    m_lines.erase(it);

    m_dirty = true;
}

void Buffer::setDirtyLine(Line* line)
{
    line->dirty = true;
    m_dirty = true;
    m_timestamp = Utils::getTimestamp();
}

void Buffer::clearDirty()
{
    m_dirty = false;
}

bool Buffer::save()
{
    FILE* fd = fopen(m_filename.c_str(), "w");
    for (Line* line : m_lines)
    {
        unsigned int pos;
        for (pos = 0; pos < line->text.length(); pos++)
        {
            wchar_t c = line->text.at(pos);

            char buffer[6] = {0, 0, 0, 0, 0, 0};
            char* end = utf8::append(c, buffer);

            char* p;
            for (p = buffer; p < end; p++)
            {
                fputc(*p, fd);
            }

        }

        // Write the End Of Line
        fwrite(line->lineEnding.c_str(), line->lineEnding.length(), 1, fd);
    }

    fclose(fd);

    return true;
}

char* Buffer::writeToMem(uint32_t& size)
{
    size = 0;

    for (Line* line : m_lines)
    {
        unsigned int pos;
        for (pos = 0; pos < line->text.length(); pos++)
        {
            wchar_t c = line->text.at(pos);

            char buffer[6] = {0, 0, 0, 0, 0, 0};
            char* end = utf8::append(c, buffer);
            size += (end - buffer);
        }
        size += line->lineEnding.length();
    }

    char* data = new char[size];
    char* p = data;

    for (Line* line : m_lines)
    {
        unsigned int pos;
        for (pos = 0; pos < line->text.length(); pos++)
        {
            wchar_t c = line->text.at(pos);

            p = utf8::append(c, p);
        }

        // Write the End Of Line
        for (pos = 0; pos < line->lineEnding.length(); pos++)
        {
            *(p++) = line->lineEnding.at(pos);
        }
    }

    return data;
}

void Buffer::dump()
{
    for (Line* line : m_lines)
    {
        for (LineToken* token : line->tokens)
        {
            printf("[%ls]", token->text.c_str());
        }
        printf("\n");
    }
}

Buffer* Buffer::loadFile(const char* filename)
{
    FILE* fd = fopen(filename, "r");
    if (fd == NULL)
    {
        return NULL;
    }

    fseek(fd, 0, SEEK_END);
    size_t length = ftell(fd);
    fseek(fd, 0, SEEK_SET);

    char* fileData = new char[length + 128];
    if (length > 0)
    {
        size_t read = fread(fileData, 1, length, fd);
        fclose(fd);
        if (read == 0)
        {
            return NULL;
        }
    }

    memset(fileData + length, 0, 128);

    char* pos = fileData;
    char* end = fileData + length;

    Buffer* buffer = new Buffer(filename);
    Line* line = NULL;
    LineToken* token = NULL;

    while (pos < end)
    {
        if (line == NULL)
        {
            line = new Line();
            line->text = L"";

            token = new LineToken();
            token->type = TOKEN_TEXT;
            token->text = L"";

            line->tokens.push_back(token);
        }

        wchar_t cur = utf8::next(pos, end);
        if (cur == 0)
        {
            break;
        }

        if (cur == L'\n' || cur == L'\r')
        {
            line->lineEnding = "";
            line->lineEnding += cur;

            if (cur == L'\r')
            {
                cur = utf8::peek_next(pos, end);
                if (cur == L'\n')
                {
                    utf8::next(pos, end);
                    line->lineEnding += cur;
                }
            }

            buffer->m_lines.push_back(line);

            line = NULL;
        }
/*
        else if (cur == L' ')
        {
            fragment = new LineFragment();
            line->fragments.push_back(fragment);
            fragment->text = L" ";
            line->length++;

            fragment = new LineFragment();
            fragment->colour = colours[line->fragments.size() % (sizeof(colours) / sizeof(uint32_t))];
            line->fragments.push_back(fragment);
            line->line += cur;
        }
*/
        else
        {
            token->text += cur;
            line->text += cur;
        }
    }

    if (line != NULL)
    {
        buffer->m_lines.push_back(line);
    }

    if (buffer->m_lines.empty())
    {
        line = new Line();
        line->text = L"";
        buffer->m_lines.push_back(line);
    }

    delete[] fileData;
    return buffer;
}

void Buffer::lock()
{
    m_mutex->lock();
}

void Buffer::unlock()
{
    m_mutex->unlock();
}

TokenAt Line::tokenAt(unsigned int column, bool ignoreSpace)
{
    TokenAt at;
    at.token = NULL;
    at.tokenColumn = 0;
    at.it = tokens.begin();

    if (column == 0)
    {
        at.token = *(at.it);
        return at;
    }

#if 0
    printf("Line::tokenAt: column=%u, ignoreSpace=%d\n", column, ignoreSpace);
#endif
    LineToken* token = NULL;
    for (at.it = tokens.begin(); at.it != tokens.end(); at.it++, at.tokenColumn += token->text.length())
    {
        token = *(at.it);
#if 0
        printf("Line::tokenAt: token=%ls, column=%d, isSpace=%d\n", token->text.c_str(), token->column, token->isSpace);
#endif
        if (at.tokenColumn + token->text.length() > column)
        {
#if 0
        printf("Line::tokenAt: Found! isSpace=%d\n", token->isSpace);
#endif
            if (!ignoreSpace || !token->isSpace)
            {
                at.token = token;
                return at;
            }
        }
    }
    return at;
}

void Line::clearTokens()
{
    vector<LineToken*>::iterator it;
    for (it = tokens.begin(); it != tokens.end(); it++)
    {
        delete *it;
    }
    tokens.clear();

    dirty = true;
}


