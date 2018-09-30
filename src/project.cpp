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

#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <libfswatch/c++/event.hpp>
#include <libfswatch/c++/monitor.hpp>

using namespace std;

Project::Project(string rootPath)
{
    m_rootPath = rootPath;

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
    m_root = new ProjectDirectory(NULL, "");

    scanDirectory(m_root, m_rootPath);

    m_root->dump(0);
#if 0
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

        struct stat stat;
        string childPath = path + "/" + dirent->d_name;

        lstat(childPath.c_str(), &stat);
        if (S_ISDIR(stat.st_mode))
        {
            ProjectDirectory* child = new ProjectDirectory(entry, dirent->d_name);
            entry->addChild(child);
            scanDirectory(child, childPath);
        }
        else if (S_ISREG(stat.st_mode))
        {
            ProjectFile* child = new ProjectFile(entry, dirent->d_name);
            entry->addChild(child);
        }
    }

    return true;
}

ProjectEntry::ProjectEntry(ProjectEntryType type, ProjectEntry* parent, std::string name)
{
    m_type = type;
    m_parent = parent;
    m_name = name;
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

ProjectFile::ProjectFile(ProjectEntry* parent, std::string name) : ProjectEntry(ENTRY_FILE, parent, name)
{
}

ProjectFile::~ProjectFile()
{
}

ProjectDirectory::ProjectDirectory(ProjectEntry* parent, std::string name) : ProjectEntry(ENTRY_DIR, parent, name)
{
}

ProjectDirectory::~ProjectDirectory()
{
}

