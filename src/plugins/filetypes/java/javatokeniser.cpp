
#include <string.h>
#include <sys/time.h>

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

class VideJavaListener : public JavaParserBaseListener
{
 private:

 public:
    TokenStream* m_tokenStream;
    std::map<Token*, std::vector<ParserRuleContext*>> tokenRuleMap;

    virtual void enterEveryRule(ParserRuleContext *ctx)
    {
        Token* startToken = ctx->getStart();
        Token* endToken = ctx->getStop();
/*
        printf("VideJavaListener::enterEveryRule: Rule:  type=%lu\n", ctx->getRuleIndex());
        printf("VideJavaListener::enterEveryRule: Start: type=%lu, line=%lu, col=%lu\n", startToken->getType(), startToken->getLine(), startToken->getCharPositionInLine());
        printf("VideJavaListener::enterEveryRule: End  : type=%lu, line=%lu, col=%lu\n", endToken->getType(), endToken->getLine(), endToken->getCharPositionInLine());
        printf("VideJavaListener::enterEveryRule: %s\n", ctx->toStringTree().c_str());
*/
        size_t idx;
        for (idx = startToken->getTokenIndex(); idx <= endToken->getTokenIndex(); idx++)
        {
            Token* token = m_tokenStream->get(idx);
            auto it = tokenRuleMap.find(token);
            if (it != tokenRuleMap.end())
            {
                it->second.push_back(ctx);
            }
            else
            {
                vector<ParserRuleContext*> v;
                v.push_back(ctx);
                tokenRuleMap.insert(make_pair(token, v));
            }
        }
    }

    virtual void visitTerminal(tree::TerminalNode *node) {}
    virtual void visitErrorNode(tree::ErrorNode *node) {}
    virtual void exitEveryRule(ParserRuleContext *ctx) {}
};

JavaTokeniser::JavaTokeniser(JavaFileTypeManager* ftm)
{
    m_ftm = ftm;
}

JavaTokeniser::~JavaTokeniser()
{
}

bool JavaTokeniser::tokenise(Buffer* buffer)
{
    log(DEBUG, "tokenise: Here!\n");

    uint32_t length;
    char* membuffer = buffer->writeToMem(length);
    ANTLRInputStream* inputStream = new ANTLRInputStream(membuffer, length);

    JavaParserContext* ctx = ((JavaFileTypeManager*)m_ftm)->parse(inputStream);

    // Create the Token -> Rule map
    JavaParser::CompilationUnitContext* compilationUnit = ctx->parser->compilationUnit();
    VideJavaListener listener;
    listener.m_tokenStream = ctx->tokenStream;
    tree::ParseTreeWalker::DEFAULT.walk(&listener, compilationUnit);

    string packageName = "";
    if (compilationUnit->packageDeclaration() != NULL)
    {
        JavaParser::PackageDeclarationContext* pkg = compilationUnit->packageDeclaration();
        JavaParser::QualifiedNameContext* pkgName = pkg->qualifiedName();
        log(DEBUG, "tokenise: package name pkgName=%p", pkgName);

        bool dot = false;
        for (auto part : pkgName->IDENTIFIER())
        {
            if (dot)
            {
                packageName += ".";
            }
            dot = true;
            packageName += part->getText();
        }
        log(DEBUG, "tokenise: package name=%s", packageName.c_str());
    }
    string className = "";

    buffer->lock();

    for (Line* line : buffer->getLines())
    {
        line->clearTokens();
        line->dirty = false;
    }

    for (auto token : ctx->tokenStream->getTokens())
    {
        if (token->getType() == JavaLexer::NEWLINE)
        {
            continue;
        }

        log(DEBUG, "tokenise: token=%p", token);
        auto it = listener.tokenRuleMap.find(token);

        unsigned int lineNum = token->getLine();
        unsigned int column = token->getCharPositionInLine();
        log(DEBUG, "tokenise: Token(2): %u, %u: type=%u: %s", lineNum, column, token->getType(), token->getText().c_str());

        Line* line = buffer->getLine(lineNum - 1);
        if (line == NULL)
        {
            continue;
        }

        if (token->getType() == JavaLexer::COMMENT)
        {
            wstring text = ::Utils::string2wstring(token->getText());

            wstring lineText = L"";
            unsigned int pos = 0;
            for (pos = 0; pos < text.length(); pos++)
            {
                wchar_t c = text.at(pos);

                bool eol = false;
                if (c == L'\r')
                {
                    if ((pos + 1) < text.length())
                    {
                        if (text.at(pos + 1) == L'\n')
                        {
                            pos++;
                        }
                        eol = true;
                    }
                }
                else if (c == L'\n')
                {
                    eol = true;
                }
                else
                {
                    lineText += c;
                }
log(DEBUG, "tokenise: c=%lc, eol=%d", c, eol);

                if (eol || pos == text.length() - 1)
                {
log(DEBUG, "tokenise:  -> line text=%ls", lineText.c_str());
                    LineToken* lineToken = new LineToken();
                    //line->tokens.push_back(lineToken);

                    lineToken->type = TOKEN_COMMENT;
                    lineToken->text = lineText;

                vector<LineToken*> splitTokens = splitText(lineToken->type, lineToken->text);
                for (LineToken* token : splitTokens)
                {
                    line->tokens.push_back(token);
                }

                    lineNum++;
                    line = buffer->getLine(lineNum - 1);

                    lineText = L"";
                }
            }

            continue;
        }

        LineToken* lineToken = new LineToken();

        lineToken->text = ::Utils::string2wstring(token->getText());

        TokenType tokenType = TOKEN_TEXT;
        if (token->getType() == JavaLexer::WS)
        {
            lineToken->isSpace = true;
            line->tokens.push_back(lineToken);
        }
        else if (token->getType() == JavaLexer::LINE_COMMENT)
        {
            lineToken->type = TOKEN_COMMENT;
            vector<LineToken*> splitTokens = splitText(lineToken->type, lineToken->text);
            for (LineToken* token : splitTokens)
            {
                line->tokens.push_back(token);
            }
        }
        else
        {
            //unsigned int count = 0;
            unsigned int lastRule = 0;
            if (it != listener.tokenRuleMap.end())
            {
                for (auto ruleIt = it->second.begin(); ruleIt != it->second.end(); ruleIt++)
                {
                    ParserRuleContext* ruleCtx = *ruleIt;
                    string ruleName = ctx->parser->getRuleNames().at(ruleCtx->getRuleIndex());
                    log(DEBUG, "tokenise: Token(2):   -> %s", ruleName.c_str());
                    lastRule = ruleCtx->getRuleIndex();
                }
            }

            if (token->getType() == JavaLexer::IDENTIFIER)
            {
                tokenType = TOKEN_IDENTIFIER;
                if (lastRule == JavaParser::RuleClassDeclaration)
                {
                    log(DEBUG, "Found Class: '%s'", token->getText().c_str());
                    className = token->getText().c_str();
                }
                else if (lastRule == JavaParser::RuleMethodDeclaration)
                {
                    log(DEBUG, "Found Method: '%s' -> %s.%s.%s", token->getText().c_str(), packageName.c_str(), className.c_str(), token->getText().c_str());
                    tokenType = TOKEN_FUNCTION;
                }
            }
            lineToken->type = tokenType;
            line->tokens.push_back(lineToken);
        }

    }

    buffer->clearDirty();
    buffer->unlock();

    log(DEBUG, "tokenise: Done!");
    return true;
}

bool JavaTokeniser::tokenise(Buffer* buffer, Line* line)
{
    // We need to reparse the whole buffer
    return tokenise(buffer);
}


