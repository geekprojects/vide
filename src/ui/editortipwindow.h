#ifndef __VIDE_EDITOR_TIP_WINDOW_H_
#define __VIDE_EDITOR_TIP_WINDOW_H_

#include <frontier/frontier.h>
#include <frontier/widgets/frame.h>

#include "editor/buffer.h"

class EditorTipWindow : public Frontier::FrontierWindow
{
 private:
    Frontier::Frame* m_frame;
    LineToken* m_token;

 public:
    EditorTipWindow(Frontier::FrontierApp* app);
    virtual ~EditorTipWindow();

    virtual bool init();

    void setToken(LineToken* token, Geek::Vector2D pos);
};

#endif
