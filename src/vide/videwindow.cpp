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
#include "vide/utils.h"

#include <frontier/widgets/iconbutton.h>
#include <frontier/widgets/resizeableframe.h>
#include <frontier/widgets/terminal.h>

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;

VideWindow::VideWindow(VideApp* vide, Project* project) : FrontierWindow(vide, L"Vide Main", WINDOW_NORMAL)
{
    m_vide = vide;
    m_project = project;
}

VideWindow::~VideWindow()
{
}

bool VideWindow::init()
{
    m_interfaceStatus = new Label(getApp(), L"", ALIGN_LEFT);

    Frame* rootFrame = new Frame(getApp(), false);

    Frame* toolbar = new Frame(getApp(), true);
    toolbar->getWidgetStyle()->applyProperty("padding", 0);
    IconButton* openButton = new IconButton(getApp(), getApp()->getTheme()->getIcon(FRONTIER_ICON_FOLDER_OPEN));
    openButton->clickSignal().connect(sigc::mem_fun(*this, &VideWindow::onOpenFile));
    toolbar->add(openButton);
    toolbar->add(new IconButton(getApp(), getApp()->getTheme()->getIcon(FRONTIER_ICON_SAVE)));
    toolbar->add(new IconButton(getApp(), getApp()->getTheme()->getIcon(FRONTIER_ICON_SYNC)));
    rootFrame->add(toolbar);

    ResizeableFrame* bottomFrame = new ResizeableFrame(getApp(), false);
    //Frame* bottomFrame = new Frame(this, false);
    rootFrame->add(bottomFrame);

    ResizeableFrame* mainFrame = new ResizeableFrame(getApp(), true);
    bottomFrame->addWithSize(mainFrame, 75);

    m_leftTabs = new Tabs(getApp(), true, TAB_LEFT);
    m_projectView = new ProjectView(m_vide, m_project);
    m_leftTabs->addTab(L"Files", getApp()->getTheme()->getIcon(FRONTIER_ICON_FOLDER_OPEN), m_projectView);

    m_structureView = new StructureView(m_vide, false);
    m_leftTabs->addTab(L"Structure", getApp()->getTheme()->getIcon(FRONTIER_ICON_SITEMAP), m_structureView);
 
    mainFrame->addWithSize(m_leftTabs, 25);

    m_contentFrame = new ResizeableFrame(getApp(), true);
    mainFrame->addWithSize(m_contentFrame, 50);

    Tabs* editorTabs = new Tabs(getApp());
    //m_contentFrame->addWithSize(editorTabs, 50);
    m_contentFrame->add(editorTabs);
    editorTabs->changeTabSignal().connect(sigc::mem_fun(*this, &VideWindow::onEditorTabChange));
    editorTabs->closeTabSignal().connect(sigc::mem_fun(*this, &VideWindow::onCloseTab));
    m_activeEditorTabs = editorTabs;
    m_editorTabs.push_back(editorTabs);

/*
    editorTabs = new Tabs(this);
    m_contentFrame->addWithSize(editorTabs, 50);
    editorTabs->changeTabSignal().connect(sigc::mem_fun(*this, &VideWindow::onEditorTabChange));
    editorTabs->closeTabSignal().connect(sigc::mem_fun(*this, &VideWindow::onCloseTab));
    m_editorTabs.push_back(editorTabs);
*/

    m_rightTabs = new Tabs(getApp(), true, TAB_RIGHT);
    m_fileStructureView = new StructureView(m_vide, true);
    m_rightTabs->addTab(L"Structure", getApp()->getTheme()->getIcon(FRONTIER_ICON_SITEMAP), m_fileStructureView);
    mainFrame->addWithSize(m_rightTabs, 25);

    Frame* statusFrame = new Frame(getApp(), true);
    statusFrame->add(m_interfaceStatus);
    statusFrame->add(m_editorStatus = new Label(getApp(), L"", ALIGN_RIGHT));
    rootFrame->add(statusFrame);

    Tabs* bottomTabs = new Tabs(getApp(), true, TAB_BOTTOM);
    Terminal* terminal;
    bottomTabs->addTab(L"Terminal", getApp()->getTheme()->getIcon(FRONTIER_ICON_TERMINAL), terminal = new Terminal(getApp()));
    terminal->run("make");
    bottomTabs->addTab(L"Search", getApp()->getTheme()->getIcon(FRONTIER_ICON_SEARCH), new Label(getApp(), L"Search"));
    bottomTabs->addTab(L"Tasks", getApp()->getTheme()->getIcon(FRONTIER_ICON_SEARCH), m_tasksView = new TasksView(m_vide));
    bottomFrame->addWithSize(bottomTabs, 25);

    setContent(rootFrame);

    m_projectView->update();
    m_structureView->update();

    m_editorTipWindow = new EditorTipWindow(getApp());

    Menu* menu = new Menu();

#if defined(__APPLE__) || defined(MACOSX)
    MenuItem* appMenu = new MenuItem(L"__APP__");
    appMenu->add(new MenuItem(L"Preferences...", ',', 0, sigc::mem_fun(*m_vide, &VideApp::showSettingsWindow)));
    appMenu->add(new MenuSeparator());
    appMenu->add(new MenuItem(L"Quit", 'q', 0, sigc::mem_fun(*m_vide, &VideApp::onQuitMenu)));
    menu->add(appMenu);
#endif

    MenuItem* fileMenu = new MenuItem(L"Project");
    fileMenu->add(new MenuItem(L"New..."));
    fileMenu->add(new MenuItem(L"Open..."));
    fileMenu->add(new MenuItem(L"Close", 'w', 0));
    fileMenu->add(new MenuSeparator());
#if !defined(__APPLE__) && !defined(MACOSX)
    fileMenu->add(new MenuItem(L"Settings"));
    fileMenu->add(new MenuSeparator());
#endif
    menu->add(fileMenu);

    MenuItem* editMenu = new MenuItem(L"Edit");
    editMenu->add(new MenuItem(L"Cut", L'x', 0));
    editMenu->add(new MenuItem(L"Copy", L'c', 0));
    editMenu->add(new MenuItem(L"Paste", L'v', 0));
    menu->add(editMenu);

    MenuItem* viewMenu = new MenuItem(L"View");
    viewMenu->add(new MenuItem(L"Split Horizontally", L'h', 0, sigc::mem_fun(*this, &VideWindow::onSplitHorizontally)));
    viewMenu->add(new MenuItem(L"Split Vertically"));
    menu->add(viewMenu);

    MenuItem* buildMenu = new MenuItem(L"Build");
    buildMenu->add(new MenuItem(L"Build"));
    buildMenu->add(new MenuItem(L"Run"));
    buildMenu->add(new MenuItem(L"Clean"));
    menu->add(buildMenu);

    MenuItem* helpMenu = new MenuItem(L"Help");
    helpMenu->add(new MenuItem(L"Vide Help"));
    menu->add(helpMenu);

    setMenu(menu);

    return true;
}

