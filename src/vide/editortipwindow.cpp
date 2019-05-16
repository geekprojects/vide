
#include "editortipwindow.h"

#include <frontier/widgets/label.h>
#include <frontier/utils.h>

using namespace std;
using namespace Frontier;

EditorTipWindow::EditorTipWindow(FrontierApp* app) : FrontierWindow(app, L"", WINDOW_TOOL_TIP)
{
    m_token = NULL;
    m_frame = NULL;
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

        m_frame = new Frame(this, false);

        for (TokenMessage message : token->messages)
        {
            Label* label = new Label(this, Frontier::Utils::string2wstring(message.text));
            m_frame->add(label);
        }
        setContent(m_frame);
    }
    if (m_token != NULL)
    {
        // Resize to be as small as possible
        setSize(Size(0, 0));

        show();
        setPosition(pos);
    }
}

