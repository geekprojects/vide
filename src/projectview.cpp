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
    m_projectList = new List(m_vide);
    m_scroller = new Scroller(m_vide, m_projectList);
    add(m_scroller);
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
            parent->addItem(item);
                break;

            case ENTRY_DIR:
            {
                TreeListItem* treeItem = new TreeListItem(m_vide, FRONTIER_ICON_FOLDER, string2wstring(entry->getName()));
                parent->addItem(treeItem);

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
            item->clickSignal().connect(sigc::mem_fun(*this, &ProjectView::onItemClicked));
        }
    }
}

void ProjectView::onItemClicked(Frontier::ListItem* item)
{
    ProjectEntry* entry = (ProjectEntry*)item->getPrivateData();
    if (entry == NULL)
    {
        return;
    }

    printf("ProjectView::onItemClicked: entry=%s\n", entry->getName().c_str());
    if (entry->getType() == ENTRY_FILE)
    {
        m_vide->getWindow()->openEntry(entry);
    }
}


