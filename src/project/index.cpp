
#include "project/project.h"

using namespace std;
using namespace Geek::Core;

static const char* ProjectDefinitionTypeString(ProjectDefinitionType type)
{
    switch (type)
    {
        case DEF_UNKNOWN:
            return "DEF_UNKNOWN";
        case DEF_NAMESPACE:
            return "DEF_NAMESPACE";
        case DEF_CLASS:
            return "DEF_CLASS";
        case DEF_CLASS_TEMPLATE:
            return "DEF_CLASS_TEMPLATE";
        case DEF_FUNCTION_SPEC:
            return "DEF_FUNCTION_SPEC";
        case DEF_FUNCTION_IMPL:
            return "DEF_FUNCTION_IMPL";
        case DEF_FUNCTION_TEMPLATE:
            return "DEF_FUNCTION_TEMPLATE";
        case DEF_FIELD:
            return "DEF_FIELD";
        case DEF_VARIABLE:
            return "DEF_VARIABLE";
        case DEF_ENUM:
            return "DEF_ENUM";
        case DEF_ENUM_CONSTANT:
            return "DEF_ENUM_CONSTANT";
        case DEF_TYPEDEF:
            return "DEF_TYPEDEF";
        default:
            return "DEF_UNKNOWN";
    }
}

static ProjectDefinitionType string2ProjectDefinitionType(string type)
{
    if (type == "DEF_NAMESPACE")
    {
        return DEF_NAMESPACE;
    }
    else if (type == "DEF_CLASS")
    {
        return DEF_CLASS;
    }
    else if (type == "DEF_CLASS_TEMPLATE")
    {
        return DEF_CLASS_TEMPLATE;
    }
    else if (type == "DEF_FUNCTION_SPEC")
    {
        return DEF_FUNCTION_SPEC;
    }
    else if (type == "DEF_FUNCTION_IMPL")
    {
        return DEF_FUNCTION_IMPL;
    }
    else if (type == "DEF_FUNCTION_TEMPLATE")
    {
        return DEF_FUNCTION_TEMPLATE;
    }
    else if (type == "DEF_FIELD")
    {
        return DEF_FIELD;
    }
    else if (type == "DEF_VARIABLE")
    {
        return DEF_VARIABLE;
    }
    else if (type == "DEF_ENUM")
    {
        return DEF_ENUM;
    }
    else if (type == "DEF_ENUM_CONSTANT")
    {
        return DEF_ENUM_CONSTANT;
    }
    else if (type == "DEF_TYPEDEF")
    {
        return DEF_TYPEDEF;
    }
    return DEF_UNKNOWN;
}

ProjectIndex::ProjectIndex(Project* project)
{
    m_project = project;
    m_db = NULL;
}

ProjectIndex::~ProjectIndex()
{
}

bool ProjectIndex::init()
{
    m_db = new Database(m_project->getVidePath() + "/index.db");

    vector<Table> tables;

    Table entries;
    entries.name = "vide_entries";
    entries.columns.insert(Column("id", true, true));
    entries.columns.insert(Column("parent_id"));
    entries.columns.insert(Column("path"));
    entries.columns.insert(Column("name"));
    entries.columns.insert(Column("type"));
    entries.columns.insert(Column("updated"));
    tables.push_back(entries);

    Table index;
    index.name = "vide_definitions";
    index.columns.insert(Column("id", true, true));
    index.columns.insert(Column("name"));
    index.columns.insert(Column("parent"));
    tables.push_back(index);

    Table sources;
    sources.name = "vide_sources";
    sources.columns.insert(Column("id", true, true));
    sources.columns.insert(Column("definition_id"));
    sources.columns.insert(Column("entry_id"));
    sources.columns.insert(Column("type"));
    sources.columns.insert(Column("line"));
    sources.columns.insert(Column("col"));
    tables.push_back(sources);

    m_db->checkSchema(tables);

    return true;
}

