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


#include "editor.h"
#include "vide.h"
#include "interfaces/vi/vi.h"

#include <wctype.h>

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;

Editor::Editor(Buffer* buffer, FileTypeManager* ftm) : Logger("Editor")
{
    m_buffer = buffer;
    m_fileTypeManager = ftm;

    m_cursor.line = 0;
    m_cursor.column = 0;
}

Editor::~Editor()
{
}

bool Editor::save()
{
    return m_buffer->save();
}

void Editor::setBuffer(Buffer* buffer)
{
    m_buffer = buffer;

    m_fileTypeManager->tokenise(m_buffer);

#if 0
    m_interface->updateStatus();

#endif
    setDirty();
}

Position Editor::findPrevWord()
{
    return findPrevWord(m_cursor);
}

Position Editor::findPrevWord(Position from)
{
    Line* line = m_buffer->getLine(from.line);
    if (from.column >= line->text.length())
    {
        from.column = line->text.length() - 1;
    }

    vector<LineToken*>::iterator it;
    it = line->tokenAt(from.column, false);

    bool prevLine = false;
    if (it != line->tokens.begin() && (it - 1) != line->tokens.begin())
    {
        LineToken* curToken = *it;
        log(DEBUG, "CURRENT TOKEN: %ls", curToken->text.c_str());

        if (curToken->column < from.column)
        {
            return Position(from.line, curToken->column);
        }

        do
        {
            it--;
        }
        while (it != line->tokens.begin() && (*it)->isSpace);

        if (it != line->tokens.begin())
        {
            LineToken* nextToken = *it;

            log(DEBUG, "PREV TOKEN: %ls", nextToken->text.c_str());
            return Position(from.line, nextToken->column);
        }
        else
        {
            prevLine = true;
        }
    }
    else
    {
        prevLine = true;
    }

    if (prevLine)
    {
        log(DEBUG, "START OF LINE");
        if (from.line > 0)
        {
            Line* prevLine = m_buffer->getLine(from.line - 1);
            return findPrevWord(Position(from.line - 1, prevLine->text.length() - 1));
        }
        else
        {
            log(DEBUG, "RETURNING START OF FILE");

            return Position(0, 0);
        }
    }

    return Position(0, 0);
}

Position Editor::findNextWord()
{
    return findNextWord(m_cursor);
}

Position Editor::findNextWord(Position from)
{
    Line* line = m_buffer->getLine(from.line);

    vector<LineToken*>::iterator it;
    it = line->tokenAt(from.column, false);

    bool nextLine = false;
    if (it != line->tokens.end() && (it + 1) != line->tokens.end())
    {
        LineToken* curToken = *it;
        log(DEBUG, "CURRENT TOKEN: %ls", curToken->text.c_str());

        do
        {
            it++;
        }
        while (it != line->tokens.end() && (*it)->isSpace);

        if (it != line->tokens.end())
        {
            LineToken* nextToken = *it;

            log(DEBUG, "NEXT TOKEN: %ls", nextToken->text.c_str());
            return Position(from.line, nextToken->column);
        }
        else
        {
            nextLine = true;
        }
    }
    else
    {
        nextLine = true;
    }

    if (nextLine)
    {
        log(DEBUG, "END OF LINE");
        if (from.line < m_buffer->getLineCount() - 1)
        {
            Line* nextLine = m_buffer->getLine(from.line + 1);
            if (!nextLine->tokens.empty() && !nextLine->tokens.at(0)->isSpace)
            {
                return Position(from.line + 1, 0);
            }
            return findNextWord(Position(from.line + 1, 0));
        }
        else
        {
            log(DEBUG, "RETURNING END OF FILE");

            return Position(from.line, line->text.length() - 1);
        }
    }

    return Position();
}

wchar_t Editor::getCharAtCursor()
{
    Line* line = m_buffer->getLine(m_cursor.line);
    if (line == NULL)
    {
        return 0;
    }

    if (m_cursor.column >= 0 && m_cursor.column < line->text.length())
    {
        return line->text.at(m_cursor.column);
    }
    else
    {
        return 0;
    }
}

void Editor::moveCursor(Position pos)
{
    moveCursorY(pos.line);
    moveCursorX(pos.column);
}

void Editor::moveCursorX(unsigned int x, bool allowXOver)
{
    if (m_cursor.column == x)
    {
        return;
    }

    if ((int)x <= 0)
    {
        // Also handle 0 here to avoid line length lookup
        x = 0;
    }
    else
    {
        unsigned int width = m_buffer->getLineLength(m_cursor.line);
        if (!allowXOver && x >= width)
        {
            x = width - 1;
        }
        else if (allowXOver && x > width)
        {
            x = width;
        }
    }

    if (m_cursor.column != x)
    {
        m_cursor.column = x;

        setDirty();
        m_cursorMovedSignal.emit();
    }
}

