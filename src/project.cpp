/*
 * Vide - Vi IDE
 * Copyright (C) 2018 Ian Parker <ian@geekprojects.com>
 *
 * This file is part of Vide.
 *
 * Vide is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Vide is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Vide.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "project.h"
#include "config.h"

#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#if 1
#include <libfswatch/c++/event.hpp>
#include <libfswatch/c++/monitor.hpp>
#endif

#include "filetypemanager.h"
#ifdef HAS_LIBCLANG
#include "cxxfiletypemanager.h"
#endif

using namespace std;

Project::Project(string rootPath)
{
    m_rootPath = rootPath;

    // Push in order that they should be evaluated
#ifdef HAS_LIBCLANG
    m_fileTypeManagers.push_back(new CXXFileTypeManager(this));
#endif
    m_fileTypeManagers.push_back(new TextFileTypeManager(this));

    m_root = NULL;
}

Project::~Project()
{

}

void process_events(const vector<fsw::event>& events, void *context)
{
    for (const fsw::event& evt : events)
    {
        printf("process_events: %s\n", evt.get_path().c_str());
    }
}

bool Project::scan()
{
    m_root = new ProjectDirectory(this, NULL, "");

    scanDirectory(m_root, m_rootPath);

#if 0
    m_root->dump(0);

    vector<string> paths;
    paths.push_back(m_rootPath);
    fsw::monitor* monitor = fsw::monitor_factory::create_monitor(fsw_monitor_type::system_default_monitor_type, paths, process_events);

    monitor->set_recursive(true);
    monitor->start();
#endif

    return true;
}

bool Project::scanDirectory(ProjectDirectory* entry, std::string path)
{
    DIR* fd;
    dirent* dirent;

    printf("Project::scanDirectory: Scanning %s\n", path.c_str());

    fd = opendir(path.c_str());
    if (fd == NULL)
    {
        return false;
    }

    while ((dirent = readdir(fd)) != NULL)
    {
        if (dirent->d_name[0] == '.')
        {
            continue;
        }

    string name = string(dirent->d_name);
    size_t pos = name.rfind(".");
    string ext = "";
    if (pos != string::npos)
    {
        ext = name.substr(pos + 1);
    }

    if (ext == "o" || ext == "dSYM")
    {
        continue;
    }

        struct stat stat;
        string childPath = path + "/" + dirent->d_name;

        lstat(childPath.c_str(), &stat);
        if (S_ISDIR(stat.st_mode))
        {
            ProjectDirectory* child = new ProjectDirectory(this, entry, dirent->d_name);
            entry->addChild(child);
            scanDirectory(child, childPath);
        }
        else if (S_ISREG(stat.st_mode))
        {
            ProjectFile* child = new ProjectFile(this, entry, dirent->d_name);

            for (FileTypeManager* ftm : m_fileTypeManagers)
            {
                bool canHandle;
                canHandle = ftm->canHandle(child);
                if (canHandle)
                {
                    child->setFileTypeManager(ftm);
                    break;
                }
            }

            entry->addChild(child);
        }
    }

    return true;
}

bool Project::index()
{
    indexDirectory(m_root);

    // Resolve all parents
    map<std::string, ProjectDefinition*>::iterator it;
    for (it = m_index.begin(); it != m_index.end(); it++)
    {
        ProjectDefinition* def = it->second;
        if (def->parent == NULL && def->parentName != "")
        {
            def->parent = findDefinition(def->parentName);
        }
    }

    return true;
}

bool Project::indexDirectory(ProjectDirectory* dir)
{
    for (ProjectEntry* entry : dir->getChildren())
    {
        switch (entry->getType())
        {
            case ENTRY_FILE:
                entry->getFileTypeManager()->index((ProjectFile*)entry);
                break;
            case ENTRY_DIR:
                indexDirectory((ProjectDirectory*)entry);
                break;
            default:
                break;
        }
    }
    return true;
}

ProjectDefinition* Project::findDefinition(std::string name)
{
    map<string, ProjectDefinition*>::iterator it = m_index.find(name);
    if (it != m_index.end())
    {
        return it->second;
    }
    return NULL;
}

void Project::addDefinition(ProjectDefinition* def)
{
    m_index.insert(make_pair(def->name, def));
}

void Project::dumpStructure()
{
    map<string, ProjectDefinition*>::iterator it;
    for (it = m_index.begin(); it != m_index.end(); it++)
    {
        ProjectDefinition* def = it->second;
        if (def->parent == NULL)
        {
            def->dump(1);
        }
    }
}

ProjectEntry::ProjectEntry(Project* project, ProjectEntryType type, ProjectEntry* parent, std::string name)
{
    m_project = project;
    m_type = type;
    m_parent = parent;
    m_name = name;
    m_editor = NULL;

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
        path = m_project->getRootPath();
    }

    path += "/" + m_name;
    return path;
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

ProjectFile::ProjectFile(Project* project, ProjectEntry* parent, std::string name)
    : ProjectEntry(project, ENTRY_FILE, parent, name)
{
}

ProjectFile::~ProjectFile()
{
}


ProjectDirectory::ProjectDirectory(Project* project, ProjectEntry* parent, std::string name)
    : ProjectEntry(project, ENTRY_DIR, parent, name)
{
}

ProjectDirectory::~ProjectDirectory()
{
}


void ProjectDefinition::dump(int level)
{
    string spaces = "";
    int i;
    for (i = 0; i < level; i++)
    {
        spaces += "    ";
    }

    printf("ProjectDefinition::dump:%s%s\n", spaces.c_str(), name.c_str());

    for (ProjectDefinitionSource source : sources)
    {
        printf("ProjectDefinition::dump:%s -> %s, line %u, type=%u\n", spaces.c_str(), source.entry->getFilePath().c_str(), source.position.line, source.type);
    }

    for (ProjectDefinition* child : children)
    {
        child->dump(level + 1);
    }
}

