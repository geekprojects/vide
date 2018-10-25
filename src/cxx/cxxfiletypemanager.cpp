
#include <string.h>

#include "cxxfiletypemanager.h"
#include "buffer.h"
#include "project.h"

using namespace std;

CXXTokeniser::CXXTokeniser(CXXFileTypeManager* ftm)
{
    m_ftm = ftm;
}

CXXTokeniser::~CXXTokeniser()
{
}

Position cxlocation2position(CXSourceLocation loc)
{
    unsigned int line;
    unsigned int column;
    clang_getExpansionLocation(loc, NULL, &line, &column, NULL);

    return Position(line - 1, column - 1);
}

void addDiagnostic(LineToken* token, CXDiagnostic diag)
{
    TokenMessage message;

    CXDiagnosticSeverity severity = clang_getDiagnosticSeverity(diag);
    switch (severity)
    {
        case CXDiagnostic_Warning:
            message.type = MESSAGE_WARNING;
            break;
        case CXDiagnostic_Error:
            message.type = MESSAGE_ERROR;
            break;
        default:
            printf("addDiagnostic: Ignoring diagnostic: severity=%d\n", severity);
            return;
    }

    CXString spelling = clang_getDiagnosticSpelling(diag);
    CXString category = clang_getDiagnosticCategoryText(diag);
    message.text = string(clang_getCString(category)) + ": " + string(clang_getCString(spelling));
    clang_disposeString(spelling);
    clang_disposeString(category);

    token->messages.push_back(message);
}

