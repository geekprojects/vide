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
#include "interface.h"
#include "filetypemanager.h"

#include <frontier/widgets/scrollbar.h>

class Vide;
class EditorTipWindow;

enum CursorType
{
    CURSOR_BLOCK,
    CURSOR_BAR,
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

    void insert(wchar_t c);
    void insertLine();
    void splitLine();
    void joinLines();
    void deleteAtCursor();
    void deleteLine();

    void copyToBuffer(int count);
    void pasteFromBuffer();

    void setInterfaceStatus(std::wstring message);
};

#endif