void Editor::moveCursorY(unsigned int y)
{
    if (m_cursor.line == y)
    {
        return;
    }

    if ((int)y <= 0)
    {
        y = 0;
    }
    else if (y >= m_buffer->getLineCount())
    {
        y = m_buffer->getLineCount() - 1;
    }

    if (m_cursor.line != y)
    {
        m_cursor.line = y;

#if 0
        unsigned int scrollPos = m_scrollBar->getPos();
        if (m_cursor.line < scrollPos)
        {
            m_scrollBar->setPos(m_cursor.line);
        }
        else
        {
            int viewLines = getViewLines();
            if (m_cursor.line >= (scrollPos + viewLines))
            {
                m_scrollBar->setPos(m_cursor.line - (viewLines - 1));
            }
        }

#endif
        setDirty();
        m_cursorMovedSignal.emit();
    }
}

void Editor::moveCursorDelta(int dx, int dy, bool allowXOver)
{
    // Move Y first as X depends on line width
    if (dy != 0)
    {
        moveCursorY(m_cursor.line + dy);
    }

    if (dx != 0)
    {
        moveCursorX(m_cursor.column + dx, allowXOver);
    }
    log(DEBUG, "moveCursorDelta: m_cursorX=%d, moveCursorY=%d", m_cursor.column, m_cursor.line);
}

void Editor::moveCursorXEnd()
{
    int width = m_buffer->getLineLength(m_cursor.line);
    m_cursor.column = width - 1;

    setDirty();
}

void Editor::moveCursorYEnd()
{
    moveCursor(Position(m_buffer->getLineCount() - 1, 0));

    setDirty();
}

void Editor::moveCursorPage(int dir)
{
#if 0
    int viewLines = getViewLines();

    moveCursorDelta(0, viewLines * dir);
#endif
}

void Editor::executeEdits(std::vector<Edit> edits)
{
    for (Edit edit : edits)
    {
        executeEdit(edit);
    }

    setDirty();
}

void Editor::executeEdit(Edit edit)
{
    Line* line = m_buffer->getLine(edit.position.line);

    switch (edit.editType)
    {
        case EDIT_INSERT:
        {
            unsigned int i;
            for (i = 0; i < edit.text.length(); i++)
            {
                line->text.insert(edit.position.column + i, 1, edit.text.at(i));
            }
            m_buffer->setDirtyLine(line);
        } break;

        case EDIT_NEW_LINE:
        {
            Line* newLine = new Line();
            newLine->lineEnding = "\n";

            m_buffer->insertLine(edit.position.line + 1, newLine);
        } break;

        case EDIT_SPLIT_LINE:
        {
            doSplitLine(edit.position, line);
        } break;

        case EDIT_JOIN_LINES:
        {
             doJoinLines(edit.position.line, line);
        } break;

        case EDIT_DELETE_CHAR:
            line->text.erase(edit.position.column, 1);
            m_buffer->setDirtyLine(line);
            break;

        case EDIT_DELETE_LINE:
            m_buffer->deleteLine(edit.position.line);
            break;

        case EDIT_DELETE_TO_END:
            line->text.erase(edit.position.column);
            m_buffer->setDirtyLine(line);
            break;
    }
}

void Editor::undoEdits(std::vector<Edit> edits)
{
    vector<Edit>::reverse_iterator rit;
    log(DEBUG, "undoEdits: Undoing %lu edits", edits.size());
    for (rit = edits.rbegin(); rit != edits.rend(); rit++)
    {
        Edit edit = *rit;
        undoEdit(edit);
    }

    setDirty();
}

void Editor::undoEdit(Edit edit)
{
    Line* line = m_buffer->getLine(edit.position.line);

    switch (edit.editType)
    {
        case EDIT_INSERT:
            log(DEBUG, "undoEdit: EDIT_INSERT: %lu chars", edit.text.length());
            line->text.erase(edit.position.column, edit.text.length());
            m_buffer->setDirtyLine(line);
            break;

        case EDIT_NEW_LINE:
            m_buffer->deleteLine(edit.position.line + 1);
            log(DEBUG, "undoEdit: EDIT_NEW_LINE");
            break;

        case EDIT_SPLIT_LINE:
        {
            log(DEBUG, "undoEdit: EDIT_SPLIT_LINE");

            doJoinLines(edit.position.line, line);
        } break;

        case EDIT_JOIN_LINES:
            log(DEBUG, "undoEdit: EDIT_JOIN_LINES");
            doSplitLine(edit.position, line);
            break;

        case EDIT_DELETE_CHAR:
            log(DEBUG, "undoEdit: EDIT_DELETE_CHAR");
            line->text.insert(edit.position.column, 1, edit.text.at(0));
            m_buffer->setDirtyLine(line);
            break;

        case EDIT_DELETE_LINE:
        {
            log(DEBUG, "undoEdit: EDIT_DELETE_LINE");

            Line* newLine = new Line();
            newLine->lineEnding = "\n";
            newLine->text = edit.text;
            m_buffer->insertLine(edit.position.line, newLine);

            m_buffer->setDirtyLine(line);
        } break;

        case EDIT_DELETE_TO_END:
            log(DEBUG, "undoEdit: EDIT_DELETE_TO_END: %ls", edit.text.c_str());
            line->text += edit.text;
            m_buffer->setDirtyLine(line);
            break;
    }
}

