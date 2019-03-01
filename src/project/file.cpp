
#include "project/project.h"

ProjectFile::ProjectFile(Project* project, ProjectEntry* parent, std::string name)
    : ProjectEntry(project, ENTRY_FILE, parent, name)
{
    m_buffer = NULL;
}

ProjectFile::~ProjectFile()
{
}

Buffer* ProjectFile::open()
{
    if (m_buffer != NULL)
    {
        return m_buffer;
    }

    m_buffer = Buffer::loadFile(getFilePath().c_str());
    if (m_buffer == NULL)
    {
        printf("ERROR: Failed to open file: %s\n", getFilePath().c_str());
        return NULL;
    }

    m_buffer->setProjectFile(this);

    getProject()->openEntrySignal().emit(this);

    return m_buffer;
}

