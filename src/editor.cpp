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

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;

Editor::Editor(Vide* vide, Buffer* buffer) : Widget(vide)
{
    m_vide = vide;
m_buffer = buffer;

    m_cursor.line = 0;
    m_cursor.column = 0;

    m_scrollBar = new ScrollBar(vide);
    m_scrollBar->setParent(this);
    m_scrollBar->changedPositionSignal().connect(sigc::mem_fun(*this, &Editor::onScrollbarChanged));

    m_interface = new ViInterface(this);
    m_format = new SimpleFormat();

    m_marginX = 40;
}

Editor::~Editor()
{
}

void Editor::calculateSize()
{
    //m_minSize.set(50, 50);
    m_minSize.set(300, 300);
    m_maxSize.set(WIDGET_SIZE_UNLIMITED, WIDGET_SIZE_UNLIMITED);

    m_scrollBar->calculateSize();
}

void Editor::layout()
{
    m_scrollBar->setPosition(m_setSize.width - m_scrollBar->getMinSize().width, 0);
    m_scrollBar->setSize(Size(m_scrollBar->getMinSize().width, m_setSize.height));

}

bool Editor::draw(Surface* surface)
{
    FontManager* fm = m_ui->getFontManager();

    surface->clear(0x002b2b2b);
    //surface->clear(0x272822);

    FontHandle* textFont = ((Vide*)m_ui)->getTextFont();

    int charWidth = fm->width(textFont, L"M");
    int charHeight = textFont->getPixelHeight(72);
    unsigned int viewLines = m_setSize.height / charHeight;

    int drawX = 0;
    int drawY = 0;

    int scrollPos = m_scrollBar->getPos();
    printf("Editor::draw: scrollPos=%d\n", scrollPos);

    vector<Line*> lines = m_buffer->getLines();

    //surface->drawRectFilled(0, 0, 9, 12, 0x0000ff00);
    unsigned int ypos = 0;
    for (ypos = 0; ypos < viewLines; ypos++)
    {
/*
        if (drawY + charHeight > m_setSize.height)
        {
            break;
        }
*/

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

        unsigned int column = m_cursor.column;
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

            unsigned int tokenLen = token->text.length();

            if (lineNumber == m_cursor.line && (tokenIt + 1) == line->tokens.end() && column >= xpos + tokenLen)
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

                uint32_t textCol = 0x00BBBBBB;
                if (xpos == column && lineNumber == m_cursor.line)
                {
                    // Draw the cursor!
                    surface->drawRectFilled(drawX, drawY, charWidth, charHeight, 0x00BBBBBB);
                    textCol = 0x002b2b2b;
                }

                if (tokenPos < token->text.length())
                {
                    wstring str = L"";
                    str += token->text.at(tokenPos);

                    fm->write(textFont,
                        surface,
                        drawX + 1,
                        drawY,
                        str,
                        token->colour,
                        //textCol,
                        true,
                        NULL);
                }

                drawX += charWidth;
            }
        }

        drawY += charHeight;
    }

    surface->drawLine(m_marginX - 1, 0, m_marginX - 1, m_setSize.height - 1, 0xffBBBBBB);

    if (m_buffer != NULL)
    {
        m_scrollBar->set(0, m_buffer->getLineCount(), viewLines);
    }

    SurfaceViewPort scrollbarVP(surface, m_scrollBar->getX(), m_scrollBar->getY(), m_scrollBar->getWidth(), m_scrollBar->getHeight());
    m_scrollBar->draw(&scrollbarVP);

    return true;
}

bool Editor::save()
{
    m_buffer->save();
    return true;
}

Widget* Editor::handleMessage(Message* msg)
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

                if (inputMessage->inputMessageType == FRONTIER_MSG_INPUT_MOUSE_BUTTON)
                {
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
                        moveCursorX(x / charWidth);
                        moveCursorY(scrollPos + (y / charHeight));
                    }

                    setDirty(DIRTY_CONTENT);
                    return this;
                }
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

void Editor::onScrollbarChanged(int pos)
{
    printf("Editor::onScrollbarChanged: pos=%d\n", pos);

}

