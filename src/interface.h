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

enum ViCommandState
{
    STATE_START,
    STATE_COUNT,
    STATE_COMMAND,
    STATE_EXTRA,
    STATE_EDIT,
    STATE_EXEC
};

struct ViCommand
{
    ViCommandState state;
    int count;

    char type;
    uint32_t key;
    uint32_t modifiers;

    std::string extra;
};

class ViInterface : public Interface
{
 protected:
    ViMode m_mode;

    // This stores the state of the current command in NORMAL mode
    ViCommand m_command;
    ViCommand m_prevCommand;

    // This stores the extended command
    std::wstring m_exCommand;

    void keyNormal(Frontier::InputMessage* inputMessage);
    void keyInsert(Frontier::InputMessage* inputMessage);
    void keyCommand(Frontier::InputMessage* inputMessage);

    bool keyCursor(uint32_t key);

    bool runCommand(bool& setPrev);
    void runExCommand(std::wstring command);

    void setMode(ViMode mode);

 public:
    ViInterface(Editor* editor);
    virtual ~ViInterface();

    virtual void key(Frontier::InputMessage* inputMessage);

    virtual void updateStatus();
};

#endif
