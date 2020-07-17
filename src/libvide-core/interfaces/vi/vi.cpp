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

#include <wctype.h>

using namespace std;
using namespace Geek;
using namespace Frontier;

VIDE_PLUGIN(ViInterfacePlugin);

ViInterfacePlugin::ViInterfacePlugin(Vide* vide) : InterfacePlugin(vide, "vi")
{
}

ViInterfacePlugin::~ViInterfacePlugin()
{
}


Interface* ViInterfacePlugin::createInterface(Editor* editor)
{
    return new ViInterface(editor);
}


ViInterface::ViInterface(Editor* editor) : Interface(editor)
{
    setMode(MODE_NORMAL);

    m_prevSearch = L"";
    m_searchString = L"";
}

ViInterface::~ViInterface()
{
}

void ViInterface::key(Frontier::KeyEvent* keyEvent)
{
    switch (m_mode)
    {
        case MODE_NORMAL:
            keyNormal(keyEvent);
            break;

        case MODE_INSERT:
            keyInsert(keyEvent);
            break;

        case MODE_EX_COMMAND:
            keyCommand(keyEvent);
            break;

        case MODE_VISUAL:
            keyVisual(keyEvent);
            break;

        case MODE_SEARCH:
            keySearch(keyEvent);
            break;

        default:
            break;
    }
}

