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
#include "ui/welcomewindow.h"

#define PROJECT_FILE "vide.project"

using namespace std;
using namespace Frontier;

Vide::Vide() : FrontierApp(L"Vide")
{
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

    m_welcomeWindow = new WelcomeWindow(this);
    m_welcomeWindow->show();

    return true;
}

void Vide::hideWelcomeWindow()
{
    m_welcomeWindow->hide();
}

bool Vide::openProject(string path)
{
    printf("Vide::openProject: path=%s\n", path.c_str());
    unsigned int len = path.length();
    unsigned int projectFileLen = strlen(PROJECT_FILE);
    if (len > projectFileLen && path.substr(len - projectFileLen) == PROJECT_FILE)
    {
        printf("Vide::openProject: Found project file\n");
        unsigned int len = path.length();
        path = path.substr(0, (len - projectFileLen));
        printf("Vide::openProject: path(2)=%s\n", path.c_str());
    }
    else
    {
        printf("Vide::openProject: No project file found\n");
        return false;
    }

    Project* project = new Project(path);
    project->scan();
    project->index();

    VideWindow* window = new VideWindow(this, project);

    window->show();

    m_videWindows.push_back(window);

    return true;
}

