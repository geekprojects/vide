#ifndef __VIDE_UI_PROJECT_WINDOW_H_
#define __VIDE_UI_PROJECT_WINDOW_H_

#include <frontier/frontier.h>
#include <frontier/widgets/textinput.h>

#include "videapp.h"

class ProjectWindow : public Frontier::FrontierWindow
{
 private:
    VideApp* m_vide;
    Frontier::TextInput* m_projectDirInput;

    virtual bool init();

    virtual void chooseProjectDir();
    virtual void create();
    virtual void cancel();

 public:
    ProjectWindow(VideApp* vide);
    virtual ~ProjectWindow();


};

#endif
