
#include <vide/project.h>

#include <geek/core-sha.h>

using namespace std;
using namespace Geek::Core;

ProjectFile::ProjectFile(ProjectModule* module, ProjectEntry* parent, std::string name)
    : ProjectEntry(module, ENTRY_FILE, parent, name)
{
    m_buffer = NULL;
    m_hasBuildArgs = false;
    m_tokeniseData = NULL;
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

    m_buffer = Buffer::loadFile((getModule()->getRootPath() + getFilePath()).c_str());
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
    return SHA::sha256File(getModule()->getRootPath() + getFilePath());
}

void ProjectFile::setBuildArgs(std::vector<string> args)
{
    m_hasBuildArgs = true;
    m_buildArgs = args;
}

