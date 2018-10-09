
#include "filetypemanager.h"

FileTypeManager::FileTypeManager()
{
}

FileTypeManager::~FileTypeManager()
{
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



