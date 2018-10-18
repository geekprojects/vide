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

using namespace std;
using namespace Frontier;

ViInterface::ViInterface(Editor* editor) : Interface(editor)
{
    setMode(MODE_NORMAL);
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

        case MODE_EX_COMMAND:
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

    char chr = inputMessage->event.key.chr;

    if (m_command.state == STATE_START || m_command.state == STATE_COUNT)
    {
        if (m_command.state == STATE_START)
        {
            m_command.count = 0;
        }

        if (isdigit(chr))
        {
            m_command.count *= 10;

            m_command.count += chr - '0';
            printf("ViInterface::keyNormal: STATE_START: count=%d\n", m_command.count);
            m_command.state = STATE_COUNT;
            return;
        }
        else
        {
            m_command.state = STATE_COMMAND;
            if (m_command.count == 0)
            {
                m_command.count = 1;
            }
        }
    }

    if (m_command.state == STATE_COMMAND)
    {
        m_command.command = chr;
        m_command.key = inputMessage->event.key.key;
        m_command.modifiers = inputMessage->event.key.modifiers;

        // Check for special cases we should handle straight away
        switch (m_command.command)
        {
            case '.': // Repeat previous command
            {
                int count = m_command.count;
                m_command = m_prevCommand;
                m_command.count *= count;
                m_command.state = STATE_EXEC;
                m_command.params = "";

                // TODO: Handle repeating insert commands
                if (m_command.type == TYPE_INSERT)
                {
                    printf("ViInterface::keyNormal: Repeating INSERT: %ls\n", m_command.edit.c_str());
                }
            } break;

            case L':': // Ex command
                setMode(MODE_EX_COMMAND);
                break;

            case L'i': // Insert
                setMode(MODE_INSERT);
                m_command.type = TYPE_INSERT;
                m_command.state = STATE_EDIT;
                break;

            case L'A':
                m_editor->moveCursorXEnd();
                m_editor->moveCursorDelta(1, 0, true);
                setMode(MODE_INSERT);
                m_command.type = TYPE_INSERT;
                m_command.state = STATE_EDIT;
                break;

            case L'I':
                m_editor->moveCursorX(0);
                setMode(MODE_INSERT);
                m_command.type = TYPE_INSERT;
                m_command.state = STATE_EDIT;
                break;

            case L'o':
                m_editor->insertLine();
                m_editor->moveCursorDelta(0, 1);
                m_editor->moveCursorX(0);
                setMode(MODE_INSERT);
                m_command.type = TYPE_INSERT;
                m_command.state = STATE_EDIT;
                break;

            case L'O':
                m_editor->moveCursorDelta(0, -1);
                m_editor->insertLine();
                m_editor->moveCursorDelta(0, 1);
                m_editor->moveCursorX(0);
                setMode(MODE_INSERT);
                m_command.type = TYPE_INSERT;
                m_command.state = STATE_EDIT;
                break;

            case L'd':
            case L'y':
                m_command.state = STATE_EXTRA;
                break;

            default:
                m_command.state = STATE_EXEC;
                break;
        }
    }
    else if (m_command.state == STATE_EXTRA)
    {
        switch (m_command.command)
        {
            case 'd':
            case 'y':
                printf("ViInterface::keyNormal: STATE_EXTRA: Extra char: %c\n", chr);
                m_command.params += chr;
                m_command.state = STATE_EXEC;
                break;
        }
    }

    if (m_command.state == STATE_EXEC)
    {
        printf("ViInterface::keyNormal: Executing '%c' %d times\n", m_command.command, m_command.count);
        int i;
        bool setPrev = false;
        bool continueRunning = true;

        for (i = 0; i < m_command.count && continueRunning; i++)
        {
            runCommand(setPrev, continueRunning);
        }

        m_command.state = STATE_START;
        if (setPrev)
        {
            m_prevCommand = m_command;
        }
    }
else if (m_command.state == STATE_EDIT)
{
            m_prevCommand = m_command;
}
}

