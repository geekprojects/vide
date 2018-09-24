#ifndef __VIDE_VIDEWINDOW_H_
#define __VIDE_VIDEWINDOW_H_

#include <frontier/frontier.h>
#include <frontier/widgets.h>

#include "editor.h"

class VideWindow : public Frontier::FrontierWindow
{
 private:
    Editor* m_editor;
    FontHandle* m_textFont;
    Frontier::Label* m_interfaceStatus;

    void onOpenFile();

    void onEditorTabChange(Frontier::Widget* widget);

    virtual bool init();

 public:
    VideWindow(Frontier::FrontierApp* app);
    ~VideWindow();

    FontHandle* getTextFont() { return m_textFont; }

    void setInterfaceStatus(std::wstring message);
};

#endif
