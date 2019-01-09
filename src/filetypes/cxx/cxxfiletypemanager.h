#ifndef __VIDE_CXX_FILE_TYPE_MANAGER_H_
#define __VIDE_CXX_FILE_TYPE_MANAGER_H_

#include "filetypes/tokeniser.h"
#include "filetypes/filetypemanager.h"

#include <clang-c/Index.h>

class CXXFileTypeManager;

struct CXXFileTypeManagerData : FileTypeManagerData
{
    CXTranslationUnit unit;
};

class CXXTokeniser : public Tokeniser
{
 protected:
    CXXFileTypeManager* m_ftm;

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

 public:
    CXXFileTypeManager(Vide* vide);
    virtual ~CXXFileTypeManager();

    virtual FileHandlerPriority canHandle(ProjectFile* file);

    virtual bool index(ProjectFile* entry);

    void indexStructure(CXTranslationUnit unit, ProjectFile* file);
    CXChildVisitResult structureVisitor(CXCursor cursor, CXCursor parent, ProjectFile* file);

    CXIndex getIndex() { return m_index; }

    CXTranslationUnit parse(ProjectFile* file, CXUnsavedFile* unsavedFile);
};


#endif
