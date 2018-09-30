#ifndef __VIDE_VIDE_H_
#define __VIDE_VIDE_H_

#include <frontier/frontier.h>
#include <frontier/widgets.h>

#include "videwindow.h"
#include "project.h"

class VideWindow;

class Vide : public Frontier::FrontierApp
{
 private:
    Project* m_project;
    VideWindow* m_mainWindow;
    FontHandle* m_textFont;

 public:
    Vide();
    ~Vide();

    virtual bool init();

    FontHandle* getTextFont() { return m_textFont; }

    Project* getProject() { return m_project; }
};

#endif
