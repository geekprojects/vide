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


#include "vi.h"
#include "editor.h"

#include <wctype.h>

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
        for (i = 0; g_commands[i].key != 0 && g_commands[i].func != 0; i++)
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

        if (!(m_command.command->flags & COMMAND_INSERT))
        {
            printf("ViInterface::keyNormal: Returning to START state\n");

            if (!(m_command.command->flags & COMMAND_NO_REPEAT))
            {
                m_prevCommand = m_command;
            }

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

        m_prevCommand = m_command;

        setMode(MODE_NORMAL);
        return;
    }
    else if (inputMessage->event.key.key == KC_RETURN)
    {
        m_editor->splitLine();
        m_editor->moveCursorDelta(0, 1);
        m_editor->moveCursorX(0);
        m_command.edit += '\n';
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
        m_command.edit = L"";
        return;
    }

    if (iswprint(c))
    {
        m_command.edit += c;
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

wstring name = command;
size_t pos = command.find(' ');
if (pos != wstring::npos)
{
name = command.substr(0, pos);
}

    ViExCommandDefinition* commandDefinition = NULL;
    for (i = 0; g_exCommands[i].name != L"" && g_exCommands[i].func != NULL; i++)
    {
        ViExCommandDefinition* def = &(g_exCommands[i]);
        if (def->name == name)
        {
            commandDefinition = def;
        }
    }

    if (commandDefinition != NULL)
    {
        commandFunction_t func = commandDefinition->func;
        ((this)->*func)(&m_command);
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

