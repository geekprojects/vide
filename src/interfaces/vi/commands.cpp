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
using namespace Frontier;

ViCommandDefinition g_commands[] =
{
    // Special commands
    {L"Undo",       KC_U, KMOD_NONE, COMMAND_NO_REPEAT, &ViInterface::commandUndo},
    {L"Repeat",     KC_PERIOD, KMOD_ANY, COMMAND_NO_REPEAT, &ViInterface::commandRepeat},
    {L"Ex Command", KC_COLON, KMOD_ANY, COMMAND_NO_REPEAT, &ViInterface::commandEx},
    {L"Visual",     KC_V, KMOD_NONE, COMMAND_NO_REPEAT, &ViInterface::commandVisual},
    {L"Search",     KC_SLASH, KMOD_NONE, COMMAND_NO_REPEAT, &ViInterface::commandSearch},
    {L"SearchBack", KC_QUESTION, KMOD_ANY, COMMAND_NO_REPEAT, &ViInterface::commandSearchBack},

    // Insert commands
    {L"Insert", KC_I, KMOD_NONE,  COMMAND_INSERT, &ViInterface::commandNop, &ViInterface::commandMoveLeft},
    {L"Insert", KC_I, KMOD_SHIFT, COMMAND_INSERT, &ViInterface::commandInsertI, &ViInterface::commandMoveLeft},
    {L"Insert", KC_A, KMOD_NONE,  COMMAND_INSERT, &ViInterface::commandInserta},
    {L"Insert", KC_A, KMOD_SHIFT, COMMAND_INSERT, &ViInterface::commandInsertA, &ViInterface::commandMoveLeft},
    {L"Insert", KC_O, KMOD_NONE,  COMMAND_INSERT, &ViInterface::commandInserto},
    {L"Insert", KC_O, KMOD_SHIFT, COMMAND_INSERT, &ViInterface::commandInsertO},
    {L"Insert", KC_C, KMOD_SHIFT, COMMAND_INSERT, &ViInterface::commandDeleteToEnd},

    // Cursor commands
    {L"EndOfLine",     KC_DOLLAR,      KMOD_ANY, COMMAND_NO_REPEAT, &ViInterface::commandMoveEndOfLine},
    {L"StartOfLine",   KC_ASCIICIRCUM, KMOD_ANY, COMMAND_NO_REPEAT, &ViInterface::commandMoveStartOfLine},
    {L"EndOfFile",     KC_G,           KMOD_SHIFT, COMMAND_NO_REPEAT, &ViInterface::commandMoveEndOfFile},
    {L"MoveDown",      KC_J,           KMOD_NONE, COMMAND_NO_REPEAT, &ViInterface::commandMoveDown},
    {L"MoveDown",      KC_DOWN,        KMOD_NONE, COMMAND_NO_REPEAT, &ViInterface::commandMoveDown},
    {L"MoveUp",        KC_K,           KMOD_NONE, COMMAND_NO_REPEAT, &ViInterface::commandMoveUp},
    {L"MoveUp",        KC_UP,          KMOD_NONE, COMMAND_NO_REPEAT, &ViInterface::commandMoveUp},
    {L"MoveLeft",      KC_H,           KMOD_NONE, COMMAND_NO_REPEAT, &ViInterface::commandMoveLeft},
    {L"MoveLeft",      KC_LEFT,        KMOD_NONE, COMMAND_NO_REPEAT, &ViInterface::commandMoveLeft},
    {L"MoveRight",     KC_L,           KMOD_NONE, COMMAND_NO_REPEAT, &ViInterface::commandMoveRight},
    {L"MoveRight",     KC_RIGHT,       KMOD_NONE, COMMAND_NO_REPEAT, &ViInterface::commandMoveRight},
    {L"MoveWord",      KC_W,           KMOD_NONE, COMMAND_NO_REPEAT, &ViInterface::commandMoveNextWord},
    {L"MoveWordEnd",   KC_E,           KMOD_NONE, COMMAND_NO_REPEAT, &ViInterface::commandMoveNextWordEnd},
    {L"MoveWordStart", KC_B,           KMOD_NONE, COMMAND_NO_REPEAT, &ViInterface::commandMoveWordStart},
    {L"MovePageDown",  KC_F,           KMOD_CONTROL, COMMAND_NO_REPEAT, &ViInterface::commandMovePageDown},
    {L"MovePageUp",    KC_B,           KMOD_CONTROL, COMMAND_NO_REPEAT, &ViInterface::commandMovePageUp},

    // Deletion
    {L"DeleteChar",  KC_X,           KMOD_NONE, COMMAND_NONE, &ViInterface::commandDeleteChar},
    {L"Delete",      KC_D,           KMOD_NONE, COMMAND_HAS_PARAM, &ViInterface::commandDelete},
    {L"DeleteToEnd", KC_D,           KMOD_SHIFT, COMMAND_NONE, &ViInterface::commandDeleteToEnd},

    // Copy & Paste
    {L"Yank",  KC_Y,           KMOD_NONE, COMMAND_HAS_PARAM | COMMAND_SPECIAL_COUNT, &ViInterface::commandYank},
    {L"Paste", KC_P,           KMOD_NONE, COMMAND_NONE, &ViInterface::commandPaste},

    // Other text manipulation
    {L"Join", KC_J,           KMOD_SHIFT, COMMAND_NONE, &ViInterface::commandJoin},
    {L"Replace", KC_R,           KMOD_NONE, COMMAND_HAS_PARAM, &ViInterface::commandReplace},

    {L"SearchNext", KC_N, KMOD_NONE, COMMAND_NONE, &ViInterface::commandSearchNext},


    // End of the list
    {L"", 0,              KMOD_NONE, COMMAND_NONE, NULL}
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
    command->addEdits(m_editor->insertLine());
    m_editor->moveCursorDelta(0, 1);
    m_editor->moveCursorX(0);
    return true;
}

