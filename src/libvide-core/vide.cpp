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


#include <vide/vide.h>
#include <vide/plugins.h>

#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define PROJECT_FILE ".vide"

#define STRINGIFY(x) XSTRINGIFY(x)
#define XSTRINGIFY(x) #x

using namespace std;
using namespace Geek;
using namespace Geek::Core;

Vide::Vide() : Logger("Vide")
{
    m_taskExecutor = NULL;
    m_timerManager = NULL;
    m_pluginManager = NULL;
}

Vide::~Vide()
{
    if (m_taskExecutor != NULL)
    {
        delete m_taskExecutor;
    }
    if (m_timerManager != NULL)
    {
        delete m_timerManager;
    }
    if (m_pluginManager != NULL)
    {
        delete m_pluginManager;
    }
}

bool Vide::init()
{
    m_taskExecutor = new TaskExecutor(2);

    m_timerManager = new TimerManager();
    m_timerManager->start();

    m_pluginManager = new VidePluginManager();
    m_pluginManager->init(this);

    return true;
}

void Vide::registerFileTypeManager(FileTypeManager* ftm)
{
    m_fileTypeManagers.push_back(ftm);
}

FileTypeManager* Vide::findFileTypeManager(ProjectFile* file)
{
    FileTypeManager* selected = NULL;
    FileHandlerPriority selectedPriority = PRIORITY_UNSUPPORTED;
    for (FileTypeManager* ftm : m_fileTypeManagers)
    {
        FileHandlerPriority priority;
        priority = ftm->canHandle(file);
        if (priority != PRIORITY_UNSUPPORTED)
        {
            if (selected == NULL || priority > selectedPriority)
            {
                selected = ftm;
                selectedPriority = priority;
            }
        }
    }

    return selected;
}

void Vide::registerBuildTool(BuildTool* ftm)
{
    m_buildTools.push_back(ftm);
}

BuildTool* Vide::findBuildTool(ProjectModule* module)
{
    BuildTool* selected = NULL;
    FileHandlerPriority selectedPriority = PRIORITY_UNSUPPORTED;
    for (BuildTool* bt : m_buildTools)
    {
        FileHandlerPriority priority;
        priority = bt->canHandle(module);
        if (priority != PRIORITY_UNSUPPORTED)
        {
            if (selected == NULL || priority > selectedPriority)
            {
                selected = bt;
                selectedPriority = priority;
            }
        }
    }

    return selected;
}

Project* Vide::openProject(string path)
{
    log(DEBUG, "openProject: path=%s", path.c_str());
    unsigned int len = path.length();
    unsigned int projectFileLen = strlen(PROJECT_FILE);

    struct stat pathStat;
    int res = stat(path.c_str(), &pathStat);
    if (res != 0)
    {
        int err = errno;
        log(ERROR, "openProject: Failed to stat path: %s", strerror(err));
        return NULL;
    }

    bool isDir = S_ISDIR(pathStat.st_mode);

    if (!isDir)
    {
        if (len > projectFileLen && path.substr(len - projectFileLen) == PROJECT_FILE)
        {
            log(DEBUG, "openProject: Found project file");
            unsigned int len = path.length();
            path = path.substr(0, (len - projectFileLen));
            log(DEBUG, "openProject: path(2)=%s", path.c_str());
        }
        else
        {
            log(ERROR, "openProject: Not a vide.project file");
            return NULL;
        }
    }
    else
    {
        res = access((path + "/" + PROJECT_FILE).c_str(), R_OK);
        if (res != 0)
        {
            log(ERROR, "openProject: Specified path doesn't contain a Vide project file. Create a project first!");
            return NULL;
        }
    }

    Project* project = new Project(this, path);
    bool loaded;
    loaded = project->load();
    if (!loaded)
    {
        delete project;
        return NULL;
    }

    project->scan();
    project->index();

    //VideWindow* window = new VideWindow(this, project);
    //m_videWindows.push_back(window);

    m_openProjectSignal.emit(project);

    //window->show();

    return project;
}

string Vide::getDataPath()
{
    return string(STRINGIFY(DATADIR));
}

