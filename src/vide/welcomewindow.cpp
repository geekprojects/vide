
#include "welcomewindow.h"
#include "projectwindow.h"

#include <frontier/widgets/label.h>
#include <frontier/widgets/iconbutton.h>
#include <frontier/widgets/list.h>

using namespace std;
using namespace Frontier;
using namespace Geek;

WelcomeWindow::WelcomeWindow(VideApp* vide) : FrontierWindow(vide, L"Welcome to Vide", WINDOW_NORMAL)
{
    m_vide = vide;
}

WelcomeWindow::~WelcomeWindow()
{
}

bool WelcomeWindow::init()
{
    Frame* rootFrame = new Frame(this, false);
    rootFrame->add(new Label(this, L"Welcome to Vide"));

    Button* createButton;
    Button* openButton;
    rootFrame->add(createButton = new Button(this, L"Create New Project"));
    rootFrame->add(openButton = new Button(this, L"Open Existing Project"));

    createButton->clickSignal().connect(sigc::mem_fun(*this, &WelcomeWindow::createProject));
    openButton->clickSignal().connect(sigc::mem_fun(*this, &WelcomeWindow::chooseProject));

    rootFrame->add(new Label(this, L"Recent Projects"));

    List* list = new List(this);
    TextListItem* item = new TextListItem(this, L"/Users/ian/projects/vide/testproject");
    item->setPrivateData(strdup("/Users/ian/projects/vide/testproject"));
    item->doubleClickSignal().connect(sigc::mem_fun(*this, &WelcomeWindow::selectProject));
    list->addItem(item);

    Scroller* scroller = new Scroller(this);
    scroller->setChild(list);
    rootFrame->add(scroller);

    setContent(rootFrame);

    return true;
}

void WelcomeWindow::createProject()
{
    ProjectWindow* projectWindow = new ProjectWindow(m_vide);
    projectWindow->show();
}

void WelcomeWindow::chooseProject()
{
    string path = m_vide->chooseFile(0, "", "");
    if (path.length() == 0)
    {
        return;
    }

    bool res = m_vide->openProject(path);
    if (res)
    {
        hide();
    }
}

void WelcomeWindow::selectProject(ListItem* item)
{
    log(DEBUG, "selectProject: item=%p -> %s", item, item->getPrivateData());

    bool res = m_vide->openProject((char*)item->getPrivateData());
    if (res)
    {
        hide();
    }
}