bool ViInterface::commandInsertO(ViCommand* command)
{
    m_editor->moveCursorDelta(0, -1);
    command->addEdits(m_editor->insertLine());
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
    Position cursor = m_editor->getCursorPosition();
    Position pos = cursor;
    TokenAt at = m_editor->getBuffer()->getToken(cursor);
    printf("ViInterface::commandMoveNextWordEnd: e: token=%p\n", at.token);

    if (at.token == NULL || at.token->isSpace || cursor.column == (at.tokenColumn + at.token->text.length() - 1) )
    {
        printf("ViInterface::commandMoveNextWordEnd: e: Looking for next word...\n");
        pos = m_editor->findNextWord();
        printf("ViInterface::commandMoveNextWordEnd: e: pos: line=%u, col=%u\n", pos.line, pos.column);
        at = m_editor->getBuffer()->getToken(pos);
    }

    printf("ViInterface::commandMoveNextWordEnd: e: token(2)=%p\n", at.token);
    if (at.token != NULL)
    {
        pos.column = at.tokenColumn + at.token->text.length() - 1;
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
    command->addEdits(m_editor->deleteAtCursor());
    return true;
}

bool ViInterface::commandDelete(ViCommand* command)
{
    if (command->params == L"d")
    {
        command->addEdits(m_editor->deleteLine());
    }
    else if (command->params == L"w")
    {
        printf("DELETE WORD\n");
        printf("ViInterface::commandDelete: DELETE WORD\n");
    }

    return true;
}

bool ViInterface::commandDeleteToEnd(ViCommand* command)
{
    command->addEdits(m_editor->deleteToEnd());
    return true;
}

bool ViInterface::commandYank(ViCommand* command)
{
    printf("ViInterface::commandYank: YANKing %d lines\n", command->count);
    m_editor->copyToBuffer(command->count);
    return true;
}

bool ViInterface::commandPaste(ViCommand* command)
{
    command->addEdits(m_editor->pasteFromBuffer());
    return true;
}

bool ViInterface::commandJoin(ViCommand* command)
{
    m_editor->moveCursorXEnd();

    if (!iswspace(m_editor->getCharAtCursor()))
    {
        m_editor->moveCursorDelta(1, 0, true);
        command->addEdits(m_editor->insert(L' '));
    }

    command->addEdits(m_editor->joinLines());

    return true;
}

bool ViInterface::commandReplace(ViCommand* command)
{
    printf("ViInterface::commandReplace: param=%ls\n", command->params.c_str());
    if (command->params.length() > 0)
    {
        command->addEdits(m_editor->replaceChar(command->params.at(0)));
    }

    return true;
}

bool ViInterface::commandUndo(ViCommand* command)
{
    if (m_prevCommands.empty())
    {
        // Nothing to undo
        printf("ViInterface::commandUndo: Nothing to undo\n");
        return true;
    }

    ViCommand* undoCommand = m_prevCommands.back();
    m_redoCommands.push_back(undoCommand);
    m_prevCommands.pop_back();

    if (undoCommand == NULL)
    {
        return true;
    }

    printf("ViInterface::commandUndo: Undoing %ls (%lu edits)\n", undoCommand->command->name.c_str(), undoCommand->edits.size());

    m_editor->undoEdits(undoCommand->edits);

    return true;
}

bool ViInterface::commandRepeat(ViCommand* command)
{
    if (m_prevCommands.empty())
    {
        // Nothing to repeat
        printf("ViInterface::commandRepeat: Nothing to repeat\n");
        return true;
    }

    ViCommand* prevCommand = m_prevCommands.back();

    if (prevCommand == NULL)
    {
        return true;
    }

    ViCommand* repeatCommand = new ViCommand(prevCommand);
    repeatCommand->position = m_editor->getCursorPosition();
    m_prevCommands.push_back(repeatCommand);

    printf("ViInterface::commandRepeat: Repeating: %ls\n", repeatCommand->command->name.c_str());

    runCommand(repeatCommand);

    if (!!(repeatCommand->command->flags & COMMAND_INSERT))
    {
        unsigned int i;
        for (i = 0; i < repeatCommand->edit.length(); i++)
        {
            insertChar(repeatCommand->edit.at(i));
        }
        if (repeatCommand->command->completeFunc != NULL)
        {
            commandFunction_t func = repeatCommand->command->completeFunc;
            ((this)->*func)(repeatCommand);
        }
    }

    repeatCommand->edits = repeatCommand->repeatedEdits;

    return true;
}

bool ViInterface::commandEx(ViCommand* command)
{
    printf("ViInterface::commandEx: Here!\n");

    setMode(MODE_EX_COMMAND);

    return true;
}

bool ViInterface::commandVisual(ViCommand* command)
{
    setMode(MODE_VISUAL);
    m_editor->setSelectEnd(m_editor->getCursorPosition());
    return true;
}

