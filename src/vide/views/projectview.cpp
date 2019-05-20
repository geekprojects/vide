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
using namespace Geek;
using namespace Geek::Gfx;

static std::wstring string2wstring(const std::string &s)
{
    std::wstring ws(s.begin(), s.end());
    return ws;
}

ProjectView::ProjectView(VideApp* vide, Project* project) : Frame(vide, L"ProjectView", false)
{
    m_vide = vide;
    m_project = project;
    m_margin = 0;

    m_projectList = new List(m_vide);
    m_scroller = new Scroller(m_vide, m_projectList);
    add(m_scroller);
}

ProjectView::~ProjectView()
{
}

void ProjectView::init()
{
}

void ProjectView::update()
{
if (m_projectList != NULL)
{
    TreeListItem* rootItem = new TreeListItem(m_vide, L"Project");
    rootItem->setOpen(true);
    m_projectList->addItem(rootItem);

    ProjectDirectory* root = m_project->getRoot();
    addDirectory(rootItem, root);
}
}

void ProjectView::addDirectory(TreeListItem* parent, ProjectDirectory* dir)
{
    for (ProjectEntry* entry : dir->getChildren())
    {
        ListItem* item = NULL;
        switch (entry->getType())
        {
            case ENTRY_FILE:
            {
                FileTypeIcon fti = entry->getFileTypeManager()->getIcon();
                Icon* icon = m_vide->getFileTypeIcon(fti);
                item = new TreeListItem(m_vide, icon, string2wstring(entry->getName()));
                parent->addItem(item);
            } break;

            case ENTRY_DIR:
            {
                TreeListItem* treeItem = new TreeListItem(
                    m_vide,
                    m_app->getTheme()->getIcon(FRONTIER_ICON_FOLDER),
                    string2wstring(entry->getName()));
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

    log(DEBUG, "onItemClicked: entry=%s", entry->getName().c_str());
    if (entry->getType() == ENTRY_FILE)
    {
        ((VideWindow*)getWindow())->openEntry(entry);
    }
}


