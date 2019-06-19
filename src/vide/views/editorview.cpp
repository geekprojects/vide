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


#include <vide/editor.h>
#include <vide/interface.h>
#include "views/editorview.h"
#include <vide/vide.h>
#include <vide/utils.h>

#include <wctype.h>

#include <frontier/utils.h>

#define ALIGN(V, SIZE) ((((V) + (SIZE) - 1) / (SIZE)) * (SIZE))

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;
using namespace Geek::Core;


class EditorTokeniseTask : public Task
{
 private:
    Editor* m_editor;
    uint64_t m_tokeniseTime;

 public:
    EditorTokeniseTask(Editor* editor) : Task(L"Tokeniser")
    {
        m_editor = editor;
    }

    virtual ~EditorTokeniseTask()
    {
    }

    void run()
    {
        uint64_t start = ::Utils::getTimestamp();
        m_editor->getFileTypeManager()->tokenise(m_editor->getBuffer());
        uint64_t end = ::Utils::getTimestamp();
        m_tokeniseTime = end - start;
        //m_editor->getBuffer()->tokeniseCompleteSignal().emit();
    }

    uint64_t getTokeniseTime()
    {
        return m_tokeniseTime;
    }
};

EditorView::EditorView(VideApp* vide, Editor* editor) : Widget(vide, L"EditorView")
{
    m_vide = vide;
    m_editor = editor;
    m_editor->cursorMovedSignal().connect(sigc::mem_fun(*this, &EditorView::onCursorMoved));
    m_editor->editedSignal().connect(sigc::mem_fun(*this, &EditorView::onEdit));
    m_characterMap = new EditorCharacterMap();

    // Kick off a tokenisation straight away
    indexTimer(NULL);

    m_indexTimer = new Timer(TIMER_ONE_SHOT, m_tokeniseTime + 10);
    m_indexTimer->signal().connect(sigc::mem_fun(*this, &EditorView::indexTimer));

    m_scrollBar = new ScrollBar(vide);
    m_scrollBar->incRefCount();
    m_scrollBar->setParent(this);
    m_scrollBar->changedPositionSignal().connect(sigc::mem_fun(*this, &EditorView::onScrollbarChanged));

    InterfacePlugin* interfacePlugin = (InterfacePlugin*)vide->getVide()->getPluginManager()->findPlugin("ViInterfacePlugin");
    if (interfacePlugin != NULL)
    {
        m_interface = interfacePlugin->createInterface(editor);
    }

    m_marginX = 40;

    FontManager* fm = m_app->getFontManager();
    FontHandle* textFont = m_vide->getTextFont();
    m_charSize.width = fm->width(textFont, L"M");
    m_charSize.height = textFont->getPixelHeight(72);

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

    m_defaultColour = 0xffffff;
    map<TokenType, uint32_t>::iterator it;
    it = m_colours.find(TOKEN_TEXT);
    if (it != m_colours.end())
    {
        m_defaultColour = it->second;
    }

    updateStatus();

}

EditorView::~EditorView()
{
    m_scrollBar->decRefCount();
}

void EditorView::calculateSize()
{
    m_minSize.set(m_marginX + (40 * m_charSize.width), m_charSize.height * 3);
    m_maxSize.set(WIDGET_SIZE_UNLIMITED, WIDGET_SIZE_UNLIMITED);

    m_scrollBar->calculateSize();
}

void EditorView::layout()
{
    m_scrollBar->setPosition(m_setSize.width - m_scrollBar->getMinSize().width, 0);
    m_scrollBar->setSize(Size(m_scrollBar->getMinSize().width, m_setSize.height));

    m_editor->setViewLines(getViewLines());
}

