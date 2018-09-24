
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

    m_mainWindow = new VideWindow(this);

    m_mainWindow->show();

    return true;
}

