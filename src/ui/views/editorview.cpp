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


#include "editor/editor.h"
#include "ui/views/editorview.h"
#include "vide.h"
#include "interfaces/vi/vi.h"

#include <wctype.h>

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;

EditorView::EditorView(Vide* vide, Editor* editor) : Widget(vide, L"EditorView")
{
    m_vide = vide;
    m_editor = editor;
    m_editor->cursorMovedSignal().connect(sigc::mem_fun(*this, &EditorView::cursorMoved));

    m_scrollBar = new ScrollBar(vide);
    m_scrollBar->incRefCount();
    m_scrollBar->setParent(this);
    m_scrollBar->changedPositionSignal().connect(sigc::mem_fun(*this, &EditorView::onScrollbarChanged));

    m_interface = new ViInterface(editor);

    m_marginX = 40;

    m_selecting = false;

    m_colours.insert(make_pair(TOKEN_TEXT, 0xF8F8F2));
    m_colours.insert(make_pair(TOKEN_COMMENT, 0x7E8E91));
    m_colours.insert(make_pair(TOKEN_KEYWORD, 0xF92672));
    m_colours.insert(make_pair(TOKEN_IDENTIFIER, 0xFD971F));
    m_colours.insert(make_pair(TOKEN_LOCAL_VARIABLE, 0xef5939));
    m_colours.insert(make_pair(TOKEN_PARAM_VARIABLE, 0x9876AA));
    m_colours.insert(make_pair(TOKEN_ACCESS_SPECIFIER, 0x66D9EF));
    m_colours.insert(make_pair(TOKEN_FUNCTION, 0xA6E22E));
    m_colours.insert(make_pair(TOKEN_PREPROCESSOR, 0xA6E22E));
    m_colours.insert(make_pair(TOKEN_LITERAL, 0xAE81FF));
    m_colours.insert(make_pair(TOKEN_STRING, 0xE6DB74));

    updateStatus();
}

EditorView::~EditorView()
{
    m_scrollBar->decRefCount();
}

void EditorView::calculateSize()
{
    //m_minSize.set(50, 50);
    m_minSize.set(300, 300);
    m_maxSize.set(WIDGET_SIZE_UNLIMITED, WIDGET_SIZE_UNLIMITED);

    m_scrollBar->calculateSize();
}

void EditorView::layout()
{
    m_scrollBar->setPosition(m_setSize.width - m_scrollBar->getMinSize().width, 0);
    m_scrollBar->setSize(Size(m_scrollBar->getMinSize().width, m_setSize.height));
}

