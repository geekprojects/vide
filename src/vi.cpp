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

ViCommandDefinition g_commands[] =
{
    // Special commands
    {KC_PERIOD, KMOD_ANY, COMMAND_NO_REPEAT, &ViInterface::commandRepeat},
    {KC_COLON, KMOD_ANY, COMMAND_NO_REPEAT, &ViInterface::commandEx},

    // Insert commands
    {KC_I, KMOD_NONE,  COMMAND_INSERT, &ViInterface::commandNop, &ViInterface::commandMoveLeft},
    {KC_I, KMOD_SHIFT, COMMAND_INSERT, &ViInterface::commandInsertI, &ViInterface::commandMoveLeft},
    {KC_A, KMOD_NONE,  COMMAND_INSERT, &ViInterface::commandInserta},
    {KC_A, KMOD_SHIFT, COMMAND_INSERT, &ViInterface::commandInsertA, &ViInterface::commandMoveLeft},
    {KC_O, KMOD_NONE,  COMMAND_INSERT, &ViInterface::commandInserto},
    {KC_O, KMOD_SHIFT, COMMAND_INSERT, &ViInterface::commandInsertO},

    // Cursor commands
    {KC_DOLLAR,      KMOD_ANY, COMMAND_NO_REPEAT, &ViInterface::commandMoveEndOfLine},
    {KC_ASCIICIRCUM, KMOD_ANY, COMMAND_NO_REPEAT, &ViInterface::commandMoveStartOfLine},
    {KC_G,           KMOD_SHIFT, COMMAND_NO_REPEAT, &ViInterface::commandMoveEndOfFile},
    {KC_J,           KMOD_NONE, COMMAND_NO_REPEAT, &ViInterface::commandMoveDown},
    {KC_DOWN,        KMOD_NONE, COMMAND_NO_REPEAT, &ViInterface::commandMoveDown},
    {KC_K,           KMOD_NONE, COMMAND_NO_REPEAT, &ViInterface::commandMoveUp},
    {KC_UP,          KMOD_NONE, COMMAND_NO_REPEAT, &ViInterface::commandMoveUp},
    {KC_H,           KMOD_NONE, COMMAND_NO_REPEAT, &ViInterface::commandMoveLeft},
    {KC_LEFT,        KMOD_NONE, COMMAND_NO_REPEAT, &ViInterface::commandMoveLeft},
    {KC_L,           KMOD_NONE, COMMAND_NO_REPEAT, &ViInterface::commandMoveRight},
    {KC_RIGHT,       KMOD_NONE, COMMAND_NO_REPEAT, &ViInterface::commandMoveRight},
    {KC_W,           KMOD_NONE, COMMAND_NO_REPEAT, &ViInterface::commandMoveNextWord},
    {KC_E,           KMOD_NONE, COMMAND_NO_REPEAT, &ViInterface::commandMoveNextWordEnd},
    {KC_B,           KMOD_NONE, COMMAND_NO_REPEAT, &ViInterface::commandMoveWordStart},
    {KC_F,           KMOD_CONTROL, COMMAND_NO_REPEAT, &ViInterface::commandMovePageDown},
    {KC_B,           KMOD_CONTROL, COMMAND_NO_REPEAT, &ViInterface::commandMovePageUp},

    // Deletion
    {KC_X,           KMOD_NONE, COMMAND_NONE, &ViInterface::commandDeleteChar},
    {KC_D,           KMOD_NONE, COMMAND_HAS_PARAM, &ViInterface::commandDelete},

    // Copy & Paste
    {KC_Y,           KMOD_NONE, COMMAND_HAS_PARAM | COMMAND_SPECIAL_COUNT, &ViInterface::commandYank},
    {KC_P,           KMOD_NONE, COMMAND_NONE, &ViInterface::commandPaste},

    // Other text manipulation
    {KC_J,           KMOD_SHIFT, COMMAND_NONE, &ViInterface::commandJoin},

};

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
    if (m_state == STATE_START || m_state == STATE_COUNT)
    {
        if (m_state == STATE_START)
        {
            m_command.count = 0;
            m_command.params = "";
        }

        if (isdigit(chr))
        {
            m_command.count *= 10;

            m_command.count += chr - '0';
            printf("ViInterface::keyNormal: STATE_START: count=%d\n", m_command.count);
            m_state = STATE_COUNT;
            return;
        }
        else
        {

            m_state = STATE_COMMAND;
            if (m_command.count == 0)
            {
                m_command.count = 1;
            }
        }
    }

    if (m_state == STATE_COMMAND)
    {
        ViCommandDefinition* commandDefinition = NULL;
        unsigned int i;
        for (i = 0; i < sizeof(g_commands) / sizeof(ViCommandDefinition); i++)
        {
            ViCommandDefinition* def = &(g_commands[i]);
            if (def->key == inputMessage->event.key.key && (def->modifiers == KMOD_ANY || def->modifiers == inputMessage->event.key.modifiers))
            {
                commandDefinition = def;
            }
        }

        if (commandDefinition == NULL)
        {
            printf("Unknown command!\n");
            m_state = STATE_START;
return;
        }

        m_command.command = commandDefinition;
        m_command.chr = chr;

        if (!!(m_command.command->flags & COMMAND_HAS_PARAM))
        {
            m_state = STATE_PARAMS;
        }
        else
        {
            m_state = STATE_EXEC;
        }
    }
    else if (m_state == STATE_PARAMS)
    {
        printf("ViInterface::keyNormal: STATE_EXTRA: Extra char: %c\n", chr);
        m_command.params += chr;
        m_state = STATE_EXEC;
    }

    if (m_state == STATE_EXEC)
    {
        runCommand(&m_command);

        if (!(m_command.command->flags & COMMAND_NO_REPEAT))
        {
            m_prevCommand = m_command;
        }

        if (!(m_command.command->flags & COMMAND_INSERT))
        {
            printf("ViInterface::keyNormal: Returning to START state\n");
            m_state = STATE_START;
        }
        else
        {
            printf("ViInterface::keyNormal: Entering insert mode\n");
            m_state = STATE_EDIT;
            setMode(MODE_INSERT);
        }
    }
    else if (m_state == STATE_EDIT)
    {
        m_prevCommand = m_command;
    }
}