void Editor::setBuffer(Buffer* buffer)
{
    m_buffer = buffer;

    m_format->tokenise(m_buffer);

    m_interface->updateStatus();

    setDirty(DIRTY_CONTENT);
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
        printf("CURRENT TOKEN: %ls\n", curToken->text.c_str());

        do
        {
            it++;
        }
        while (it != line->tokens.end() && (*it)->isSpace);

        if (it != line->tokens.end())
        {
            LineToken* nextToken = *it;

            printf("NEXT TOKEN: %lsn", nextToken->text.c_str());
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
        printf("END OF LINE\n");
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
            printf("RETURNING END OF FILE\n");

            return Position(from.line, line->text.length() - 1);
        }
    }

    return Position();
}

void Editor::moveCursor(Position pos)
{
    moveCursorY(pos.line);
    moveCursorX(pos.column);
}

void Editor::moveCursorX(unsigned int x)
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
        if (x > width)
        {
            x = width;
        }
    }

    if (m_cursor.column != x)
    {
        m_cursor.column = x;
        setDirty(DIRTY_CONTENT);
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
        unsigned int scrollPos = m_scrollBar->getPos();
        m_cursor.line = y;
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
        setDirty(DIRTY_CONTENT);
    }
}

void Editor::moveCursorDelta(int dx, int dy)
{
    // Move Y first as X depends on line width
    if (dy != 0)
    {
        moveCursorY(m_cursor.line + dy);
    }

    if (dx != 0)
    {
        moveCursorX(m_cursor.column + dx);
    }
    printf("Editor::moveCursorDelta: m_cursorX=%d, moveCursorY=%d\n", m_cursor.column, m_cursor.line);
}

void Editor::moveCursorXEnd()
{
    int width = m_buffer->getLineLength(m_cursor.line);
    m_cursor.column = width - 1;
    setDirty(DIRTY_CONTENT);
}

void Editor::moveCursorPage(int dir)
{
    int viewLines = getViewLines();

    moveCursorDelta(0, viewLines * dir);
}

void Editor::insert(wchar_t c)
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
    printf("Editor::insert: m_cursorX=%u, textLen=%u\n", m_cursor.column, textLen);

    line->text.insert(m_cursor.column, 1, c);
    m_cursor.column++;

    m_format->tokenise(line);

    setDirty(DIRTY_CONTENT);
}

void Editor::insertLine()
{
    Line* line = new Line();
    line->lineEnding = "\n";

    m_buffer->insertLine(m_cursor.line + 1, line);
    setDirty(DIRTY_CONTENT);
}

void Editor::splitLine()
{
    Line* line = m_buffer->getLine(m_cursor.line);

    wstring text1 = line->text.substr(0, m_cursor.column);
    wstring text2 = line->text.substr(m_cursor.column);

    line->text = text1;

    Line* newLine = new Line();
    newLine->lineEnding = line->lineEnding;
    newLine->text = text2;

    m_buffer->insertLine(m_cursor.line + 1, newLine);
    m_format->tokenise(line);
    m_format->tokenise(newLine);
    setDirty(DIRTY_CONTENT);
}

void Editor::deleteAtCursor()
{
    Line* line = m_buffer->getLine(m_cursor.line);
    line->text.erase(m_cursor.column, 1);

    m_format->tokenise(line);

    setDirty(DIRTY_CONTENT);
}

void Editor::deleteLine()
{
    m_buffer->deleteLine(m_cursor.line);

    unsigned int count = m_buffer->getLineCount();
    if (count == 0)
    {
        m_cursor.line = 0;
        Line* line = new Line();
        line->lineEnding = "\n";

        m_buffer->insertLine(m_cursor.line, line);
    }

    if (m_cursor.line >= m_buffer->getLineCount())
    {
        m_cursor.line = m_buffer->getLineCount() - 1;
    }

    setDirty(DIRTY_CONTENT);
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
            printf("Editor::copyToBuffer: Copying: %ls\n", line->text.c_str());
            copyVec.push_back(line->text);
        }
    }
    m_vide->setBuffer(copyVec);
}

void Editor::pasteFromBuffer()
{
    vector<wstring> copyVec = m_vide->getBuffer();

    for (wstring text : copyVec)
    {
        Line* line = new Line();
        line->lineEnding = "\n";
        line->text = text;
        m_format->tokenise(line);

        m_buffer->insertLine(++m_cursor.line, line);
    }
    setDirty(DIRTY_CONTENT);
}

void Editor::setInterfaceStatus(std::wstring message)
{
    m_vide->getWindow()->setInterfaceStatus(message);
}

unsigned int Editor::getViewLines()
{
    FontHandle* textFont = ((Vide*)m_ui)->getTextFont();
    int charHeight = textFont->getPixelHeight(72);
    return m_setSize.height / charHeight;
}