void Editor::doJoinLines(unsigned int line, Line* line1)
{
    Line* line2 = m_buffer->getLine(line + 1);

    line1->text += line2->text;
    m_buffer->deleteLine(line + 1);
    m_buffer->setDirtyLine(line1);
}

void Editor::doSplitLine(Position position, Line* line)
{
    wstring text1 = line->text.substr(0, position.column);
    wstring text2 = line->text.substr(position.column);

    line->text = text1;

    Line* newLine = new Line();
    newLine->lineEnding = line->lineEnding;
    newLine->text = text2;

    m_buffer->insertLine(position.line + 1, newLine);
    m_buffer->setDirtyLine(line);
    m_buffer->setDirtyLine(newLine);
}

vector<Edit> Editor::insert(wchar_t c)
{
    Line* line = m_buffer->getLine(m_cursor.line);

    unsigned int textLen = line->text.length();
    if (m_cursor.column > textLen)
    {
        if (textLen > 0)
        {
            m_cursor.column = textLen;
        }
        else
        {
            m_cursor.column = 0;
        }
    }
    log(DEBUG, "insert: m_cursorX=%u, textLen=%u", m_cursor.column, textLen);

    vector<Edit> edits;
    edits.push_back(Edit(m_cursor, EDIT_INSERT, c));

    executeEdits(edits);

    return edits;
}

vector<Edit> Editor::insertLine()
{
    vector<Edit> edits;
    edits.push_back(Edit(m_cursor, EDIT_NEW_LINE));

    executeEdits(edits);

    return edits;
}

vector<Edit> Editor::splitLine()
{
    vector<Edit> edits;
    edits.push_back(Edit(m_cursor, EDIT_SPLIT_LINE));

    executeEdits(edits);

    return edits;
}

vector<Edit> Editor::joinLines()
{
    vector<Edit> edits;

    unsigned int count = m_buffer->getLineCount();

    if (m_cursor.line >= count - 1)
    {
        return edits;
    }

    edits.push_back(Edit(m_cursor, EDIT_JOIN_LINES));

    executeEdits(edits);

    return edits;
}

vector<Edit> Editor::deleteAtCursor()
{
    vector<Edit> edits;

    Line* line = m_buffer->getLine(m_cursor.line);
    edits.push_back(Edit(m_cursor, EDIT_DELETE_CHAR, line->text.at(m_cursor.column)));

    executeEdits(edits);

    return edits;
}

vector<Edit> Editor::deleteLine()
{
    vector<Edit> edits;

    Line* line = m_buffer->getLine(m_cursor.line);
    edits.push_back(Edit(m_cursor, EDIT_DELETE_LINE, line->text));

    unsigned int count = m_buffer->getLineCount();
    if (count == 1)
    {
        edits.push_back(Edit(m_cursor, EDIT_NEW_LINE));
    }

    executeEdits(edits);

    if (m_cursor.line >= m_buffer->getLineCount())
    {
        m_cursor.line = m_buffer->getLineCount() - 1;
    }

    return edits;
}

vector<Edit> Editor::deleteToEnd()
{
    vector<Edit> edits;

    Line* line = m_buffer->getLine(m_cursor.line);
    wstring text = line->text.substr(m_cursor.column);
    edits.push_back(Edit(m_cursor, EDIT_DELETE_TO_END, text));

    executeEdits(edits);

    return edits;
}

void Editor::copyToBuffer(int count)
{
    vector<wstring> copyVec;

    int i;
    for (i = 0; i < count; i++)
    {
        Line* line = m_buffer->getLine(m_cursor.line + i);
        if (line != NULL)
        {
            log(DEBUG, "copyToBuffer: Copying: %ls", line->text.c_str());
            copyVec.push_back(line->text);
        }
    }
#if 0
    m_vide->setBuffer(copyVec);
#endif

}

vector<Edit> Editor::pasteFromBuffer()
{
    vector<Edit> edits;

#if 0
    vector<wstring> copyVec = m_vide->getBuffer();

    for (wstring text : copyVec)
    {
        m_cursor.column = 0;
        edits.push_back(Edit(m_cursor, EDIT_NEW_LINE));
        m_cursor.line++;
        edits.push_back(Edit(m_cursor, EDIT_INSERT, text));
    }

    executeEdits(edits);
#endif

    return edits;
}

