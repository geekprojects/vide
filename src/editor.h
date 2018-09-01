#ifndef __VIDE_EDITOR_H_
#define __VIDE_EDITOR_H_

#include <frontier/widgets.h>

class Editor : public Frontier::Widget
{
 private:
    int m_cursorX;
    int m_cursorY;

 public:

    Editor(Frontier::FrontierApp* ui);
    virtual ~Editor();

    virtual void calculateSize();
    virtual bool draw(Geek::Gfx::Surface* surface);

    virtual Widget* handleMessage(Frontier::Message* msg);
};

#endif
