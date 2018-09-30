#ifndef __VIDE_PROJECT_WIDGET_H_
#define __VIDE_PROJECT_WIDGET_H_

#include "vide.h"

#include <frontier/widgets.h>

class Vide;
class ProjectDirectory;

class ProjectView : public Frontier::Frame
{
 private:
    Vide* m_vide;
    Frontier::Scroller* m_scroller;
    Frontier::List* m_projectList;

    void addDirectory(Frontier::TreeListItem* parent, ProjectDirectory* dir);

 public:
    ProjectView(Vide* vide);
    virtual ~ProjectView();

    virtual void update();

    virtual void init();
};

#endif
