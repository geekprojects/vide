#ifndef __VIDE_CXX_FILE_TYPE_MANAGER_H_
#define __VIDE_CXX_FILE_TYPE_MANAGER_H_

#include "filetypes/tokeniser.h"
#include "filetypes/filetypemanager.h"

#include <clang-c/Index.h>

static Position cxlocation2position(CXSourceLocation loc)
{
    unsigned int line;
    unsigned int column;
    clang_getExpansionLocation(loc, NULL, &line, &column, NULL);

    return Position(line - 1, column - 1);
}

class CXXFileTypeManager;

struct CXXFileTypeManagerData : FileTypeManagerData
{
    CXTranslationUnit unit;
};

class CXXTokeniser : public Tokeniser
{
 protected:
    CXXFileTypeManager* m_ftm;

    void addDiagnostic(LineToken* token, CXDiagnostic diag);

 public:
    CXXTokeniser(CXXFileTypeManager* ftm);
    virtual ~CXXTokeniser();

    virtual bool tokenise(Buffer* buffer);
    virtual bool tokenise(Buffer* buffer, Line* line);

};

class CXXFileTypeManager : public FileTypeManager
{
 protected:
    CXIndex m_index;
    Geek::Gfx::Surface* m_iconSurface;
    Frontier::Icon* m_icon;

 public:
    CXXFileTypeManager(Vide* vide);
    virtual ~CXXFileTypeManager();

    virtual FileHandlerPriority canHandle(ProjectFile* file);

    virtual bool index(ProjectFile* entry);

    void indexStructure(CXTranslationUnit unit, ProjectFile* file);
    CXChildVisitResult structureVisitor(CXCursor cursor, CXCursor parent, ProjectFile* file);

    CXIndex getIndex() { return m_index; }

    CXTranslationUnit parse(ProjectFile* file, CXUnsavedFile* unsavedFile);

    Frontier::Icon* getIcon();
};


#endif
