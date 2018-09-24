#ifndef __VIDE_INTERFACE_H_
#define __VIDE_INTERFACE_H_

#include <frontier/messages.h>

class Editor;

class Interface
{
 protected:

    Editor* m_editor;

 public:
    Interface(Editor* editor);
    virtual ~Interface();

    virtual void key(Frontier::InputMessage* inputMessage);

    virtual void updateStatus();
};

enum ViMode
{
    MODE_NORMAL,
    MODE_INSERT,
    MODE_COMMAND,
};

class ViInterface : public Interface
{
 protected:
    ViMode m_mode;
    std::wstring m_command;

    void keyNormal(Frontier::InputMessage* inputMessage);
    void keyInsert(Frontier::InputMessage* inputMessage);
    void keyCommand(Frontier::InputMessage* inputMessage);
    bool keyCursor(Frontier::InputMessage* inputMessage);

    void runCommand(std::wstring command);

    void setMode(ViMode mode);

 public:
    ViInterface(Editor* editor);
    virtual ~ViInterface();

    virtual void key(Frontier::InputMessage* inputMessage);

    virtual void updateStatus();
};

#endif
