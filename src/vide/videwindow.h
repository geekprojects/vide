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
#include <frontier/widgets/label.h>
#include <frontier/widgets/tabs.h>
#include <frontier/widgets/resizeableframe.h>

#include "views/editorview.h"
#include "views/projectview.h"
#include "views/structureview.h"
#include "views/tasksview.h"
#include "editortipwindow.h"

class Vide;
class ProjectEntry;
class ProjectView;
class TasksView;

class VideWindow : public Frontier::FrontierWindow
{
 private:
    VideApp* m_vide;
    Project* m_project;

    Frontier::Tabs* m_leftTabs;
    Frontier::Tabs* m_rightTabs;
    FontHandle* m_textFont;
    Frontier::Label* m_editorStatus;
    Frontier::Label* m_interfaceStatus;

    Frontier::ResizeableFrame* m_contentFrame;
    std::vector<Frontier::Tabs*> m_editorTabs;
    Frontier::Tabs* m_activeEditorTabs;

    ProjectView* m_projectView;
    StructureView* m_structureView;
    StructureView* m_fileStructureView;
    TasksView* m_tasksView;

    EditorTipWindow* m_editorTipWindow;

    void onOpenFile();

    void onEditorTabChange(Frontier::Widget* widget);
    void onCloseTab(Frontier::Widget* tab);
    void onSplitHorizontally(Frontier::MenuItem* item);

    virtual bool init();

 public:
    VideWindow(VideApp* app, Project* project);
    ~VideWindow();

    FontHandle* getTextFont() { return m_textFont; }

    void setEditorStatus(std::wstring message);
    void setInterfaceStatus(std::wstring message);

    EditorTipWindow* getEditorTipWindow() { return m_editorTipWindow; }

    Project* getProject() { return m_project; }
    Editor* openEntry(ProjectEntry* entry);
    Editor* openEntry(ProjectEntry* entry, Position pos);
    void closeEntry(ProjectEntry* entry);
};

#endif
