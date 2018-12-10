#ifndef __VIDE_UI_WELCOME_WINDOW_H_
#define __VIDE_UI_WELCOME_WINDOW_H_

#include <frontier/frontier.h>
#include <frontier/widgets/label.h>

#include "vide.h"

class Vide;

class WelcomeWindow : public Frontier::FrontierWindow
{
 private:
    Vide* m_vide;

    virtual bool init();

    void createProject();
    void chooseProject();

 public:
    WelcomeWindow(Vide* vide);
    virtual ~WelcomeWindow();


};

#endif
