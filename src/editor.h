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
#include "format.h"

#include <frontier/widgets.h>

class Vide;

class Editor : public Frontier::Widget
{
 private:
    Vide* m_vide;

    int m_marginX;
    unsigned int m_cursorX;
    unsigned int m_cursorY;

    Frontier::ScrollBar* m_scrollBar;

    Buffer* m_buffer;
    Interface* m_interface;
    Format* m_format;

    unsigned int getViewLines();

 public:

    Editor(Vide* window);
    virtual ~Editor();

    virtual void calculateSize();
    virtual void layout();

    virtual bool draw(Geek::Gfx::Surface* surface);

    virtual Widget* handleMessage(Frontier::Message* msg);
    void onScrollbarChanged(int pos);

    void setBuffer(Buffer* buffer);
    Buffer* getBuffer() { return m_buffer; }

    unsigned int getCursorX() { return m_cursorX; }
    unsigned int getCursorY() { return m_cursorY; }

    void moveCursorX(unsigned int x);
    void moveCursorY(unsigned int y);
    void moveCursorDelta(int dx, int dy);
    void moveCursorXEnd();
    void moveCursorNextToken();
    void moveCursorPage(int dir);

    void insert(wchar_t c);
    void deleteAtCursor();

    void setInterfaceStatus(std::wstring message);
};

#endif
