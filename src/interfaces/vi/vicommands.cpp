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


    // End of the list
    {0,              KMOD_NONE, COMMAND_NONE, NULL}
};

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

