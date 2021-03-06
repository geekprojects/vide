
#include <vide/filetypemanager.h>
#include <vide/project.h>
#include <vide/vide.h>

using namespace std;
using namespace Frontier;

FileTypeManager::FileTypeManager(Vide* vide) : VidePlugin(vide)
{
}

FileTypeManager::~FileTypeManager()
{
}

bool FileTypeManager::init()
{
    getVide()->registerFileTypeManager(this);
    return true;
}

FileHandlerPriority FileTypeManager::canHandle(ProjectFile* file)
{
    return PRIORITY_UNSUPPORTED;
}

bool FileTypeManager::index(ProjectFile* file)
{
    // No indexing by default
    return true;
}

bool FileTypeManager::tokenise(Buffer* buffer)
{
    if (m_tokeniser == NULL)
    {
        return true;
    }

    return m_tokeniser->tokenise(buffer);
}

bool FileTypeManager::tokenise(Buffer* buffer, Line* line)
{
    if (m_tokeniser == NULL)
    {
        return true;
    }

    return m_tokeniser->tokenise(buffer, line);
}

FileTypeIcon FileTypeManager::getIcon()
{
    FileTypeIcon fti;
    fti.type = ICON_ICON;
    fti.icon = FRONTIER_ICON_FILE;
    return fti;
}

VIDE_PLUGIN(TextFileTypeManager);

TextFileTypeManager::TextFileTypeManager(Vide* vide) : FileTypeManager(vide)
{
    m_tokeniser = new SimpleTokeniser();
}

TextFileTypeManager::~TextFileTypeManager()
{
    delete m_tokeniser;
}

FileHandlerPriority TextFileTypeManager::canHandle(ProjectFile* file)
{
    // We'll take anything!
    return PRIORITY_LOW;
}

FileTypeIcon TextFileTypeManager::getIcon()
{
    FileTypeIcon fti;
    fti.type = ICON_ICON;
    fti.icon = FRONTIER_ICON_FILE_ALT;
    return fti;
}