bool EditorView::draw(Surface* surface)
{
    Buffer* buffer = m_editor->getBuffer();

    buffer->lock();

    if (buffer->isDirty())
    {
        buffer->clearDirty();
        //m_vide->getTaskExecutor()->addTask(new EditorTokeniseTask(m_editor));
    }

    m_editor->clearDirty();

    Position cursor = m_editor->getCursorPosition();

    if (isActive())
    {
        surface->clear(0x00202020);
    }
    else
    {
        surface->clear(0x002f2f2f);
    }

    FontManager* fm = m_app->getFontManager();
    FontHandle* textFont = m_vide->getTextFont();
    FontHandle* textIconFont = m_vide->getTextIconFont();
    uint32_t iconColour = 0x004b4b4b;

    unsigned int viewLines = m_setSize.height / m_charSize.height;
    unsigned int viewColumns = m_setSize.width / m_charSize.width;
    m_characterMap->reset(viewLines, viewColumns);

    unsigned int scrollPos = m_scrollBar->getPos();

    int drawX = 0;
    int drawY = 0;
    unsigned int drawLine = 0;
    unsigned int drawColumn = 0;
    unsigned int startX = m_marginX;

    bool hasSel = m_editor->hasSelection();
    Position selectStart;
    Position selectEnd;
    if (hasSel)
    {
        selectStart = m_editor->getSelectStart();
        selectEnd = m_editor->getSelectEnd();
        if (selectStart > selectEnd)
        {
            Position tmp = selectEnd;
            selectEnd = selectStart;
            selectStart = tmp;
        }
    }

    unsigned int ypos = 0;
    vector<Line*> lines = buffer->getLines();
    for (ypos = 0; drawLine < viewLines; ypos++, drawLine++)
    {
        Position bufferPos(scrollPos + ypos, 0);

        if (bufferPos.line >= lines.size())
        {
            break;
        }

        // Draw margin
        wchar_t marginbuffer[1024];
        swprintf(marginbuffer, 1024, L"%4d", bufferPos.line + 1);
        fm->write(textFont,
            surface,
            0,
            drawY,
            wstring(marginbuffer),
            0x00BBBBBB,
            true,
            NULL);
 
        drawX = startX;
        unsigned int xpos = 0;
        drawColumn = 0;

        Line* line = lines.at(bufferPos.line);

        // Check the cursor column is valid
        if (bufferPos.line == cursor.line && cursor.column > line->text.length())
        {
            cursor.column = line->text.length();
        }

        m_characterMap->setToken(drawLine, 0, viewColumns, NULL, bufferPos);

        // Draw a line of tokens
        vector<LineToken*>::iterator tokenIt;
        for (tokenIt = line->tokens.begin(); tokenIt != line->tokens.end(); tokenIt++)
        {
            LineToken* token = *tokenIt;

            unsigned int tokenLen = token->text.length();

            if (bufferPos.line == cursor.line &&
                (tokenIt + 1) == line->tokens.end() &&
                bufferPos.column >= xpos + tokenLen)
            {
                tokenLen++;
            }

            uint32_t colour = m_defaultColour;
            map<TokenType, uint32_t>::iterator it;
            it = m_colours.find(token->type);
            if (it != m_colours.end())
            {
                colour = it->second;
            }

            bool hasMessage = false;
            uint32_t messageCol = 0;
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
                hasMessage = true;
            }

            // Draw the current token
            unsigned int tokenPos;
            for (tokenPos = 0; tokenPos < tokenLen && drawLine < viewLines; xpos++, tokenPos++, bufferPos.column++)
            {
                if (drawX + m_charSize.width > (m_setSize.width - m_scrollBar->getWidth()))
                {
                    drawX = m_marginX;
                    drawY += m_charSize.height;
                    drawLine++;
                    drawColumn = 0;
                    if (drawLine >= viewLines)
                    {
                        break;
                    }
                }

                if (hasSel && bufferPos >= selectStart && bufferPos < selectEnd)
                {
                    // Highlight the selected region
                    surface->drawRectFilled(drawX, drawY, m_charSize.width, m_charSize.height, 0x00214283);
                }

                if (xpos == cursor.column && bufferPos.line == cursor.line)
                {
                    drawCursor(surface, drawX, drawY);
                }

                int numChars = 1;
                if (tokenPos < token->text.length())
                {
                    wchar_t c = token->text.at(tokenPos);
                    wstring str = wstring(&c, 1);
                    if (c == '\t')
                    {
                        wstring text = L"";
                        text += FRONTIER_ICON_ARROW_RIGHT;

                        int alignedX = ALIGN(xpos + 1, 8);
                        numChars = alignedX - xpos;

                        if (numChars > 1)
                        {
                            fm->write(textIconFont,
                                surface,
                                drawX,
                                drawY,
                                text,
                                iconColour,
                                true,
                                NULL);
                        }
                    }

                    fm->write(textFont,
                        surface,
                        drawX + 1,
                        drawY,
                        str,
                        colour,
                        true,
                        NULL);
                    m_characterMap->setToken(drawLine, drawColumn, numChars, token, bufferPos);
                    if (hasMessage)
                    {
                        surface->drawLine(
                            drawX, drawY + m_charSize.height - 1, 
                            drawX + (m_charSize.width * numChars), drawY + m_charSize.height - 1, 
                            messageCol);
                    }

                    drawX += (m_charSize.width * numChars);
                    drawColumn += numChars;
                }
            }
        }

        if (cursor.column >= xpos && bufferPos.line == cursor.line)
        {
            // The cursor is just beyond the last character
            drawCursor(surface, drawX, drawY);
        }

        drawY += m_charSize.height;
    }

    buffer->unlock();

    surface->drawLine(m_marginX - 1, 0, m_marginX - 1, m_setSize.height - 1, 0xffBBBBBB);

    if (buffer != NULL)
    {
        m_scrollBar->set(0, buffer->getLineCount(), viewLines);
    }

    SurfaceViewPort scrollbarVP(
        surface,
        m_scrollBar->getX(), m_scrollBar->getY(),
        m_scrollBar->getWidth(), m_scrollBar->getHeight());
    m_scrollBar->draw(&scrollbarVP);

    return true;
}

