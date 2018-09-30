#ifndef __VIDE_VIDEWINDOW_H_
#define __VIDE_VIDEWINDOW_H_

#include <frontier/frontier.h>
#include <frontier/widgets.h>

#include "editor.h"
#include "projectview.h"

class Vide;
class ProjectView;

class VideWindow : public Frontier::FrontierWindow
{
 private:
    Vide* m_vide;
    Editor* m_editor;
    FontHandle* m_textFont;
    Frontier::Label* m_interfaceStatus;
    ProjectView* m_projectView;

    void onOpenFile();

    void onEditorTabChange(Frontier::Widget* widget);

    virtual bool init();

 public:
    VideWindow(Vide* app);
    ~VideWindow();

    FontHandle* getTextFont() { return m_textFont; }

    void setInterfaceStatus(std::wstring message);
};

#endif
