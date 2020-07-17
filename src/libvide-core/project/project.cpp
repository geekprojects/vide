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


#include <vide/project.h>
//#include "config.h"
#include <vide/vide.h>
#include <vide/utils.h>

#include <geek/core-file.h>
#include <geek/core-string.h>

#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#if 1
#include <libfswatch/c++/event.hpp>
#include <libfswatch/c++/monitor.hpp>
#endif

#include <vide/filetypemanager.h>

using namespace std;
using namespace Geek;

Project::Project(Vide* vide, string rootPath) : Logger("Project")
{
    m_vide = vide;

    char* rp = realpath(rootPath.c_str(), NULL);
    m_rootPath = string(rp);
    free(rp);
    log(DEBUG, "Project: m_rootPath=%s -> %s", rootPath.c_str(), m_rootPath.c_str());

    m_index = new ProjectIndex(this);
}

Project::~Project()
{

}

bool Project::init()
{
    m_config["version"] = "1.0";
    m_config["root"] = m_rootPath;

    ProjectModule* module = new ProjectModule(this, "root", L"Root", m_rootPath);
    module->init(m_config["modules"][0]);
    m_modules.push_back(module);

    m_index->init();

    return true;
}

bool Project::load()
{
    try
    {
        log(DEBUG, "Loading config: %s", getConfigPath().c_str());
        m_config = YAML::LoadFile(getConfigPath().c_str());
    }
    catch (const exception& e)
    {
        log(ERROR, "load: Failed to load project file: %s", e.what());
        return false;
    }

    for (YAML::Node node : m_config["modules"])
    {
        string id = node["id"].as<std::string>();
        wstring name = ::Utils::string2wstring(node["name"].as<std::string>());
        string path = node["path"].as<std::string>();
        ProjectModule* module = new ProjectModule(this, id, name, path);
        module->load(node);

        m_modules.push_back(module);
    }

    m_index->init();

    return true;
}

bool Project::save()
{
    YAML::Emitter emitter;

    emitter << m_config;

    FILE* fd = fopen(getConfigPath().c_str(), "w");
    fwrite(emitter.c_str(), emitter.size(), 1, fd);
    fclose(fd);

    return true;
}

string Project::getConfigPath()
{
    string videDir = getVidePath();
    Geek::Core::File::mkdirs(videDir); 
    return videDir + "/project.yml";
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
    for (ProjectModule* module : m_modules)
    {
        module->scan();
    }

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

bool Project::index()
{
    for (ProjectModule* module : m_modules)
    {
        module->index();
    }
    // XXX indexDirectory(m_root);
/*
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
*/

    return true;
}

ProjectEntry* Project::getEntry(string path)
{
#if 0
    vector<string> pathParts = Geek::Core::splitString(path, '/');

    ProjectEntry* pos = m_root;
    while (pos != NULL && !pathParts.empty())
    {
        string part = pathParts[0];
        pathParts.erase(pathParts.begin());

        if (part == ".")
        {
            continue;
        }

        pos = pos->getChild(part);
    }

    return pos;
#else
return NULL;
#endif
}


ProjectDefinition* Project::findDefinition(std::string name)
{
    return m_index->findDefinition(name);

    return NULL;
}

void Project::addDefinition(ProjectDefinition* def)
{
    m_index->addDefinition(def);
}

void Project::dumpStructure()
{
/*
    map<string, ProjectDefinition*>::iterator it;
    for (it = m_index.begin(); it != m_index.end(); it++)
    {
        ProjectDefinition* def = it->second;
        if (def->parent == NULL)
        {
            def->dump(1);
        }
    }
*/
}

ProjectDirectory::ProjectDirectory(ProjectModule* module, ProjectEntry* parent, std::string name)
    : ProjectEntry(module, ENTRY_DIR, parent, name)
{
}

ProjectDirectory::~ProjectDirectory()
{
}


bool ProjectDefinition::isSource(ProjectEntry* entry)
{
    if (entry->getId() == 0)
    {
        return false;
    }

    for (ProjectDefinitionSource source : sources)
    {
        if (source.entry != NULL && source.entry->getId() == entry->getId())
        {
            return true;
        }
    }
    return false;
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

FileIndexTask::FileIndexTask(ProjectFile* file) : Task()
{
    m_file = file;
    string title = string("Indexing file: ") + file->getName();
    setTitle(::Utils::string2wstring(title));
}

FileIndexTask::~FileIndexTask()
{
}

void FileIndexTask::run()
{
    m_file->getFileTypeManager()->index(m_file);
}

