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
#include "editor/buffer.h"

#include <wctype.h>

using namespace std;

Tokeniser::Tokeniser() : Logger("Tokeniser")
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
        Line* line = *lineIt;
        if (line->dirty)
        {
            bool res;
            res = tokenise(buffer, line);
            if (!res)
            {
                return false;
            }
        }
    }
    buffer->clearDirty();

    return true;
}

bool Tokeniser::tokenise(Buffer* buffer, Line* line)
{
    line->dirty = false;
    return true;
}

vector<LineToken*> Tokeniser::splitText(TokenType type, wstring text)
{
    vector<LineToken*> tokens;

    LineToken* token = NULL;
    size_t pos;
    int t = 0;

    for (pos = 0; pos < text.length(); pos++)
    {

        wchar_t c = text.at(pos);
        if (iswspace(c))
        {
            token = new LineToken();
            tokens.push_back(token);
            token->column = pos;
            token->isSpace = true;
            token->type = type;

            while (pos < text.length())
            {
                token->text += c;
                if (pos + 1 >= text.length())
                {
                    break;
                }

                c = text.at(pos + 1);
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
                token->type = type;
                token->column = pos;
                tokens.push_back(token);
                t++;
            }

            token->text += c;
        }
    }

    if (tokens.empty())
    {
        // No tokens for this line. Add an empty one
        token = new LineToken();
        token->isSpace = true;
        token->type = TOKEN_TEXT;
        tokens.push_back(token);
    }

    return tokens;
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

    line->tokens = splitText(TOKEN_TEXT, line->text);

    line->dirty = false;

    return true;
}

