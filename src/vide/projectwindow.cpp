
#include "projectwindow.h"

#include <frontier/widgets/label.h>
#include <frontier/widgets/iconbutton.h>
#include <frontier/widgets/list.h>
#include <frontier/widgets/grid.h>
#include <frontier/widgets/textinput.h>
#include <frontier/widgets/combobox.h>
#include <frontier/fontawesome.h>
#include <frontier/utils.h>

#include <unistd.h>

using namespace std;
using namespace Frontier;
using namespace Geek;

ProjectWindow::ProjectWindow(VideApp* vide) : FrontierWindow(vide, L"Vide Project", WINDOW_NORMAL)
{
    m_vide = vide;
}

ProjectWindow::~ProjectWindow()
{
}

bool ProjectWindow::init()
{
    Frame* rootFrame = new Frame(this, false);
    rootFrame->add(new Label(this, L"Project to Vide"));

    Grid* grid = new Grid(this);
    rootFrame->add(grid);

    grid->put(0, 0, new Label(this, L"Project Name:"));
    grid->put(1, 0, new TextInput(this));

    grid->put(0, 1, new Label(this, L"Project Directory:"));
    Frame* rootDirFrame = new Frame(this, true);
    IconButton* chooseDirButton;
    rootDirFrame->setMargin(0);
    rootDirFrame->setPadding(0);
    rootDirFrame->add(m_projectDirInput = new TextInput(this));
    rootDirFrame->add(chooseDirButton = new IconButton(this, getApp()->getTheme()->getIcon(FRONTIER_ICON_FOLDER)));
    grid->put(1, 1, rootDirFrame);
    chooseDirButton->clickSignal().connect(sigc::mem_fun(*this, &ProjectWindow::chooseProjectDir));

    grid->put(0, 2, new Label(this, L"Project Type:"));

    vector<wstring> projectTypes;
    projectTypes.push_back(L"C/C++");
    projectTypes.push_back(L"Java");
    projectTypes.push_back(L"Other");
    ComboBox* projectTypeBox = new ComboBox(this, projectTypes);
    grid->put(1, 2, projectTypeBox);

    vector<wstring> buildTypes;
    buildTypes.push_back(L"Autoconf");
    buildTypes.push_back(L"Makefile");
    buildTypes.push_back(L"CMake");
    buildTypes.push_back(L"Other...");
    ComboBox* buildTypeBox = new ComboBox(this, buildTypes);
    grid->put(0, 3, new Label(this, L"Build System:"));
    grid->put(1, 3, buildTypeBox);

    grid->put(0, 4, new Label(this, L"Include Dirs:"));
    List* includeList = new List(this);
    includeList->addItem(new TextListItem(this, L"include"));
    grid->put(1, 4, new Scroller(this, includeList));

    grid->put(0, 5, new Label(this, L"System Include Dirs:"));
    List* sysIncludeList = new List(this);
    sysIncludeList->addItem(new TextListItem(this, L"/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include"));
    sysIncludeList->addItem(new TextListItem(this, L"/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include/c++/v1"));
    grid->put(1, 5, new Scroller(this, sysIncludeList));

    Frame* buttonFrame = new Frame(this, true);
    Button* createButton;
    Button* cancelButton;
    buttonFrame->add(createButton = new Button(this, L"Create"));
    buttonFrame->add(cancelButton = new Button(this, L"Cancel"));
    rootFrame->add(buttonFrame);

    createButton->clickSignal().connect(sigc::mem_fun(*this, &ProjectWindow::create));
    cancelButton->clickSignal().connect(sigc::mem_fun(*this, &ProjectWindow::cancel));

    setContent(rootFrame);

    return true;
}

void ProjectWindow::chooseProjectDir()
{
    string dir = getApp()->chooseFile(DIRECTORIES_ONLY, "", "");
    if (dir.length() != 0)
    {
        m_projectDirInput->setText(Utils::string2wstring(dir));
    }
}

void ProjectWindow::create()
{
    string path = Utils::wstring2string(m_projectDirInput->getText());
    if (path != "")
    {
        string projectFile = path + "/vide.project";

        int res;
        res = access(projectFile.c_str(), R_OK);
        if (res == 0)
        {
            // Project file already exists
            return;
        }

        Project* project = new Project(m_vide, path);
        project->init();
        project->save();

        m_vide->hideWelcomeWindow();
        m_vide->openProject(path);
        hide();
    }
}

void ProjectWindow::cancel()
{
    hide();
}

