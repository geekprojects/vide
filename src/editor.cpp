
#include "editor.h"
#include "vide.h"

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;

Editor::Editor(FrontierWindow* window) : Widget(window)
{
    m_cursorX = 0;
    m_cursorY = 0;

    m_scrollBar = new ScrollBar(window);
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

    //surface->clear(0x002b2b2b);
    surface->clear(0x272822);

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

        unsigned int cursorX = m_cursorX;
        if (cursorX > line->text.length())
        {
            cursorX = line->text.length();
        }

        vector<LineToken*>::iterator tokenIt;
        for (tokenIt = line->tokens.begin(); tokenIt != line->tokens.end(); tokenIt++)
        {
            LineToken* token = *tokenIt;

            unsigned int tokenLen = token->text.length();
            if (lineNumber == m_cursorY && (tokenIt + 1) == line->tokens.end() && cursorX >= xpos + tokenLen)
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
                if (xpos == cursorX && lineNumber == m_cursorY)
                {
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
                moveCursorDelta(0, -(inputMessage->event.wheel.scrollY));
                return this;

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

void Editor::moveCursorX(unsigned int x)
{
    if (m_cursorX == x)
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
        unsigned int width = m_buffer->getLineLength(m_cursorY);
        if (x > width)
        {
            x = width;
        }
    }

    if (m_cursorX != x)
    {
        m_cursorX = x;
        setDirty(DIRTY_CONTENT);
    }
}

void Editor::moveCursorY(unsigned int y)
{
    if (m_cursorY == y)
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

    if (m_cursorY != y)
    {
        unsigned int scrollPos = m_scrollBar->getPos();
        m_cursorY = y;
        if (m_cursorY < scrollPos)
        {
            m_scrollBar->setPos(m_cursorY);
        }
        else
        {
            int viewLines = getViewLines();
            if (m_cursorY >= (scrollPos + viewLines))
            {
                m_scrollBar->setPos(m_cursorY - (viewLines - 1));
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
        moveCursorY(m_cursorY + dy);
    }

    if (dx != 0)
    {
        moveCursorX(m_cursorX + dx);
    }
    printf("Editor::moveCursorDelta: m_cursorX=%d, moveCursorY=%d\n", m_cursorX, m_cursorY);
}

void Editor::moveCursorXEnd()
{
    int width = m_buffer->getLineLength(m_cursorY);
    m_cursorX = width - 1;
    setDirty(DIRTY_CONTENT);
}

void Editor::moveCursorPage(int dir)
{
    int viewLines = getViewLines();

    moveCursorDelta(0, viewLines * dir);
}

void Editor::insert(wchar_t c)
{
    Line* line = m_buffer->getLine(m_cursorY);

    unsigned int textLen = line->text.length();
    if (m_cursorX > textLen)
    {
        if (textLen > 0)
        {
            m_cursorX = textLen;
        }
        else
        {
            m_cursorX = 0;
        }
    }
    printf("Editor::insert: m_cursorX=%u, textLen=%u\n", m_cursorX, textLen);

    line->text.insert(m_cursorX, 1, c);
    m_cursorX++;

    m_format->tokenise(line);

    setDirty(DIRTY_CONTENT);
}

void Editor::deleteAtCursor()
{
    Line* line = m_buffer->getLine(m_cursorY);
    line->text.erase(m_cursorX, 1);

    m_format->tokenise(line);

    setDirty(DIRTY_CONTENT);
}

void Editor::setInterfaceStatus(std::wstring message)
{
    // TODO: Which window?
    //((Vide*)m_ui)->setInterfaceStatus(message);
}

unsigned int Editor::getViewLines()
{
    FontHandle* textFont = ((Vide*)m_ui)->getTextFont();
    int charHeight = textFont->getPixelHeight(72);
    return m_setSize.height / charHeight;
}

