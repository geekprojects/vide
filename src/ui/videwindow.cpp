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

    m_leftTabs = new Tabs(this);
    m_projectView = new ProjectView(m_vide);
    m_leftTabs->addTab(L"Files", m_projectView);

    m_structureView = new StructureView(m_vide, false);
    m_leftTabs->addTab(L"Structure", m_structureView);
 
    mainFrame->addWithSize(m_leftTabs, 25);

    m_editorTabs = new Tabs(this);
    mainFrame->addWithSize(m_editorTabs, 50);
    m_editorTabs->changeTabSignal().connect(sigc::mem_fun(*this, &VideWindow::onEditorTabChange));
    m_editorTabs->closeTabSignal().connect(sigc::mem_fun(*this, &VideWindow::onCloseTab));

    m_rightTabs = new Tabs(this);
    m_fileStructureView = new StructureView(m_vide, true);
    m_rightTabs->addTab(L"Structure", m_fileStructureView);
    mainFrame->addWithSize(m_rightTabs, 25);

    Frame* statusFrame = new Frame(this, true);
    statusFrame->add(m_interfaceStatus);
    statusFrame->add(new Label(this, L"test.cpp", ALIGN_RIGHT));
    rootFrame->add(statusFrame);

    setContent(rootFrame);

    m_projectView->update();
    m_structureView->update();

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
    if (widget != NULL)
    {
        printf("VideWindow::onEditorTabChange: Setting active widget: %p\n", widget);
        setActiveWidget(widget);

        EditorView* editor = (EditorView*)widget;
        m_fileStructureView->setProjectFile(editor->getEditor()->getBuffer()->getProjectFile());
    }
    else
    {
        m_fileStructureView->setProjectFile(NULL);
    }
}

void VideWindow::onCloseTab(Widget* tab)
{
    printf("VideWindow::onCloseTab: Closing tab: %p\n", tab);
    m_editorTabs->closeTab(tab);
}

void VideWindow::setInterfaceStatus(std::wstring message)
{
    m_interfaceStatus->setText(message);
}

Editor* VideWindow::openEntry(ProjectEntry* entry)
{
    string filePath = entry->getFilePath();
    printf("VideWindow::openEntry: filePath=%s\n", filePath.c_str());

    EditorView* activeEditorView = (EditorView*)m_editorTabs->getActiveTab();

    Editor* editor = entry->getEditor();
    EditorView* editorView = NULL;
    if (editor == NULL)
    {
        Buffer* buffer = Buffer::loadFile(filePath.c_str());
        buffer->setProjectFile((ProjectFile*)entry);

        editor = new Editor(buffer, entry->getFileTypeManager());
        editor->setBuffer(buffer);

        editorView = new EditorView(m_vide, editor);
        m_editorTabs->addTab(Frontier::Utils::string2wstring(entry->getName()), editorView, true);

        entry->setEditor(editor);
        //editor->incRefCount(); // The entry keeps a reference

        entry->dumpDefinitions();
    }
    else
    {
        for (Tab tab : m_editorTabs->getTabs())
        {
            EditorView* ev = (EditorView*)tab.content;
            if (ev->getEditor() == editor)
            {
                editorView = ev;
                break;
            }
        }

        // Make sure the editor is actually on a tab
        if (editorView == NULL)
        {
            // Reopen tab
            editorView = new EditorView(m_vide, editor);
            m_editorTabs->addTab(Frontier::Utils::string2wstring(entry->getName()), editorView, true);
        }
    }

    if (activeEditorView != editorView)
    {
        printf("VideWindow::openEntry: Setting active widget: %p\n", editor);
        m_editorTabs->setActiveTab(editorView);

        m_fileStructureView->setProjectFile((ProjectFile*)entry);

        getContent()->setDirty();
    }

    setActiveWidget(editorView);

    return editor;
}

Editor* VideWindow::openEntry(ProjectEntry* entry, Position pos)
{
    Editor* editor = openEntry(entry);
    editor->moveCursor(pos);
    printf("VideWindow::openEntry: line=%u, column=%u\n", pos.line, pos.column);
    return editor;
}

