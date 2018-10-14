
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
    message.text = string(clang_getCString(spelling));
    printf("%s\n", clang_getCString(spelling));
    clang_disposeString(spelling);

    CXString category = clang_getDiagnosticCategoryText(diag);
    printf("category: %s\n", clang_getCString(category));
    clang_disposeString(category);

    token->messages.push_back(message);
}

bool CXXTokeniser::tokenise(Buffer* buffer)
{
    CXUnsavedFile file[1];
    file[0].Filename = strdup(buffer->getFilename().c_str());
    uint32_t length;
    file[0].Contents = buffer->writeToMem(length);
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

            printf("CXXTokeniser::tokenise:  %u:  -> [%ls] token kind=%u, cursor kind=%u\n", t, text.c_str(), kind, cursorKind);

            LineToken* lineToken = new LineToken();
            lineToken->text = text;
            lineToken->column = start.column;

#if 0
            char msg[1024];
            snprintf(msg, 1024, "token=%u, cursor=%u", kind, cursorKind);
            TokenMessage message;
            message.type = MESSAGE_INFO;
            message.text = string(msg);
            lineToken->messages.push_back(message);
#endif

            switch (kind)
            {
                case CXToken_Punctuation:
                    lineToken->type = TOKEN_TEXT;
                    break;
                case CXToken_Keyword:
                    lineToken->type = TOKEN_KEYWORD;
                    if (cursorKind == CXCursor_CXXAccessSpecifier)
                    {
                        lineToken->type = TOKEN_ACCESS_SPECIFIER;
                    }
                    break;
                case CXToken_Identifier:
                    if (cursorKind == CXCursor_ParmDecl)
                    {
                        lineToken->type = TOKEN_PARAM_VARIABLE;
                    }
                    else
                    {
                        lineToken->type = TOKEN_IDENTIFIER;
                    }
                    break;

                case CXToken_Literal:
                    lineToken->type = TOKEN_TEXT;
                    break;

                case CXToken_Comment:
                    lineToken->type = TOKEN_COMMENT;
                    break;
            }

            line->tokens.push_back(lineToken);

            unsigned isDef = clang_isCursorDefinition(cursors[t]);
            // Inspired by: https://github.com/drothlis/clang-ctags/blob/master/clang-ctags
            if ((isDef && (cursorKind != CXCursor_CXXAccessSpecifier && cursorKind != CXCursor_TemplateTypeParameter && cursorKind != CXCursor_UnexposedDecl)) || (cursorKind == CXCursor_FunctionDecl || cursorKind == CXCursor_CXXMethod || cursorKind == CXCursor_FunctionTemplate))
            {
                printf("CXXTokeniser::tokenise:  %u:  -> DEFINITION: Add to structure\n", t);
            }
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

        unsigned int num;
        num = clang_getDiagnosticNumRanges(diag);
        printf(" -> %u ranges\n", num);
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
                printf(" -> %u: %u: %u,%u -> %u,%u\n", i, r, start.line, start.column, end.line, end.column);

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
                    printf(" -> %u: %ls\n", i, token->text.c_str());
                    addDiagnostic(token, diag);

                    pos.column += token->text.length();
                }
            }
        }
        else
        {
            Position pos = cxlocation2position(cxLocation);
            printf(" -> %u: %u,%u\n", i, pos.line, pos.column);
            LineToken* token = buffer->getToken(pos);
            if (token != NULL)
            {
                printf(" -> %u: %ls\n", i, token->text.c_str());
                addDiagnostic(token, diag);
            }
        }

    }


    clang_disposeTranslationUnit(unit);

    return true;
}

bool CXXTokeniser::tokenise(Buffer* buffer, Line* line)
{
    // We need to reparse the whole buffer
    return tokenise(buffer);
}

CXXFileTypeManager::CXXFileTypeManager()
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
    CXXFileTypeManagerData* data = (CXXFileTypeManagerData*)file->getFileTypeManagerData();
    if (data == NULL)
    {
        data = new CXXFileTypeManagerData();

        const char* argv[] =
        {
            "-x", "c++", NULL
        };

        data->unit = clang_parseTranslationUnit(
            m_index,
            file->getFilePath().c_str(), argv, 2,
            NULL, 0,
            CXTranslationUnit_KeepGoing);

    }
    else
    {
    }
    return true;
}

