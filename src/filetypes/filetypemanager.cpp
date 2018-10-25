
#include "filetypemanager.h"
#include "project.h"

FileTypeManager::FileTypeManager(Project* project)
{
    m_project = project;
}

FileTypeManager::~FileTypeManager()
{
}

bool FileTypeManager::canHandle(ProjectFile* file)
{
    return false;
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

TextFileTypeManager::TextFileTypeManager(Project* project) : FileTypeManager(project)
{
    m_tokeniser = new SimpleTokeniser();
}

TextFileTypeManager::~TextFileTypeManager()
{
    delete m_tokeniser;
}

bool TextFileTypeManager::canHandle(ProjectFile* file)
{
    // We'll take anything!
    return true;
}



