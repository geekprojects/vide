
#include <vide/project.h>

using namespace std;
using namespace Geek;
using namespace Geek::Core;

static const char* ProjectDefinitionTypeString(ProjectDefinitionType type)
{
    switch (type)
    {
        case DEF_NONE:
            return "DEF_NONE";
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
        case DEF_PACKAGE:
            return "DEF_PACKAGE";
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
    else if (type == "DEF_PACKAGE")
    {
        return DEF_PACKAGE;
    }
    return DEF_UNKNOWN;
}

ProjectIndex::ProjectIndex(Project* project) : Logger("ProjectIndex")
{
    m_project = project;
    m_db = NULL;
    m_dbMutex = Thread::createMutex();
}

ProjectIndex::~ProjectIndex()
{
}

bool ProjectIndex::init()
{
    m_dbMutex->lock();
    m_db = new Database(m_project->getVidePath() + "/index.db");

    vector<Table> tables;

    Table entries;
    entries.name = "vide_entries";
    entries.columns.insert(Column("id", true, true));
    entries.columns.insert(Column("module_id"));
    entries.columns.insert(Column("parent_id"));
    entries.columns.insert(Column("path"));
    entries.columns.insert(Column("name"));
    entries.columns.insert(Column("type"));
    entries.columns.insert(Column("hash"));
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

    m_db->execute("CREATE INDEX IF NOT EXISTS vide_entries_parent_idx ON vide_entries (parent_id)");
    m_db->execute("CREATE UNIQUE INDEX IF NOT EXISTS vide_definitions_name_idx ON vide_definitions (name)");
    m_db->execute("CREATE INDEX IF NOT EXISTS vide_sources_def_idx ON vide_sources (definition_id)");
    m_db->execute("CREATE INDEX IF NOT EXISTS vide_sources_entry_idx ON vide_sources (entry_id)");

    m_dbMutex->unlock();

    return true;
}

void ProjectIndex::addEntry(ProjectEntry* entry)
{
    if (entry->getId() != 0)
    {
        // Already indexed?
        return;
    }

    m_dbMutex->lock();
    string sql = "SELECT id, hash FROM vide_entries WHERE module_id = ? AND path = ?";
    PreparedStatement* ps = m_db->prepareStatement(sql);
    ps->bindString(1, entry->getModule()->getId());
    ps->bindString(2, entry->getFilePath());
    ps->executeQuery();
    if (ps->step())
    {
        entry->setId(ps->getInt(0));
        entry->setHash(ps->getString(1));
    }
    else
    {
        int64_t parentId = 0;

        log(DEBUG, "addEntry: parent=%p", entry->getParent());
        if (entry->getParent() != NULL)
        {
            log(DEBUG, "addEntry: parent=%s, id=%lld", entry->getParent()->getName().c_str(), entry->getParent()->getId());
            parentId = entry->getParent()->getId();
            if (parentId == 0)
            {
                log(WARN, "addEntry:  -> LOOKING UP PARENT ENTITY");
            }
        }

        string insertSql = "INSERT INTO vide_entries (id, module_id, parent_id, path, name, type, updated) VALUES (null, ?, ?, ?, ?, ?, ?)";
        PreparedStatement* insertPs = m_db->prepareStatement(insertSql);
        insertPs->bindString(1, entry->getModule()->getId());
        insertPs->bindInt64(2, parentId);
        insertPs->bindString(3, entry->getFilePath());
        insertPs->bindString(4, entry->getName());
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
        insertPs->bindString(5, type);
        insertPs->bindInt64(6, 0);
        insertPs->execute();
        entry->setId(m_db->getLastInsertId());
        m_db->endTransaction();
        delete insertPs;
    }
    delete ps;

    m_dbMutex->unlock();
}

void ProjectIndex::updateEntry(ProjectEntry* entry)
{
    if (entry->getId() == 0)
    {
        // Not indexed?
        return;
    }
     
    string sql = "UPDATE vide_entries SET hash = ? WHERE id=?";

    m_dbMutex->lock();

    PreparedStatement* ps = m_db->prepareStatement(sql);
    ps->bindString(1, entry->getHash());
    ps->bindInt64(2, entry->getId());
    ps->execute();
    delete ps;

    m_dbMutex->unlock();
}

void ProjectIndex::removeSources(ProjectEntry* entry)
{
    string sql = "DELETE FROM vide_sources WHERE entry_id = ?";

    m_dbMutex->lock();
    PreparedStatement* ps = m_db->prepareStatement(sql);
    ps->bindInt64(1, entry->getId());
    ps->execute();

    delete ps;

    m_dbMutex->unlock();
}

ProjectDefinition* ProjectIndex::findDefinition(std::string name)
{
    string sql = "SELECT id, name, parent FROM vide_definitions WHERE name = ?";

    m_dbMutex->lock();

    PreparedStatement* ps = m_db->prepareStatement(sql);
    ps->bindString(1, name);
    ps->executeQuery();
    ProjectDefinition* def = NULL;
    if (ps->step())
    {
        def = createDefinition(ps);
    }

    delete ps;

    m_dbMutex->unlock();

    return def;
}

void ProjectIndex::addDefinition(ProjectDefinition* def)
{
    m_dbMutex->lock();

    m_db->startTransaction();
    if (def->id == 0)
    {
        string sql = "INSERT INTO vide_definitions (id, name, parent) VALUES (null, ?, ?)";

        vector<string> args;
        args.push_back(def->name);
        args.push_back(def->parentName);
        m_db->executeQuery(sql, args);
        def->id = m_db->getLastInsertId();

        log(DEBUG, "addDefinition: id=%lld", def->id);
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

    m_dbMutex->unlock();
}

vector<ProjectDefinition*> ProjectIndex::getEntryDefinitions(ProjectEntry* entry)
{
    vector<ProjectDefinition*> results;
    string sql = "SELECT d.id, d.name, d.parent FROM vide_definitions d WHERE EXISTS (SELECT 1 FROM vide_sources s WHERE s.definition_id = d.id AND s.entry_id=?)";

    m_dbMutex->lock();

    PreparedStatement* ps = m_db->prepareStatement(sql);
    ps->bindInt64(1, entry->getId());
    ps->executeQuery();
    while (ps->step())
    {
        ProjectDefinition* def = createDefinition(ps);

        log(DEBUG, "getEntryDefinitions: def=%s", def->name.c_str());

        results.push_back(def);
    }

    m_dbMutex->unlock();

    return results;
}

vector<ProjectDefinition*> ProjectIndex::getRootDefinitions()
{
    vector<ProjectDefinition*> results;
    string sql = "SELECT d.id, d.name, d.parent FROM vide_definitions d WHERE parent IS NULL OR parent = ''";

    m_dbMutex->lock();

    PreparedStatement* ps = m_db->prepareStatement(sql);
    ps->executeQuery();
    while (ps->step())
    {
        ProjectDefinition* def = createDefinition(ps);

        log(DEBUG, "getRootDefinitions: def=%s", def->name.c_str());

        results.push_back(def);
    }

    m_dbMutex->unlock();

    return results;
}

// The m_dbMutex must already be locked!
ProjectDefinition* ProjectIndex::createDefinition(Geek::Core::PreparedStatement* ps)
{
    ProjectDefinition* def = new ProjectDefinition();
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
        ProjectEntry* entry = m_project->getEntry(path);
        if (entry != NULL)
        {
            source.entry = m_project->getEntry(path);

#if 0
            log(DEBUG, "findDefinition: source: id=%lld -> path=%s, entry=%p", source.id, path.c_str(), source.entry);
#endif

            def->sources.push_back(source);
        }
    }

    return def;
}

