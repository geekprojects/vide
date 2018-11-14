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

#ifndef __VIDE_UI_VIEWS_EDITOR_VIEW_H_
#define __VIDE_UI_VIEWS_EDITOR_VIEW_H_

#include "buffer.h"
#include "editor.h"
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

class EditorView : public Frontier::Widget
{
 private:
    Vide* m_vide;
    Editor* m_editor;
    Interface* m_interface;

    int m_marginX;
    CursorType m_cursorType;

    Frontier::ScrollBar* m_scrollBar;
    EditorTipWindow* m_tipWindow;

    std::map<TokenType, uint32_t> m_colours;

    unsigned int getViewLines();

    void drawCursor();

 public:
    EditorView(Vide* window, Editor* editor);
    virtual ~EditorView();

    Editor* getEditor() { return m_editor; }

    virtual void calculateSize();
    virtual void layout();

    virtual bool draw(Geek::Gfx::Surface* surface);

    virtual Widget* handleMessage(Frontier::Message* msg);
    void onScrollbarChanged(int pos);
    void onMouseLeave();

    CursorType getCursorType() { return m_cursorType; }
    void setCursorType(CursorType type) { m_cursorType = type; }

    void setInterfaceStatus(std::wstring message);

    virtual Frontier::WindowCursor getCursor() { return Frontier::CURSOR_EDIT; }
};

#endif

