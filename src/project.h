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
#include <map>

#include <wchar.h>

#include <sigc++/sigc++.h>

#include "filetypes/filetypemanager.h"
#include "editor/buffer.h"

class Vide;
class Project;
class ProjectEntry;
class Editor;
class FileTypeManager;
struct FileTypeManagerData;

enum ProjectDefinitionType
{
    DEF_NAMESPACE,
    DEF_CLASS,
    DEF_CLASS_TEMPLATE,
    DEF_FUNCTION_SPEC,
    DEF_FUNCTION_IMPL,
    DEF_FUNCTION_TEMPLATE,
    DEF_FIELD,
    DEF_VARIABLE,
    DEF_ENUM,
    DEF_ENUM_CONSTANT,
    DEF_TYPEDEF,
};

struct ProjectDefinitionSource
{
    ProjectEntry* entry;
    Position position;
    ProjectDefinitionType type;
};

struct ProjectDefinition
{
    std::vector<ProjectDefinitionSource> sources;
    std::string name;
    std::string parentName;
    ProjectDefinition* parent;
    std::vector<ProjectDefinition*> children;

    ProjectEntry* entry;

    void dump(int level);
};

enum ProjectEntryType
{
    ENTRY_PROJECT,
    ENTRY_DIR,
    ENTRY_FILE,
    ENTRY_UNKNOWN,
};

class ProjectEntry
{
 private:
    Project* m_project;
    ProjectEntryType m_type;
    ProjectEntry* m_parent;
    std::string m_name;
    Editor* m_editor;

    FileTypeManager* m_fileTypeManager;
    FileTypeManagerData* m_fileTypeManagerData;

    std::vector<ProjectEntry*> m_children;
    std::map<std::string, ProjectDefinition*> m_index;

 public:
    ProjectEntry(Project* project, ProjectEntryType type, ProjectEntry* parent, std::string name);
    virtual ~ProjectEntry();

    Project* getProject() { return m_project; }
    ProjectEntryType getType() { return m_type; }
    std::string getName() { return m_name; }
    std::string getFilePath();
    std::string getFileDir();

    void addChild(ProjectEntry* entry);
    std::vector<ProjectEntry*>& getChildren() { return m_children; }

    virtual Buffer* open();

    void setEditor(Editor* editor) { m_editor = editor; }
    Editor* getEditor() { return m_editor; }

    void setFileTypeManager(FileTypeManager* ftm) { m_fileTypeManager = ftm; }
    FileTypeManager* getFileTypeManager() { return m_fileTypeManager; }
    void setFileTypeManagerData(FileTypeManagerData* ftmd) { m_fileTypeManagerData = ftmd; }
    FileTypeManagerData* getFileTypeManagerData() { return m_fileTypeManagerData; }

    void addDefinition(ProjectDefinition* def);
    void dumpDefinitions();
    std::map<std::string, ProjectDefinition*>& getIndex() { return m_index; }

    void dump(int level);
};

class ProjectFile : public ProjectEntry
{
 private:
    Buffer* m_buffer;

 public:
    ProjectFile(Project* project, ProjectEntry* parent, std::string name);
    virtual ~ProjectFile();

    virtual Buffer* open();
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
    Vide* m_vide;
    std::string m_rootPath;

    ProjectDirectory* m_root;

    std::map<std::string, ProjectDefinition*> m_index;

    sigc::signal<void, ProjectEntry*> m_openEntrySignal;

    bool scanDirectory(ProjectDirectory* entry, std::string path);
    bool indexDirectory(ProjectDirectory* dir);

 public:
    Project(Vide* vide, std::string rootPath);
    ~Project();

    bool scan();
    bool index();

    std::string getRootPath() { return m_rootPath; }
    ProjectDirectory* getRoot() { return m_root; }

    ProjectDefinition* findDefinition(std::string name);
    void addDefinition(ProjectDefinition* def);
    std::map<std::string, ProjectDefinition*>& getIndex() { return m_index; }

    sigc::signal<void, ProjectEntry*> openEntrySignal() { return m_openEntrySignal; }

    void dumpStructure();
};

#endif
