#ifndef __VIDE_UI_PROJECT_WINDOW_H_
#define __VIDE_UI_PROJECT_WINDOW_H_

#include <frontier/frontier.h>
#include <frontier/widgets/textinput.h>

#include "vide.h"

class ProjectWindow : public Frontier::FrontierWindow
{
 private:
    Vide* m_vide;
    Frontier::TextInput* m_projectDirInput;

    virtual bool init();

    virtual void chooseProjectDir();
    virtual void create();
    virtual void cancel();

 public:
    ProjectWindow(Vide* vide);
    virtual ~ProjectWindow();


};

#endif
