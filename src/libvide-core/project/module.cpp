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

ProjectModule::ProjectModule(Project* project, std::string id, std::wstring name, std::string path)
    : Logger("ProjectModule")
{
    m_project = project;
    m_id = id;
    m_name = name;
    m_path = path;
}

ProjectModule::~ProjectModule()
{
}

bool ProjectModule::init(YAML::Node config)
{
    config["id"] = "root";
    config["name"] = "Root";
    config["path"] = m_path;

    m_buildTool = m_project->getVide()->findBuildTool(this);
    if (m_buildTool != NULL)
    {
        log(DEBUG, "init: buildTool: %s", m_buildTool->getPluginName().c_str());
        config["buildTool"]["name"] = m_buildTool->getPluginName();
    }
    else
    {
        log(WARN, "init: Unable to detect build tool");
    }

    return true;
}

bool ProjectModule::load(YAML::Node config)
{
    if (config["buildTool"]["name"])
    {
        string buildToolName = config["buildTool"]["name"].as<std::string>();
        m_buildTool = (BuildTool*)m_project->getVide()->getPluginManager()->findPlugin(buildToolName);
    }

    return true;
}

bool ProjectModule::scan()
{
    m_root = new ProjectDirectory(this, NULL, "");
    m_project->getIndex()->addEntry(m_root);

    scanDirectory(m_root, m_path);

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

bool ProjectModule::index()
{
    indexDirectory(m_root);

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

bool ProjectModule::scanDirectory(ProjectDirectory* entry, std::string path)
{
    DIR* fd;
    dirent* dirent;

    log(DEBUG, "scanDirectory: Scanning %s", path.c_str());

    fd = opendir(path.c_str());
    if (fd == NULL)
    {
        return false;
    }

    vector<string> names;
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

        if (ext == "o" || ext == "dSYM" || ext == "Plo" || ext == "a" || ext == "la" || ext == "la" || ext == "lo")
        {
            continue;
        }
        names.push_back(dirent->d_name);
    }

    std::sort(names.begin(), names.end());

    for (string name : names)
    {
        struct stat stat;
        string childPath = path + "/" + name;

        lstat(childPath.c_str(), &stat);
        if (S_ISDIR(stat.st_mode))
        {
            ProjectDirectory* child = new ProjectDirectory(this, entry, name);
            m_project->getIndex()->addEntry(child);
            entry->addChild(child);
            scanDirectory(child, childPath);
        }
        else if (S_ISREG(stat.st_mode))
        {
            ProjectFile* child = new ProjectFile(this, entry, name);
            m_project->getIndex()->addEntry(child);

            FileTypeManager* ftm = m_project->getVide()->findFileTypeManager(child);
            if (ftm != NULL)
            {
                child->setFileTypeManager(ftm);
           }

            entry->addChild(child);
        }
    }

    return true;
}

bool ProjectModule::indexDirectory(ProjectDirectory* dir)
{
    for (ProjectEntry* entry : dir->getChildren())
    {
        switch (entry->getType())
        {
            case ENTRY_FILE:
                indexFile((ProjectFile*)entry);
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

bool ProjectModule::indexFile(ProjectFile* file)
{
    string hash = file->calculateHash();

    if (hash != file->getHash())
    {
        log(DEBUG, "indexFile: File modified: %s", file->getFilePath().c_str());
        file->setHash(hash);

        m_project->getIndex()->removeSources(file);
        m_project->getIndex()->updateEntry(file);

        m_project->getVide()->getTaskExecutor()->addTask(new FileIndexTask(file));
        //file->getFileTypeManager()->index(file);
    }

    return true;
}

