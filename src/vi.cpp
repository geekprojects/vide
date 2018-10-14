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


#include "interface.h"
#include "editor.h"

#include <wctype.h>

using namespace std;
using namespace Frontier;

ViInterface::ViInterface(Editor* editor) : Interface(editor)
{
    m_mode = MODE_NORMAL;
}

ViInterface::~ViInterface()
{
}

void ViInterface::key(Frontier::InputMessage* inputMessage)
{
    switch (m_mode)
    {
        case MODE_NORMAL:
            keyNormal(inputMessage);
            break;

        case MODE_INSERT:
            keyInsert(inputMessage);
            break;

        case MODE_COMMAND:
            keyCommand(inputMessage);
            break;

        default:
            break;
    }
}

void ViInterface::keyNormal(Frontier::InputMessage* inputMessage)
{
    if (!inputMessage->event.key.direction)
    {
        return;
    }

    switch (inputMessage->event.key.chr)
    {
        case L':':
            setMode(MODE_COMMAND);
            break;

        case L'i':
            setMode(MODE_INSERT);
            break;
        case L'A':
            m_editor->moveCursorXEnd();
            m_editor->moveCursorDelta(1, 0);
            setMode(MODE_INSERT);
            break;
        case L'I':
            m_editor->moveCursorX(0);
            setMode(MODE_INSERT);
            break;

        case L'x':
            m_editor->deleteAtCursor();
            break;

        case L'^':
            m_editor->moveCursorX(0);
            break;

        case L'$':
            m_editor->moveCursorXEnd();
            break;

        case L'j':
            m_editor->moveCursorDelta(0, 1);
            break;
        case L'k':
            m_editor->moveCursorDelta(0, -1);
            break;
        case L'h':
            m_editor->moveCursorDelta(-1, 0);
            break;
        case L'l':
            m_editor->moveCursorDelta(1, 0);
            break;

        default:
            switch (inputMessage->event.key.key)
            {
                case KC_F:
                    if (!!(inputMessage->event.key.modifiers & KMOD_CONTROL))
                    {
                        m_editor->moveCursorPage(1);
                    }
                    break;
                case KC_B:
                    if (!!(inputMessage->event.key.modifiers & KMOD_CONTROL))
                    {
                        m_editor->moveCursorPage(-1);
                    }
                    break;

                default:
                    keyCursor(inputMessage);
            }
            break;
    }
}

void ViInterface::keyInsert(Frontier::InputMessage* inputMessage)
{
    if (!inputMessage->event.key.direction)
    {
        return;
    }
    else if (inputMessage->event.key.key == KC_ESCAPE)
    {
        setMode(MODE_NORMAL);
        return;
    }
    else if (inputMessage->event.key.key == KC_BACKSPACE)
    {
        if (m_editor->getCursorX() > 0)
        {
            m_editor->moveCursorDelta(-1, 0);
            m_editor->deleteAtCursor();
        }
    }

    bool cursor;
    cursor = keyCursor(inputMessage);
    if (cursor)
    {
        return;
    }

    wchar_t c = inputMessage->event.key.chr;
    if (iswprint(c))
    {
        m_editor->insert(c);
    }
}

void ViInterface::keyCommand(Frontier::InputMessage* inputMessage)
{
    if (!inputMessage->event.key.direction)
    {
        return;
    }

    if (inputMessage->event.key.key == KC_ESCAPE)
    {
        setMode(MODE_NORMAL);
    }
    else if (inputMessage->event.key.key == KC_RETURN)
    {
        printf("ViInterface::keyCommand: COMMAND: %ls\n", m_command.c_str());
        runCommand(m_command);
        setMode(MODE_NORMAL);
    }
    else if (inputMessage->event.key.key == KC_BACKSPACE)
    {
        if (m_command.length() > 0)
        {
            m_command = m_command.substr(0, m_command.length() - 1);
            updateStatus();
        }
    }
    else if (iswprint(inputMessage->event.key.chr))
    {
        m_command += inputMessage->event.key.chr;
        updateStatus();
    }
}

bool ViInterface::keyCursor(InputMessage* inputMessage)
{
    switch (inputMessage->event.key.key)
    {
        case KC_PAGE_DOWN:
            m_editor->moveCursorPage(1);
            return true;

        case KC_PAGE_UP:
            m_editor->moveCursorPage(-1);
            return true;

        case KC_UP:
            m_editor->moveCursorDelta(0, -1);
            return true;

        case KC_DOWN:
            m_editor->moveCursorDelta(0, 1);
            return true;

        case KC_LEFT:
            m_editor->moveCursorDelta(-1, 0);
            return true;

        case KC_RIGHT:
            m_editor->moveCursorDelta(1, 0);
            return true;
    }
    return false;
}
 
void ViInterface::runCommand(wstring command)
{
    bool isNumber = true;
    size_t i;
    string number = "";
    for (i = 0; i < command.length(); i++)
    {
        wchar_t c = command.at(i);
        if (!iswdigit(c))
        {
            isNumber = false;
            break;
        }
        number += (char)c;
    }

    printf("ViInterface::runCommand: isNumber=%d\n", isNumber);
    if (isNumber)
    {
        int n = atoi(number.c_str()) - 1;
        m_editor->moveCursorY(n);
        return;
    }
}

void ViInterface::setMode(ViMode mode)
{
    m_mode = mode;
    if (m_mode == MODE_COMMAND)
    {
        m_command = L"";
    }
    updateStatus();
}

void ViInterface::updateStatus()
{
    switch (m_mode)
    {
        case MODE_NORMAL:
            m_editor->setInterfaceStatus(L"Normal");
            break;
        case MODE_INSERT:
            m_editor->setInterfaceStatus(L"Insert");
            break;
        case MODE_COMMAND:
            m_editor->setInterfaceStatus(L"Command: " + m_command);
            break;
    }
}

