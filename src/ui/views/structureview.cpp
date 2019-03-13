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

StructureView::StructureView(Vide* vide, bool fileView) : Frame(vide, L"StructureView", false)
{
    m_vide = vide;
    m_fileView = fileView;

    m_margin = 0;
}

StructureView::~StructureView()
{
}

void StructureView::init()
{
    m_structureList = new List(m_vide);
    m_scroller = new Scroller(m_vide, m_structureList);
    add(m_scroller);
}

void StructureView::update()
{
    m_structureList->clearItems();

    vector<ProjectDefinition*> defs;
    VideWindow* videWindow = (VideWindow*)getWindow();
    Project* project = videWindow->getProject();
    if (!m_fileView)
    {
        defs = project->getIndex()->getRootDefinitions();
    }
    else
    {
        if (m_projectFile == NULL)
        {
            return;
        }
        defs = project->getIndex()->getEntryDefinitions(m_projectFile);
    }

    for (ProjectDefinition* def : defs)
    {
        log(DEBUG, "update: def: %s", def->name.c_str());
        addDefinition(NULL, def);
    }
}

void StructureView::setProjectFile(ProjectFile* projectFile)
{
    m_projectFile = projectFile;
    update();
}

uint32_t typeToIcon(ProjectDefinitionType type)
{
    switch (type)
    {
        case DEF_NAMESPACE:
            return FRONTIER_ICON_GLOBE;
        case DEF_CLASS:
            return FRONTIER_ICON_COGS;

        default:
            return FRONTIER_ICON_COG;
    }
}

void StructureView::addDefinition(Frontier::TreeListItem* parent, ProjectDefinition* def)
{
    ProjectDefinitionSource fileSource;
    bool singleFileSource = false;
    if (m_fileView)
    {
        bool found = false;
        for (ProjectDefinitionSource source : def->sources)
        {
            if (source.entry == m_projectFile)
            {
                fileSource = source;
                found = true;
                break;
            }
        }
        if (!found)
        {
            return;
        }
        singleFileSource = true;
    }
    else if (def->sources.size() == 1)
    {
        fileSource = def->sources[0];
        singleFileSource = true;
    }

    wstring name = Utils::string2wstring(def->name);
    uint32_t icon = FRONTIER_ICON_CIRCLE;

    if (singleFileSource)
    {
        char linestr[32];
        snprintf(linestr, 32, "%u", fileSource.position.line);
        name += L" " + Utils::string2wstring(fileSource.entry->getName() + ":" + string(linestr));
        icon = typeToIcon(fileSource.type);
    }

    TreeListItem* item = new TreeListItem(m_vide, m_app->getTheme()->getIcon(icon), name);
    if (parent == NULL)
    {
        m_structureList->addItem(item);
    }
    else
    {
        parent->addItem(item);
    }

    if (singleFileSource)
    {
        ProjectDefinitionSource* src = new ProjectDefinitionSource();
        *src = fileSource;
        item->setPrivateData(src);
        item->clickSignal().connect(sigc::mem_fun(*this, &StructureView::onItemClicked));
    }

    if (!m_fileView && def->sources.size() > 1)
    {
        for (ProjectDefinitionSource source : def->sources)
        {

            char linestr[32];
            snprintf(linestr, 32, "%u", source.position.line);
            TextListItem* sourceItem = new TextListItem(m_vide,
                m_app->getTheme()->getIcon(typeToIcon(source.type)),
                Utils::string2wstring(source.entry->getName() + ":" + string(linestr) ));
            item->addItem(sourceItem);

            ProjectDefinitionSource* src = new ProjectDefinitionSource();
            *src = source;
            sourceItem->setPrivateData(src);
            sourceItem->clickSignal().connect(sigc::mem_fun(*this, &StructureView::onItemClicked));
        }
    }

    for (ProjectDefinition* child : def->children)
    {
        addDefinition(item, child);
    }
}

void StructureView::onItemClicked(Frontier::ListItem* item)
{
    ProjectDefinitionSource* source = (ProjectDefinitionSource*)item->getPrivateData();
    ((VideWindow*)getWindow())->openEntry(source->entry, source->position);
}

