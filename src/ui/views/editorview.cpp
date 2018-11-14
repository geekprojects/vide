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
#include "ui/views/editorview.h"
#include "vide.h"
#include "interfaces/vi/vi.h"

#include <wctype.h>

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;

EditorView::EditorView(Vide* vide, Editor* editor) : Widget(vide)
{
    m_vide = vide;
    m_editor = editor;

    m_cursorType = CURSOR_BLOCK;

    m_scrollBar = new ScrollBar(vide);
    m_scrollBar->incRefCount();
    m_scrollBar->setParent(this);
    m_scrollBar->changedPositionSignal().connect(sigc::mem_fun(*this, &EditorView::onScrollbarChanged));

    m_interface = new ViInterface(editor);

    m_marginX = 40;

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
}

EditorView::~EditorView()
{
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
        uint64_t start = m_ui->getTimestamp();
        m_editor->getFileTypeManager()->tokenise(buffer);
        uint64_t end = m_ui->getTimestamp();
        uint64_t diff = end - start;
        printf("Editor::draw: tokenise time=%llu\n", diff);
    }

    uint64_t start = m_ui->getTimestamp();

    FontManager* fm = m_ui->getFontManager();

    surface->clear(0x002b2b2b);
    //surface->clear(0x272822);

    FontHandle* textFont = ((Vide*)m_ui)->getTextFont();

    int charWidth = fm->width(textFont, L"M");
    int charHeight = textFont->getPixelHeight(72);
    unsigned int viewLines = m_setSize.height / charHeight;

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

    int scrollPos = m_scrollBar->getPos();

    vector<Line*> lines = buffer->getLines();

    //surface->drawRectFilled(0, 0, 9, 12, 0x0000ff00);
    unsigned int ypos = 0;
    for (ypos = 0; ypos < viewLines; ypos++)
    {
        unsigned int lineNumber = scrollPos + ypos;

        if (lineNumber >= lines.size())
        {
            break;
        }

        // Draw margin
        wchar_t marginbuffer[1024];
        swprintf(marginbuffer, 1024, L"%4d", lineNumber + 1);

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

        Line* line = lines.at(lineNumber);

Position cursor = m_editor->getCursorPosition();
        unsigned int column = cursor.column;
        if (column > line->text.length())
        {
            column = line->text.length();
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

            if (lineNumber == cursor.line && (tokenIt + 1) == line->tokens.end() && column >= xpos + tokenLen)
            {
                //cursorX = xpos + fragLen;
                tokenLen++;
            }

            unsigned int tokenPos;
            for (tokenPos = 0; tokenPos < tokenLen; xpos++, tokenPos++)
            {
                if (drawX + charWidth > (m_setSize.width - m_scrollBar->getWidth()))
                {
                    break;
                }

                if (xpos == column && lineNumber == cursor.line)
                {
                    // Draw the cursor!
                    switch (m_cursorType)
                    {
                        case CURSOR_BLOCK:
                            surface->drawRectFilled(drawX, drawY, charWidth, charHeight, 0x00BBBBBB);
                            break;
                        case CURSOR_BAR:
                            surface->drawRectFilled(drawX, drawY, 1, charHeight, 0x00BBBBBB);
                            break;
                    }
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

        drawY += charHeight;
    }

    uint64_t end = m_ui->getTimestamp();
    uint64_t diff = end - start;
    printf("Editor::draw: time=%llu\n", diff);

    surface->drawLine(m_marginX - 1, 0, m_marginX - 1, m_setSize.height - 1, 0xffBBBBBB);

    if (buffer != NULL)
    {
        m_scrollBar->set(0, buffer->getLineCount(), viewLines);
    }

    SurfaceViewPort scrollbarVP(surface, m_scrollBar->getX(), m_scrollBar->getY(), m_scrollBar->getWidth(), m_scrollBar->getHeight());
    m_scrollBar->draw(&scrollbarVP);

    return true;
}

Widget* EditorView::handleMessage(Message* msg)
{
    if (msg->messageType == FRONTIER_MSG_INPUT)
    {
        InputMessage* inputMessage = (InputMessage*)msg;
        switch (inputMessage->inputMessageType)
        {
            case FRONTIER_MSG_INPUT_KEY:
            {
                wchar_t c = L'?';
                if (iswprint(inputMessage->event.key.chr))
                {
                    c = inputMessage->event.key.chr;
                }

                printf("Editor::handleMessage: Key press: 0x%x (%d) -> %lc, modifiers=0x%x\n",
                    inputMessage->event.key.key,
                    inputMessage->event.key.key,
                    c,
                    inputMessage->event.key.modifiers);

                m_interface->key(inputMessage);

                return this;
            } break;

            case FRONTIER_MSG_INPUT_MOUSE_BUTTON:
            case FRONTIER_MSG_INPUT_MOUSE_MOTION:
            {
                int x = inputMessage->event.button.x;
                int y = inputMessage->event.button.y;

                if (m_scrollBar->intersects(x, y))
                {
                    return m_scrollBar->handleMessage(msg);
                }

                Vector2D thisPos = getAbsolutePosition();
                x -= thisPos.x;
                y -= thisPos.y;

                if (x > m_marginX)
                {
                    x -= m_marginX;

                    FontManager* fm = m_ui->getFontManager();
                    FontHandle* textFont = ((Vide*)m_ui)->getTextFont();

                    int charWidth = fm->width(textFont, L"M");
                    int charHeight = textFont->getPixelHeight(72);

                    int scrollPos = m_scrollBar->getPos();
                    int mouseCursorX = x / charWidth;
                    int mouseCursorY = scrollPos + (y / charHeight);
 
                    if (inputMessage->inputMessageType == FRONTIER_MSG_INPUT_MOUSE_BUTTON)
                    {
                        m_editor->moveCursorX(mouseCursorX);
                        m_editor->moveCursorY(mouseCursorY);

                        setDirty(DIRTY_CONTENT);
                        return this;
                    }
                    else if (inputMessage->inputMessageType == FRONTIER_MSG_INPUT_MOUSE_MOTION)
                    {
                        LineToken* token = m_editor->getBuffer()->getToken(Position(mouseCursorY, mouseCursorX));
                        bool showTip = false;
                        if (token != NULL)
                        {
                            if (!token->messages.empty())
                            {
                                int x = inputMessage->event.button.x;
                                int y = inputMessage->event.button.y;
                                Geek::Vector2D screenPos = m_vide->getWindow()->getScreenPosition(Geek::Vector2D(x + 1, y + 1));
                                m_vide->getWindow()->getEditorTipWindow()->setToken(token, screenPos);

                                showTip = true;
                            }
                        }
                        if (!showTip)
                        {
                            m_vide->getWindow()->getEditorTipWindow()->hide();
                        }
                    }
                }
                return this;
            } break;

            case FRONTIER_MSG_INPUT_MOUSE_WHEEL:
            {
                int scrollPos = m_scrollBar->getPos();
                scrollPos -= inputMessage->event.wheel.scrollY;
                m_scrollBar->setPos(scrollPos);

                return this;
            } break;

            default:
                //printf("Editor::handleMessage: Unhandled input message type: %d\n", inputMessage->inputMessageType);
                break;
        }
    }
    else
    {
        printf("Editor::handleMessage: Unhandled message type: %d\n", msg->messageType);
    }

    return NULL;
}

void EditorView::onScrollbarChanged(int pos)
{
    printf("Editor::onScrollbarChanged: pos=%d\n", pos);

}

void EditorView::onMouseLeave()
{
    m_vide->getWindow()->getEditorTipWindow()->hide();
}

void EditorView::setInterfaceStatus(std::wstring message)
{
    m_vide->getWindow()->setInterfaceStatus(message);
}

unsigned int EditorView::getViewLines()
{
    FontHandle* textFont = ((Vide*)m_ui)->getTextFont();
    int charHeight = textFont->getPixelHeight(72);
    return m_setSize.height / charHeight;
}

