
#include "vide.h"

using namespace std;
using namespace Frontier;

Vide::Vide()
{
}

Vide::~Vide()
{
}

bool Vide::init()
{
    bool res;
    res = FrontierApp::init();
    if (!res)
    {
        return false;
    }

    m_textFont = getFontManager()->openFont(
        "Hack",
        FontStyle_Normal,
        //36);
        10);
    if (m_textFont == NULL)
    {
        printf("Vide::init: Failed to find font: Hack\n");
        return false;
    }

    vector<wstring> lines1;
    lines1.push_back(L"#include <stdio.h>");
    lines1.push_back(L"");
    lines1.push_back(L"int main(int argc, char** argv)");
    lines1.push_back(L"{");
    lines1.push_back(L"    printf(\"Hello, world!\\n\");");
    lines1.push_back(L"    return 0;");
    lines1.push_back(L"}");

    vector<wstring> lines2;
    lines2.push_back(L"#ifndef __TEST_H_");
    lines2.push_back(L"#define __TEST_H_");
    lines2.push_back(L"");
    lines2.push_back(L"void testFunc();");
    lines2.push_back(L"");
    lines2.push_back(L"#endif");

    m_interfaceStatus = new Label(this, L"", ALIGN_LEFT);

    Frame* rootFrame = new Frame(this, false);

    Frame* toolbar = new Frame(this, true);
    toolbar->setPadding(0);
    IconButton* openButton = new IconButton(this, FRONTIER_ICON_FOLDER_OPEN);
    openButton->clickSignal().connect(sigc::mem_fun(*this, &Vide::onOpenFile));
    toolbar->add(openButton);
    toolbar->add(new IconButton(this, FRONTIER_ICON_SAVE));
    toolbar->add(new IconButton(this, FRONTIER_ICON_SYNC));
    rootFrame->add(toolbar);

    ResizeableFrame* mainFrame = new ResizeableFrame(this, true);
    rootFrame->add(mainFrame);

    List* list = new List(this);
    list->addItem(new TextListItem(L"test.cpp"));
    list->addItem(new TextListItem(L"test.h"));
    Scroller* scroller = new Scroller(this);
    scroller->setChild(list);
    mainFrame->add(scroller);

    Tabs* tabs = new Tabs(this);
    mainFrame->add(tabs);
    tabs->changeTabSignal().connect(sigc::mem_fun(*this, &Vide::onEditorTabChange));

    m_editor = new Editor(this);
    Buffer* buffer = Buffer::loadFile("main.cpp");
    m_editor->setBuffer(buffer);
    tabs->addTab(L"main.cpp", m_editor);

    Editor* editor2 = new Editor(this);
    Buffer* buffer2 = Buffer::loadFile("editor.cpp");
    editor2->setBuffer(buffer2);
    tabs->addTab(L"editor.cpp", editor2);

    List* list2 = new List(this);
    list2->addItem(new TextListItem(L"main()"));
    list2->addItem(new TextListItem(L"TestClass::method()"));
    Scroller* scroller2 = new Scroller(this);
    scroller2->setChild(list2);
    mainFrame->add(scroller2);

    Frame* statusFrame = new Frame(this, true);
    statusFrame->add(m_interfaceStatus);
    statusFrame->add(new Label(this, L"test.cpp", ALIGN_RIGHT));
    rootFrame->add(statusFrame);

    m_mainWindow = new FrontierWindow(this);
    m_mainWindow->setContent(rootFrame);
    m_mainWindow->setActiveWidget(m_editor);

    m_mainWindow->show();

    return true;
}

void Vide::onOpenFile()
{
    printf("Vide::onOpenFile: Here!\n");
    string file = chooseFile();
    printf("Vide::onOpenFile: file=%s\n", file.c_str());
}

void Vide::onEditorTabChange(Widget* widget)
{
printf("Vide::onEditorTabChange: Setting active widget: %p\n", widget);
    m_mainWindow->setActiveWidget(widget);
}

void Vide::setInterfaceStatus(std::wstring message)
{
    m_interfaceStatus->setText(message);
}


