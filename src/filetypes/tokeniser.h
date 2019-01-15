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

#ifndef __VIDE_FORMAT_H_
#define __VIDE_FORMAT_H_

#include <geek/core-logger.h>

class Buffer;
struct Line;

enum TokenType
{
    TOKEN_TEXT,
    TOKEN_COMMENT,
    TOKEN_KEYWORD,
    TOKEN_TYPE_REF,
    TOKEN_IDENTIFIER,
    TOKEN_LOCAL_VARIABLE,
    TOKEN_PARAM_VARIABLE,
    TOKEN_ACCESS_SPECIFIER,
    TOKEN_FUNCTION,
    TOKEN_PREPROCESSOR,
    TOKEN_LITERAL,
    TOKEN_STRING,
};

class Tokeniser : public Geek::Logger
{
 protected:

 public:
    Tokeniser();
    virtual ~Tokeniser();

    virtual bool tokenise(Buffer* buffer);
    virtual bool tokenise(Buffer* buffer, Line* line);
};

class SimpleTokeniser : public Tokeniser
{
 protected:

 public:
    SimpleTokeniser();
    virtual ~SimpleTokeniser();

    virtual bool tokenise(Buffer* buffer, Line* line);
};

#endif
