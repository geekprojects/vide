
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
    Frame* rootFrame = new Frame(this, true);

    List* pagesList = new List(this);
    Scroller* scroller = new Scroller(this);
    scroller->setChild(pagesList);
    rootFrame->add(scroller);

    pagesList->addItem(new TextListItem(this, L"General"));
    pagesList->addItem(new TextListItem(this, L"Editor"));

    rootFrame->add(new Button(this, L"Settings!"));

    setContent(rootFrame);

    closeSignal().connect(sigc::mem_fun(*this, &SettingsWindow::onClose));

    return true;
}

bool SettingsWindow::onClose()
{
    hide();

    return true;
}

