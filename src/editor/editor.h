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

#ifndef __VIDE_EDITOR_H_
#define __VIDE_EDITOR_H_

#include "buffer.h"
#include "filetypes/filetypemanager.h"

#include <geek/core-logger.h>
#include <sigc++/sigc++.h>

class Vide;
class FileTypeManager;

enum EditType
{
    EDIT_INSERT,
    EDIT_NEW_LINE,
    EDIT_SPLIT_LINE,
    EDIT_JOIN_LINES,
    EDIT_DELETE_CHAR,
    EDIT_DELETE_LINE,
    EDIT_DELETE_TO_END,
    EDIT_REPLACE,
};

struct Edit
{
    Position position;
    EditType editType;
    std::wstring prevText;
    std::wstring newText;

    Edit() {}
    Edit(Position _pos, EditType _editType)
    {
        position = _pos;
        editType = _editType;
        prevText = L"";
        newText = L"";
    }

    Edit(Position _pos, EditType _editType, wchar_t _prevChr, wchar_t _newChr)
    {
        position = _pos;
        editType = _editType;
        if (_prevChr != 0)
        {
            prevText = std::wstring(L"") + _prevChr;
        }
        else
        {
            prevText = L"";
        }
        if (_newChr != 0)
        {
            newText = std::wstring(L"") + _newChr;
        }
        else
        {
            newText = L"";
        }
    }

    Edit(Position _pos, EditType _editType, std::wstring _prevText, std::wstring _newText)
    {
        position = _pos;
        editType = _editType;
        prevText = _prevText;
        newText = _newText;
    }
};

class Editor : public Geek::Logger
{
 private:
    Vide* m_vide;

    Position m_cursor;
    bool m_dirty;

    Position m_selectStart;
    Position m_selectEnd;

    Buffer* m_buffer;

    FileTypeManager* m_fileTypeManager;

    sigc::signal<void> m_cursorMovedSignal;
    sigc::signal<void> m_editedSignal;

    void executeEdit(Edit edit);

    void doJoinLines(unsigned int line, Line* line1);
    void doSplitLine(Position pos, Line* line);


 public:
    Editor(Vide* vide, Buffer* buffer, FileTypeManager* ftm);
    virtual ~Editor();

    bool save();

    void setBuffer(Buffer* buffer);
    Buffer* getBuffer() { return m_buffer; }
    FileTypeManager* getFileTypeManager() { return m_fileTypeManager; }

    Position getCursorPosition() { return m_cursor; }
    unsigned int getCursorX() { return m_cursor.column; }
    unsigned int getCursorY() { return m_cursor.line; }
    bool isDirty() { return m_dirty; }
    void setDirty() { m_dirty = true; }
    void clearDirty() { m_dirty = false; }

    Position getSelectStart() { return m_selectStart; }
    Position getSelectEnd() { return m_selectEnd; }
    void setSelectStart(Position pos) { m_selectStart = pos; }
    void setSelectEnd(Position pos) { m_selectEnd = pos; }
    void clearSelection() { m_selectStart.line = -1; m_selectEnd.line = -1; }
    bool hasSelection()
    {
        return ((int)m_selectStart.line != -1 && m_selectStart != m_selectEnd);
    }

    Position findPrevWord();
    Position findPrevWord(Position from);
    Position findNextWord();
    Position findNextWord(Position from);
    wchar_t getCharAtCursor();

    void moveCursor(Position pos);
    void moveCursorX(unsigned int x, bool allowXOver = false);
    void moveCursorY(unsigned int y);
    void moveCursorDelta(int dx, int dy, bool allowXOver = false);
    void moveCursorXEnd();
    void moveCursorYEnd();
    void moveCursorNextToken();
    void moveCursorPage(int dir);

    void searchNext(std::wstring pattern);
    void searchPrev(std::wstring pattern);

    void executeEdits(std::vector<Edit> edits);
    void undoEdits(std::vector<Edit> edits);
    void undoEdit(Edit edit);

    std::vector<Edit> insert(wchar_t c);
    std::vector<Edit> insertLine();
    std::vector<Edit> splitLine();
    std::vector<Edit> joinLines();
    std::vector<Edit> deleteAtCursor();
    std::vector<Edit> deleteLine();
    std::vector<Edit> deleteToEnd();
    std::vector<Edit> replaceChar(wchar_t c);

    void copyToBuffer(int count);
    std::vector<Edit>  pasteFromBuffer();

    sigc::signal<void> cursorMovedSignal() { return m_cursorMovedSignal; }
    sigc::signal<void> editedSignal() { return m_editedSignal; }
};

#endif

