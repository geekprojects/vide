
#include "projectview.h"

using namespace std;
using namespace Frontier;

static std::wstring string2wstring(const std::string &s)
{
    std::wstring ws(s.begin(), s.end());
    return ws;
}

ProjectView::ProjectView(Vide* vide) : Frame(vide, false)
{
    m_vide = vide;
    m_margin = 0;
}

ProjectView::~ProjectView()
{
}

void ProjectView::init()
{
printf("ProjectView::init: m_vide=%p\n", m_vide);

    m_projectList = new List(m_vide);
    m_scroller = new Scroller(m_vide, m_projectList);
    Label* projectLabel = new Label(m_vide, L"Project", ALIGN_LEFT);
    projectLabel->setMargin(2);
    add(projectLabel);
    add(m_scroller);
/*
*/
}

void ProjectView::update()
{
    TreeListItem* rootItem = new TreeListItem(m_vide, L"Project");
    m_projectList->addItem(rootItem);

    Project* project = m_vide->getProject();
    ProjectDirectory* root = project->getRoot();
    addDirectory(rootItem, root);
}

void ProjectView::addDirectory(TreeListItem* parent, ProjectDirectory* dir)
{
    for (ProjectEntry* entry : dir->getChildren())
    {
        ListItem* item = NULL;
        switch (entry->getType())
        {
            case ENTRY_FILE:
                item = new TextListItem(m_vide, FRONTIER_ICON_FILE, string2wstring(entry->getName()));
                break;

            case ENTRY_DIR:
            {
                TreeListItem* treeItem = new TreeListItem(m_vide, FRONTIER_ICON_FOLDER, string2wstring(entry->getName()));

                addDirectory(treeItem, (ProjectDirectory*)entry);

                item = treeItem;
            } break;

            default:
                // Skip
                break;

        }
        if (item != NULL)
        {
            item->setPrivateData(entry);
            parent->addItem(item);
        }
    }
}

