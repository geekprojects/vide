
#include "editor.h"
#include "vide.h"

using namespace std;
using namespace Frontier;
using namespace Geek::Gfx;

Editor::Editor(FrontierApp* ui) : Widget(ui)
{
    m_cursorX = 0;
    m_cursorY = 0;
}

Editor::~Editor()
{
}

void Editor::calculateSize()
{
    //m_minSize.set(50, 50);
    m_minSize.set(300, 300);
    m_maxSize.set(WIDGET_SIZE_UNLIMITED, WIDGET_SIZE_UNLIMITED);
}

bool Editor::draw(Surface* surface)
{
    FontManager* fm = m_ui->getFontManager();

    surface->clear(0x002b2b2b);

    FontHandle* textFont = ((Vide*)m_ui)->getTextFont();

    int charWidth = fm->width(textFont, L"M");
    int charHeight = textFont->getPixelHeight(72);

    vector<wstring> lines;
    lines.push_back(L"#include <stdio.h>");
    lines.push_back(L"");
    lines.push_back(L"int main(int argc, char** argv)");
    lines.push_back(L"{");
    lines.push_back(L"    printf(\"Hello, world!\\n\");");
    lines.push_back(L"    return 0;");
    lines.push_back(L"}");

    int drawX = 0;
    int drawY = 0;

    //surface->drawRectFilled(0, 0, 9, 12, 0x0000ff00);
    int ypos = 0;
    for (ypos = 0; ypos < lines.size(); ypos++)
    {
        if (drawY + charHeight > m_setSize.height)
        {
            break;
        }

        drawX = 0;
        int xpos = 0;
        wstring line = lines[ypos];
        for (xpos = 0; xpos < line.length(); xpos++)
        {
            if (drawX + charWidth > m_setSize.width)
            {
                break;
            }

            wstring str = L"";
            str =+ line.at(xpos);

            uint32_t textCol = 0x00BBBBBB;
            if (xpos == m_cursorX && ypos == m_cursorY)
            {
                surface->drawRectFilled(drawX, drawY, charWidth, charHeight, 0x00BBBBBB);
                textCol = 0x002b2b2b;
            }

            fm->write(textFont,
                surface,
                drawX + 1,
                drawY,
                str,
                textCol,
                true,
                NULL);

            drawX += charWidth;
        }

        drawY += charHeight;
    }

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
/*
                printf("Editor::handleMessage: Key press: 0x%x (%d) -> %lc\n",
                    inputMessage->event.key.key,
                    inputMessage->event.key.key,
                    inputMessage->event.key.chr);
*/
if (inputMessage->event.key.direction)
{
                switch (inputMessage->event.key.key)
                {
                    case KC_J:
                        m_cursorY++;
                        break;
                    case KC_K:
                        m_cursorY--;
                        break;
                    case KC_H:
                        m_cursorX--;
                        break;
                    case KC_L:
                        m_cursorX++;
                        break;
                }
                setDirty();
}
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

