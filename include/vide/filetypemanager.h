#ifndef __VIDE_FILE_TYPE_MANAGER_H_
#define __VIDE_FILE_TYPE_MANAGER_H_

#include <vide/tokeniser.h>
#include <vide/plugins.h>
#include <vide/vide.h>

#include <frontier/icon.h>
#include <geek/gfx-surface.h>

class Project;
class ProjectFile;
class VidePlugin;

enum FileTypeIconType
{
    ICON_ICON,
    ICON_SURFACE
};

struct FileTypeIcon
{
    FileTypeIconType type;
    union
    {
        uint32_t icon;
        Geek::Gfx::Surface* surface;
    };
};

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

    virtual FileTypeIcon getIcon();
};

class TextFileTypeManager : public FileTypeManager
{
 protected:

 public:
    TextFileTypeManager(Vide* vide);
    virtual ~TextFileTypeManager();

    virtual FileHandlerPriority canHandle(ProjectFile* file);

    virtual FileTypeIcon getIcon();
};

#endif