void EditorView::drawCursor(Surface* surface, int x, int y)
{
    CursorType cursorType = m_interface->getCursorType();

    bool active = isActive();

    // Draw the cursor!
    switch (cursorType)
    {
        case CURSOR_BLOCK:
            if (active)
            {
                surface->drawRectFilled(x, y, m_charSize.width, m_charSize.height, 0x00BBBBBB);
            }
            else
            {
                surface->drawRect(x, y, m_charSize.width, m_charSize.height, 0x00888888);
            }
            break;
        case CURSOR_BAR:
            if (active)
            {
                surface->drawRectFilled(x, y, 1, m_charSize.height, 0x00BBBBBB);
            }
            else
            {
                surface->drawRectFilled(x, y, 1, m_charSize.height, 0x00888888);
            }
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
            else if (!!(keyEvent->modifiers & KMOD_ALT) && !!(keyEvent->modifiers & KMOD_COMMAND))
            {
                if (keyEvent->key == KC_LEFT)
                {
                    log(DEBUG, "handleMessage: MOVING LEFT!!");
                    return this;
                }
                if (keyEvent->key == KC_RIGHT)
                {
                    log(DEBUG, "handleMessage: MOVING RIGHT!!");
                    return this;
                }
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

                LineToken* selectedToken = m_characterMap->getToken(y / m_charSize.height, x / m_charSize.width);
                Position mousePos = m_characterMap->getPosition(y / m_charSize.height, x / m_charSize.width);

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
                    if (selectedToken != NULL && !selectedToken->messages.empty())
                    {
                        int x = mouseEvent->x;
                        int y = mouseEvent->y;
                        Geek::Vector2D screenPos = videWindow->getScreenPosition(Geek::Vector2D(x + 1, y + 1));
                        videWindow->getEditorTipWindow()->setToken(selectedToken, screenPos);
                    }
                    else
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

void EditorView::onCursorMoved()
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

void EditorView::onEdit()
{
    m_indexTimer->setPeriod(m_tokeniseTime + 10);
    if (m_indexTimer->isActive())
    {
        log(DEBUG, "onEdit: Resetting timer...");
        m_vide->getVide()->getTimerManager()->resetTimer(m_indexTimer);
    }
    else
    {
        log(DEBUG, "onEdit: Adding timer...");
        m_vide->getVide()->getTimerManager()->addTimer(m_indexTimer);
    }
}

void EditorView::indexTimer(Timer* timer)
{
    log(DEBUG, "indexTimer: INDEX TIMER!\n");
    EditorTokeniseTask* task = new EditorTokeniseTask(m_editor);
    task->completeSignal().connect(sigc::mem_fun(*this, &EditorView::tokeniseComplete));
    m_vide->getVide()->getTaskExecutor()->addTask(task);
}

void EditorView::updateStatus()
{
    VideWindow* videWindow = (VideWindow*)getWindow();
    if (videWindow != NULL)
    {

        videWindow->setInterfaceStatus(m_interface->getStatus());
        wchar_t editorStatus[1024];
        swprintf(
            editorStatus,
            1024,
            L"Line: %d, Col: %d",
            m_editor->getCursorPosition().line + 1,
            m_editor->getCursorPosition().column + 1);
        videWindow->setEditorStatus(wstring(editorStatus));
    }
}

unsigned int EditorView::getViewLines()
{
    FontHandle* textFont = m_vide->getTextFont();
    int charHeight = textFont->getPixelHeight(72);
    return m_setSize.height / charHeight;
}

void EditorView::tokeniseComplete(Task* task)
{
    EditorTokeniseTask* tokeniseTask = (EditorTokeniseTask*)task;
    m_tokeniseTime = tokeniseTask->getTokeniseTime();
    getWindow()->requestUpdate();
}

EditorCharacterMap::EditorCharacterMap()
{
    m_lines = 0;
    m_columns = 0;
    m_map = NULL;
}

EditorCharacterMap::~EditorCharacterMap()
{
    if (m_map != NULL)
    {
        delete[] m_map;
    }
}

EditorCharacter* EditorCharacterMap::get(int line, int column)
{
    if (m_map == NULL)
    {
        return NULL;
    }

    if (line >= m_lines || column >= m_columns)
    {
        printf("ERROR: EditorCharacterMap::get: Position is outside of map: %d, %d > %d, %d\n", line, column, m_lines, m_columns);
        return NULL;
    }

    return &(m_map[(line * m_columns) + column]);
}

void EditorCharacterMap::reset(int lines, int columns)
{
    if (m_map != NULL && (lines != m_lines || columns != m_columns))
    {
        delete[] m_map;
        m_map = NULL;
    }

    m_lines = lines;
    m_columns = columns;

    if (m_map == NULL)
    {
        m_map = new EditorCharacter[m_lines * m_columns];
    }
    memset(m_map, 0, sizeof(EditorCharacter) * m_lines * m_columns);
}

void EditorCharacterMap::setToken(int line, int column, int width, LineToken* token, Position bufferPos)
{
    int i;
    for (i = 0; i < width; i++)
    {
        EditorCharacter* ec = get(line, column + i);
        if (ec == NULL)
        {
            printf("ERROR: Failed to set token: line=%d, column=%d\n", line, column);
            continue;
        }
        ec->position = bufferPos;
        ec->token = token;
    }
}

LineToken* EditorCharacterMap::getToken(int line, int column)
{
    EditorCharacter* c = get(line, column);
    if (c == NULL)
    {
        return NULL;
    }
    return c->token;
}

Position EditorCharacterMap::getPosition(int line, int column)
{
    EditorCharacter* ec = get(line, column);
/*
    if (ec == NULL)
    {
        return Position(0, 0);
    }
*/

    if (ec != NULL && ec->token != NULL)
    {
        return ec->position;
    }

    for (; column >= 0; column--)
    {
        ec = get(line, column);
        if (ec == NULL)
        {
            continue;
        }

        if (ec->token != NULL)
        {
            return ec->position;
        }
    }

    if (ec != NULL)
    {
        return Position(ec->position.line, 0);
    }
    else
    {
        return Position(0, 0);
    }
}

