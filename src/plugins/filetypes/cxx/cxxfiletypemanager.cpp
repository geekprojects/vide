
#include <string.h>

#include "cxxfiletypemanager.h"
#include <vide/buffer.h>
#include <vide/project.h>
#include <vide/utils.h>

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;

VIDE_PLUGIN(CXXFileTypeManager);

CXXFileTypeManager::CXXFileTypeManager(Vide* vide) : FileTypeManager(vide)
{
    m_tokeniser = new CXXTokeniser(this);

    m_index = clang_createIndex(1, 1);
    clang_CXIndex_setGlobalOptions(m_index, CXGlobalOpt_ThreadBackgroundPriorityForAll);

    m_iconSurface = Surface::loadPNG(vide->getDataPath() + "/icons/cpp_256x256.png");
}

CXXFileTypeManager::~CXXFileTypeManager()
{
  clang_disposeIndex(m_index);
}

FileHandlerPriority CXXFileTypeManager::canHandle(ProjectFile* file)
{
    string name = file->getName();
    size_t pos = name.rfind(".");
    string ext = "";

    if (pos != string::npos)
    {
        ext = name.substr(pos + 1);
    }

    // We handle C, C++, ObjC, ObjC++
    if (ext == "cpp" || ext == "c" || ext == "h" || ext == "mm" || ext == "m")
    {
        return PRIORITY_HIGH;
    }

    return PRIORITY_UNSUPPORTED;
}

bool CXXFileTypeManager::index(ProjectFile* file)
{
    Project* project = file->getProject();

    YAML::Node config = project->getConfig();
    if (!config["filetypes"]["cxx"])
    {
        YAML::Node cxxflags;
        cxxflags.push_back("-Wall");
        cxxflags.push_back("-Werror");
    }

    CXTranslationUnit unit = parse(file, NULL);
    if (unit == NULL)
    {
        return false;
    }

    indexStructure(unit, file);

    //clang_disposeTranslationUnit(unit);

    return true;
}

struct StructureVisitorData
{
    CXXFileTypeManager* ftm;
    ProjectFile* file;
};

static CXChildVisitResult structureVisitorFunc(CXCursor cursor, CXCursor parent, CXClientData client_data)
{
    StructureVisitorData* data = (StructureVisitorData*)client_data;
    return data->ftm->structureVisitor(cursor, parent, data->file);
}

string buildName(CXCursor cursor)
{
    CXString cxName = clang_getCursorDisplayName(cursor);
    string cursorName = string(clang_getCString(cxName));
    clang_disposeString(cxName);

    CXCursor parentCursor = clang_getCursorSemanticParent(cursor);
    CXCursorKind parentCursorKind = clang_getCursorKind(parentCursor);
    if (parentCursorKind != CXCursor_TranslationUnit)
    {
        string parentName = buildName(parentCursor);
        return parentName + "::" + cursorName;
    }

    return cursorName;
}

void CXXFileTypeManager::indexStructure(CXTranslationUnit unit, ProjectFile* file)
{
    StructureVisitorData data;
    data.ftm = this;
    data.file = file;

    clang_visitChildren(clang_getTranslationUnitCursor(unit), structureVisitorFunc, (CXClientData*)&data);
}