bool EditorView::draw(Surface* surface)
{
    Buffer* buffer = m_editor->getBuffer();
    if (buffer->isDirty())
    {
        uint64_t start = m_app->getTimestamp();
        m_editor->getFileTypeManager()->tokenise(buffer);
        uint64_t end = m_app->getTimestamp();
        uint64_t diff = end - start;
        log(DEBUG, "draw: tokenise time=%llu", diff);
    }

    m_editor->clearDirty();

    Position cursor = m_editor->getCursorPosition();

    uint64_t start = m_app->getTimestamp();

    FontManager* fm = m_app->getFontManager();

    surface->clear(0x002b2b2b);
    //surface->clear(0x272822);

    FontHandle* textFont = ((Vide*)m_app)->getTextFont();

    int charWidth = fm->width(textFont, L"M");
    int charHeight = textFont->getPixelHeight(72);
    unsigned int viewLines = m_setSize.height / charHeight;

    // Make sure that we are scrolled to wherever the cursor is
    unsigned int scrollPos = m_scrollBar->getPos();

    // Set the default colour to the TEXT colour
    uint32_t defaultColour = 0xffffff;
    map<TokenType, uint32_t>::iterator it;
    it = m_colours.find(TOKEN_TEXT);
    if (it != m_colours.end())
    {
        defaultColour = it->second;
    }

    int drawX = 0;
    int drawY = 0;

    Position selectStart = m_editor->getSelectStart();
    Position selectEnd = m_editor->getSelectEnd();
    if (selectStart > selectEnd)
    {
        Position tmp = selectEnd;
        selectEnd = selectStart;
        selectStart = tmp;
    }

    bool hasSel = m_editor->hasSelection();


    vector<Line*> lines = buffer->getLines();

    //surface->drawRectFilled(0, 0, 9, 12, 0x0000ff00);
    unsigned int ypos = 0;
    for (ypos = 0; ypos < viewLines; ypos++)
    {
        Position drawPos(scrollPos + ypos, 0);

        if (drawPos.line >= lines.size())
        {
            break;
        }

        // Draw margin
        wchar_t marginbuffer[1024];
        swprintf(marginbuffer, 1024, L"%4d", drawPos.line + 1);

        fm->write(textFont,
            surface,
            0,
            drawY,
            wstring(marginbuffer),
            0x00BBBBBB,
            true,
            NULL);
 
        drawX = m_marginX;
        unsigned int xpos = 0;

        Line* line = lines.at(drawPos.line);

        if (drawPos.line == cursor.line && cursor.column > line->text.length())
        {
            cursor.column = line->text.length();
        }

        if (line->tokens.empty())
        {
            surface->drawRectFilled(drawX, drawY, charWidth, charHeight, 0x00BBBBBB);
        }

        vector<LineToken*>::iterator tokenIt;
        for (tokenIt = line->tokens.begin(); tokenIt != line->tokens.end(); tokenIt++)
        {
            LineToken* token = *tokenIt;

            unsigned int startX = drawX;
            unsigned int tokenLen = token->text.length();

            if (drawPos.line == cursor.line && (tokenIt + 1) == line->tokens.end() && drawPos.column >= xpos + tokenLen)
            {
                //cursorX = xpos + fragLen;
                tokenLen++;
            }

            unsigned int tokenPos;
            for (tokenPos = 0; tokenPos < tokenLen; xpos++, tokenPos++, drawPos.column++)
            {
                if (drawX + charWidth > (m_setSize.width - m_scrollBar->getWidth()))
                {
                    break;
                }

                if (hasSel && drawPos >= selectStart && drawPos < selectEnd)
                {
                    // Highlight the selected region
                    surface->drawRectFilled(drawX, drawY, charWidth, charHeight, 0x00214283);
                }

                if (xpos == cursor.column && drawPos.line == cursor.line)
                {
                    drawCursor(surface, drawX, drawY, charWidth, charHeight);
                }

                if (tokenPos < token->text.length())
                {
                    wstring str = L"";
                    str += token->text.at(tokenPos);

                    uint32_t colour;
                    map<TokenType, uint32_t>::iterator it;
                    it = m_colours.find(token->type);
                    if (it != m_colours.end())
                    {
                        colour = it->second;
                    }
                    else
                    {
                        colour = defaultColour;
                    }

                    fm->write(textFont,
                        surface,
                        drawX + 1,
                        drawY,
                        str,
                        colour,
                        true,
                        NULL);
                }

                drawX += charWidth;
            }

            if (!token->messages.empty())
            {
                int maxType = 0;
                for (TokenMessage message : token->messages)
                {
                    if (message.type > maxType)
                    {
                        maxType = message.type;
                    }
                }
                uint32_t messageCol = 0;
                switch (maxType)
                {
                    case ::MESSAGE_INFO:
                        messageCol = 0xff6897BB;
                        break;
                    case MESSAGE_WARNING:
                        messageCol = 0xffFFC66D;
                        break;
                    case MESSAGE_ERROR:
                        messageCol = 0xffff0000;
                        break;
                }
                surface->drawLine(startX, drawY + charHeight - 1, drawX, drawY + charHeight - 1, messageCol);
            }
        }
            if (xpos == cursor.column && drawPos.line == cursor.line)
            {
                drawCursor(surface, drawX, drawY, charWidth, charHeight);
            }

        drawY += charHeight;
    }

    uint64_t end = m_app->getTimestamp();
    uint64_t diff = end - start;
    log(DEBUG, "draw: time=%llu", diff);

    surface->drawLine(m_marginX - 1, 0, m_marginX - 1, m_setSize.height - 1, 0xffBBBBBB);

    if (buffer != NULL)
    {
        m_scrollBar->set(0, buffer->getLineCount(), viewLines);
    }

    SurfaceViewPort scrollbarVP(surface, m_scrollBar->getX(), m_scrollBar->getY(), m_scrollBar->getWidth(), m_scrollBar->getHeight());
    m_scrollBar->draw(&scrollbarVP);

    return true;
}

void EditorView::drawCursor(Surface* surface, int x, int y, int w, int h)
{
    CursorType cursorType = m_interface->getCursorType();

    // Draw the cursor!
    switch (cursorType)
    {
        case CURSOR_BLOCK:
            surface->drawRectFilled(x, y, w, h, 0x00BBBBBB);
            break;
        case CURSOR_BAR:
            surface->drawRectFilled(x, y, 1, h, 0x00BBBBBB);
            break;
    }
}