void ProjectIndex::addEntry(ProjectEntry* entry)
{
    if (entry->getId() != 0)
    {
        // Already indexed?
        return;
    }

    string sql = "SELECT id, type, updated FROM vide_entries WHERE path = ?";
    PreparedStatement* ps = m_db->prepareStatement(sql);
    ps->bindString(1, entry->getFilePath());
    ps->executeQuery();
    if (ps->step())
    {
        entry->setId(ps->getInt(0));
    }
    else
    {
int64_t parentId = 0;

        printf("ProjectIndex::addEntry: parent=%p\n", entry->getParent());
        if (entry->getParent() != NULL)
        {
            printf("ProjectIndex::addEntry: parent=%s, id=%lld\n", entry->getParent()->getName().c_str(), entry->getParent()->getId());
            parentId = entry->getParent()->getId();
            if (parentId == 0)
            {
                printf("ProjectIndex::addEntry:  -> LOOKING UP PARENT ENTITY\n");
            }
        }

        string insertSql = "INSERT INTO vide_entries (id, parent_id, path, name, type, updated) VALUES (null, ?, ?, ?, ?, ?)";
        PreparedStatement* insertPs = m_db->prepareStatement(insertSql);
        insertPs->bindInt64(1, parentId);
        insertPs->bindString(2, entry->getFilePath());
        insertPs->bindString(3, entry->getName());
        string type;
        switch (entry->getType())
        {
            case ENTRY_PROJECT:
                type = "PROJECT";
                break;
            case ENTRY_DIR:
                type = "DIR";
                break;
            case ENTRY_FILE:
                type = "FILE";
                break;
            default:
                type = "UNKNOWN";
                break;
        }
        insertPs->bindString(4, type);
        insertPs->bindInt64(5, 0);
        insertPs->execute();
        entry->setId(m_db->getLastInsertId());
        m_db->endTransaction();
        delete insertPs;
    }
    delete ps;
}

ProjectDefinition* ProjectIndex::findDefinition(std::string name)
{
    string sql = "SELECT id, name, parent FROM vide_definitions WHERE name = ?";

    PreparedStatement* ps = m_db->prepareStatement(sql);
    ps->bindString(1, name);
    ps->executeQuery();
    ProjectDefinition* def = NULL;
    if (ps->step())
    {
        def = new ProjectDefinition();
        def->id = ps->getInt(0);
        def->name = ps->getString(1);
        def->parentName = ps->getString(2);

        string sourcesSql = "SELECT s.id, s.entry_id, s.type, s.line, s.col, e.path FROM vide_sources s JOIN vide_entries e on e.id = s.entry_id WHERE definition_id=?";
        PreparedStatement* sourcesPs = m_db->prepareStatement(sourcesSql);
        sourcesPs->bindInt64(1, def->id);
        sourcesPs->executeQuery();
        while (sourcesPs->step())
        {
            ProjectDefinitionSource source;
            source.id = sourcesPs->getInt(0);
            source.type = string2ProjectDefinitionType(sourcesPs->getString(2));
            int64_t line = sourcesPs->getInt64(3);
            int64_t col = sourcesPs->getInt64(4);
            source.position = Position(line, col);

            string path = sourcesPs->getString(5);
            source.entry = m_project->getEntry(path);

            printf("ProjectIndex::findDefinition: source: id=%lld -> path=%s, entry=%p\n", source.id, path.c_str(), source.entry);

def->sources.push_back(source);
        }
        delete sourcesPs;
    }

    delete ps;

    return def;
}

void ProjectIndex::addDefinition(ProjectDefinition* def)
{
    printf("ProjectIndex::addDefinition: Here!\n");
    m_db->startTransaction();
    if (def->id == 0)
    {
        printf("ProjectIndex::addDefinition: Saving...\n");

        string sql = "INSERT INTO vide_definitions (id, name, parent) VALUES (null, ?, ?)";

        vector<string> args;
        args.push_back(def->name);
        args.push_back(def->parentName);
        m_db->executeQuery(sql, args);
        def->id = m_db->getLastInsertId();

        printf("ProjectIndex::addDefinition: id=%lld\n", def->id);
    }

    // Save entries
    for (ProjectDefinitionSource& source : def->sources)
    {
        if (source.id == 0)
        {
            string sql = "INSERT INTO vide_sources (id, definition_id, entry_id, type, line, col) VALUES (null, ?, ?, ?, ?, ?)";
            PreparedStatement* ps = m_db->prepareStatement(sql);
            ps->bindInt64(1, def->id);
            ps->bindInt64(2, source.entry->getId());
            ps->bindString(3, ProjectDefinitionTypeString(source.type));
            ps->bindInt64(4, source.position.line);
            ps->bindInt64(5, source.position.column);
            ps->execute();
            source.id = m_db->getLastInsertId();
            delete ps;
        }
    }
    m_db->endTransaction();
}

