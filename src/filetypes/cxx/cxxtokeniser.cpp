
#include <string.h>

#include "cxxfiletypemanager.h"
#include "editor/buffer.h"
#include "project/project.h"

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;

CXXTokeniser::CXXTokeniser(CXXFileTypeManager* ftm)
{
    m_ftm = ftm;
}

CXXTokeniser::~CXXTokeniser()
{
}

void CXXTokeniser::addDiagnostic(LineToken* token, CXDiagnostic diag)
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
            log(WARN, "addDiagnostic: Ignoring diagnostic: severity=%d", severity);
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

    CXTranslationUnit unit = m_ftm->parse(buffer->getProjectFile(), file);
    if (unit == NULL)
    {
        return false;
    }
    CXFile cxfile = clang_getFile(unit, buffer->getFilename().c_str());

    unsigned int l = 0;
    for (Line* line : buffer->getLines())
    {
        line->clearTokens();
        line->dirty = false;
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
        log(DEBUG, "tokenise: Line: %ls, tokens=%u", line->text.c_str(), cxTokenCount);
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
                log(DEBUG, "tokenise: Token is not on this line?");
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
            log(DEBUG, "tokenise:  %u:  -> start: line=%u, col=%u, end: line=%u, col=%u, length=%u", t, start.line, start.column, end.line, end.column, length);
#endif
            lastEnd = end.column;

            wstring text = line->text.substr(start.column, length);

#if 0
            log(DEBUG, "tokenise:  %u:  -> [%ls] token kind=%u, cursor kind=%u", t, text.c_str(), kind, cursorKind);
#endif

            LineToken* lineToken = new LineToken();
            lineToken->text = text;
            lineToken->column = start.column;

#if 0
            char msg[1024];
            snprintf(msg, 1024, "token=%u, cursor=%u", kind, cursorKind);
            TokenMessage message;
            message.type = ::MESSAGE_INFO;
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

                case 70: // Invalid -> Comment or unreachable (#if 0 etc)
                    lineToken->type = TOKEN_COMMENT;
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

            if (lineToken->text.find(L' ') != string::npos || lineToken->text.find(L'\t') != string::npos)
            {
                vector<LineToken*> splitTokens = splitText(lineToken->type, lineToken->text);
                for (LineToken* token : splitTokens)
                {
                    line->tokens.push_back(token);
                }
                delete lineToken;
            }
            else
            {
                line->tokens.push_back(lineToken);
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
        log(DEBUG, "%s", clang_getCString(str));
        clang_disposeString(str);

        unsigned int fixes = clang_getDiagnosticNumFixIts(diag);
        unsigned int f;
        for (f = 0; f < fixes; f++)
        {
            CXSourceRange range;
            CXString fixStr;
            fixStr = clang_getDiagnosticFixIt(diag, f, &range);
            CXSourceLocation diagStart = clang_getRangeStart(range);
            CXSourceLocation diagEnd = clang_getRangeEnd(range);
            Position start = cxlocation2position(diagStart);
            Position end = cxlocation2position(diagEnd);
            log(DEBUG, " FIX: -> %u: %u: %u,%u -> %u,%u: %s", i, f, start.line, start.column, end.line, end.column, clang_getCString(fixStr));
        }

        // Attach diagnostic messages to tokens
        unsigned int num;
        num = clang_getDiagnosticNumRanges(diag);
#if 0
        log(DEBUG, " -> %u ranges", num);
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
                log(DEBUG, " -> %u: %u: %u,%u -> %u,%u", i, r, start.line, start.column, end.line, end.column);
#endif

                if (start.line != end.line)
                {
                    log(WARN, "tokenise: TODO: Multi-line diagnostics");
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
                    log(DEBUG, " -> %u: %ls", i, token->text.c_str());
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
            log(DEBUG, " -> %u: %u,%u", i, pos.line, pos.column);
#endif
            LineToken* token = buffer->getToken(pos);
            if (token != NULL)
            {
#if 0
                log(DEBUG, " -> %u: %ls", i, token->text.c_str());
#endif
                addDiagnostic(token, diag);
            }
        }
    }

    m_ftm->indexStructure(unit, buffer->getProjectFile());

    clang_disposeTranslationUnit(unit);

    delete[] membuffer;

    buffer->clearDirty();

    return true;
}

bool CXXTokeniser::tokenise(Buffer* buffer, Line* line)
{
    // We need to reparse the whole buffer
    return tokenise(buffer);
}

