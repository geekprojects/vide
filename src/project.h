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

class ProjectEntry
{
 private:
    ProjectEntryType m_type;
    ProjectEntry* m_parent;
    std::string m_name;

    std::vector<ProjectEntry*> m_children;

 public:
    ProjectEntry(ProjectEntryType type, ProjectEntry* parent, std::string name);
    virtual ~ProjectEntry();

    ProjectEntryType getType() { return m_type; }
    std::string getName() { return m_name; }

    void addChild(ProjectEntry* entry);
    std::vector<ProjectEntry*>& getChildren() { return m_children; }

    void dump(int level);
};

class ProjectFile : public ProjectEntry
{
 private:

 public:
    ProjectFile(ProjectEntry* parent, std::string name);
    virtual ~ProjectFile();
};

class ProjectDirectory : public ProjectEntry
{
 private:

 public:
    ProjectDirectory(ProjectEntry* parent, std::string name);
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

    ProjectDirectory* getRoot() { return m_root; }
};

#endif