void VideWindow::onOpenFile(Widget* w)
{
    log(DEBUG, "onOpenFile: Here!");
    string file = getApp()->chooseFile(0, "", "");
    log(DEBUG, "onOpenFile: file=%s", file.c_str());
}

void VideWindow::onEditorTabChange(Widget* widget)
{
    if (widget != NULL)
    {
        log(DEBUG, "onEditorTabChange: Setting active widget: %p", widget);
        m_activeEditorTabs = (Tabs*)(widget->getParent());
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
    log(DEBUG, "onCloseTab: Closing tab: %p", tab);
    //m_editorTabs->closeTab(tab);
}

void VideWindow::setEditorStatus(std::wstring message)
{
    m_editorStatus->setText(message);
}

void VideWindow::setInterfaceStatus(std::wstring message)
{
    m_interfaceStatus->setText(message);
}

Editor* VideWindow::openEntry(ProjectEntry* entry)
{
    string filePath = entry->getFilePath();
    log(DEBUG, "openEntry: filePath=%s", filePath.c_str());

    EditorView* activeEditorView = (EditorView*)m_activeEditorTabs->getActiveTab();

    Editor* editor = entry->getEditor();
    EditorView* editorView = NULL;
    if (editor == NULL)
    {
        Buffer* buffer = entry->open();
        if (buffer == NULL)
        {
            log(ERROR, "openEntry: Failed to open buffer");
            return NULL;
        }

        editor = new Editor(m_vide->getVide(), buffer, entry->getFileTypeManager());
        editor->setBuffer(buffer);

        editorView = new EditorView(m_vide, editor);
        Icon* icon = m_vide->getFileTypeIcon(entry->getFileTypeManager()->getIcon());
        m_activeEditorTabs->addTab(Frontier::Utils::string2wstring(entry->getName()), icon, editorView, true);

        entry->setEditor(editor);
        //editor->incRefCount(); // The entry keeps a reference

        entry->dumpDefinitions();
    }
    else
    {
        for (Tabs* tabs : m_editorTabs)
        {
            for (Tab* tab : tabs->getTabs())
            {
                EditorView* ev = (EditorView*)tab->getContent();
                if (ev->getEditor() == editor)
                {
                    editorView = ev;
                    break;
                }
            }
            if (editorView != NULL)
            {
                break;
            }
        }

        // Make sure the editor is actually on a tab
        if (editorView == NULL)
        {
            // Reopen tab
            editorView = new EditorView(m_vide, editor);
            m_activeEditorTabs->addTab(Frontier::Utils::string2wstring(entry->getName()), editorView, true);
        }
    }

    if (activeEditorView != editorView)
    {
        log(DEBUG, "openEntry: Setting active widget: %p", editor);
        m_activeEditorTabs->setActiveTab(editorView);

        m_fileStructureView->setProjectFile((ProjectFile*)entry);

        getContent()->setDirty();
    }

    setActiveWidget(editorView);
    editorView->updateStatus();

    return editor;
}

Editor* VideWindow::openEntry(ProjectEntry* entry, Position pos)
{
    Editor* editor = openEntry(entry);
    editor->moveCursor(pos);
    log(DEBUG, "openEntry: line=%u, column=%u", pos.line, pos.column);
    return editor;
}

void VideWindow::onSplitHorizontally(Frontier::MenuItem* item)
{
log(DEBUG, "onSplitHorizontally: HERE!");
    Tabs* editorTabs = new Tabs(getApp());
    m_contentFrame->add(editorTabs);
    editorTabs->changeTabSignal().connect(sigc::mem_fun(*this, &VideWindow::onEditorTabChange));
    editorTabs->closeTabSignal().connect(sigc::mem_fun(*this, &VideWindow::onCloseTab));
    m_activeEditorTabs = editorTabs;
    m_editorTabs.push_back(editorTabs);
    
}

