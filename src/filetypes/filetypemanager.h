#ifndef __VIDE_FILE_TYPE_MANAGER_H_
#define __VIDE_FILE_TYPE_MANAGER_H_

#include "tokeniser.h"

class Project;
class ProjectFile;

struct FileTypeManagerData
{
};

class FileTypeManager
{
 protected:

    Project* m_project;
    Tokeniser* m_tokeniser;

 public:
    FileTypeManager(Project* project);
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
    TextFileTypeManager(Project* project);
    virtual ~TextFileTypeManager();

    virtual bool canHandle(ProjectFile* file);
};

#endif
