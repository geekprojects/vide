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


#include <vide/editor.h>
#include <vide/vide.h>
//#include "interfaces/vi/vi.h"
#include <vide/re.h>

#include <wctype.h>

#include <geek/core-tasks.h>

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;
using namespace Geek::Core;

Editor::Editor(Vide* vide, Buffer* buffer, FileTypeManager* ftm) : Logger("Editor")
{
    m_vide = vide;
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

    //m_fileTypeManager->tokenise(m_buffer);

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

    // Find starting token
    TokenAt at;
    at = line->tokenAt(from.column, false);

    vector<LineToken*>::iterator it = at.it;
    int lineNum = from.line;
    int column = at.tokenColumn;
    while (true)
    {
        if (it == line->tokens.begin())
        {
            // Beginning of a line!
            if (lineNum == 0)
            {
                // Beginning of the buffer!
                return Position(0, 0);
            }

            lineNum--;
            line = m_buffer->getLine(lineNum);
            column = line->text.length();
            it = line->tokens.end();

            continue;
        }

        // Get previous token
        it--;
        LineToken* token = (*it);
        column -= token->text.length(); 
        if (!token->isSpace)
        {
            return Position(lineNum, column);
        }
    }
}

Position Editor::findNextWord()
{
    return findNextWord(m_cursor);
}

