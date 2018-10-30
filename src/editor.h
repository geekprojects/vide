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
#include "interfaces/interface.h"
#include "filetypes/filetypemanager.h"

#include <frontier/widgets/scrollbar.h>

class Vide;
class EditorTipWindow;

enum CursorType
{
    CURSOR_BLOCK,
    CURSOR_BAR,
};

enum EditType
{
    EDIT_INSERT,
    EDIT_NEW_LINE,
    EDIT_SPLIT_LINE,
    EDIT_JOIN_LINES,
    EDIT_DELETE_CHAR,
    EDIT_DELETE_LINE,
    EDIT_DELETE_TO_END,
};

struct Edit
{
    Position position;
    EditType editType;
    std::wstring text;

    Edit() {}
    Edit(Position _pos, EditType _editType)
    {
        position = _pos;
        editType = _editType;
    }
    Edit(Position _pos, EditType _editType, wchar_t _chr)
    {
        position = _pos;
        editType = _editType;
        text = std::wstring(L"") + _chr;
    }
    Edit(Position _pos, EditType _editType, std::wstring _text)
    {
        position = _pos;
        editType = _editType;
        text = _text;
    }
};

class Editor : public Frontier::Widget
{
 private:
    Vide* m_vide;

    int m_marginX;
    Position m_cursor;
    CursorType m_cursorType;

    Frontier::ScrollBar* m_scrollBar;

    Buffer* m_buffer;
    Interface* m_interface;
    FileTypeManager* m_fileTypeManager;

    EditorTipWindow* m_tipWindow;

    std::map<TokenType, uint32_t> m_colours;

    unsigned int getViewLines();

    void drawCursor();

    void doJoinLines(unsigned int line, Line* line1);
    void doSplitLine(Position pos, Line* line);

 public:

    Editor(Vide* window, Buffer* buffer, FileTypeManager* ftm);
    virtual ~Editor();

    virtual void calculateSize();
    virtual void layout();

    virtual bool draw(Geek::Gfx::Surface* surface);

    bool save();

    virtual Widget* handleMessage(Frontier::Message* msg);
    void onScrollbarChanged(int pos);
    void onMouseLeave();

    void setBuffer(Buffer* buffer);
    Buffer* getBuffer() { return m_buffer; }

    Position getCursor() { return m_cursor; }
    unsigned int getCursorX() { return m_cursor.column; }
    unsigned int getCursorY() { return m_cursor.line; }

    CursorType getCursorType() { return m_cursorType; }
    void setCursorType(CursorType type) { m_cursorType = type; }

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

    void executeEdits(std::vector<Edit> edits);
    void executeEdit(Edit edit);
    void undoEdits(std::vector<Edit> edits);
    void undoEdit(Edit edit);

    std::vector<Edit> insert(wchar_t c);
    std::vector<Edit> insertLine();
    std::vector<Edit> splitLine();
    std::vector<Edit> joinLines();
    std::vector<Edit> deleteAtCursor();
    std::vector<Edit> deleteLine();
    std::vector<Edit> deleteToEnd();

    void copyToBuffer(int count);
    std::vector<Edit>  pasteFromBuffer();

    void setInterfaceStatus(std::wstring message);
};

#endif

