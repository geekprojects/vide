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

#ifndef __VIDE_VIDEWINDOW_H_
#define __VIDE_VIDEWINDOW_H_

#include <frontier/frontier.h>
#include <frontier/widgets.h>

#include "editor.h"
#include "projectview.h"

class Vide;
class ProjectEntry;
class ProjectView;

class VideWindow : public Frontier::FrontierWindow
{
 private:
    Vide* m_vide;
    Frontier::Tabs* m_tabs;
    FontHandle* m_textFont;
    Frontier::Label* m_interfaceStatus;
    ProjectView* m_projectView;

    void onOpenFile();

    void onEditorTabChange(Frontier::Widget* widget);

    virtual bool init();

 public:
    VideWindow(Vide* app);
    ~VideWindow();

    FontHandle* getTextFont() { return m_textFont; }

    void setInterfaceStatus(std::wstring message);

    void openEntry(ProjectEntry* entry);
};

#endif
