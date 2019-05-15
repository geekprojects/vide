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

#include <geek/core-database.h>
#include <geek/core-thread.h>

#include <yaml-cpp/yaml.h>
#include <sigc++/sigc++.h>

#include <vide/filetypemanager.h>
#include <vide/buffer.h>

class Vide;
class Project;
class ProjectEntry;
class Editor;
class BuildTool;
class FileTypeManager;
struct FileTypeManagerData;

enum ProjectDefinitionType
{
    DEF_UNKNOWN,
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
    int64_t id;

    ProjectEntry* entry;
    Position position;
    ProjectDefinitionType type;

    ProjectDefinitionSource()
    {
        id = 0;
    }
};

struct ProjectDefinition
{
    int64_t id;
    std::vector<ProjectDefinitionSource> sources;
    std::string name;
    std::string parentName;
    ProjectDefinition* parent;
    std::vector<ProjectDefinition*> children;

    ProjectEntry* entry;

    ProjectDefinition()
    {
        id = 0;
    }

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
    int64_t m_id;
    Project* m_project;
    ProjectEntryType m_type;
    ProjectEntry* m_parent;
    std::string m_name;
    Editor* m_editor;

    bool m_indexed;
    std::string m_hash;

    FileTypeManager* m_fileTypeManager;
    FileTypeManagerData* m_fileTypeManagerData;

    std::vector<ProjectEntry*> m_children;

 public:
    ProjectEntry(Project* project, ProjectEntryType type, ProjectEntry* parent, std::string name);
    virtual ~ProjectEntry();

    void setId(int64_t id) { m_id = id; }
    int64_t getId() { return m_id; }

    Project* getProject() { return m_project; }
    ProjectEntryType getType() { return m_type; }
    std::string getName() { return m_name; }
    std::string getFilePath();
    std::string getFileDir();
    std::string getAbsolutePath();

    void addChild(ProjectEntry* entry);
    std::vector<ProjectEntry*>& getChildren() { return m_children; }
    ProjectEntry* getChild(std::string name);
    ProjectEntry* getParent() { return m_parent; }

    virtual Buffer* open();

    virtual std::string calculateHash();

    void setEditor(Editor* editor) { m_editor = editor; }
    Editor* getEditor() { return m_editor; }

    void setIndexed(bool indexed) { m_indexed = indexed; }
    bool setIndexed() { return m_indexed; }
    void setHash(std::string hash) { m_hash = hash; }
    std::string getHash() { return m_hash; }

    void setFileTypeManager(FileTypeManager* ftm) { m_fileTypeManager = ftm; }
    FileTypeManager* getFileTypeManager() { return m_fileTypeManager; }
    void setFileTypeManagerData(FileTypeManagerData* ftmd) { m_fileTypeManagerData = ftmd; }
    FileTypeManagerData* getFileTypeManagerData() { return m_fileTypeManagerData; }

    void addDefinition(ProjectDefinition* def);
    void dumpDefinitions();

    void dump(int level);
};

class ProjectFile : public ProjectEntry
{
 private:
    Buffer* m_buffer;

    bool m_hasBuildArgs;
    std::vector<std::string> m_buildArgs;

    void* m_tokeniseData;

 public:
    ProjectFile(Project* project, ProjectEntry* parent, std::string name);
    virtual ~ProjectFile();

    virtual Buffer* open();

    virtual std::string calculateHash();

    void setBuildArgs(std::vector<std::string> args);
    std::vector<std::string> getBuildArgs() { return m_buildArgs; }
    bool hasBuildArgs() { return m_hasBuildArgs; }

    void setTokeniseData(void* data) { m_tokeniseData = data; }
    void* getTokeniseData() { return m_tokeniseData; }
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

class ProjectIndex : public Geek::Logger
{
 private:
    Project* m_project;
    Geek::Core::Database* m_db;
    Geek::Mutex* m_dbMutex;

    ProjectDefinition* createDefinition(Geek::Core::PreparedStatement* ps);

 public:
    ProjectIndex(Project* project);
    ~ProjectIndex();

    bool init();

    void addEntry(ProjectEntry* entry);
    void updateEntry(ProjectEntry* entry);

    void removeSources(ProjectEntry* entry);

    ProjectDefinition* findDefinition(std::string name);
    void addDefinition(ProjectDefinition* def);
    std::vector<ProjectDefinition*> getEntryDefinitions(ProjectEntry* entry);
    std::vector<ProjectDefinition*> getRootDefinitions();
};

class Project : public Geek::Logger
{
 private:
    Vide* m_vide;
    std::string m_rootPath;

    YAML::Node m_config;

    ProjectDirectory* m_root;

    BuildTool* m_buildTool;

    ProjectIndex* m_index;

    sigc::signal<void, ProjectEntry*> m_openEntrySignal;

    bool scanDirectory(ProjectDirectory* entry, std::string path);
    bool indexDirectory(ProjectDirectory* dir);
    bool indexFile(ProjectFile* file);

 public:
    Project(Vide* vide, std::string rootPath);
    ~Project();

    bool init();
    bool load();
    bool save();

    YAML::Node& getConfig() { return m_config; }

    bool scan();
    bool index();

    Vide* getVide() { return m_vide; }
    std::string getRootPath() { return m_rootPath; }
    std::string getVidePath() { return getRootPath() + "/.vide"; }
    std::string getConfigPath();

    ProjectDirectory* getRoot() { return m_root; }
    ProjectEntry* getEntry(std::string path);

    ProjectIndex* getIndex() { return m_index; }
    ProjectDefinition* findDefinition(std::string name);
    void addDefinition(ProjectDefinition* def);

    BuildTool* getBuildTool() { return m_buildTool; }

    sigc::signal<void, ProjectEntry*> openEntrySignal() { return m_openEntrySignal; }

    void dumpStructure();
};

class FileIndexTask : public Geek::Core::Task
{
 private:
    ProjectFile* m_file;

 public:
    FileIndexTask(ProjectFile* file);
    virtual ~FileIndexTask();

    virtual void run();
};

#endif
