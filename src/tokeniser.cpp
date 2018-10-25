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

#include "tokeniser.h"
#include "buffer.h"

#include <wctype.h>

using namespace std;

Tokeniser::Tokeniser()
{
}

Tokeniser::~Tokeniser()
{
}


bool Tokeniser::tokenise(Buffer* buffer)
{
    vector<Line*>::iterator lineIt;

    for (lineIt = buffer->getLines().begin(); lineIt != buffer->getLines().end(); lineIt++)
    {
        bool res;
        res = tokenise(buffer, *lineIt);
        if (!res)
        {
            return false;
        }
    }

    return true;
}

bool Tokeniser::tokenise(Buffer* buffer, Line* line)
{
    return true;
}

SimpleTokeniser::SimpleTokeniser()
{
}

SimpleTokeniser::~SimpleTokeniser()
{
}

bool SimpleTokeniser::tokenise(Buffer* buffer, Line* line)
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
                token->type = TOKEN_TEXT;
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
        token->type = TOKEN_TEXT;
        line->tokens.push_back(token);
    }

    return true;
}