bool CXXTokeniser::tokenise(Buffer* buffer)
{
    uint32_t length;
    char* membuffer = buffer->writeToMem(length);

    CXUnsavedFile file[1];
    file[0].Filename = strdup(buffer->getFilename().c_str());
    file[0].Contents = membuffer;
    file[0].Length = length;

    const char* argv[] =
    {
        "-x", "c++",
        "-Wall",
        "-I/Users/ian/projects/vide/testproject/include", NULL
    };

    CXTranslationUnit unit = clang_parseTranslationUnit(
        m_ftm->getIndex(),
        buffer->getFilename().c_str(), argv, 4,
        file, 1,
        CXTranslationUnit_KeepGoing);

    CXFile cxfile = clang_getFile(unit, buffer->getFilename().c_str());

    unsigned int l = 0;
    for (Line* line : buffer->getLines())
    {
        line->clearTokens();
        if (line->text.length() == 0)
        {
            LineToken* token = new LineToken();
            token->isSpace = true;
            line->tokens.push_back(token);

            l++;
            continue;
        }

        CXSourceLocation lineStart = clang_getLocation(unit, cxfile, l + 1, 1);
        CXSourceLocation lineEnd = clang_getLocation(unit, cxfile, l + 1, line->text.length() + 1);

        CXSourceRange range = clang_getRange(lineStart, lineEnd);

        CXToken* cxTokens;
        unsigned int cxTokenCount;
        clang_tokenize(unit, range, &cxTokens, &cxTokenCount);

        CXCursor* cursors = new CXCursor[cxTokenCount];
        clang_annotateTokens(unit, cxTokens, cxTokenCount, cursors);

#if 0
        printf("CXXTokeniser::tokenise: Line: %ls, tokens=%u\n", line->text.c_str(), cxTokenCount);
#endif

        unsigned int lastEnd = 0;
        unsigned int t;
        for (t = 0; t < cxTokenCount; t++)
        {
            CXTokenKind kind = clang_getTokenKind(cxTokens[t]);
            CXCursorKind cursorKind = clang_getCursorKind(cursors[t]);

            CXSourceRange tokenRange = clang_getTokenExtent(unit, cxTokens[t]);
            CXSourceLocation tokenStart = clang_getRangeStart(tokenRange);
            CXSourceLocation tokenEnd = clang_getRangeEnd(tokenRange);
            Position start = cxlocation2position(tokenStart);
            Position end = cxlocation2position(tokenEnd);
            unsigned int length = end.column - start.column;

            if (start.line != l)
            { 
#if 0
                printf("CXXTokeniser::tokenise: Token is not on this line?\n");
#endif
                break;
            }

            if (lastEnd < start.column)
            {
                // There was white space!
                LineToken* lineToken = new LineToken();
                lineToken->column = lastEnd;
                lineToken->isSpace = true;
                unsigned int wlen = (start.column - lastEnd);
                lineToken->text = line->text.substr(lastEnd, wlen);
                line->tokens.push_back(lineToken);
            }

#if 0
            printf("CXXTokeniser::tokenise:  %u:  -> start: line=%u, col=%u, end: line=%u, col=%u, length=%u\n", t, start.line, start.column, end.line, end.column, length);
#endif
            lastEnd = end.column;

            wstring text = line->text.substr(start.column, length);

#if 0
            printf("CXXTokeniser::tokenise:  %u:  -> [%ls] token kind=%u, cursor kind=%u\n", t, text.c_str(), kind, cursorKind);
#endif

            LineToken* lineToken = new LineToken();
            lineToken->text = text;
            lineToken->column = start.column;

#if 1
            char msg[1024];
            snprintf(msg, 1024, "token=%u, cursor=%u", kind, cursorKind);
            TokenMessage message;
            message.type = MESSAGE_INFO;
            message.text = string(msg);
            lineToken->messages.push_back(message);
#endif

            switch (cursorKind)
            {
                case CXCursor_CXXAccessSpecifier:
                    lineToken->type = TOKEN_ACCESS_SPECIFIER;
                    break;

                case CXCursor_ParmDecl:
                    lineToken->type = TOKEN_PARAM_VARIABLE;
                    break;

                case CXCursor_FunctionDecl:
                case CXCursor_CXXMethod:
                case CXCursor_Constructor:
                case CXCursor_Destructor:
                    lineToken->type = TOKEN_FUNCTION;
                    break;

                case CXCursor_PreprocessingDirective:
                    lineToken->type = TOKEN_PREPROCESSOR;
                    break;

                default:
                    if (kind == CXToken_Comment)
                    {
                        lineToken->type = TOKEN_COMMENT;
                    }
                    else if (kind == CXToken_Identifier)
                    {
                        lineToken->type = TOKEN_IDENTIFIER;
                    }
                    else if (kind == CXToken_Keyword)
                    {
                        lineToken->type = TOKEN_KEYWORD;
                    }
                    else if (kind == CXToken_Literal)
                    {
                        lineToken->type = TOKEN_LITERAL;
                    }
                    else
                    {
                        lineToken->type = TOKEN_TEXT;
                    }
                    break;
            }

            line->tokens.push_back(lineToken);
        }

        clang_disposeTokens(unit, cxTokens, cxTokenCount);

        l++;
    }

    // Handle diagnostics: Errors and warnings
    unsigned int i;
    unsigned int n = clang_getNumDiagnostics(unit);
    for (i = 0; i != n; ++i)
    {
        CXDiagnostic diag = clang_getDiagnostic(unit, i);
        CXSourceLocation cxLocation = clang_getDiagnosticLocation(diag);
        int inMainFile = clang_Location_isFromMainFile(cxLocation);
        if (!inMainFile)
        {
            continue;
        }

        CXString str = clang_formatDiagnostic(diag, clang_defaultDiagnosticDisplayOptions());
        printf("%s\n", clang_getCString(str));
        clang_disposeString(str);

        // Attach diagnostic messages to tokens
        unsigned int num;
        num = clang_getDiagnosticNumRanges(diag);
#if 0
        printf(" -> %u ranges\n", num);
#endif
        if (num > 0)
        {
            unsigned int r;
            for (r = 0; r < num; r++)
            {
                CXSourceRange range = clang_getDiagnosticRange(diag, r);
                CXSourceLocation diagStart = clang_getRangeStart(range);
                CXSourceLocation diagEnd = clang_getRangeEnd(range);

                Position start = cxlocation2position(diagStart);
                Position end = cxlocation2position(diagEnd);
#if 0
                printf(" -> %u: %u: %u,%u -> %u,%u\n", i, r, start.line, start.column, end.line, end.column);
#endif

                if (start.line != end.line)
                {
                    printf("CXXTokeniser::tokenise: TODO: Multi-line diagnostics\n");
                    continue;
                }

                Position pos = start;
                while (pos.column <= end.column)
                {
                    LineToken* token = buffer->getToken(pos);
                    if (token == NULL)
                    {
                        break;
                    }
#if 0
                    printf(" -> %u: %ls\n", i, token->text.c_str());
#endif
                    addDiagnostic(token, diag);

                    pos.column += token->text.length();
                }
            }
        }
        else
        {
            Position pos = cxlocation2position(cxLocation);
#if 0
            printf(" -> %u: %u,%u\n", i, pos.line, pos.column);
#endif
            LineToken* token = buffer->getToken(pos);
            if (token != NULL)
            {
#if 0
                printf(" -> %u: %ls\n", i, token->text.c_str());
#endif
                addDiagnostic(token, diag);
            }
        }
    }

    m_ftm->indexStructure(unit, buffer->getProjectFile());

    clang_disposeTranslationUnit(unit);

    delete[] membuffer;

    return true;
}

