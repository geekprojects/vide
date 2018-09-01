
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
        36);
        //11);
    if (m_textFont == NULL)
    {
        printf("Vide::init: Failed to find font: Hack\n");
        return false;
    }

    Frame* rootFrame = new Frame(this, false);

    Frame* toolbar = new Frame(this, true);
    toolbar->setPadding(0);
    IconButton* openButton = new IconButton(this, FRONTIER_ICON_FOLDER_OPEN);
    openButton->clickSignal().connect(sigc::mem_fun(*this, &Vide::onOpenFile));
    toolbar->add(openButton);
    toolbar->add(new IconButton(this, FRONTIER_ICON_SAVE));
    toolbar->add(new IconButton(this, FRONTIER_ICON_SYNC));
    rootFrame->add(toolbar);

    m_editor = new Editor(this);
    rootFrame->add(m_editor);

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

int main(int argc, char** argv)
{
    Vide app;

    app.init();

    app.main();

    return 0;
}


