#ifndef __VIDE_FILE_TYPE_MANAGER_H_
#define __VIDE_FILE_TYPE_MANAGER_H_

#include "tokeniser.h"

class ProjectFile;

struct FileTypeManagerData
{
};

class FileTypeManager
{
 protected:

    Tokeniser* m_tokeniser;

 public:
    FileTypeManager();
    virtual ~FileTypeManager();

    virtual bool canHandle(ProjectFile* file);

    Tokeniser* getTokeniser() { return m_tokeniser; }

    virtual bool index(ProjectFile* entry);

    virtual bool tokenise(Buffer* buffer);
    virtual bool tokenise(Buffer* buffer, Line* line);
};

class TextFileTypeManager : public FileTypeManager
{
 protected:

 public:
    TextFileTypeManager();
    virtual ~TextFileTypeManager();

    virtual bool canHandle(ProjectFile* file);
};

#endif