void ViInterface::keyNormal(Frontier::KeyEvent* keyEvent)
{
    if (!keyEvent->direction)
    {
        return;
    }

    char chr = keyEvent->chr;
    if (m_state == STATE_START || m_state == STATE_COUNT)
    {
        if (m_state == STATE_START)
        {
            m_command = new ViCommand();
        }

        if (isdigit(chr))
        {
            m_command->count *= 10;

            m_command->count += chr - '0';
            printf("ViInterface::keyNormal: STATE_START: count=%d\n", m_command->count);
            m_state = STATE_COUNT;
            return;
        }
#if 0
        else if (chr == '%')
        {
            if (m_command->count != 0)
            {
                printf("ViInterface::keyNormal: count is not 0!\n");
            }
            m_command->count = RANGE_ALL;
            m_state = STATE_COMMAND;
            return;
        }
#endif
        else
        {

            m_state = STATE_COMMAND;
            if (m_command->count == 0)
            {
                m_command->count = 1;
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
            if (def->key == keyEvent->key &&
                (def->modifiers == KMOD_ANY || def->modifiers == keyEvent->modifiers))
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

        m_command->command = commandDefinition;
        m_command->chr = chr;

        if (!!(m_command->command->flags & COMMAND_HAS_PARAM))
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
        m_command->params += chr;
        m_state = STATE_EXEC;
    }

    if (m_state == STATE_EXEC)
    {
        m_command->position = m_editor->getCursorPosition();
        runCommand(m_command);

        if (!(m_command->command->flags & COMMAND_INSERT))
        {
            printf("ViInterface::keyNormal: Returning to START state\n");

            if (!(m_command->command->flags & COMMAND_NO_REPEAT))
            {
                m_prevCommands.push_back(m_command);
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
        m_prevCommands.push_back(m_command);
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

void ViInterface::keyInsert(Frontier::KeyEvent* keyEvent)
{
    wchar_t c = keyEvent->chr;

    if (!keyEvent->direction)
    {
        return;
    }


    switch (keyEvent->key)
    {
        case KC_ESCAPE:
            if (m_command->command->completeFunc != NULL)
            {
                commandFunction_t func = m_command->command->completeFunc;
                ((this)->*func)(m_command);
            }

            m_prevCommands.push_back(m_command);

            setMode(MODE_NORMAL);
            break;

        case KC_BACKSPACE:
            if (m_editor->getCursorX() > 0)
            {
                bool eol = m_editor->isCursorAtEndOfLine();
                m_editor->moveCursorDelta(-1, 0, true);
                m_command->addEdits(m_editor->deleteAtCursor());
                if (eol)
                {
                    m_editor->moveCursorDelta(1, 0, true);
                }
            }
            break;

        case KC_PAGE_DOWN:
            m_editor->moveCursorPage(1);
            m_command->edit = L"";
            break;

        case KC_PAGE_UP:
            m_editor->moveCursorPage(-1);
            m_command->edit = L"";
            break;

        case KC_UP:
            m_editor->moveCursorDelta(0, -1);
            m_command->edit = L"";
            break;

        case KC_DOWN:
            m_editor->moveCursorDelta(0, 1);
            m_command->edit = L"";
            break;

        case KC_LEFT:
            m_editor->moveCursorDelta(-1, 0);
            m_command->edit = L"";
            break;

        case KC_RIGHT:
            m_editor->moveCursorDelta(1, 0);
            m_command->edit = L"";
            break;

        case KC_RETURN:
            c = L'\n';
            // Fall through!
        default:
            insertChar(c);
            break;
    }
}

void ViInterface::insertChar(wchar_t c)
{
    if (c == L'\n')
    {
        m_command->addEdits(m_editor->splitLine());
        m_editor->moveCursorDelta(0, 1);
        m_editor->moveCursorX(0);
        m_command->edit += '\n';
    }
    else if (iswprint(c))
    {
        m_command->edit += c;
        m_command->addEdits(m_editor->insert(c));
        m_editor->moveCursorDelta(1, 0, true);
    }
}

void ViInterface::keyCommand(Frontier::KeyEvent* keyEvent)
{
    if (!keyEvent->direction)
    {
        return;
    }

    if (keyEvent->key == KC_ESCAPE)
    {
        setMode(MODE_NORMAL);
    }
    else if (keyEvent->key == KC_RETURN)
    {
        printf("ViInterface::keyCommand: COMMAND: %ls\n", m_exCommand.c_str());
        runExCommand(m_exCommand);
        setMode(MODE_NORMAL);
    }
    else if (keyEvent->key == KC_BACKSPACE)
    {
        if (m_exCommand.length() > 0)
        {
            m_exCommand = m_exCommand.substr(0, m_exCommand.length() - 1);
        }
    }
    else if (iswprint(keyEvent->chr))
    {
        m_exCommand += keyEvent->chr;
    }
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

    if (command.at(0) == '%')
    {
        printf("ViInterface::runExCommand: Range: ALL\n");
        command = command.substr(1);
    }
    printf("ViInterface::runExCommand: command=%ls\n", command.c_str());

    wstring name = command;
    size_t pos = wstring::npos;
    for (i = 0; i < command.length(); i++)
    {
        if (!iswalpha(command.at(i)))
        {
            pos = i;
            break;
        }
    }
    if (pos != wstring::npos)
    {
        name = command.substr(0, pos);
command = command.substr(pos);
    }
    printf("ViInterface::runExCommand: name=%ls, command=%ls\n", name.c_str(), command.c_str());
m_command->params = command;

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
        ((this)->*func)(m_command);
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
            m_command = new ViCommand();
            break;

        case MODE_EX_COMMAND:
            m_exCommand = L"";
            break;

        default:
            break;
    }
}

CursorType ViInterface::getCursorType()
{
    switch (m_mode)
    {
        case MODE_NORMAL:
            return CURSOR_BLOCK;
        case MODE_INSERT:
            return CURSOR_BAR;
        case MODE_EX_COMMAND:
            return CURSOR_BLOCK;
        default:
            return CURSOR_BLOCK;
    }
}

wstring ViInterface::getStatus()
{
    switch (m_mode)
    {
        case MODE_NORMAL:
            return L"Normal";
        case MODE_INSERT:
            return L"Insert";
        case MODE_EX_COMMAND:
            return L"Command: " + m_exCommand;
        case MODE_VISUAL:
            return L"Visual";
        case MODE_SEARCH:
            return L"Search: " + m_searchString;
    }
    return L"";
}



