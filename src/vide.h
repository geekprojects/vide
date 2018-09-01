#ifndef __VIDE_VIDE_H_
#define __VIDE_VIDE_H_

#include <frontier/frontier.h>
#include <frontier/widgets.h>

#include "editor.h"

class Vide : public Frontier::FrontierApp
{
 private:
    Frontier::FrontierWindow* m_mainWindow;
    Editor* m_editor;
    FontHandle* m_textFont;

    void onOpenFile();

 public:
    Vide();
    ~Vide();

    virtual bool init();

    FontHandle* getTextFont() { return m_textFont; }
};

#endif
