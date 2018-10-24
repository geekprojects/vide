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

#ifndef __VIDE_INTERFACE_H_
#define __VIDE_INTERFACE_H_

#include <frontier/messages.h>

class Editor;

class Interface
{
 protected:

    Editor* m_editor;

 public:
    Interface(Editor* editor);
    virtual ~Interface();

    virtual void key(Frontier::InputMessage* inputMessage);

    virtual void updateStatus();
};

enum ViMode
{
    MODE_NORMAL,
    MODE_INSERT,
    MODE_EX_COMMAND, // Extended command mode
};

enum ViCommandType
{
    TYPE_NONE,
    TYPE_INSERT,
    TYPE_DELETE,
    TYPE_CURSOR,
    TYPE_OTHER,
};

enum ViCommandState
{
    STATE_START,
    STATE_COUNT,
    STATE_COMMAND,
    STATE_PARAMS,
    STATE_EDIT,
    STATE_EXEC
};

enum ViCommandDefinitionFlags
{
    COMMAND_NONE = 0x0,
    COMMAND_INSERT = 0x1,
    COMMAND_HAS_PARAM = 0x2,
    COMMAND_NO_REPEAT = 0x4,
    COMMAND_SPECIAL_COUNT = 0x8,
};

class ViInterface;
struct ViCommand;

typedef bool(ViInterface::*commandFunction_t)(ViCommand*);

struct ViCommandDefinition
{
    uint32_t key;
    uint32_t modifiers;
    uint32_t flags;
    commandFunction_t func;
    commandFunction_t completeFunc;
};

struct ViCommand
{
    ViCommandDefinition* command;
    char chr; // HACK
    int count;

    std::string params;
    std::wstring edit;
};

class ViInterface : public Interface
{
 protected:
    ViMode m_mode;

    // This stores the state of the current command in NORMAL mode
    ViCommandState m_state;
    ViCommand m_command;
    ViCommand m_prevCommand;

    // This stores the extended command
    std::wstring m_exCommand;

    void keyNormal(Frontier::InputMessage* inputMessage);
    void keyInsert(Frontier::InputMessage* inputMessage);
    void keyCommand(Frontier::InputMessage* inputMessage);

    bool keyCursor(uint32_t key);

    bool runCommand(ViCommand* command);
    void runExCommand(std::wstring command);

    void setMode(ViMode mode);

 public:
    ViInterface(Editor* editor);
    virtual ~ViInterface();

    virtual void key(Frontier::InputMessage* inputMessage);

    virtual void updateStatus();

    bool commandNop(ViCommand* command);
    bool commandInserti(ViCommand* command);
    bool commandInsertI(ViCommand* command);
    bool commandInsertA(ViCommand* command);
    bool commandInserta(ViCommand* command);
    bool commandInsertO(ViCommand* command);
    bool commandInserto(ViCommand* command);

    bool commandMoveEndOfLine(ViCommand* command);
    bool commandMoveStartOfLine(ViCommand* command);
    bool commandMoveEndOfFile(ViCommand* command);
    bool commandMoveDown(ViCommand* command);
    bool commandMoveUp(ViCommand* command);
    bool commandMoveLeft(ViCommand* command);
    bool commandMoveRight(ViCommand* command);
    bool commandMoveNextWord(ViCommand* command);
    bool commandMoveNextWordEnd(ViCommand* command);
    bool commandMoveWordStart(ViCommand* command);
    bool commandMovePageDown(ViCommand* command);
    bool commandMovePageUp(ViCommand* command);

    bool commandDeleteChar(ViCommand* command);
    bool commandDelete(ViCommand* command);

    bool commandYank(ViCommand* command);
    bool commandPaste(ViCommand* command);

    bool commandJoin(ViCommand* command);

    bool commandRepeat(ViCommand* command);
    bool commandEx(ViCommand* command);
};

#endif
