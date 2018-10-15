
#include "editortipwindow.h"

#include <frontier/widgets/label.h>
#include <frontier/utils.h>

using namespace std;
using namespace Frontier;

EditorTipWindow::EditorTipWindow(FrontierApp* app) : FrontierWindow(app, L"", WINDOW_POPUP)
{
m_token = NULL;
}

EditorTipWindow::~EditorTipWindow()
{
}

bool EditorTipWindow::init()
{
//    m_label = new Label(this, L"Editor Tip Window");

    return true;
}

void EditorTipWindow::setToken(LineToken* token, Geek::Vector2D pos)
{
    if (token != m_token)
    {
        m_token = token;

        if (m_token == NULL)
        {
            hide();
            return;
        }

        Frame* oldFrame = m_frame;


        m_frame = new Frame(this, false);

        for (TokenMessage message : token->messages)
        {
            Label* label = new Label(this, Frontier::Utils::string2wstring(message.text));
            m_frame->add(label);
        }
        setContent(m_frame);

        if (oldFrame != NULL)
        {
            delete oldFrame;
        }
    }
    if (m_token != NULL)
    {
        show();
        setPosition(pos);
    }
}

