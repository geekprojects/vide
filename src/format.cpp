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

#include "format.h"

using namespace std;

Format::Format()
{
}

Format::~Format()
{
}


bool Format::tokenise(Buffer* buffer)
{
    vector<Line*>::iterator lineIt;

    for (lineIt = buffer->getLines().begin(); lineIt != buffer->getLines().end(); lineIt++)
    {
        bool res;
        res = tokenise(*lineIt);
        if (!res)
        {
            return false;
        }
    }

    return true;
}

bool Format::tokenise(Line* line)
{

    return true;
}

static uint32_t g_colours[] =
{
    0xbbb529,
    0x77b767,
    0xcc7832,
    0x808080,
    0xffc66d,
    0xd0d0ff,
    0xb389c5

/*
    0xF8F8F2,
    0xAE81FF,
    0xE6DB74,
    0xBCA3A3,
    0x960050
*/
};

SimpleFormat::SimpleFormat()
{
}

SimpleFormat::~SimpleFormat()
{
}

bool SimpleFormat::tokenise(Line* line)
{
    line->clearTokens();

    LineToken* token = NULL;
    size_t pos;
    int t = 0;
    for (pos = 0; pos < line->text.length(); pos++)
    {

        wchar_t c = line->text.at(pos);
        if (iswspace(c))
        {
            token = new LineToken();
            line->tokens.push_back(token);
            token->column = pos;
            token->isSpace = true;

            while (pos < line->text.length())
            {
                token->text += c;
                if (pos + 1 >= line->text.length())
                {
                    break;
                }

                c = line->text.at(pos + 1);
                if (!iswspace(c))
                {
                    break;
                }

                pos++;
            }

            token = NULL;
        }
        else
        {
            if (token == NULL)
            {
                token = new LineToken();
                token->colour = g_colours[t % (sizeof(g_colours) / sizeof(uint32_t))];
                token->column = pos;
                line->tokens.push_back(token);
                t++;
            }

            token->text += c;
        }
    }

    if (line->tokens.empty())
    {
        // No tokens for this line. Add an empty one
        token = new LineToken();
        token->isSpace = true;
        line->tokens.push_back(token);
    }

    return true;
}

