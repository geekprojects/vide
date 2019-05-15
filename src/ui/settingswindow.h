#ifndef __VIDE_UI_SETTINGSWINDOW_H_
#define __VIDE_UI_SETTINGSWINDOW_H_

#include <frontier/frontier.h>
#include <frontier/widgets/label.h>
#include <frontier/widgets/list.h>

#include "vide.h"

class SettingsWindow : public Frontier::FrontierWindow
{
 private:

    virtual bool init();

 public:
    SettingsWindow(Vide* vide);
    virtual ~SettingsWindow();

    bool onClose();
};

#endif