Widget* EditorView::handleEvent(Event* event)
{
    switch (event->eventType)
    {
        case FRONTIER_EVENT_KEY:
        {
            KeyEvent* keyEvent = (KeyEvent*)event;

            wchar_t c = L'?';
            if (iswprint(keyEvent->chr))
            {
                c = keyEvent->chr;
            }

            log(DEBUG, "handleMessage: Key press: 0x%x (%d) -> %lc, modifiers=0x%x",
                keyEvent->key,
                keyEvent->key,
                c,
                keyEvent->modifiers);

            if (keyEvent->key == KC_TAB && !!(keyEvent->modifiers & KMOD_CONTROL))
            {
                Tabs* tabs = (Tabs*)findParent(typeid(Tabs));
                if (tabs != NULL)
                {
                    if (!!(keyEvent->modifiers & KMOD_SHIFT))
                    {
                        log(DEBUG, "handleMessage: Prev tab!!");
                        tabs->prevTab();
                    }
                    else
                    {
                        log(DEBUG, "handleMessage: Next tab!!");
                        tabs->nextTab();
                    }
                }
                return this;
            }

            m_interface->key(keyEvent);
            updateStatus();

            if (m_editor->isDirty())
            {
                setDirty(DIRTY_CONTENT);
            }

            return this;
        } break;

        case FRONTIER_EVENT_MOUSE_BUTTON:
        case FRONTIER_EVENT_MOUSE_MOTION:
        {
            MouseEvent* mouseEvent = (MouseEvent*)event;

                int x = mouseEvent->x;
                int y = mouseEvent->y;

                if (m_scrollBar->intersects(x, y))
                {
                    return m_scrollBar->handleEvent(event);
                }

                Vector2D thisPos = getAbsolutePosition();
                x -= thisPos.x;
                y -= thisPos.y;

                if (x > m_marginX)
                {
                    x -= m_marginX;

                    FontManager* fm = m_app->getFontManager();
                    FontHandle* textFont = ((Vide*)m_app)->getTextFont();

                    int charWidth = fm->width(textFont, L"M");
                    int charHeight = textFont->getPixelHeight(72);

                    int scrollPos = m_scrollBar->getPos();

                    Position mousePos;
                    mousePos.line = scrollPos + (y / charHeight);
                    mousePos.column = x / charWidth;
 
                    if (event->eventType == FRONTIER_EVENT_MOUSE_BUTTON)
                    {
                        MouseButtonEvent* mouseButtonEvent = (MouseButtonEvent*)event;
                        if (mouseButtonEvent->direction)
                        {
                            m_selecting = true;
                            m_editor->setSelectStart(mousePos);
                            m_editor->setSelectEnd(mousePos);
                            m_editor->moveCursor(mousePos);
                        }
                        else
                        {
                            m_selecting = false;
                        }

                        setDirty(DIRTY_CONTENT);
                        return this;
                    }
                    else if (event->eventType == FRONTIER_EVENT_MOUSE_MOTION)
                    {
                        if (m_selecting)
                        {
                            m_editor->setSelectEnd(mousePos);
                            m_editor->moveCursorX(mousePos.column);
                            m_editor->moveCursorY(mousePos.line);
                            setDirty(DIRTY_CONTENT);
                        }

                        VideWindow* videWindow = (VideWindow*)getWindow();
                        LineToken* token = m_editor->getBuffer()->getToken(mousePos);
                        bool showTip = false;
                        if (token != NULL)
                        {
                            if (!token->messages.empty())
                            {
                                int x = mouseEvent->x;
                                int y = mouseEvent->y;
                                Geek::Vector2D screenPos = videWindow->getScreenPosition(Geek::Vector2D(x + 1, y + 1));
                                videWindow->getEditorTipWindow()->setToken(token, screenPos);

                                showTip = true;
                            }
                        }
                        if (!showTip)
                        {
                            videWindow->getEditorTipWindow()->hide();
                        }
                    }
                }
                return this;
            } break;

            case FRONTIER_EVENT_MOUSE_SCROLL:
            {
                MouseScrollEvent* mouseScrollEvent = (MouseScrollEvent*)event;
                int scrollPos = m_scrollBar->getPos();
                scrollPos -= mouseScrollEvent->scrollY;
                m_scrollBar->setPos(scrollPos);

                setDirty(DIRTY_CONTENT);

                return this;
            } break;

            default:
                //log(WARN, "handleMessage: Unhandled input message type: %d", inputMessage->inputMessageType);
                break;
        }

    return NULL;
}

void EditorView::onScrollbarChanged(int pos)
{
    log(DEBUG, "onScrollbarChanged: pos=%d", pos);
}

void EditorView::onMouseLeave()
{
    VideWindow* videWindow = (VideWindow*)getWindow();
    videWindow->getEditorTipWindow()->hide();
}

void EditorView::cursorMoved()
{
    unsigned int scrollPos = m_scrollBar->getPos();
    Position cursor = m_editor->getCursorPosition();

    if (cursor.line < scrollPos)
    {
        scrollPos = cursor.line;
        m_scrollBar->setPos(scrollPos);
    }
    else
    {
        unsigned int viewLines = getViewLines();
        if (cursor.line >= (scrollPos + viewLines))
        {
            scrollPos = (cursor.line - viewLines) + 1;
            m_scrollBar->setPos(scrollPos);
        }
    }
}

void EditorView::updateStatus()
{
    VideWindow* videWindow = (VideWindow*)getWindow();
    if (videWindow != NULL)
    {

        videWindow->setInterfaceStatus(m_interface->getStatus());
        wchar_t editorStatus[1024];
        swprintf(editorStatus, 1024, L"Line: %d, Col: %d", m_editor->getCursorPosition().line + 1, m_editor->getCursorPosition().column + 1);
        videWindow->setEditorStatus(wstring(editorStatus));
    }
}

unsigned int EditorView::getViewLines()
{
    FontHandle* textFont = ((Vide*)m_app)->getTextFont();
    int charHeight = textFont->getPixelHeight(72);
    return m_setSize.height / charHeight;
}

