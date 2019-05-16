
#include "vi.h"

using namespace std;
using namespace Frontier;

void ViInterface::keySearch(Frontier::KeyEvent* keyEvent)
{
    if (!keyEvent->direction)
    {
        return;
    }

    switch (keyEvent->key)
    {
        case KC_ESCAPE:
            setMode(MODE_NORMAL);
            break;

        case KC_RETURN:
            printf("ViInterface::keySearch: KC_RETURN: Searching: %ls\n", m_searchString.c_str());
            setMode(MODE_NORMAL);

            if (m_searchString.length() == 0)
            {
                m_searchString = m_prevSearch;
            }

            if (m_searchDirection)
            {
                m_editor->searchNext(m_searchString);
            }
            else
            {
                m_editor->searchPrev(m_searchString);
            }
            break;

        default:
            if (iswprint(keyEvent->chr))
            {
                m_searchString += keyEvent->chr;
            }
            break;
    }
}

bool ViInterface::commandSearch(ViCommand* command)
{
    setMode(MODE_SEARCH);

    m_searchDirection = true;
    m_prevSearch = m_searchString;
    m_searchString = L"";

    return true;
}

bool ViInterface::commandSearchBack(ViCommand* command)
{
    setMode(MODE_SEARCH);

    m_searchDirection = false;
    m_prevSearch = m_searchString;
    m_searchString = L"";

    return true;
}

bool ViInterface::commandSearchNext(ViCommand* command)
{
    if (m_searchString.length() > 0)
    {
        if (m_searchDirection)
        {
            m_editor->searchNext(m_searchString);
        }
        else
        {
            m_editor->searchPrev(m_searchString);
        }
    }

    return true;
}

