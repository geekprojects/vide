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

using namespace std;
using namespace Frontier;

VideWindow::VideWindow(Vide* vide) : FrontierWindow(vide)
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
    mainFrame->add(m_projectView);

    Tabs* tabs = new Tabs(this);
    mainFrame->add(tabs);
    tabs->changeTabSignal().connect(sigc::mem_fun(*this, &VideWindow::onEditorTabChange));

    m_editor = new Editor(this);
    Buffer* buffer = Buffer::loadFile("main.cpp");
    m_editor->setBuffer(buffer);
    tabs->addTab(L"main.cpp", m_editor);

    Editor* editor2 = new Editor(this);
    Buffer* buffer2 = Buffer::loadFile("editor.cpp");
    editor2->setBuffer(buffer2);
    tabs->addTab(L"editor.cpp", editor2);

    List* list2 = new List(this);
    list2->addItem(new TextListItem(this, L"main()"));
    list2->addItem(new TextListItem(this, L"TestClass::method()"));
    Scroller* scroller2 = new Scroller(this);
    scroller2->setChild(list2);
    mainFrame->add(scroller2);

    Frame* statusFrame = new Frame(this, true);
    statusFrame->add(m_interfaceStatus);
    statusFrame->add(new Label(this, L"test.cpp", ALIGN_RIGHT));
    rootFrame->add(statusFrame);

    setContent(rootFrame);
    setActiveWidget(m_editor);

    m_projectView->update();

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


