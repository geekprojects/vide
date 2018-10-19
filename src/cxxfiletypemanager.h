#ifndef __VIDE_CXX_FILE_TYPE_MANAGER_H_
#define __VIDE_CXX_FILE_TYPE_MANAGER_H_

#include "tokeniser.h"
#include "filetypemanager.h"

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
    CXXFileTypeManager();
    virtual ~CXXFileTypeManager();

    virtual bool canHandle(ProjectFile* file);

    virtual bool index(ProjectFile* entry);

    CXIndex getIndex() { return m_index; }
};


#endif
