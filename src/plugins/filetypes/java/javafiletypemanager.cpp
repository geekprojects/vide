#include <string.h>

#include "javafiletypemanager.h"
#include <vide/buffer.h>
#include <vide/project.h>
#include <vide/utils.h>

#include "JavaLexer.h"
#include "JavaParser.h"
#include "JavaParserBaseListener.h"

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;
using namespace antlr4;

VIDE_PLUGIN(JavaFileTypeManager);

JavaFileTypeManager::JavaFileTypeManager(Vide* vide) : FileTypeManager(vide)
{
    m_tokeniser = new JavaTokeniser(this);

    m_iconSurface = Surface::loadPNG(vide->getDataPath() + "/icons/java_256x256.png");
}

JavaFileTypeManager::~JavaFileTypeManager()
{
}

FileHandlerPriority JavaFileTypeManager::canHandle(ProjectFile* file)
{
    string name = file->getName();
    size_t pos = name.rfind(".");
    string ext = "";

    if (pos != string::npos)
    {
        ext = name.substr(pos + 1);
    }

    if (ext == "java")
    {
        return PRIORITY_HIGH;
    }

    return PRIORITY_UNSUPPORTED;
}


class VideJavaIndexListener : public JavaParserBaseListener
{
 private:
    JavaParserContext* m_ctx;

 public:
    ProjectDefinition* m_packageDefinition;

    Project* m_project;
    ProjectFile* m_file;

    std::string m_className;

    VideJavaIndexListener(JavaParserContext* ctx)
    {
m_ctx = ctx;
    }

    Token* find(Token* start, Token* end, size_t type)
    {
        size_t startPos = start->getTokenIndex();
        size_t endPos = end->getTokenIndex();
        size_t pos;
        for (pos = startPos; pos <= endPos; pos++)
        { 
            Token* token = m_ctx->tokenStream->get(pos);
            if (token->getType() == type)
            {
                return token;
            }
        }
        return NULL;
    }

std::string stripDots(std::string name)
{
while (name.length() > 0 && name.at(0) == '.')
{
name = name.substr(1);
}
return name;
}

    void addDefinition(std::string name, Token* token, ProjectDefinitionType type, std::string parentName)
    {
name = stripDots(name);
if (name.length() == 0)
{
return;
}
parentName = stripDots(parentName);

        ProjectDefinition* def;
        def = new ProjectDefinition();
        def->name = name;
        def->parentName = parentName;
        def->parent = m_project->findDefinition(parentName);

        ProjectDefinitionSource source;
        source.entry = m_file;
        source.position = Position(token->getLine() - 1, token->getCharPositionInLine());
        source.type = type;
        def->sources.push_back(source);
        m_project->addDefinition(def);
        m_file->addDefinition(def);
    }

    virtual void enterEveryRule(ParserRuleContext *rule)
    {
        Token* startToken = rule->getStart();
        Token* endToken = rule->getStop();

        printf("VideJavaIndexListener::enterEveryRule: rule=%zu: start=(%zu) %s, end=(%zu) %s\n",
            rule->getRuleIndex(),
            startToken->getType(),
            startToken->getText().c_str(),
            endToken->getType(),
            endToken->getText().c_str());
        switch (rule->getRuleIndex())
        {
            case JavaParser::RuleClassDeclaration:
            {
                Token* t = find(startToken, endToken, JavaLexer::IDENTIFIER);
                if (t != NULL)
                {
                    printf("VideJavaIndexListener::enterEveryRule: Found Class: '%s'.'%s'\n", m_ctx->packageName.c_str(), t->getText().c_str());
m_className = m_ctx->packageName + "." + t->getText();
addDefinition(m_className, t, DEF_CLASS, m_ctx->packageName);
                }
            } break;

            case JavaParser::RuleFieldDeclaration:
            {
                Token* t = find(startToken, endToken, JavaLexer::IDENTIFIER);
                if (t != NULL)
                {
                    printf("VideJavaIndexListener::enterEveryRule: Found field: '%s'.'%s'.'%s'\n", m_ctx->packageName.c_str(), "X", t->getText().c_str());
addDefinition(m_className + "." + t->getText(), t, DEF_FIELD, m_className);
                }
            } break;

            case JavaParser::RuleMethodDeclaration:
            {
                Token* t = find(startToken, endToken, JavaLexer::IDENTIFIER);
                if (t != NULL)
                {
                    printf("VideJavaIndexListener::enterEveryRule: Found method: '%s'.'%s'.'%s'\n", m_ctx->packageName.c_str(), "X", t->getText().c_str());
addDefinition(m_className + "." + t->getText(), t, DEF_FUNCTION_IMPL, m_className);
                }
            } break;
        }

    }

