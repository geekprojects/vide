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


#include "buffer.h"

#include "utf8.h"

using namespace std;

uint32_t colours[] =
{
0xbbb529,
0x77b767,
0xcc7832,
0x808080,
0xffc66d,
0xd0d0ff,
0xb389c5
};

Buffer::Buffer()
{
}

Buffer::~Buffer()
{
}

void Buffer::dump()
{
    vector<Line*>::iterator lineIt;
    for (lineIt = m_lines.begin(); lineIt != m_lines.end(); lineIt++)
    {
        Line* line = *lineIt;
        vector<LineToken*>::iterator tokenIt;
        for (tokenIt = line->tokens.begin(); tokenIt != line->tokens.end(); tokenIt++)
        {
            LineToken* token = *tokenIt;
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
    size_t read = fread(fileData, 1, length, fd);
    fclose(fd);
    if (read == 0)
    {
        return NULL;
    }

    memset(fileData + length, 0, 128);


    char* pos = fileData;
    char* end = fileData + length;

    Buffer* buffer = new Buffer();
    Line* line = NULL;
    LineToken* token = NULL;

    while (pos < end)
    {
        if (line == NULL)
        {
            line = new Line();
            line->text = L"";

            token = new LineToken();
            token->colour = colours[line->tokens.size() % (sizeof(colours) / sizeof(uint32_t))];
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
            line->lineEnding = L"";
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

    delete[] fileData;
    return buffer;
}

void Line::clearTokens()
{
    vector<LineToken*>::iterator it;
    for (it = tokens.begin(); it != tokens.end(); it++)
    {
        delete *it;
    }
    tokens.clear();
}


