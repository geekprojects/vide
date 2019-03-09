
#include "project/project.h"

using namespace std;
using namespace Geek;

ProjectEntry::ProjectEntry(Project* project, ProjectEntryType type, ProjectEntry* parent, std::string name)
{
    m_id = 0;
    m_project = project;
    m_type = type;
    m_parent = parent;
    m_name = name;
    m_editor = NULL;

    m_updated = false;
    m_indexed = false;

    m_fileTypeManager = NULL;
    m_fileTypeManagerData = NULL;
}

ProjectEntry::~ProjectEntry()
{
}

void ProjectEntry::addChild(ProjectEntry* entry)
{
    m_children.push_back(entry);
}

ProjectEntry* ProjectEntry::getChild(string name)
{
    for (ProjectEntry* child : m_children)
    {
        if (child->getName() == name)
        {
            return child;
        }
    }
    return NULL;
}

Buffer* ProjectEntry::open()
{
    return NULL;
}

void ProjectEntry::dump(int level)
{
    string spaces = "";
    int i;
    for (i = 0; i < level + 1; i++)
    {
        spaces += "  ";
    }
    printf("ProjectEntry::dump:%s%d - %s\n", spaces.c_str(), m_type, m_name.c_str());
    vector<ProjectEntry*>::iterator it;
    for (it = m_children.begin(); it != m_children.end(); it++)
    {
        ProjectEntry* entry = *it;
        entry->dump(level + 1);
    }
}

string ProjectEntry::getFilePath()
{
    string path = "";
    if (m_parent != NULL)
    {
        path = m_parent->getFilePath();
    }
    else
    {
        //path = m_project->getRootPath();
    }

    unsigned int size = path.length();
    if (path.length() == 0 || path.substr(size -1, 1) != "/")
    {
        path += "/";
    }

    path += m_name;
    return path;
}

string ProjectEntry::getFileDir()
{
    if (m_parent != NULL)
    {
        return m_parent->getFilePath();
    }
    else
    {
        return m_project->getRootPath();
    }
}

string ProjectEntry::getAbsolutePath()
{
    return m_project->getRootPath() + getFilePath();
}

void ProjectEntry::addDefinition(ProjectDefinition* def)
{
    m_index.insert(make_pair(def->name, def));
}

void ProjectEntry::dumpDefinitions()
{
    map<string, ProjectDefinition*>::iterator it;

    for (it = m_index.begin(); it != m_index.end(); it++)
    {
        printf("ProjectEntry::dumpDefinitions: %s: %s\n", m_name.c_str(), it->second->name.c_str());
    }
}

