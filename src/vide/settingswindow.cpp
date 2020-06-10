
#include "settingswindow.h"

#include <frontier/widgets/button.h>

using namespace std;
using namespace Frontier;

SettingsWindow::SettingsWindow(VideApp* vide) : FrontierWindow(vide, L"Settings", WINDOW_NORMAL)
{
}

SettingsWindow::~SettingsWindow()
{
}

bool SettingsWindow::init()
{
    Frame* rootFrame = new Frame(getApp(), true);

    List* pagesList = new List(getApp());
    Scroller* scroller = new Scroller(getApp());
    scroller->setChild(pagesList);
    rootFrame->add(scroller);

    pagesList->addItem(new TextListItem(getApp(), L"General"));
    pagesList->addItem(new TextListItem(getApp(), L"Editor"));

    rootFrame->add(new Button(getApp(), L"Settings!"));

    setContent(rootFrame);

    closeSignal().connect(sigc::mem_fun(*this, &SettingsWindow::onClose));

    return true;
}

void SettingsWindow::onClose()
{
    hide();
}

