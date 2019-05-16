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
#include <vide/re.h>

using namespace std;
using namespace Frontier;

ViExCommandDefinition g_exCommands[] =
{
    {L"w", &ViInterface::exCommandWrite},
    {L"s", &ViInterface::exCommandSubstitute},
    {L"", NULL}
};

bool ViInterface::exCommandWrite(ViCommand* command)
{
    printf("ViInterface::exCommandWrite: Here!!\n");

    m_editor->save();

    return true;
}

bool ViInterface::exCommandSubstitute(ViCommand* command)
{
    wchar_t sep = command->params.at(0);
    printf("ViInterface::exCommandSubstitute: Separator: %lc\n", sep);

    vector<wstring> parts;
    size_t i;
    wstring part = L"";
    for (i = 1; i < command->params.length(); i++)
    {
        wchar_t c = command->params.at(i);
        if (c == sep)
        {
            parts.push_back(part);
            part = L"";
        }
        else
        {
            part += c;
        }
    }

    if (part.length() > 0)
    {
        parts.push_back(part);
    }

    for (wstring p : parts)
    {
        printf("ViInterface::exCommandSubstitute: Part: %ls\n", p.c_str());
    }

    wstring pattern = parts.at(0);
    wstring subst = parts.at(1);

    RegularExpression re;
    bool res = re.compile(pattern);
    if (!res)
    {
        printf("ViInterface::exCommandSubstitute: Invalid pattern: %ls\n", pattern.c_str());
        return false;
    }

    for (i = 0; i < m_editor->getBuffer()->getLineCount(); i++)
    {
        Line* line = m_editor->getBuffer()->getLine(i);
        printf("ViInterface::exCommandSubstitute: line: %ls\n", line->text.c_str());

        wstring out = re.replace(line->text, subst);
        printf("ViInterface::exCommandSubstitute: Out: %ls\n", out.c_str());
        line->text = out;
        m_editor->getBuffer()->setDirtyLine(line);
    }

    return true;
}

