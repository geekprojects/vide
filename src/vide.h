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
    Frontier::Label* m_interfaceStatus;

    void onOpenFile();

    void onEditorTabChange(Frontier::Widget* widget);

 public:
    Vide();
    ~Vide();

    virtual bool init();

    FontHandle* getTextFont() { return m_textFont; }

    void setInterfaceStatus(std::wstring message);
};

#endif
