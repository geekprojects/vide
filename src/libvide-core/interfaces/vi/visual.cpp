
#include "vi.h"

using namespace std;
using namespace Frontier;

void ViInterface::keyVisual(Frontier::KeyEvent* keyEvent)
{
    if (!keyEvent->direction)
    {
        return;
    }

    switch (keyEvent->key)
    {
        case KC_UP:
            m_editor->moveCursorDelta(0, -1);
            m_editor->setSelectEnd(m_editor->getCursorPosition());
            break;

        case KC_DOWN:
            m_editor->moveCursorDelta(0, 1);
            m_editor->setSelectEnd(m_editor->getCursorPosition());
            break;

        case KC_LEFT:
            m_editor->moveCursorDelta(-1, 0);
            m_editor->setSelectEnd(m_editor->getCursorPosition());
            break;

        case KC_RIGHT:
            m_editor->moveCursorDelta(1, 0);
            m_editor->setSelectEnd(m_editor->getCursorPosition());
            break;

        case KC_ESCAPE:
            setMode(MODE_NORMAL);
            break;
    }
}

