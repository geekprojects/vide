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

#include <vide/editor.h>
#include "views/view.h"
#include "videapp.h"

#include <frontier/widgets/scrollbar.h>

class VideApp;
class EditorTipWindow;
class Interface;
class Editor;

struct EditorCharacter
{
    Position position;
    LineToken* token;
};

class EditorCharacterMap
{
 private:
    int m_lines;
    int m_columns;
    EditorCharacter* m_map;

    EditorCharacter* get(int line, int column);

 public:
    EditorCharacterMap();
    ~EditorCharacterMap();

    void reset(int lines, int columns);
    void setToken(int line, int column, int width, LineToken* token, Position bufferPos);
    LineToken* getToken(int line, int column);
    Position getPosition(int line, int column);
};

class EditorView : public Frontier::Widget, public View
{
 private:
    VideApp* m_vide;
    Editor* m_editor;
    // XXX Interface* m_interface;
    EditorCharacterMap* m_characterMap;

    Geek::Core::Timer* m_indexTimer;
    uint64_t m_tokeniseTime;

    int m_marginX;
    Frontier::Size m_charSize;

    bool m_selecting;

    Frontier::ScrollBar* m_scrollBar;

    std::map<TokenType, uint32_t> m_colours;
    uint32_t m_defaultColour;

    unsigned int getViewLines();

    void drawCursor(Geek::Gfx::Surface* surface, int x, int y);

    void onCursorMoved();
    void onScrollbarChanged(int pos);
    void onMouseLeave();
    void onEdit();
    void indexTimer(Geek::Core::Timer*);
    void tokeniseComplete(Geek::Core::Task* task);

 public:
    EditorView(VideApp* vide, Editor* editor);
    virtual ~EditorView();

    Editor* getEditor() { return m_editor; }

    virtual void calculateSize();
    virtual void layout();

    virtual bool draw(Geek::Gfx::Surface* surface);

    virtual Widget* handleEvent(Frontier::Event* event);

    void updateStatus();

    virtual Frontier::WindowCursor getCursor() { return Frontier::CURSOR_EDIT; }
};

#endif

