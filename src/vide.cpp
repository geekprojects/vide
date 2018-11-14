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


#include "vide.h"

using namespace std;
using namespace Frontier;

Vide::Vide(string projectDir) : FrontierApp(L"Vide")
{
    m_projectDir = projectDir;
}

Vide::~Vide()
{
}

bool Vide::init()
{
    bool res;
    res = FrontierApp::init();
    if (!res)
    {
        return false;
    }

    m_textFont = getFontManager()->openFont(
        "Hack",
        "Regular",
        //36);
        10);
    if (m_textFont == NULL)
    {
        printf("Vide::init: Failed to find font: Hack\n");
        return false;
    }

    m_project = new Project(m_projectDir);
    m_project->scan();
    m_project->index();

    m_mainWindow = new VideWindow(this);

    m_mainWindow->show();

    return true;
}

