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


#include "videwindow.h"
#include "utils.h"

#include <frontier/widgets/iconbutton.h>
#include <frontier/widgets/resizeableframe.h>

using namespace std;
using namespace Frontier;

VideWindow::VideWindow(Vide* vide) : FrontierWindow(vide, L"Vide", WINDOW_NORMAL)
{
    m_vide = vide;
}

VideWindow::~VideWindow()
{
}

bool VideWindow::init()
{
    m_interfaceStatus = new Label(this, L"", ALIGN_LEFT);

    Frame* rootFrame = new Frame(this, false);

    Frame* toolbar = new Frame(this, true);
    toolbar->setPadding(0);
    IconButton* openButton = new IconButton(this, FRONTIER_ICON_FOLDER_OPEN);
    openButton->clickSignal().connect(sigc::mem_fun(*this, &VideWindow::onOpenFile));
    toolbar->add(openButton);
    toolbar->add(new IconButton(this, FRONTIER_ICON_SAVE));
    toolbar->add(new IconButton(this, FRONTIER_ICON_SYNC));
    rootFrame->add(toolbar);

    ResizeableFrame* mainFrame = new ResizeableFrame(this, true);
    rootFrame->add(mainFrame);

    m_projectView = new ProjectView(m_vide);
    mainFrame->addWithSize(m_projectView, 25);

    m_tabs = new Tabs(this);
    mainFrame->addWithSize(m_tabs, 50);
    m_tabs->changeTabSignal().connect(sigc::mem_fun(*this, &VideWindow::onEditorTabChange));

    List* list2 = new List(this);
    list2->addItem(new TextListItem(this, L"main()"));
    list2->addItem(new TextListItem(this, L"TestClass::method()"));
    Scroller* scroller2 = new Scroller(this);
    scroller2->setChild(list2);
    mainFrame->addWithSize(scroller2, 25);

    Frame* statusFrame = new Frame(this, true);
    statusFrame->add(m_interfaceStatus);
    statusFrame->add(new Label(this, L"test.cpp", ALIGN_RIGHT));
    rootFrame->add(statusFrame);

    setContent(rootFrame);

    m_projectView->update();

    m_editorTipWindow = new EditorTipWindow(getApp());

    return true;
}

void VideWindow::onOpenFile()
{
    printf("VideWindow::onOpenFile: Here!\n");
    string file = getApp()->chooseFile();
    printf("VideWindow::onOpenFile: file=%s\n", file.c_str());
}

void VideWindow::onEditorTabChange(Widget* widget)
{
printf("VideWindow::onEditorTabChange: Setting active widget: %p\n", widget);
    setActiveWidget(widget);
}

void VideWindow::setInterfaceStatus(std::wstring message)
{
    m_interfaceStatus->setText(message);
}

void VideWindow::openEntry(ProjectEntry* entry)
{
    string filePath = entry->getFilePath();
    printf("VideWindow::openEntry: filePath=%s\n", filePath.c_str());

    Editor* editor = entry->getEditor();
    if (editor == NULL)
    {
        Buffer* buffer = Buffer::loadFile(filePath.c_str());
buffer->setProjectFile((ProjectFile*)entry);

        editor = new Editor(m_vide, buffer, entry->getFileTypeManager());
        editor->setBuffer(buffer);
        m_tabs->addTab(Frontier::Utils::string2wstring(entry->getName()), editor);
        entry->setEditor(editor);
    }

    printf("VideWindow::openEntry: Setting active widget: %p\n", editor);
    m_tabs->setActiveTab(editor);
    setActiveWidget(editor);
}

