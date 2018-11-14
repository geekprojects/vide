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
#include "interfaces/vi/vi.h"

#include <wctype.h>

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;

Editor::Editor(Vide* vide, Buffer* buffer, FileTypeManager* ftm) : Widget(vide)
{
    m_vide = vide;
    m_buffer = buffer;

    m_cursor.line = 0;
    m_cursor.column = 0;
    m_cursorType = CURSOR_BLOCK;

    m_scrollBar = new ScrollBar(vide);
    m_scrollBar->incRefCount();
    m_scrollBar->setParent(this);
    m_scrollBar->changedPositionSignal().connect(sigc::mem_fun(*this, &Editor::onScrollbarChanged));

    m_interface = new ViInterface(this);
    m_fileTypeManager = ftm;

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
    if (m_buffer->isDirty())
    {
        uint64_t start = m_ui->getTimestamp();
        m_fileTypeManager->tokenise(m_buffer);
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

    vector<Line*> lines = m_buffer->getLines();

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

            unsigned int startX = drawX;
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

                if (xpos == column && lineNumber == m_cursor.line)
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
    return m_buffer->save();
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
                        moveCursorX(mouseCursorX);
                        moveCursorY(mouseCursorY);

                        setDirty(DIRTY_CONTENT);
                        return this;
                    }
                    else if (inputMessage->inputMessageType == FRONTIER_MSG_INPUT_MOUSE_MOTION)
                    {
                        LineToken* token = m_buffer->getToken(Position(mouseCursorY, mouseCursorX));
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

void Editor::onScrollbarChanged(int pos)
{
    printf("Editor::onScrollbarChanged: pos=%d\n", pos);

}

void Editor::onMouseLeave()
{
    m_vide->getWindow()->getEditorTipWindow()->hide();
}

void Editor::setBuffer(Buffer* buffer)
{
    m_buffer = buffer;

    m_fileTypeManager->tokenise(m_buffer);

    m_interface->updateStatus();

    setDirty(DIRTY_CONTENT);
}

Position Editor::findPrevWord()
{
    return findPrevWord(m_cursor);
}

Position Editor::findPrevWord(Position from)
{
    Line* line = m_buffer->getLine(from.line);
    vector<LineToken*>::iterator it;
    it = line->tokenAt(from.column, false);

    bool prevLine = false;
    if (it != line->tokens.begin() && (it - 1) != line->tokens.begin())
    {
        LineToken* curToken = *it;
        printf("CURRENT TOKEN: %ls\n", curToken->text.c_str());

        if (curToken->column < from.column)
        {
            return Position(from.line, curToken->column);
        }

        do
        {
            it--;
        }
        while (it != line->tokens.begin() && (*it)->isSpace);

        if (it != line->tokens.begin())
        {
            LineToken* nextToken = *it;

            printf("PREV TOKEN: %lsn", nextToken->text.c_str());
            return Position(from.line, nextToken->column);
        }
        else
        {
            prevLine = true;
        }
    }
    else
    {
        prevLine = true;
    }

    if (prevLine)
    {
        printf("START OF LINE\n");
        if (from.line > 0)
        {
            Line* prevLine = m_buffer->getLine(from.line - 1);
            return findPrevWord(Position(from.line - 1, prevLine->text.length() - 1));
        }
        else
        {
            printf("RETURNING START OF FILE\n");

            return Position(0, 0);
        }
    }

    return Position(0, 0);
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
    printf("Editor::moveCursorDelta: m_cursorX=%d, moveCursorY=%d\n", m_cursor.column, m_cursor.line);
}

void Editor::moveCursorXEnd()
{
    int width = m_buffer->getLineLength(m_cursor.line);
    m_cursor.column = width - 1;
    setDirty(DIRTY_CONTENT);
}

void Editor::moveCursorYEnd()
{
    moveCursor(Position(m_buffer->getLineCount() - 1, 0));

    setDirty(DIRTY_CONTENT);
}

void Editor::moveCursorPage(int dir)
{
    int viewLines = getViewLines();

    moveCursorDelta(0, viewLines * dir);
}

void Editor::executeEdits(std::vector<Edit> edits)
{
    for (Edit edit : edits)
    {
        executeEdit(edit);
    }

    setDirty(DIRTY_CONTENT);
}

void Editor::executeEdit(Edit edit)
{
    Line* line = m_buffer->getLine(edit.position.line);

    switch (edit.editType)
    {
        case EDIT_INSERT:
        {
            unsigned int i;
            for (i = 0; i < edit.text.length(); i++)
            {
                line->text.insert(edit.position.column + i, 1, edit.text.at(i));
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
            m_buffer->setDirtyLine(line);
            break;

        case EDIT_DELETE_LINE:
            m_buffer->deleteLine(edit.position.line);
            break;

        case EDIT_DELETE_TO_END:
            line->text.erase(edit.position.column);
            m_buffer->setDirtyLine(line);
            break;
    }
}

void Editor::undoEdits(std::vector<Edit> edits)
{
    vector<Edit>::reverse_iterator rit;
    printf("Editor::undoEdits: Undoing %lu edits\n", edits.size());
    for (rit = edits.rbegin(); rit != edits.rend(); rit++)
    {
        Edit edit = *rit;
        undoEdit(edit);
    }

    setDirty(DIRTY_CONTENT);
}

void Editor::undoEdit(Edit edit)
{
    Line* line = m_buffer->getLine(edit.position.line);

    switch (edit.editType)
    {
        case EDIT_INSERT:
            printf("Editor::undoEdit: EDIT_INSERT: %lu chars\n", edit.text.length());
            line->text.erase(edit.position.column, edit.text.length());
            m_buffer->setDirtyLine(line);
            break;

        case EDIT_NEW_LINE:
            m_buffer->deleteLine(edit.position.line + 1);
            printf("Editor::undoEdit: EDIT_NEW_LINE\n");
            break;

        case EDIT_SPLIT_LINE:
        {
            printf("Editor::undoEdit: EDIT_SPLIT_LINE:\n");

            doJoinLines(edit.position.line, line);
        } break;

        case EDIT_JOIN_LINES:
            printf("Editor::undoEdit: EDIT_JOIN_LINES:\n");
            doSplitLine(edit.position, line);
            break;

        case EDIT_DELETE_CHAR:
            printf("Editor::undoEdit: EDIT_DELETE_CHAR:\n");
            line->text.insert(edit.position.column, 1, edit.text.at(0));
            m_buffer->setDirtyLine(line);
            break;

        case EDIT_DELETE_LINE:
        {
            printf("Editor::undoEdit: EDIT_DELETE_LINE:\n");

            Line* newLine = new Line();
            newLine->lineEnding = "\n";
            newLine->text = edit.text;
            m_buffer->insertLine(edit.position.line, newLine);

            m_buffer->setDirtyLine(line);
        } break;

        case EDIT_DELETE_TO_END:
            printf("Editor::undoEdit: EDIT_DELETE_TO_END: %ls\n", edit.text.c_str());
            line->text += edit.text;
            m_buffer->setDirtyLine(line);
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
    printf("Editor::insert: m_cursorX=%u, textLen=%u\n", m_cursor.column, textLen);

    vector<Edit> edits;
    edits.push_back(Edit(m_cursor, EDIT_INSERT, c));

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
    edits.push_back(Edit(m_cursor, EDIT_DELETE_CHAR, line->text.at(m_cursor.column)));

    executeEdits(edits);

    return edits;
}

vector<Edit> Editor::deleteLine()
{
    vector<Edit> edits;

    Line* line = m_buffer->getLine(m_cursor.line);
    edits.push_back(Edit(m_cursor, EDIT_DELETE_LINE, line->text));

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
    edits.push_back(Edit(m_cursor, EDIT_DELETE_TO_END, text));

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
            printf("Editor::copyToBuffer: Copying: %ls\n", line->text.c_str());
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
        edits.push_back(Edit(m_cursor, EDIT_INSERT, text));
    }

    executeEdits(edits);

    return edits;
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

