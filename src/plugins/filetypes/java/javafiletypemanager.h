#ifndef __VIDE_JAVA_FILE_TYPE_MANAGER_H_
#define __VIDE_JAVA_FILE_TYPE_MANAGER_H_

#include <vide/tokeniser.h>
#include <vide/filetypemanager.h>

#include "JavaLexer.h"
#include "JavaParser.h"
#include "JavaParserListener.h"

class JavaFileTypeManager;

struct JavaFileTypeManagerData : FileTypeManagerData
{
};

struct JavaParserContext
{
    antlr4::ANTLRInputStream* inputStream;
    JavaLexer* lexer;
    antlr4::CommonTokenStream* tokenStream;
    JavaParser* parser;

    std::string packageName;

    JavaParserContext();
    virtual ~JavaParserContext();

   std::string getPackageName();
};

class JavaTokeniser : public Tokeniser
{
 protected:
    JavaFileTypeManager* m_ftm;

 public:
    JavaTokeniser(JavaFileTypeManager* ftm);
    virtual ~JavaTokeniser();

    virtual bool tokenise(Buffer* buffer);
    virtual bool tokenise(Buffer* buffer, Line* line);
};

class JavaFileTypeManager : public FileTypeManager
{
   Geek::Gfx::Surface* m_iconSurface;

 public:
    JavaFileTypeManager(Vide* vide);
    virtual ~JavaFileTypeManager();

    virtual FileHandlerPriority canHandle(ProjectFile* file);

    virtual bool index(ProjectFile* entry);

    FileTypeIcon getIcon();

    JavaParserContext* parse(antlr4::ANTLRInputStream* inputStream);
};

#endif

