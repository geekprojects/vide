#ifndef __VIDE_FILE_TYPE_MANAGER_H_
#define __VIDE_FILE_TYPE_MANAGER_H_

#include "tokeniser.h"
#include "plugins/plugins.h"
#include "vide.h"

#include <frontier/icon.h>

class Project;
class ProjectFile;
class VidePlugin;

struct FileTypeManagerData
{
};

class FileTypeManager : public VidePlugin
{
 protected:
    Tokeniser* m_tokeniser;

 public:
    FileTypeManager(Vide* vide);
    virtual ~FileTypeManager();

    virtual bool init();

    virtual FileHandlerPriority canHandle(ProjectFile* file);

    Tokeniser* getTokeniser() { return m_tokeniser; }

    virtual bool index(ProjectFile* entry);

    virtual bool tokenise(Buffer* buffer);
    virtual bool tokenise(Buffer* buffer, Line* line);

    virtual Frontier::Icon* getIcon();
};

class TextFileTypeManager : public FileTypeManager
{
 protected:

 public:
    TextFileTypeManager(Vide* vide);
    virtual ~TextFileTypeManager();

    virtual FileHandlerPriority canHandle(ProjectFile* file);

    virtual Frontier::Icon* getIcon();
};

#endif
