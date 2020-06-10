#ifndef __VIDE_UI_WELCOME_WINDOW_H_
#define __VIDE_UI_WELCOME_WINDOW_H_

#include <frontier/frontier.h>
#include <frontier/widgets/label.h>
#include <frontier/widgets/list.h>

#include "videapp.h"

class VideApp;

class WelcomeWindow : public Frontier::FrontierWindow
{
 private:
    VideApp* m_vide;

    virtual bool init();

    void createProject(Frontier::Widget* button);
    void chooseProject(Frontier::Widget* button);
    void selectProject(Frontier::Widget* item);

 public:
    WelcomeWindow(VideApp* vide);
    virtual ~WelcomeWindow();


};

#endif
