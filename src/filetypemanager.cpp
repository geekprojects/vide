
#include "filetypemanager.h"
#include "project.h"

FileTypeManager::FileTypeManager()
{
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

TextFileTypeManager::TextFileTypeManager()
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



