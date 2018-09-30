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


#include "projectview.h"

using namespace std;
using namespace Frontier;

static std::wstring string2wstring(const std::string &s)
{
    std::wstring ws(s.begin(), s.end());
    return ws;
}

ProjectView::ProjectView(Vide* vide) : Frame(vide, false)
{
    m_vide = vide;
    m_margin = 0;
}

ProjectView::~ProjectView()
{
}

void ProjectView::init()
{
printf("ProjectView::init: m_vide=%p\n", m_vide);

    m_projectList = new List(m_vide);
    m_scroller = new Scroller(m_vide, m_projectList);
    Label* projectLabel = new Label(m_vide, L"Project", ALIGN_LEFT);
    projectLabel->setMargin(2);
    add(projectLabel);
    add(m_scroller);
/*
*/
}

void ProjectView::update()
{
    TreeListItem* rootItem = new TreeListItem(m_vide, L"Project");
    m_projectList->addItem(rootItem);

    Project* project = m_vide->getProject();
    ProjectDirectory* root = project->getRoot();
    addDirectory(rootItem, root);
}

void ProjectView::addDirectory(TreeListItem* parent, ProjectDirectory* dir)
{
    for (ProjectEntry* entry : dir->getChildren())
    {
        ListItem* item = NULL;
        switch (entry->getType())
        {
            case ENTRY_FILE:
                item = new TextListItem(m_vide, FRONTIER_ICON_FILE, string2wstring(entry->getName()));
                break;

            case ENTRY_DIR:
            {
                TreeListItem* treeItem = new TreeListItem(m_vide, FRONTIER_ICON_FOLDER, string2wstring(entry->getName()));

                addDirectory(treeItem, (ProjectDirectory*)entry);

                item = treeItem;
            } break;

            default:
                // Skip
                break;

        }
        if (item != NULL)
        {
            item->setPrivateData(entry);
            parent->addItem(item);
        }
    }
}

