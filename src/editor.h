#ifndef __VIDE_EDITOR_H_
#define __VIDE_EDITOR_H_

#include "buffer.h"
#include "interface.h"
#include "format.h"

#include <frontier/widgets.h>

class Editor : public Frontier::Widget
{
 private:
    int m_marginX;
    unsigned int m_cursorX;
    unsigned int m_cursorY;

    Frontier::ScrollBar* m_scrollBar;

    Buffer* m_buffer;
    Interface* m_interface;
    Format* m_format;

    unsigned int getViewLines();

 public:

    Editor(Frontier::FrontierWindow* window);
    virtual ~Editor();

    virtual void calculateSize();
    virtual void layout();

    virtual bool draw(Geek::Gfx::Surface* surface);

    virtual Widget* handleMessage(Frontier::Message* msg);
    void onScrollbarChanged(int pos);

    void setBuffer(Buffer* buffer);
    Buffer* getBuffer() { return m_buffer; }

    unsigned int getCursorX() { return m_cursorX; }
    unsigned int getCursorY() { return m_cursorY; }

    void moveCursorX(unsigned int x);
    void moveCursorY(unsigned int y);
    void moveCursorDelta(int dx, int dy);
    void moveCursorXEnd();
    void moveCursorNextToken();
    void moveCursorPage(int dir);

    void insert(wchar_t c);
    void deleteAtCursor();

    void setInterfaceStatus(std::wstring message);
};

#endif
