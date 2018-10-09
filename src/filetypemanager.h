#ifndef __VIDE_FILE_TYPE_MANAGER_H_
#define __VIDE_FILE_TYPE_MANAGER_H_

#include "tokeniser.h"

class FileTypeManager
{
 protected:

    Tokeniser* m_tokeniser;

 public:
    FileTypeManager();
    virtual ~FileTypeManager();

    Tokeniser* getTokeniser() { return m_tokeniser; }

    virtual bool tokenise(Buffer* buffer);
    virtual bool tokenise(Buffer* buffer, Line* line);
};

class TextFileTypeManager : public FileTypeManager
{
 protected:

 public:
    TextFileTypeManager();
    virtual ~TextFileTypeManager();
};



#endif
