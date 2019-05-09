#ifndef __VIDE_UI_TASKS_VIEW_H_
#define __VIDE_UI_TASKS_VIEW_H_

#include "vide.h"
#include "ui/views/view.h"

#include <frontier/widgets/frame.h>
#include <frontier/widgets/scroller.h>
#include <frontier/widgets/list.h>

struct ProjectDefinition;

class TasksView : public Frontier::Frame, public View
{
 private:
    Vide* m_vide;
    Frontier::Scroller* m_scroller;
    Frontier::List* m_tasksList;

 public:
    TasksView(Vide* vide);
    virtual ~TasksView();

    virtual void init();

    void update(Geek::Core::Task* task);
};

#endif