bool CXXTokeniser::tokenise(Buffer* buffer, Line* line)
{
    // We need to reparse the whole buffer
    return tokenise(buffer);
}

CXXFileTypeManager::CXXFileTypeManager(Project* project) : FileTypeManager(project)
{
    m_tokeniser = new CXXTokeniser(this);

    m_index = clang_createIndex(0, 0);
}

CXXFileTypeManager::~CXXFileTypeManager()
{
  clang_disposeIndex(m_index);
}

bool CXXFileTypeManager::canHandle(ProjectFile* file)
{
    string name = file->getName();
    size_t pos = name.rfind(".");
    string ext = "";

    if (pos != string::npos)
    {
        ext = name.substr(pos + 1);
    }

    if (ext == "cpp" || ext == "c" || ext == "h")
    {
        return true;
    }

    return false;
}

bool CXXFileTypeManager::index(ProjectFile* file)
{

    const char* argv[] =
    {
        "-x", "c++", NULL
    };

    CXTranslationUnit unit = clang_parseTranslationUnit(
        m_index,
        file->getFilePath().c_str(), argv, 2,
        NULL, 0,
        CXTranslationUnit_KeepGoing);

    indexStructure(unit, file);

    clang_disposeTranslationUnit(unit);

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
            printf("CXXTokeniser::structureVisitor: WARN: Ignoring CXCursor %u\n", cursorKind);

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
            parentDef = m_project->findDefinition(parentName);
        }

        ProjectDefinition* def = m_project->findDefinition(defName);
        if (def == NULL)
        {
            def = new ProjectDefinition();
            def->name = defName;
            def->parentName = parentName;
            def->parent = NULL;
        }

        if (def->parent == NULL && parentName != "")
        {
            parentDef = m_project->findDefinition(parentName);

            if (parentDef != NULL)
            {
                parentDef->children.push_back(def);
                def->parent = parentDef;
            }
        }

#if 0
        printf("CXXTokeniser::structureVisitor: Line %u: %s, parent=%s (%p) (kind=%u, isDef=%u)\n", pos.line, defName.c_str(), parentName.c_str(), parentDef, cursorKind, isDef);
#endif

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
                source.type = DEF_TYPEDEF;
                break;
            case CXCursor_VarDecl:
                source.type = DEF_VARIABLE;
                break;


            default:
                printf("CXXTokeniser::structureVisitor: Unhandled cursor kind: %u\n", cursorKind);
                exit(1);
        }
        def->sources.push_back(source);

        m_project->addDefinition(def);
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