bool ViInterface::runCommand(bool& setPrev, bool& continueRunning)
{
    setPrev = true;
    continueRunning = true;

    switch (m_command.command)
    {
        case L'x':
            m_editor->deleteAtCursor();
            m_command.type = TYPE_DELETE;
            break;

        case L'^':
            m_editor->moveCursorX(0);
            m_command.type = TYPE_CURSOR;
            break;

        case L'$':
            m_editor->moveCursorXEnd();
            m_command.type = TYPE_CURSOR;
            break;

        case L'j':
            m_editor->moveCursorDelta(0, 1);
            m_command.type = TYPE_CURSOR;
            setPrev = false;
            break;
        case L'k':
            m_editor->moveCursorDelta(0, -1);
            m_command.type = TYPE_CURSOR;
            setPrev = false;
            break;
        case L'h':
            m_editor->moveCursorDelta(-1, 0);
            m_command.type = TYPE_CURSOR;
            setPrev = false;
            break;
        case L'l':
            m_editor->moveCursorDelta(1, 0);
            m_command.type = TYPE_CURSOR;
            setPrev = false;
            break;

        case L'w':
        {
            Position pos = m_editor->findNextWord();
            m_editor->moveCursor(pos);
            m_command.type = TYPE_CURSOR;
            setPrev = false;
        } break;

        case L'e':
        {
            Position cursor = m_editor->getCursor();
            Position pos = cursor;
            LineToken* token = m_editor->getBuffer()->getToken(cursor);
            printf("ViInterface::runCommand: e: token=%p\n", token);

            if (token == NULL || token->isSpace || cursor.column == (token->column + token->text.length() - 1) )
            {
                printf("ViInterface::runCommand: e: Looking for next word...\n");
                pos = m_editor->findNextWord();
                printf("ViInterface::runCommand: e: pos: line=%u, col=%u\n", pos.line, pos.column);
                token = m_editor->getBuffer()->getToken(pos);
            }

            printf("ViInterface::runCommand: e: token(2)=%p\n", token);
            if (token != NULL)
            {
                pos.column = token->column + token->text.length() - 1;
                m_editor->moveCursor(pos);
            }
            m_command.type = TYPE_CURSOR;
            setPrev = false;
        } break;

        case L'b':
        {
            Position pos = m_editor->findPrevWord();
            m_editor->moveCursor(pos);
            m_command.type = TYPE_CURSOR;
            setPrev = false;
        } break;

        case L'd':
            if (m_command.params == "d")
            {
                m_editor->deleteLine();
                m_command.type = TYPE_DELETE;
            }
            else if (m_command.params == "w")
            {
                printf("DELETE WORD\n");
            }
            break;

        case L'J':
            m_editor->moveCursorXEnd();

            if (!iswspace(m_editor->getCharAtCursor()))
            {
                m_editor->moveCursorDelta(1, 0, true);
                m_editor->insert(L' ');
            }

            m_editor->joinLines();
            m_command.type = TYPE_OTHER;
            break;

        case L'y':
            printf("ViInterface::runCommand: YANKing %d lines\n", m_command.count);
            m_editor->copyToBuffer(m_command.count);
            continueRunning = false;
            m_command.type = TYPE_OTHER;
            break;

        case L'p':
            m_editor->pasteFromBuffer();
            m_command.type = TYPE_OTHER;
            break;

        default:
            switch (m_command.key)
            {
                case KC_F:
                    if (!!(m_command.modifiers & KMOD_CONTROL))
                    {
                        m_editor->moveCursorPage(1);
                        m_command.type = TYPE_CURSOR;
                        setPrev = false;
                    }
                    break;

                case KC_B:
                    if (!!(m_command.modifiers & KMOD_CONTROL))
                    {
                        m_editor->moveCursorPage(-1);
                        m_command.type = TYPE_CURSOR;
                        setPrev = false;
                    }
                    break;

                default:
                    keyCursor(m_command.key);
                    m_command.type = TYPE_CURSOR;
                    setPrev = false;
                    break;
            }
            break;
    }
    return true;
}

void ViInterface::keyInsert(Frontier::InputMessage* inputMessage)
{
    wchar_t c = inputMessage->event.key.chr;

    if (!inputMessage->event.key.direction)
    {
        return;
    }
    else if (inputMessage->event.key.key == KC_ESCAPE)
    {
        // Is there any logic to this?
        if (m_command.command == 'i' || m_command.command == 'I' || m_command.command == 'A')
        {
            m_editor->moveCursorDelta(-1, 0);
        }

        setMode(MODE_NORMAL);
        return;
    }
    else if (inputMessage->event.key.key == KC_RETURN)
    {
        m_editor->splitLine();
        m_editor->moveCursorDelta(0, 1);
        m_editor->moveCursorX(0);
        m_prevCommand.edit += '\n';
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
    cursor = keyCursor(inputMessage->event.key.key);
    if (cursor)
    {
        m_prevCommand.edit = L"";
        return;
    }

    if (iswprint(c))
    {
        m_prevCommand.edit += c;
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
        printf("ViInterface::keyCommand: COMMAND: %ls\n", m_exCommand.c_str());
        runExCommand(m_exCommand);
        setMode(MODE_NORMAL);
    }
    else if (inputMessage->event.key.key == KC_BACKSPACE)
    {
        if (m_exCommand.length() > 0)
        {
            m_exCommand = m_exCommand.substr(0, m_exCommand.length() - 1);
            updateStatus();
        }
    }
    else if (iswprint(inputMessage->event.key.chr))
    {
        m_exCommand += inputMessage->event.key.chr;
        updateStatus();
    }
}

bool ViInterface::keyCursor(uint32_t key)
{
    switch (key)
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
 
void ViInterface::runExCommand(wstring command)
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

    printf("ViInterface::runExCommand: isNumber=%d\n", isNumber);
    if (isNumber)
    {
        int n = atoi(number.c_str()) - 1;
        m_editor->moveCursorY(n);
        return;
    }

    if (command == L"w")
    {
        m_editor->save();
    }
}

void ViInterface::setMode(ViMode mode)
{
    m_mode = mode;

    switch (m_mode)
    {
        case MODE_NORMAL:
            m_command.state = STATE_START;
            m_command.type = TYPE_NONE;
            m_command.count = 0;
            m_command.command = 0;
            m_command.params = "";
            m_command.edit = L"";
            break;

        case MODE_EX_COMMAND:
            m_exCommand = L"";
            break;

        default:
            break;
    }
    updateStatus();
}

void ViInterface::updateStatus()
{
    switch (m_mode)
    {
        case MODE_NORMAL:
            m_editor->setInterfaceStatus(L"Normal");
            m_editor->setCursorType(CURSOR_BLOCK);
            break;
        case MODE_INSERT:
            m_editor->setInterfaceStatus(L"Insert");
            m_editor->setCursorType(CURSOR_BAR);
            break;
        case MODE_EX_COMMAND:
            m_editor->setInterfaceStatus(L"Command: " + m_exCommand);
            m_editor->setCursorType(CURSOR_BLOCK);
            break;
    }
}