bool ViInterface::runCommand(ViCommand* command)
{
    printf("ViInterface::keyNormal: Executing '%c' %d times\n", command->command->key, command->count);
    int i;

    int count = command->count;
    if (!!(command->command->flags & COMMAND_INSERT) || !!(command->command->flags & COMMAND_SPECIAL_COUNT))
    {
        count = 1;
    }

    commandFunction_t func = command->command->func;
    for (i = 0; i < count; i++)
    {
        ((this)->*func)(command);
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
        if (m_command.command->completeFunc != NULL)
        {
            commandFunction_t func = m_command.command->completeFunc;
            ((this)->*func)(&m_command);
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
            m_state = STATE_START;
            //m_command.type = TYPE_NONE;
            m_command.count = 0;
            m_command.command = NULL;
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

bool ViInterface::commandNop(ViCommand* command)
{
printf("ViInterface::commandNop: here\n");
    return true;
}

bool ViInterface::commandInsertI(ViCommand* command)
{
    m_editor->moveCursorX(0);
    return true;
}

bool ViInterface::commandInsertA(ViCommand* command)
{
     m_editor->moveCursorXEnd();
     m_editor->moveCursorDelta(1, 0, true);
    return true;
}

bool ViInterface::commandInserta(ViCommand* command)
{
    m_editor->moveCursorDelta(1, 0, true);
    return true;
}

bool ViInterface::commandInserto(ViCommand* command)
{
    m_editor->insertLine();
    m_editor->moveCursorDelta(0, 1);
    m_editor->moveCursorX(0);
    return true;
}

bool ViInterface::commandInsertO(ViCommand* command)
{
    m_editor->moveCursorDelta(0, -1);
    m_editor->insertLine();
    m_editor->moveCursorDelta(0, 1);
    m_editor->moveCursorX(0);
    return true;
}

bool ViInterface::commandMoveEndOfLine(ViCommand* command)
{
    m_editor->moveCursorXEnd();
    return true;
}

bool ViInterface::commandMoveStartOfLine(ViCommand* command)
{
    m_editor->moveCursorX(0);
    return true;
}

bool ViInterface::commandMoveEndOfFile(ViCommand* command)
{
    m_editor->moveCursorYEnd();
    return true;
}

bool ViInterface::commandMoveDown(ViCommand* command)
{
    m_editor->moveCursorDelta(0, 1);
    return true;
}

bool ViInterface::commandMoveUp(ViCommand* command)
{
    m_editor->moveCursorDelta(0, -1);
    return true;
}

bool ViInterface::commandMoveLeft(ViCommand* command)
{
    m_editor->moveCursorDelta(-1, 0);
    return true;
}

bool ViInterface::commandMoveRight(ViCommand* command)
{
    m_editor->moveCursorDelta(1, 0);
    return true;
}

bool ViInterface::commandMoveNextWord(ViCommand* command)
{
    Position pos = m_editor->findNextWord();
    m_editor->moveCursor(pos);
    return true;
}

bool ViInterface::commandMoveNextWordEnd(ViCommand* command)
{
    Position cursor = m_editor->getCursor();
    Position pos = cursor;
    LineToken* token = m_editor->getBuffer()->getToken(cursor);
    printf("ViInterface::commandMoveNextWordEnd: e: token=%p\n", token);

    if (token == NULL || token->isSpace || cursor.column == (token->column + token->text.length() - 1) )
    {
        printf("ViInterface::commandMoveNextWordEnd: e: Looking for next word...\n");
        pos = m_editor->findNextWord();
        printf("ViInterface::commandMoveNextWordEnd: e: pos: line=%u, col=%u\n", pos.line, pos.column);
        token = m_editor->getBuffer()->getToken(pos);
    }

    printf("ViInterface::commandMoveNextWordEnd: e: token(2)=%p\n", token);
    if (token != NULL)
    {
        pos.column = token->column + token->text.length() - 1;
        m_editor->moveCursor(pos);
    }
    return true;
}

bool ViInterface::commandMoveWordStart(ViCommand* command)
{
    Position pos = m_editor->findPrevWord();
    m_editor->moveCursor(pos);
    return true;
}

bool ViInterface::commandMovePageDown(ViCommand* command)
{
    m_editor->moveCursorPage(1);
    return true;
}

bool ViInterface::commandMovePageUp(ViCommand* command)
{
    m_editor->moveCursorPage(-1);
    return true;
}

bool ViInterface::commandDeleteChar(ViCommand* command)
{
    m_editor->deleteAtCursor();
    return true;
}

bool ViInterface::commandDelete(ViCommand* command)
{

    if (command->params == "d")
    {
        m_editor->deleteLine();
    }
    else if (m_command.params == "w")
    {
        printf("DELETE WORD\n");
        printf("ViInterface::commandDelete: DELETE WORD\n");
    }

    return true;
}

bool ViInterface::commandYank(ViCommand* command)
{
    printf("ViInterface::commandYank: YANKing %d lines\n", m_command.count);
    m_editor->copyToBuffer(m_command.count);
    return true;
}

bool ViInterface::commandPaste(ViCommand* command)
{
    m_editor->pasteFromBuffer();
    return true;
}

bool ViInterface::commandJoin(ViCommand* command)
{
    m_editor->moveCursorXEnd();

    if (!iswspace(m_editor->getCharAtCursor()))
    {
        m_editor->moveCursorDelta(1, 0, true);
        m_editor->insert(L' ');
    }

    m_editor->joinLines();

    return true;
}

bool ViInterface::commandRepeat(ViCommand* command)
{
    printf("ViInterface::commandRepeat: Here!\n");

    if (m_prevCommand.command != NULL)
    {
        runCommand(&m_prevCommand);
    }

    return true;
}

bool ViInterface::commandEx(ViCommand* command)
{
    printf("ViInterface::commandEx: Here!\n");

    setMode(MODE_EX_COMMAND);

    return true;
}

