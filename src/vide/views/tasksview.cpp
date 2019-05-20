
#include "tasksview.h"

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Core;

TasksView::TasksView(VideApp* vide) : Frame(vide, L"TasksView", false)
{
    m_vide = vide;
}

TasksView::~TasksView()
{
}

void TasksView::init()
{
    m_tasksList = new List(m_vide);
    m_scroller = new Scroller(m_vide, m_tasksList);
    add(m_scroller);

    update(NULL);

    m_vide->getVide()->getTaskExecutor()->queuedSignal().connect(sigc::mem_fun(*this, &TasksView::update));
    m_vide->getVide()->getTaskExecutor()->startedSignal().connect(sigc::mem_fun(*this, &TasksView::update));
    m_vide->getVide()->getTaskExecutor()->completeSignal().connect(sigc::mem_fun(*this, &TasksView::update));
}

void TasksView::update(Task* task)
{
    m_tasksList->clearItems();

    vector<TaskInfo> tasks = m_vide->getVide()->getTaskExecutor()->getTaskInfo();
    for (TaskInfo info : tasks)
    {
        unsigned int icon;
        switch (info.state)
        {
            case TASK_CREATED:
            case TASK_QUEUED:
                icon = FRONTIER_ICON_HOURGLASS_START;
                break;
            case TASK_RUNNING:
                icon = FRONTIER_ICON_CHECK_CIRCLE;
                break;
        }
        TreeListItem* item = new TreeListItem(m_vide, m_app->getTheme()->getIcon(icon), info.title);
        m_tasksList->addItem(item);
    }
    setDirty();
}