    virtual void visitTerminal(tree::TerminalNode *node) {}
    virtual void visitErrorNode(tree::ErrorNode *node) {}
    virtual void exitEveryRule(ParserRuleContext *ctx) {}
};

bool JavaFileTypeManager::index(ProjectFile* file)
{
    //Project* project = file->getProject();
    log(DEBUG, "JavaFileTypeManager::index: File: %s\n", file->getAbsolutePath().c_str());

    ANTLRFileStream* inputStream = new ANTLRFileStream(file->getAbsolutePath());
    JavaParserContext* ctx = parse(inputStream);

    Project* project = file->getProject();
    ProjectDefinition* packageDef = NULL;
    if (ctx->packageName.length() > 0)
    {
        packageDef = project->findDefinition(ctx->packageName);
        if (packageDef == NULL)
        {
            packageDef = new ProjectDefinition();
            packageDef->name = ctx->packageName;
            packageDef->parentName = "";
            packageDef->parent = NULL;

            ProjectDefinitionSource source;
            source.entry = file->getParent();
            source.position = Position(0, 0);
            source.type = DEF_PACKAGE;
            packageDef->sources.push_back(source);
            project->addDefinition(packageDef);
            file->addDefinition(packageDef);
        }
    }

    JavaParser::CompilationUnitContext* compilationUnit = ctx->parser->compilationUnit();
    VideJavaIndexListener listener(ctx);
listener.m_packageDefinition = packageDef;
listener.m_file = file;
listener.m_project = project;
    //listener.m_tokenStream = ctx->tokenStream;
    tree::ParseTreeWalker::DEFAULT.walk(&listener, compilationUnit);

    return true;
}

FileTypeIcon JavaFileTypeManager::getIcon()
{
    FileTypeIcon fti;
    fti.type = ICON_SURFACE;
    fti.surface = m_iconSurface;
    return fti;
}

JavaParserContext* JavaFileTypeManager::parse(ANTLRInputStream* inputStream)
{
    JavaParserContext* ctx = new JavaParserContext();

    try
    {
        ctx->inputStream = inputStream;
        ctx->lexer = new JavaLexer(ctx->inputStream);
        ctx->tokenStream = new CommonTokenStream(ctx->lexer);
        ctx->tokenStream->fill();
        ctx->parser = new JavaParser(ctx->tokenStream);
    }
    catch (std::exception& e)
    {
        log(ERROR, "Failed to parse file: %s", e.what());
        return NULL;
    }

    ctx->packageName = "";
    JavaParser::CompilationUnitContext* compilationUnit = ctx->parser->compilationUnit();
    if (compilationUnit->packageDeclaration() != NULL)
    {
        JavaParser::PackageDeclarationContext* pkg = compilationUnit->packageDeclaration();
        JavaParser::QualifiedNameContext* pkgName = pkg->qualifiedName();

        bool dot = false;
        for (auto part : pkgName->IDENTIFIER())
        {
            if (dot)
            {
                ctx->packageName += ".";
            }
            dot = true;
            ctx->packageName += part->getText();
        }
    }

    ctx->parser->reset();

    return ctx;
}

JavaParserContext::JavaParserContext()
{
    inputStream = NULL;
    lexer = NULL;
    tokenStream = NULL;
    parser = NULL;
}

JavaParserContext::~JavaParserContext()
{
    if (parser != NULL)
    {
        delete parser;
    }
    if (tokenStream != NULL)
    {
        delete tokenStream;
    }
    if (lexer != NULL)
    {
        delete lexer;
    }
    if (inputStream != NULL)
    {
        delete inputStream;
    }
}

string JavaParserContext::getPackageName()
{
    return packageName;
}


