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

#ifndef __VIDE_VIDE_H_
#define __VIDE_VIDE_H_

#include <frontier/frontier.h>
#include <frontier/widgets.h>

#include "ui/videwindow.h"
#include "ui/welcomewindow.h"
#include "filetypes/filetypemanager.h"
#include "project.h"

class VideWindow;
class WelcomeWindow;
class VidePluginManager;

class Vide : public Frontier::FrontierApp
{
 private:
    WelcomeWindow* m_welcomeWindow;

    VidePluginManager* m_pluginManager;

    std::vector<FileTypeManager*> m_fileTypeManagers;

    std::vector<VideWindow*> m_videWindows;
    FontHandle* m_textFont;

    std::vector<std::wstring> m_buffer;

    sigc::signal<void, Project*> m_openProjectSignal;

 public:
    Vide();
    virtual ~Vide();

    virtual bool init();

    void registerFileTypeManager(FileTypeManager* ftm);
    FileTypeManager* findFileTypeManager(ProjectFile* file);

    FontHandle* getTextFont() { return m_textFont; }

    void setBuffer(std::vector<std::wstring> buffer) { m_buffer = buffer; }
    std::vector<std::wstring> getBuffer() { return m_buffer; }

    void showWelcomeWindow();
    void hideWelcomeWindow();

    bool openProject(std::string path);
    VideWindow* getProjectWindow(Project* project);

    // Hooks for plugins
    sigc::signal<void, Project*> openProjectSignal() { return m_openProjectSignal; }
};

#endif
