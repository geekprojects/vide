#ifndef __VIDE_STRUCTURE_WIDGET_H_
#define __VIDE_STRUCTURE_WIDGET_H_

#include "vide.h"

#include <frontier/widgets/frame.h>
#include <frontier/widgets/scroller.h>
#include <frontier/widgets/list.h>

struct ProjectDefinition;

class StructureView : public Frontier::Frame
{
 private:
    Vide* m_vide;
    Frontier::Scroller* m_scroller;
    Frontier::List* m_structureList;

    void addDefinition(Frontier::TreeListItem* parent, ProjectDefinition* def);

    void onItemClicked(Frontier::ListItem* item);

 public:
    StructureView(Vide* vide);
    virtual ~StructureView();

    virtual void update();

    virtual void init();
};

#endif
