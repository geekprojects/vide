#ifndef __VIDE_FILE_TYPE_MANAGER_H_
#define __VIDE_FILE_TYPE_MANAGER_H_

#include "tokeniser.h"
#include "plugins/plugins.h"

class Project;
class ProjectFile;
class VidePlugin;

struct FileTypeManagerData
{
};

enum FileTypeManagerPriority
{
    PRIORITY_UNSUPPORTED =  -1,
    PRIORITY_LOW =  1,
    PRIORITY_HIGH =  100,
};

class FileTypeManager : public VidePlugin
{
 protected:
    Tokeniser* m_tokeniser;

 public:
    FileTypeManager(Vide* vide);
    virtual ~FileTypeManager();

    virtual bool init();

    virtual FileTypeManagerPriority canHandle(ProjectFile* file);

    Tokeniser* getTokeniser() { return m_tokeniser; }

    virtual bool index(ProjectFile* entry);

    virtual bool tokenise(Buffer* buffer);
    virtual bool tokenise(Buffer* buffer, Line* line);
};

class TextFileTypeManager : public FileTypeManager
{
 protected:

 public:
    TextFileTypeManager(Vide* vide);
    virtual ~TextFileTypeManager();

    virtual FileTypeManagerPriority canHandle(ProjectFile* file);
};

#endif
