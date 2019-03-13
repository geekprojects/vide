
#include "project/project.h"

#include <geek/core-sha.h>

using namespace std;
using namespace Geek::Core;

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

    m_buffer = Buffer::loadFile((getProject()->getRootPath() + getFilePath()).c_str());
    if (m_buffer == NULL)
    {
        printf("ERROR: Failed to open file: %s\n", getFilePath().c_str());
        return NULL;
    }

    m_buffer->setProjectFile(this);

    getProject()->openEntrySignal().emit(this);

    return m_buffer;
}

string ProjectFile::calculateHash()
{
    return SHA::sha256File(getProject()->getRootPath() + getFilePath());
}