Position Editor::findNextWord(Position from)
{
    Line* line = m_buffer->getLine(from.line);

    TokenAt at;
    at = line->tokenAt(from.column, false);

    bool nextLine = false;
    if (at.it != line->tokens.end() && (at.it + 1) != line->tokens.end())
    {
        LineToken* curToken = *(at.it);
        log(DEBUG, "CURRENT TOKEN: %ls", curToken->text.c_str());

        do
        {
at.tokenColumn += (*(at.it))->text.length();
            at.it++;
        }
        while (at.it != line->tokens.end() && (*(at.it))->isSpace);

        if (at.it != line->tokens.end())
        {
            LineToken* nextToken = *at.it;

            log(DEBUG, "NEXT TOKEN: %ls", nextToken->text.c_str());
            return Position(from.line, at.tokenColumn);
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
    int viewLines = getViewLines();

    moveCursorDelta(0, viewLines * dir);
}

bool Editor::isCursorAtEndOfLine()
{
    unsigned int width = m_buffer->getLineLength(m_cursor.line);
    return (m_cursor.column >= width);
}

void Editor::searchNext(wstring pattern)
{
    RegularExpression re;
    bool res;

    printf("Editor::searchNext: Position: line=%u, col=%u\n", m_cursor.line, m_cursor.column);

    res = re.compile(pattern);
    if (!res)
    {
        printf("Editor::searchNext: Invalid pattern!\n");
        return;
    }

    unsigned int lineNum = m_cursor.line;
    bool found = false;
    while (true)
    {
        printf("Editor::searchNext: lineNum=%u\n", lineNum);

        Line* line = m_buffer->getLine(lineNum);

        vector<Match> matches = re.match(line->text);
        for (Match match : matches)
        {
            printf("Editor::searchNext: Match: column=%d\n", match.start);
            if (lineNum != m_cursor.line || match.start > (int)m_cursor.column)
            {
                printf("Editor::searchNext: Found at: line=%d, col=%d\n", lineNum, match.start);
                m_cursor.line = lineNum;
                m_cursor.column = match.start;

                setDirty();
                found = true;
                break;
            }
        }
        if (found)
        {
            break;
        }

        lineNum++;
        if (lineNum >= m_buffer->getLineCount())
        {
            lineNum = 0;
        }

        if (lineNum == m_cursor.line)
        {
            break;
        }
    }
}

void Editor::searchPrev(wstring pattern)
{
    RegularExpression re;
    bool res;

    printf("Editor::searchPrev: Position: line=%u, col=%u\n", m_cursor.line, m_cursor.column);

    res = re.compile(pattern);
    if (!res)
    {
        printf("Editor::searchPrev: Invalid pattern!\n");
        return;
    }

    unsigned int lineNum = m_cursor.line;
    bool found = false;
    while (true)
    {
        Line* line = m_buffer->getLine(lineNum);

        vector<Match> matches = re.match(line->text);
        int column = 0;
        for (Match match : matches)
        {
            printf("Editor::searchPrev: Match: column=%d\n", match.start);
            if (lineNum != m_cursor.line || match.start < (int)m_cursor.column)
            {
                column = match.start;
                printf("Editor::searchPrev: Found at: line=%d, col=%d\n", lineNum, match.start);
                found = true;
                break;
            }
        }

        if (found)
        {
            m_cursor.line = lineNum;
            m_cursor.column = column;

            setDirty();
            break;
        }

        lineNum--;
        if (lineNum < 0)
        {
            lineNum = m_buffer->getLineCount() - 1;
        }

        if (lineNum == m_cursor.line)
        {
            break;
        }
    }
}


void Editor::executeEdits(vector<Edit> edits)
{
    m_buffer->lock();
    for (Edit edit : edits)
    {
        executeEdit(edit);
    }
    m_buffer->unlock();

    m_editedSignal.emit();
    setDirty();
}

void Editor::executeEdit(Edit edit)
{
    Line* line = m_buffer->getLine(edit.position.line);

    TokenAt at = m_buffer->getToken(edit.position);
    unsigned int tokenPos = 0;
    if (at.token != NULL)
    {
        tokenPos = edit.position.column - at.tokenColumn;
        log(DEBUG, "executeEdit: column=%u, tokenColumn=%u", edit.position.column, tokenPos);
    }

    switch (edit.editType)
    {
        case EDIT_INSERT:
        {
            unsigned int i;
            for (i = 0; i < edit.newText.length(); i++)
            {
                line->text.insert(edit.position.column + i, 1, edit.newText.at(i));
                if (at.token != NULL)
                {
                    at.token->text.insert(tokenPos, 1, edit.newText.at(i));
                }
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
                if (at.token != NULL)
                {
                    at.token->text.erase(tokenPos, 1);
                }
            m_buffer->setDirtyLine(line);
            break;

        case EDIT_DELETE_LINE:
            m_buffer->deleteLine(edit.position.line);
            break;

        case EDIT_DELETE_TO_END:
            line->text.erase(edit.position.column);
            m_buffer->setDirtyLine(line);
            break;

        case EDIT_REPLACE:
            line->text.replace(edit.position.column, edit.newText.length(), edit.newText);
            m_buffer->setDirtyLine(line);
            break;
    }

}

void Editor::undoEdits(vector<Edit> edits)
{
    vector<Edit>::reverse_iterator rit;
    log(DEBUG, "undoEdits: Undoing %lu edits", edits.size());
    for (rit = edits.rbegin(); rit != edits.rend(); rit++)
    {
        Edit edit = *rit;
        undoEdit(edit);
    }

    m_editedSignal.emit();
    setDirty();
}

void Editor::undoEdit(Edit edit)
{
    Line* line = m_buffer->getLine(edit.position.line);

    switch (edit.editType)
    {
        case EDIT_INSERT:
            log(DEBUG, "undoEdit: EDIT_INSERT: %lu chars", edit.newText.length());
            line->text.erase(edit.position.column, edit.newText.length());
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
            line->text.insert(edit.position.column, 1, edit.prevText.at(0));
            m_buffer->setDirtyLine(line);
            break;

        case EDIT_DELETE_LINE:
        {
            log(DEBUG, "undoEdit: EDIT_DELETE_LINE");

            Line* newLine = new Line();
            newLine->lineEnding = "\n";
            newLine->text = edit.prevText;
            m_buffer->insertLine(edit.position.line, newLine);

            m_buffer->setDirtyLine(line);
        } break;

        case EDIT_DELETE_TO_END:
            log(DEBUG, "undoEdit: EDIT_DELETE_TO_END: %ls", edit.prevText.c_str());
            line->text += edit.prevText;
            m_buffer->setDirtyLine(line);
            break;

        case EDIT_REPLACE:
            line->text.replace(edit.position.column, edit.prevText.length(), edit.prevText);
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
    edits.push_back(Edit(m_cursor, EDIT_INSERT, 0, c));

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

    if (m_cursor.column >= line->text.length())
    {
        return edits;
    }

    edits.push_back(Edit(m_cursor, EDIT_DELETE_CHAR, line->text.at(m_cursor.column), 0));

    executeEdits(edits);

    if (m_cursor.column >= line->text.length() && m_cursor.column > 0)
    {
        m_cursor.column--;
    }

    return edits;
}

vector<Edit> Editor::deleteLine()
{
    vector<Edit> edits;

    Line* line = m_buffer->getLine(m_cursor.line);
    edits.push_back(Edit(m_cursor, EDIT_DELETE_LINE, line->text, L""));

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
    edits.push_back(Edit(m_cursor, EDIT_DELETE_TO_END, text, L""));

    executeEdits(edits);

    return edits;
}

vector<Edit> Editor::replaceChar(wchar_t c)
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
    log(DEBUG, "replaceChar: m_cursorX=%u, textLen=%u", m_cursor.column, textLen);

    vector<Edit> edits;
    edits.push_back(Edit(m_cursor, EDIT_REPLACE, line->text.at(m_cursor.column), c));

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

    m_vide->setBuffer(copyVec);
}

vector<Edit> Editor::pasteFromBuffer()
{
    vector<Edit> edits;

    vector<wstring> copyVec = m_vide->getBuffer();

    for (wstring text : copyVec)
    {
        m_cursor.column = 0;
        edits.push_back(Edit(m_cursor, EDIT_NEW_LINE));
        m_cursor.line++;
        edits.push_back(Edit(m_cursor, EDIT_INSERT, L"", text));
    }

    executeEdits(edits);

    return edits;
}

