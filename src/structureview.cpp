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

StructureView::StructureView(Vide* vide) : Frame(vide, false)
{
    m_vide = vide;
    m_margin = 0;
}

StructureView::~StructureView()
{
}

void StructureView::init()
{
printf("StructureView::init: m_vide=%p\n", m_vide);

    m_structureList = new List(m_vide);
    m_scroller = new Scroller(m_vide, m_structureList);
    //Label* projectLabel = new Label(m_vide, L"Project", ALIGN_LEFT);
    //projectLabel->setMargin(2);
    //add(projectLabel);
    add(m_scroller);
/*
*/
}

void StructureView::update()
{
    //TreeListItem* rootItem = new TreeListItem(m_vide, L"Project");
    map<string, ProjectDefinition*> index = m_vide->getProject()->getIndex();
    map<string, ProjectDefinition*>::iterator it;
    for (it = index.begin(); it != index.end(); it++)
{
ProjectDefinition* def = it->second;
if (def->parent == NULL)
{
addDefinition(NULL, def);
}
}

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
    wstring name = Utils::string2wstring(def->name);
uint32_t icon = FRONTIER_ICON_CIRCLE;
    if (def->sources.size() == 1)
    {
        char linestr[32];
        snprintf(linestr, 32, "%u", def->sources[0].position.line);
        name += L" " + Utils::string2wstring(def->sources[0].entry->getName() + ":" + string(linestr));
icon = typeToIcon(def->sources[0].type);
    }

    TreeListItem* item = new TreeListItem(m_vide, icon, name);

if (def->sources.size() == 1)
{
ProjectDefinitionSource* src = new ProjectDefinitionSource();
*src = def->sources[0];
item->setPrivateData(src);
            item->clickSignal().connect(sigc::mem_fun(*this, &StructureView::onItemClicked));
}

    if (parent == NULL)
    {
        m_structureList->addItem(item);
    }
    else
    {
        parent->addItem(item);
    }

    if (def->sources.size() > 1)
    {
        for (ProjectDefinitionSource source : def->sources)
        {

            char linestr[32];
            snprintf(linestr, 32, "%u", source.position.line);
            TextListItem* sourceItem = new TextListItem(m_vide, typeToIcon(source.type), Utils::string2wstring(source.entry->getName() + ":" + string(linestr) ));
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
    m_vide->getWindow()->openEntry(source->entry, source->position);
}


