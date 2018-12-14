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

#ifndef __VIDE_PROJECT_WIDGET_H_
#define __VIDE_PROJECT_WIDGET_H_

#include "vide.h"
#include "project.h"
#include "ui/views/view.h"

#include <frontier/widgets/frame.h>
#include <frontier/widgets/scroller.h>
#include <frontier/widgets/list.h>

class Vide;
class Project;
class ProjectDirectory;

class ProjectView : public Frontier::Frame, public View
{
 private:
    Vide* m_vide;
    Project* m_project;
    Frontier::Scroller* m_scroller;
    Frontier::List* m_projectList;

    void addDirectory(Frontier::TreeListItem* parent, ProjectDirectory* dir);

    void onItemClicked(Frontier::ListItem* item);

 public:
    ProjectView(Vide* vide, Project* project);
    virtual ~ProjectView();

    virtual void update();

    virtual void init();
};

#endif
