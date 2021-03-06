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

#ifndef __VIDE_INTERFACES_VI_H_
#define __VIDE_INTERFACES_VI_H_

#include <vide/interface.h>
#include <vide/buffer.h>
#include <vide/editor.h>

enum ViMode
{
    MODE_NORMAL,
    MODE_INSERT,
    MODE_EX_COMMAND, // Extended command mode
    MODE_VISUAL,
    MODE_SEARCH,
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

#define RANGE_ALL -1

class ViInterface;
struct ViCommand;

typedef bool(ViInterface::*commandFunction_t)(ViCommand*);

struct ViCommandDefinition
{
    std::wstring name;
    uint32_t key;
    uint32_t modifiers;
    uint32_t flags;
    commandFunction_t func;
    commandFunction_t completeFunc;
    commandFunction_t undoFunc;
};

struct ViExCommandDefinition
{
    std::wstring name;
    commandFunction_t func;
};

struct ViCommand
{
    ViCommandDefinition* command;
    ViExCommandDefinition* exCommand;
    char chr; // HACK
    int count;

    std::wstring params;
    std::wstring edit;

    Position position;
    std::vector<Edit> edits;
    std::vector<Edit> repeatedEdits;

    bool isCopy;

    ViCommand()
    {
        command = NULL;
        exCommand = NULL;
        count = 0;
        params = L"";
        edit = L"";
        isCopy = false;
    }

    ViCommand(ViCommand* command)
    {
        this->command = command->command;
        this->exCommand = command->exCommand;
        this->chr = command->chr;
        this->count = command->count;
        this->params = command->params;
        this->edit = command->edit;
        this->position = command->position;
        this->edits = command->edits;
        this->isCopy = true;
    }

    void addEdits(std::vector<Edit> added)
    {
        for (Edit edit : added)
        {
            if (!isCopy)
            {
                edits.push_back(edit);
            }
            else
            {
                repeatedEdits.push_back(edit);
            }
        }
    }
};

class ViInterfacePlugin : public InterfacePlugin
{
 private:

 public:
    ViInterfacePlugin(Vide* vide);
    virtual ~ViInterfacePlugin();

    virtual Interface* createInterface(Editor* editor);
};

class ViInterface : public Interface
{
 protected:
    ViMode m_mode;

    // This stores the state of the current command in NORMAL mode
    ViCommandState m_state;
    ViCommand* m_command;

    std::vector<ViCommand*> m_prevCommands;
    std::vector<ViCommand*> m_redoCommands;

    // This stores the extended command
    std::wstring m_exCommand;

    // Search
    std::wstring m_prevSearch;
    std::wstring m_searchString;
    bool m_searchDirection;

    void keyNormal(Frontier::KeyEvent* keyEvent);
    void keyInsert(Frontier::KeyEvent* keyEvent);
    void keyCommand(Frontier::KeyEvent* keyEvent);
    void keyVisual(Frontier::KeyEvent* keyEvent);
    void keySearch(Frontier::KeyEvent* keyEvent);

    void insertChar(wchar_t c);

    bool runCommand(ViCommand* command);
    void runExCommand(std::wstring command);

    void setMode(ViMode mode);

 public:
    ViInterface(Editor* editor);
    virtual ~ViInterface();

    virtual void key(Frontier::KeyEvent* keyEvent);

    virtual CursorType getCursorType();
    virtual std::wstring getStatus();

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
    bool commandDeleteToEnd(ViCommand* command);

    bool commandYank(ViCommand* command);
    bool commandPaste(ViCommand* command);

    bool commandJoin(ViCommand* command);
    bool commandReplace(ViCommand* command);

    bool commandUndo(ViCommand* command);
    bool commandRepeat(ViCommand* command);
    bool commandEx(ViCommand* command);
    bool commandVisual(ViCommand* command);
    bool commandSearch(ViCommand* command);
    bool commandSearchBack(ViCommand* command);
    bool commandSearchNext(ViCommand* command);

    bool exCommandWrite(ViCommand* command);
    bool exCommandSubstitute(ViCommand* command);
};

extern ViCommandDefinition g_commands[];
extern ViExCommandDefinition g_exCommands[];

#endif