CXChildVisitResult CXXFileTypeManager::structureVisitor(CXCursor cursor, CXCursor parent, ProjectFile* file)
{
    Project* project = file->getProject();

    CXSourceLocation sourceLocation = clang_getCursorLocation(cursor);

    int inMainFile = clang_Location_isFromMainFile(sourceLocation);
    if (!inMainFile)
    {
        return CXChildVisit_Continue;
    }

    CXCursorKind cursorKind = clang_getCursorKind(cursor);
    unsigned isDef = clang_isCursorDefinition(cursor);

    // Inspired by: https://github.com/drothlis/clang-ctags/blob/master/clang-ctags
    if ((isDef &&
            (cursorKind != CXCursor_CXXAccessSpecifier &&
            cursorKind != CXCursor_TemplateTypeParameter &&
            cursorKind != CXCursor_UnexposedDecl)) ||
        cursorKind == CXCursor_FunctionDecl ||
        cursorKind == CXCursor_CXXMethod ||
        cursorKind == CXCursor_FunctionTemplate ||
        cursorKind == CXCursor_Constructor ||
        cursorKind == CXCursor_Destructor)
    {
        if (cursorKind == CXCursor_NonTypeTemplateParameter ||
            cursorKind == CXCursor_ClassTemplatePartialSpecialization ||
            cursorKind == CXCursor_ConversionFunction ||
            cursorKind == CXCursor_TemplateTemplateParameter)
        {
            log(WARN, "structureVisitor: Ignoring CXCursor %u", cursorKind);

            return CXChildVisit_Continue;
        }

        Position pos = cxlocation2position(sourceLocation);

        string defName = buildName(cursor);

        CXCursor parentCursor = clang_getCursorSemanticParent(cursor);
        CXCursorKind parentCursorKind = clang_getCursorKind(parentCursor);
        string parentName = "";
        ProjectDefinition* parentDef = NULL;
        if (parentCursorKind != CXCursor_TranslationUnit)
        {
            parentName = buildName(parentCursor);
            parentDef = project->findDefinition(parentName);
        }

        ProjectDefinition* def = project->findDefinition(defName);
        if (def == NULL)
        {
            def = new ProjectDefinition();
            def->name = defName;
            def->parentName = parentName;
            def->parent = NULL;
        }

        if (def->parent == NULL && parentName != "")
        {
            parentDef = project->findDefinition(parentName);

            if (parentDef != NULL)
            {
                parentDef->children.push_back(def);
                def->parent = parentDef;
            }
        }

#if 0
        log(DEBUG, "structureVisitor: Line %u: %s, parent=%s (%p) (kind=%u, isDef=%u)", pos.line, defName.c_str(), parentName.c_str(), parentDef, cursorKind, isDef);
#endif

if (!def->isSource(file))
{

        ProjectDefinitionSource source;
        source.entry = file;
        source.position = pos;

        switch (cursorKind)
        {
            case CXCursor_FunctionDecl:
            case CXCursor_CXXMethod:
            case CXCursor_Constructor:
            case CXCursor_Destructor:
                if (isDef)
                {
                    source.type = DEF_FUNCTION_IMPL;
                }
                else
                {
                    source.type = DEF_FUNCTION_SPEC;
                }
                break;
            case CXCursor_FunctionTemplate:
                source.type = DEF_FUNCTION_TEMPLATE;
                break;
            case CXCursor_Namespace:
                source.type = DEF_NAMESPACE;
                break;
            case CXCursor_ClassDecl:
            case CXCursor_StructDecl:
            case CXCursor_UnionDecl:
                source.type = DEF_CLASS;
                break;
            case CXCursor_ClassTemplate:
                source.type = DEF_CLASS_TEMPLATE;
                break;
            case CXCursor_FieldDecl:
                source.type = DEF_FIELD;
                break;
            case CXCursor_EnumDecl:
                source.type = DEF_ENUM;
                break;
            case CXCursor_EnumConstantDecl:
                source.type = DEF_ENUM_CONSTANT;
                break;
            case CXCursor_TypedefDecl:
            case CXCursor_TypeAliasTemplateDecl:
            case CXCursor_TypeAliasDecl:
                source.type = DEF_TYPEDEF;
                break;
            case CXCursor_VarDecl:
                source.type = DEF_VARIABLE;
                break;


            default:
                log(ERROR, "structureVisitor: Unhandled cursor kind: %u", cursorKind);
                exit(1);
        }
        def->sources.push_back(source);
}

        project->addDefinition(def);
        file->addDefinition(def);
    }

    if (cursorKind == CXCursor_Namespace ||
        cursorKind == CXCursor_StructDecl ||
        cursorKind == CXCursor_UnionDecl ||
        cursorKind == CXCursor_EnumDecl ||
        cursorKind == CXCursor_ClassDecl ||
        cursorKind == CXCursor_ClassTemplate ||
        cursorKind == CXCursor_ClassTemplatePartialSpecialization)
    {
        return CXChildVisit_Recurse;
    }
    else
    {
        return CXChildVisit_Continue;
    }
}

