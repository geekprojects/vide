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

#ifndef __VIDE_PROJECT_H_
#define __VIDE_PROJECT_H_

#include <string>
#include <vector>

#include <wchar.h>

enum ProjectEntryType
{
    ENTRY_PROJECT,
    ENTRY_DIR,
    ENTRY_FILE,
    ENTRY_UNKNOWN,
};

class Project;
class Editor;

class ProjectEntry
{
 private:
    Project* m_project;
    ProjectEntryType m_type;
    ProjectEntry* m_parent;
    std::string m_name;
    Editor* m_editor;

    std::vector<ProjectEntry*> m_children;

 public:
    ProjectEntry(Project* project, ProjectEntryType type, ProjectEntry* parent, std::string name);
    virtual ~ProjectEntry();

    Project* getProject() { return m_project; }
    ProjectEntryType getType() { return m_type; }
    std::string getName() { return m_name; }
    std::string getFilePath();

    void addChild(ProjectEntry* entry);
    std::vector<ProjectEntry*>& getChildren() { return m_children; }

    void setEditor(Editor* editor) { m_editor = editor; }
    Editor* getEditor() { return m_editor; }

    void dump(int level);
};

class ProjectFile : public ProjectEntry
{
 private:

 public:
    ProjectFile(Project* project, ProjectEntry* parent, std::string name);
    virtual ~ProjectFile();
};

class ProjectDirectory : public ProjectEntry
{
 private:

 public:
    ProjectDirectory(Project* project, ProjectEntry* parent, std::string name);
    virtual ~ProjectDirectory();

};

enum ProjectIndexEntryType
{
    INDEX_FILE,
    INDEX_SYMBOL,
};

class ProjectIndexEntry
{
 private:
    ProjectIndexEntryType m_type;

 public:
    ProjectIndexEntry();
    virtual ~ProjectIndexEntry();

    
};

class ProjectIndex
{
 private:

 public:
};

class Project
{
 private:
    std::string m_rootPath;

    ProjectDirectory* m_root;

    bool scanDirectory(ProjectDirectory* entry, std::string path);

 public:
    Project(std::string rootPath);
    ~Project();

    bool scan();

    std::string getRootPath() { return m_rootPath; }
    ProjectDirectory* getRoot() { return m_root; }
};

#endif
