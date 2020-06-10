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


#include "videapp.h"
#include "welcomewindow.h"
#include "settingswindow.h"
#include <vide/plugins.h>

#include <sys/stat.h>
#include <unistd.h>

#define PROJECT_FILE ".vide"

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Core;

VideApp::VideApp(Vide* vide) : FrontierApp(L"VideApp")
{
    m_vide = vide;
    m_settingsWindow = NULL;
}

VideApp::~VideApp()
{
}

bool VideApp::init()
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
        9);
    if (m_textFont == NULL)
    {
        FrontierApp::log(ERROR, "init: Failed to find font: Hack");
        return false;
    }

    m_textIconFont = getFontManager()->openFont(
        "Font Awesome 5 Free",
        "Solid",
        9);
    if (m_textIconFont == NULL)
    {
        FrontierApp::log(ERROR, "init: Failed to find font: Font Awesome");
        return false;
    }

    m_welcomeWindow = new WelcomeWindow(this);

    m_vide->openProjectSignal().connect(sigc::mem_fun(*this, &VideApp::onOpenProject));

    return true;
}

void VideApp::showWelcomeWindow()
{
    m_welcomeWindow->show();
}

void VideApp::hideWelcomeWindow()
{
    m_welcomeWindow->hide();
}

void VideApp::showSettingsWindow(MenuItem* item)
{
    if (m_settingsWindow == NULL)
    {
        m_settingsWindow = new SettingsWindow(this);
    }
    m_settingsWindow->show();
}

VideWindow* VideApp::getProjectWindow(Project* project)
{
    for (VideWindow* vw: m_videWindows)
    {
        if (vw->getProject() == project)
        {
            return vw;
        }
    }
    return NULL;
}

void VideApp::onOpenProject(Project* project)
{
log(DEBUG, "onOpenProject: Here!");
    VideWindow* window = new VideWindow(this, project);
    m_videWindows.push_back(window);

log(DEBUG, "onOpenProject: Opening window...");
    window->show();
}

Frontier::Icon* VideApp::getFileTypeIcon(FileTypeIcon fti)
{
    Icon* icon = NULL;
    switch (fti.type)
    {
        case ICON_ICON:
            icon = getTheme()->getIcon(fti.icon);
            break;
        case ICON_SURFACE:
            icon = new SurfaceIcon(getTheme(), fti.surface);
            break;
    }
    return icon;
}