CXTranslationUnit CXXFileTypeManager::parse(ProjectFile* file, CXUnsavedFile* unsavedFile)
{
    vector<string> buildArgs;
    if (!file->hasBuildArgs())
    {
        BuildTool* buildTool = file->getModule()->getBuildTool();

        buildArgs.push_back("-x");
        buildArgs.push_back("c++");
        buildArgs.push_back("-Wall");
        buildArgs.push_back("-ferror-limit=100");
        buildArgs.push_back("-I/usr/include");
        buildArgs.push_back("-I/usr/local/include");
#ifdef __APPLE__
        buildArgs.push_back("-I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include");
        buildArgs.push_back("-I/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include/c++/v1");
#endif

        if (buildTool != NULL)
        {
            vector<string> buildToolArgs = buildTool->getFileFlags(file);
            for (string arg : buildToolArgs)
            {
                if (arg.length() > 2 && arg.at(0) == '-' && arg.at(1) == 'I')
                {
                    // Make any relative include paths absolute
                    string includePath = arg.substr(2);
                    log(DEBUG, "parse: original includePath: %s", includePath.c_str());
                    includePath = ::Utils::mkpath(file->getProject()->getRootPath() + file->getFileDir(), includePath);
                    log(DEBUG, "parse: absolute includePath: %s", includePath.c_str());
                    arg = "-I" + includePath;
                }
                buildArgs.push_back(arg);
            }
        }
        file->setBuildArgs(buildArgs);
    }
    else
    {
        buildArgs = file->getBuildArgs();
    }

    int argc = buildArgs.size();

    log(DEBUG, "parse: argc=%d", argc);

    char* argv[argc + 1];

    int i = 0;
    for (string arg : buildArgs)
    {
        argv[i++] = strdup(arg.c_str());
    }
    argv[i++] = NULL;

    for (char* arg : argv)
    {
        if (arg != NULL)
        {
            log(DEBUG, "parse: arg: %s", arg);
        }
    }

    int unsavedFileCount = 0;
    if (unsavedFile != NULL)
    {
        unsavedFileCount = 1;
    }

unsigned int flags = clang_defaultEditingTranslationUnitOptions();
printf("XXX: flags=0x%x\n", flags);

    CXTranslationUnit unit;
    if (file->getTokeniseData() == NULL)
    {
        unit = clang_parseTranslationUnit(
            getIndex(),
            file->getAbsolutePath().c_str(), argv, argc,
            unsavedFile, unsavedFileCount,
            CXTranslationUnit_DetailedPreprocessingRecord | CXTranslationUnit_KeepGoing | CXTranslationUnit_PrecompiledPreamble);
        file->setTokeniseData(unit);
    }
    else
    {
        unit = (CXTranslationUnit)(file->getTokeniseData());
        clang_reparseTranslationUnit(unit, unsavedFileCount, unsavedFile, CXTranslationUnit_DetailedPreprocessingRecord | CXTranslationUnit_KeepGoing | CXTranslationUnit_PrecompiledPreamble);
    }

    for (char* arg : argv)
    {
        if (arg != NULL)
        {
            free(arg);
        }
    }

    return unit;
}

FileTypeIcon CXXFileTypeManager::getIcon()
{
    FileTypeIcon fti;
    fti.type = ICON_SURFACE;
    fti.surface = m_iconSurface;
    return fti;
}
 
