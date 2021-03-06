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

#ifndef __VIDE_VIDE_APP_H_
#define __VIDE_VIDE_APP_H_

#include <vide/vide.h>
#include <vide/filetypemanager.h>
#include <vide/buildtool.h>
#include <vide/project.h>

#include <frontier/frontier.h>
#include <frontier/widgets.h>

#include "videwindow.h"
#include "welcomewindow.h"

class SettingsWindow;
class VideWindow;
class WelcomeWindow;
class VidePluginManager;
class BuildTool;

class VideApp : public Frontier::FrontierApp
{
 private:
    Vide* m_vide;

    WelcomeWindow* m_welcomeWindow;
    SettingsWindow* m_settingsWindow;

    std::vector<VideWindow*> m_videWindows;
    Geek::FontHandle* m_textFont;
    Geek::FontHandle* m_textIconFont;

    void onOpenProject(Project* project);

 public:
    VideApp(Vide* vide);
    virtual ~VideApp();

    virtual bool init();

    Vide* getVide() { return m_vide; }

    Geek::FontHandle* getTextFont() { return m_textFont; }
    Geek::FontHandle* getTextIconFont() { return m_textIconFont; }

    void showWelcomeWindow();
    void hideWelcomeWindow();

    void showSettingsWindow(Frontier::MenuItem* item = NULL);

    VideWindow* getProjectWindow(Project* project);

    Frontier::Icon* getFileTypeIcon(FileTypeIcon fti);
};

#endif
