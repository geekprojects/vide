
// Generated from JavaParser.g4 by ANTLR 4.7.2


#include "JavaParserListener.h"

#include "JavaParser.h"


using namespace antlrcpp;
using namespace antlr4;

JavaParser::JavaParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

JavaParser::~JavaParser() {
  delete _interpreter;
}

std::string JavaParser::getGrammarFileName() const {
  return "JavaParser.g4";
}

const std::vector<std::string>& JavaParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& JavaParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- CompilationUnitContext ------------------------------------------------------------------

JavaParser::CompilationUnitContext::CompilationUnitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaParser::CompilationUnitContext::EOF() {
  return getToken(JavaParser::EOF, 0);
}

JavaParser::PackageDeclarationContext* JavaParser::CompilationUnitContext::packageDeclaration() {
  return getRuleContext<JavaParser::PackageDeclarationContext>(0);
}

std::vector<JavaParser::ImportDeclarationContext *> JavaParser::CompilationUnitContext::importDeclaration() {
  return getRuleContexts<JavaParser::ImportDeclarationContext>();
}

JavaParser::ImportDeclarationContext* JavaParser::CompilationUnitContext::importDeclaration(size_t i) {
  return getRuleContext<JavaParser::ImportDeclarationContext>(i);
}

std::vector<JavaParser::TypeDeclarationContext *> JavaParser::CompilationUnitContext::typeDeclaration() {
  return getRuleContexts<JavaParser::TypeDeclarationContext>();
}

JavaParser::TypeDeclarationContext* JavaParser::CompilationUnitContext::typeDeclaration(size_t i) {
  return getRuleContext<JavaParser::TypeDeclarationContext>(i);
}


size_t JavaParser::CompilationUnitContext::getRuleIndex() const {
  return JavaParser::RuleCompilationUnit;
}

void JavaParser::CompilationUnitContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCompilationUnit(this);
}

void JavaParser::CompilationUnitContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCompilationUnit(this);
}

JavaParser::CompilationUnitContext* JavaParser::compilationUnit() {
  CompilationUnitContext *_localctx = _tracker.createInstance<CompilationUnitContext>(_ctx, getState());
  enterRule(_localctx, 0, JavaParser::RuleCompilationUnit);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(209);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
    case 1: {
      setState(208);
      packageDeclaration();
      break;
    }

    }
    setState(214);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == JavaParser::IMPORT) {
      setState(211);
      importDeclaration();
      setState(216);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(220);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << JavaParser::ABSTRACT)
      | (1ULL << JavaParser::CLASS)
      | (1ULL << JavaParser::ENUM)
      | (1ULL << JavaParser::FINAL)
      | (1ULL << JavaParser::INTERFACE)
      | (1ULL << JavaParser::PRIVATE)
      | (1ULL << JavaParser::PROTECTED)
      | (1ULL << JavaParser::PUBLIC)
      | (1ULL << JavaParser::STATIC)
      | (1ULL << JavaParser::STRICTFP))) != 0) || _la == JavaParser::SEMI

    || _la == JavaParser::AT) {
      setState(217);
      typeDeclaration();
      setState(222);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(223);
    match(JavaParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PackageDeclarationContext ------------------------------------------------------------------

JavaParser::PackageDeclarationContext::PackageDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaParser::PackageDeclarationContext::PACKAGE() {
  return getToken(JavaParser::PACKAGE, 0);
}

JavaParser::QualifiedNameContext* JavaParser::PackageDeclarationContext::qualifiedName() {
  return getRuleContext<JavaParser::QualifiedNameContext>(0);
}

tree::TerminalNode* JavaParser::PackageDeclarationContext::SEMI() {
  return getToken(JavaParser::SEMI, 0);
}

std::vector<JavaParser::AnnotationContext *> JavaParser::PackageDeclarationContext::annotation() {
  return getRuleContexts<JavaParser::AnnotationContext>();
}

JavaParser::AnnotationContext* JavaParser::PackageDeclarationContext::annotation(size_t i) {
  return getRuleContext<JavaParser::AnnotationContext>(i);
}


size_t JavaParser::PackageDeclarationContext::getRuleIndex() const {
  return JavaParser::RulePackageDeclaration;
}

void JavaParser::PackageDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPackageDeclaration(this);
}

void JavaParser::PackageDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPackageDeclaration(this);
}

JavaParser::PackageDeclarationContext* JavaParser::packageDeclaration() {
  PackageDeclarationContext *_localctx = _tracker.createInstance<PackageDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 2, JavaParser::RulePackageDeclaration);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(228);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == JavaParser::AT) {
      setState(225);
      annotation();
      setState(230);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(231);
    match(JavaParser::PACKAGE);
    setState(232);
    qualifiedName();
    setState(233);
    match(JavaParser::SEMI);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ImportDeclarationContext ------------------------------------------------------------------

JavaParser::ImportDeclarationContext::ImportDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaParser::ImportDeclarationContext::IMPORT() {
  return getToken(JavaParser::IMPORT, 0);
}

JavaParser::QualifiedNameContext* JavaParser::ImportDeclarationContext::qualifiedName() {
  return getRuleContext<JavaParser::QualifiedNameContext>(0);
}

tree::TerminalNode* JavaParser::ImportDeclarationContext::SEMI() {
  return getToken(JavaParser::SEMI, 0);
}

tree::TerminalNode* JavaParser::ImportDeclarationContext::STATIC() {
  return getToken(JavaParser::STATIC, 0);
}

tree::TerminalNode* JavaParser::ImportDeclarationContext::DOT() {
  return getToken(JavaParser::DOT, 0);
}

tree::TerminalNode* JavaParser::ImportDeclarationContext::MUL() {
  return getToken(JavaParser::MUL, 0);
}


size_t JavaParser::ImportDeclarationContext::getRuleIndex() const {
  return JavaParser::RuleImportDeclaration;
}

void JavaParser::ImportDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterImportDeclaration(this);
}

void JavaParser::ImportDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitImportDeclaration(this);
}

JavaParser::ImportDeclarationContext* JavaParser::importDeclaration() {
  ImportDeclarationContext *_localctx = _tracker.createInstance<ImportDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 4, JavaParser::RuleImportDeclaration);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(235);
    match(JavaParser::IMPORT);
    setState(237);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaParser::STATIC) {
      setState(236);
      match(JavaParser::STATIC);
    }
    setState(239);
    qualifiedName();
    setState(242);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaParser::DOT) {
      setState(240);
      match(JavaParser::DOT);
      setState(241);
      match(JavaParser::MUL);
    }
    setState(244);
    match(JavaParser::SEMI);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeDeclarationContext ------------------------------------------------------------------

JavaParser::TypeDeclarationContext::TypeDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaParser::ClassDeclarationContext* JavaParser::TypeDeclarationContext::classDeclaration() {
  return getRuleContext<JavaParser::ClassDeclarationContext>(0);
}

JavaParser::EnumDeclarationContext* JavaParser::TypeDeclarationContext::enumDeclaration() {
  return getRuleContext<JavaParser::EnumDeclarationContext>(0);
}

JavaParser::InterfaceDeclarationContext* JavaParser::TypeDeclarationContext::interfaceDeclaration() {
  return getRuleContext<JavaParser::InterfaceDeclarationContext>(0);
}

JavaParser::AnnotationTypeDeclarationContext* JavaParser::TypeDeclarationContext::annotationTypeDeclaration() {
  return getRuleContext<JavaParser::AnnotationTypeDeclarationContext>(0);
}

std::vector<JavaParser::ClassOrInterfaceModifierContext *> JavaParser::TypeDeclarationContext::classOrInterfaceModifier() {
  return getRuleContexts<JavaParser::ClassOrInterfaceModifierContext>();
}

JavaParser::ClassOrInterfaceModifierContext* JavaParser::TypeDeclarationContext::classOrInterfaceModifier(size_t i) {
  return getRuleContext<JavaParser::ClassOrInterfaceModifierContext>(i);
}

tree::TerminalNode* JavaParser::TypeDeclarationContext::SEMI() {
  return getToken(JavaParser::SEMI, 0);
}


size_t JavaParser::TypeDeclarationContext::getRuleIndex() const {
  return JavaParser::RuleTypeDeclaration;
}

void JavaParser::TypeDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeDeclaration(this);
}

void JavaParser::TypeDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeDeclaration(this);
}

JavaParser::TypeDeclarationContext* JavaParser::typeDeclaration() {
  TypeDeclarationContext *_localctx = _tracker.createInstance<TypeDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 6, JavaParser::RuleTypeDeclaration);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    setState(259);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaParser::ABSTRACT:
      case JavaParser::CLASS:
      case JavaParser::ENUM:
      case JavaParser::FINAL:
      case JavaParser::INTERFACE:
      case JavaParser::PRIVATE:
      case JavaParser::PROTECTED:
      case JavaParser::PUBLIC:
      case JavaParser::STATIC:
      case JavaParser::STRICTFP:
      case JavaParser::AT: {
        enterOuterAlt(_localctx, 1);
        setState(249);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
          if (alt == 1) {
            setState(246);
            classOrInterfaceModifier(); 
          }
          setState(251);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx);
        }
        setState(256);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case JavaParser::CLASS: {
            setState(252);
            classDeclaration();
            break;
          }

          case JavaParser::ENUM: {
            setState(253);
            enumDeclaration();
            break;
          }

          case JavaParser::INTERFACE: {
            setState(254);
            interfaceDeclaration();
            break;
          }

          case JavaParser::AT: {
            setState(255);
            annotationTypeDeclaration();
            break;
          }

        default:
          throw NoViableAltException(this);
        }
        break;
      }

      case JavaParser::SEMI: {
        enterOuterAlt(_localctx, 2);
        setState(258);
        match(JavaParser::SEMI);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ModifierContext ------------------------------------------------------------------

JavaParser::ModifierContext::ModifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaParser::ClassOrInterfaceModifierContext* JavaParser::ModifierContext::classOrInterfaceModifier() {
  return getRuleContext<JavaParser::ClassOrInterfaceModifierContext>(0);
}

tree::TerminalNode* JavaParser::ModifierContext::NATIVE() {
  return getToken(JavaParser::NATIVE, 0);
}

tree::TerminalNode* JavaParser::ModifierContext::SYNCHRONIZED() {
  return getToken(JavaParser::SYNCHRONIZED, 0);
}

tree::TerminalNode* JavaParser::ModifierContext::TRANSIENT() {
  return getToken(JavaParser::TRANSIENT, 0);
}

tree::TerminalNode* JavaParser::ModifierContext::VOLATILE() {
  return getToken(JavaParser::VOLATILE, 0);
}


size_t JavaParser::ModifierContext::getRuleIndex() const {
  return JavaParser::RuleModifier;
}

void JavaParser::ModifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterModifier(this);
}

void JavaParser::ModifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitModifier(this);
}

JavaParser::ModifierContext* JavaParser::modifier() {
  ModifierContext *_localctx = _tracker.createInstance<ModifierContext>(_ctx, getState());
  enterRule(_localctx, 8, JavaParser::RuleModifier);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(266);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaParser::ABSTRACT:
      case JavaParser::FINAL:
      case JavaParser::PRIVATE:
      case JavaParser::PROTECTED:
      case JavaParser::PUBLIC:
      case JavaParser::STATIC:
      case JavaParser::STRICTFP:
      case JavaParser::AT: {
        enterOuterAlt(_localctx, 1);
        setState(261);
        classOrInterfaceModifier();
        break;
      }

      case JavaParser::NATIVE: {
        enterOuterAlt(_localctx, 2);
        setState(262);
        match(JavaParser::NATIVE);
        break;
      }

      case JavaParser::SYNCHRONIZED: {
        enterOuterAlt(_localctx, 3);
        setState(263);
        match(JavaParser::SYNCHRONIZED);
        break;
      }

      case JavaParser::TRANSIENT: {
        enterOuterAlt(_localctx, 4);
        setState(264);
        match(JavaParser::TRANSIENT);
        break;
      }

      case JavaParser::VOLATILE: {
        enterOuterAlt(_localctx, 5);
        setState(265);
        match(JavaParser::VOLATILE);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ClassOrInterfaceModifierContext ------------------------------------------------------------------

JavaParser::ClassOrInterfaceModifierContext::ClassOrInterfaceModifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaParser::AnnotationContext* JavaParser::ClassOrInterfaceModifierContext::annotation() {
  return getRuleContext<JavaParser::AnnotationContext>(0);
}

tree::TerminalNode* JavaParser::ClassOrInterfaceModifierContext::PUBLIC() {
  return getToken(JavaParser::PUBLIC, 0);
}

tree::TerminalNode* JavaParser::ClassOrInterfaceModifierContext::PROTECTED() {
  return getToken(JavaParser::PROTECTED, 0);
}

tree::TerminalNode* JavaParser::ClassOrInterfaceModifierContext::PRIVATE() {
  return getToken(JavaParser::PRIVATE, 0);
}

tree::TerminalNode* JavaParser::ClassOrInterfaceModifierContext::STATIC() {
  return getToken(JavaParser::STATIC, 0);
}

tree::TerminalNode* JavaParser::ClassOrInterfaceModifierContext::ABSTRACT() {
  return getToken(JavaParser::ABSTRACT, 0);
}

tree::TerminalNode* JavaParser::ClassOrInterfaceModifierContext::FINAL() {
  return getToken(JavaParser::FINAL, 0);
}

tree::TerminalNode* JavaParser::ClassOrInterfaceModifierContext::STRICTFP() {
  return getToken(JavaParser::STRICTFP, 0);
}


size_t JavaParser::ClassOrInterfaceModifierContext::getRuleIndex() const {
  return JavaParser::RuleClassOrInterfaceModifier;
}

void JavaParser::ClassOrInterfaceModifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterClassOrInterfaceModifier(this);
}

void JavaParser::ClassOrInterfaceModifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitClassOrInterfaceModifier(this);
}

JavaParser::ClassOrInterfaceModifierContext* JavaParser::classOrInterfaceModifier() {
  ClassOrInterfaceModifierContext *_localctx = _tracker.createInstance<ClassOrInterfaceModifierContext>(_ctx, getState());
  enterRule(_localctx, 10, JavaParser::RuleClassOrInterfaceModifier);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(276);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaParser::AT: {
        enterOuterAlt(_localctx, 1);
        setState(268);
        annotation();
        break;
      }

      case JavaParser::PUBLIC: {
        enterOuterAlt(_localctx, 2);
        setState(269);
        match(JavaParser::PUBLIC);
        break;
      }

      case JavaParser::PROTECTED: {
        enterOuterAlt(_localctx, 3);
        setState(270);
        match(JavaParser::PROTECTED);
        break;
      }

      case JavaParser::PRIVATE: {
        enterOuterAlt(_localctx, 4);
        setState(271);
        match(JavaParser::PRIVATE);
        break;
      }

      case JavaParser::STATIC: {
        enterOuterAlt(_localctx, 5);
        setState(272);
        match(JavaParser::STATIC);
        break;
      }

      case JavaParser::ABSTRACT: {
        enterOuterAlt(_localctx, 6);
        setState(273);
        match(JavaParser::ABSTRACT);
        break;
      }

      case JavaParser::FINAL: {
        enterOuterAlt(_localctx, 7);
        setState(274);
        match(JavaParser::FINAL);
        break;
      }

      case JavaParser::STRICTFP: {
        enterOuterAlt(_localctx, 8);
        setState(275);
        match(JavaParser::STRICTFP);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableModifierContext ------------------------------------------------------------------

JavaParser::VariableModifierContext::VariableModifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaParser::VariableModifierContext::FINAL() {
  return getToken(JavaParser::FINAL, 0);
}

JavaParser::AnnotationContext* JavaParser::VariableModifierContext::annotation() {
  return getRuleContext<JavaParser::AnnotationContext>(0);
}


size_t JavaParser::VariableModifierContext::getRuleIndex() const {
  return JavaParser::RuleVariableModifier;
}

void JavaParser::VariableModifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariableModifier(this);
}

void JavaParser::VariableModifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariableModifier(this);
}

JavaParser::VariableModifierContext* JavaParser::variableModifier() {
  VariableModifierContext *_localctx = _tracker.createInstance<VariableModifierContext>(_ctx, getState());
  enterRule(_localctx, 12, JavaParser::RuleVariableModifier);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(280);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaParser::FINAL: {
        enterOuterAlt(_localctx, 1);
        setState(278);
        match(JavaParser::FINAL);
        break;
      }

      case JavaParser::AT: {
        enterOuterAlt(_localctx, 2);
        setState(279);
        annotation();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ClassDeclarationContext ------------------------------------------------------------------

JavaParser::ClassDeclarationContext::ClassDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaParser::ClassDeclarationContext::CLASS() {
  return getToken(JavaParser::CLASS, 0);
}

tree::TerminalNode* JavaParser::ClassDeclarationContext::IDENTIFIER() {
  return getToken(JavaParser::IDENTIFIER, 0);
}

JavaParser::ClassBodyContext* JavaParser::ClassDeclarationContext::classBody() {
  return getRuleContext<JavaParser::ClassBodyContext>(0);
}

JavaParser::TypeParametersContext* JavaParser::ClassDeclarationContext::typeParameters() {
  return getRuleContext<JavaParser::TypeParametersContext>(0);
}

tree::TerminalNode* JavaParser::ClassDeclarationContext::EXTENDS() {
  return getToken(JavaParser::EXTENDS, 0);
}

JavaParser::TypeTypeContext* JavaParser::ClassDeclarationContext::typeType() {
  return getRuleContext<JavaParser::TypeTypeContext>(0);
}

tree::TerminalNode* JavaParser::ClassDeclarationContext::IMPLEMENTS() {
  return getToken(JavaParser::IMPLEMENTS, 0);
}

JavaParser::TypeListContext* JavaParser::ClassDeclarationContext::typeList() {
  return getRuleContext<JavaParser::TypeListContext>(0);
}


size_t JavaParser::ClassDeclarationContext::getRuleIndex() const {
  return JavaParser::RuleClassDeclaration;
}

void JavaParser::ClassDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterClassDeclaration(this);
}

void JavaParser::ClassDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitClassDeclaration(this);
}

JavaParser::ClassDeclarationContext* JavaParser::classDeclaration() {
  ClassDeclarationContext *_localctx = _tracker.createInstance<ClassDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 14, JavaParser::RuleClassDeclaration);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(282);
    match(JavaParser::CLASS);
    setState(283);
    match(JavaParser::IDENTIFIER);
    setState(285);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaParser::LT) {
      setState(284);
      typeParameters();
    }
    setState(289);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaParser::EXTENDS) {
      setState(287);
      match(JavaParser::EXTENDS);
      setState(288);
      typeType();
    }
    setState(293);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaParser::IMPLEMENTS) {
      setState(291);
      match(JavaParser::IMPLEMENTS);
      setState(292);
      typeList();
    }
    setState(295);
    classBody();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeParametersContext ------------------------------------------------------------------

JavaParser::TypeParametersContext::TypeParametersContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaParser::TypeParametersContext::LT() {
  return getToken(JavaParser::LT, 0);
}

std::vector<JavaParser::TypeParameterContext *> JavaParser::TypeParametersContext::typeParameter() {
  return getRuleContexts<JavaParser::TypeParameterContext>();
}

JavaParser::TypeParameterContext* JavaParser::TypeParametersContext::typeParameter(size_t i) {
  return getRuleContext<JavaParser::TypeParameterContext>(i);
}

tree::TerminalNode* JavaParser::TypeParametersContext::GT() {
  return getToken(JavaParser::GT, 0);
}

std::vector<tree::TerminalNode *> JavaParser::TypeParametersContext::COMMA() {
  return getTokens(JavaParser::COMMA);
}

tree::TerminalNode* JavaParser::TypeParametersContext::COMMA(size_t i) {
  return getToken(JavaParser::COMMA, i);
}


size_t JavaParser::TypeParametersContext::getRuleIndex() const {
  return JavaParser::RuleTypeParameters;
}

void JavaParser::TypeParametersContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeParameters(this);
}

void JavaParser::TypeParametersContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeParameters(this);
}

JavaParser::TypeParametersContext* JavaParser::typeParameters() {
  TypeParametersContext *_localctx = _tracker.createInstance<TypeParametersContext>(_ctx, getState());
  enterRule(_localctx, 16, JavaParser::RuleTypeParameters);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(297);
    match(JavaParser::LT);
    setState(298);
    typeParameter();
    setState(303);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == JavaParser::COMMA) {
      setState(299);
      match(JavaParser::COMMA);
      setState(300);
      typeParameter();
      setState(305);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(306);
    match(JavaParser::GT);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeParameterContext ------------------------------------------------------------------

JavaParser::TypeParameterContext::TypeParameterContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaParser::TypeParameterContext::IDENTIFIER() {
  return getToken(JavaParser::IDENTIFIER, 0);
}

std::vector<JavaParser::AnnotationContext *> JavaParser::TypeParameterContext::annotation() {
  return getRuleContexts<JavaParser::AnnotationContext>();
}

JavaParser::AnnotationContext* JavaParser::TypeParameterContext::annotation(size_t i) {
  return getRuleContext<JavaParser::AnnotationContext>(i);
}

tree::TerminalNode* JavaParser::TypeParameterContext::EXTENDS() {
  return getToken(JavaParser::EXTENDS, 0);
}

JavaParser::TypeBoundContext* JavaParser::TypeParameterContext::typeBound() {
  return getRuleContext<JavaParser::TypeBoundContext>(0);
}


size_t JavaParser::TypeParameterContext::getRuleIndex() const {
  return JavaParser::RuleTypeParameter;
}

void JavaParser::TypeParameterContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeParameter(this);
}

void JavaParser::TypeParameterContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeParameter(this);
}

JavaParser::TypeParameterContext* JavaParser::typeParameter() {
  TypeParameterContext *_localctx = _tracker.createInstance<TypeParameterContext>(_ctx, getState());
  enterRule(_localctx, 18, JavaParser::RuleTypeParameter);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(311);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == JavaParser::AT) {
      setState(308);
      annotation();
      setState(313);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(314);
    match(JavaParser::IDENTIFIER);
    setState(317);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaParser::EXTENDS) {
      setState(315);
      match(JavaParser::EXTENDS);
      setState(316);
      typeBound();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeBoundContext ------------------------------------------------------------------

JavaParser::TypeBoundContext::TypeBoundContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<JavaParser::TypeTypeContext *> JavaParser::TypeBoundContext::typeType() {
  return getRuleContexts<JavaParser::TypeTypeContext>();
}

JavaParser::TypeTypeContext* JavaParser::TypeBoundContext::typeType(size_t i) {
  return getRuleContext<JavaParser::TypeTypeContext>(i);
}

std::vector<tree::TerminalNode *> JavaParser::TypeBoundContext::BITAND() {
  return getTokens(JavaParser::BITAND);
}

tree::TerminalNode* JavaParser::TypeBoundContext::BITAND(size_t i) {
  return getToken(JavaParser::BITAND, i);
}


size_t JavaParser::TypeBoundContext::getRuleIndex() const {
  return JavaParser::RuleTypeBound;
}

void JavaParser::TypeBoundContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeBound(this);
}

void JavaParser::TypeBoundContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeBound(this);
}

JavaParser::TypeBoundContext* JavaParser::typeBound() {
  TypeBoundContext *_localctx = _tracker.createInstance<TypeBoundContext>(_ctx, getState());
  enterRule(_localctx, 20, JavaParser::RuleTypeBound);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(319);
    typeType();
    setState(324);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == JavaParser::BITAND) {
      setState(320);
      match(JavaParser::BITAND);
      setState(321);
      typeType();
      setState(326);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EnumDeclarationContext ------------------------------------------------------------------

JavaParser::EnumDeclarationContext::EnumDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaParser::EnumDeclarationContext::ENUM() {
  return getToken(JavaParser::ENUM, 0);
}

tree::TerminalNode* JavaParser::EnumDeclarationContext::IDENTIFIER() {
  return getToken(JavaParser::IDENTIFIER, 0);
}

tree::TerminalNode* JavaParser::EnumDeclarationContext::LBRACE() {
  return getToken(JavaParser::LBRACE, 0);
}

tree::TerminalNode* JavaParser::EnumDeclarationContext::RBRACE() {
  return getToken(JavaParser::RBRACE, 0);
}

tree::TerminalNode* JavaParser::EnumDeclarationContext::IMPLEMENTS() {
  return getToken(JavaParser::IMPLEMENTS, 0);
}

JavaParser::TypeListContext* JavaParser::EnumDeclarationContext::typeList() {
  return getRuleContext<JavaParser::TypeListContext>(0);
}

JavaParser::EnumConstantsContext* JavaParser::EnumDeclarationContext::enumConstants() {
  return getRuleContext<JavaParser::EnumConstantsContext>(0);
}

tree::TerminalNode* JavaParser::EnumDeclarationContext::COMMA() {
  return getToken(JavaParser::COMMA, 0);
}

JavaParser::EnumBodyDeclarationsContext* JavaParser::EnumDeclarationContext::enumBodyDeclarations() {
  return getRuleContext<JavaParser::EnumBodyDeclarationsContext>(0);
}


size_t JavaParser::EnumDeclarationContext::getRuleIndex() const {
  return JavaParser::RuleEnumDeclaration;
}

void JavaParser::EnumDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEnumDeclaration(this);
}

void JavaParser::EnumDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEnumDeclaration(this);
}

JavaParser::EnumDeclarationContext* JavaParser::enumDeclaration() {
  EnumDeclarationContext *_localctx = _tracker.createInstance<EnumDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 22, JavaParser::RuleEnumDeclaration);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(327);
    match(JavaParser::ENUM);
    setState(328);
    match(JavaParser::IDENTIFIER);
    setState(331);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaParser::IMPLEMENTS) {
      setState(329);
      match(JavaParser::IMPLEMENTS);
      setState(330);
      typeList();
    }
    setState(333);
    match(JavaParser::LBRACE);
    setState(335);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaParser::AT

    || _la == JavaParser::IDENTIFIER) {
      setState(334);
      enumConstants();
    }
    setState(338);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaParser::COMMA) {
      setState(337);
      match(JavaParser::COMMA);
    }
    setState(341);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaParser::SEMI) {
      setState(340);
      enumBodyDeclarations();
    }
    setState(343);
    match(JavaParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EnumConstantsContext ------------------------------------------------------------------

JavaParser::EnumConstantsContext::EnumConstantsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<JavaParser::EnumConstantContext *> JavaParser::EnumConstantsContext::enumConstant() {
  return getRuleContexts<JavaParser::EnumConstantContext>();
}

JavaParser::EnumConstantContext* JavaParser::EnumConstantsContext::enumConstant(size_t i) {
  return getRuleContext<JavaParser::EnumConstantContext>(i);
}

std::vector<tree::TerminalNode *> JavaParser::EnumConstantsContext::COMMA() {
  return getTokens(JavaParser::COMMA);
}

tree::TerminalNode* JavaParser::EnumConstantsContext::COMMA(size_t i) {
  return getToken(JavaParser::COMMA, i);
}


size_t JavaParser::EnumConstantsContext::getRuleIndex() const {
  return JavaParser::RuleEnumConstants;
}

void JavaParser::EnumConstantsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEnumConstants(this);
}

void JavaParser::EnumConstantsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEnumConstants(this);
}

JavaParser::EnumConstantsContext* JavaParser::enumConstants() {
  EnumConstantsContext *_localctx = _tracker.createInstance<EnumConstantsContext>(_ctx, getState());
  enterRule(_localctx, 24, JavaParser::RuleEnumConstants);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(345);
    enumConstant();
    setState(350);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(346);
        match(JavaParser::COMMA);
        setState(347);
        enumConstant(); 
      }
      setState(352);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EnumConstantContext ------------------------------------------------------------------

JavaParser::EnumConstantContext::EnumConstantContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaParser::EnumConstantContext::IDENTIFIER() {
  return getToken(JavaParser::IDENTIFIER, 0);
}

std::vector<JavaParser::AnnotationContext *> JavaParser::EnumConstantContext::annotation() {
  return getRuleContexts<JavaParser::AnnotationContext>();
}

JavaParser::AnnotationContext* JavaParser::EnumConstantContext::annotation(size_t i) {
  return getRuleContext<JavaParser::AnnotationContext>(i);
}

JavaParser::ArgumentsContext* JavaParser::EnumConstantContext::arguments() {
  return getRuleContext<JavaParser::ArgumentsContext>(0);
}

JavaParser::ClassBodyContext* JavaParser::EnumConstantContext::classBody() {
  return getRuleContext<JavaParser::ClassBodyContext>(0);
}


size_t JavaParser::EnumConstantContext::getRuleIndex() const {
  return JavaParser::RuleEnumConstant;
}

void JavaParser::EnumConstantContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEnumConstant(this);
}

void JavaParser::EnumConstantContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEnumConstant(this);
}

JavaParser::EnumConstantContext* JavaParser::enumConstant() {
  EnumConstantContext *_localctx = _tracker.createInstance<EnumConstantContext>(_ctx, getState());
  enterRule(_localctx, 26, JavaParser::RuleEnumConstant);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(356);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == JavaParser::AT) {
      setState(353);
      annotation();
      setState(358);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(359);
    match(JavaParser::IDENTIFIER);
    setState(361);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaParser::LPAREN) {
      setState(360);
      arguments();
    }
    setState(364);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaParser::LBRACE) {
      setState(363);
      classBody();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EnumBodyDeclarationsContext ------------------------------------------------------------------

JavaParser::EnumBodyDeclarationsContext::EnumBodyDeclarationsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaParser::EnumBodyDeclarationsContext::SEMI() {
  return getToken(JavaParser::SEMI, 0);
}

std::vector<JavaParser::ClassBodyDeclarationContext *> JavaParser::EnumBodyDeclarationsContext::classBodyDeclaration() {
  return getRuleContexts<JavaParser::ClassBodyDeclarationContext>();
}

JavaParser::ClassBodyDeclarationContext* JavaParser::EnumBodyDeclarationsContext::classBodyDeclaration(size_t i) {
  return getRuleContext<JavaParser::ClassBodyDeclarationContext>(i);
}


size_t JavaParser::EnumBodyDeclarationsContext::getRuleIndex() const {
  return JavaParser::RuleEnumBodyDeclarations;
}

void JavaParser::EnumBodyDeclarationsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEnumBodyDeclarations(this);
}

void JavaParser::EnumBodyDeclarationsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEnumBodyDeclarations(this);
}

JavaParser::EnumBodyDeclarationsContext* JavaParser::enumBodyDeclarations() {
  EnumBodyDeclarationsContext *_localctx = _tracker.createInstance<EnumBodyDeclarationsContext>(_ctx, getState());
  enterRule(_localctx, 28, JavaParser::RuleEnumBodyDeclarations);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(366);
    match(JavaParser::SEMI);
    setState(370);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << JavaParser::ABSTRACT)
      | (1ULL << JavaParser::BOOLEAN)
      | (1ULL << JavaParser::BYTE)
      | (1ULL << JavaParser::CHAR)
      | (1ULL << JavaParser::CLASS)
      | (1ULL << JavaParser::DOUBLE)
      | (1ULL << JavaParser::ENUM)
      | (1ULL << JavaParser::FINAL)
      | (1ULL << JavaParser::FLOAT)
      | (1ULL << JavaParser::INT)
      | (1ULL << JavaParser::INTERFACE)
      | (1ULL << JavaParser::LONG)
      | (1ULL << JavaParser::NATIVE)
      | (1ULL << JavaParser::PRIVATE)
      | (1ULL << JavaParser::PROTECTED)
      | (1ULL << JavaParser::PUBLIC)
      | (1ULL << JavaParser::SHORT)
      | (1ULL << JavaParser::STATIC)
      | (1ULL << JavaParser::STRICTFP)
      | (1ULL << JavaParser::SYNCHRONIZED)
      | (1ULL << JavaParser::TRANSIENT)
      | (1ULL << JavaParser::VOID)
      | (1ULL << JavaParser::VOLATILE)
      | (1ULL << JavaParser::LBRACE))) != 0) || ((((_la - 67) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 67)) & ((1ULL << (JavaParser::SEMI - 67))
      | (1ULL << (JavaParser::LT - 67))
      | (1ULL << (JavaParser::AT - 67))
      | (1ULL << (JavaParser::IDENTIFIER - 67)))) != 0)) {
      setState(367);
      classBodyDeclaration();
      setState(372);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InterfaceDeclarationContext ------------------------------------------------------------------

JavaParser::InterfaceDeclarationContext::InterfaceDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaParser::InterfaceDeclarationContext::INTERFACE() {
  return getToken(JavaParser::INTERFACE, 0);
}

tree::TerminalNode* JavaParser::InterfaceDeclarationContext::IDENTIFIER() {
  return getToken(JavaParser::IDENTIFIER, 0);
}

JavaParser::InterfaceBodyContext* JavaParser::InterfaceDeclarationContext::interfaceBody() {
  return getRuleContext<JavaParser::InterfaceBodyContext>(0);
}

JavaParser::TypeParametersContext* JavaParser::InterfaceDeclarationContext::typeParameters() {
  return getRuleContext<JavaParser::TypeParametersContext>(0);
}

tree::TerminalNode* JavaParser::InterfaceDeclarationContext::EXTENDS() {
  return getToken(JavaParser::EXTENDS, 0);
}

JavaParser::TypeListContext* JavaParser::InterfaceDeclarationContext::typeList() {
  return getRuleContext<JavaParser::TypeListContext>(0);
}


size_t JavaParser::InterfaceDeclarationContext::getRuleIndex() const {
  return JavaParser::RuleInterfaceDeclaration;
}

void JavaParser::InterfaceDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInterfaceDeclaration(this);
}

void JavaParser::InterfaceDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInterfaceDeclaration(this);
}

JavaParser::InterfaceDeclarationContext* JavaParser::interfaceDeclaration() {
  InterfaceDeclarationContext *_localctx = _tracker.createInstance<InterfaceDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 30, JavaParser::RuleInterfaceDeclaration);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(373);
    match(JavaParser::INTERFACE);
    setState(374);
    match(JavaParser::IDENTIFIER);
    setState(376);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaParser::LT) {
      setState(375);
      typeParameters();
    }
    setState(380);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaParser::EXTENDS) {
      setState(378);
      match(JavaParser::EXTENDS);
      setState(379);
      typeList();
    }
    setState(382);
    interfaceBody();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ClassBodyContext ------------------------------------------------------------------

JavaParser::ClassBodyContext::ClassBodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaParser::ClassBodyContext::LBRACE() {
  return getToken(JavaParser::LBRACE, 0);
}

tree::TerminalNode* JavaParser::ClassBodyContext::RBRACE() {
  return getToken(JavaParser::RBRACE, 0);
}

std::vector<JavaParser::ClassBodyDeclarationContext *> JavaParser::ClassBodyContext::classBodyDeclaration() {
  return getRuleContexts<JavaParser::ClassBodyDeclarationContext>();
}

JavaParser::ClassBodyDeclarationContext* JavaParser::ClassBodyContext::classBodyDeclaration(size_t i) {
  return getRuleContext<JavaParser::ClassBodyDeclarationContext>(i);
}


size_t JavaParser::ClassBodyContext::getRuleIndex() const {
  return JavaParser::RuleClassBody;
}

void JavaParser::ClassBodyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterClassBody(this);
}

void JavaParser::ClassBodyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitClassBody(this);
}

JavaParser::ClassBodyContext* JavaParser::classBody() {
  ClassBodyContext *_localctx = _tracker.createInstance<ClassBodyContext>(_ctx, getState());
  enterRule(_localctx, 32, JavaParser::RuleClassBody);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(384);
    match(JavaParser::LBRACE);
    setState(388);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << JavaParser::ABSTRACT)
      | (1ULL << JavaParser::BOOLEAN)
      | (1ULL << JavaParser::BYTE)
      | (1ULL << JavaParser::CHAR)
      | (1ULL << JavaParser::CLASS)
      | (1ULL << JavaParser::DOUBLE)
      | (1ULL << JavaParser::ENUM)
      | (1ULL << JavaParser::FINAL)
      | (1ULL << JavaParser::FLOAT)
      | (1ULL << JavaParser::INT)
      | (1ULL << JavaParser::INTERFACE)
      | (1ULL << JavaParser::LONG)
      | (1ULL << JavaParser::NATIVE)
      | (1ULL << JavaParser::PRIVATE)
      | (1ULL << JavaParser::PROTECTED)
      | (1ULL << JavaParser::PUBLIC)
      | (1ULL << JavaParser::SHORT)
      | (1ULL << JavaParser::STATIC)
      | (1ULL << JavaParser::STRICTFP)
      | (1ULL << JavaParser::SYNCHRONIZED)
      | (1ULL << JavaParser::TRANSIENT)
      | (1ULL << JavaParser::VOID)
      | (1ULL << JavaParser::VOLATILE)
      | (1ULL << JavaParser::LBRACE))) != 0) || ((((_la - 67) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 67)) & ((1ULL << (JavaParser::SEMI - 67))
      | (1ULL << (JavaParser::LT - 67))
      | (1ULL << (JavaParser::AT - 67))
      | (1ULL << (JavaParser::IDENTIFIER - 67)))) != 0)) {
      setState(385);
      classBodyDeclaration();
      setState(390);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(391);
    match(JavaParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InterfaceBodyContext ------------------------------------------------------------------

JavaParser::InterfaceBodyContext::InterfaceBodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaParser::InterfaceBodyContext::LBRACE() {
  return getToken(JavaParser::LBRACE, 0);
}

tree::TerminalNode* JavaParser::InterfaceBodyContext::RBRACE() {
  return getToken(JavaParser::RBRACE, 0);
}

std::vector<JavaParser::InterfaceBodyDeclarationContext *> JavaParser::InterfaceBodyContext::interfaceBodyDeclaration() {
  return getRuleContexts<JavaParser::InterfaceBodyDeclarationContext>();
}

JavaParser::InterfaceBodyDeclarationContext* JavaParser::InterfaceBodyContext::interfaceBodyDeclaration(size_t i) {
  return getRuleContext<JavaParser::InterfaceBodyDeclarationContext>(i);
}


size_t JavaParser::InterfaceBodyContext::getRuleIndex() const {
  return JavaParser::RuleInterfaceBody;
}

void JavaParser::InterfaceBodyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInterfaceBody(this);
}

void JavaParser::InterfaceBodyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInterfaceBody(this);
}

JavaParser::InterfaceBodyContext* JavaParser::interfaceBody() {
  InterfaceBodyContext *_localctx = _tracker.createInstance<InterfaceBodyContext>(_ctx, getState());
  enterRule(_localctx, 34, JavaParser::RuleInterfaceBody);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(393);
    match(JavaParser::LBRACE);
    setState(397);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << JavaParser::ABSTRACT)
      | (1ULL << JavaParser::BOOLEAN)
      | (1ULL << JavaParser::BYTE)
      | (1ULL << JavaParser::CHAR)
      | (1ULL << JavaParser::CLASS)
      | (1ULL << JavaParser::DEFAULT)
      | (1ULL << JavaParser::DOUBLE)
      | (1ULL << JavaParser::ENUM)
      | (1ULL << JavaParser::FINAL)
      | (1ULL << JavaParser::FLOAT)
      | (1ULL << JavaParser::INT)
      | (1ULL << JavaParser::INTERFACE)
      | (1ULL << JavaParser::LONG)
      | (1ULL << JavaParser::NATIVE)
      | (1ULL << JavaParser::PRIVATE)
      | (1ULL << JavaParser::PROTECTED)
      | (1ULL << JavaParser::PUBLIC)
      | (1ULL << JavaParser::SHORT)
      | (1ULL << JavaParser::STATIC)
      | (1ULL << JavaParser::STRICTFP)
      | (1ULL << JavaParser::SYNCHRONIZED)
      | (1ULL << JavaParser::TRANSIENT)
      | (1ULL << JavaParser::VOID)
      | (1ULL << JavaParser::VOLATILE))) != 0) || ((((_la - 67) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 67)) & ((1ULL << (JavaParser::SEMI - 67))
      | (1ULL << (JavaParser::LT - 67))
      | (1ULL << (JavaParser::AT - 67))
      | (1ULL << (JavaParser::IDENTIFIER - 67)))) != 0)) {
      setState(394);
      interfaceBodyDeclaration();
      setState(399);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(400);
    match(JavaParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ClassBodyDeclarationContext ------------------------------------------------------------------

JavaParser::ClassBodyDeclarationContext::ClassBodyDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaParser::ClassBodyDeclarationContext::SEMI() {
  return getToken(JavaParser::SEMI, 0);
}

JavaParser::BlockContext* JavaParser::ClassBodyDeclarationContext::block() {
  return getRuleContext<JavaParser::BlockContext>(0);
}

tree::TerminalNode* JavaParser::ClassBodyDeclarationContext::STATIC() {
  return getToken(JavaParser::STATIC, 0);
}

JavaParser::MemberDeclarationContext* JavaParser::ClassBodyDeclarationContext::memberDeclaration() {
  return getRuleContext<JavaParser::MemberDeclarationContext>(0);
}

std::vector<JavaParser::ModifierContext *> JavaParser::ClassBodyDeclarationContext::modifier() {
  return getRuleContexts<JavaParser::ModifierContext>();
}

JavaParser::ModifierContext* JavaParser::ClassBodyDeclarationContext::modifier(size_t i) {
  return getRuleContext<JavaParser::ModifierContext>(i);
}


size_t JavaParser::ClassBodyDeclarationContext::getRuleIndex() const {
  return JavaParser::RuleClassBodyDeclaration;
}

void JavaParser::ClassBodyDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterClassBodyDeclaration(this);
}

void JavaParser::ClassBodyDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitClassBodyDeclaration(this);
}

JavaParser::ClassBodyDeclarationContext* JavaParser::classBodyDeclaration() {
  ClassBodyDeclarationContext *_localctx = _tracker.createInstance<ClassBodyDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 36, JavaParser::RuleClassBodyDeclaration);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    setState(414);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(402);
      match(JavaParser::SEMI);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(404);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == JavaParser::STATIC) {
        setState(403);
        match(JavaParser::STATIC);
      }
      setState(406);
      block();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(410);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(407);
          modifier(); 
        }
        setState(412);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
      }
      setState(413);
      memberDeclaration();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MemberDeclarationContext ------------------------------------------------------------------

JavaParser::MemberDeclarationContext::MemberDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaParser::MethodDeclarationContext* JavaParser::MemberDeclarationContext::methodDeclaration() {
  return getRuleContext<JavaParser::MethodDeclarationContext>(0);
}

JavaParser::GenericMethodDeclarationContext* JavaParser::MemberDeclarationContext::genericMethodDeclaration() {
  return getRuleContext<JavaParser::GenericMethodDeclarationContext>(0);
}

JavaParser::FieldDeclarationContext* JavaParser::MemberDeclarationContext::fieldDeclaration() {
  return getRuleContext<JavaParser::FieldDeclarationContext>(0);
}

JavaParser::ConstructorDeclarationContext* JavaParser::MemberDeclarationContext::constructorDeclaration() {
  return getRuleContext<JavaParser::ConstructorDeclarationContext>(0);
}

JavaParser::GenericConstructorDeclarationContext* JavaParser::MemberDeclarationContext::genericConstructorDeclaration() {
  return getRuleContext<JavaParser::GenericConstructorDeclarationContext>(0);
}

JavaParser::InterfaceDeclarationContext* JavaParser::MemberDeclarationContext::interfaceDeclaration() {
  return getRuleContext<JavaParser::InterfaceDeclarationContext>(0);
}

JavaParser::AnnotationTypeDeclarationContext* JavaParser::MemberDeclarationContext::annotationTypeDeclaration() {
  return getRuleContext<JavaParser::AnnotationTypeDeclarationContext>(0);
}

JavaParser::ClassDeclarationContext* JavaParser::MemberDeclarationContext::classDeclaration() {
  return getRuleContext<JavaParser::ClassDeclarationContext>(0);
}

JavaParser::EnumDeclarationContext* JavaParser::MemberDeclarationContext::enumDeclaration() {
  return getRuleContext<JavaParser::EnumDeclarationContext>(0);
}


size_t JavaParser::MemberDeclarationContext::getRuleIndex() const {
  return JavaParser::RuleMemberDeclaration;
}

void JavaParser::MemberDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMemberDeclaration(this);
}

void JavaParser::MemberDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMemberDeclaration(this);
}

JavaParser::MemberDeclarationContext* JavaParser::memberDeclaration() {
  MemberDeclarationContext *_localctx = _tracker.createInstance<MemberDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 38, JavaParser::RuleMemberDeclaration);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(425);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(416);
      methodDeclaration();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(417);
      genericMethodDeclaration();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(418);
      fieldDeclaration();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(419);
      constructorDeclaration();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(420);
      genericConstructorDeclaration();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(421);
      interfaceDeclaration();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(422);
      annotationTypeDeclaration();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(423);
      classDeclaration();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(424);
      enumDeclaration();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MethodDeclarationContext ------------------------------------------------------------------

JavaParser::MethodDeclarationContext::MethodDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaParser::TypeTypeOrVoidContext* JavaParser::MethodDeclarationContext::typeTypeOrVoid() {
  return getRuleContext<JavaParser::TypeTypeOrVoidContext>(0);
}

tree::TerminalNode* JavaParser::MethodDeclarationContext::IDENTIFIER() {
  return getToken(JavaParser::IDENTIFIER, 0);
}

JavaParser::FormalParametersContext* JavaParser::MethodDeclarationContext::formalParameters() {
  return getRuleContext<JavaParser::FormalParametersContext>(0);
}

JavaParser::MethodBodyContext* JavaParser::MethodDeclarationContext::methodBody() {
  return getRuleContext<JavaParser::MethodBodyContext>(0);
}

std::vector<tree::TerminalNode *> JavaParser::MethodDeclarationContext::LBRACK() {
  return getTokens(JavaParser::LBRACK);
}

tree::TerminalNode* JavaParser::MethodDeclarationContext::LBRACK(size_t i) {
  return getToken(JavaParser::LBRACK, i);
}

std::vector<tree::TerminalNode *> JavaParser::MethodDeclarationContext::RBRACK() {
  return getTokens(JavaParser::RBRACK);
}

tree::TerminalNode* JavaParser::MethodDeclarationContext::RBRACK(size_t i) {
  return getToken(JavaParser::RBRACK, i);
}

tree::TerminalNode* JavaParser::MethodDeclarationContext::THROWS() {
  return getToken(JavaParser::THROWS, 0);
}

JavaParser::QualifiedNameListContext* JavaParser::MethodDeclarationContext::qualifiedNameList() {
  return getRuleContext<JavaParser::QualifiedNameListContext>(0);
}


size_t JavaParser::MethodDeclarationContext::getRuleIndex() const {
  return JavaParser::RuleMethodDeclaration;
}

void JavaParser::MethodDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMethodDeclaration(this);
}

void JavaParser::MethodDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMethodDeclaration(this);
}

JavaParser::MethodDeclarationContext* JavaParser::methodDeclaration() {
  MethodDeclarationContext *_localctx = _tracker.createInstance<MethodDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 40, JavaParser::RuleMethodDeclaration);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(427);
    typeTypeOrVoid();
    setState(428);
    match(JavaParser::IDENTIFIER);
    setState(429);
    formalParameters();
    setState(434);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == JavaParser::LBRACK) {
      setState(430);
      match(JavaParser::LBRACK);
      setState(431);
      match(JavaParser::RBRACK);
      setState(436);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(439);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaParser::THROWS) {
      setState(437);
      match(JavaParser::THROWS);
      setState(438);
      qualifiedNameList();
    }
    setState(441);
    methodBody();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MethodBodyContext ------------------------------------------------------------------

JavaParser::MethodBodyContext::MethodBodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaParser::BlockContext* JavaParser::MethodBodyContext::block() {
  return getRuleContext<JavaParser::BlockContext>(0);
}

tree::TerminalNode* JavaParser::MethodBodyContext::SEMI() {
  return getToken(JavaParser::SEMI, 0);
}


size_t JavaParser::MethodBodyContext::getRuleIndex() const {
  return JavaParser::RuleMethodBody;
}

void JavaParser::MethodBodyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMethodBody(this);
}

void JavaParser::MethodBodyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMethodBody(this);
}

JavaParser::MethodBodyContext* JavaParser::methodBody() {
  MethodBodyContext *_localctx = _tracker.createInstance<MethodBodyContext>(_ctx, getState());
  enterRule(_localctx, 42, JavaParser::RuleMethodBody);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(445);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaParser::LBRACE: {
        enterOuterAlt(_localctx, 1);
        setState(443);
        block();
        break;
      }

      case JavaParser::SEMI: {
        enterOuterAlt(_localctx, 2);
        setState(444);
        match(JavaParser::SEMI);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeTypeOrVoidContext ------------------------------------------------------------------

JavaParser::TypeTypeOrVoidContext::TypeTypeOrVoidContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaParser::TypeTypeContext* JavaParser::TypeTypeOrVoidContext::typeType() {
  return getRuleContext<JavaParser::TypeTypeContext>(0);
}

tree::TerminalNode* JavaParser::TypeTypeOrVoidContext::VOID() {
  return getToken(JavaParser::VOID, 0);
}


size_t JavaParser::TypeTypeOrVoidContext::getRuleIndex() const {
  return JavaParser::RuleTypeTypeOrVoid;
}

void JavaParser::TypeTypeOrVoidContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeTypeOrVoid(this);
}

void JavaParser::TypeTypeOrVoidContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeTypeOrVoid(this);
}

JavaParser::TypeTypeOrVoidContext* JavaParser::typeTypeOrVoid() {
  TypeTypeOrVoidContext *_localctx = _tracker.createInstance<TypeTypeOrVoidContext>(_ctx, getState());
  enterRule(_localctx, 44, JavaParser::RuleTypeTypeOrVoid);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(449);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaParser::BOOLEAN:
      case JavaParser::BYTE:
      case JavaParser::CHAR:
      case JavaParser::DOUBLE:
      case JavaParser::FLOAT:
      case JavaParser::INT:
      case JavaParser::LONG:
      case JavaParser::SHORT:
      case JavaParser::AT:
      case JavaParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(447);
        typeType();
        break;
      }

      case JavaParser::VOID: {
        enterOuterAlt(_localctx, 2);
        setState(448);
        match(JavaParser::VOID);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GenericMethodDeclarationContext ------------------------------------------------------------------

JavaParser::GenericMethodDeclarationContext::GenericMethodDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaParser::TypeParametersContext* JavaParser::GenericMethodDeclarationContext::typeParameters() {
  return getRuleContext<JavaParser::TypeParametersContext>(0);
}

JavaParser::MethodDeclarationContext* JavaParser::GenericMethodDeclarationContext::methodDeclaration() {
  return getRuleContext<JavaParser::MethodDeclarationContext>(0);
}


size_t JavaParser::GenericMethodDeclarationContext::getRuleIndex() const {
  return JavaParser::RuleGenericMethodDeclaration;
}

void JavaParser::GenericMethodDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGenericMethodDeclaration(this);
}

void JavaParser::GenericMethodDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGenericMethodDeclaration(this);
}

JavaParser::GenericMethodDeclarationContext* JavaParser::genericMethodDeclaration() {
  GenericMethodDeclarationContext *_localctx = _tracker.createInstance<GenericMethodDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 46, JavaParser::RuleGenericMethodDeclaration);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(451);
    typeParameters();
    setState(452);
    methodDeclaration();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GenericConstructorDeclarationContext ------------------------------------------------------------------

JavaParser::GenericConstructorDeclarationContext::GenericConstructorDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaParser::TypeParametersContext* JavaParser::GenericConstructorDeclarationContext::typeParameters() {
  return getRuleContext<JavaParser::TypeParametersContext>(0);
}

JavaParser::ConstructorDeclarationContext* JavaParser::GenericConstructorDeclarationContext::constructorDeclaration() {
  return getRuleContext<JavaParser::ConstructorDeclarationContext>(0);
}


size_t JavaParser::GenericConstructorDeclarationContext::getRuleIndex() const {
  return JavaParser::RuleGenericConstructorDeclaration;
}

void JavaParser::GenericConstructorDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGenericConstructorDeclaration(this);
}

void JavaParser::GenericConstructorDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGenericConstructorDeclaration(this);
}

JavaParser::GenericConstructorDeclarationContext* JavaParser::genericConstructorDeclaration() {
  GenericConstructorDeclarationContext *_localctx = _tracker.createInstance<GenericConstructorDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 48, JavaParser::RuleGenericConstructorDeclaration);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(454);
    typeParameters();
    setState(455);
    constructorDeclaration();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstructorDeclarationContext ------------------------------------------------------------------

JavaParser::ConstructorDeclarationContext::ConstructorDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaParser::ConstructorDeclarationContext::IDENTIFIER() {
  return getToken(JavaParser::IDENTIFIER, 0);
}

JavaParser::FormalParametersContext* JavaParser::ConstructorDeclarationContext::formalParameters() {
  return getRuleContext<JavaParser::FormalParametersContext>(0);
}

JavaParser::BlockContext* JavaParser::ConstructorDeclarationContext::block() {
  return getRuleContext<JavaParser::BlockContext>(0);
}

tree::TerminalNode* JavaParser::ConstructorDeclarationContext::THROWS() {
  return getToken(JavaParser::THROWS, 0);
}

JavaParser::QualifiedNameListContext* JavaParser::ConstructorDeclarationContext::qualifiedNameList() {
  return getRuleContext<JavaParser::QualifiedNameListContext>(0);
}


size_t JavaParser::ConstructorDeclarationContext::getRuleIndex() const {
  return JavaParser::RuleConstructorDeclaration;
}

void JavaParser::ConstructorDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConstructorDeclaration(this);
}

void JavaParser::ConstructorDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConstructorDeclaration(this);
}

JavaParser::ConstructorDeclarationContext* JavaParser::constructorDeclaration() {
  ConstructorDeclarationContext *_localctx = _tracker.createInstance<ConstructorDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 50, JavaParser::RuleConstructorDeclaration);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(457);
    match(JavaParser::IDENTIFIER);
    setState(458);
    formalParameters();
    setState(461);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaParser::THROWS) {
      setState(459);
      match(JavaParser::THROWS);
      setState(460);
      qualifiedNameList();
    }
    setState(463);
    dynamic_cast<ConstructorDeclarationContext *>(_localctx)->constructorBody = block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FieldDeclarationContext ------------------------------------------------------------------

JavaParser::FieldDeclarationContext::FieldDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaParser::TypeTypeContext* JavaParser::FieldDeclarationContext::typeType() {
  return getRuleContext<JavaParser::TypeTypeContext>(0);
}

JavaParser::VariableDeclaratorsContext* JavaParser::FieldDeclarationContext::variableDeclarators() {
  return getRuleContext<JavaParser::VariableDeclaratorsContext>(0);
}

tree::TerminalNode* JavaParser::FieldDeclarationContext::SEMI() {
  return getToken(JavaParser::SEMI, 0);
}


size_t JavaParser::FieldDeclarationContext::getRuleIndex() const {
  return JavaParser::RuleFieldDeclaration;
}

void JavaParser::FieldDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFieldDeclaration(this);
}

void JavaParser::FieldDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFieldDeclaration(this);
}

JavaParser::FieldDeclarationContext* JavaParser::fieldDeclaration() {
  FieldDeclarationContext *_localctx = _tracker.createInstance<FieldDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 52, JavaParser::RuleFieldDeclaration);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(465);
    typeType();
    setState(466);
    variableDeclarators();
    setState(467);
    match(JavaParser::SEMI);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InterfaceBodyDeclarationContext ------------------------------------------------------------------

JavaParser::InterfaceBodyDeclarationContext::InterfaceBodyDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaParser::InterfaceMemberDeclarationContext* JavaParser::InterfaceBodyDeclarationContext::interfaceMemberDeclaration() {
  return getRuleContext<JavaParser::InterfaceMemberDeclarationContext>(0);
}

std::vector<JavaParser::ModifierContext *> JavaParser::InterfaceBodyDeclarationContext::modifier() {
  return getRuleContexts<JavaParser::ModifierContext>();
}

JavaParser::ModifierContext* JavaParser::InterfaceBodyDeclarationContext::modifier(size_t i) {
  return getRuleContext<JavaParser::ModifierContext>(i);
}

tree::TerminalNode* JavaParser::InterfaceBodyDeclarationContext::SEMI() {
  return getToken(JavaParser::SEMI, 0);
}


size_t JavaParser::InterfaceBodyDeclarationContext::getRuleIndex() const {
  return JavaParser::RuleInterfaceBodyDeclaration;
}

void JavaParser::InterfaceBodyDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInterfaceBodyDeclaration(this);
}

void JavaParser::InterfaceBodyDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInterfaceBodyDeclaration(this);
}

JavaParser::InterfaceBodyDeclarationContext* JavaParser::interfaceBodyDeclaration() {
  InterfaceBodyDeclarationContext *_localctx = _tracker.createInstance<InterfaceBodyDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 54, JavaParser::RuleInterfaceBodyDeclaration);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    setState(477);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaParser::ABSTRACT:
      case JavaParser::BOOLEAN:
      case JavaParser::BYTE:
      case JavaParser::CHAR:
      case JavaParser::CLASS:
      case JavaParser::DEFAULT:
      case JavaParser::DOUBLE:
      case JavaParser::ENUM:
      case JavaParser::FINAL:
      case JavaParser::FLOAT:
      case JavaParser::INT:
      case JavaParser::INTERFACE:
      case JavaParser::LONG:
      case JavaParser::NATIVE:
      case JavaParser::PRIVATE:
      case JavaParser::PROTECTED:
      case JavaParser::PUBLIC:
      case JavaParser::SHORT:
      case JavaParser::STATIC:
      case JavaParser::STRICTFP:
      case JavaParser::SYNCHRONIZED:
      case JavaParser::TRANSIENT:
      case JavaParser::VOID:
      case JavaParser::VOLATILE:
      case JavaParser::LT:
      case JavaParser::AT:
      case JavaParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(472);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 41, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
          if (alt == 1) {
            setState(469);
            modifier(); 
          }
          setState(474);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 41, _ctx);
        }
        setState(475);
        interfaceMemberDeclaration();
        break;
      }

      case JavaParser::SEMI: {
        enterOuterAlt(_localctx, 2);
        setState(476);
        match(JavaParser::SEMI);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InterfaceMemberDeclarationContext ------------------------------------------------------------------

JavaParser::InterfaceMemberDeclarationContext::InterfaceMemberDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaParser::ConstDeclarationContext* JavaParser::InterfaceMemberDeclarationContext::constDeclaration() {
  return getRuleContext<JavaParser::ConstDeclarationContext>(0);
}

JavaParser::InterfaceMethodDeclarationContext* JavaParser::InterfaceMemberDeclarationContext::interfaceMethodDeclaration() {
  return getRuleContext<JavaParser::InterfaceMethodDeclarationContext>(0);
}

JavaParser::GenericInterfaceMethodDeclarationContext* JavaParser::InterfaceMemberDeclarationContext::genericInterfaceMethodDeclaration() {
  return getRuleContext<JavaParser::GenericInterfaceMethodDeclarationContext>(0);
}

JavaParser::InterfaceDeclarationContext* JavaParser::InterfaceMemberDeclarationContext::interfaceDeclaration() {
  return getRuleContext<JavaParser::InterfaceDeclarationContext>(0);
}

JavaParser::AnnotationTypeDeclarationContext* JavaParser::InterfaceMemberDeclarationContext::annotationTypeDeclaration() {
  return getRuleContext<JavaParser::AnnotationTypeDeclarationContext>(0);
}

JavaParser::ClassDeclarationContext* JavaParser::InterfaceMemberDeclarationContext::classDeclaration() {
  return getRuleContext<JavaParser::ClassDeclarationContext>(0);
}

JavaParser::EnumDeclarationContext* JavaParser::InterfaceMemberDeclarationContext::enumDeclaration() {
  return getRuleContext<JavaParser::EnumDeclarationContext>(0);
}


size_t JavaParser::InterfaceMemberDeclarationContext::getRuleIndex() const {
  return JavaParser::RuleInterfaceMemberDeclaration;
}

void JavaParser::InterfaceMemberDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInterfaceMemberDeclaration(this);
}

void JavaParser::InterfaceMemberDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInterfaceMemberDeclaration(this);
}

JavaParser::InterfaceMemberDeclarationContext* JavaParser::interfaceMemberDeclaration() {
  InterfaceMemberDeclarationContext *_localctx = _tracker.createInstance<InterfaceMemberDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 56, JavaParser::RuleInterfaceMemberDeclaration);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(486);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 43, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(479);
      constDeclaration();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(480);
      interfaceMethodDeclaration();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(481);
      genericInterfaceMethodDeclaration();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(482);
      interfaceDeclaration();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(483);
      annotationTypeDeclaration();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(484);
      classDeclaration();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(485);
      enumDeclaration();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstDeclarationContext ------------------------------------------------------------------

JavaParser::ConstDeclarationContext::ConstDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaParser::TypeTypeContext* JavaParser::ConstDeclarationContext::typeType() {
  return getRuleContext<JavaParser::TypeTypeContext>(0);
}

std::vector<JavaParser::ConstantDeclaratorContext *> JavaParser::ConstDeclarationContext::constantDeclarator() {
  return getRuleContexts<JavaParser::ConstantDeclaratorContext>();
}

JavaParser::ConstantDeclaratorContext* JavaParser::ConstDeclarationContext::constantDeclarator(size_t i) {
  return getRuleContext<JavaParser::ConstantDeclaratorContext>(i);
}

tree::TerminalNode* JavaParser::ConstDeclarationContext::SEMI() {
  return getToken(JavaParser::SEMI, 0);
}

std::vector<tree::TerminalNode *> JavaParser::ConstDeclarationContext::COMMA() {
  return getTokens(JavaParser::COMMA);
}

tree::TerminalNode* JavaParser::ConstDeclarationContext::COMMA(size_t i) {
  return getToken(JavaParser::COMMA, i);
}


size_t JavaParser::ConstDeclarationContext::getRuleIndex() const {
  return JavaParser::RuleConstDeclaration;
}

void JavaParser::ConstDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConstDeclaration(this);
}

void JavaParser::ConstDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConstDeclaration(this);
}

JavaParser::ConstDeclarationContext* JavaParser::constDeclaration() {
  ConstDeclarationContext *_localctx = _tracker.createInstance<ConstDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 58, JavaParser::RuleConstDeclaration);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(488);
    typeType();
    setState(489);
    constantDeclarator();
    setState(494);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == JavaParser::COMMA) {
      setState(490);
      match(JavaParser::COMMA);
      setState(491);
      constantDeclarator();
      setState(496);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(497);
    match(JavaParser::SEMI);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstantDeclaratorContext ------------------------------------------------------------------

JavaParser::ConstantDeclaratorContext::ConstantDeclaratorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaParser::ConstantDeclaratorContext::IDENTIFIER() {
  return getToken(JavaParser::IDENTIFIER, 0);
}

tree::TerminalNode* JavaParser::ConstantDeclaratorContext::ASSIGN() {
  return getToken(JavaParser::ASSIGN, 0);
}

JavaParser::VariableInitializerContext* JavaParser::ConstantDeclaratorContext::variableInitializer() {
  return getRuleContext<JavaParser::VariableInitializerContext>(0);
}

std::vector<tree::TerminalNode *> JavaParser::ConstantDeclaratorContext::LBRACK() {
  return getTokens(JavaParser::LBRACK);
}

tree::TerminalNode* JavaParser::ConstantDeclaratorContext::LBRACK(size_t i) {
  return getToken(JavaParser::LBRACK, i);
}

std::vector<tree::TerminalNode *> JavaParser::ConstantDeclaratorContext::RBRACK() {
  return getTokens(JavaParser::RBRACK);
}

tree::TerminalNode* JavaParser::ConstantDeclaratorContext::RBRACK(size_t i) {
  return getToken(JavaParser::RBRACK, i);
}


size_t JavaParser::ConstantDeclaratorContext::getRuleIndex() const {
  return JavaParser::RuleConstantDeclarator;
}

void JavaParser::ConstantDeclaratorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConstantDeclarator(this);
}

void JavaParser::ConstantDeclaratorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConstantDeclarator(this);
}

JavaParser::ConstantDeclaratorContext* JavaParser::constantDeclarator() {
  ConstantDeclaratorContext *_localctx = _tracker.createInstance<ConstantDeclaratorContext>(_ctx, getState());
  enterRule(_localctx, 60, JavaParser::RuleConstantDeclarator);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(499);
    match(JavaParser::IDENTIFIER);
    setState(504);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == JavaParser::LBRACK) {
      setState(500);
      match(JavaParser::LBRACK);
      setState(501);
      match(JavaParser::RBRACK);
      setState(506);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(507);
    match(JavaParser::ASSIGN);
    setState(508);
    variableInitializer();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InterfaceMethodDeclarationContext ------------------------------------------------------------------

JavaParser::InterfaceMethodDeclarationContext::InterfaceMethodDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaParser::InterfaceMethodDeclarationContext::IDENTIFIER() {
  return getToken(JavaParser::IDENTIFIER, 0);
}

JavaParser::FormalParametersContext* JavaParser::InterfaceMethodDeclarationContext::formalParameters() {
  return getRuleContext<JavaParser::FormalParametersContext>(0);
}

JavaParser::MethodBodyContext* JavaParser::InterfaceMethodDeclarationContext::methodBody() {
  return getRuleContext<JavaParser::MethodBodyContext>(0);
}

JavaParser::TypeTypeOrVoidContext* JavaParser::InterfaceMethodDeclarationContext::typeTypeOrVoid() {
  return getRuleContext<JavaParser::TypeTypeOrVoidContext>(0);
}

JavaParser::TypeParametersContext* JavaParser::InterfaceMethodDeclarationContext::typeParameters() {
  return getRuleContext<JavaParser::TypeParametersContext>(0);
}

std::vector<JavaParser::InterfaceMethodModifierContext *> JavaParser::InterfaceMethodDeclarationContext::interfaceMethodModifier() {
  return getRuleContexts<JavaParser::InterfaceMethodModifierContext>();
}

JavaParser::InterfaceMethodModifierContext* JavaParser::InterfaceMethodDeclarationContext::interfaceMethodModifier(size_t i) {
  return getRuleContext<JavaParser::InterfaceMethodModifierContext>(i);
}

std::vector<tree::TerminalNode *> JavaParser::InterfaceMethodDeclarationContext::LBRACK() {
  return getTokens(JavaParser::LBRACK);
}

tree::TerminalNode* JavaParser::InterfaceMethodDeclarationContext::LBRACK(size_t i) {
  return getToken(JavaParser::LBRACK, i);
}

std::vector<tree::TerminalNode *> JavaParser::InterfaceMethodDeclarationContext::RBRACK() {
  return getTokens(JavaParser::RBRACK);
}

tree::TerminalNode* JavaParser::InterfaceMethodDeclarationContext::RBRACK(size_t i) {
  return getToken(JavaParser::RBRACK, i);
}

tree::TerminalNode* JavaParser::InterfaceMethodDeclarationContext::THROWS() {
  return getToken(JavaParser::THROWS, 0);
}

JavaParser::QualifiedNameListContext* JavaParser::InterfaceMethodDeclarationContext::qualifiedNameList() {
  return getRuleContext<JavaParser::QualifiedNameListContext>(0);
}

std::vector<JavaParser::AnnotationContext *> JavaParser::InterfaceMethodDeclarationContext::annotation() {
  return getRuleContexts<JavaParser::AnnotationContext>();
}

JavaParser::AnnotationContext* JavaParser::InterfaceMethodDeclarationContext::annotation(size_t i) {
  return getRuleContext<JavaParser::AnnotationContext>(i);
}


size_t JavaParser::InterfaceMethodDeclarationContext::getRuleIndex() const {
  return JavaParser::RuleInterfaceMethodDeclaration;
}

void JavaParser::InterfaceMethodDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInterfaceMethodDeclaration(this);
}

void JavaParser::InterfaceMethodDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInterfaceMethodDeclaration(this);
}

JavaParser::InterfaceMethodDeclarationContext* JavaParser::interfaceMethodDeclaration() {
  InterfaceMethodDeclarationContext *_localctx = _tracker.createInstance<InterfaceMethodDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 62, JavaParser::RuleInterfaceMethodDeclaration);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(513);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 46, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(510);
        interfaceMethodModifier(); 
      }
      setState(515);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 46, _ctx);
    }
    setState(526);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaParser::BOOLEAN:
      case JavaParser::BYTE:
      case JavaParser::CHAR:
      case JavaParser::DOUBLE:
      case JavaParser::FLOAT:
      case JavaParser::INT:
      case JavaParser::LONG:
      case JavaParser::SHORT:
      case JavaParser::VOID:
      case JavaParser::AT:
      case JavaParser::IDENTIFIER: {
        setState(516);
        typeTypeOrVoid();
        break;
      }

      case JavaParser::LT: {
        setState(517);
        typeParameters();
        setState(521);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 47, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
          if (alt == 1) {
            setState(518);
            annotation(); 
          }
          setState(523);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 47, _ctx);
        }
        setState(524);
        typeTypeOrVoid();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(528);
    match(JavaParser::IDENTIFIER);
    setState(529);
    formalParameters();
    setState(534);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == JavaParser::LBRACK) {
      setState(530);
      match(JavaParser::LBRACK);
      setState(531);
      match(JavaParser::RBRACK);
      setState(536);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(539);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaParser::THROWS) {
      setState(537);
      match(JavaParser::THROWS);
      setState(538);
      qualifiedNameList();
    }
    setState(541);
    methodBody();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InterfaceMethodModifierContext ------------------------------------------------------------------

JavaParser::InterfaceMethodModifierContext::InterfaceMethodModifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaParser::AnnotationContext* JavaParser::InterfaceMethodModifierContext::annotation() {
  return getRuleContext<JavaParser::AnnotationContext>(0);
}

tree::TerminalNode* JavaParser::InterfaceMethodModifierContext::PUBLIC() {
  return getToken(JavaParser::PUBLIC, 0);
}

tree::TerminalNode* JavaParser::InterfaceMethodModifierContext::ABSTRACT() {
  return getToken(JavaParser::ABSTRACT, 0);
}

tree::TerminalNode* JavaParser::InterfaceMethodModifierContext::DEFAULT() {
  return getToken(JavaParser::DEFAULT, 0);
}

tree::TerminalNode* JavaParser::InterfaceMethodModifierContext::STATIC() {
  return getToken(JavaParser::STATIC, 0);
}

tree::TerminalNode* JavaParser::InterfaceMethodModifierContext::STRICTFP() {
  return getToken(JavaParser::STRICTFP, 0);
}


size_t JavaParser::InterfaceMethodModifierContext::getRuleIndex() const {
  return JavaParser::RuleInterfaceMethodModifier;
}

void JavaParser::InterfaceMethodModifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInterfaceMethodModifier(this);
}

void JavaParser::InterfaceMethodModifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInterfaceMethodModifier(this);
}

JavaParser::InterfaceMethodModifierContext* JavaParser::interfaceMethodModifier() {
  InterfaceMethodModifierContext *_localctx = _tracker.createInstance<InterfaceMethodModifierContext>(_ctx, getState());
  enterRule(_localctx, 64, JavaParser::RuleInterfaceMethodModifier);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(549);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaParser::AT: {
        enterOuterAlt(_localctx, 1);
        setState(543);
        annotation();
        break;
      }

      case JavaParser::PUBLIC: {
        enterOuterAlt(_localctx, 2);
        setState(544);
        match(JavaParser::PUBLIC);
        break;
      }

      case JavaParser::ABSTRACT: {
        enterOuterAlt(_localctx, 3);
        setState(545);
        match(JavaParser::ABSTRACT);
        break;
      }

      case JavaParser::DEFAULT: {
        enterOuterAlt(_localctx, 4);
        setState(546);
        match(JavaParser::DEFAULT);
        break;
      }

      case JavaParser::STATIC: {
        enterOuterAlt(_localctx, 5);
        setState(547);
        match(JavaParser::STATIC);
        break;
      }

      case JavaParser::STRICTFP: {
        enterOuterAlt(_localctx, 6);
        setState(548);
        match(JavaParser::STRICTFP);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GenericInterfaceMethodDeclarationContext ------------------------------------------------------------------

JavaParser::GenericInterfaceMethodDeclarationContext::GenericInterfaceMethodDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaParser::TypeParametersContext* JavaParser::GenericInterfaceMethodDeclarationContext::typeParameters() {
  return getRuleContext<JavaParser::TypeParametersContext>(0);
}

JavaParser::InterfaceMethodDeclarationContext* JavaParser::GenericInterfaceMethodDeclarationContext::interfaceMethodDeclaration() {
  return getRuleContext<JavaParser::InterfaceMethodDeclarationContext>(0);
}


size_t JavaParser::GenericInterfaceMethodDeclarationContext::getRuleIndex() const {
  return JavaParser::RuleGenericInterfaceMethodDeclaration;
}

void JavaParser::GenericInterfaceMethodDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGenericInterfaceMethodDeclaration(this);
}

void JavaParser::GenericInterfaceMethodDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGenericInterfaceMethodDeclaration(this);
}

JavaParser::GenericInterfaceMethodDeclarationContext* JavaParser::genericInterfaceMethodDeclaration() {
  GenericInterfaceMethodDeclarationContext *_localctx = _tracker.createInstance<GenericInterfaceMethodDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 66, JavaParser::RuleGenericInterfaceMethodDeclaration);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(551);
    typeParameters();
    setState(552);
    interfaceMethodDeclaration();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableDeclaratorsContext ------------------------------------------------------------------

JavaParser::VariableDeclaratorsContext::VariableDeclaratorsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<JavaParser::VariableDeclaratorContext *> JavaParser::VariableDeclaratorsContext::variableDeclarator() {
  return getRuleContexts<JavaParser::VariableDeclaratorContext>();
}

JavaParser::VariableDeclaratorContext* JavaParser::VariableDeclaratorsContext::variableDeclarator(size_t i) {
  return getRuleContext<JavaParser::VariableDeclaratorContext>(i);
}

std::vector<tree::TerminalNode *> JavaParser::VariableDeclaratorsContext::COMMA() {
  return getTokens(JavaParser::COMMA);
}

tree::TerminalNode* JavaParser::VariableDeclaratorsContext::COMMA(size_t i) {
  return getToken(JavaParser::COMMA, i);
}


size_t JavaParser::VariableDeclaratorsContext::getRuleIndex() const {
  return JavaParser::RuleVariableDeclarators;
}

void JavaParser::VariableDeclaratorsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariableDeclarators(this);
}

void JavaParser::VariableDeclaratorsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariableDeclarators(this);
}

JavaParser::VariableDeclaratorsContext* JavaParser::variableDeclarators() {
  VariableDeclaratorsContext *_localctx = _tracker.createInstance<VariableDeclaratorsContext>(_ctx, getState());
  enterRule(_localctx, 68, JavaParser::RuleVariableDeclarators);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(554);
    variableDeclarator();
    setState(559);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == JavaParser::COMMA) {
      setState(555);
      match(JavaParser::COMMA);
      setState(556);
      variableDeclarator();
      setState(561);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableDeclaratorContext ------------------------------------------------------------------

JavaParser::VariableDeclaratorContext::VariableDeclaratorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaParser::VariableDeclaratorIdContext* JavaParser::VariableDeclaratorContext::variableDeclaratorId() {
  return getRuleContext<JavaParser::VariableDeclaratorIdContext>(0);
}

tree::TerminalNode* JavaParser::VariableDeclaratorContext::ASSIGN() {
  return getToken(JavaParser::ASSIGN, 0);
}

JavaParser::VariableInitializerContext* JavaParser::VariableDeclaratorContext::variableInitializer() {
  return getRuleContext<JavaParser::VariableInitializerContext>(0);
}


size_t JavaParser::VariableDeclaratorContext::getRuleIndex() const {
  return JavaParser::RuleVariableDeclarator;
}

void JavaParser::VariableDeclaratorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariableDeclarator(this);
}

void JavaParser::VariableDeclaratorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariableDeclarator(this);
}

JavaParser::VariableDeclaratorContext* JavaParser::variableDeclarator() {
  VariableDeclaratorContext *_localctx = _tracker.createInstance<VariableDeclaratorContext>(_ctx, getState());
  enterRule(_localctx, 70, JavaParser::RuleVariableDeclarator);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(562);
    variableDeclaratorId();
    setState(565);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaParser::ASSIGN) {
      setState(563);
      match(JavaParser::ASSIGN);
      setState(564);
      variableInitializer();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableDeclaratorIdContext ------------------------------------------------------------------

JavaParser::VariableDeclaratorIdContext::VariableDeclaratorIdContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaParser::VariableDeclaratorIdContext::IDENTIFIER() {
  return getToken(JavaParser::IDENTIFIER, 0);
}

std::vector<tree::TerminalNode *> JavaParser::VariableDeclaratorIdContext::LBRACK() {
  return getTokens(JavaParser::LBRACK);
}

tree::TerminalNode* JavaParser::VariableDeclaratorIdContext::LBRACK(size_t i) {
  return getToken(JavaParser::LBRACK, i);
}

std::vector<tree::TerminalNode *> JavaParser::VariableDeclaratorIdContext::RBRACK() {
  return getTokens(JavaParser::RBRACK);
}

tree::TerminalNode* JavaParser::VariableDeclaratorIdContext::RBRACK(size_t i) {
  return getToken(JavaParser::RBRACK, i);
}


size_t JavaParser::VariableDeclaratorIdContext::getRuleIndex() const {
  return JavaParser::RuleVariableDeclaratorId;
}

void JavaParser::VariableDeclaratorIdContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariableDeclaratorId(this);
}

void JavaParser::VariableDeclaratorIdContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariableDeclaratorId(this);
}

JavaParser::VariableDeclaratorIdContext* JavaParser::variableDeclaratorId() {
  VariableDeclaratorIdContext *_localctx = _tracker.createInstance<VariableDeclaratorIdContext>(_ctx, getState());
  enterRule(_localctx, 72, JavaParser::RuleVariableDeclaratorId);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(567);
    match(JavaParser::IDENTIFIER);
    setState(572);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == JavaParser::LBRACK) {
      setState(568);
      match(JavaParser::LBRACK);
      setState(569);
      match(JavaParser::RBRACK);
      setState(574);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableInitializerContext ------------------------------------------------------------------

JavaParser::VariableInitializerContext::VariableInitializerContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaParser::ArrayInitializerContext* JavaParser::VariableInitializerContext::arrayInitializer() {
  return getRuleContext<JavaParser::ArrayInitializerContext>(0);
}

JavaParser::ExpressionContext* JavaParser::VariableInitializerContext::expression() {
  return getRuleContext<JavaParser::ExpressionContext>(0);
}


size_t JavaParser::VariableInitializerContext::getRuleIndex() const {
  return JavaParser::RuleVariableInitializer;
}

void JavaParser::VariableInitializerContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariableInitializer(this);
}

void JavaParser::VariableInitializerContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariableInitializer(this);
}

JavaParser::VariableInitializerContext* JavaParser::variableInitializer() {
  VariableInitializerContext *_localctx = _tracker.createInstance<VariableInitializerContext>(_ctx, getState());
  enterRule(_localctx, 74, JavaParser::RuleVariableInitializer);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(577);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaParser::LBRACE: {
        enterOuterAlt(_localctx, 1);
        setState(575);
        arrayInitializer();
        break;
      }

      case JavaParser::BOOLEAN:
      case JavaParser::BYTE:
      case JavaParser::CHAR:
      case JavaParser::DOUBLE:
      case JavaParser::FLOAT:
      case JavaParser::INT:
      case JavaParser::LONG:
      case JavaParser::NEW:
      case JavaParser::SHORT:
      case JavaParser::SUPER:
      case JavaParser::THIS:
      case JavaParser::VOID:
      case JavaParser::DECIMAL_LITERAL:
      case JavaParser::HEX_LITERAL:
      case JavaParser::OCT_LITERAL:
      case JavaParser::BINARY_LITERAL:
      case JavaParser::FLOAT_LITERAL:
      case JavaParser::HEX_FLOAT_LITERAL:
      case JavaParser::BOOL_LITERAL:
      case JavaParser::CHAR_LITERAL:
      case JavaParser::STRING_LITERAL:
      case JavaParser::NULL_LITERAL:
      case JavaParser::LPAREN:
      case JavaParser::LT:
      case JavaParser::BANG:
      case JavaParser::TILDE:
      case JavaParser::INC:
      case JavaParser::DEC:
      case JavaParser::ADD:
      case JavaParser::SUB:
      case JavaParser::AT:
      case JavaParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 2);
        setState(576);
        expression(0);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrayInitializerContext ------------------------------------------------------------------

JavaParser::ArrayInitializerContext::ArrayInitializerContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaParser::ArrayInitializerContext::LBRACE() {
  return getToken(JavaParser::LBRACE, 0);
}

tree::TerminalNode* JavaParser::ArrayInitializerContext::RBRACE() {
  return getToken(JavaParser::RBRACE, 0);
}

std::vector<JavaParser::VariableInitializerContext *> JavaParser::ArrayInitializerContext::variableInitializer() {
  return getRuleContexts<JavaParser::VariableInitializerContext>();
}

JavaParser::VariableInitializerContext* JavaParser::ArrayInitializerContext::variableInitializer(size_t i) {
  return getRuleContext<JavaParser::VariableInitializerContext>(i);
}

std::vector<tree::TerminalNode *> JavaParser::ArrayInitializerContext::COMMA() {
  return getTokens(JavaParser::COMMA);
}

tree::TerminalNode* JavaParser::ArrayInitializerContext::COMMA(size_t i) {
  return getToken(JavaParser::COMMA, i);
}


size_t JavaParser::ArrayInitializerContext::getRuleIndex() const {
  return JavaParser::RuleArrayInitializer;
}

void JavaParser::ArrayInitializerContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrayInitializer(this);
}

void JavaParser::ArrayInitializerContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrayInitializer(this);
}

JavaParser::ArrayInitializerContext* JavaParser::arrayInitializer() {
  ArrayInitializerContext *_localctx = _tracker.createInstance<ArrayInitializerContext>(_ctx, getState());
  enterRule(_localctx, 76, JavaParser::RuleArrayInitializer);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(579);
    match(JavaParser::LBRACE);
    setState(591);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << JavaParser::BOOLEAN)
      | (1ULL << JavaParser::BYTE)
      | (1ULL << JavaParser::CHAR)
      | (1ULL << JavaParser::DOUBLE)
      | (1ULL << JavaParser::FLOAT)
      | (1ULL << JavaParser::INT)
      | (1ULL << JavaParser::LONG)
      | (1ULL << JavaParser::NEW)
      | (1ULL << JavaParser::SHORT)
      | (1ULL << JavaParser::SUPER)
      | (1ULL << JavaParser::THIS)
      | (1ULL << JavaParser::VOID)
      | (1ULL << JavaParser::DECIMAL_LITERAL)
      | (1ULL << JavaParser::HEX_LITERAL)
      | (1ULL << JavaParser::OCT_LITERAL)
      | (1ULL << JavaParser::BINARY_LITERAL)
      | (1ULL << JavaParser::FLOAT_LITERAL)
      | (1ULL << JavaParser::HEX_FLOAT_LITERAL)
      | (1ULL << JavaParser::BOOL_LITERAL)
      | (1ULL << JavaParser::CHAR_LITERAL)
      | (1ULL << JavaParser::STRING_LITERAL)
      | (1ULL << JavaParser::NULL_LITERAL)
      | (1ULL << JavaParser::LPAREN)
      | (1ULL << JavaParser::LBRACE))) != 0) || ((((_la - 72) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 72)) & ((1ULL << (JavaParser::LT - 72))
      | (1ULL << (JavaParser::BANG - 72))
      | (1ULL << (JavaParser::TILDE - 72))
      | (1ULL << (JavaParser::INC - 72))
      | (1ULL << (JavaParser::DEC - 72))
      | (1ULL << (JavaParser::ADD - 72))
      | (1ULL << (JavaParser::SUB - 72))
      | (1ULL << (JavaParser::AT - 72))
      | (1ULL << (JavaParser::IDENTIFIER - 72)))) != 0)) {
      setState(580);
      variableInitializer();
      setState(585);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 56, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(581);
          match(JavaParser::COMMA);
          setState(582);
          variableInitializer(); 
        }
        setState(587);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 56, _ctx);
      }
      setState(589);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == JavaParser::COMMA) {
        setState(588);
        match(JavaParser::COMMA);
      }
    }
    setState(593);
    match(JavaParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ClassOrInterfaceTypeContext ------------------------------------------------------------------

JavaParser::ClassOrInterfaceTypeContext::ClassOrInterfaceTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> JavaParser::ClassOrInterfaceTypeContext::IDENTIFIER() {
  return getTokens(JavaParser::IDENTIFIER);
}

tree::TerminalNode* JavaParser::ClassOrInterfaceTypeContext::IDENTIFIER(size_t i) {
  return getToken(JavaParser::IDENTIFIER, i);
}

std::vector<JavaParser::TypeArgumentsContext *> JavaParser::ClassOrInterfaceTypeContext::typeArguments() {
  return getRuleContexts<JavaParser::TypeArgumentsContext>();
}

JavaParser::TypeArgumentsContext* JavaParser::ClassOrInterfaceTypeContext::typeArguments(size_t i) {
  return getRuleContext<JavaParser::TypeArgumentsContext>(i);
}

std::vector<tree::TerminalNode *> JavaParser::ClassOrInterfaceTypeContext::DOT() {
  return getTokens(JavaParser::DOT);
}

tree::TerminalNode* JavaParser::ClassOrInterfaceTypeContext::DOT(size_t i) {
  return getToken(JavaParser::DOT, i);
}


size_t JavaParser::ClassOrInterfaceTypeContext::getRuleIndex() const {
  return JavaParser::RuleClassOrInterfaceType;
}

void JavaParser::ClassOrInterfaceTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterClassOrInterfaceType(this);
}

void JavaParser::ClassOrInterfaceTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitClassOrInterfaceType(this);
}

JavaParser::ClassOrInterfaceTypeContext* JavaParser::classOrInterfaceType() {
  ClassOrInterfaceTypeContext *_localctx = _tracker.createInstance<ClassOrInterfaceTypeContext>(_ctx, getState());
  enterRule(_localctx, 78, JavaParser::RuleClassOrInterfaceType);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(595);
    match(JavaParser::IDENTIFIER);
    setState(597);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 59, _ctx)) {
    case 1: {
      setState(596);
      typeArguments();
      break;
    }

    }
    setState(606);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 61, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(599);
        match(JavaParser::DOT);
        setState(600);
        match(JavaParser::IDENTIFIER);
        setState(602);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 60, _ctx)) {
        case 1: {
          setState(601);
          typeArguments();
          break;
        }

        } 
      }
      setState(608);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 61, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeArgumentContext ------------------------------------------------------------------

JavaParser::TypeArgumentContext::TypeArgumentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaParser::TypeTypeContext* JavaParser::TypeArgumentContext::typeType() {
  return getRuleContext<JavaParser::TypeTypeContext>(0);
}

tree::TerminalNode* JavaParser::TypeArgumentContext::QUESTION() {
  return getToken(JavaParser::QUESTION, 0);
}

tree::TerminalNode* JavaParser::TypeArgumentContext::EXTENDS() {
  return getToken(JavaParser::EXTENDS, 0);
}

tree::TerminalNode* JavaParser::TypeArgumentContext::SUPER() {
  return getToken(JavaParser::SUPER, 0);
}


size_t JavaParser::TypeArgumentContext::getRuleIndex() const {
  return JavaParser::RuleTypeArgument;
}

void JavaParser::TypeArgumentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeArgument(this);
}

void JavaParser::TypeArgumentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeArgument(this);
}

JavaParser::TypeArgumentContext* JavaParser::typeArgument() {
  TypeArgumentContext *_localctx = _tracker.createInstance<TypeArgumentContext>(_ctx, getState());
  enterRule(_localctx, 80, JavaParser::RuleTypeArgument);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(615);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaParser::BOOLEAN:
      case JavaParser::BYTE:
      case JavaParser::CHAR:
      case JavaParser::DOUBLE:
      case JavaParser::FLOAT:
      case JavaParser::INT:
      case JavaParser::LONG:
      case JavaParser::SHORT:
      case JavaParser::AT:
      case JavaParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(609);
        typeType();
        break;
      }

      case JavaParser::QUESTION: {
        enterOuterAlt(_localctx, 2);
        setState(610);
        match(JavaParser::QUESTION);
        setState(613);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == JavaParser::EXTENDS

        || _la == JavaParser::SUPER) {
          setState(611);
          _la = _input->LA(1);
          if (!(_la == JavaParser::EXTENDS

          || _la == JavaParser::SUPER)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(612);
          typeType();
        }
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- QualifiedNameListContext ------------------------------------------------------------------

JavaParser::QualifiedNameListContext::QualifiedNameListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<JavaParser::QualifiedNameContext *> JavaParser::QualifiedNameListContext::qualifiedName() {
  return getRuleContexts<JavaParser::QualifiedNameContext>();
}

JavaParser::QualifiedNameContext* JavaParser::QualifiedNameListContext::qualifiedName(size_t i) {
  return getRuleContext<JavaParser::QualifiedNameContext>(i);
}

std::vector<tree::TerminalNode *> JavaParser::QualifiedNameListContext::COMMA() {
  return getTokens(JavaParser::COMMA);
}

tree::TerminalNode* JavaParser::QualifiedNameListContext::COMMA(size_t i) {
  return getToken(JavaParser::COMMA, i);
}


size_t JavaParser::QualifiedNameListContext::getRuleIndex() const {
  return JavaParser::RuleQualifiedNameList;
}

void JavaParser::QualifiedNameListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterQualifiedNameList(this);
}

void JavaParser::QualifiedNameListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitQualifiedNameList(this);
}

JavaParser::QualifiedNameListContext* JavaParser::qualifiedNameList() {
  QualifiedNameListContext *_localctx = _tracker.createInstance<QualifiedNameListContext>(_ctx, getState());
  enterRule(_localctx, 82, JavaParser::RuleQualifiedNameList);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(617);
    qualifiedName();
    setState(622);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == JavaParser::COMMA) {
      setState(618);
      match(JavaParser::COMMA);
      setState(619);
      qualifiedName();
      setState(624);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FormalParametersContext ------------------------------------------------------------------

JavaParser::FormalParametersContext::FormalParametersContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaParser::FormalParametersContext::LPAREN() {
  return getToken(JavaParser::LPAREN, 0);
}

tree::TerminalNode* JavaParser::FormalParametersContext::RPAREN() {
  return getToken(JavaParser::RPAREN, 0);
}

JavaParser::FormalParameterListContext* JavaParser::FormalParametersContext::formalParameterList() {
  return getRuleContext<JavaParser::FormalParameterListContext>(0);
}


size_t JavaParser::FormalParametersContext::getRuleIndex() const {
  return JavaParser::RuleFormalParameters;
}

void JavaParser::FormalParametersContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFormalParameters(this);
}

void JavaParser::FormalParametersContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFormalParameters(this);
}

JavaParser::FormalParametersContext* JavaParser::formalParameters() {
  FormalParametersContext *_localctx = _tracker.createInstance<FormalParametersContext>(_ctx, getState());
  enterRule(_localctx, 84, JavaParser::RuleFormalParameters);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(625);
    match(JavaParser::LPAREN);
    setState(627);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << JavaParser::BOOLEAN)
      | (1ULL << JavaParser::BYTE)
      | (1ULL << JavaParser::CHAR)
      | (1ULL << JavaParser::DOUBLE)
      | (1ULL << JavaParser::FINAL)
      | (1ULL << JavaParser::FLOAT)
      | (1ULL << JavaParser::INT)
      | (1ULL << JavaParser::LONG)
      | (1ULL << JavaParser::SHORT))) != 0) || _la == JavaParser::AT

    || _la == JavaParser::IDENTIFIER) {
      setState(626);
      formalParameterList();
    }
    setState(629);
    match(JavaParser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FormalParameterListContext ------------------------------------------------------------------

JavaParser::FormalParameterListContext::FormalParameterListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<JavaParser::FormalParameterContext *> JavaParser::FormalParameterListContext::formalParameter() {
  return getRuleContexts<JavaParser::FormalParameterContext>();
}

JavaParser::FormalParameterContext* JavaParser::FormalParameterListContext::formalParameter(size_t i) {
  return getRuleContext<JavaParser::FormalParameterContext>(i);
}

std::vector<tree::TerminalNode *> JavaParser::FormalParameterListContext::COMMA() {
  return getTokens(JavaParser::COMMA);
}

tree::TerminalNode* JavaParser::FormalParameterListContext::COMMA(size_t i) {
  return getToken(JavaParser::COMMA, i);
}

JavaParser::LastFormalParameterContext* JavaParser::FormalParameterListContext::lastFormalParameter() {
  return getRuleContext<JavaParser::LastFormalParameterContext>(0);
}


size_t JavaParser::FormalParameterListContext::getRuleIndex() const {
  return JavaParser::RuleFormalParameterList;
}

void JavaParser::FormalParameterListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFormalParameterList(this);
}

void JavaParser::FormalParameterListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFormalParameterList(this);
}

JavaParser::FormalParameterListContext* JavaParser::formalParameterList() {
  FormalParameterListContext *_localctx = _tracker.createInstance<FormalParameterListContext>(_ctx, getState());
  enterRule(_localctx, 86, JavaParser::RuleFormalParameterList);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    setState(644);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 68, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(631);
      formalParameter();
      setState(636);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 66, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(632);
          match(JavaParser::COMMA);
          setState(633);
          formalParameter(); 
        }
        setState(638);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 66, _ctx);
      }
      setState(641);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == JavaParser::COMMA) {
        setState(639);
        match(JavaParser::COMMA);
        setState(640);
        lastFormalParameter();
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(643);
      lastFormalParameter();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FormalParameterContext ------------------------------------------------------------------

JavaParser::FormalParameterContext::FormalParameterContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaParser::TypeTypeContext* JavaParser::FormalParameterContext::typeType() {
  return getRuleContext<JavaParser::TypeTypeContext>(0);
}

JavaParser::VariableDeclaratorIdContext* JavaParser::FormalParameterContext::variableDeclaratorId() {
  return getRuleContext<JavaParser::VariableDeclaratorIdContext>(0);
}

std::vector<JavaParser::VariableModifierContext *> JavaParser::FormalParameterContext::variableModifier() {
  return getRuleContexts<JavaParser::VariableModifierContext>();
}

JavaParser::VariableModifierContext* JavaParser::FormalParameterContext::variableModifier(size_t i) {
  return getRuleContext<JavaParser::VariableModifierContext>(i);
}


size_t JavaParser::FormalParameterContext::getRuleIndex() const {
  return JavaParser::RuleFormalParameter;
}

void JavaParser::FormalParameterContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFormalParameter(this);
}

void JavaParser::FormalParameterContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFormalParameter(this);
}

JavaParser::FormalParameterContext* JavaParser::formalParameter() {
  FormalParameterContext *_localctx = _tracker.createInstance<FormalParameterContext>(_ctx, getState());
  enterRule(_localctx, 88, JavaParser::RuleFormalParameter);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(649);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 69, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(646);
        variableModifier(); 
      }
      setState(651);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 69, _ctx);
    }
    setState(652);
    typeType();
    setState(653);
    variableDeclaratorId();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LastFormalParameterContext ------------------------------------------------------------------

JavaParser::LastFormalParameterContext::LastFormalParameterContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaParser::TypeTypeContext* JavaParser::LastFormalParameterContext::typeType() {
  return getRuleContext<JavaParser::TypeTypeContext>(0);
}

tree::TerminalNode* JavaParser::LastFormalParameterContext::ELLIPSIS() {
  return getToken(JavaParser::ELLIPSIS, 0);
}

JavaParser::VariableDeclaratorIdContext* JavaParser::LastFormalParameterContext::variableDeclaratorId() {
  return getRuleContext<JavaParser::VariableDeclaratorIdContext>(0);
}

std::vector<JavaParser::VariableModifierContext *> JavaParser::LastFormalParameterContext::variableModifier() {
  return getRuleContexts<JavaParser::VariableModifierContext>();
}

JavaParser::VariableModifierContext* JavaParser::LastFormalParameterContext::variableModifier(size_t i) {
  return getRuleContext<JavaParser::VariableModifierContext>(i);
}


size_t JavaParser::LastFormalParameterContext::getRuleIndex() const {
  return JavaParser::RuleLastFormalParameter;
}

void JavaParser::LastFormalParameterContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLastFormalParameter(this);
}

void JavaParser::LastFormalParameterContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLastFormalParameter(this);
}

JavaParser::LastFormalParameterContext* JavaParser::lastFormalParameter() {
  LastFormalParameterContext *_localctx = _tracker.createInstance<LastFormalParameterContext>(_ctx, getState());
  enterRule(_localctx, 90, JavaParser::RuleLastFormalParameter);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(658);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 70, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(655);
        variableModifier(); 
      }
      setState(660);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 70, _ctx);
    }
    setState(661);
    typeType();
    setState(662);
    match(JavaParser::ELLIPSIS);
    setState(663);
    variableDeclaratorId();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- QualifiedNameContext ------------------------------------------------------------------

JavaParser::QualifiedNameContext::QualifiedNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> JavaParser::QualifiedNameContext::IDENTIFIER() {
  return getTokens(JavaParser::IDENTIFIER);
}

tree::TerminalNode* JavaParser::QualifiedNameContext::IDENTIFIER(size_t i) {
  return getToken(JavaParser::IDENTIFIER, i);
}

std::vector<tree::TerminalNode *> JavaParser::QualifiedNameContext::DOT() {
  return getTokens(JavaParser::DOT);
}

tree::TerminalNode* JavaParser::QualifiedNameContext::DOT(size_t i) {
  return getToken(JavaParser::DOT, i);
}


size_t JavaParser::QualifiedNameContext::getRuleIndex() const {
  return JavaParser::RuleQualifiedName;
}

void JavaParser::QualifiedNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterQualifiedName(this);
}

void JavaParser::QualifiedNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitQualifiedName(this);
}

JavaParser::QualifiedNameContext* JavaParser::qualifiedName() {
  QualifiedNameContext *_localctx = _tracker.createInstance<QualifiedNameContext>(_ctx, getState());
  enterRule(_localctx, 92, JavaParser::RuleQualifiedName);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(665);
    match(JavaParser::IDENTIFIER);
    setState(670);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 71, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(666);
        match(JavaParser::DOT);
        setState(667);
        match(JavaParser::IDENTIFIER); 
      }
      setState(672);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 71, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LiteralContext ------------------------------------------------------------------

JavaParser::LiteralContext::LiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaParser::IntegerLiteralContext* JavaParser::LiteralContext::integerLiteral() {
  return getRuleContext<JavaParser::IntegerLiteralContext>(0);
}

JavaParser::FloatLiteralContext* JavaParser::LiteralContext::floatLiteral() {
  return getRuleContext<JavaParser::FloatLiteralContext>(0);
}

tree::TerminalNode* JavaParser::LiteralContext::CHAR_LITERAL() {
  return getToken(JavaParser::CHAR_LITERAL, 0);
}

tree::TerminalNode* JavaParser::LiteralContext::STRING_LITERAL() {
  return getToken(JavaParser::STRING_LITERAL, 0);
}

tree::TerminalNode* JavaParser::LiteralContext::BOOL_LITERAL() {
  return getToken(JavaParser::BOOL_LITERAL, 0);
}

tree::TerminalNode* JavaParser::LiteralContext::NULL_LITERAL() {
  return getToken(JavaParser::NULL_LITERAL, 0);
}


size_t JavaParser::LiteralContext::getRuleIndex() const {
  return JavaParser::RuleLiteral;
}

void JavaParser::LiteralContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLiteral(this);
}

void JavaParser::LiteralContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLiteral(this);
}

JavaParser::LiteralContext* JavaParser::literal() {
  LiteralContext *_localctx = _tracker.createInstance<LiteralContext>(_ctx, getState());
  enterRule(_localctx, 94, JavaParser::RuleLiteral);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(679);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaParser::DECIMAL_LITERAL:
      case JavaParser::HEX_LITERAL:
      case JavaParser::OCT_LITERAL:
      case JavaParser::BINARY_LITERAL: {
        enterOuterAlt(_localctx, 1);
        setState(673);
        integerLiteral();
        break;
      }

      case JavaParser::FLOAT_LITERAL:
      case JavaParser::HEX_FLOAT_LITERAL: {
        enterOuterAlt(_localctx, 2);
        setState(674);
        floatLiteral();
        break;
      }

      case JavaParser::CHAR_LITERAL: {
        enterOuterAlt(_localctx, 3);
        setState(675);
        match(JavaParser::CHAR_LITERAL);
        break;
      }

      case JavaParser::STRING_LITERAL: {
        enterOuterAlt(_localctx, 4);
        setState(676);
        match(JavaParser::STRING_LITERAL);
        break;
      }

      case JavaParser::BOOL_LITERAL: {
        enterOuterAlt(_localctx, 5);
        setState(677);
        match(JavaParser::BOOL_LITERAL);
        break;
      }

      case JavaParser::NULL_LITERAL: {
        enterOuterAlt(_localctx, 6);
        setState(678);
        match(JavaParser::NULL_LITERAL);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IntegerLiteralContext ------------------------------------------------------------------

JavaParser::IntegerLiteralContext::IntegerLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaParser::IntegerLiteralContext::DECIMAL_LITERAL() {
  return getToken(JavaParser::DECIMAL_LITERAL, 0);
}

tree::TerminalNode* JavaParser::IntegerLiteralContext::HEX_LITERAL() {
  return getToken(JavaParser::HEX_LITERAL, 0);
}

tree::TerminalNode* JavaParser::IntegerLiteralContext::OCT_LITERAL() {
  return getToken(JavaParser::OCT_LITERAL, 0);
}

tree::TerminalNode* JavaParser::IntegerLiteralContext::BINARY_LITERAL() {
  return getToken(JavaParser::BINARY_LITERAL, 0);
}


size_t JavaParser::IntegerLiteralContext::getRuleIndex() const {
  return JavaParser::RuleIntegerLiteral;
}

void JavaParser::IntegerLiteralContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIntegerLiteral(this);
}

void JavaParser::IntegerLiteralContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIntegerLiteral(this);
}

JavaParser::IntegerLiteralContext* JavaParser::integerLiteral() {
  IntegerLiteralContext *_localctx = _tracker.createInstance<IntegerLiteralContext>(_ctx, getState());
  enterRule(_localctx, 96, JavaParser::RuleIntegerLiteral);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(681);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << JavaParser::DECIMAL_LITERAL)
      | (1ULL << JavaParser::HEX_LITERAL)
      | (1ULL << JavaParser::OCT_LITERAL)
      | (1ULL << JavaParser::BINARY_LITERAL))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FloatLiteralContext ------------------------------------------------------------------

JavaParser::FloatLiteralContext::FloatLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaParser::FloatLiteralContext::FLOAT_LITERAL() {
  return getToken(JavaParser::FLOAT_LITERAL, 0);
}

tree::TerminalNode* JavaParser::FloatLiteralContext::HEX_FLOAT_LITERAL() {
  return getToken(JavaParser::HEX_FLOAT_LITERAL, 0);
}


size_t JavaParser::FloatLiteralContext::getRuleIndex() const {
  return JavaParser::RuleFloatLiteral;
}

void JavaParser::FloatLiteralContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFloatLiteral(this);
}

void JavaParser::FloatLiteralContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFloatLiteral(this);
}

JavaParser::FloatLiteralContext* JavaParser::floatLiteral() {
  FloatLiteralContext *_localctx = _tracker.createInstance<FloatLiteralContext>(_ctx, getState());
  enterRule(_localctx, 98, JavaParser::RuleFloatLiteral);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(683);
    _la = _input->LA(1);
    if (!(_la == JavaParser::FLOAT_LITERAL

    || _la == JavaParser::HEX_FLOAT_LITERAL)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AnnotationContext ------------------------------------------------------------------

JavaParser::AnnotationContext::AnnotationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaParser::AnnotationContext::AT() {
  return getToken(JavaParser::AT, 0);
}

JavaParser::QualifiedNameContext* JavaParser::AnnotationContext::qualifiedName() {
  return getRuleContext<JavaParser::QualifiedNameContext>(0);
}

tree::TerminalNode* JavaParser::AnnotationContext::LPAREN() {
  return getToken(JavaParser::LPAREN, 0);
}

tree::TerminalNode* JavaParser::AnnotationContext::RPAREN() {
  return getToken(JavaParser::RPAREN, 0);
}

JavaParser::ElementValuePairsContext* JavaParser::AnnotationContext::elementValuePairs() {
  return getRuleContext<JavaParser::ElementValuePairsContext>(0);
}

JavaParser::ElementValueContext* JavaParser::AnnotationContext::elementValue() {
  return getRuleContext<JavaParser::ElementValueContext>(0);
}


size_t JavaParser::AnnotationContext::getRuleIndex() const {
  return JavaParser::RuleAnnotation;
}

void JavaParser::AnnotationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAnnotation(this);
}

void JavaParser::AnnotationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAnnotation(this);
}

JavaParser::AnnotationContext* JavaParser::annotation() {
  AnnotationContext *_localctx = _tracker.createInstance<AnnotationContext>(_ctx, getState());
  enterRule(_localctx, 100, JavaParser::RuleAnnotation);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(685);
    match(JavaParser::AT);
    setState(686);
    qualifiedName();
    setState(693);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaParser::LPAREN) {
      setState(687);
      match(JavaParser::LPAREN);
      setState(690);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 73, _ctx)) {
      case 1: {
        setState(688);
        elementValuePairs();
        break;
      }

      case 2: {
        setState(689);
        elementValue();
        break;
      }

      }
      setState(692);
      match(JavaParser::RPAREN);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ElementValuePairsContext ------------------------------------------------------------------

JavaParser::ElementValuePairsContext::ElementValuePairsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<JavaParser::ElementValuePairContext *> JavaParser::ElementValuePairsContext::elementValuePair() {
  return getRuleContexts<JavaParser::ElementValuePairContext>();
}

JavaParser::ElementValuePairContext* JavaParser::ElementValuePairsContext::elementValuePair(size_t i) {
  return getRuleContext<JavaParser::ElementValuePairContext>(i);
}

std::vector<tree::TerminalNode *> JavaParser::ElementValuePairsContext::COMMA() {
  return getTokens(JavaParser::COMMA);
}

tree::TerminalNode* JavaParser::ElementValuePairsContext::COMMA(size_t i) {
  return getToken(JavaParser::COMMA, i);
}


size_t JavaParser::ElementValuePairsContext::getRuleIndex() const {
  return JavaParser::RuleElementValuePairs;
}

void JavaParser::ElementValuePairsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterElementValuePairs(this);
}

void JavaParser::ElementValuePairsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitElementValuePairs(this);
}

JavaParser::ElementValuePairsContext* JavaParser::elementValuePairs() {
  ElementValuePairsContext *_localctx = _tracker.createInstance<ElementValuePairsContext>(_ctx, getState());
  enterRule(_localctx, 102, JavaParser::RuleElementValuePairs);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(695);
    elementValuePair();
    setState(700);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == JavaParser::COMMA) {
      setState(696);
      match(JavaParser::COMMA);
      setState(697);
      elementValuePair();
      setState(702);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ElementValuePairContext ------------------------------------------------------------------

JavaParser::ElementValuePairContext::ElementValuePairContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaParser::ElementValuePairContext::IDENTIFIER() {
  return getToken(JavaParser::IDENTIFIER, 0);
}

tree::TerminalNode* JavaParser::ElementValuePairContext::ASSIGN() {
  return getToken(JavaParser::ASSIGN, 0);
}

JavaParser::ElementValueContext* JavaParser::ElementValuePairContext::elementValue() {
  return getRuleContext<JavaParser::ElementValueContext>(0);
}


size_t JavaParser::ElementValuePairContext::getRuleIndex() const {
  return JavaParser::RuleElementValuePair;
}

void JavaParser::ElementValuePairContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterElementValuePair(this);
}

void JavaParser::ElementValuePairContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitElementValuePair(this);
}

JavaParser::ElementValuePairContext* JavaParser::elementValuePair() {
  ElementValuePairContext *_localctx = _tracker.createInstance<ElementValuePairContext>(_ctx, getState());
  enterRule(_localctx, 104, JavaParser::RuleElementValuePair);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(703);
    match(JavaParser::IDENTIFIER);
    setState(704);
    match(JavaParser::ASSIGN);
    setState(705);
    elementValue();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ElementValueContext ------------------------------------------------------------------

JavaParser::ElementValueContext::ElementValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaParser::ExpressionContext* JavaParser::ElementValueContext::expression() {
  return getRuleContext<JavaParser::ExpressionContext>(0);
}

JavaParser::AnnotationContext* JavaParser::ElementValueContext::annotation() {
  return getRuleContext<JavaParser::AnnotationContext>(0);
}

JavaParser::ElementValueArrayInitializerContext* JavaParser::ElementValueContext::elementValueArrayInitializer() {
  return getRuleContext<JavaParser::ElementValueArrayInitializerContext>(0);
}


size_t JavaParser::ElementValueContext::getRuleIndex() const {
  return JavaParser::RuleElementValue;
}

void JavaParser::ElementValueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterElementValue(this);
}

void JavaParser::ElementValueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitElementValue(this);
}

JavaParser::ElementValueContext* JavaParser::elementValue() {
  ElementValueContext *_localctx = _tracker.createInstance<ElementValueContext>(_ctx, getState());
  enterRule(_localctx, 106, JavaParser::RuleElementValue);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(710);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 76, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(707);
      expression(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(708);
      annotation();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(709);
      elementValueArrayInitializer();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ElementValueArrayInitializerContext ------------------------------------------------------------------

JavaParser::ElementValueArrayInitializerContext::ElementValueArrayInitializerContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaParser::ElementValueArrayInitializerContext::LBRACE() {
  return getToken(JavaParser::LBRACE, 0);
}

tree::TerminalNode* JavaParser::ElementValueArrayInitializerContext::RBRACE() {
  return getToken(JavaParser::RBRACE, 0);
}

std::vector<JavaParser::ElementValueContext *> JavaParser::ElementValueArrayInitializerContext::elementValue() {
  return getRuleContexts<JavaParser::ElementValueContext>();
}

JavaParser::ElementValueContext* JavaParser::ElementValueArrayInitializerContext::elementValue(size_t i) {
  return getRuleContext<JavaParser::ElementValueContext>(i);
}

std::vector<tree::TerminalNode *> JavaParser::ElementValueArrayInitializerContext::COMMA() {
  return getTokens(JavaParser::COMMA);
}

tree::TerminalNode* JavaParser::ElementValueArrayInitializerContext::COMMA(size_t i) {
  return getToken(JavaParser::COMMA, i);
}


size_t JavaParser::ElementValueArrayInitializerContext::getRuleIndex() const {
  return JavaParser::RuleElementValueArrayInitializer;
}

void JavaParser::ElementValueArrayInitializerContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterElementValueArrayInitializer(this);
}

void JavaParser::ElementValueArrayInitializerContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitElementValueArrayInitializer(this);
}

JavaParser::ElementValueArrayInitializerContext* JavaParser::elementValueArrayInitializer() {
  ElementValueArrayInitializerContext *_localctx = _tracker.createInstance<ElementValueArrayInitializerContext>(_ctx, getState());
  enterRule(_localctx, 108, JavaParser::RuleElementValueArrayInitializer);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(712);
    match(JavaParser::LBRACE);
    setState(721);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << JavaParser::BOOLEAN)
      | (1ULL << JavaParser::BYTE)
      | (1ULL << JavaParser::CHAR)
      | (1ULL << JavaParser::DOUBLE)
      | (1ULL << JavaParser::FLOAT)
      | (1ULL << JavaParser::INT)
      | (1ULL << JavaParser::LONG)
      | (1ULL << JavaParser::NEW)
      | (1ULL << JavaParser::SHORT)
      | (1ULL << JavaParser::SUPER)
      | (1ULL << JavaParser::THIS)
      | (1ULL << JavaParser::VOID)
      | (1ULL << JavaParser::DECIMAL_LITERAL)
      | (1ULL << JavaParser::HEX_LITERAL)
      | (1ULL << JavaParser::OCT_LITERAL)
      | (1ULL << JavaParser::BINARY_LITERAL)
      | (1ULL << JavaParser::FLOAT_LITERAL)
      | (1ULL << JavaParser::HEX_FLOAT_LITERAL)
      | (1ULL << JavaParser::BOOL_LITERAL)
      | (1ULL << JavaParser::CHAR_LITERAL)
      | (1ULL << JavaParser::STRING_LITERAL)
      | (1ULL << JavaParser::NULL_LITERAL)
      | (1ULL << JavaParser::LPAREN)
      | (1ULL << JavaParser::LBRACE))) != 0) || ((((_la - 72) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 72)) & ((1ULL << (JavaParser::LT - 72))
      | (1ULL << (JavaParser::BANG - 72))
      | (1ULL << (JavaParser::TILDE - 72))
      | (1ULL << (JavaParser::INC - 72))
      | (1ULL << (JavaParser::DEC - 72))
      | (1ULL << (JavaParser::ADD - 72))
      | (1ULL << (JavaParser::SUB - 72))
      | (1ULL << (JavaParser::AT - 72))
      | (1ULL << (JavaParser::IDENTIFIER - 72)))) != 0)) {
      setState(713);
      elementValue();
      setState(718);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 77, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(714);
          match(JavaParser::COMMA);
          setState(715);
          elementValue(); 
        }
        setState(720);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 77, _ctx);
      }
    }
    setState(724);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaParser::COMMA) {
      setState(723);
      match(JavaParser::COMMA);
    }
    setState(726);
    match(JavaParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AnnotationTypeDeclarationContext ------------------------------------------------------------------

JavaParser::AnnotationTypeDeclarationContext::AnnotationTypeDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaParser::AnnotationTypeDeclarationContext::AT() {
  return getToken(JavaParser::AT, 0);
}

tree::TerminalNode* JavaParser::AnnotationTypeDeclarationContext::INTERFACE() {
  return getToken(JavaParser::INTERFACE, 0);
}

tree::TerminalNode* JavaParser::AnnotationTypeDeclarationContext::IDENTIFIER() {
  return getToken(JavaParser::IDENTIFIER, 0);
}

JavaParser::AnnotationTypeBodyContext* JavaParser::AnnotationTypeDeclarationContext::annotationTypeBody() {
  return getRuleContext<JavaParser::AnnotationTypeBodyContext>(0);
}


size_t JavaParser::AnnotationTypeDeclarationContext::getRuleIndex() const {
  return JavaParser::RuleAnnotationTypeDeclaration;
}

void JavaParser::AnnotationTypeDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAnnotationTypeDeclaration(this);
}

void JavaParser::AnnotationTypeDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAnnotationTypeDeclaration(this);
}

JavaParser::AnnotationTypeDeclarationContext* JavaParser::annotationTypeDeclaration() {
  AnnotationTypeDeclarationContext *_localctx = _tracker.createInstance<AnnotationTypeDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 110, JavaParser::RuleAnnotationTypeDeclaration);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(728);
    match(JavaParser::AT);
    setState(729);
    match(JavaParser::INTERFACE);
    setState(730);
    match(JavaParser::IDENTIFIER);
    setState(731);
    annotationTypeBody();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AnnotationTypeBodyContext ------------------------------------------------------------------

JavaParser::AnnotationTypeBodyContext::AnnotationTypeBodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaParser::AnnotationTypeBodyContext::LBRACE() {
  return getToken(JavaParser::LBRACE, 0);
}

tree::TerminalNode* JavaParser::AnnotationTypeBodyContext::RBRACE() {
  return getToken(JavaParser::RBRACE, 0);
}

std::vector<JavaParser::AnnotationTypeElementDeclarationContext *> JavaParser::AnnotationTypeBodyContext::annotationTypeElementDeclaration() {
  return getRuleContexts<JavaParser::AnnotationTypeElementDeclarationContext>();
}

JavaParser::AnnotationTypeElementDeclarationContext* JavaParser::AnnotationTypeBodyContext::annotationTypeElementDeclaration(size_t i) {
  return getRuleContext<JavaParser::AnnotationTypeElementDeclarationContext>(i);
}


size_t JavaParser::AnnotationTypeBodyContext::getRuleIndex() const {
  return JavaParser::RuleAnnotationTypeBody;
}

void JavaParser::AnnotationTypeBodyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAnnotationTypeBody(this);
}

void JavaParser::AnnotationTypeBodyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAnnotationTypeBody(this);
}

JavaParser::AnnotationTypeBodyContext* JavaParser::annotationTypeBody() {
  AnnotationTypeBodyContext *_localctx = _tracker.createInstance<AnnotationTypeBodyContext>(_ctx, getState());
  enterRule(_localctx, 112, JavaParser::RuleAnnotationTypeBody);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(733);
    match(JavaParser::LBRACE);
    setState(737);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << JavaParser::ABSTRACT)
      | (1ULL << JavaParser::BOOLEAN)
      | (1ULL << JavaParser::BYTE)
      | (1ULL << JavaParser::CHAR)
      | (1ULL << JavaParser::CLASS)
      | (1ULL << JavaParser::DOUBLE)
      | (1ULL << JavaParser::ENUM)
      | (1ULL << JavaParser::FINAL)
      | (1ULL << JavaParser::FLOAT)
      | (1ULL << JavaParser::INT)
      | (1ULL << JavaParser::INTERFACE)
      | (1ULL << JavaParser::LONG)
      | (1ULL << JavaParser::NATIVE)
      | (1ULL << JavaParser::PRIVATE)
      | (1ULL << JavaParser::PROTECTED)
      | (1ULL << JavaParser::PUBLIC)
      | (1ULL << JavaParser::SHORT)
      | (1ULL << JavaParser::STATIC)
      | (1ULL << JavaParser::STRICTFP)
      | (1ULL << JavaParser::SYNCHRONIZED)
      | (1ULL << JavaParser::TRANSIENT)
      | (1ULL << JavaParser::VOLATILE))) != 0) || ((((_la - 67) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 67)) & ((1ULL << (JavaParser::SEMI - 67))
      | (1ULL << (JavaParser::AT - 67))
      | (1ULL << (JavaParser::IDENTIFIER - 67)))) != 0)) {
      setState(734);
      annotationTypeElementDeclaration();
      setState(739);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(740);
    match(JavaParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AnnotationTypeElementDeclarationContext ------------------------------------------------------------------

JavaParser::AnnotationTypeElementDeclarationContext::AnnotationTypeElementDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaParser::AnnotationTypeElementRestContext* JavaParser::AnnotationTypeElementDeclarationContext::annotationTypeElementRest() {
  return getRuleContext<JavaParser::AnnotationTypeElementRestContext>(0);
}

std::vector<JavaParser::ModifierContext *> JavaParser::AnnotationTypeElementDeclarationContext::modifier() {
  return getRuleContexts<JavaParser::ModifierContext>();
}

JavaParser::ModifierContext* JavaParser::AnnotationTypeElementDeclarationContext::modifier(size_t i) {
  return getRuleContext<JavaParser::ModifierContext>(i);
}

tree::TerminalNode* JavaParser::AnnotationTypeElementDeclarationContext::SEMI() {
  return getToken(JavaParser::SEMI, 0);
}


size_t JavaParser::AnnotationTypeElementDeclarationContext::getRuleIndex() const {
  return JavaParser::RuleAnnotationTypeElementDeclaration;
}

void JavaParser::AnnotationTypeElementDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAnnotationTypeElementDeclaration(this);
}

void JavaParser::AnnotationTypeElementDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAnnotationTypeElementDeclaration(this);
}

JavaParser::AnnotationTypeElementDeclarationContext* JavaParser::annotationTypeElementDeclaration() {
  AnnotationTypeElementDeclarationContext *_localctx = _tracker.createInstance<AnnotationTypeElementDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 114, JavaParser::RuleAnnotationTypeElementDeclaration);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    setState(750);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaParser::ABSTRACT:
      case JavaParser::BOOLEAN:
      case JavaParser::BYTE:
      case JavaParser::CHAR:
      case JavaParser::CLASS:
      case JavaParser::DOUBLE:
      case JavaParser::ENUM:
      case JavaParser::FINAL:
      case JavaParser::FLOAT:
      case JavaParser::INT:
      case JavaParser::INTERFACE:
      case JavaParser::LONG:
      case JavaParser::NATIVE:
      case JavaParser::PRIVATE:
      case JavaParser::PROTECTED:
      case JavaParser::PUBLIC:
      case JavaParser::SHORT:
      case JavaParser::STATIC:
      case JavaParser::STRICTFP:
      case JavaParser::SYNCHRONIZED:
      case JavaParser::TRANSIENT:
      case JavaParser::VOLATILE:
      case JavaParser::AT:
      case JavaParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(745);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 81, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
          if (alt == 1) {
            setState(742);
            modifier(); 
          }
          setState(747);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 81, _ctx);
        }
        setState(748);
        annotationTypeElementRest();
        break;
      }

      case JavaParser::SEMI: {
        enterOuterAlt(_localctx, 2);
        setState(749);
        match(JavaParser::SEMI);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AnnotationTypeElementRestContext ------------------------------------------------------------------

JavaParser::AnnotationTypeElementRestContext::AnnotationTypeElementRestContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaParser::TypeTypeContext* JavaParser::AnnotationTypeElementRestContext::typeType() {
  return getRuleContext<JavaParser::TypeTypeContext>(0);
}

JavaParser::AnnotationMethodOrConstantRestContext* JavaParser::AnnotationTypeElementRestContext::annotationMethodOrConstantRest() {
  return getRuleContext<JavaParser::AnnotationMethodOrConstantRestContext>(0);
}

tree::TerminalNode* JavaParser::AnnotationTypeElementRestContext::SEMI() {
  return getToken(JavaParser::SEMI, 0);
}

JavaParser::ClassDeclarationContext* JavaParser::AnnotationTypeElementRestContext::classDeclaration() {
  return getRuleContext<JavaParser::ClassDeclarationContext>(0);
}

JavaParser::InterfaceDeclarationContext* JavaParser::AnnotationTypeElementRestContext::interfaceDeclaration() {
  return getRuleContext<JavaParser::InterfaceDeclarationContext>(0);
}

JavaParser::EnumDeclarationContext* JavaParser::AnnotationTypeElementRestContext::enumDeclaration() {
  return getRuleContext<JavaParser::EnumDeclarationContext>(0);
}

JavaParser::AnnotationTypeDeclarationContext* JavaParser::AnnotationTypeElementRestContext::annotationTypeDeclaration() {
  return getRuleContext<JavaParser::AnnotationTypeDeclarationContext>(0);
}


size_t JavaParser::AnnotationTypeElementRestContext::getRuleIndex() const {
  return JavaParser::RuleAnnotationTypeElementRest;
}

void JavaParser::AnnotationTypeElementRestContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAnnotationTypeElementRest(this);
}

void JavaParser::AnnotationTypeElementRestContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAnnotationTypeElementRest(this);
}

JavaParser::AnnotationTypeElementRestContext* JavaParser::annotationTypeElementRest() {
  AnnotationTypeElementRestContext *_localctx = _tracker.createInstance<AnnotationTypeElementRestContext>(_ctx, getState());
  enterRule(_localctx, 116, JavaParser::RuleAnnotationTypeElementRest);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(772);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 87, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(752);
      typeType();
      setState(753);
      annotationMethodOrConstantRest();
      setState(754);
      match(JavaParser::SEMI);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(756);
      classDeclaration();
      setState(758);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 83, _ctx)) {
      case 1: {
        setState(757);
        match(JavaParser::SEMI);
        break;
      }

      }
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(760);
      interfaceDeclaration();
      setState(762);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 84, _ctx)) {
      case 1: {
        setState(761);
        match(JavaParser::SEMI);
        break;
      }

      }
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(764);
      enumDeclaration();
      setState(766);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 85, _ctx)) {
      case 1: {
        setState(765);
        match(JavaParser::SEMI);
        break;
      }

      }
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(768);
      annotationTypeDeclaration();
      setState(770);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 86, _ctx)) {
      case 1: {
        setState(769);
        match(JavaParser::SEMI);
        break;
      }

      }
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AnnotationMethodOrConstantRestContext ------------------------------------------------------------------

JavaParser::AnnotationMethodOrConstantRestContext::AnnotationMethodOrConstantRestContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaParser::AnnotationMethodRestContext* JavaParser::AnnotationMethodOrConstantRestContext::annotationMethodRest() {
  return getRuleContext<JavaParser::AnnotationMethodRestContext>(0);
}

JavaParser::AnnotationConstantRestContext* JavaParser::AnnotationMethodOrConstantRestContext::annotationConstantRest() {
  return getRuleContext<JavaParser::AnnotationConstantRestContext>(0);
}


size_t JavaParser::AnnotationMethodOrConstantRestContext::getRuleIndex() const {
  return JavaParser::RuleAnnotationMethodOrConstantRest;
}

void JavaParser::AnnotationMethodOrConstantRestContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAnnotationMethodOrConstantRest(this);
}

void JavaParser::AnnotationMethodOrConstantRestContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAnnotationMethodOrConstantRest(this);
}

JavaParser::AnnotationMethodOrConstantRestContext* JavaParser::annotationMethodOrConstantRest() {
  AnnotationMethodOrConstantRestContext *_localctx = _tracker.createInstance<AnnotationMethodOrConstantRestContext>(_ctx, getState());
  enterRule(_localctx, 118, JavaParser::RuleAnnotationMethodOrConstantRest);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(776);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 88, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(774);
      annotationMethodRest();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(775);
      annotationConstantRest();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AnnotationMethodRestContext ------------------------------------------------------------------

JavaParser::AnnotationMethodRestContext::AnnotationMethodRestContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaParser::AnnotationMethodRestContext::IDENTIFIER() {
  return getToken(JavaParser::IDENTIFIER, 0);
}

tree::TerminalNode* JavaParser::AnnotationMethodRestContext::LPAREN() {
  return getToken(JavaParser::LPAREN, 0);
}

tree::TerminalNode* JavaParser::AnnotationMethodRestContext::RPAREN() {
  return getToken(JavaParser::RPAREN, 0);
}

JavaParser::DefaultValueContext* JavaParser::AnnotationMethodRestContext::defaultValue() {
  return getRuleContext<JavaParser::DefaultValueContext>(0);
}


size_t JavaParser::AnnotationMethodRestContext::getRuleIndex() const {
  return JavaParser::RuleAnnotationMethodRest;
}

void JavaParser::AnnotationMethodRestContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAnnotationMethodRest(this);
}

void JavaParser::AnnotationMethodRestContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAnnotationMethodRest(this);
}

JavaParser::AnnotationMethodRestContext* JavaParser::annotationMethodRest() {
  AnnotationMethodRestContext *_localctx = _tracker.createInstance<AnnotationMethodRestContext>(_ctx, getState());
  enterRule(_localctx, 120, JavaParser::RuleAnnotationMethodRest);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(778);
    match(JavaParser::IDENTIFIER);
    setState(779);
    match(JavaParser::LPAREN);
    setState(780);
    match(JavaParser::RPAREN);
    setState(782);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaParser::DEFAULT) {
      setState(781);
      defaultValue();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AnnotationConstantRestContext ------------------------------------------------------------------

JavaParser::AnnotationConstantRestContext::AnnotationConstantRestContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaParser::VariableDeclaratorsContext* JavaParser::AnnotationConstantRestContext::variableDeclarators() {
  return getRuleContext<JavaParser::VariableDeclaratorsContext>(0);
}


size_t JavaParser::AnnotationConstantRestContext::getRuleIndex() const {
  return JavaParser::RuleAnnotationConstantRest;
}

void JavaParser::AnnotationConstantRestContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAnnotationConstantRest(this);
}

void JavaParser::AnnotationConstantRestContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAnnotationConstantRest(this);
}

JavaParser::AnnotationConstantRestContext* JavaParser::annotationConstantRest() {
  AnnotationConstantRestContext *_localctx = _tracker.createInstance<AnnotationConstantRestContext>(_ctx, getState());
  enterRule(_localctx, 122, JavaParser::RuleAnnotationConstantRest);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(784);
    variableDeclarators();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DefaultValueContext ------------------------------------------------------------------

JavaParser::DefaultValueContext::DefaultValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaParser::DefaultValueContext::DEFAULT() {
  return getToken(JavaParser::DEFAULT, 0);
}

JavaParser::ElementValueContext* JavaParser::DefaultValueContext::elementValue() {
  return getRuleContext<JavaParser::ElementValueContext>(0);
}


size_t JavaParser::DefaultValueContext::getRuleIndex() const {
  return JavaParser::RuleDefaultValue;
}

void JavaParser::DefaultValueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDefaultValue(this);
}

void JavaParser::DefaultValueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDefaultValue(this);
}

JavaParser::DefaultValueContext* JavaParser::defaultValue() {
  DefaultValueContext *_localctx = _tracker.createInstance<DefaultValueContext>(_ctx, getState());
  enterRule(_localctx, 124, JavaParser::RuleDefaultValue);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(786);
    match(JavaParser::DEFAULT);
    setState(787);
    elementValue();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockContext ------------------------------------------------------------------

JavaParser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaParser::BlockContext::LBRACE() {
  return getToken(JavaParser::LBRACE, 0);
}

tree::TerminalNode* JavaParser::BlockContext::RBRACE() {
  return getToken(JavaParser::RBRACE, 0);
}

std::vector<JavaParser::BlockStatementContext *> JavaParser::BlockContext::blockStatement() {
  return getRuleContexts<JavaParser::BlockStatementContext>();
}

JavaParser::BlockStatementContext* JavaParser::BlockContext::blockStatement(size_t i) {
  return getRuleContext<JavaParser::BlockStatementContext>(i);
}


size_t JavaParser::BlockContext::getRuleIndex() const {
  return JavaParser::RuleBlock;
}

void JavaParser::BlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBlock(this);
}

void JavaParser::BlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBlock(this);
}

JavaParser::BlockContext* JavaParser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 126, JavaParser::RuleBlock);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(789);
    match(JavaParser::LBRACE);
    setState(793);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << JavaParser::ABSTRACT)
      | (1ULL << JavaParser::ASSERT)
      | (1ULL << JavaParser::BOOLEAN)
      | (1ULL << JavaParser::BREAK)
      | (1ULL << JavaParser::BYTE)
      | (1ULL << JavaParser::CHAR)
      | (1ULL << JavaParser::CLASS)
      | (1ULL << JavaParser::CONTINUE)
      | (1ULL << JavaParser::DO)
      | (1ULL << JavaParser::DOUBLE)
      | (1ULL << JavaParser::FINAL)
      | (1ULL << JavaParser::FLOAT)
      | (1ULL << JavaParser::FOR)
      | (1ULL << JavaParser::IF)
      | (1ULL << JavaParser::INT)
      | (1ULL << JavaParser::INTERFACE)
      | (1ULL << JavaParser::LONG)
      | (1ULL << JavaParser::NEW)
      | (1ULL << JavaParser::PRIVATE)
      | (1ULL << JavaParser::PROTECTED)
      | (1ULL << JavaParser::PUBLIC)
      | (1ULL << JavaParser::RETURN)
      | (1ULL << JavaParser::SHORT)
      | (1ULL << JavaParser::STATIC)
      | (1ULL << JavaParser::STRICTFP)
      | (1ULL << JavaParser::SUPER)
      | (1ULL << JavaParser::SWITCH)
      | (1ULL << JavaParser::SYNCHRONIZED)
      | (1ULL << JavaParser::THIS)
      | (1ULL << JavaParser::THROW)
      | (1ULL << JavaParser::TRY)
      | (1ULL << JavaParser::VOID)
      | (1ULL << JavaParser::WHILE)
      | (1ULL << JavaParser::DECIMAL_LITERAL)
      | (1ULL << JavaParser::HEX_LITERAL)
      | (1ULL << JavaParser::OCT_LITERAL)
      | (1ULL << JavaParser::BINARY_LITERAL)
      | (1ULL << JavaParser::FLOAT_LITERAL)
      | (1ULL << JavaParser::HEX_FLOAT_LITERAL)
      | (1ULL << JavaParser::BOOL_LITERAL)
      | (1ULL << JavaParser::CHAR_LITERAL)
      | (1ULL << JavaParser::STRING_LITERAL)
      | (1ULL << JavaParser::NULL_LITERAL)
      | (1ULL << JavaParser::LPAREN)
      | (1ULL << JavaParser::LBRACE))) != 0) || ((((_la - 67) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 67)) & ((1ULL << (JavaParser::SEMI - 67))
      | (1ULL << (JavaParser::LT - 67))
      | (1ULL << (JavaParser::BANG - 67))
      | (1ULL << (JavaParser::TILDE - 67))
      | (1ULL << (JavaParser::INC - 67))
      | (1ULL << (JavaParser::DEC - 67))
      | (1ULL << (JavaParser::ADD - 67))
      | (1ULL << (JavaParser::SUB - 67))
      | (1ULL << (JavaParser::AT - 67))
      | (1ULL << (JavaParser::IDENTIFIER - 67)))) != 0)) {
      setState(790);
      blockStatement();
      setState(795);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(796);
    match(JavaParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockStatementContext ------------------------------------------------------------------

JavaParser::BlockStatementContext::BlockStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaParser::LocalVariableDeclarationContext* JavaParser::BlockStatementContext::localVariableDeclaration() {
  return getRuleContext<JavaParser::LocalVariableDeclarationContext>(0);
}

tree::TerminalNode* JavaParser::BlockStatementContext::SEMI() {
  return getToken(JavaParser::SEMI, 0);
}

JavaParser::StatementContext* JavaParser::BlockStatementContext::statement() {
  return getRuleContext<JavaParser::StatementContext>(0);
}

JavaParser::LocalTypeDeclarationContext* JavaParser::BlockStatementContext::localTypeDeclaration() {
  return getRuleContext<JavaParser::LocalTypeDeclarationContext>(0);
}


size_t JavaParser::BlockStatementContext::getRuleIndex() const {
  return JavaParser::RuleBlockStatement;
}

void JavaParser::BlockStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBlockStatement(this);
}

void JavaParser::BlockStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBlockStatement(this);
}

JavaParser::BlockStatementContext* JavaParser::blockStatement() {
  BlockStatementContext *_localctx = _tracker.createInstance<BlockStatementContext>(_ctx, getState());
  enterRule(_localctx, 128, JavaParser::RuleBlockStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(803);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 91, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(798);
      localVariableDeclaration();
      setState(799);
      match(JavaParser::SEMI);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(801);
      statement();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(802);
      localTypeDeclaration();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LocalVariableDeclarationContext ------------------------------------------------------------------

JavaParser::LocalVariableDeclarationContext::LocalVariableDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaParser::TypeTypeContext* JavaParser::LocalVariableDeclarationContext::typeType() {
  return getRuleContext<JavaParser::TypeTypeContext>(0);
}

JavaParser::VariableDeclaratorsContext* JavaParser::LocalVariableDeclarationContext::variableDeclarators() {
  return getRuleContext<JavaParser::VariableDeclaratorsContext>(0);
}

std::vector<JavaParser::VariableModifierContext *> JavaParser::LocalVariableDeclarationContext::variableModifier() {
  return getRuleContexts<JavaParser::VariableModifierContext>();
}

JavaParser::VariableModifierContext* JavaParser::LocalVariableDeclarationContext::variableModifier(size_t i) {
  return getRuleContext<JavaParser::VariableModifierContext>(i);
}


size_t JavaParser::LocalVariableDeclarationContext::getRuleIndex() const {
  return JavaParser::RuleLocalVariableDeclaration;
}

void JavaParser::LocalVariableDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLocalVariableDeclaration(this);
}

void JavaParser::LocalVariableDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLocalVariableDeclaration(this);
}

JavaParser::LocalVariableDeclarationContext* JavaParser::localVariableDeclaration() {
  LocalVariableDeclarationContext *_localctx = _tracker.createInstance<LocalVariableDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 130, JavaParser::RuleLocalVariableDeclaration);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(808);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 92, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(805);
        variableModifier(); 
      }
      setState(810);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 92, _ctx);
    }
    setState(811);
    typeType();
    setState(812);
    variableDeclarators();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LocalTypeDeclarationContext ------------------------------------------------------------------

JavaParser::LocalTypeDeclarationContext::LocalTypeDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaParser::ClassDeclarationContext* JavaParser::LocalTypeDeclarationContext::classDeclaration() {
  return getRuleContext<JavaParser::ClassDeclarationContext>(0);
}

JavaParser::InterfaceDeclarationContext* JavaParser::LocalTypeDeclarationContext::interfaceDeclaration() {
  return getRuleContext<JavaParser::InterfaceDeclarationContext>(0);
}

std::vector<JavaParser::ClassOrInterfaceModifierContext *> JavaParser::LocalTypeDeclarationContext::classOrInterfaceModifier() {
  return getRuleContexts<JavaParser::ClassOrInterfaceModifierContext>();
}

JavaParser::ClassOrInterfaceModifierContext* JavaParser::LocalTypeDeclarationContext::classOrInterfaceModifier(size_t i) {
  return getRuleContext<JavaParser::ClassOrInterfaceModifierContext>(i);
}

tree::TerminalNode* JavaParser::LocalTypeDeclarationContext::SEMI() {
  return getToken(JavaParser::SEMI, 0);
}


size_t JavaParser::LocalTypeDeclarationContext::getRuleIndex() const {
  return JavaParser::RuleLocalTypeDeclaration;
}

void JavaParser::LocalTypeDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLocalTypeDeclaration(this);
}

void JavaParser::LocalTypeDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLocalTypeDeclaration(this);
}

JavaParser::LocalTypeDeclarationContext* JavaParser::localTypeDeclaration() {
  LocalTypeDeclarationContext *_localctx = _tracker.createInstance<LocalTypeDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 132, JavaParser::RuleLocalTypeDeclaration);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(825);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaParser::ABSTRACT:
      case JavaParser::CLASS:
      case JavaParser::FINAL:
      case JavaParser::INTERFACE:
      case JavaParser::PRIVATE:
      case JavaParser::PROTECTED:
      case JavaParser::PUBLIC:
      case JavaParser::STATIC:
      case JavaParser::STRICTFP:
      case JavaParser::AT: {
        enterOuterAlt(_localctx, 1);
        setState(817);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << JavaParser::ABSTRACT)
          | (1ULL << JavaParser::FINAL)
          | (1ULL << JavaParser::PRIVATE)
          | (1ULL << JavaParser::PROTECTED)
          | (1ULL << JavaParser::PUBLIC)
          | (1ULL << JavaParser::STATIC)
          | (1ULL << JavaParser::STRICTFP))) != 0) || _la == JavaParser::AT) {
          setState(814);
          classOrInterfaceModifier();
          setState(819);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(822);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case JavaParser::CLASS: {
            setState(820);
            classDeclaration();
            break;
          }

          case JavaParser::INTERFACE: {
            setState(821);
            interfaceDeclaration();
            break;
          }

        default:
          throw NoViableAltException(this);
        }
        break;
      }

      case JavaParser::SEMI: {
        enterOuterAlt(_localctx, 2);
        setState(824);
        match(JavaParser::SEMI);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

JavaParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaParser::BlockContext* JavaParser::StatementContext::block() {
  return getRuleContext<JavaParser::BlockContext>(0);
}

tree::TerminalNode* JavaParser::StatementContext::ASSERT() {
  return getToken(JavaParser::ASSERT, 0);
}

std::vector<JavaParser::ExpressionContext *> JavaParser::StatementContext::expression() {
  return getRuleContexts<JavaParser::ExpressionContext>();
}

JavaParser::ExpressionContext* JavaParser::StatementContext::expression(size_t i) {
  return getRuleContext<JavaParser::ExpressionContext>(i);
}

tree::TerminalNode* JavaParser::StatementContext::SEMI() {
  return getToken(JavaParser::SEMI, 0);
}

tree::TerminalNode* JavaParser::StatementContext::COLON() {
  return getToken(JavaParser::COLON, 0);
}

tree::TerminalNode* JavaParser::StatementContext::IF() {
  return getToken(JavaParser::IF, 0);
}

JavaParser::ParExpressionContext* JavaParser::StatementContext::parExpression() {
  return getRuleContext<JavaParser::ParExpressionContext>(0);
}

std::vector<JavaParser::StatementContext *> JavaParser::StatementContext::statement() {
  return getRuleContexts<JavaParser::StatementContext>();
}

JavaParser::StatementContext* JavaParser::StatementContext::statement(size_t i) {
  return getRuleContext<JavaParser::StatementContext>(i);
}

tree::TerminalNode* JavaParser::StatementContext::ELSE() {
  return getToken(JavaParser::ELSE, 0);
}

tree::TerminalNode* JavaParser::StatementContext::FOR() {
  return getToken(JavaParser::FOR, 0);
}

tree::TerminalNode* JavaParser::StatementContext::LPAREN() {
  return getToken(JavaParser::LPAREN, 0);
}

JavaParser::ForControlContext* JavaParser::StatementContext::forControl() {
  return getRuleContext<JavaParser::ForControlContext>(0);
}

tree::TerminalNode* JavaParser::StatementContext::RPAREN() {
  return getToken(JavaParser::RPAREN, 0);
}

tree::TerminalNode* JavaParser::StatementContext::WHILE() {
  return getToken(JavaParser::WHILE, 0);
}

tree::TerminalNode* JavaParser::StatementContext::DO() {
  return getToken(JavaParser::DO, 0);
}

tree::TerminalNode* JavaParser::StatementContext::TRY() {
  return getToken(JavaParser::TRY, 0);
}

JavaParser::FinallyBlockContext* JavaParser::StatementContext::finallyBlock() {
  return getRuleContext<JavaParser::FinallyBlockContext>(0);
}

std::vector<JavaParser::CatchClauseContext *> JavaParser::StatementContext::catchClause() {
  return getRuleContexts<JavaParser::CatchClauseContext>();
}

JavaParser::CatchClauseContext* JavaParser::StatementContext::catchClause(size_t i) {
  return getRuleContext<JavaParser::CatchClauseContext>(i);
}

JavaParser::ResourceSpecificationContext* JavaParser::StatementContext::resourceSpecification() {
  return getRuleContext<JavaParser::ResourceSpecificationContext>(0);
}

tree::TerminalNode* JavaParser::StatementContext::SWITCH() {
  return getToken(JavaParser::SWITCH, 0);
}

tree::TerminalNode* JavaParser::StatementContext::LBRACE() {
  return getToken(JavaParser::LBRACE, 0);
}

tree::TerminalNode* JavaParser::StatementContext::RBRACE() {
  return getToken(JavaParser::RBRACE, 0);
}

std::vector<JavaParser::SwitchBlockStatementGroupContext *> JavaParser::StatementContext::switchBlockStatementGroup() {
  return getRuleContexts<JavaParser::SwitchBlockStatementGroupContext>();
}

JavaParser::SwitchBlockStatementGroupContext* JavaParser::StatementContext::switchBlockStatementGroup(size_t i) {
  return getRuleContext<JavaParser::SwitchBlockStatementGroupContext>(i);
}

std::vector<JavaParser::SwitchLabelContext *> JavaParser::StatementContext::switchLabel() {
  return getRuleContexts<JavaParser::SwitchLabelContext>();
}

JavaParser::SwitchLabelContext* JavaParser::StatementContext::switchLabel(size_t i) {
  return getRuleContext<JavaParser::SwitchLabelContext>(i);
}

tree::TerminalNode* JavaParser::StatementContext::SYNCHRONIZED() {
  return getToken(JavaParser::SYNCHRONIZED, 0);
}

tree::TerminalNode* JavaParser::StatementContext::RETURN() {
  return getToken(JavaParser::RETURN, 0);
}

tree::TerminalNode* JavaParser::StatementContext::THROW() {
  return getToken(JavaParser::THROW, 0);
}

tree::TerminalNode* JavaParser::StatementContext::BREAK() {
  return getToken(JavaParser::BREAK, 0);
}

tree::TerminalNode* JavaParser::StatementContext::IDENTIFIER() {
  return getToken(JavaParser::IDENTIFIER, 0);
}

tree::TerminalNode* JavaParser::StatementContext::CONTINUE() {
  return getToken(JavaParser::CONTINUE, 0);
}


size_t JavaParser::StatementContext::getRuleIndex() const {
  return JavaParser::RuleStatement;
}

void JavaParser::StatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatement(this);
}

void JavaParser::StatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatement(this);
}

JavaParser::StatementContext* JavaParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 134, JavaParser::RuleStatement);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    setState(931);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 108, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(827);
      dynamic_cast<StatementContext *>(_localctx)->blockLabel = block();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(828);
      match(JavaParser::ASSERT);
      setState(829);
      expression(0);
      setState(832);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == JavaParser::COLON) {
        setState(830);
        match(JavaParser::COLON);
        setState(831);
        expression(0);
      }
      setState(834);
      match(JavaParser::SEMI);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(836);
      match(JavaParser::IF);
      setState(837);
      parExpression();
      setState(838);
      statement();
      setState(841);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 97, _ctx)) {
      case 1: {
        setState(839);
        match(JavaParser::ELSE);
        setState(840);
        statement();
        break;
      }

      }
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(843);
      match(JavaParser::FOR);
      setState(844);
      match(JavaParser::LPAREN);
      setState(845);
      forControl();
      setState(846);
      match(JavaParser::RPAREN);
      setState(847);
      statement();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(849);
      match(JavaParser::WHILE);
      setState(850);
      parExpression();
      setState(851);
      statement();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(853);
      match(JavaParser::DO);
      setState(854);
      statement();
      setState(855);
      match(JavaParser::WHILE);
      setState(856);
      parExpression();
      setState(857);
      match(JavaParser::SEMI);
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(859);
      match(JavaParser::TRY);
      setState(860);
      block();
      setState(870);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case JavaParser::CATCH: {
          setState(862); 
          _errHandler->sync(this);
          _la = _input->LA(1);
          do {
            setState(861);
            catchClause();
            setState(864); 
            _errHandler->sync(this);
            _la = _input->LA(1);
          } while (_la == JavaParser::CATCH);
          setState(867);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == JavaParser::FINALLY) {
            setState(866);
            finallyBlock();
          }
          break;
        }

        case JavaParser::FINALLY: {
          setState(869);
          finallyBlock();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(872);
      match(JavaParser::TRY);
      setState(873);
      resourceSpecification();
      setState(874);
      block();
      setState(878);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == JavaParser::CATCH) {
        setState(875);
        catchClause();
        setState(880);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(882);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == JavaParser::FINALLY) {
        setState(881);
        finallyBlock();
      }
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(884);
      match(JavaParser::SWITCH);
      setState(885);
      parExpression();
      setState(886);
      match(JavaParser::LBRACE);
      setState(890);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 103, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(887);
          switchBlockStatementGroup(); 
        }
        setState(892);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 103, _ctx);
      }
      setState(896);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == JavaParser::CASE

      || _la == JavaParser::DEFAULT) {
        setState(893);
        switchLabel();
        setState(898);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(899);
      match(JavaParser::RBRACE);
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(901);
      match(JavaParser::SYNCHRONIZED);
      setState(902);
      parExpression();
      setState(903);
      block();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(905);
      match(JavaParser::RETURN);
      setState(907);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << JavaParser::BOOLEAN)
        | (1ULL << JavaParser::BYTE)
        | (1ULL << JavaParser::CHAR)
        | (1ULL << JavaParser::DOUBLE)
        | (1ULL << JavaParser::FLOAT)
        | (1ULL << JavaParser::INT)
        | (1ULL << JavaParser::LONG)
        | (1ULL << JavaParser::NEW)
        | (1ULL << JavaParser::SHORT)
        | (1ULL << JavaParser::SUPER)
        | (1ULL << JavaParser::THIS)
        | (1ULL << JavaParser::VOID)
        | (1ULL << JavaParser::DECIMAL_LITERAL)
        | (1ULL << JavaParser::HEX_LITERAL)
        | (1ULL << JavaParser::OCT_LITERAL)
        | (1ULL << JavaParser::BINARY_LITERAL)
        | (1ULL << JavaParser::FLOAT_LITERAL)
        | (1ULL << JavaParser::HEX_FLOAT_LITERAL)
        | (1ULL << JavaParser::BOOL_LITERAL)
        | (1ULL << JavaParser::CHAR_LITERAL)
        | (1ULL << JavaParser::STRING_LITERAL)
        | (1ULL << JavaParser::NULL_LITERAL)
        | (1ULL << JavaParser::LPAREN))) != 0) || ((((_la - 72) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 72)) & ((1ULL << (JavaParser::LT - 72))
        | (1ULL << (JavaParser::BANG - 72))
        | (1ULL << (JavaParser::TILDE - 72))
        | (1ULL << (JavaParser::INC - 72))
        | (1ULL << (JavaParser::DEC - 72))
        | (1ULL << (JavaParser::ADD - 72))
        | (1ULL << (JavaParser::SUB - 72))
        | (1ULL << (JavaParser::AT - 72))
        | (1ULL << (JavaParser::IDENTIFIER - 72)))) != 0)) {
        setState(906);
        expression(0);
      }
      setState(909);
      match(JavaParser::SEMI);
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(910);
      match(JavaParser::THROW);
      setState(911);
      expression(0);
      setState(912);
      match(JavaParser::SEMI);
      break;
    }

    case 13: {
      enterOuterAlt(_localctx, 13);
      setState(914);
      match(JavaParser::BREAK);
      setState(916);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == JavaParser::IDENTIFIER) {
        setState(915);
        match(JavaParser::IDENTIFIER);
      }
      setState(918);
      match(JavaParser::SEMI);
      break;
    }

    case 14: {
      enterOuterAlt(_localctx, 14);
      setState(919);
      match(JavaParser::CONTINUE);
      setState(921);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == JavaParser::IDENTIFIER) {
        setState(920);
        match(JavaParser::IDENTIFIER);
      }
      setState(923);
      match(JavaParser::SEMI);
      break;
    }

    case 15: {
      enterOuterAlt(_localctx, 15);
      setState(924);
      match(JavaParser::SEMI);
      break;
    }

    case 16: {
      enterOuterAlt(_localctx, 16);
      setState(925);
      dynamic_cast<StatementContext *>(_localctx)->statementExpression = expression(0);
      setState(926);
      match(JavaParser::SEMI);
      break;
    }

    case 17: {
      enterOuterAlt(_localctx, 17);
      setState(928);
      dynamic_cast<StatementContext *>(_localctx)->identifierLabel = match(JavaParser::IDENTIFIER);
      setState(929);
      match(JavaParser::COLON);
      setState(930);
      statement();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CatchClauseContext ------------------------------------------------------------------

JavaParser::CatchClauseContext::CatchClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaParser::CatchClauseContext::CATCH() {
  return getToken(JavaParser::CATCH, 0);
}

tree::TerminalNode* JavaParser::CatchClauseContext::LPAREN() {
  return getToken(JavaParser::LPAREN, 0);
}

JavaParser::CatchTypeContext* JavaParser::CatchClauseContext::catchType() {
  return getRuleContext<JavaParser::CatchTypeContext>(0);
}

tree::TerminalNode* JavaParser::CatchClauseContext::IDENTIFIER() {
  return getToken(JavaParser::IDENTIFIER, 0);
}

tree::TerminalNode* JavaParser::CatchClauseContext::RPAREN() {
  return getToken(JavaParser::RPAREN, 0);
}

JavaParser::BlockContext* JavaParser::CatchClauseContext::block() {
  return getRuleContext<JavaParser::BlockContext>(0);
}

std::vector<JavaParser::VariableModifierContext *> JavaParser::CatchClauseContext::variableModifier() {
  return getRuleContexts<JavaParser::VariableModifierContext>();
}

JavaParser::VariableModifierContext* JavaParser::CatchClauseContext::variableModifier(size_t i) {
  return getRuleContext<JavaParser::VariableModifierContext>(i);
}


size_t JavaParser::CatchClauseContext::getRuleIndex() const {
  return JavaParser::RuleCatchClause;
}

void JavaParser::CatchClauseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCatchClause(this);
}

void JavaParser::CatchClauseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCatchClause(this);
}

JavaParser::CatchClauseContext* JavaParser::catchClause() {
  CatchClauseContext *_localctx = _tracker.createInstance<CatchClauseContext>(_ctx, getState());
  enterRule(_localctx, 136, JavaParser::RuleCatchClause);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(933);
    match(JavaParser::CATCH);
    setState(934);
    match(JavaParser::LPAREN);
    setState(938);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == JavaParser::FINAL || _la == JavaParser::AT) {
      setState(935);
      variableModifier();
      setState(940);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(941);
    catchType();
    setState(942);
    match(JavaParser::IDENTIFIER);
    setState(943);
    match(JavaParser::RPAREN);
    setState(944);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CatchTypeContext ------------------------------------------------------------------

JavaParser::CatchTypeContext::CatchTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<JavaParser::QualifiedNameContext *> JavaParser::CatchTypeContext::qualifiedName() {
  return getRuleContexts<JavaParser::QualifiedNameContext>();
}

JavaParser::QualifiedNameContext* JavaParser::CatchTypeContext::qualifiedName(size_t i) {
  return getRuleContext<JavaParser::QualifiedNameContext>(i);
}

std::vector<tree::TerminalNode *> JavaParser::CatchTypeContext::BITOR() {
  return getTokens(JavaParser::BITOR);
}

tree::TerminalNode* JavaParser::CatchTypeContext::BITOR(size_t i) {
  return getToken(JavaParser::BITOR, i);
}


size_t JavaParser::CatchTypeContext::getRuleIndex() const {
  return JavaParser::RuleCatchType;
}

void JavaParser::CatchTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCatchType(this);
}

void JavaParser::CatchTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCatchType(this);
}

JavaParser::CatchTypeContext* JavaParser::catchType() {
  CatchTypeContext *_localctx = _tracker.createInstance<CatchTypeContext>(_ctx, getState());
  enterRule(_localctx, 138, JavaParser::RuleCatchType);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(946);
    qualifiedName();
    setState(951);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == JavaParser::BITOR) {
      setState(947);
      match(JavaParser::BITOR);
      setState(948);
      qualifiedName();
      setState(953);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FinallyBlockContext ------------------------------------------------------------------

JavaParser::FinallyBlockContext::FinallyBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaParser::FinallyBlockContext::FINALLY() {
  return getToken(JavaParser::FINALLY, 0);
}

JavaParser::BlockContext* JavaParser::FinallyBlockContext::block() {
  return getRuleContext<JavaParser::BlockContext>(0);
}


size_t JavaParser::FinallyBlockContext::getRuleIndex() const {
  return JavaParser::RuleFinallyBlock;
}

void JavaParser::FinallyBlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFinallyBlock(this);
}

void JavaParser::FinallyBlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFinallyBlock(this);
}

JavaParser::FinallyBlockContext* JavaParser::finallyBlock() {
  FinallyBlockContext *_localctx = _tracker.createInstance<FinallyBlockContext>(_ctx, getState());
  enterRule(_localctx, 140, JavaParser::RuleFinallyBlock);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(954);
    match(JavaParser::FINALLY);
    setState(955);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ResourceSpecificationContext ------------------------------------------------------------------

JavaParser::ResourceSpecificationContext::ResourceSpecificationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaParser::ResourceSpecificationContext::LPAREN() {
  return getToken(JavaParser::LPAREN, 0);
}

JavaParser::ResourcesContext* JavaParser::ResourceSpecificationContext::resources() {
  return getRuleContext<JavaParser::ResourcesContext>(0);
}

tree::TerminalNode* JavaParser::ResourceSpecificationContext::RPAREN() {
  return getToken(JavaParser::RPAREN, 0);
}

tree::TerminalNode* JavaParser::ResourceSpecificationContext::SEMI() {
  return getToken(JavaParser::SEMI, 0);
}


size_t JavaParser::ResourceSpecificationContext::getRuleIndex() const {
  return JavaParser::RuleResourceSpecification;
}

void JavaParser::ResourceSpecificationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterResourceSpecification(this);
}

void JavaParser::ResourceSpecificationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitResourceSpecification(this);
}

JavaParser::ResourceSpecificationContext* JavaParser::resourceSpecification() {
  ResourceSpecificationContext *_localctx = _tracker.createInstance<ResourceSpecificationContext>(_ctx, getState());
  enterRule(_localctx, 142, JavaParser::RuleResourceSpecification);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(957);
    match(JavaParser::LPAREN);
    setState(958);
    resources();
    setState(960);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaParser::SEMI) {
      setState(959);
      match(JavaParser::SEMI);
    }
    setState(962);
    match(JavaParser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ResourcesContext ------------------------------------------------------------------

JavaParser::ResourcesContext::ResourcesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<JavaParser::ResourceContext *> JavaParser::ResourcesContext::resource() {
  return getRuleContexts<JavaParser::ResourceContext>();
}

JavaParser::ResourceContext* JavaParser::ResourcesContext::resource(size_t i) {
  return getRuleContext<JavaParser::ResourceContext>(i);
}

std::vector<tree::TerminalNode *> JavaParser::ResourcesContext::SEMI() {
  return getTokens(JavaParser::SEMI);
}

tree::TerminalNode* JavaParser::ResourcesContext::SEMI(size_t i) {
  return getToken(JavaParser::SEMI, i);
}


size_t JavaParser::ResourcesContext::getRuleIndex() const {
  return JavaParser::RuleResources;
}

void JavaParser::ResourcesContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterResources(this);
}

void JavaParser::ResourcesContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitResources(this);
}

JavaParser::ResourcesContext* JavaParser::resources() {
  ResourcesContext *_localctx = _tracker.createInstance<ResourcesContext>(_ctx, getState());
  enterRule(_localctx, 144, JavaParser::RuleResources);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(964);
    resource();
    setState(969);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 112, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(965);
        match(JavaParser::SEMI);
        setState(966);
        resource(); 
      }
      setState(971);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 112, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ResourceContext ------------------------------------------------------------------

JavaParser::ResourceContext::ResourceContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaParser::ClassOrInterfaceTypeContext* JavaParser::ResourceContext::classOrInterfaceType() {
  return getRuleContext<JavaParser::ClassOrInterfaceTypeContext>(0);
}

JavaParser::VariableDeclaratorIdContext* JavaParser::ResourceContext::variableDeclaratorId() {
  return getRuleContext<JavaParser::VariableDeclaratorIdContext>(0);
}

tree::TerminalNode* JavaParser::ResourceContext::ASSIGN() {
  return getToken(JavaParser::ASSIGN, 0);
}

JavaParser::ExpressionContext* JavaParser::ResourceContext::expression() {
  return getRuleContext<JavaParser::ExpressionContext>(0);
}

std::vector<JavaParser::VariableModifierContext *> JavaParser::ResourceContext::variableModifier() {
  return getRuleContexts<JavaParser::VariableModifierContext>();
}

JavaParser::VariableModifierContext* JavaParser::ResourceContext::variableModifier(size_t i) {
  return getRuleContext<JavaParser::VariableModifierContext>(i);
}


size_t JavaParser::ResourceContext::getRuleIndex() const {
  return JavaParser::RuleResource;
}

void JavaParser::ResourceContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterResource(this);
}

void JavaParser::ResourceContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitResource(this);
}

JavaParser::ResourceContext* JavaParser::resource() {
  ResourceContext *_localctx = _tracker.createInstance<ResourceContext>(_ctx, getState());
  enterRule(_localctx, 146, JavaParser::RuleResource);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(975);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == JavaParser::FINAL || _la == JavaParser::AT) {
      setState(972);
      variableModifier();
      setState(977);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(978);
    classOrInterfaceType();
    setState(979);
    variableDeclaratorId();
    setState(980);
    match(JavaParser::ASSIGN);
    setState(981);
    expression(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SwitchBlockStatementGroupContext ------------------------------------------------------------------

JavaParser::SwitchBlockStatementGroupContext::SwitchBlockStatementGroupContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<JavaParser::SwitchLabelContext *> JavaParser::SwitchBlockStatementGroupContext::switchLabel() {
  return getRuleContexts<JavaParser::SwitchLabelContext>();
}

JavaParser::SwitchLabelContext* JavaParser::SwitchBlockStatementGroupContext::switchLabel(size_t i) {
  return getRuleContext<JavaParser::SwitchLabelContext>(i);
}

std::vector<JavaParser::BlockStatementContext *> JavaParser::SwitchBlockStatementGroupContext::blockStatement() {
  return getRuleContexts<JavaParser::BlockStatementContext>();
}

JavaParser::BlockStatementContext* JavaParser::SwitchBlockStatementGroupContext::blockStatement(size_t i) {
  return getRuleContext<JavaParser::BlockStatementContext>(i);
}


size_t JavaParser::SwitchBlockStatementGroupContext::getRuleIndex() const {
  return JavaParser::RuleSwitchBlockStatementGroup;
}

void JavaParser::SwitchBlockStatementGroupContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSwitchBlockStatementGroup(this);
}

void JavaParser::SwitchBlockStatementGroupContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSwitchBlockStatementGroup(this);
}

JavaParser::SwitchBlockStatementGroupContext* JavaParser::switchBlockStatementGroup() {
  SwitchBlockStatementGroupContext *_localctx = _tracker.createInstance<SwitchBlockStatementGroupContext>(_ctx, getState());
  enterRule(_localctx, 148, JavaParser::RuleSwitchBlockStatementGroup);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(984); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(983);
      switchLabel();
      setState(986); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == JavaParser::CASE

    || _la == JavaParser::DEFAULT);
    setState(989); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(988);
      blockStatement();
      setState(991); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << JavaParser::ABSTRACT)
      | (1ULL << JavaParser::ASSERT)
      | (1ULL << JavaParser::BOOLEAN)
      | (1ULL << JavaParser::BREAK)
      | (1ULL << JavaParser::BYTE)
      | (1ULL << JavaParser::CHAR)
      | (1ULL << JavaParser::CLASS)
      | (1ULL << JavaParser::CONTINUE)
      | (1ULL << JavaParser::DO)
      | (1ULL << JavaParser::DOUBLE)
      | (1ULL << JavaParser::FINAL)
      | (1ULL << JavaParser::FLOAT)
      | (1ULL << JavaParser::FOR)
      | (1ULL << JavaParser::IF)
      | (1ULL << JavaParser::INT)
      | (1ULL << JavaParser::INTERFACE)
      | (1ULL << JavaParser::LONG)
      | (1ULL << JavaParser::NEW)
      | (1ULL << JavaParser::PRIVATE)
      | (1ULL << JavaParser::PROTECTED)
      | (1ULL << JavaParser::PUBLIC)
      | (1ULL << JavaParser::RETURN)
      | (1ULL << JavaParser::SHORT)
      | (1ULL << JavaParser::STATIC)
      | (1ULL << JavaParser::STRICTFP)
      | (1ULL << JavaParser::SUPER)
      | (1ULL << JavaParser::SWITCH)
      | (1ULL << JavaParser::SYNCHRONIZED)
      | (1ULL << JavaParser::THIS)
      | (1ULL << JavaParser::THROW)
      | (1ULL << JavaParser::TRY)
      | (1ULL << JavaParser::VOID)
      | (1ULL << JavaParser::WHILE)
      | (1ULL << JavaParser::DECIMAL_LITERAL)
      | (1ULL << JavaParser::HEX_LITERAL)
      | (1ULL << JavaParser::OCT_LITERAL)
      | (1ULL << JavaParser::BINARY_LITERAL)
      | (1ULL << JavaParser::FLOAT_LITERAL)
      | (1ULL << JavaParser::HEX_FLOAT_LITERAL)
      | (1ULL << JavaParser::BOOL_LITERAL)
      | (1ULL << JavaParser::CHAR_LITERAL)
      | (1ULL << JavaParser::STRING_LITERAL)
      | (1ULL << JavaParser::NULL_LITERAL)
      | (1ULL << JavaParser::LPAREN)
      | (1ULL << JavaParser::LBRACE))) != 0) || ((((_la - 67) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 67)) & ((1ULL << (JavaParser::SEMI - 67))
      | (1ULL << (JavaParser::LT - 67))
      | (1ULL << (JavaParser::BANG - 67))
      | (1ULL << (JavaParser::TILDE - 67))
      | (1ULL << (JavaParser::INC - 67))
      | (1ULL << (JavaParser::DEC - 67))
      | (1ULL << (JavaParser::ADD - 67))
      | (1ULL << (JavaParser::SUB - 67))
      | (1ULL << (JavaParser::AT - 67))
      | (1ULL << (JavaParser::IDENTIFIER - 67)))) != 0));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SwitchLabelContext ------------------------------------------------------------------

JavaParser::SwitchLabelContext::SwitchLabelContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaParser::SwitchLabelContext::CASE() {
  return getToken(JavaParser::CASE, 0);
}

tree::TerminalNode* JavaParser::SwitchLabelContext::COLON() {
  return getToken(JavaParser::COLON, 0);
}

JavaParser::ExpressionContext* JavaParser::SwitchLabelContext::expression() {
  return getRuleContext<JavaParser::ExpressionContext>(0);
}

tree::TerminalNode* JavaParser::SwitchLabelContext::IDENTIFIER() {
  return getToken(JavaParser::IDENTIFIER, 0);
}

tree::TerminalNode* JavaParser::SwitchLabelContext::DEFAULT() {
  return getToken(JavaParser::DEFAULT, 0);
}


size_t JavaParser::SwitchLabelContext::getRuleIndex() const {
  return JavaParser::RuleSwitchLabel;
}

void JavaParser::SwitchLabelContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSwitchLabel(this);
}

void JavaParser::SwitchLabelContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSwitchLabel(this);
}

JavaParser::SwitchLabelContext* JavaParser::switchLabel() {
  SwitchLabelContext *_localctx = _tracker.createInstance<SwitchLabelContext>(_ctx, getState());
  enterRule(_localctx, 150, JavaParser::RuleSwitchLabel);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(1001);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaParser::CASE: {
        enterOuterAlt(_localctx, 1);
        setState(993);
        match(JavaParser::CASE);
        setState(996);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 116, _ctx)) {
        case 1: {
          setState(994);
          dynamic_cast<SwitchLabelContext *>(_localctx)->constantExpression = expression(0);
          break;
        }

        case 2: {
          setState(995);
          dynamic_cast<SwitchLabelContext *>(_localctx)->enumConstantName = match(JavaParser::IDENTIFIER);
          break;
        }

        }
        setState(998);
        match(JavaParser::COLON);
        break;
      }

      case JavaParser::DEFAULT: {
        enterOuterAlt(_localctx, 2);
        setState(999);
        match(JavaParser::DEFAULT);
        setState(1000);
        match(JavaParser::COLON);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ForControlContext ------------------------------------------------------------------

JavaParser::ForControlContext::ForControlContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaParser::EnhancedForControlContext* JavaParser::ForControlContext::enhancedForControl() {
  return getRuleContext<JavaParser::EnhancedForControlContext>(0);
}

std::vector<tree::TerminalNode *> JavaParser::ForControlContext::SEMI() {
  return getTokens(JavaParser::SEMI);
}

tree::TerminalNode* JavaParser::ForControlContext::SEMI(size_t i) {
  return getToken(JavaParser::SEMI, i);
}

JavaParser::ForInitContext* JavaParser::ForControlContext::forInit() {
  return getRuleContext<JavaParser::ForInitContext>(0);
}

JavaParser::ExpressionContext* JavaParser::ForControlContext::expression() {
  return getRuleContext<JavaParser::ExpressionContext>(0);
}

JavaParser::ExpressionListContext* JavaParser::ForControlContext::expressionList() {
  return getRuleContext<JavaParser::ExpressionListContext>(0);
}


size_t JavaParser::ForControlContext::getRuleIndex() const {
  return JavaParser::RuleForControl;
}

void JavaParser::ForControlContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterForControl(this);
}

void JavaParser::ForControlContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitForControl(this);
}

JavaParser::ForControlContext* JavaParser::forControl() {
  ForControlContext *_localctx = _tracker.createInstance<ForControlContext>(_ctx, getState());
  enterRule(_localctx, 152, JavaParser::RuleForControl);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(1015);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 121, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(1003);
      enhancedForControl();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(1005);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << JavaParser::BOOLEAN)
        | (1ULL << JavaParser::BYTE)
        | (1ULL << JavaParser::CHAR)
        | (1ULL << JavaParser::DOUBLE)
        | (1ULL << JavaParser::FINAL)
        | (1ULL << JavaParser::FLOAT)
        | (1ULL << JavaParser::INT)
        | (1ULL << JavaParser::LONG)
        | (1ULL << JavaParser::NEW)
        | (1ULL << JavaParser::SHORT)
        | (1ULL << JavaParser::SUPER)
        | (1ULL << JavaParser::THIS)
        | (1ULL << JavaParser::VOID)
        | (1ULL << JavaParser::DECIMAL_LITERAL)
        | (1ULL << JavaParser::HEX_LITERAL)
        | (1ULL << JavaParser::OCT_LITERAL)
        | (1ULL << JavaParser::BINARY_LITERAL)
        | (1ULL << JavaParser::FLOAT_LITERAL)
        | (1ULL << JavaParser::HEX_FLOAT_LITERAL)
        | (1ULL << JavaParser::BOOL_LITERAL)
        | (1ULL << JavaParser::CHAR_LITERAL)
        | (1ULL << JavaParser::STRING_LITERAL)
        | (1ULL << JavaParser::NULL_LITERAL)
        | (1ULL << JavaParser::LPAREN))) != 0) || ((((_la - 72) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 72)) & ((1ULL << (JavaParser::LT - 72))
        | (1ULL << (JavaParser::BANG - 72))
        | (1ULL << (JavaParser::TILDE - 72))
        | (1ULL << (JavaParser::INC - 72))
        | (1ULL << (JavaParser::DEC - 72))
        | (1ULL << (JavaParser::ADD - 72))
        | (1ULL << (JavaParser::SUB - 72))
        | (1ULL << (JavaParser::AT - 72))
        | (1ULL << (JavaParser::IDENTIFIER - 72)))) != 0)) {
        setState(1004);
        forInit();
      }
      setState(1007);
      match(JavaParser::SEMI);
      setState(1009);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << JavaParser::BOOLEAN)
        | (1ULL << JavaParser::BYTE)
        | (1ULL << JavaParser::CHAR)
        | (1ULL << JavaParser::DOUBLE)
        | (1ULL << JavaParser::FLOAT)
        | (1ULL << JavaParser::INT)
        | (1ULL << JavaParser::LONG)
        | (1ULL << JavaParser::NEW)
        | (1ULL << JavaParser::SHORT)
        | (1ULL << JavaParser::SUPER)
        | (1ULL << JavaParser::THIS)
        | (1ULL << JavaParser::VOID)
        | (1ULL << JavaParser::DECIMAL_LITERAL)
        | (1ULL << JavaParser::HEX_LITERAL)
        | (1ULL << JavaParser::OCT_LITERAL)
        | (1ULL << JavaParser::BINARY_LITERAL)
        | (1ULL << JavaParser::FLOAT_LITERAL)
        | (1ULL << JavaParser::HEX_FLOAT_LITERAL)
        | (1ULL << JavaParser::BOOL_LITERAL)
        | (1ULL << JavaParser::CHAR_LITERAL)
        | (1ULL << JavaParser::STRING_LITERAL)
        | (1ULL << JavaParser::NULL_LITERAL)
        | (1ULL << JavaParser::LPAREN))) != 0) || ((((_la - 72) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 72)) & ((1ULL << (JavaParser::LT - 72))
        | (1ULL << (JavaParser::BANG - 72))
        | (1ULL << (JavaParser::TILDE - 72))
        | (1ULL << (JavaParser::INC - 72))
        | (1ULL << (JavaParser::DEC - 72))
        | (1ULL << (JavaParser::ADD - 72))
        | (1ULL << (JavaParser::SUB - 72))
        | (1ULL << (JavaParser::AT - 72))
        | (1ULL << (JavaParser::IDENTIFIER - 72)))) != 0)) {
        setState(1008);
        expression(0);
      }
      setState(1011);
      match(JavaParser::SEMI);
      setState(1013);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << JavaParser::BOOLEAN)
        | (1ULL << JavaParser::BYTE)
        | (1ULL << JavaParser::CHAR)
        | (1ULL << JavaParser::DOUBLE)
        | (1ULL << JavaParser::FLOAT)
        | (1ULL << JavaParser::INT)
        | (1ULL << JavaParser::LONG)
        | (1ULL << JavaParser::NEW)
        | (1ULL << JavaParser::SHORT)
        | (1ULL << JavaParser::SUPER)
        | (1ULL << JavaParser::THIS)
        | (1ULL << JavaParser::VOID)
        | (1ULL << JavaParser::DECIMAL_LITERAL)
        | (1ULL << JavaParser::HEX_LITERAL)
        | (1ULL << JavaParser::OCT_LITERAL)
        | (1ULL << JavaParser::BINARY_LITERAL)
        | (1ULL << JavaParser::FLOAT_LITERAL)
        | (1ULL << JavaParser::HEX_FLOAT_LITERAL)
        | (1ULL << JavaParser::BOOL_LITERAL)
        | (1ULL << JavaParser::CHAR_LITERAL)
        | (1ULL << JavaParser::STRING_LITERAL)
        | (1ULL << JavaParser::NULL_LITERAL)
        | (1ULL << JavaParser::LPAREN))) != 0) || ((((_la - 72) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 72)) & ((1ULL << (JavaParser::LT - 72))
        | (1ULL << (JavaParser::BANG - 72))
        | (1ULL << (JavaParser::TILDE - 72))
        | (1ULL << (JavaParser::INC - 72))
        | (1ULL << (JavaParser::DEC - 72))
        | (1ULL << (JavaParser::ADD - 72))
        | (1ULL << (JavaParser::SUB - 72))
        | (1ULL << (JavaParser::AT - 72))
        | (1ULL << (JavaParser::IDENTIFIER - 72)))) != 0)) {
        setState(1012);
        dynamic_cast<ForControlContext *>(_localctx)->forUpdate = expressionList();
      }
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ForInitContext ------------------------------------------------------------------

JavaParser::ForInitContext::ForInitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaParser::LocalVariableDeclarationContext* JavaParser::ForInitContext::localVariableDeclaration() {
  return getRuleContext<JavaParser::LocalVariableDeclarationContext>(0);
}

JavaParser::ExpressionListContext* JavaParser::ForInitContext::expressionList() {
  return getRuleContext<JavaParser::ExpressionListContext>(0);
}


size_t JavaParser::ForInitContext::getRuleIndex() const {
  return JavaParser::RuleForInit;
}

void JavaParser::ForInitContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterForInit(this);
}

void JavaParser::ForInitContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitForInit(this);
}

JavaParser::ForInitContext* JavaParser::forInit() {
  ForInitContext *_localctx = _tracker.createInstance<ForInitContext>(_ctx, getState());
  enterRule(_localctx, 154, JavaParser::RuleForInit);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(1019);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 122, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(1017);
      localVariableDeclaration();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(1018);
      expressionList();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EnhancedForControlContext ------------------------------------------------------------------

JavaParser::EnhancedForControlContext::EnhancedForControlContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaParser::TypeTypeContext* JavaParser::EnhancedForControlContext::typeType() {
  return getRuleContext<JavaParser::TypeTypeContext>(0);
}

JavaParser::VariableDeclaratorIdContext* JavaParser::EnhancedForControlContext::variableDeclaratorId() {
  return getRuleContext<JavaParser::VariableDeclaratorIdContext>(0);
}

tree::TerminalNode* JavaParser::EnhancedForControlContext::COLON() {
  return getToken(JavaParser::COLON, 0);
}

JavaParser::ExpressionContext* JavaParser::EnhancedForControlContext::expression() {
  return getRuleContext<JavaParser::ExpressionContext>(0);
}

std::vector<JavaParser::VariableModifierContext *> JavaParser::EnhancedForControlContext::variableModifier() {
  return getRuleContexts<JavaParser::VariableModifierContext>();
}

JavaParser::VariableModifierContext* JavaParser::EnhancedForControlContext::variableModifier(size_t i) {
  return getRuleContext<JavaParser::VariableModifierContext>(i);
}


size_t JavaParser::EnhancedForControlContext::getRuleIndex() const {
  return JavaParser::RuleEnhancedForControl;
}

void JavaParser::EnhancedForControlContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEnhancedForControl(this);
}

void JavaParser::EnhancedForControlContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEnhancedForControl(this);
}

JavaParser::EnhancedForControlContext* JavaParser::enhancedForControl() {
  EnhancedForControlContext *_localctx = _tracker.createInstance<EnhancedForControlContext>(_ctx, getState());
  enterRule(_localctx, 156, JavaParser::RuleEnhancedForControl);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(1024);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 123, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(1021);
        variableModifier(); 
      }
      setState(1026);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 123, _ctx);
    }
    setState(1027);
    typeType();
    setState(1028);
    variableDeclaratorId();
    setState(1029);
    match(JavaParser::COLON);
    setState(1030);
    expression(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParExpressionContext ------------------------------------------------------------------

JavaParser::ParExpressionContext::ParExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaParser::ParExpressionContext::LPAREN() {
  return getToken(JavaParser::LPAREN, 0);
}

JavaParser::ExpressionContext* JavaParser::ParExpressionContext::expression() {
  return getRuleContext<JavaParser::ExpressionContext>(0);
}

tree::TerminalNode* JavaParser::ParExpressionContext::RPAREN() {
  return getToken(JavaParser::RPAREN, 0);
}


size_t JavaParser::ParExpressionContext::getRuleIndex() const {
  return JavaParser::RuleParExpression;
}

void JavaParser::ParExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParExpression(this);
}

void JavaParser::ParExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParExpression(this);
}

JavaParser::ParExpressionContext* JavaParser::parExpression() {
  ParExpressionContext *_localctx = _tracker.createInstance<ParExpressionContext>(_ctx, getState());
  enterRule(_localctx, 158, JavaParser::RuleParExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1032);
    match(JavaParser::LPAREN);
    setState(1033);
    expression(0);
    setState(1034);
    match(JavaParser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionListContext ------------------------------------------------------------------

JavaParser::ExpressionListContext::ExpressionListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<JavaParser::ExpressionContext *> JavaParser::ExpressionListContext::expression() {
  return getRuleContexts<JavaParser::ExpressionContext>();
}

JavaParser::ExpressionContext* JavaParser::ExpressionListContext::expression(size_t i) {
  return getRuleContext<JavaParser::ExpressionContext>(i);
}

std::vector<tree::TerminalNode *> JavaParser::ExpressionListContext::COMMA() {
  return getTokens(JavaParser::COMMA);
}

tree::TerminalNode* JavaParser::ExpressionListContext::COMMA(size_t i) {
  return getToken(JavaParser::COMMA, i);
}


size_t JavaParser::ExpressionListContext::getRuleIndex() const {
  return JavaParser::RuleExpressionList;
}

void JavaParser::ExpressionListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpressionList(this);
}

void JavaParser::ExpressionListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpressionList(this);
}

JavaParser::ExpressionListContext* JavaParser::expressionList() {
  ExpressionListContext *_localctx = _tracker.createInstance<ExpressionListContext>(_ctx, getState());
  enterRule(_localctx, 160, JavaParser::RuleExpressionList);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1036);
    expression(0);
    setState(1041);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == JavaParser::COMMA) {
      setState(1037);
      match(JavaParser::COMMA);
      setState(1038);
      expression(0);
      setState(1043);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MethodCallContext ------------------------------------------------------------------

JavaParser::MethodCallContext::MethodCallContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaParser::MethodCallContext::IDENTIFIER() {
  return getToken(JavaParser::IDENTIFIER, 0);
}

tree::TerminalNode* JavaParser::MethodCallContext::LPAREN() {
  return getToken(JavaParser::LPAREN, 0);
}

tree::TerminalNode* JavaParser::MethodCallContext::RPAREN() {
  return getToken(JavaParser::RPAREN, 0);
}

JavaParser::ExpressionListContext* JavaParser::MethodCallContext::expressionList() {
  return getRuleContext<JavaParser::ExpressionListContext>(0);
}

tree::TerminalNode* JavaParser::MethodCallContext::THIS() {
  return getToken(JavaParser::THIS, 0);
}

tree::TerminalNode* JavaParser::MethodCallContext::SUPER() {
  return getToken(JavaParser::SUPER, 0);
}


size_t JavaParser::MethodCallContext::getRuleIndex() const {
  return JavaParser::RuleMethodCall;
}

void JavaParser::MethodCallContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMethodCall(this);
}

void JavaParser::MethodCallContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMethodCall(this);
}

JavaParser::MethodCallContext* JavaParser::methodCall() {
  MethodCallContext *_localctx = _tracker.createInstance<MethodCallContext>(_ctx, getState());
  enterRule(_localctx, 162, JavaParser::RuleMethodCall);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(1062);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(1044);
        match(JavaParser::IDENTIFIER);
        setState(1045);
        match(JavaParser::LPAREN);
        setState(1047);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << JavaParser::BOOLEAN)
          | (1ULL << JavaParser::BYTE)
          | (1ULL << JavaParser::CHAR)
          | (1ULL << JavaParser::DOUBLE)
          | (1ULL << JavaParser::FLOAT)
          | (1ULL << JavaParser::INT)
          | (1ULL << JavaParser::LONG)
          | (1ULL << JavaParser::NEW)
          | (1ULL << JavaParser::SHORT)
          | (1ULL << JavaParser::SUPER)
          | (1ULL << JavaParser::THIS)
          | (1ULL << JavaParser::VOID)
          | (1ULL << JavaParser::DECIMAL_LITERAL)
          | (1ULL << JavaParser::HEX_LITERAL)
          | (1ULL << JavaParser::OCT_LITERAL)
          | (1ULL << JavaParser::BINARY_LITERAL)
          | (1ULL << JavaParser::FLOAT_LITERAL)
          | (1ULL << JavaParser::HEX_FLOAT_LITERAL)
          | (1ULL << JavaParser::BOOL_LITERAL)
          | (1ULL << JavaParser::CHAR_LITERAL)
          | (1ULL << JavaParser::STRING_LITERAL)
          | (1ULL << JavaParser::NULL_LITERAL)
          | (1ULL << JavaParser::LPAREN))) != 0) || ((((_la - 72) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 72)) & ((1ULL << (JavaParser::LT - 72))
          | (1ULL << (JavaParser::BANG - 72))
          | (1ULL << (JavaParser::TILDE - 72))
          | (1ULL << (JavaParser::INC - 72))
          | (1ULL << (JavaParser::DEC - 72))
          | (1ULL << (JavaParser::ADD - 72))
          | (1ULL << (JavaParser::SUB - 72))
          | (1ULL << (JavaParser::AT - 72))
          | (1ULL << (JavaParser::IDENTIFIER - 72)))) != 0)) {
          setState(1046);
          expressionList();
        }
        setState(1049);
        match(JavaParser::RPAREN);
        break;
      }

      case JavaParser::THIS: {
        enterOuterAlt(_localctx, 2);
        setState(1050);
        match(JavaParser::THIS);
        setState(1051);
        match(JavaParser::LPAREN);
        setState(1053);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << JavaParser::BOOLEAN)
          | (1ULL << JavaParser::BYTE)
          | (1ULL << JavaParser::CHAR)
          | (1ULL << JavaParser::DOUBLE)
          | (1ULL << JavaParser::FLOAT)
          | (1ULL << JavaParser::INT)
          | (1ULL << JavaParser::LONG)
          | (1ULL << JavaParser::NEW)
          | (1ULL << JavaParser::SHORT)
          | (1ULL << JavaParser::SUPER)
          | (1ULL << JavaParser::THIS)
          | (1ULL << JavaParser::VOID)
          | (1ULL << JavaParser::DECIMAL_LITERAL)
          | (1ULL << JavaParser::HEX_LITERAL)
          | (1ULL << JavaParser::OCT_LITERAL)
          | (1ULL << JavaParser::BINARY_LITERAL)
          | (1ULL << JavaParser::FLOAT_LITERAL)
          | (1ULL << JavaParser::HEX_FLOAT_LITERAL)
          | (1ULL << JavaParser::BOOL_LITERAL)
          | (1ULL << JavaParser::CHAR_LITERAL)
          | (1ULL << JavaParser::STRING_LITERAL)
          | (1ULL << JavaParser::NULL_LITERAL)
          | (1ULL << JavaParser::LPAREN))) != 0) || ((((_la - 72) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 72)) & ((1ULL << (JavaParser::LT - 72))
          | (1ULL << (JavaParser::BANG - 72))
          | (1ULL << (JavaParser::TILDE - 72))
          | (1ULL << (JavaParser::INC - 72))
          | (1ULL << (JavaParser::DEC - 72))
          | (1ULL << (JavaParser::ADD - 72))
          | (1ULL << (JavaParser::SUB - 72))
          | (1ULL << (JavaParser::AT - 72))
          | (1ULL << (JavaParser::IDENTIFIER - 72)))) != 0)) {
          setState(1052);
          expressionList();
        }
        setState(1055);
        match(JavaParser::RPAREN);
        break;
      }

      case JavaParser::SUPER: {
        enterOuterAlt(_localctx, 3);
        setState(1056);
        match(JavaParser::SUPER);
        setState(1057);
        match(JavaParser::LPAREN);
        setState(1059);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << JavaParser::BOOLEAN)
          | (1ULL << JavaParser::BYTE)
          | (1ULL << JavaParser::CHAR)
          | (1ULL << JavaParser::DOUBLE)
          | (1ULL << JavaParser::FLOAT)
          | (1ULL << JavaParser::INT)
          | (1ULL << JavaParser::LONG)
          | (1ULL << JavaParser::NEW)
          | (1ULL << JavaParser::SHORT)
          | (1ULL << JavaParser::SUPER)
          | (1ULL << JavaParser::THIS)
          | (1ULL << JavaParser::VOID)
          | (1ULL << JavaParser::DECIMAL_LITERAL)
          | (1ULL << JavaParser::HEX_LITERAL)
          | (1ULL << JavaParser::OCT_LITERAL)
          | (1ULL << JavaParser::BINARY_LITERAL)
          | (1ULL << JavaParser::FLOAT_LITERAL)
          | (1ULL << JavaParser::HEX_FLOAT_LITERAL)
          | (1ULL << JavaParser::BOOL_LITERAL)
          | (1ULL << JavaParser::CHAR_LITERAL)
          | (1ULL << JavaParser::STRING_LITERAL)
          | (1ULL << JavaParser::NULL_LITERAL)
          | (1ULL << JavaParser::LPAREN))) != 0) || ((((_la - 72) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 72)) & ((1ULL << (JavaParser::LT - 72))
          | (1ULL << (JavaParser::BANG - 72))
          | (1ULL << (JavaParser::TILDE - 72))
          | (1ULL << (JavaParser::INC - 72))
          | (1ULL << (JavaParser::DEC - 72))
          | (1ULL << (JavaParser::ADD - 72))
          | (1ULL << (JavaParser::SUB - 72))
          | (1ULL << (JavaParser::AT - 72))
          | (1ULL << (JavaParser::IDENTIFIER - 72)))) != 0)) {
          setState(1058);
          expressionList();
        }
        setState(1061);
        match(JavaParser::RPAREN);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionContext ------------------------------------------------------------------

JavaParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaParser::PrimaryContext* JavaParser::ExpressionContext::primary() {
  return getRuleContext<JavaParser::PrimaryContext>(0);
}

JavaParser::MethodCallContext* JavaParser::ExpressionContext::methodCall() {
  return getRuleContext<JavaParser::MethodCallContext>(0);
}

tree::TerminalNode* JavaParser::ExpressionContext::NEW() {
  return getToken(JavaParser::NEW, 0);
}

JavaParser::CreatorContext* JavaParser::ExpressionContext::creator() {
  return getRuleContext<JavaParser::CreatorContext>(0);
}

tree::TerminalNode* JavaParser::ExpressionContext::LPAREN() {
  return getToken(JavaParser::LPAREN, 0);
}

JavaParser::TypeTypeContext* JavaParser::ExpressionContext::typeType() {
  return getRuleContext<JavaParser::TypeTypeContext>(0);
}

tree::TerminalNode* JavaParser::ExpressionContext::RPAREN() {
  return getToken(JavaParser::RPAREN, 0);
}

std::vector<JavaParser::ExpressionContext *> JavaParser::ExpressionContext::expression() {
  return getRuleContexts<JavaParser::ExpressionContext>();
}

JavaParser::ExpressionContext* JavaParser::ExpressionContext::expression(size_t i) {
  return getRuleContext<JavaParser::ExpressionContext>(i);
}

tree::TerminalNode* JavaParser::ExpressionContext::ADD() {
  return getToken(JavaParser::ADD, 0);
}

tree::TerminalNode* JavaParser::ExpressionContext::SUB() {
  return getToken(JavaParser::SUB, 0);
}

tree::TerminalNode* JavaParser::ExpressionContext::INC() {
  return getToken(JavaParser::INC, 0);
}

tree::TerminalNode* JavaParser::ExpressionContext::DEC() {
  return getToken(JavaParser::DEC, 0);
}

tree::TerminalNode* JavaParser::ExpressionContext::TILDE() {
  return getToken(JavaParser::TILDE, 0);
}

tree::TerminalNode* JavaParser::ExpressionContext::BANG() {
  return getToken(JavaParser::BANG, 0);
}

JavaParser::LambdaExpressionContext* JavaParser::ExpressionContext::lambdaExpression() {
  return getRuleContext<JavaParser::LambdaExpressionContext>(0);
}

tree::TerminalNode* JavaParser::ExpressionContext::COLONCOLON() {
  return getToken(JavaParser::COLONCOLON, 0);
}

tree::TerminalNode* JavaParser::ExpressionContext::IDENTIFIER() {
  return getToken(JavaParser::IDENTIFIER, 0);
}

JavaParser::TypeArgumentsContext* JavaParser::ExpressionContext::typeArguments() {
  return getRuleContext<JavaParser::TypeArgumentsContext>(0);
}

JavaParser::ClassTypeContext* JavaParser::ExpressionContext::classType() {
  return getRuleContext<JavaParser::ClassTypeContext>(0);
}

tree::TerminalNode* JavaParser::ExpressionContext::MUL() {
  return getToken(JavaParser::MUL, 0);
}

tree::TerminalNode* JavaParser::ExpressionContext::DIV() {
  return getToken(JavaParser::DIV, 0);
}

tree::TerminalNode* JavaParser::ExpressionContext::MOD() {
  return getToken(JavaParser::MOD, 0);
}

std::vector<tree::TerminalNode *> JavaParser::ExpressionContext::LT() {
  return getTokens(JavaParser::LT);
}

tree::TerminalNode* JavaParser::ExpressionContext::LT(size_t i) {
  return getToken(JavaParser::LT, i);
}

std::vector<tree::TerminalNode *> JavaParser::ExpressionContext::GT() {
  return getTokens(JavaParser::GT);
}

tree::TerminalNode* JavaParser::ExpressionContext::GT(size_t i) {
  return getToken(JavaParser::GT, i);
}

tree::TerminalNode* JavaParser::ExpressionContext::LE() {
  return getToken(JavaParser::LE, 0);
}

tree::TerminalNode* JavaParser::ExpressionContext::GE() {
  return getToken(JavaParser::GE, 0);
}

tree::TerminalNode* JavaParser::ExpressionContext::EQUAL() {
  return getToken(JavaParser::EQUAL, 0);
}

tree::TerminalNode* JavaParser::ExpressionContext::NOTEQUAL() {
  return getToken(JavaParser::NOTEQUAL, 0);
}

tree::TerminalNode* JavaParser::ExpressionContext::BITAND() {
  return getToken(JavaParser::BITAND, 0);
}

tree::TerminalNode* JavaParser::ExpressionContext::CARET() {
  return getToken(JavaParser::CARET, 0);
}

tree::TerminalNode* JavaParser::ExpressionContext::BITOR() {
  return getToken(JavaParser::BITOR, 0);
}

tree::TerminalNode* JavaParser::ExpressionContext::AND() {
  return getToken(JavaParser::AND, 0);
}

tree::TerminalNode* JavaParser::ExpressionContext::OR() {
  return getToken(JavaParser::OR, 0);
}

tree::TerminalNode* JavaParser::ExpressionContext::COLON() {
  return getToken(JavaParser::COLON, 0);
}

tree::TerminalNode* JavaParser::ExpressionContext::QUESTION() {
  return getToken(JavaParser::QUESTION, 0);
}

tree::TerminalNode* JavaParser::ExpressionContext::ASSIGN() {
  return getToken(JavaParser::ASSIGN, 0);
}

tree::TerminalNode* JavaParser::ExpressionContext::ADD_ASSIGN() {
  return getToken(JavaParser::ADD_ASSIGN, 0);
}

tree::TerminalNode* JavaParser::ExpressionContext::SUB_ASSIGN() {
  return getToken(JavaParser::SUB_ASSIGN, 0);
}

tree::TerminalNode* JavaParser::ExpressionContext::MUL_ASSIGN() {
  return getToken(JavaParser::MUL_ASSIGN, 0);
}

tree::TerminalNode* JavaParser::ExpressionContext::DIV_ASSIGN() {
  return getToken(JavaParser::DIV_ASSIGN, 0);
}

tree::TerminalNode* JavaParser::ExpressionContext::AND_ASSIGN() {
  return getToken(JavaParser::AND_ASSIGN, 0);
}

tree::TerminalNode* JavaParser::ExpressionContext::OR_ASSIGN() {
  return getToken(JavaParser::OR_ASSIGN, 0);
}

tree::TerminalNode* JavaParser::ExpressionContext::XOR_ASSIGN() {
  return getToken(JavaParser::XOR_ASSIGN, 0);
}

tree::TerminalNode* JavaParser::ExpressionContext::RSHIFT_ASSIGN() {
  return getToken(JavaParser::RSHIFT_ASSIGN, 0);
}

tree::TerminalNode* JavaParser::ExpressionContext::URSHIFT_ASSIGN() {
  return getToken(JavaParser::URSHIFT_ASSIGN, 0);
}

tree::TerminalNode* JavaParser::ExpressionContext::LSHIFT_ASSIGN() {
  return getToken(JavaParser::LSHIFT_ASSIGN, 0);
}

tree::TerminalNode* JavaParser::ExpressionContext::MOD_ASSIGN() {
  return getToken(JavaParser::MOD_ASSIGN, 0);
}

tree::TerminalNode* JavaParser::ExpressionContext::DOT() {
  return getToken(JavaParser::DOT, 0);
}

tree::TerminalNode* JavaParser::ExpressionContext::THIS() {
  return getToken(JavaParser::THIS, 0);
}

JavaParser::InnerCreatorContext* JavaParser::ExpressionContext::innerCreator() {
  return getRuleContext<JavaParser::InnerCreatorContext>(0);
}

tree::TerminalNode* JavaParser::ExpressionContext::SUPER() {
  return getToken(JavaParser::SUPER, 0);
}

JavaParser::SuperSuffixContext* JavaParser::ExpressionContext::superSuffix() {
  return getRuleContext<JavaParser::SuperSuffixContext>(0);
}

JavaParser::ExplicitGenericInvocationContext* JavaParser::ExpressionContext::explicitGenericInvocation() {
  return getRuleContext<JavaParser::ExplicitGenericInvocationContext>(0);
}

JavaParser::NonWildcardTypeArgumentsContext* JavaParser::ExpressionContext::nonWildcardTypeArguments() {
  return getRuleContext<JavaParser::NonWildcardTypeArgumentsContext>(0);
}

tree::TerminalNode* JavaParser::ExpressionContext::LBRACK() {
  return getToken(JavaParser::LBRACK, 0);
}

tree::TerminalNode* JavaParser::ExpressionContext::RBRACK() {
  return getToken(JavaParser::RBRACK, 0);
}

tree::TerminalNode* JavaParser::ExpressionContext::INSTANCEOF() {
  return getToken(JavaParser::INSTANCEOF, 0);
}


size_t JavaParser::ExpressionContext::getRuleIndex() const {
  return JavaParser::RuleExpression;
}

void JavaParser::ExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpression(this);
}

void JavaParser::ExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpression(this);
}


JavaParser::ExpressionContext* JavaParser::expression() {
   return expression(0);
}

JavaParser::ExpressionContext* JavaParser::expression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  JavaParser::ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, parentState);
  JavaParser::ExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 164;
  enterRecursionRule(_localctx, 164, JavaParser::RuleExpression, precedence);

    size_t _la = 0;

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(1095);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 132, _ctx)) {
    case 1: {
      setState(1065);
      primary();
      break;
    }

    case 2: {
      setState(1066);
      methodCall();
      break;
    }

    case 3: {
      setState(1067);
      match(JavaParser::NEW);
      setState(1068);
      creator();
      break;
    }

    case 4: {
      setState(1069);
      match(JavaParser::LPAREN);
      setState(1070);
      typeType();
      setState(1071);
      match(JavaParser::RPAREN);
      setState(1072);
      expression(21);
      break;
    }

    case 5: {
      setState(1074);
      dynamic_cast<ExpressionContext *>(_localctx)->prefix = _input->LT(1);
      _la = _input->LA(1);
      if (!(((((_la - 83) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 83)) & ((1ULL << (JavaParser::INC - 83))
        | (1ULL << (JavaParser::DEC - 83))
        | (1ULL << (JavaParser::ADD - 83))
        | (1ULL << (JavaParser::SUB - 83)))) != 0))) {
        dynamic_cast<ExpressionContext *>(_localctx)->prefix = _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(1075);
      expression(19);
      break;
    }

    case 6: {
      setState(1076);
      dynamic_cast<ExpressionContext *>(_localctx)->prefix = _input->LT(1);
      _la = _input->LA(1);
      if (!(_la == JavaParser::BANG

      || _la == JavaParser::TILDE)) {
        dynamic_cast<ExpressionContext *>(_localctx)->prefix = _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(1077);
      expression(18);
      break;
    }

    case 7: {
      setState(1078);
      lambdaExpression();
      break;
    }

    case 8: {
      setState(1079);
      typeType();
      setState(1080);
      match(JavaParser::COLONCOLON);
      setState(1086);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case JavaParser::LT:
        case JavaParser::IDENTIFIER: {
          setState(1082);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == JavaParser::LT) {
            setState(1081);
            typeArguments();
          }
          setState(1084);
          match(JavaParser::IDENTIFIER);
          break;
        }

        case JavaParser::NEW: {
          setState(1085);
          match(JavaParser::NEW);
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      break;
    }

    case 9: {
      setState(1088);
      classType();
      setState(1089);
      match(JavaParser::COLONCOLON);
      setState(1091);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == JavaParser::LT) {
        setState(1090);
        typeArguments();
      }
      setState(1093);
      match(JavaParser::NEW);
      break;
    }

    }
    _ctx->stop = _input->LT(-1);
    setState(1177);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 138, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(1175);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 137, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(1097);

          if (!(precpred(_ctx, 17))) throw FailedPredicateException(this, "precpred(_ctx, 17)");
          setState(1098);
          dynamic_cast<ExpressionContext *>(_localctx)->bop = _input->LT(1);
          _la = _input->LA(1);
          if (!(((((_la - 87) & ~ 0x3fULL) == 0) &&
            ((1ULL << (_la - 87)) & ((1ULL << (JavaParser::MUL - 87))
            | (1ULL << (JavaParser::DIV - 87))
            | (1ULL << (JavaParser::MOD - 87)))) != 0))) {
            dynamic_cast<ExpressionContext *>(_localctx)->bop = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(1099);
          expression(18);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(1100);

          if (!(precpred(_ctx, 16))) throw FailedPredicateException(this, "precpred(_ctx, 16)");
          setState(1101);
          dynamic_cast<ExpressionContext *>(_localctx)->bop = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == JavaParser::ADD

          || _la == JavaParser::SUB)) {
            dynamic_cast<ExpressionContext *>(_localctx)->bop = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(1102);
          expression(17);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(1103);

          if (!(precpred(_ctx, 15))) throw FailedPredicateException(this, "precpred(_ctx, 15)");
          setState(1111);
          _errHandler->sync(this);
          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 133, _ctx)) {
          case 1: {
            setState(1104);
            match(JavaParser::LT);
            setState(1105);
            match(JavaParser::LT);
            break;
          }

          case 2: {
            setState(1106);
            match(JavaParser::GT);
            setState(1107);
            match(JavaParser::GT);
            setState(1108);
            match(JavaParser::GT);
            break;
          }

          case 3: {
            setState(1109);
            match(JavaParser::GT);
            setState(1110);
            match(JavaParser::GT);
            break;
          }

          }
          setState(1113);
          expression(16);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(1114);

          if (!(precpred(_ctx, 14))) throw FailedPredicateException(this, "precpred(_ctx, 14)");
          setState(1115);
          dynamic_cast<ExpressionContext *>(_localctx)->bop = _input->LT(1);
          _la = _input->LA(1);
          if (!(((((_la - 71) & ~ 0x3fULL) == 0) &&
            ((1ULL << (_la - 71)) & ((1ULL << (JavaParser::GT - 71))
            | (1ULL << (JavaParser::LT - 71))
            | (1ULL << (JavaParser::LE - 71))
            | (1ULL << (JavaParser::GE - 71)))) != 0))) {
            dynamic_cast<ExpressionContext *>(_localctx)->bop = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(1116);
          expression(15);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(1117);

          if (!(precpred(_ctx, 12))) throw FailedPredicateException(this, "precpred(_ctx, 12)");
          setState(1118);
          dynamic_cast<ExpressionContext *>(_localctx)->bop = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == JavaParser::EQUAL

          || _la == JavaParser::NOTEQUAL)) {
            dynamic_cast<ExpressionContext *>(_localctx)->bop = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(1119);
          expression(13);
          break;
        }

        case 6: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(1120);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(1121);
          dynamic_cast<ExpressionContext *>(_localctx)->bop = match(JavaParser::BITAND);
          setState(1122);
          expression(12);
          break;
        }

        case 7: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(1123);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(1124);
          dynamic_cast<ExpressionContext *>(_localctx)->bop = match(JavaParser::CARET);
          setState(1125);
          expression(11);
          break;
        }

        case 8: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(1126);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(1127);
          dynamic_cast<ExpressionContext *>(_localctx)->bop = match(JavaParser::BITOR);
          setState(1128);
          expression(10);
          break;
        }

        case 9: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(1129);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(1130);
          dynamic_cast<ExpressionContext *>(_localctx)->bop = match(JavaParser::AND);
          setState(1131);
          expression(9);
          break;
        }

        case 10: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(1132);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(1133);
          dynamic_cast<ExpressionContext *>(_localctx)->bop = match(JavaParser::OR);
          setState(1134);
          expression(8);
          break;
        }

        case 11: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(1135);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(1136);
          dynamic_cast<ExpressionContext *>(_localctx)->bop = match(JavaParser::QUESTION);
          setState(1137);
          expression(0);
          setState(1138);
          match(JavaParser::COLON);
          setState(1139);
          expression(7);
          break;
        }

        case 12: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(1141);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(1142);
          dynamic_cast<ExpressionContext *>(_localctx)->bop = _input->LT(1);
          _la = _input->LA(1);
          if (!(((((_la - 70) & ~ 0x3fULL) == 0) &&
            ((1ULL << (_la - 70)) & ((1ULL << (JavaParser::ASSIGN - 70))
            | (1ULL << (JavaParser::ADD_ASSIGN - 70))
            | (1ULL << (JavaParser::SUB_ASSIGN - 70))
            | (1ULL << (JavaParser::MUL_ASSIGN - 70))
            | (1ULL << (JavaParser::DIV_ASSIGN - 70))
            | (1ULL << (JavaParser::AND_ASSIGN - 70))
            | (1ULL << (JavaParser::OR_ASSIGN - 70))
            | (1ULL << (JavaParser::XOR_ASSIGN - 70))
            | (1ULL << (JavaParser::MOD_ASSIGN - 70))
            | (1ULL << (JavaParser::LSHIFT_ASSIGN - 70))
            | (1ULL << (JavaParser::RSHIFT_ASSIGN - 70))
            | (1ULL << (JavaParser::URSHIFT_ASSIGN - 70)))) != 0))) {
            dynamic_cast<ExpressionContext *>(_localctx)->bop = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(1143);
          expression(5);
          break;
        }

        case 13: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(1144);

          if (!(precpred(_ctx, 25))) throw FailedPredicateException(this, "precpred(_ctx, 25)");
          setState(1145);
          dynamic_cast<ExpressionContext *>(_localctx)->bop = match(JavaParser::DOT);
          setState(1157);
          _errHandler->sync(this);
          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 135, _ctx)) {
          case 1: {
            setState(1146);
            match(JavaParser::IDENTIFIER);
            break;
          }

          case 2: {
            setState(1147);
            methodCall();
            break;
          }

          case 3: {
            setState(1148);
            match(JavaParser::THIS);
            break;
          }

          case 4: {
            setState(1149);
            match(JavaParser::NEW);
            setState(1151);
            _errHandler->sync(this);

            _la = _input->LA(1);
            if (_la == JavaParser::LT) {
              setState(1150);
              nonWildcardTypeArguments();
            }
            setState(1153);
            innerCreator();
            break;
          }

          case 5: {
            setState(1154);
            match(JavaParser::SUPER);
            setState(1155);
            superSuffix();
            break;
          }

          case 6: {
            setState(1156);
            explicitGenericInvocation();
            break;
          }

          }
          break;
        }

        case 14: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(1159);

          if (!(precpred(_ctx, 24))) throw FailedPredicateException(this, "precpred(_ctx, 24)");
          setState(1160);
          match(JavaParser::LBRACK);
          setState(1161);
          expression(0);
          setState(1162);
          match(JavaParser::RBRACK);
          break;
        }

        case 15: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(1164);

          if (!(precpred(_ctx, 20))) throw FailedPredicateException(this, "precpred(_ctx, 20)");
          setState(1165);
          dynamic_cast<ExpressionContext *>(_localctx)->postfix = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == JavaParser::INC

          || _la == JavaParser::DEC)) {
            dynamic_cast<ExpressionContext *>(_localctx)->postfix = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          break;
        }

        case 16: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(1166);

          if (!(precpred(_ctx, 13))) throw FailedPredicateException(this, "precpred(_ctx, 13)");
          setState(1167);
          dynamic_cast<ExpressionContext *>(_localctx)->bop = match(JavaParser::INSTANCEOF);
          setState(1168);
          typeType();
          break;
        }

        case 17: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(1169);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(1170);
          match(JavaParser::COLONCOLON);
          setState(1172);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == JavaParser::LT) {
            setState(1171);
            typeArguments();
          }
          setState(1174);
          match(JavaParser::IDENTIFIER);
          break;
        }

        } 
      }
      setState(1179);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 138, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- LambdaExpressionContext ------------------------------------------------------------------

JavaParser::LambdaExpressionContext::LambdaExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaParser::LambdaParametersContext* JavaParser::LambdaExpressionContext::lambdaParameters() {
  return getRuleContext<JavaParser::LambdaParametersContext>(0);
}

tree::TerminalNode* JavaParser::LambdaExpressionContext::ARROW() {
  return getToken(JavaParser::ARROW, 0);
}

JavaParser::LambdaBodyContext* JavaParser::LambdaExpressionContext::lambdaBody() {
  return getRuleContext<JavaParser::LambdaBodyContext>(0);
}


size_t JavaParser::LambdaExpressionContext::getRuleIndex() const {
  return JavaParser::RuleLambdaExpression;
}

void JavaParser::LambdaExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLambdaExpression(this);
}

void JavaParser::LambdaExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLambdaExpression(this);
}

JavaParser::LambdaExpressionContext* JavaParser::lambdaExpression() {
  LambdaExpressionContext *_localctx = _tracker.createInstance<LambdaExpressionContext>(_ctx, getState());
  enterRule(_localctx, 166, JavaParser::RuleLambdaExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1180);
    lambdaParameters();
    setState(1181);
    match(JavaParser::ARROW);
    setState(1182);
    lambdaBody();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LambdaParametersContext ------------------------------------------------------------------

JavaParser::LambdaParametersContext::LambdaParametersContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> JavaParser::LambdaParametersContext::IDENTIFIER() {
  return getTokens(JavaParser::IDENTIFIER);
}

tree::TerminalNode* JavaParser::LambdaParametersContext::IDENTIFIER(size_t i) {
  return getToken(JavaParser::IDENTIFIER, i);
}

tree::TerminalNode* JavaParser::LambdaParametersContext::LPAREN() {
  return getToken(JavaParser::LPAREN, 0);
}

tree::TerminalNode* JavaParser::LambdaParametersContext::RPAREN() {
  return getToken(JavaParser::RPAREN, 0);
}

JavaParser::FormalParameterListContext* JavaParser::LambdaParametersContext::formalParameterList() {
  return getRuleContext<JavaParser::FormalParameterListContext>(0);
}

std::vector<tree::TerminalNode *> JavaParser::LambdaParametersContext::COMMA() {
  return getTokens(JavaParser::COMMA);
}

tree::TerminalNode* JavaParser::LambdaParametersContext::COMMA(size_t i) {
  return getToken(JavaParser::COMMA, i);
}


size_t JavaParser::LambdaParametersContext::getRuleIndex() const {
  return JavaParser::RuleLambdaParameters;
}

void JavaParser::LambdaParametersContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLambdaParameters(this);
}

void JavaParser::LambdaParametersContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLambdaParameters(this);
}

JavaParser::LambdaParametersContext* JavaParser::lambdaParameters() {
  LambdaParametersContext *_localctx = _tracker.createInstance<LambdaParametersContext>(_ctx, getState());
  enterRule(_localctx, 168, JavaParser::RuleLambdaParameters);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(1200);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 141, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(1184);
      match(JavaParser::IDENTIFIER);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(1185);
      match(JavaParser::LPAREN);
      setState(1187);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << JavaParser::BOOLEAN)
        | (1ULL << JavaParser::BYTE)
        | (1ULL << JavaParser::CHAR)
        | (1ULL << JavaParser::DOUBLE)
        | (1ULL << JavaParser::FINAL)
        | (1ULL << JavaParser::FLOAT)
        | (1ULL << JavaParser::INT)
        | (1ULL << JavaParser::LONG)
        | (1ULL << JavaParser::SHORT))) != 0) || _la == JavaParser::AT

      || _la == JavaParser::IDENTIFIER) {
        setState(1186);
        formalParameterList();
      }
      setState(1189);
      match(JavaParser::RPAREN);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(1190);
      match(JavaParser::LPAREN);
      setState(1191);
      match(JavaParser::IDENTIFIER);
      setState(1196);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == JavaParser::COMMA) {
        setState(1192);
        match(JavaParser::COMMA);
        setState(1193);
        match(JavaParser::IDENTIFIER);
        setState(1198);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(1199);
      match(JavaParser::RPAREN);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LambdaBodyContext ------------------------------------------------------------------

JavaParser::LambdaBodyContext::LambdaBodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaParser::ExpressionContext* JavaParser::LambdaBodyContext::expression() {
  return getRuleContext<JavaParser::ExpressionContext>(0);
}

JavaParser::BlockContext* JavaParser::LambdaBodyContext::block() {
  return getRuleContext<JavaParser::BlockContext>(0);
}


size_t JavaParser::LambdaBodyContext::getRuleIndex() const {
  return JavaParser::RuleLambdaBody;
}

void JavaParser::LambdaBodyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLambdaBody(this);
}

void JavaParser::LambdaBodyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLambdaBody(this);
}

JavaParser::LambdaBodyContext* JavaParser::lambdaBody() {
  LambdaBodyContext *_localctx = _tracker.createInstance<LambdaBodyContext>(_ctx, getState());
  enterRule(_localctx, 170, JavaParser::RuleLambdaBody);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(1204);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaParser::BOOLEAN:
      case JavaParser::BYTE:
      case JavaParser::CHAR:
      case JavaParser::DOUBLE:
      case JavaParser::FLOAT:
      case JavaParser::INT:
      case JavaParser::LONG:
      case JavaParser::NEW:
      case JavaParser::SHORT:
      case JavaParser::SUPER:
      case JavaParser::THIS:
      case JavaParser::VOID:
      case JavaParser::DECIMAL_LITERAL:
      case JavaParser::HEX_LITERAL:
      case JavaParser::OCT_LITERAL:
      case JavaParser::BINARY_LITERAL:
      case JavaParser::FLOAT_LITERAL:
      case JavaParser::HEX_FLOAT_LITERAL:
      case JavaParser::BOOL_LITERAL:
      case JavaParser::CHAR_LITERAL:
      case JavaParser::STRING_LITERAL:
      case JavaParser::NULL_LITERAL:
      case JavaParser::LPAREN:
      case JavaParser::LT:
      case JavaParser::BANG:
      case JavaParser::TILDE:
      case JavaParser::INC:
      case JavaParser::DEC:
      case JavaParser::ADD:
      case JavaParser::SUB:
      case JavaParser::AT:
      case JavaParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(1202);
        expression(0);
        break;
      }

      case JavaParser::LBRACE: {
        enterOuterAlt(_localctx, 2);
        setState(1203);
        block();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrimaryContext ------------------------------------------------------------------

JavaParser::PrimaryContext::PrimaryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaParser::PrimaryContext::LPAREN() {
  return getToken(JavaParser::LPAREN, 0);
}

JavaParser::ExpressionContext* JavaParser::PrimaryContext::expression() {
  return getRuleContext<JavaParser::ExpressionContext>(0);
}

tree::TerminalNode* JavaParser::PrimaryContext::RPAREN() {
  return getToken(JavaParser::RPAREN, 0);
}

tree::TerminalNode* JavaParser::PrimaryContext::THIS() {
  return getToken(JavaParser::THIS, 0);
}

tree::TerminalNode* JavaParser::PrimaryContext::SUPER() {
  return getToken(JavaParser::SUPER, 0);
}

JavaParser::LiteralContext* JavaParser::PrimaryContext::literal() {
  return getRuleContext<JavaParser::LiteralContext>(0);
}

tree::TerminalNode* JavaParser::PrimaryContext::IDENTIFIER() {
  return getToken(JavaParser::IDENTIFIER, 0);
}

JavaParser::TypeTypeOrVoidContext* JavaParser::PrimaryContext::typeTypeOrVoid() {
  return getRuleContext<JavaParser::TypeTypeOrVoidContext>(0);
}

tree::TerminalNode* JavaParser::PrimaryContext::DOT() {
  return getToken(JavaParser::DOT, 0);
}

tree::TerminalNode* JavaParser::PrimaryContext::CLASS() {
  return getToken(JavaParser::CLASS, 0);
}

JavaParser::NonWildcardTypeArgumentsContext* JavaParser::PrimaryContext::nonWildcardTypeArguments() {
  return getRuleContext<JavaParser::NonWildcardTypeArgumentsContext>(0);
}

JavaParser::ExplicitGenericInvocationSuffixContext* JavaParser::PrimaryContext::explicitGenericInvocationSuffix() {
  return getRuleContext<JavaParser::ExplicitGenericInvocationSuffixContext>(0);
}

JavaParser::ArgumentsContext* JavaParser::PrimaryContext::arguments() {
  return getRuleContext<JavaParser::ArgumentsContext>(0);
}


size_t JavaParser::PrimaryContext::getRuleIndex() const {
  return JavaParser::RulePrimary;
}

void JavaParser::PrimaryContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPrimary(this);
}

void JavaParser::PrimaryContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPrimary(this);
}

JavaParser::PrimaryContext* JavaParser::primary() {
  PrimaryContext *_localctx = _tracker.createInstance<PrimaryContext>(_ctx, getState());
  enterRule(_localctx, 172, JavaParser::RulePrimary);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(1224);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 144, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(1206);
      match(JavaParser::LPAREN);
      setState(1207);
      expression(0);
      setState(1208);
      match(JavaParser::RPAREN);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(1210);
      match(JavaParser::THIS);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(1211);
      match(JavaParser::SUPER);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(1212);
      literal();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(1213);
      match(JavaParser::IDENTIFIER);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(1214);
      typeTypeOrVoid();
      setState(1215);
      match(JavaParser::DOT);
      setState(1216);
      match(JavaParser::CLASS);
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(1218);
      nonWildcardTypeArguments();
      setState(1222);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case JavaParser::SUPER:
        case JavaParser::IDENTIFIER: {
          setState(1219);
          explicitGenericInvocationSuffix();
          break;
        }

        case JavaParser::THIS: {
          setState(1220);
          match(JavaParser::THIS);
          setState(1221);
          arguments();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ClassTypeContext ------------------------------------------------------------------

JavaParser::ClassTypeContext::ClassTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaParser::ClassTypeContext::IDENTIFIER() {
  return getToken(JavaParser::IDENTIFIER, 0);
}

JavaParser::ClassOrInterfaceTypeContext* JavaParser::ClassTypeContext::classOrInterfaceType() {
  return getRuleContext<JavaParser::ClassOrInterfaceTypeContext>(0);
}

tree::TerminalNode* JavaParser::ClassTypeContext::DOT() {
  return getToken(JavaParser::DOT, 0);
}

std::vector<JavaParser::AnnotationContext *> JavaParser::ClassTypeContext::annotation() {
  return getRuleContexts<JavaParser::AnnotationContext>();
}

JavaParser::AnnotationContext* JavaParser::ClassTypeContext::annotation(size_t i) {
  return getRuleContext<JavaParser::AnnotationContext>(i);
}

JavaParser::TypeArgumentsContext* JavaParser::ClassTypeContext::typeArguments() {
  return getRuleContext<JavaParser::TypeArgumentsContext>(0);
}


size_t JavaParser::ClassTypeContext::getRuleIndex() const {
  return JavaParser::RuleClassType;
}

void JavaParser::ClassTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterClassType(this);
}

void JavaParser::ClassTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitClassType(this);
}

JavaParser::ClassTypeContext* JavaParser::classType() {
  ClassTypeContext *_localctx = _tracker.createInstance<ClassTypeContext>(_ctx, getState());
  enterRule(_localctx, 174, JavaParser::RuleClassType);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1229);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 145, _ctx)) {
    case 1: {
      setState(1226);
      classOrInterfaceType();
      setState(1227);
      match(JavaParser::DOT);
      break;
    }

    }
    setState(1234);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == JavaParser::AT) {
      setState(1231);
      annotation();
      setState(1236);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(1237);
    match(JavaParser::IDENTIFIER);
    setState(1239);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaParser::LT) {
      setState(1238);
      typeArguments();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CreatorContext ------------------------------------------------------------------

JavaParser::CreatorContext::CreatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaParser::NonWildcardTypeArgumentsContext* JavaParser::CreatorContext::nonWildcardTypeArguments() {
  return getRuleContext<JavaParser::NonWildcardTypeArgumentsContext>(0);
}

JavaParser::CreatedNameContext* JavaParser::CreatorContext::createdName() {
  return getRuleContext<JavaParser::CreatedNameContext>(0);
}

JavaParser::ClassCreatorRestContext* JavaParser::CreatorContext::classCreatorRest() {
  return getRuleContext<JavaParser::ClassCreatorRestContext>(0);
}

JavaParser::ArrayCreatorRestContext* JavaParser::CreatorContext::arrayCreatorRest() {
  return getRuleContext<JavaParser::ArrayCreatorRestContext>(0);
}


size_t JavaParser::CreatorContext::getRuleIndex() const {
  return JavaParser::RuleCreator;
}

void JavaParser::CreatorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCreator(this);
}

void JavaParser::CreatorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCreator(this);
}

JavaParser::CreatorContext* JavaParser::creator() {
  CreatorContext *_localctx = _tracker.createInstance<CreatorContext>(_ctx, getState());
  enterRule(_localctx, 176, JavaParser::RuleCreator);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(1250);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaParser::LT: {
        enterOuterAlt(_localctx, 1);
        setState(1241);
        nonWildcardTypeArguments();
        setState(1242);
        createdName();
        setState(1243);
        classCreatorRest();
        break;
      }

      case JavaParser::BOOLEAN:
      case JavaParser::BYTE:
      case JavaParser::CHAR:
      case JavaParser::DOUBLE:
      case JavaParser::FLOAT:
      case JavaParser::INT:
      case JavaParser::LONG:
      case JavaParser::SHORT:
      case JavaParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 2);
        setState(1245);
        createdName();
        setState(1248);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case JavaParser::LBRACK: {
            setState(1246);
            arrayCreatorRest();
            break;
          }

          case JavaParser::LPAREN: {
            setState(1247);
            classCreatorRest();
            break;
          }

        default:
          throw NoViableAltException(this);
        }
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CreatedNameContext ------------------------------------------------------------------

JavaParser::CreatedNameContext::CreatedNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> JavaParser::CreatedNameContext::IDENTIFIER() {
  return getTokens(JavaParser::IDENTIFIER);
}

tree::TerminalNode* JavaParser::CreatedNameContext::IDENTIFIER(size_t i) {
  return getToken(JavaParser::IDENTIFIER, i);
}

std::vector<JavaParser::TypeArgumentsOrDiamondContext *> JavaParser::CreatedNameContext::typeArgumentsOrDiamond() {
  return getRuleContexts<JavaParser::TypeArgumentsOrDiamondContext>();
}

JavaParser::TypeArgumentsOrDiamondContext* JavaParser::CreatedNameContext::typeArgumentsOrDiamond(size_t i) {
  return getRuleContext<JavaParser::TypeArgumentsOrDiamondContext>(i);
}

std::vector<tree::TerminalNode *> JavaParser::CreatedNameContext::DOT() {
  return getTokens(JavaParser::DOT);
}

tree::TerminalNode* JavaParser::CreatedNameContext::DOT(size_t i) {
  return getToken(JavaParser::DOT, i);
}

JavaParser::PrimitiveTypeContext* JavaParser::CreatedNameContext::primitiveType() {
  return getRuleContext<JavaParser::PrimitiveTypeContext>(0);
}


size_t JavaParser::CreatedNameContext::getRuleIndex() const {
  return JavaParser::RuleCreatedName;
}

void JavaParser::CreatedNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCreatedName(this);
}

void JavaParser::CreatedNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCreatedName(this);
}

JavaParser::CreatedNameContext* JavaParser::createdName() {
  CreatedNameContext *_localctx = _tracker.createInstance<CreatedNameContext>(_ctx, getState());
  enterRule(_localctx, 178, JavaParser::RuleCreatedName);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(1267);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(1252);
        match(JavaParser::IDENTIFIER);
        setState(1254);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == JavaParser::LT) {
          setState(1253);
          typeArgumentsOrDiamond();
        }
        setState(1263);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == JavaParser::DOT) {
          setState(1256);
          match(JavaParser::DOT);
          setState(1257);
          match(JavaParser::IDENTIFIER);
          setState(1259);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == JavaParser::LT) {
            setState(1258);
            typeArgumentsOrDiamond();
          }
          setState(1265);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        break;
      }

      case JavaParser::BOOLEAN:
      case JavaParser::BYTE:
      case JavaParser::CHAR:
      case JavaParser::DOUBLE:
      case JavaParser::FLOAT:
      case JavaParser::INT:
      case JavaParser::LONG:
      case JavaParser::SHORT: {
        enterOuterAlt(_localctx, 2);
        setState(1266);
        primitiveType();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InnerCreatorContext ------------------------------------------------------------------

JavaParser::InnerCreatorContext::InnerCreatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaParser::InnerCreatorContext::IDENTIFIER() {
  return getToken(JavaParser::IDENTIFIER, 0);
}

JavaParser::ClassCreatorRestContext* JavaParser::InnerCreatorContext::classCreatorRest() {
  return getRuleContext<JavaParser::ClassCreatorRestContext>(0);
}

JavaParser::NonWildcardTypeArgumentsOrDiamondContext* JavaParser::InnerCreatorContext::nonWildcardTypeArgumentsOrDiamond() {
  return getRuleContext<JavaParser::NonWildcardTypeArgumentsOrDiamondContext>(0);
}


size_t JavaParser::InnerCreatorContext::getRuleIndex() const {
  return JavaParser::RuleInnerCreator;
}

void JavaParser::InnerCreatorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInnerCreator(this);
}

void JavaParser::InnerCreatorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInnerCreator(this);
}

JavaParser::InnerCreatorContext* JavaParser::innerCreator() {
  InnerCreatorContext *_localctx = _tracker.createInstance<InnerCreatorContext>(_ctx, getState());
  enterRule(_localctx, 180, JavaParser::RuleInnerCreator);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1269);
    match(JavaParser::IDENTIFIER);
    setState(1271);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaParser::LT) {
      setState(1270);
      nonWildcardTypeArgumentsOrDiamond();
    }
    setState(1273);
    classCreatorRest();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrayCreatorRestContext ------------------------------------------------------------------

JavaParser::ArrayCreatorRestContext::ArrayCreatorRestContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> JavaParser::ArrayCreatorRestContext::LBRACK() {
  return getTokens(JavaParser::LBRACK);
}

tree::TerminalNode* JavaParser::ArrayCreatorRestContext::LBRACK(size_t i) {
  return getToken(JavaParser::LBRACK, i);
}

std::vector<tree::TerminalNode *> JavaParser::ArrayCreatorRestContext::RBRACK() {
  return getTokens(JavaParser::RBRACK);
}

tree::TerminalNode* JavaParser::ArrayCreatorRestContext::RBRACK(size_t i) {
  return getToken(JavaParser::RBRACK, i);
}

JavaParser::ArrayInitializerContext* JavaParser::ArrayCreatorRestContext::arrayInitializer() {
  return getRuleContext<JavaParser::ArrayInitializerContext>(0);
}

std::vector<JavaParser::ExpressionContext *> JavaParser::ArrayCreatorRestContext::expression() {
  return getRuleContexts<JavaParser::ExpressionContext>();
}

JavaParser::ExpressionContext* JavaParser::ArrayCreatorRestContext::expression(size_t i) {
  return getRuleContext<JavaParser::ExpressionContext>(i);
}


size_t JavaParser::ArrayCreatorRestContext::getRuleIndex() const {
  return JavaParser::RuleArrayCreatorRest;
}

void JavaParser::ArrayCreatorRestContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrayCreatorRest(this);
}

void JavaParser::ArrayCreatorRestContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrayCreatorRest(this);
}

JavaParser::ArrayCreatorRestContext* JavaParser::arrayCreatorRest() {
  ArrayCreatorRestContext *_localctx = _tracker.createInstance<ArrayCreatorRestContext>(_ctx, getState());
  enterRule(_localctx, 182, JavaParser::RuleArrayCreatorRest);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(1275);
    match(JavaParser::LBRACK);
    setState(1303);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaParser::RBRACK: {
        setState(1276);
        match(JavaParser::RBRACK);
        setState(1281);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == JavaParser::LBRACK) {
          setState(1277);
          match(JavaParser::LBRACK);
          setState(1278);
          match(JavaParser::RBRACK);
          setState(1283);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(1284);
        arrayInitializer();
        break;
      }

      case JavaParser::BOOLEAN:
      case JavaParser::BYTE:
      case JavaParser::CHAR:
      case JavaParser::DOUBLE:
      case JavaParser::FLOAT:
      case JavaParser::INT:
      case JavaParser::LONG:
      case JavaParser::NEW:
      case JavaParser::SHORT:
      case JavaParser::SUPER:
      case JavaParser::THIS:
      case JavaParser::VOID:
      case JavaParser::DECIMAL_LITERAL:
      case JavaParser::HEX_LITERAL:
      case JavaParser::OCT_LITERAL:
      case JavaParser::BINARY_LITERAL:
      case JavaParser::FLOAT_LITERAL:
      case JavaParser::HEX_FLOAT_LITERAL:
      case JavaParser::BOOL_LITERAL:
      case JavaParser::CHAR_LITERAL:
      case JavaParser::STRING_LITERAL:
      case JavaParser::NULL_LITERAL:
      case JavaParser::LPAREN:
      case JavaParser::LT:
      case JavaParser::BANG:
      case JavaParser::TILDE:
      case JavaParser::INC:
      case JavaParser::DEC:
      case JavaParser::ADD:
      case JavaParser::SUB:
      case JavaParser::AT:
      case JavaParser::IDENTIFIER: {
        setState(1285);
        expression(0);
        setState(1286);
        match(JavaParser::RBRACK);
        setState(1293);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 156, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
          if (alt == 1) {
            setState(1287);
            match(JavaParser::LBRACK);
            setState(1288);
            expression(0);
            setState(1289);
            match(JavaParser::RBRACK); 
          }
          setState(1295);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 156, _ctx);
        }
        setState(1300);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 157, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
          if (alt == 1) {
            setState(1296);
            match(JavaParser::LBRACK);
            setState(1297);
            match(JavaParser::RBRACK); 
          }
          setState(1302);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 157, _ctx);
        }
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ClassCreatorRestContext ------------------------------------------------------------------

JavaParser::ClassCreatorRestContext::ClassCreatorRestContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaParser::ArgumentsContext* JavaParser::ClassCreatorRestContext::arguments() {
  return getRuleContext<JavaParser::ArgumentsContext>(0);
}

JavaParser::ClassBodyContext* JavaParser::ClassCreatorRestContext::classBody() {
  return getRuleContext<JavaParser::ClassBodyContext>(0);
}


size_t JavaParser::ClassCreatorRestContext::getRuleIndex() const {
  return JavaParser::RuleClassCreatorRest;
}

void JavaParser::ClassCreatorRestContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterClassCreatorRest(this);
}

void JavaParser::ClassCreatorRestContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitClassCreatorRest(this);
}

JavaParser::ClassCreatorRestContext* JavaParser::classCreatorRest() {
  ClassCreatorRestContext *_localctx = _tracker.createInstance<ClassCreatorRestContext>(_ctx, getState());
  enterRule(_localctx, 184, JavaParser::RuleClassCreatorRest);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1305);
    arguments();
    setState(1307);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 159, _ctx)) {
    case 1: {
      setState(1306);
      classBody();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExplicitGenericInvocationContext ------------------------------------------------------------------

JavaParser::ExplicitGenericInvocationContext::ExplicitGenericInvocationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaParser::NonWildcardTypeArgumentsContext* JavaParser::ExplicitGenericInvocationContext::nonWildcardTypeArguments() {
  return getRuleContext<JavaParser::NonWildcardTypeArgumentsContext>(0);
}

JavaParser::ExplicitGenericInvocationSuffixContext* JavaParser::ExplicitGenericInvocationContext::explicitGenericInvocationSuffix() {
  return getRuleContext<JavaParser::ExplicitGenericInvocationSuffixContext>(0);
}


size_t JavaParser::ExplicitGenericInvocationContext::getRuleIndex() const {
  return JavaParser::RuleExplicitGenericInvocation;
}

void JavaParser::ExplicitGenericInvocationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExplicitGenericInvocation(this);
}

void JavaParser::ExplicitGenericInvocationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExplicitGenericInvocation(this);
}

JavaParser::ExplicitGenericInvocationContext* JavaParser::explicitGenericInvocation() {
  ExplicitGenericInvocationContext *_localctx = _tracker.createInstance<ExplicitGenericInvocationContext>(_ctx, getState());
  enterRule(_localctx, 186, JavaParser::RuleExplicitGenericInvocation);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1309);
    nonWildcardTypeArguments();
    setState(1310);
    explicitGenericInvocationSuffix();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeArgumentsOrDiamondContext ------------------------------------------------------------------

JavaParser::TypeArgumentsOrDiamondContext::TypeArgumentsOrDiamondContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaParser::TypeArgumentsOrDiamondContext::LT() {
  return getToken(JavaParser::LT, 0);
}

tree::TerminalNode* JavaParser::TypeArgumentsOrDiamondContext::GT() {
  return getToken(JavaParser::GT, 0);
}

JavaParser::TypeArgumentsContext* JavaParser::TypeArgumentsOrDiamondContext::typeArguments() {
  return getRuleContext<JavaParser::TypeArgumentsContext>(0);
}


size_t JavaParser::TypeArgumentsOrDiamondContext::getRuleIndex() const {
  return JavaParser::RuleTypeArgumentsOrDiamond;
}

void JavaParser::TypeArgumentsOrDiamondContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeArgumentsOrDiamond(this);
}

void JavaParser::TypeArgumentsOrDiamondContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeArgumentsOrDiamond(this);
}

JavaParser::TypeArgumentsOrDiamondContext* JavaParser::typeArgumentsOrDiamond() {
  TypeArgumentsOrDiamondContext *_localctx = _tracker.createInstance<TypeArgumentsOrDiamondContext>(_ctx, getState());
  enterRule(_localctx, 188, JavaParser::RuleTypeArgumentsOrDiamond);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(1315);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 160, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(1312);
      match(JavaParser::LT);
      setState(1313);
      match(JavaParser::GT);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(1314);
      typeArguments();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NonWildcardTypeArgumentsOrDiamondContext ------------------------------------------------------------------

JavaParser::NonWildcardTypeArgumentsOrDiamondContext::NonWildcardTypeArgumentsOrDiamondContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaParser::NonWildcardTypeArgumentsOrDiamondContext::LT() {
  return getToken(JavaParser::LT, 0);
}

tree::TerminalNode* JavaParser::NonWildcardTypeArgumentsOrDiamondContext::GT() {
  return getToken(JavaParser::GT, 0);
}

JavaParser::NonWildcardTypeArgumentsContext* JavaParser::NonWildcardTypeArgumentsOrDiamondContext::nonWildcardTypeArguments() {
  return getRuleContext<JavaParser::NonWildcardTypeArgumentsContext>(0);
}


size_t JavaParser::NonWildcardTypeArgumentsOrDiamondContext::getRuleIndex() const {
  return JavaParser::RuleNonWildcardTypeArgumentsOrDiamond;
}

void JavaParser::NonWildcardTypeArgumentsOrDiamondContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNonWildcardTypeArgumentsOrDiamond(this);
}

void JavaParser::NonWildcardTypeArgumentsOrDiamondContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNonWildcardTypeArgumentsOrDiamond(this);
}

JavaParser::NonWildcardTypeArgumentsOrDiamondContext* JavaParser::nonWildcardTypeArgumentsOrDiamond() {
  NonWildcardTypeArgumentsOrDiamondContext *_localctx = _tracker.createInstance<NonWildcardTypeArgumentsOrDiamondContext>(_ctx, getState());
  enterRule(_localctx, 190, JavaParser::RuleNonWildcardTypeArgumentsOrDiamond);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(1320);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 161, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(1317);
      match(JavaParser::LT);
      setState(1318);
      match(JavaParser::GT);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(1319);
      nonWildcardTypeArguments();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NonWildcardTypeArgumentsContext ------------------------------------------------------------------

JavaParser::NonWildcardTypeArgumentsContext::NonWildcardTypeArgumentsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaParser::NonWildcardTypeArgumentsContext::LT() {
  return getToken(JavaParser::LT, 0);
}

JavaParser::TypeListContext* JavaParser::NonWildcardTypeArgumentsContext::typeList() {
  return getRuleContext<JavaParser::TypeListContext>(0);
}

tree::TerminalNode* JavaParser::NonWildcardTypeArgumentsContext::GT() {
  return getToken(JavaParser::GT, 0);
}


size_t JavaParser::NonWildcardTypeArgumentsContext::getRuleIndex() const {
  return JavaParser::RuleNonWildcardTypeArguments;
}

void JavaParser::NonWildcardTypeArgumentsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNonWildcardTypeArguments(this);
}

void JavaParser::NonWildcardTypeArgumentsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNonWildcardTypeArguments(this);
}

JavaParser::NonWildcardTypeArgumentsContext* JavaParser::nonWildcardTypeArguments() {
  NonWildcardTypeArgumentsContext *_localctx = _tracker.createInstance<NonWildcardTypeArgumentsContext>(_ctx, getState());
  enterRule(_localctx, 192, JavaParser::RuleNonWildcardTypeArguments);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1322);
    match(JavaParser::LT);
    setState(1323);
    typeList();
    setState(1324);
    match(JavaParser::GT);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeListContext ------------------------------------------------------------------

JavaParser::TypeListContext::TypeListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<JavaParser::TypeTypeContext *> JavaParser::TypeListContext::typeType() {
  return getRuleContexts<JavaParser::TypeTypeContext>();
}

JavaParser::TypeTypeContext* JavaParser::TypeListContext::typeType(size_t i) {
  return getRuleContext<JavaParser::TypeTypeContext>(i);
}

std::vector<tree::TerminalNode *> JavaParser::TypeListContext::COMMA() {
  return getTokens(JavaParser::COMMA);
}

tree::TerminalNode* JavaParser::TypeListContext::COMMA(size_t i) {
  return getToken(JavaParser::COMMA, i);
}


size_t JavaParser::TypeListContext::getRuleIndex() const {
  return JavaParser::RuleTypeList;
}

void JavaParser::TypeListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeList(this);
}

void JavaParser::TypeListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeList(this);
}

JavaParser::TypeListContext* JavaParser::typeList() {
  TypeListContext *_localctx = _tracker.createInstance<TypeListContext>(_ctx, getState());
  enterRule(_localctx, 194, JavaParser::RuleTypeList);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1326);
    typeType();
    setState(1331);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == JavaParser::COMMA) {
      setState(1327);
      match(JavaParser::COMMA);
      setState(1328);
      typeType();
      setState(1333);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeTypeContext ------------------------------------------------------------------

JavaParser::TypeTypeContext::TypeTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaParser::ClassOrInterfaceTypeContext* JavaParser::TypeTypeContext::classOrInterfaceType() {
  return getRuleContext<JavaParser::ClassOrInterfaceTypeContext>(0);
}

JavaParser::PrimitiveTypeContext* JavaParser::TypeTypeContext::primitiveType() {
  return getRuleContext<JavaParser::PrimitiveTypeContext>(0);
}

JavaParser::AnnotationContext* JavaParser::TypeTypeContext::annotation() {
  return getRuleContext<JavaParser::AnnotationContext>(0);
}

std::vector<tree::TerminalNode *> JavaParser::TypeTypeContext::LBRACK() {
  return getTokens(JavaParser::LBRACK);
}

tree::TerminalNode* JavaParser::TypeTypeContext::LBRACK(size_t i) {
  return getToken(JavaParser::LBRACK, i);
}

std::vector<tree::TerminalNode *> JavaParser::TypeTypeContext::RBRACK() {
  return getTokens(JavaParser::RBRACK);
}

tree::TerminalNode* JavaParser::TypeTypeContext::RBRACK(size_t i) {
  return getToken(JavaParser::RBRACK, i);
}


size_t JavaParser::TypeTypeContext::getRuleIndex() const {
  return JavaParser::RuleTypeType;
}

void JavaParser::TypeTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeType(this);
}

void JavaParser::TypeTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeType(this);
}

JavaParser::TypeTypeContext* JavaParser::typeType() {
  TypeTypeContext *_localctx = _tracker.createInstance<TypeTypeContext>(_ctx, getState());
  enterRule(_localctx, 196, JavaParser::RuleTypeType);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(1335);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaParser::AT) {
      setState(1334);
      annotation();
    }
    setState(1339);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaParser::IDENTIFIER: {
        setState(1337);
        classOrInterfaceType();
        break;
      }

      case JavaParser::BOOLEAN:
      case JavaParser::BYTE:
      case JavaParser::CHAR:
      case JavaParser::DOUBLE:
      case JavaParser::FLOAT:
      case JavaParser::INT:
      case JavaParser::LONG:
      case JavaParser::SHORT: {
        setState(1338);
        primitiveType();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(1345);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 165, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(1341);
        match(JavaParser::LBRACK);
        setState(1342);
        match(JavaParser::RBRACK); 
      }
      setState(1347);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 165, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrimitiveTypeContext ------------------------------------------------------------------

JavaParser::PrimitiveTypeContext::PrimitiveTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaParser::PrimitiveTypeContext::BOOLEAN() {
  return getToken(JavaParser::BOOLEAN, 0);
}

tree::TerminalNode* JavaParser::PrimitiveTypeContext::CHAR() {
  return getToken(JavaParser::CHAR, 0);
}

tree::TerminalNode* JavaParser::PrimitiveTypeContext::BYTE() {
  return getToken(JavaParser::BYTE, 0);
}

tree::TerminalNode* JavaParser::PrimitiveTypeContext::SHORT() {
  return getToken(JavaParser::SHORT, 0);
}

tree::TerminalNode* JavaParser::PrimitiveTypeContext::INT() {
  return getToken(JavaParser::INT, 0);
}

tree::TerminalNode* JavaParser::PrimitiveTypeContext::LONG() {
  return getToken(JavaParser::LONG, 0);
}

tree::TerminalNode* JavaParser::PrimitiveTypeContext::FLOAT() {
  return getToken(JavaParser::FLOAT, 0);
}

tree::TerminalNode* JavaParser::PrimitiveTypeContext::DOUBLE() {
  return getToken(JavaParser::DOUBLE, 0);
}


size_t JavaParser::PrimitiveTypeContext::getRuleIndex() const {
  return JavaParser::RulePrimitiveType;
}

void JavaParser::PrimitiveTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPrimitiveType(this);
}

void JavaParser::PrimitiveTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPrimitiveType(this);
}

JavaParser::PrimitiveTypeContext* JavaParser::primitiveType() {
  PrimitiveTypeContext *_localctx = _tracker.createInstance<PrimitiveTypeContext>(_ctx, getState());
  enterRule(_localctx, 198, JavaParser::RulePrimitiveType);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1348);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << JavaParser::BOOLEAN)
      | (1ULL << JavaParser::BYTE)
      | (1ULL << JavaParser::CHAR)
      | (1ULL << JavaParser::DOUBLE)
      | (1ULL << JavaParser::FLOAT)
      | (1ULL << JavaParser::INT)
      | (1ULL << JavaParser::LONG)
      | (1ULL << JavaParser::SHORT))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeArgumentsContext ------------------------------------------------------------------

JavaParser::TypeArgumentsContext::TypeArgumentsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaParser::TypeArgumentsContext::LT() {
  return getToken(JavaParser::LT, 0);
}

std::vector<JavaParser::TypeArgumentContext *> JavaParser::TypeArgumentsContext::typeArgument() {
  return getRuleContexts<JavaParser::TypeArgumentContext>();
}

JavaParser::TypeArgumentContext* JavaParser::TypeArgumentsContext::typeArgument(size_t i) {
  return getRuleContext<JavaParser::TypeArgumentContext>(i);
}

tree::TerminalNode* JavaParser::TypeArgumentsContext::GT() {
  return getToken(JavaParser::GT, 0);
}

std::vector<tree::TerminalNode *> JavaParser::TypeArgumentsContext::COMMA() {
  return getTokens(JavaParser::COMMA);
}

tree::TerminalNode* JavaParser::TypeArgumentsContext::COMMA(size_t i) {
  return getToken(JavaParser::COMMA, i);
}


size_t JavaParser::TypeArgumentsContext::getRuleIndex() const {
  return JavaParser::RuleTypeArguments;
}

void JavaParser::TypeArgumentsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeArguments(this);
}

void JavaParser::TypeArgumentsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeArguments(this);
}

JavaParser::TypeArgumentsContext* JavaParser::typeArguments() {
  TypeArgumentsContext *_localctx = _tracker.createInstance<TypeArgumentsContext>(_ctx, getState());
  enterRule(_localctx, 200, JavaParser::RuleTypeArguments);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1350);
    match(JavaParser::LT);
    setState(1351);
    typeArgument();
    setState(1356);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == JavaParser::COMMA) {
      setState(1352);
      match(JavaParser::COMMA);
      setState(1353);
      typeArgument();
      setState(1358);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(1359);
    match(JavaParser::GT);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SuperSuffixContext ------------------------------------------------------------------

JavaParser::SuperSuffixContext::SuperSuffixContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaParser::ArgumentsContext* JavaParser::SuperSuffixContext::arguments() {
  return getRuleContext<JavaParser::ArgumentsContext>(0);
}

tree::TerminalNode* JavaParser::SuperSuffixContext::DOT() {
  return getToken(JavaParser::DOT, 0);
}

tree::TerminalNode* JavaParser::SuperSuffixContext::IDENTIFIER() {
  return getToken(JavaParser::IDENTIFIER, 0);
}


size_t JavaParser::SuperSuffixContext::getRuleIndex() const {
  return JavaParser::RuleSuperSuffix;
}

void JavaParser::SuperSuffixContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSuperSuffix(this);
}

void JavaParser::SuperSuffixContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSuperSuffix(this);
}

JavaParser::SuperSuffixContext* JavaParser::superSuffix() {
  SuperSuffixContext *_localctx = _tracker.createInstance<SuperSuffixContext>(_ctx, getState());
  enterRule(_localctx, 202, JavaParser::RuleSuperSuffix);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(1367);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaParser::LPAREN: {
        enterOuterAlt(_localctx, 1);
        setState(1361);
        arguments();
        break;
      }

      case JavaParser::DOT: {
        enterOuterAlt(_localctx, 2);
        setState(1362);
        match(JavaParser::DOT);
        setState(1363);
        match(JavaParser::IDENTIFIER);
        setState(1365);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 167, _ctx)) {
        case 1: {
          setState(1364);
          arguments();
          break;
        }

        }
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExplicitGenericInvocationSuffixContext ------------------------------------------------------------------

JavaParser::ExplicitGenericInvocationSuffixContext::ExplicitGenericInvocationSuffixContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaParser::ExplicitGenericInvocationSuffixContext::SUPER() {
  return getToken(JavaParser::SUPER, 0);
}

JavaParser::SuperSuffixContext* JavaParser::ExplicitGenericInvocationSuffixContext::superSuffix() {
  return getRuleContext<JavaParser::SuperSuffixContext>(0);
}

tree::TerminalNode* JavaParser::ExplicitGenericInvocationSuffixContext::IDENTIFIER() {
  return getToken(JavaParser::IDENTIFIER, 0);
}

JavaParser::ArgumentsContext* JavaParser::ExplicitGenericInvocationSuffixContext::arguments() {
  return getRuleContext<JavaParser::ArgumentsContext>(0);
}


size_t JavaParser::ExplicitGenericInvocationSuffixContext::getRuleIndex() const {
  return JavaParser::RuleExplicitGenericInvocationSuffix;
}

void JavaParser::ExplicitGenericInvocationSuffixContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExplicitGenericInvocationSuffix(this);
}

void JavaParser::ExplicitGenericInvocationSuffixContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExplicitGenericInvocationSuffix(this);
}

JavaParser::ExplicitGenericInvocationSuffixContext* JavaParser::explicitGenericInvocationSuffix() {
  ExplicitGenericInvocationSuffixContext *_localctx = _tracker.createInstance<ExplicitGenericInvocationSuffixContext>(_ctx, getState());
  enterRule(_localctx, 204, JavaParser::RuleExplicitGenericInvocationSuffix);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(1373);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaParser::SUPER: {
        enterOuterAlt(_localctx, 1);
        setState(1369);
        match(JavaParser::SUPER);
        setState(1370);
        superSuffix();
        break;
      }

      case JavaParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 2);
        setState(1371);
        match(JavaParser::IDENTIFIER);
        setState(1372);
        arguments();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgumentsContext ------------------------------------------------------------------

JavaParser::ArgumentsContext::ArgumentsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaParser::ArgumentsContext::LPAREN() {
  return getToken(JavaParser::LPAREN, 0);
}

tree::TerminalNode* JavaParser::ArgumentsContext::RPAREN() {
  return getToken(JavaParser::RPAREN, 0);
}

JavaParser::ExpressionListContext* JavaParser::ArgumentsContext::expressionList() {
  return getRuleContext<JavaParser::ExpressionListContext>(0);
}


size_t JavaParser::ArgumentsContext::getRuleIndex() const {
  return JavaParser::RuleArguments;
}

void JavaParser::ArgumentsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArguments(this);
}

void JavaParser::ArgumentsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArguments(this);
}

JavaParser::ArgumentsContext* JavaParser::arguments() {
  ArgumentsContext *_localctx = _tracker.createInstance<ArgumentsContext>(_ctx, getState());
  enterRule(_localctx, 206, JavaParser::RuleArguments);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1375);
    match(JavaParser::LPAREN);
    setState(1377);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << JavaParser::BOOLEAN)
      | (1ULL << JavaParser::BYTE)
      | (1ULL << JavaParser::CHAR)
      | (1ULL << JavaParser::DOUBLE)
      | (1ULL << JavaParser::FLOAT)
      | (1ULL << JavaParser::INT)
      | (1ULL << JavaParser::LONG)
      | (1ULL << JavaParser::NEW)
      | (1ULL << JavaParser::SHORT)
      | (1ULL << JavaParser::SUPER)
      | (1ULL << JavaParser::THIS)
      | (1ULL << JavaParser::VOID)
      | (1ULL << JavaParser::DECIMAL_LITERAL)
      | (1ULL << JavaParser::HEX_LITERAL)
      | (1ULL << JavaParser::OCT_LITERAL)
      | (1ULL << JavaParser::BINARY_LITERAL)
      | (1ULL << JavaParser::FLOAT_LITERAL)
      | (1ULL << JavaParser::HEX_FLOAT_LITERAL)
      | (1ULL << JavaParser::BOOL_LITERAL)
      | (1ULL << JavaParser::CHAR_LITERAL)
      | (1ULL << JavaParser::STRING_LITERAL)
      | (1ULL << JavaParser::NULL_LITERAL)
      | (1ULL << JavaParser::LPAREN))) != 0) || ((((_la - 72) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 72)) & ((1ULL << (JavaParser::LT - 72))
      | (1ULL << (JavaParser::BANG - 72))
      | (1ULL << (JavaParser::TILDE - 72))
      | (1ULL << (JavaParser::INC - 72))
      | (1ULL << (JavaParser::DEC - 72))
      | (1ULL << (JavaParser::ADD - 72))
      | (1ULL << (JavaParser::SUB - 72))
      | (1ULL << (JavaParser::AT - 72))
      | (1ULL << (JavaParser::IDENTIFIER - 72)))) != 0)) {
      setState(1376);
      expressionList();
    }
    setState(1379);
    match(JavaParser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool JavaParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 82: return expressionSempred(dynamic_cast<ExpressionContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool JavaParser::expressionSempred(ExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 17);
    case 1: return precpred(_ctx, 16);
    case 2: return precpred(_ctx, 15);
    case 3: return precpred(_ctx, 14);
    case 4: return precpred(_ctx, 12);
    case 5: return precpred(_ctx, 11);
    case 6: return precpred(_ctx, 10);
    case 7: return precpred(_ctx, 9);
    case 8: return precpred(_ctx, 8);
    case 9: return precpred(_ctx, 7);
    case 10: return precpred(_ctx, 6);
    case 11: return precpred(_ctx, 5);
    case 12: return precpred(_ctx, 25);
    case 13: return precpred(_ctx, 24);
    case 14: return precpred(_ctx, 20);
    case 15: return precpred(_ctx, 13);
    case 16: return precpred(_ctx, 3);

  default:
    break;
  }
  return true;
}

// Static vars and initialization.
std::vector<dfa::DFA> JavaParser::_decisionToDFA;
atn::PredictionContextCache JavaParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN JavaParser::_atn;
std::vector<uint16_t> JavaParser::_serializedATN;

std::vector<std::string> JavaParser::_ruleNames = {
  "compilationUnit", "packageDeclaration", "importDeclaration", "typeDeclaration", 
  "modifier", "classOrInterfaceModifier", "variableModifier", "classDeclaration", 
  "typeParameters", "typeParameter", "typeBound", "enumDeclaration", "enumConstants", 
  "enumConstant", "enumBodyDeclarations", "interfaceDeclaration", "classBody", 
  "interfaceBody", "classBodyDeclaration", "memberDeclaration", "methodDeclaration", 
  "methodBody", "typeTypeOrVoid", "genericMethodDeclaration", "genericConstructorDeclaration", 
  "constructorDeclaration", "fieldDeclaration", "interfaceBodyDeclaration", 
  "interfaceMemberDeclaration", "constDeclaration", "constantDeclarator", 
  "interfaceMethodDeclaration", "interfaceMethodModifier", "genericInterfaceMethodDeclaration", 
  "variableDeclarators", "variableDeclarator", "variableDeclaratorId", "variableInitializer", 
  "arrayInitializer", "classOrInterfaceType", "typeArgument", "qualifiedNameList", 
  "formalParameters", "formalParameterList", "formalParameter", "lastFormalParameter", 
  "qualifiedName", "literal", "integerLiteral", "floatLiteral", "annotation", 
  "elementValuePairs", "elementValuePair", "elementValue", "elementValueArrayInitializer", 
  "annotationTypeDeclaration", "annotationTypeBody", "annotationTypeElementDeclaration", 
  "annotationTypeElementRest", "annotationMethodOrConstantRest", "annotationMethodRest", 
  "annotationConstantRest", "defaultValue", "block", "blockStatement", "localVariableDeclaration", 
  "localTypeDeclaration", "statement", "catchClause", "catchType", "finallyBlock", 
  "resourceSpecification", "resources", "resource", "switchBlockStatementGroup", 
  "switchLabel", "forControl", "forInit", "enhancedForControl", "parExpression", 
  "expressionList", "methodCall", "expression", "lambdaExpression", "lambdaParameters", 
  "lambdaBody", "primary", "classType", "creator", "createdName", "innerCreator", 
  "arrayCreatorRest", "classCreatorRest", "explicitGenericInvocation", "typeArgumentsOrDiamond", 
  "nonWildcardTypeArgumentsOrDiamond", "nonWildcardTypeArguments", "typeList", 
  "typeType", "primitiveType", "typeArguments", "superSuffix", "explicitGenericInvocationSuffix", 
  "arguments"
};

std::vector<std::string> JavaParser::_literalNames = {
  "", "'abstract'", "'assert'", "'boolean'", "'break'", "'byte'", "'case'", 
  "'catch'", "'char'", "'class'", "'const'", "'continue'", "'default'", 
  "'do'", "'double'", "'else'", "'enum'", "'extends'", "'final'", "'finally'", 
  "'float'", "'for'", "'if'", "'goto'", "'implements'", "'import'", "'instanceof'", 
  "'int'", "'interface'", "'long'", "'native'", "'new'", "'package'", "'private'", 
  "'protected'", "'public'", "'return'", "'short'", "'static'", "'strictfp'", 
  "'super'", "'switch'", "'synchronized'", "'this'", "'throw'", "'throws'", 
  "'transient'", "'try'", "'void'", "'volatile'", "'while'", "", "", "", 
  "", "", "", "", "", "", "'null'", "'('", "')'", "'{'", "'}'", "'['", "']'", 
  "';'", "','", "'.'", "'='", "'>'", "'<'", "'!'", "'~'", "'?'", "':'", 
  "'=='", "'<='", "'>='", "'!='", "'&&'", "'||'", "'++'", "'--'", "'+'", 
  "'-'", "'*'", "'/'", "'&'", "'|'", "'^'", "'%'", "'+='", "'-='", "'*='", 
  "'/='", "'&='", "'|='", "'^='", "'%='", "'<<='", "'>>='", "'>>>='", "'->'", 
  "'::'", "'@'", "'...'"
};

std::vector<std::string> JavaParser::_symbolicNames = {
  "", "ABSTRACT", "ASSERT", "BOOLEAN", "BREAK", "BYTE", "CASE", "CATCH", 
  "CHAR", "CLASS", "CONST", "CONTINUE", "DEFAULT", "DO", "DOUBLE", "ELSE", 
  "ENUM", "EXTENDS", "FINAL", "FINALLY", "FLOAT", "FOR", "IF", "GOTO", "IMPLEMENTS", 
  "IMPORT", "INSTANCEOF", "INT", "INTERFACE", "LONG", "NATIVE", "NEW", "PACKAGE", 
  "PRIVATE", "PROTECTED", "PUBLIC", "RETURN", "SHORT", "STATIC", "STRICTFP", 
  "SUPER", "SWITCH", "SYNCHRONIZED", "THIS", "THROW", "THROWS", "TRANSIENT", 
  "TRY", "VOID", "VOLATILE", "WHILE", "DECIMAL_LITERAL", "HEX_LITERAL", 
  "OCT_LITERAL", "BINARY_LITERAL", "FLOAT_LITERAL", "HEX_FLOAT_LITERAL", 
  "BOOL_LITERAL", "CHAR_LITERAL", "STRING_LITERAL", "NULL_LITERAL", "LPAREN", 
  "RPAREN", "LBRACE", "RBRACE", "LBRACK", "RBRACK", "SEMI", "COMMA", "DOT", 
  "ASSIGN", "GT", "LT", "BANG", "TILDE", "QUESTION", "COLON", "EQUAL", "LE", 
  "GE", "NOTEQUAL", "AND", "OR", "INC", "DEC", "ADD", "SUB", "MUL", "DIV", 
  "BITAND", "BITOR", "CARET", "MOD", "ADD_ASSIGN", "SUB_ASSIGN", "MUL_ASSIGN", 
  "DIV_ASSIGN", "AND_ASSIGN", "OR_ASSIGN", "XOR_ASSIGN", "MOD_ASSIGN", "LSHIFT_ASSIGN", 
  "RSHIFT_ASSIGN", "URSHIFT_ASSIGN", "ARROW", "COLONCOLON", "AT", "ELLIPSIS", 
  "WS", "NEWLINE", "COMMENT", "LINE_COMMENT", "IDENTIFIER"
};

dfa::Vocabulary JavaParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> JavaParser::_tokenNames;

JavaParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x3, 0x72, 0x568, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
    0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 
    0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 
    0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 
    0x4, 0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 0x9, 0x11, 0x4, 
    0x12, 0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x4, 0x14, 0x9, 0x14, 0x4, 0x15, 
    0x9, 0x15, 0x4, 0x16, 0x9, 0x16, 0x4, 0x17, 0x9, 0x17, 0x4, 0x18, 0x9, 
    0x18, 0x4, 0x19, 0x9, 0x19, 0x4, 0x1a, 0x9, 0x1a, 0x4, 0x1b, 0x9, 0x1b, 
    0x4, 0x1c, 0x9, 0x1c, 0x4, 0x1d, 0x9, 0x1d, 0x4, 0x1e, 0x9, 0x1e, 0x4, 
    0x1f, 0x9, 0x1f, 0x4, 0x20, 0x9, 0x20, 0x4, 0x21, 0x9, 0x21, 0x4, 0x22, 
    0x9, 0x22, 0x4, 0x23, 0x9, 0x23, 0x4, 0x24, 0x9, 0x24, 0x4, 0x25, 0x9, 
    0x25, 0x4, 0x26, 0x9, 0x26, 0x4, 0x27, 0x9, 0x27, 0x4, 0x28, 0x9, 0x28, 
    0x4, 0x29, 0x9, 0x29, 0x4, 0x2a, 0x9, 0x2a, 0x4, 0x2b, 0x9, 0x2b, 0x4, 
    0x2c, 0x9, 0x2c, 0x4, 0x2d, 0x9, 0x2d, 0x4, 0x2e, 0x9, 0x2e, 0x4, 0x2f, 
    0x9, 0x2f, 0x4, 0x30, 0x9, 0x30, 0x4, 0x31, 0x9, 0x31, 0x4, 0x32, 0x9, 
    0x32, 0x4, 0x33, 0x9, 0x33, 0x4, 0x34, 0x9, 0x34, 0x4, 0x35, 0x9, 0x35, 
    0x4, 0x36, 0x9, 0x36, 0x4, 0x37, 0x9, 0x37, 0x4, 0x38, 0x9, 0x38, 0x4, 
    0x39, 0x9, 0x39, 0x4, 0x3a, 0x9, 0x3a, 0x4, 0x3b, 0x9, 0x3b, 0x4, 0x3c, 
    0x9, 0x3c, 0x4, 0x3d, 0x9, 0x3d, 0x4, 0x3e, 0x9, 0x3e, 0x4, 0x3f, 0x9, 
    0x3f, 0x4, 0x40, 0x9, 0x40, 0x4, 0x41, 0x9, 0x41, 0x4, 0x42, 0x9, 0x42, 
    0x4, 0x43, 0x9, 0x43, 0x4, 0x44, 0x9, 0x44, 0x4, 0x45, 0x9, 0x45, 0x4, 
    0x46, 0x9, 0x46, 0x4, 0x47, 0x9, 0x47, 0x4, 0x48, 0x9, 0x48, 0x4, 0x49, 
    0x9, 0x49, 0x4, 0x4a, 0x9, 0x4a, 0x4, 0x4b, 0x9, 0x4b, 0x4, 0x4c, 0x9, 
    0x4c, 0x4, 0x4d, 0x9, 0x4d, 0x4, 0x4e, 0x9, 0x4e, 0x4, 0x4f, 0x9, 0x4f, 
    0x4, 0x50, 0x9, 0x50, 0x4, 0x51, 0x9, 0x51, 0x4, 0x52, 0x9, 0x52, 0x4, 
    0x53, 0x9, 0x53, 0x4, 0x54, 0x9, 0x54, 0x4, 0x55, 0x9, 0x55, 0x4, 0x56, 
    0x9, 0x56, 0x4, 0x57, 0x9, 0x57, 0x4, 0x58, 0x9, 0x58, 0x4, 0x59, 0x9, 
    0x59, 0x4, 0x5a, 0x9, 0x5a, 0x4, 0x5b, 0x9, 0x5b, 0x4, 0x5c, 0x9, 0x5c, 
    0x4, 0x5d, 0x9, 0x5d, 0x4, 0x5e, 0x9, 0x5e, 0x4, 0x5f, 0x9, 0x5f, 0x4, 
    0x60, 0x9, 0x60, 0x4, 0x61, 0x9, 0x61, 0x4, 0x62, 0x9, 0x62, 0x4, 0x63, 
    0x9, 0x63, 0x4, 0x64, 0x9, 0x64, 0x4, 0x65, 0x9, 0x65, 0x4, 0x66, 0x9, 
    0x66, 0x4, 0x67, 0x9, 0x67, 0x4, 0x68, 0x9, 0x68, 0x4, 0x69, 0x9, 0x69, 
    0x3, 0x2, 0x5, 0x2, 0xd4, 0xa, 0x2, 0x3, 0x2, 0x7, 0x2, 0xd7, 0xa, 0x2, 
    0xc, 0x2, 0xe, 0x2, 0xda, 0xb, 0x2, 0x3, 0x2, 0x7, 0x2, 0xdd, 0xa, 0x2, 
    0xc, 0x2, 0xe, 0x2, 0xe0, 0xb, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x7, 
    0x3, 0xe5, 0xa, 0x3, 0xc, 0x3, 0xe, 0x3, 0xe8, 0xb, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x4, 0x3, 0x4, 0x5, 0x4, 0xf0, 0xa, 0x4, 
    0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x5, 0x4, 0xf5, 0xa, 0x4, 0x3, 0x4, 0x3, 
    0x4, 0x3, 0x5, 0x7, 0x5, 0xfa, 0xa, 0x5, 0xc, 0x5, 0xe, 0x5, 0xfd, 0xb, 
    0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x5, 0x5, 0x103, 0xa, 0x5, 
    0x3, 0x5, 0x5, 0x5, 0x106, 0xa, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 
    0x6, 0x3, 0x6, 0x5, 0x6, 0x10d, 0xa, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 
    0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x5, 0x7, 0x117, 0xa, 
    0x7, 0x3, 0x8, 0x3, 0x8, 0x5, 0x8, 0x11b, 0xa, 0x8, 0x3, 0x9, 0x3, 0x9, 
    0x3, 0x9, 0x5, 0x9, 0x120, 0xa, 0x9, 0x3, 0x9, 0x3, 0x9, 0x5, 0x9, 0x124, 
    0xa, 0x9, 0x3, 0x9, 0x3, 0x9, 0x5, 0x9, 0x128, 0xa, 0x9, 0x3, 0x9, 0x3, 
    0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x7, 0xa, 0x130, 0xa, 0xa, 
    0xc, 0xa, 0xe, 0xa, 0x133, 0xb, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xb, 0x7, 
    0xb, 0x138, 0xa, 0xb, 0xc, 0xb, 0xe, 0xb, 0x13b, 0xb, 0xb, 0x3, 0xb, 
    0x3, 0xb, 0x3, 0xb, 0x5, 0xb, 0x140, 0xa, 0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 
    0xc, 0x7, 0xc, 0x145, 0xa, 0xc, 0xc, 0xc, 0xe, 0xc, 0x148, 0xb, 0xc, 
    0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x5, 0xd, 0x14e, 0xa, 0xd, 0x3, 
    0xd, 0x3, 0xd, 0x5, 0xd, 0x152, 0xa, 0xd, 0x3, 0xd, 0x5, 0xd, 0x155, 
    0xa, 0xd, 0x3, 0xd, 0x5, 0xd, 0x158, 0xa, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 
    0xe, 0x3, 0xe, 0x3, 0xe, 0x7, 0xe, 0x15f, 0xa, 0xe, 0xc, 0xe, 0xe, 0xe, 
    0x162, 0xb, 0xe, 0x3, 0xf, 0x7, 0xf, 0x165, 0xa, 0xf, 0xc, 0xf, 0xe, 
    0xf, 0x168, 0xb, 0xf, 0x3, 0xf, 0x3, 0xf, 0x5, 0xf, 0x16c, 0xa, 0xf, 
    0x3, 0xf, 0x5, 0xf, 0x16f, 0xa, 0xf, 0x3, 0x10, 0x3, 0x10, 0x7, 0x10, 
    0x173, 0xa, 0x10, 0xc, 0x10, 0xe, 0x10, 0x176, 0xb, 0x10, 0x3, 0x11, 
    0x3, 0x11, 0x3, 0x11, 0x5, 0x11, 0x17b, 0xa, 0x11, 0x3, 0x11, 0x3, 0x11, 
    0x5, 0x11, 0x17f, 0xa, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x12, 0x3, 0x12, 
    0x7, 0x12, 0x185, 0xa, 0x12, 0xc, 0x12, 0xe, 0x12, 0x188, 0xb, 0x12, 
    0x3, 0x12, 0x3, 0x12, 0x3, 0x13, 0x3, 0x13, 0x7, 0x13, 0x18e, 0xa, 0x13, 
    0xc, 0x13, 0xe, 0x13, 0x191, 0xb, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x14, 
    0x3, 0x14, 0x5, 0x14, 0x197, 0xa, 0x14, 0x3, 0x14, 0x3, 0x14, 0x7, 0x14, 
    0x19b, 0xa, 0x14, 0xc, 0x14, 0xe, 0x14, 0x19e, 0xb, 0x14, 0x3, 0x14, 
    0x5, 0x14, 0x1a1, 0xa, 0x14, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 
    0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x5, 0x15, 0x1ac, 
    0xa, 0x15, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x7, 
    0x16, 0x1b3, 0xa, 0x16, 0xc, 0x16, 0xe, 0x16, 0x1b6, 0xb, 0x16, 0x3, 
    0x16, 0x3, 0x16, 0x5, 0x16, 0x1ba, 0xa, 0x16, 0x3, 0x16, 0x3, 0x16, 
    0x3, 0x17, 0x3, 0x17, 0x5, 0x17, 0x1c0, 0xa, 0x17, 0x3, 0x18, 0x3, 0x18, 
    0x5, 0x18, 0x1c4, 0xa, 0x18, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x1a, 
    0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x5, 
    0x1b, 0x1d0, 0xa, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1c, 0x3, 0x1c, 
    0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1d, 0x7, 0x1d, 0x1d9, 0xa, 0x1d, 0xc, 0x1d, 
    0xe, 0x1d, 0x1dc, 0xb, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x5, 0x1d, 0x1e0, 
    0xa, 0x1d, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x3, 
    0x1e, 0x3, 0x1e, 0x5, 0x1e, 0x1e9, 0xa, 0x1e, 0x3, 0x1f, 0x3, 0x1f, 
    0x3, 0x1f, 0x3, 0x1f, 0x7, 0x1f, 0x1ef, 0xa, 0x1f, 0xc, 0x1f, 0xe, 0x1f, 
    0x1f2, 0xb, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 
    0x7, 0x20, 0x1f9, 0xa, 0x20, 0xc, 0x20, 0xe, 0x20, 0x1fc, 0xb, 0x20, 
    0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x21, 0x7, 0x21, 0x202, 0xa, 0x21, 
    0xc, 0x21, 0xe, 0x21, 0x205, 0xb, 0x21, 0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 
    0x7, 0x21, 0x20a, 0xa, 0x21, 0xc, 0x21, 0xe, 0x21, 0x20d, 0xb, 0x21, 
    0x3, 0x21, 0x3, 0x21, 0x5, 0x21, 0x211, 0xa, 0x21, 0x3, 0x21, 0x3, 0x21, 
    0x3, 0x21, 0x3, 0x21, 0x7, 0x21, 0x217, 0xa, 0x21, 0xc, 0x21, 0xe, 0x21, 
    0x21a, 0xb, 0x21, 0x3, 0x21, 0x3, 0x21, 0x5, 0x21, 0x21e, 0xa, 0x21, 
    0x3, 0x21, 0x3, 0x21, 0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x3, 
    0x22, 0x3, 0x22, 0x5, 0x22, 0x228, 0xa, 0x22, 0x3, 0x23, 0x3, 0x23, 
    0x3, 0x23, 0x3, 0x24, 0x3, 0x24, 0x3, 0x24, 0x7, 0x24, 0x230, 0xa, 0x24, 
    0xc, 0x24, 0xe, 0x24, 0x233, 0xb, 0x24, 0x3, 0x25, 0x3, 0x25, 0x3, 0x25, 
    0x5, 0x25, 0x238, 0xa, 0x25, 0x3, 0x26, 0x3, 0x26, 0x3, 0x26, 0x7, 0x26, 
    0x23d, 0xa, 0x26, 0xc, 0x26, 0xe, 0x26, 0x240, 0xb, 0x26, 0x3, 0x27, 
    0x3, 0x27, 0x5, 0x27, 0x244, 0xa, 0x27, 0x3, 0x28, 0x3, 0x28, 0x3, 0x28, 
    0x3, 0x28, 0x7, 0x28, 0x24a, 0xa, 0x28, 0xc, 0x28, 0xe, 0x28, 0x24d, 
    0xb, 0x28, 0x3, 0x28, 0x5, 0x28, 0x250, 0xa, 0x28, 0x5, 0x28, 0x252, 
    0xa, 0x28, 0x3, 0x28, 0x3, 0x28, 0x3, 0x29, 0x3, 0x29, 0x5, 0x29, 0x258, 
    0xa, 0x29, 0x3, 0x29, 0x3, 0x29, 0x3, 0x29, 0x5, 0x29, 0x25d, 0xa, 0x29, 
    0x7, 0x29, 0x25f, 0xa, 0x29, 0xc, 0x29, 0xe, 0x29, 0x262, 0xb, 0x29, 
    0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x5, 0x2a, 0x268, 0xa, 0x2a, 
    0x5, 0x2a, 0x26a, 0xa, 0x2a, 0x3, 0x2b, 0x3, 0x2b, 0x3, 0x2b, 0x7, 0x2b, 
    0x26f, 0xa, 0x2b, 0xc, 0x2b, 0xe, 0x2b, 0x272, 0xb, 0x2b, 0x3, 0x2c, 
    0x3, 0x2c, 0x5, 0x2c, 0x276, 0xa, 0x2c, 0x3, 0x2c, 0x3, 0x2c, 0x3, 0x2d, 
    0x3, 0x2d, 0x3, 0x2d, 0x7, 0x2d, 0x27d, 0xa, 0x2d, 0xc, 0x2d, 0xe, 0x2d, 
    0x280, 0xb, 0x2d, 0x3, 0x2d, 0x3, 0x2d, 0x5, 0x2d, 0x284, 0xa, 0x2d, 
    0x3, 0x2d, 0x5, 0x2d, 0x287, 0xa, 0x2d, 0x3, 0x2e, 0x7, 0x2e, 0x28a, 
    0xa, 0x2e, 0xc, 0x2e, 0xe, 0x2e, 0x28d, 0xb, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 
    0x3, 0x2e, 0x3, 0x2f, 0x7, 0x2f, 0x293, 0xa, 0x2f, 0xc, 0x2f, 0xe, 0x2f, 
    0x296, 0xb, 0x2f, 0x3, 0x2f, 0x3, 0x2f, 0x3, 0x2f, 0x3, 0x2f, 0x3, 0x30, 
    0x3, 0x30, 0x3, 0x30, 0x7, 0x30, 0x29f, 0xa, 0x30, 0xc, 0x30, 0xe, 0x30, 
    0x2a2, 0xb, 0x30, 0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 
    0x3, 0x31, 0x5, 0x31, 0x2aa, 0xa, 0x31, 0x3, 0x32, 0x3, 0x32, 0x3, 0x33, 
    0x3, 0x33, 0x3, 0x34, 0x3, 0x34, 0x3, 0x34, 0x3, 0x34, 0x3, 0x34, 0x5, 
    0x34, 0x2b5, 0xa, 0x34, 0x3, 0x34, 0x5, 0x34, 0x2b8, 0xa, 0x34, 0x3, 
    0x35, 0x3, 0x35, 0x3, 0x35, 0x7, 0x35, 0x2bd, 0xa, 0x35, 0xc, 0x35, 
    0xe, 0x35, 0x2c0, 0xb, 0x35, 0x3, 0x36, 0x3, 0x36, 0x3, 0x36, 0x3, 0x36, 
    0x3, 0x37, 0x3, 0x37, 0x3, 0x37, 0x5, 0x37, 0x2c9, 0xa, 0x37, 0x3, 0x38, 
    0x3, 0x38, 0x3, 0x38, 0x3, 0x38, 0x7, 0x38, 0x2cf, 0xa, 0x38, 0xc, 0x38, 
    0xe, 0x38, 0x2d2, 0xb, 0x38, 0x5, 0x38, 0x2d4, 0xa, 0x38, 0x3, 0x38, 
    0x5, 0x38, 0x2d7, 0xa, 0x38, 0x3, 0x38, 0x3, 0x38, 0x3, 0x39, 0x3, 0x39, 
    0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x3a, 0x3, 0x3a, 0x7, 0x3a, 0x2e2, 
    0xa, 0x3a, 0xc, 0x3a, 0xe, 0x3a, 0x2e5, 0xb, 0x3a, 0x3, 0x3a, 0x3, 0x3a, 
    0x3, 0x3b, 0x7, 0x3b, 0x2ea, 0xa, 0x3b, 0xc, 0x3b, 0xe, 0x3b, 0x2ed, 
    0xb, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x5, 0x3b, 0x2f1, 0xa, 0x3b, 0x3, 0x3c, 
    0x3, 0x3c, 0x3, 0x3c, 0x3, 0x3c, 0x3, 0x3c, 0x3, 0x3c, 0x5, 0x3c, 0x2f9, 
    0xa, 0x3c, 0x3, 0x3c, 0x3, 0x3c, 0x5, 0x3c, 0x2fd, 0xa, 0x3c, 0x3, 0x3c, 
    0x3, 0x3c, 0x5, 0x3c, 0x301, 0xa, 0x3c, 0x3, 0x3c, 0x3, 0x3c, 0x5, 0x3c, 
    0x305, 0xa, 0x3c, 0x5, 0x3c, 0x307, 0xa, 0x3c, 0x3, 0x3d, 0x3, 0x3d, 
    0x5, 0x3d, 0x30b, 0xa, 0x3d, 0x3, 0x3e, 0x3, 0x3e, 0x3, 0x3e, 0x3, 0x3e, 
    0x5, 0x3e, 0x311, 0xa, 0x3e, 0x3, 0x3f, 0x3, 0x3f, 0x3, 0x40, 0x3, 0x40, 
    0x3, 0x40, 0x3, 0x41, 0x3, 0x41, 0x7, 0x41, 0x31a, 0xa, 0x41, 0xc, 0x41, 
    0xe, 0x41, 0x31d, 0xb, 0x41, 0x3, 0x41, 0x3, 0x41, 0x3, 0x42, 0x3, 0x42, 
    0x3, 0x42, 0x3, 0x42, 0x3, 0x42, 0x5, 0x42, 0x326, 0xa, 0x42, 0x3, 0x43, 
    0x7, 0x43, 0x329, 0xa, 0x43, 0xc, 0x43, 0xe, 0x43, 0x32c, 0xb, 0x43, 
    0x3, 0x43, 0x3, 0x43, 0x3, 0x43, 0x3, 0x44, 0x7, 0x44, 0x332, 0xa, 0x44, 
    0xc, 0x44, 0xe, 0x44, 0x335, 0xb, 0x44, 0x3, 0x44, 0x3, 0x44, 0x5, 0x44, 
    0x339, 0xa, 0x44, 0x3, 0x44, 0x5, 0x44, 0x33c, 0xa, 0x44, 0x3, 0x45, 
    0x3, 0x45, 0x3, 0x45, 0x3, 0x45, 0x3, 0x45, 0x5, 0x45, 0x343, 0xa, 0x45, 
    0x3, 0x45, 0x3, 0x45, 0x3, 0x45, 0x3, 0x45, 0x3, 0x45, 0x3, 0x45, 0x3, 
    0x45, 0x5, 0x45, 0x34c, 0xa, 0x45, 0x3, 0x45, 0x3, 0x45, 0x3, 0x45, 
    0x3, 0x45, 0x3, 0x45, 0x3, 0x45, 0x3, 0x45, 0x3, 0x45, 0x3, 0x45, 0x3, 
    0x45, 0x3, 0x45, 0x3, 0x45, 0x3, 0x45, 0x3, 0x45, 0x3, 0x45, 0x3, 0x45, 
    0x3, 0x45, 0x3, 0x45, 0x3, 0x45, 0x6, 0x45, 0x361, 0xa, 0x45, 0xd, 0x45, 
    0xe, 0x45, 0x362, 0x3, 0x45, 0x5, 0x45, 0x366, 0xa, 0x45, 0x3, 0x45, 
    0x5, 0x45, 0x369, 0xa, 0x45, 0x3, 0x45, 0x3, 0x45, 0x3, 0x45, 0x3, 0x45, 
    0x7, 0x45, 0x36f, 0xa, 0x45, 0xc, 0x45, 0xe, 0x45, 0x372, 0xb, 0x45, 
    0x3, 0x45, 0x5, 0x45, 0x375, 0xa, 0x45, 0x3, 0x45, 0x3, 0x45, 0x3, 0x45, 
    0x3, 0x45, 0x7, 0x45, 0x37b, 0xa, 0x45, 0xc, 0x45, 0xe, 0x45, 0x37e, 
    0xb, 0x45, 0x3, 0x45, 0x7, 0x45, 0x381, 0xa, 0x45, 0xc, 0x45, 0xe, 0x45, 
    0x384, 0xb, 0x45, 0x3, 0x45, 0x3, 0x45, 0x3, 0x45, 0x3, 0x45, 0x3, 0x45, 
    0x3, 0x45, 0x3, 0x45, 0x3, 0x45, 0x5, 0x45, 0x38e, 0xa, 0x45, 0x3, 0x45, 
    0x3, 0x45, 0x3, 0x45, 0x3, 0x45, 0x3, 0x45, 0x3, 0x45, 0x3, 0x45, 0x5, 
    0x45, 0x397, 0xa, 0x45, 0x3, 0x45, 0x3, 0x45, 0x3, 0x45, 0x5, 0x45, 
    0x39c, 0xa, 0x45, 0x3, 0x45, 0x3, 0x45, 0x3, 0x45, 0x3, 0x45, 0x3, 0x45, 
    0x3, 0x45, 0x3, 0x45, 0x3, 0x45, 0x5, 0x45, 0x3a6, 0xa, 0x45, 0x3, 0x46, 
    0x3, 0x46, 0x3, 0x46, 0x7, 0x46, 0x3ab, 0xa, 0x46, 0xc, 0x46, 0xe, 0x46, 
    0x3ae, 0xb, 0x46, 0x3, 0x46, 0x3, 0x46, 0x3, 0x46, 0x3, 0x46, 0x3, 0x46, 
    0x3, 0x47, 0x3, 0x47, 0x3, 0x47, 0x7, 0x47, 0x3b8, 0xa, 0x47, 0xc, 0x47, 
    0xe, 0x47, 0x3bb, 0xb, 0x47, 0x3, 0x48, 0x3, 0x48, 0x3, 0x48, 0x3, 0x49, 
    0x3, 0x49, 0x3, 0x49, 0x5, 0x49, 0x3c3, 0xa, 0x49, 0x3, 0x49, 0x3, 0x49, 
    0x3, 0x4a, 0x3, 0x4a, 0x3, 0x4a, 0x7, 0x4a, 0x3ca, 0xa, 0x4a, 0xc, 0x4a, 
    0xe, 0x4a, 0x3cd, 0xb, 0x4a, 0x3, 0x4b, 0x7, 0x4b, 0x3d0, 0xa, 0x4b, 
    0xc, 0x4b, 0xe, 0x4b, 0x3d3, 0xb, 0x4b, 0x3, 0x4b, 0x3, 0x4b, 0x3, 0x4b, 
    0x3, 0x4b, 0x3, 0x4b, 0x3, 0x4c, 0x6, 0x4c, 0x3db, 0xa, 0x4c, 0xd, 0x4c, 
    0xe, 0x4c, 0x3dc, 0x3, 0x4c, 0x6, 0x4c, 0x3e0, 0xa, 0x4c, 0xd, 0x4c, 
    0xe, 0x4c, 0x3e1, 0x3, 0x4d, 0x3, 0x4d, 0x3, 0x4d, 0x5, 0x4d, 0x3e7, 
    0xa, 0x4d, 0x3, 0x4d, 0x3, 0x4d, 0x3, 0x4d, 0x5, 0x4d, 0x3ec, 0xa, 0x4d, 
    0x3, 0x4e, 0x3, 0x4e, 0x5, 0x4e, 0x3f0, 0xa, 0x4e, 0x3, 0x4e, 0x3, 0x4e, 
    0x5, 0x4e, 0x3f4, 0xa, 0x4e, 0x3, 0x4e, 0x3, 0x4e, 0x5, 0x4e, 0x3f8, 
    0xa, 0x4e, 0x5, 0x4e, 0x3fa, 0xa, 0x4e, 0x3, 0x4f, 0x3, 0x4f, 0x5, 0x4f, 
    0x3fe, 0xa, 0x4f, 0x3, 0x50, 0x7, 0x50, 0x401, 0xa, 0x50, 0xc, 0x50, 
    0xe, 0x50, 0x404, 0xb, 0x50, 0x3, 0x50, 0x3, 0x50, 0x3, 0x50, 0x3, 0x50, 
    0x3, 0x50, 0x3, 0x51, 0x3, 0x51, 0x3, 0x51, 0x3, 0x51, 0x3, 0x52, 0x3, 
    0x52, 0x3, 0x52, 0x7, 0x52, 0x412, 0xa, 0x52, 0xc, 0x52, 0xe, 0x52, 
    0x415, 0xb, 0x52, 0x3, 0x53, 0x3, 0x53, 0x3, 0x53, 0x5, 0x53, 0x41a, 
    0xa, 0x53, 0x3, 0x53, 0x3, 0x53, 0x3, 0x53, 0x3, 0x53, 0x5, 0x53, 0x420, 
    0xa, 0x53, 0x3, 0x53, 0x3, 0x53, 0x3, 0x53, 0x3, 0x53, 0x5, 0x53, 0x426, 
    0xa, 0x53, 0x3, 0x53, 0x5, 0x53, 0x429, 0xa, 0x53, 0x3, 0x54, 0x3, 0x54, 
    0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 
    0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 
    0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 0x5, 0x54, 0x43d, 0xa, 0x54, 0x3, 0x54, 
    0x3, 0x54, 0x5, 0x54, 0x441, 0xa, 0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 
    0x5, 0x54, 0x446, 0xa, 0x54, 0x3, 0x54, 0x3, 0x54, 0x5, 0x54, 0x44a, 
    0xa, 0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 
    0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 
    0x3, 0x54, 0x3, 0x54, 0x5, 0x54, 0x45a, 0xa, 0x54, 0x3, 0x54, 0x3, 0x54, 
    0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 
    0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 
    0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 
    0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 
    0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 
    0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 0x5, 0x54, 0x482, 0xa, 0x54, 
    0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 0x5, 0x54, 0x488, 0xa, 0x54, 
    0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 
    0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 
    0x5, 0x54, 0x497, 0xa, 0x54, 0x3, 0x54, 0x7, 0x54, 0x49a, 0xa, 0x54, 
    0xc, 0x54, 0xe, 0x54, 0x49d, 0xb, 0x54, 0x3, 0x55, 0x3, 0x55, 0x3, 0x55, 
    0x3, 0x55, 0x3, 0x56, 0x3, 0x56, 0x3, 0x56, 0x5, 0x56, 0x4a6, 0xa, 0x56, 
    0x3, 0x56, 0x3, 0x56, 0x3, 0x56, 0x3, 0x56, 0x3, 0x56, 0x7, 0x56, 0x4ad, 
    0xa, 0x56, 0xc, 0x56, 0xe, 0x56, 0x4b0, 0xb, 0x56, 0x3, 0x56, 0x5, 0x56, 
    0x4b3, 0xa, 0x56, 0x3, 0x57, 0x3, 0x57, 0x5, 0x57, 0x4b7, 0xa, 0x57, 
    0x3, 0x58, 0x3, 0x58, 0x3, 0x58, 0x3, 0x58, 0x3, 0x58, 0x3, 0x58, 0x3, 
    0x58, 0x3, 0x58, 0x3, 0x58, 0x3, 0x58, 0x3, 0x58, 0x3, 0x58, 0x3, 0x58, 
    0x3, 0x58, 0x3, 0x58, 0x3, 0x58, 0x5, 0x58, 0x4c9, 0xa, 0x58, 0x5, 0x58, 
    0x4cb, 0xa, 0x58, 0x3, 0x59, 0x3, 0x59, 0x3, 0x59, 0x5, 0x59, 0x4d0, 
    0xa, 0x59, 0x3, 0x59, 0x7, 0x59, 0x4d3, 0xa, 0x59, 0xc, 0x59, 0xe, 0x59, 
    0x4d6, 0xb, 0x59, 0x3, 0x59, 0x3, 0x59, 0x5, 0x59, 0x4da, 0xa, 0x59, 
    0x3, 0x5a, 0x3, 0x5a, 0x3, 0x5a, 0x3, 0x5a, 0x3, 0x5a, 0x3, 0x5a, 0x3, 
    0x5a, 0x5, 0x5a, 0x4e3, 0xa, 0x5a, 0x5, 0x5a, 0x4e5, 0xa, 0x5a, 0x3, 
    0x5b, 0x3, 0x5b, 0x5, 0x5b, 0x4e9, 0xa, 0x5b, 0x3, 0x5b, 0x3, 0x5b, 
    0x3, 0x5b, 0x5, 0x5b, 0x4ee, 0xa, 0x5b, 0x7, 0x5b, 0x4f0, 0xa, 0x5b, 
    0xc, 0x5b, 0xe, 0x5b, 0x4f3, 0xb, 0x5b, 0x3, 0x5b, 0x5, 0x5b, 0x4f6, 
    0xa, 0x5b, 0x3, 0x5c, 0x3, 0x5c, 0x5, 0x5c, 0x4fa, 0xa, 0x5c, 0x3, 0x5c, 
    0x3, 0x5c, 0x3, 0x5d, 0x3, 0x5d, 0x3, 0x5d, 0x3, 0x5d, 0x7, 0x5d, 0x502, 
    0xa, 0x5d, 0xc, 0x5d, 0xe, 0x5d, 0x505, 0xb, 0x5d, 0x3, 0x5d, 0x3, 0x5d, 
    0x3, 0x5d, 0x3, 0x5d, 0x3, 0x5d, 0x3, 0x5d, 0x3, 0x5d, 0x7, 0x5d, 0x50e, 
    0xa, 0x5d, 0xc, 0x5d, 0xe, 0x5d, 0x511, 0xb, 0x5d, 0x3, 0x5d, 0x3, 0x5d, 
    0x7, 0x5d, 0x515, 0xa, 0x5d, 0xc, 0x5d, 0xe, 0x5d, 0x518, 0xb, 0x5d, 
    0x5, 0x5d, 0x51a, 0xa, 0x5d, 0x3, 0x5e, 0x3, 0x5e, 0x5, 0x5e, 0x51e, 
    0xa, 0x5e, 0x3, 0x5f, 0x3, 0x5f, 0x3, 0x5f, 0x3, 0x60, 0x3, 0x60, 0x3, 
    0x60, 0x5, 0x60, 0x526, 0xa, 0x60, 0x3, 0x61, 0x3, 0x61, 0x3, 0x61, 
    0x5, 0x61, 0x52b, 0xa, 0x61, 0x3, 0x62, 0x3, 0x62, 0x3, 0x62, 0x3, 0x62, 
    0x3, 0x63, 0x3, 0x63, 0x3, 0x63, 0x7, 0x63, 0x534, 0xa, 0x63, 0xc, 0x63, 
    0xe, 0x63, 0x537, 0xb, 0x63, 0x3, 0x64, 0x5, 0x64, 0x53a, 0xa, 0x64, 
    0x3, 0x64, 0x3, 0x64, 0x5, 0x64, 0x53e, 0xa, 0x64, 0x3, 0x64, 0x3, 0x64, 
    0x7, 0x64, 0x542, 0xa, 0x64, 0xc, 0x64, 0xe, 0x64, 0x545, 0xb, 0x64, 
    0x3, 0x65, 0x3, 0x65, 0x3, 0x66, 0x3, 0x66, 0x3, 0x66, 0x3, 0x66, 0x7, 
    0x66, 0x54d, 0xa, 0x66, 0xc, 0x66, 0xe, 0x66, 0x550, 0xb, 0x66, 0x3, 
    0x66, 0x3, 0x66, 0x3, 0x67, 0x3, 0x67, 0x3, 0x67, 0x3, 0x67, 0x5, 0x67, 
    0x558, 0xa, 0x67, 0x5, 0x67, 0x55a, 0xa, 0x67, 0x3, 0x68, 0x3, 0x68, 
    0x3, 0x68, 0x3, 0x68, 0x5, 0x68, 0x560, 0xa, 0x68, 0x3, 0x69, 0x3, 0x69, 
    0x5, 0x69, 0x564, 0xa, 0x69, 0x3, 0x69, 0x3, 0x69, 0x3, 0x69, 0x2, 0x3, 
    0xa6, 0x6a, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 
    0x18, 0x1a, 0x1c, 0x1e, 0x20, 0x22, 0x24, 0x26, 0x28, 0x2a, 0x2c, 0x2e, 
    0x30, 0x32, 0x34, 0x36, 0x38, 0x3a, 0x3c, 0x3e, 0x40, 0x42, 0x44, 0x46, 
    0x48, 0x4a, 0x4c, 0x4e, 0x50, 0x52, 0x54, 0x56, 0x58, 0x5a, 0x5c, 0x5e, 
    0x60, 0x62, 0x64, 0x66, 0x68, 0x6a, 0x6c, 0x6e, 0x70, 0x72, 0x74, 0x76, 
    0x78, 0x7a, 0x7c, 0x7e, 0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c, 0x8e, 
    0x90, 0x92, 0x94, 0x96, 0x98, 0x9a, 0x9c, 0x9e, 0xa0, 0xa2, 0xa4, 0xa6, 
    0xa8, 0xaa, 0xac, 0xae, 0xb0, 0xb2, 0xb4, 0xb6, 0xb8, 0xba, 0xbc, 0xbe, 
    0xc0, 0xc2, 0xc4, 0xc6, 0xc8, 0xca, 0xcc, 0xce, 0xd0, 0x2, 0xe, 0x4, 
    0x2, 0x13, 0x13, 0x2a, 0x2a, 0x3, 0x2, 0x35, 0x38, 0x3, 0x2, 0x39, 0x3a, 
    0x3, 0x2, 0x55, 0x58, 0x3, 0x2, 0x4b, 0x4c, 0x4, 0x2, 0x59, 0x5a, 0x5e, 
    0x5e, 0x3, 0x2, 0x57, 0x58, 0x4, 0x2, 0x49, 0x4a, 0x50, 0x51, 0x4, 0x2, 
    0x4f, 0x4f, 0x52, 0x52, 0x4, 0x2, 0x48, 0x48, 0x5f, 0x69, 0x3, 0x2, 
    0x55, 0x56, 0xa, 0x2, 0x5, 0x5, 0x7, 0x7, 0xa, 0xa, 0x10, 0x10, 0x16, 
    0x16, 0x1d, 0x1d, 0x1f, 0x1f, 0x27, 0x27, 0x2, 0x601, 0x2, 0xd3, 0x3, 
    0x2, 0x2, 0x2, 0x4, 0xe6, 0x3, 0x2, 0x2, 0x2, 0x6, 0xed, 0x3, 0x2, 0x2, 
    0x2, 0x8, 0x105, 0x3, 0x2, 0x2, 0x2, 0xa, 0x10c, 0x3, 0x2, 0x2, 0x2, 
    0xc, 0x116, 0x3, 0x2, 0x2, 0x2, 0xe, 0x11a, 0x3, 0x2, 0x2, 0x2, 0x10, 
    0x11c, 0x3, 0x2, 0x2, 0x2, 0x12, 0x12b, 0x3, 0x2, 0x2, 0x2, 0x14, 0x139, 
    0x3, 0x2, 0x2, 0x2, 0x16, 0x141, 0x3, 0x2, 0x2, 0x2, 0x18, 0x149, 0x3, 
    0x2, 0x2, 0x2, 0x1a, 0x15b, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x166, 0x3, 0x2, 
    0x2, 0x2, 0x1e, 0x170, 0x3, 0x2, 0x2, 0x2, 0x20, 0x177, 0x3, 0x2, 0x2, 
    0x2, 0x22, 0x182, 0x3, 0x2, 0x2, 0x2, 0x24, 0x18b, 0x3, 0x2, 0x2, 0x2, 
    0x26, 0x1a0, 0x3, 0x2, 0x2, 0x2, 0x28, 0x1ab, 0x3, 0x2, 0x2, 0x2, 0x2a, 
    0x1ad, 0x3, 0x2, 0x2, 0x2, 0x2c, 0x1bf, 0x3, 0x2, 0x2, 0x2, 0x2e, 0x1c3, 
    0x3, 0x2, 0x2, 0x2, 0x30, 0x1c5, 0x3, 0x2, 0x2, 0x2, 0x32, 0x1c8, 0x3, 
    0x2, 0x2, 0x2, 0x34, 0x1cb, 0x3, 0x2, 0x2, 0x2, 0x36, 0x1d3, 0x3, 0x2, 
    0x2, 0x2, 0x38, 0x1df, 0x3, 0x2, 0x2, 0x2, 0x3a, 0x1e8, 0x3, 0x2, 0x2, 
    0x2, 0x3c, 0x1ea, 0x3, 0x2, 0x2, 0x2, 0x3e, 0x1f5, 0x3, 0x2, 0x2, 0x2, 
    0x40, 0x203, 0x3, 0x2, 0x2, 0x2, 0x42, 0x227, 0x3, 0x2, 0x2, 0x2, 0x44, 
    0x229, 0x3, 0x2, 0x2, 0x2, 0x46, 0x22c, 0x3, 0x2, 0x2, 0x2, 0x48, 0x234, 
    0x3, 0x2, 0x2, 0x2, 0x4a, 0x239, 0x3, 0x2, 0x2, 0x2, 0x4c, 0x243, 0x3, 
    0x2, 0x2, 0x2, 0x4e, 0x245, 0x3, 0x2, 0x2, 0x2, 0x50, 0x255, 0x3, 0x2, 
    0x2, 0x2, 0x52, 0x269, 0x3, 0x2, 0x2, 0x2, 0x54, 0x26b, 0x3, 0x2, 0x2, 
    0x2, 0x56, 0x273, 0x3, 0x2, 0x2, 0x2, 0x58, 0x286, 0x3, 0x2, 0x2, 0x2, 
    0x5a, 0x28b, 0x3, 0x2, 0x2, 0x2, 0x5c, 0x294, 0x3, 0x2, 0x2, 0x2, 0x5e, 
    0x29b, 0x3, 0x2, 0x2, 0x2, 0x60, 0x2a9, 0x3, 0x2, 0x2, 0x2, 0x62, 0x2ab, 
    0x3, 0x2, 0x2, 0x2, 0x64, 0x2ad, 0x3, 0x2, 0x2, 0x2, 0x66, 0x2af, 0x3, 
    0x2, 0x2, 0x2, 0x68, 0x2b9, 0x3, 0x2, 0x2, 0x2, 0x6a, 0x2c1, 0x3, 0x2, 
    0x2, 0x2, 0x6c, 0x2c8, 0x3, 0x2, 0x2, 0x2, 0x6e, 0x2ca, 0x3, 0x2, 0x2, 
    0x2, 0x70, 0x2da, 0x3, 0x2, 0x2, 0x2, 0x72, 0x2df, 0x3, 0x2, 0x2, 0x2, 
    0x74, 0x2f0, 0x3, 0x2, 0x2, 0x2, 0x76, 0x306, 0x3, 0x2, 0x2, 0x2, 0x78, 
    0x30a, 0x3, 0x2, 0x2, 0x2, 0x7a, 0x30c, 0x3, 0x2, 0x2, 0x2, 0x7c, 0x312, 
    0x3, 0x2, 0x2, 0x2, 0x7e, 0x314, 0x3, 0x2, 0x2, 0x2, 0x80, 0x317, 0x3, 
    0x2, 0x2, 0x2, 0x82, 0x325, 0x3, 0x2, 0x2, 0x2, 0x84, 0x32a, 0x3, 0x2, 
    0x2, 0x2, 0x86, 0x33b, 0x3, 0x2, 0x2, 0x2, 0x88, 0x3a5, 0x3, 0x2, 0x2, 
    0x2, 0x8a, 0x3a7, 0x3, 0x2, 0x2, 0x2, 0x8c, 0x3b4, 0x3, 0x2, 0x2, 0x2, 
    0x8e, 0x3bc, 0x3, 0x2, 0x2, 0x2, 0x90, 0x3bf, 0x3, 0x2, 0x2, 0x2, 0x92, 
    0x3c6, 0x3, 0x2, 0x2, 0x2, 0x94, 0x3d1, 0x3, 0x2, 0x2, 0x2, 0x96, 0x3da, 
    0x3, 0x2, 0x2, 0x2, 0x98, 0x3eb, 0x3, 0x2, 0x2, 0x2, 0x9a, 0x3f9, 0x3, 
    0x2, 0x2, 0x2, 0x9c, 0x3fd, 0x3, 0x2, 0x2, 0x2, 0x9e, 0x402, 0x3, 0x2, 
    0x2, 0x2, 0xa0, 0x40a, 0x3, 0x2, 0x2, 0x2, 0xa2, 0x40e, 0x3, 0x2, 0x2, 
    0x2, 0xa4, 0x428, 0x3, 0x2, 0x2, 0x2, 0xa6, 0x449, 0x3, 0x2, 0x2, 0x2, 
    0xa8, 0x49e, 0x3, 0x2, 0x2, 0x2, 0xaa, 0x4b2, 0x3, 0x2, 0x2, 0x2, 0xac, 
    0x4b6, 0x3, 0x2, 0x2, 0x2, 0xae, 0x4ca, 0x3, 0x2, 0x2, 0x2, 0xb0, 0x4cf, 
    0x3, 0x2, 0x2, 0x2, 0xb2, 0x4e4, 0x3, 0x2, 0x2, 0x2, 0xb4, 0x4f5, 0x3, 
    0x2, 0x2, 0x2, 0xb6, 0x4f7, 0x3, 0x2, 0x2, 0x2, 0xb8, 0x4fd, 0x3, 0x2, 
    0x2, 0x2, 0xba, 0x51b, 0x3, 0x2, 0x2, 0x2, 0xbc, 0x51f, 0x3, 0x2, 0x2, 
    0x2, 0xbe, 0x525, 0x3, 0x2, 0x2, 0x2, 0xc0, 0x52a, 0x3, 0x2, 0x2, 0x2, 
    0xc2, 0x52c, 0x3, 0x2, 0x2, 0x2, 0xc4, 0x530, 0x3, 0x2, 0x2, 0x2, 0xc6, 
    0x539, 0x3, 0x2, 0x2, 0x2, 0xc8, 0x546, 0x3, 0x2, 0x2, 0x2, 0xca, 0x548, 
    0x3, 0x2, 0x2, 0x2, 0xcc, 0x559, 0x3, 0x2, 0x2, 0x2, 0xce, 0x55f, 0x3, 
    0x2, 0x2, 0x2, 0xd0, 0x561, 0x3, 0x2, 0x2, 0x2, 0xd2, 0xd4, 0x5, 0x4, 
    0x3, 0x2, 0xd3, 0xd2, 0x3, 0x2, 0x2, 0x2, 0xd3, 0xd4, 0x3, 0x2, 0x2, 
    0x2, 0xd4, 0xd8, 0x3, 0x2, 0x2, 0x2, 0xd5, 0xd7, 0x5, 0x6, 0x4, 0x2, 
    0xd6, 0xd5, 0x3, 0x2, 0x2, 0x2, 0xd7, 0xda, 0x3, 0x2, 0x2, 0x2, 0xd8, 
    0xd6, 0x3, 0x2, 0x2, 0x2, 0xd8, 0xd9, 0x3, 0x2, 0x2, 0x2, 0xd9, 0xde, 
    0x3, 0x2, 0x2, 0x2, 0xda, 0xd8, 0x3, 0x2, 0x2, 0x2, 0xdb, 0xdd, 0x5, 
    0x8, 0x5, 0x2, 0xdc, 0xdb, 0x3, 0x2, 0x2, 0x2, 0xdd, 0xe0, 0x3, 0x2, 
    0x2, 0x2, 0xde, 0xdc, 0x3, 0x2, 0x2, 0x2, 0xde, 0xdf, 0x3, 0x2, 0x2, 
    0x2, 0xdf, 0xe1, 0x3, 0x2, 0x2, 0x2, 0xe0, 0xde, 0x3, 0x2, 0x2, 0x2, 
    0xe1, 0xe2, 0x7, 0x2, 0x2, 0x3, 0xe2, 0x3, 0x3, 0x2, 0x2, 0x2, 0xe3, 
    0xe5, 0x5, 0x66, 0x34, 0x2, 0xe4, 0xe3, 0x3, 0x2, 0x2, 0x2, 0xe5, 0xe8, 
    0x3, 0x2, 0x2, 0x2, 0xe6, 0xe4, 0x3, 0x2, 0x2, 0x2, 0xe6, 0xe7, 0x3, 
    0x2, 0x2, 0x2, 0xe7, 0xe9, 0x3, 0x2, 0x2, 0x2, 0xe8, 0xe6, 0x3, 0x2, 
    0x2, 0x2, 0xe9, 0xea, 0x7, 0x22, 0x2, 0x2, 0xea, 0xeb, 0x5, 0x5e, 0x30, 
    0x2, 0xeb, 0xec, 0x7, 0x45, 0x2, 0x2, 0xec, 0x5, 0x3, 0x2, 0x2, 0x2, 
    0xed, 0xef, 0x7, 0x1b, 0x2, 0x2, 0xee, 0xf0, 0x7, 0x28, 0x2, 0x2, 0xef, 
    0xee, 0x3, 0x2, 0x2, 0x2, 0xef, 0xf0, 0x3, 0x2, 0x2, 0x2, 0xf0, 0xf1, 
    0x3, 0x2, 0x2, 0x2, 0xf1, 0xf4, 0x5, 0x5e, 0x30, 0x2, 0xf2, 0xf3, 0x7, 
    0x47, 0x2, 0x2, 0xf3, 0xf5, 0x7, 0x59, 0x2, 0x2, 0xf4, 0xf2, 0x3, 0x2, 
    0x2, 0x2, 0xf4, 0xf5, 0x3, 0x2, 0x2, 0x2, 0xf5, 0xf6, 0x3, 0x2, 0x2, 
    0x2, 0xf6, 0xf7, 0x7, 0x45, 0x2, 0x2, 0xf7, 0x7, 0x3, 0x2, 0x2, 0x2, 
    0xf8, 0xfa, 0x5, 0xc, 0x7, 0x2, 0xf9, 0xf8, 0x3, 0x2, 0x2, 0x2, 0xfa, 
    0xfd, 0x3, 0x2, 0x2, 0x2, 0xfb, 0xf9, 0x3, 0x2, 0x2, 0x2, 0xfb, 0xfc, 
    0x3, 0x2, 0x2, 0x2, 0xfc, 0x102, 0x3, 0x2, 0x2, 0x2, 0xfd, 0xfb, 0x3, 
    0x2, 0x2, 0x2, 0xfe, 0x103, 0x5, 0x10, 0x9, 0x2, 0xff, 0x103, 0x5, 0x18, 
    0xd, 0x2, 0x100, 0x103, 0x5, 0x20, 0x11, 0x2, 0x101, 0x103, 0x5, 0x70, 
    0x39, 0x2, 0x102, 0xfe, 0x3, 0x2, 0x2, 0x2, 0x102, 0xff, 0x3, 0x2, 0x2, 
    0x2, 0x102, 0x100, 0x3, 0x2, 0x2, 0x2, 0x102, 0x101, 0x3, 0x2, 0x2, 
    0x2, 0x103, 0x106, 0x3, 0x2, 0x2, 0x2, 0x104, 0x106, 0x7, 0x45, 0x2, 
    0x2, 0x105, 0xfb, 0x3, 0x2, 0x2, 0x2, 0x105, 0x104, 0x3, 0x2, 0x2, 0x2, 
    0x106, 0x9, 0x3, 0x2, 0x2, 0x2, 0x107, 0x10d, 0x5, 0xc, 0x7, 0x2, 0x108, 
    0x10d, 0x7, 0x20, 0x2, 0x2, 0x109, 0x10d, 0x7, 0x2c, 0x2, 0x2, 0x10a, 
    0x10d, 0x7, 0x30, 0x2, 0x2, 0x10b, 0x10d, 0x7, 0x33, 0x2, 0x2, 0x10c, 
    0x107, 0x3, 0x2, 0x2, 0x2, 0x10c, 0x108, 0x3, 0x2, 0x2, 0x2, 0x10c, 
    0x109, 0x3, 0x2, 0x2, 0x2, 0x10c, 0x10a, 0x3, 0x2, 0x2, 0x2, 0x10c, 
    0x10b, 0x3, 0x2, 0x2, 0x2, 0x10d, 0xb, 0x3, 0x2, 0x2, 0x2, 0x10e, 0x117, 
    0x5, 0x66, 0x34, 0x2, 0x10f, 0x117, 0x7, 0x25, 0x2, 0x2, 0x110, 0x117, 
    0x7, 0x24, 0x2, 0x2, 0x111, 0x117, 0x7, 0x23, 0x2, 0x2, 0x112, 0x117, 
    0x7, 0x28, 0x2, 0x2, 0x113, 0x117, 0x7, 0x3, 0x2, 0x2, 0x114, 0x117, 
    0x7, 0x14, 0x2, 0x2, 0x115, 0x117, 0x7, 0x29, 0x2, 0x2, 0x116, 0x10e, 
    0x3, 0x2, 0x2, 0x2, 0x116, 0x10f, 0x3, 0x2, 0x2, 0x2, 0x116, 0x110, 
    0x3, 0x2, 0x2, 0x2, 0x116, 0x111, 0x3, 0x2, 0x2, 0x2, 0x116, 0x112, 
    0x3, 0x2, 0x2, 0x2, 0x116, 0x113, 0x3, 0x2, 0x2, 0x2, 0x116, 0x114, 
    0x3, 0x2, 0x2, 0x2, 0x116, 0x115, 0x3, 0x2, 0x2, 0x2, 0x117, 0xd, 0x3, 
    0x2, 0x2, 0x2, 0x118, 0x11b, 0x7, 0x14, 0x2, 0x2, 0x119, 0x11b, 0x5, 
    0x66, 0x34, 0x2, 0x11a, 0x118, 0x3, 0x2, 0x2, 0x2, 0x11a, 0x119, 0x3, 
    0x2, 0x2, 0x2, 0x11b, 0xf, 0x3, 0x2, 0x2, 0x2, 0x11c, 0x11d, 0x7, 0xb, 
    0x2, 0x2, 0x11d, 0x11f, 0x7, 0x72, 0x2, 0x2, 0x11e, 0x120, 0x5, 0x12, 
    0xa, 0x2, 0x11f, 0x11e, 0x3, 0x2, 0x2, 0x2, 0x11f, 0x120, 0x3, 0x2, 
    0x2, 0x2, 0x120, 0x123, 0x3, 0x2, 0x2, 0x2, 0x121, 0x122, 0x7, 0x13, 
    0x2, 0x2, 0x122, 0x124, 0x5, 0xc6, 0x64, 0x2, 0x123, 0x121, 0x3, 0x2, 
    0x2, 0x2, 0x123, 0x124, 0x3, 0x2, 0x2, 0x2, 0x124, 0x127, 0x3, 0x2, 
    0x2, 0x2, 0x125, 0x126, 0x7, 0x1a, 0x2, 0x2, 0x126, 0x128, 0x5, 0xc4, 
    0x63, 0x2, 0x127, 0x125, 0x3, 0x2, 0x2, 0x2, 0x127, 0x128, 0x3, 0x2, 
    0x2, 0x2, 0x128, 0x129, 0x3, 0x2, 0x2, 0x2, 0x129, 0x12a, 0x5, 0x22, 
    0x12, 0x2, 0x12a, 0x11, 0x3, 0x2, 0x2, 0x2, 0x12b, 0x12c, 0x7, 0x4a, 
    0x2, 0x2, 0x12c, 0x131, 0x5, 0x14, 0xb, 0x2, 0x12d, 0x12e, 0x7, 0x46, 
    0x2, 0x2, 0x12e, 0x130, 0x5, 0x14, 0xb, 0x2, 0x12f, 0x12d, 0x3, 0x2, 
    0x2, 0x2, 0x130, 0x133, 0x3, 0x2, 0x2, 0x2, 0x131, 0x12f, 0x3, 0x2, 
    0x2, 0x2, 0x131, 0x132, 0x3, 0x2, 0x2, 0x2, 0x132, 0x134, 0x3, 0x2, 
    0x2, 0x2, 0x133, 0x131, 0x3, 0x2, 0x2, 0x2, 0x134, 0x135, 0x7, 0x49, 
    0x2, 0x2, 0x135, 0x13, 0x3, 0x2, 0x2, 0x2, 0x136, 0x138, 0x5, 0x66, 
    0x34, 0x2, 0x137, 0x136, 0x3, 0x2, 0x2, 0x2, 0x138, 0x13b, 0x3, 0x2, 
    0x2, 0x2, 0x139, 0x137, 0x3, 0x2, 0x2, 0x2, 0x139, 0x13a, 0x3, 0x2, 
    0x2, 0x2, 0x13a, 0x13c, 0x3, 0x2, 0x2, 0x2, 0x13b, 0x139, 0x3, 0x2, 
    0x2, 0x2, 0x13c, 0x13f, 0x7, 0x72, 0x2, 0x2, 0x13d, 0x13e, 0x7, 0x13, 
    0x2, 0x2, 0x13e, 0x140, 0x5, 0x16, 0xc, 0x2, 0x13f, 0x13d, 0x3, 0x2, 
    0x2, 0x2, 0x13f, 0x140, 0x3, 0x2, 0x2, 0x2, 0x140, 0x15, 0x3, 0x2, 0x2, 
    0x2, 0x141, 0x146, 0x5, 0xc6, 0x64, 0x2, 0x142, 0x143, 0x7, 0x5b, 0x2, 
    0x2, 0x143, 0x145, 0x5, 0xc6, 0x64, 0x2, 0x144, 0x142, 0x3, 0x2, 0x2, 
    0x2, 0x145, 0x148, 0x3, 0x2, 0x2, 0x2, 0x146, 0x144, 0x3, 0x2, 0x2, 
    0x2, 0x146, 0x147, 0x3, 0x2, 0x2, 0x2, 0x147, 0x17, 0x3, 0x2, 0x2, 0x2, 
    0x148, 0x146, 0x3, 0x2, 0x2, 0x2, 0x149, 0x14a, 0x7, 0x12, 0x2, 0x2, 
    0x14a, 0x14d, 0x7, 0x72, 0x2, 0x2, 0x14b, 0x14c, 0x7, 0x1a, 0x2, 0x2, 
    0x14c, 0x14e, 0x5, 0xc4, 0x63, 0x2, 0x14d, 0x14b, 0x3, 0x2, 0x2, 0x2, 
    0x14d, 0x14e, 0x3, 0x2, 0x2, 0x2, 0x14e, 0x14f, 0x3, 0x2, 0x2, 0x2, 
    0x14f, 0x151, 0x7, 0x41, 0x2, 0x2, 0x150, 0x152, 0x5, 0x1a, 0xe, 0x2, 
    0x151, 0x150, 0x3, 0x2, 0x2, 0x2, 0x151, 0x152, 0x3, 0x2, 0x2, 0x2, 
    0x152, 0x154, 0x3, 0x2, 0x2, 0x2, 0x153, 0x155, 0x7, 0x46, 0x2, 0x2, 
    0x154, 0x153, 0x3, 0x2, 0x2, 0x2, 0x154, 0x155, 0x3, 0x2, 0x2, 0x2, 
    0x155, 0x157, 0x3, 0x2, 0x2, 0x2, 0x156, 0x158, 0x5, 0x1e, 0x10, 0x2, 
    0x157, 0x156, 0x3, 0x2, 0x2, 0x2, 0x157, 0x158, 0x3, 0x2, 0x2, 0x2, 
    0x158, 0x159, 0x3, 0x2, 0x2, 0x2, 0x159, 0x15a, 0x7, 0x42, 0x2, 0x2, 
    0x15a, 0x19, 0x3, 0x2, 0x2, 0x2, 0x15b, 0x160, 0x5, 0x1c, 0xf, 0x2, 
    0x15c, 0x15d, 0x7, 0x46, 0x2, 0x2, 0x15d, 0x15f, 0x5, 0x1c, 0xf, 0x2, 
    0x15e, 0x15c, 0x3, 0x2, 0x2, 0x2, 0x15f, 0x162, 0x3, 0x2, 0x2, 0x2, 
    0x160, 0x15e, 0x3, 0x2, 0x2, 0x2, 0x160, 0x161, 0x3, 0x2, 0x2, 0x2, 
    0x161, 0x1b, 0x3, 0x2, 0x2, 0x2, 0x162, 0x160, 0x3, 0x2, 0x2, 0x2, 0x163, 
    0x165, 0x5, 0x66, 0x34, 0x2, 0x164, 0x163, 0x3, 0x2, 0x2, 0x2, 0x165, 
    0x168, 0x3, 0x2, 0x2, 0x2, 0x166, 0x164, 0x3, 0x2, 0x2, 0x2, 0x166, 
    0x167, 0x3, 0x2, 0x2, 0x2, 0x167, 0x169, 0x3, 0x2, 0x2, 0x2, 0x168, 
    0x166, 0x3, 0x2, 0x2, 0x2, 0x169, 0x16b, 0x7, 0x72, 0x2, 0x2, 0x16a, 
    0x16c, 0x5, 0xd0, 0x69, 0x2, 0x16b, 0x16a, 0x3, 0x2, 0x2, 0x2, 0x16b, 
    0x16c, 0x3, 0x2, 0x2, 0x2, 0x16c, 0x16e, 0x3, 0x2, 0x2, 0x2, 0x16d, 
    0x16f, 0x5, 0x22, 0x12, 0x2, 0x16e, 0x16d, 0x3, 0x2, 0x2, 0x2, 0x16e, 
    0x16f, 0x3, 0x2, 0x2, 0x2, 0x16f, 0x1d, 0x3, 0x2, 0x2, 0x2, 0x170, 0x174, 
    0x7, 0x45, 0x2, 0x2, 0x171, 0x173, 0x5, 0x26, 0x14, 0x2, 0x172, 0x171, 
    0x3, 0x2, 0x2, 0x2, 0x173, 0x176, 0x3, 0x2, 0x2, 0x2, 0x174, 0x172, 
    0x3, 0x2, 0x2, 0x2, 0x174, 0x175, 0x3, 0x2, 0x2, 0x2, 0x175, 0x1f, 0x3, 
    0x2, 0x2, 0x2, 0x176, 0x174, 0x3, 0x2, 0x2, 0x2, 0x177, 0x178, 0x7, 
    0x1e, 0x2, 0x2, 0x178, 0x17a, 0x7, 0x72, 0x2, 0x2, 0x179, 0x17b, 0x5, 
    0x12, 0xa, 0x2, 0x17a, 0x179, 0x3, 0x2, 0x2, 0x2, 0x17a, 0x17b, 0x3, 
    0x2, 0x2, 0x2, 0x17b, 0x17e, 0x3, 0x2, 0x2, 0x2, 0x17c, 0x17d, 0x7, 
    0x13, 0x2, 0x2, 0x17d, 0x17f, 0x5, 0xc4, 0x63, 0x2, 0x17e, 0x17c, 0x3, 
    0x2, 0x2, 0x2, 0x17e, 0x17f, 0x3, 0x2, 0x2, 0x2, 0x17f, 0x180, 0x3, 
    0x2, 0x2, 0x2, 0x180, 0x181, 0x5, 0x24, 0x13, 0x2, 0x181, 0x21, 0x3, 
    0x2, 0x2, 0x2, 0x182, 0x186, 0x7, 0x41, 0x2, 0x2, 0x183, 0x185, 0x5, 
    0x26, 0x14, 0x2, 0x184, 0x183, 0x3, 0x2, 0x2, 0x2, 0x185, 0x188, 0x3, 
    0x2, 0x2, 0x2, 0x186, 0x184, 0x3, 0x2, 0x2, 0x2, 0x186, 0x187, 0x3, 
    0x2, 0x2, 0x2, 0x187, 0x189, 0x3, 0x2, 0x2, 0x2, 0x188, 0x186, 0x3, 
    0x2, 0x2, 0x2, 0x189, 0x18a, 0x7, 0x42, 0x2, 0x2, 0x18a, 0x23, 0x3, 
    0x2, 0x2, 0x2, 0x18b, 0x18f, 0x7, 0x41, 0x2, 0x2, 0x18c, 0x18e, 0x5, 
    0x38, 0x1d, 0x2, 0x18d, 0x18c, 0x3, 0x2, 0x2, 0x2, 0x18e, 0x191, 0x3, 
    0x2, 0x2, 0x2, 0x18f, 0x18d, 0x3, 0x2, 0x2, 0x2, 0x18f, 0x190, 0x3, 
    0x2, 0x2, 0x2, 0x190, 0x192, 0x3, 0x2, 0x2, 0x2, 0x191, 0x18f, 0x3, 
    0x2, 0x2, 0x2, 0x192, 0x193, 0x7, 0x42, 0x2, 0x2, 0x193, 0x25, 0x3, 
    0x2, 0x2, 0x2, 0x194, 0x1a1, 0x7, 0x45, 0x2, 0x2, 0x195, 0x197, 0x7, 
    0x28, 0x2, 0x2, 0x196, 0x195, 0x3, 0x2, 0x2, 0x2, 0x196, 0x197, 0x3, 
    0x2, 0x2, 0x2, 0x197, 0x198, 0x3, 0x2, 0x2, 0x2, 0x198, 0x1a1, 0x5, 
    0x80, 0x41, 0x2, 0x199, 0x19b, 0x5, 0xa, 0x6, 0x2, 0x19a, 0x199, 0x3, 
    0x2, 0x2, 0x2, 0x19b, 0x19e, 0x3, 0x2, 0x2, 0x2, 0x19c, 0x19a, 0x3, 
    0x2, 0x2, 0x2, 0x19c, 0x19d, 0x3, 0x2, 0x2, 0x2, 0x19d, 0x19f, 0x3, 
    0x2, 0x2, 0x2, 0x19e, 0x19c, 0x3, 0x2, 0x2, 0x2, 0x19f, 0x1a1, 0x5, 
    0x28, 0x15, 0x2, 0x1a0, 0x194, 0x3, 0x2, 0x2, 0x2, 0x1a0, 0x196, 0x3, 
    0x2, 0x2, 0x2, 0x1a0, 0x19c, 0x3, 0x2, 0x2, 0x2, 0x1a1, 0x27, 0x3, 0x2, 
    0x2, 0x2, 0x1a2, 0x1ac, 0x5, 0x2a, 0x16, 0x2, 0x1a3, 0x1ac, 0x5, 0x30, 
    0x19, 0x2, 0x1a4, 0x1ac, 0x5, 0x36, 0x1c, 0x2, 0x1a5, 0x1ac, 0x5, 0x34, 
    0x1b, 0x2, 0x1a6, 0x1ac, 0x5, 0x32, 0x1a, 0x2, 0x1a7, 0x1ac, 0x5, 0x20, 
    0x11, 0x2, 0x1a8, 0x1ac, 0x5, 0x70, 0x39, 0x2, 0x1a9, 0x1ac, 0x5, 0x10, 
    0x9, 0x2, 0x1aa, 0x1ac, 0x5, 0x18, 0xd, 0x2, 0x1ab, 0x1a2, 0x3, 0x2, 
    0x2, 0x2, 0x1ab, 0x1a3, 0x3, 0x2, 0x2, 0x2, 0x1ab, 0x1a4, 0x3, 0x2, 
    0x2, 0x2, 0x1ab, 0x1a5, 0x3, 0x2, 0x2, 0x2, 0x1ab, 0x1a6, 0x3, 0x2, 
    0x2, 0x2, 0x1ab, 0x1a7, 0x3, 0x2, 0x2, 0x2, 0x1ab, 0x1a8, 0x3, 0x2, 
    0x2, 0x2, 0x1ab, 0x1a9, 0x3, 0x2, 0x2, 0x2, 0x1ab, 0x1aa, 0x3, 0x2, 
    0x2, 0x2, 0x1ac, 0x29, 0x3, 0x2, 0x2, 0x2, 0x1ad, 0x1ae, 0x5, 0x2e, 
    0x18, 0x2, 0x1ae, 0x1af, 0x7, 0x72, 0x2, 0x2, 0x1af, 0x1b4, 0x5, 0x56, 
    0x2c, 0x2, 0x1b0, 0x1b1, 0x7, 0x43, 0x2, 0x2, 0x1b1, 0x1b3, 0x7, 0x44, 
    0x2, 0x2, 0x1b2, 0x1b0, 0x3, 0x2, 0x2, 0x2, 0x1b3, 0x1b6, 0x3, 0x2, 
    0x2, 0x2, 0x1b4, 0x1b2, 0x3, 0x2, 0x2, 0x2, 0x1b4, 0x1b5, 0x3, 0x2, 
    0x2, 0x2, 0x1b5, 0x1b9, 0x3, 0x2, 0x2, 0x2, 0x1b6, 0x1b4, 0x3, 0x2, 
    0x2, 0x2, 0x1b7, 0x1b8, 0x7, 0x2f, 0x2, 0x2, 0x1b8, 0x1ba, 0x5, 0x54, 
    0x2b, 0x2, 0x1b9, 0x1b7, 0x3, 0x2, 0x2, 0x2, 0x1b9, 0x1ba, 0x3, 0x2, 
    0x2, 0x2, 0x1ba, 0x1bb, 0x3, 0x2, 0x2, 0x2, 0x1bb, 0x1bc, 0x5, 0x2c, 
    0x17, 0x2, 0x1bc, 0x2b, 0x3, 0x2, 0x2, 0x2, 0x1bd, 0x1c0, 0x5, 0x80, 
    0x41, 0x2, 0x1be, 0x1c0, 0x7, 0x45, 0x2, 0x2, 0x1bf, 0x1bd, 0x3, 0x2, 
    0x2, 0x2, 0x1bf, 0x1be, 0x3, 0x2, 0x2, 0x2, 0x1c0, 0x2d, 0x3, 0x2, 0x2, 
    0x2, 0x1c1, 0x1c4, 0x5, 0xc6, 0x64, 0x2, 0x1c2, 0x1c4, 0x7, 0x32, 0x2, 
    0x2, 0x1c3, 0x1c1, 0x3, 0x2, 0x2, 0x2, 0x1c3, 0x1c2, 0x3, 0x2, 0x2, 
    0x2, 0x1c4, 0x2f, 0x3, 0x2, 0x2, 0x2, 0x1c5, 0x1c6, 0x5, 0x12, 0xa, 
    0x2, 0x1c6, 0x1c7, 0x5, 0x2a, 0x16, 0x2, 0x1c7, 0x31, 0x3, 0x2, 0x2, 
    0x2, 0x1c8, 0x1c9, 0x5, 0x12, 0xa, 0x2, 0x1c9, 0x1ca, 0x5, 0x34, 0x1b, 
    0x2, 0x1ca, 0x33, 0x3, 0x2, 0x2, 0x2, 0x1cb, 0x1cc, 0x7, 0x72, 0x2, 
    0x2, 0x1cc, 0x1cf, 0x5, 0x56, 0x2c, 0x2, 0x1cd, 0x1ce, 0x7, 0x2f, 0x2, 
    0x2, 0x1ce, 0x1d0, 0x5, 0x54, 0x2b, 0x2, 0x1cf, 0x1cd, 0x3, 0x2, 0x2, 
    0x2, 0x1cf, 0x1d0, 0x3, 0x2, 0x2, 0x2, 0x1d0, 0x1d1, 0x3, 0x2, 0x2, 
    0x2, 0x1d1, 0x1d2, 0x5, 0x80, 0x41, 0x2, 0x1d2, 0x35, 0x3, 0x2, 0x2, 
    0x2, 0x1d3, 0x1d4, 0x5, 0xc6, 0x64, 0x2, 0x1d4, 0x1d5, 0x5, 0x46, 0x24, 
    0x2, 0x1d5, 0x1d6, 0x7, 0x45, 0x2, 0x2, 0x1d6, 0x37, 0x3, 0x2, 0x2, 
    0x2, 0x1d7, 0x1d9, 0x5, 0xa, 0x6, 0x2, 0x1d8, 0x1d7, 0x3, 0x2, 0x2, 
    0x2, 0x1d9, 0x1dc, 0x3, 0x2, 0x2, 0x2, 0x1da, 0x1d8, 0x3, 0x2, 0x2, 
    0x2, 0x1da, 0x1db, 0x3, 0x2, 0x2, 0x2, 0x1db, 0x1dd, 0x3, 0x2, 0x2, 
    0x2, 0x1dc, 0x1da, 0x3, 0x2, 0x2, 0x2, 0x1dd, 0x1e0, 0x5, 0x3a, 0x1e, 
    0x2, 0x1de, 0x1e0, 0x7, 0x45, 0x2, 0x2, 0x1df, 0x1da, 0x3, 0x2, 0x2, 
    0x2, 0x1df, 0x1de, 0x3, 0x2, 0x2, 0x2, 0x1e0, 0x39, 0x3, 0x2, 0x2, 0x2, 
    0x1e1, 0x1e9, 0x5, 0x3c, 0x1f, 0x2, 0x1e2, 0x1e9, 0x5, 0x40, 0x21, 0x2, 
    0x1e3, 0x1e9, 0x5, 0x44, 0x23, 0x2, 0x1e4, 0x1e9, 0x5, 0x20, 0x11, 0x2, 
    0x1e5, 0x1e9, 0x5, 0x70, 0x39, 0x2, 0x1e6, 0x1e9, 0x5, 0x10, 0x9, 0x2, 
    0x1e7, 0x1e9, 0x5, 0x18, 0xd, 0x2, 0x1e8, 0x1e1, 0x3, 0x2, 0x2, 0x2, 
    0x1e8, 0x1e2, 0x3, 0x2, 0x2, 0x2, 0x1e8, 0x1e3, 0x3, 0x2, 0x2, 0x2, 
    0x1e8, 0x1e4, 0x3, 0x2, 0x2, 0x2, 0x1e8, 0x1e5, 0x3, 0x2, 0x2, 0x2, 
    0x1e8, 0x1e6, 0x3, 0x2, 0x2, 0x2, 0x1e8, 0x1e7, 0x3, 0x2, 0x2, 0x2, 
    0x1e9, 0x3b, 0x3, 0x2, 0x2, 0x2, 0x1ea, 0x1eb, 0x5, 0xc6, 0x64, 0x2, 
    0x1eb, 0x1f0, 0x5, 0x3e, 0x20, 0x2, 0x1ec, 0x1ed, 0x7, 0x46, 0x2, 0x2, 
    0x1ed, 0x1ef, 0x5, 0x3e, 0x20, 0x2, 0x1ee, 0x1ec, 0x3, 0x2, 0x2, 0x2, 
    0x1ef, 0x1f2, 0x3, 0x2, 0x2, 0x2, 0x1f0, 0x1ee, 0x3, 0x2, 0x2, 0x2, 
    0x1f0, 0x1f1, 0x3, 0x2, 0x2, 0x2, 0x1f1, 0x1f3, 0x3, 0x2, 0x2, 0x2, 
    0x1f2, 0x1f0, 0x3, 0x2, 0x2, 0x2, 0x1f3, 0x1f4, 0x7, 0x45, 0x2, 0x2, 
    0x1f4, 0x3d, 0x3, 0x2, 0x2, 0x2, 0x1f5, 0x1fa, 0x7, 0x72, 0x2, 0x2, 
    0x1f6, 0x1f7, 0x7, 0x43, 0x2, 0x2, 0x1f7, 0x1f9, 0x7, 0x44, 0x2, 0x2, 
    0x1f8, 0x1f6, 0x3, 0x2, 0x2, 0x2, 0x1f9, 0x1fc, 0x3, 0x2, 0x2, 0x2, 
    0x1fa, 0x1f8, 0x3, 0x2, 0x2, 0x2, 0x1fa, 0x1fb, 0x3, 0x2, 0x2, 0x2, 
    0x1fb, 0x1fd, 0x3, 0x2, 0x2, 0x2, 0x1fc, 0x1fa, 0x3, 0x2, 0x2, 0x2, 
    0x1fd, 0x1fe, 0x7, 0x48, 0x2, 0x2, 0x1fe, 0x1ff, 0x5, 0x4c, 0x27, 0x2, 
    0x1ff, 0x3f, 0x3, 0x2, 0x2, 0x2, 0x200, 0x202, 0x5, 0x42, 0x22, 0x2, 
    0x201, 0x200, 0x3, 0x2, 0x2, 0x2, 0x202, 0x205, 0x3, 0x2, 0x2, 0x2, 
    0x203, 0x201, 0x3, 0x2, 0x2, 0x2, 0x203, 0x204, 0x3, 0x2, 0x2, 0x2, 
    0x204, 0x210, 0x3, 0x2, 0x2, 0x2, 0x205, 0x203, 0x3, 0x2, 0x2, 0x2, 
    0x206, 0x211, 0x5, 0x2e, 0x18, 0x2, 0x207, 0x20b, 0x5, 0x12, 0xa, 0x2, 
    0x208, 0x20a, 0x5, 0x66, 0x34, 0x2, 0x209, 0x208, 0x3, 0x2, 0x2, 0x2, 
    0x20a, 0x20d, 0x3, 0x2, 0x2, 0x2, 0x20b, 0x209, 0x3, 0x2, 0x2, 0x2, 
    0x20b, 0x20c, 0x3, 0x2, 0x2, 0x2, 0x20c, 0x20e, 0x3, 0x2, 0x2, 0x2, 
    0x20d, 0x20b, 0x3, 0x2, 0x2, 0x2, 0x20e, 0x20f, 0x5, 0x2e, 0x18, 0x2, 
    0x20f, 0x211, 0x3, 0x2, 0x2, 0x2, 0x210, 0x206, 0x3, 0x2, 0x2, 0x2, 
    0x210, 0x207, 0x3, 0x2, 0x2, 0x2, 0x211, 0x212, 0x3, 0x2, 0x2, 0x2, 
    0x212, 0x213, 0x7, 0x72, 0x2, 0x2, 0x213, 0x218, 0x5, 0x56, 0x2c, 0x2, 
    0x214, 0x215, 0x7, 0x43, 0x2, 0x2, 0x215, 0x217, 0x7, 0x44, 0x2, 0x2, 
    0x216, 0x214, 0x3, 0x2, 0x2, 0x2, 0x217, 0x21a, 0x3, 0x2, 0x2, 0x2, 
    0x218, 0x216, 0x3, 0x2, 0x2, 0x2, 0x218, 0x219, 0x3, 0x2, 0x2, 0x2, 
    0x219, 0x21d, 0x3, 0x2, 0x2, 0x2, 0x21a, 0x218, 0x3, 0x2, 0x2, 0x2, 
    0x21b, 0x21c, 0x7, 0x2f, 0x2, 0x2, 0x21c, 0x21e, 0x5, 0x54, 0x2b, 0x2, 
    0x21d, 0x21b, 0x3, 0x2, 0x2, 0x2, 0x21d, 0x21e, 0x3, 0x2, 0x2, 0x2, 
    0x21e, 0x21f, 0x3, 0x2, 0x2, 0x2, 0x21f, 0x220, 0x5, 0x2c, 0x17, 0x2, 
    0x220, 0x41, 0x3, 0x2, 0x2, 0x2, 0x221, 0x228, 0x5, 0x66, 0x34, 0x2, 
    0x222, 0x228, 0x7, 0x25, 0x2, 0x2, 0x223, 0x228, 0x7, 0x3, 0x2, 0x2, 
    0x224, 0x228, 0x7, 0xe, 0x2, 0x2, 0x225, 0x228, 0x7, 0x28, 0x2, 0x2, 
    0x226, 0x228, 0x7, 0x29, 0x2, 0x2, 0x227, 0x221, 0x3, 0x2, 0x2, 0x2, 
    0x227, 0x222, 0x3, 0x2, 0x2, 0x2, 0x227, 0x223, 0x3, 0x2, 0x2, 0x2, 
    0x227, 0x224, 0x3, 0x2, 0x2, 0x2, 0x227, 0x225, 0x3, 0x2, 0x2, 0x2, 
    0x227, 0x226, 0x3, 0x2, 0x2, 0x2, 0x228, 0x43, 0x3, 0x2, 0x2, 0x2, 0x229, 
    0x22a, 0x5, 0x12, 0xa, 0x2, 0x22a, 0x22b, 0x5, 0x40, 0x21, 0x2, 0x22b, 
    0x45, 0x3, 0x2, 0x2, 0x2, 0x22c, 0x231, 0x5, 0x48, 0x25, 0x2, 0x22d, 
    0x22e, 0x7, 0x46, 0x2, 0x2, 0x22e, 0x230, 0x5, 0x48, 0x25, 0x2, 0x22f, 
    0x22d, 0x3, 0x2, 0x2, 0x2, 0x230, 0x233, 0x3, 0x2, 0x2, 0x2, 0x231, 
    0x22f, 0x3, 0x2, 0x2, 0x2, 0x231, 0x232, 0x3, 0x2, 0x2, 0x2, 0x232, 
    0x47, 0x3, 0x2, 0x2, 0x2, 0x233, 0x231, 0x3, 0x2, 0x2, 0x2, 0x234, 0x237, 
    0x5, 0x4a, 0x26, 0x2, 0x235, 0x236, 0x7, 0x48, 0x2, 0x2, 0x236, 0x238, 
    0x5, 0x4c, 0x27, 0x2, 0x237, 0x235, 0x3, 0x2, 0x2, 0x2, 0x237, 0x238, 
    0x3, 0x2, 0x2, 0x2, 0x238, 0x49, 0x3, 0x2, 0x2, 0x2, 0x239, 0x23e, 0x7, 
    0x72, 0x2, 0x2, 0x23a, 0x23b, 0x7, 0x43, 0x2, 0x2, 0x23b, 0x23d, 0x7, 
    0x44, 0x2, 0x2, 0x23c, 0x23a, 0x3, 0x2, 0x2, 0x2, 0x23d, 0x240, 0x3, 
    0x2, 0x2, 0x2, 0x23e, 0x23c, 0x3, 0x2, 0x2, 0x2, 0x23e, 0x23f, 0x3, 
    0x2, 0x2, 0x2, 0x23f, 0x4b, 0x3, 0x2, 0x2, 0x2, 0x240, 0x23e, 0x3, 0x2, 
    0x2, 0x2, 0x241, 0x244, 0x5, 0x4e, 0x28, 0x2, 0x242, 0x244, 0x5, 0xa6, 
    0x54, 0x2, 0x243, 0x241, 0x3, 0x2, 0x2, 0x2, 0x243, 0x242, 0x3, 0x2, 
    0x2, 0x2, 0x244, 0x4d, 0x3, 0x2, 0x2, 0x2, 0x245, 0x251, 0x7, 0x41, 
    0x2, 0x2, 0x246, 0x24b, 0x5, 0x4c, 0x27, 0x2, 0x247, 0x248, 0x7, 0x46, 
    0x2, 0x2, 0x248, 0x24a, 0x5, 0x4c, 0x27, 0x2, 0x249, 0x247, 0x3, 0x2, 
    0x2, 0x2, 0x24a, 0x24d, 0x3, 0x2, 0x2, 0x2, 0x24b, 0x249, 0x3, 0x2, 
    0x2, 0x2, 0x24b, 0x24c, 0x3, 0x2, 0x2, 0x2, 0x24c, 0x24f, 0x3, 0x2, 
    0x2, 0x2, 0x24d, 0x24b, 0x3, 0x2, 0x2, 0x2, 0x24e, 0x250, 0x7, 0x46, 
    0x2, 0x2, 0x24f, 0x24e, 0x3, 0x2, 0x2, 0x2, 0x24f, 0x250, 0x3, 0x2, 
    0x2, 0x2, 0x250, 0x252, 0x3, 0x2, 0x2, 0x2, 0x251, 0x246, 0x3, 0x2, 
    0x2, 0x2, 0x251, 0x252, 0x3, 0x2, 0x2, 0x2, 0x252, 0x253, 0x3, 0x2, 
    0x2, 0x2, 0x253, 0x254, 0x7, 0x42, 0x2, 0x2, 0x254, 0x4f, 0x3, 0x2, 
    0x2, 0x2, 0x255, 0x257, 0x7, 0x72, 0x2, 0x2, 0x256, 0x258, 0x5, 0xca, 
    0x66, 0x2, 0x257, 0x256, 0x3, 0x2, 0x2, 0x2, 0x257, 0x258, 0x3, 0x2, 
    0x2, 0x2, 0x258, 0x260, 0x3, 0x2, 0x2, 0x2, 0x259, 0x25a, 0x7, 0x47, 
    0x2, 0x2, 0x25a, 0x25c, 0x7, 0x72, 0x2, 0x2, 0x25b, 0x25d, 0x5, 0xca, 
    0x66, 0x2, 0x25c, 0x25b, 0x3, 0x2, 0x2, 0x2, 0x25c, 0x25d, 0x3, 0x2, 
    0x2, 0x2, 0x25d, 0x25f, 0x3, 0x2, 0x2, 0x2, 0x25e, 0x259, 0x3, 0x2, 
    0x2, 0x2, 0x25f, 0x262, 0x3, 0x2, 0x2, 0x2, 0x260, 0x25e, 0x3, 0x2, 
    0x2, 0x2, 0x260, 0x261, 0x3, 0x2, 0x2, 0x2, 0x261, 0x51, 0x3, 0x2, 0x2, 
    0x2, 0x262, 0x260, 0x3, 0x2, 0x2, 0x2, 0x263, 0x26a, 0x5, 0xc6, 0x64, 
    0x2, 0x264, 0x267, 0x7, 0x4d, 0x2, 0x2, 0x265, 0x266, 0x9, 0x2, 0x2, 
    0x2, 0x266, 0x268, 0x5, 0xc6, 0x64, 0x2, 0x267, 0x265, 0x3, 0x2, 0x2, 
    0x2, 0x267, 0x268, 0x3, 0x2, 0x2, 0x2, 0x268, 0x26a, 0x3, 0x2, 0x2, 
    0x2, 0x269, 0x263, 0x3, 0x2, 0x2, 0x2, 0x269, 0x264, 0x3, 0x2, 0x2, 
    0x2, 0x26a, 0x53, 0x3, 0x2, 0x2, 0x2, 0x26b, 0x270, 0x5, 0x5e, 0x30, 
    0x2, 0x26c, 0x26d, 0x7, 0x46, 0x2, 0x2, 0x26d, 0x26f, 0x5, 0x5e, 0x30, 
    0x2, 0x26e, 0x26c, 0x3, 0x2, 0x2, 0x2, 0x26f, 0x272, 0x3, 0x2, 0x2, 
    0x2, 0x270, 0x26e, 0x3, 0x2, 0x2, 0x2, 0x270, 0x271, 0x3, 0x2, 0x2, 
    0x2, 0x271, 0x55, 0x3, 0x2, 0x2, 0x2, 0x272, 0x270, 0x3, 0x2, 0x2, 0x2, 
    0x273, 0x275, 0x7, 0x3f, 0x2, 0x2, 0x274, 0x276, 0x5, 0x58, 0x2d, 0x2, 
    0x275, 0x274, 0x3, 0x2, 0x2, 0x2, 0x275, 0x276, 0x3, 0x2, 0x2, 0x2, 
    0x276, 0x277, 0x3, 0x2, 0x2, 0x2, 0x277, 0x278, 0x7, 0x40, 0x2, 0x2, 
    0x278, 0x57, 0x3, 0x2, 0x2, 0x2, 0x279, 0x27e, 0x5, 0x5a, 0x2e, 0x2, 
    0x27a, 0x27b, 0x7, 0x46, 0x2, 0x2, 0x27b, 0x27d, 0x5, 0x5a, 0x2e, 0x2, 
    0x27c, 0x27a, 0x3, 0x2, 0x2, 0x2, 0x27d, 0x280, 0x3, 0x2, 0x2, 0x2, 
    0x27e, 0x27c, 0x3, 0x2, 0x2, 0x2, 0x27e, 0x27f, 0x3, 0x2, 0x2, 0x2, 
    0x27f, 0x283, 0x3, 0x2, 0x2, 0x2, 0x280, 0x27e, 0x3, 0x2, 0x2, 0x2, 
    0x281, 0x282, 0x7, 0x46, 0x2, 0x2, 0x282, 0x284, 0x5, 0x5c, 0x2f, 0x2, 
    0x283, 0x281, 0x3, 0x2, 0x2, 0x2, 0x283, 0x284, 0x3, 0x2, 0x2, 0x2, 
    0x284, 0x287, 0x3, 0x2, 0x2, 0x2, 0x285, 0x287, 0x5, 0x5c, 0x2f, 0x2, 
    0x286, 0x279, 0x3, 0x2, 0x2, 0x2, 0x286, 0x285, 0x3, 0x2, 0x2, 0x2, 
    0x287, 0x59, 0x3, 0x2, 0x2, 0x2, 0x288, 0x28a, 0x5, 0xe, 0x8, 0x2, 0x289, 
    0x288, 0x3, 0x2, 0x2, 0x2, 0x28a, 0x28d, 0x3, 0x2, 0x2, 0x2, 0x28b, 
    0x289, 0x3, 0x2, 0x2, 0x2, 0x28b, 0x28c, 0x3, 0x2, 0x2, 0x2, 0x28c, 
    0x28e, 0x3, 0x2, 0x2, 0x2, 0x28d, 0x28b, 0x3, 0x2, 0x2, 0x2, 0x28e, 
    0x28f, 0x5, 0xc6, 0x64, 0x2, 0x28f, 0x290, 0x5, 0x4a, 0x26, 0x2, 0x290, 
    0x5b, 0x3, 0x2, 0x2, 0x2, 0x291, 0x293, 0x5, 0xe, 0x8, 0x2, 0x292, 0x291, 
    0x3, 0x2, 0x2, 0x2, 0x293, 0x296, 0x3, 0x2, 0x2, 0x2, 0x294, 0x292, 
    0x3, 0x2, 0x2, 0x2, 0x294, 0x295, 0x3, 0x2, 0x2, 0x2, 0x295, 0x297, 
    0x3, 0x2, 0x2, 0x2, 0x296, 0x294, 0x3, 0x2, 0x2, 0x2, 0x297, 0x298, 
    0x5, 0xc6, 0x64, 0x2, 0x298, 0x299, 0x7, 0x6d, 0x2, 0x2, 0x299, 0x29a, 
    0x5, 0x4a, 0x26, 0x2, 0x29a, 0x5d, 0x3, 0x2, 0x2, 0x2, 0x29b, 0x2a0, 
    0x7, 0x72, 0x2, 0x2, 0x29c, 0x29d, 0x7, 0x47, 0x2, 0x2, 0x29d, 0x29f, 
    0x7, 0x72, 0x2, 0x2, 0x29e, 0x29c, 0x3, 0x2, 0x2, 0x2, 0x29f, 0x2a2, 
    0x3, 0x2, 0x2, 0x2, 0x2a0, 0x29e, 0x3, 0x2, 0x2, 0x2, 0x2a0, 0x2a1, 
    0x3, 0x2, 0x2, 0x2, 0x2a1, 0x5f, 0x3, 0x2, 0x2, 0x2, 0x2a2, 0x2a0, 0x3, 
    0x2, 0x2, 0x2, 0x2a3, 0x2aa, 0x5, 0x62, 0x32, 0x2, 0x2a4, 0x2aa, 0x5, 
    0x64, 0x33, 0x2, 0x2a5, 0x2aa, 0x7, 0x3c, 0x2, 0x2, 0x2a6, 0x2aa, 0x7, 
    0x3d, 0x2, 0x2, 0x2a7, 0x2aa, 0x7, 0x3b, 0x2, 0x2, 0x2a8, 0x2aa, 0x7, 
    0x3e, 0x2, 0x2, 0x2a9, 0x2a3, 0x3, 0x2, 0x2, 0x2, 0x2a9, 0x2a4, 0x3, 
    0x2, 0x2, 0x2, 0x2a9, 0x2a5, 0x3, 0x2, 0x2, 0x2, 0x2a9, 0x2a6, 0x3, 
    0x2, 0x2, 0x2, 0x2a9, 0x2a7, 0x3, 0x2, 0x2, 0x2, 0x2a9, 0x2a8, 0x3, 
    0x2, 0x2, 0x2, 0x2aa, 0x61, 0x3, 0x2, 0x2, 0x2, 0x2ab, 0x2ac, 0x9, 0x3, 
    0x2, 0x2, 0x2ac, 0x63, 0x3, 0x2, 0x2, 0x2, 0x2ad, 0x2ae, 0x9, 0x4, 0x2, 
    0x2, 0x2ae, 0x65, 0x3, 0x2, 0x2, 0x2, 0x2af, 0x2b0, 0x7, 0x6c, 0x2, 
    0x2, 0x2b0, 0x2b7, 0x5, 0x5e, 0x30, 0x2, 0x2b1, 0x2b4, 0x7, 0x3f, 0x2, 
    0x2, 0x2b2, 0x2b5, 0x5, 0x68, 0x35, 0x2, 0x2b3, 0x2b5, 0x5, 0x6c, 0x37, 
    0x2, 0x2b4, 0x2b2, 0x3, 0x2, 0x2, 0x2, 0x2b4, 0x2b3, 0x3, 0x2, 0x2, 
    0x2, 0x2b4, 0x2b5, 0x3, 0x2, 0x2, 0x2, 0x2b5, 0x2b6, 0x3, 0x2, 0x2, 
    0x2, 0x2b6, 0x2b8, 0x7, 0x40, 0x2, 0x2, 0x2b7, 0x2b1, 0x3, 0x2, 0x2, 
    0x2, 0x2b7, 0x2b8, 0x3, 0x2, 0x2, 0x2, 0x2b8, 0x67, 0x3, 0x2, 0x2, 0x2, 
    0x2b9, 0x2be, 0x5, 0x6a, 0x36, 0x2, 0x2ba, 0x2bb, 0x7, 0x46, 0x2, 0x2, 
    0x2bb, 0x2bd, 0x5, 0x6a, 0x36, 0x2, 0x2bc, 0x2ba, 0x3, 0x2, 0x2, 0x2, 
    0x2bd, 0x2c0, 0x3, 0x2, 0x2, 0x2, 0x2be, 0x2bc, 0x3, 0x2, 0x2, 0x2, 
    0x2be, 0x2bf, 0x3, 0x2, 0x2, 0x2, 0x2bf, 0x69, 0x3, 0x2, 0x2, 0x2, 0x2c0, 
    0x2be, 0x3, 0x2, 0x2, 0x2, 0x2c1, 0x2c2, 0x7, 0x72, 0x2, 0x2, 0x2c2, 
    0x2c3, 0x7, 0x48, 0x2, 0x2, 0x2c3, 0x2c4, 0x5, 0x6c, 0x37, 0x2, 0x2c4, 
    0x6b, 0x3, 0x2, 0x2, 0x2, 0x2c5, 0x2c9, 0x5, 0xa6, 0x54, 0x2, 0x2c6, 
    0x2c9, 0x5, 0x66, 0x34, 0x2, 0x2c7, 0x2c9, 0x5, 0x6e, 0x38, 0x2, 0x2c8, 
    0x2c5, 0x3, 0x2, 0x2, 0x2, 0x2c8, 0x2c6, 0x3, 0x2, 0x2, 0x2, 0x2c8, 
    0x2c7, 0x3, 0x2, 0x2, 0x2, 0x2c9, 0x6d, 0x3, 0x2, 0x2, 0x2, 0x2ca, 0x2d3, 
    0x7, 0x41, 0x2, 0x2, 0x2cb, 0x2d0, 0x5, 0x6c, 0x37, 0x2, 0x2cc, 0x2cd, 
    0x7, 0x46, 0x2, 0x2, 0x2cd, 0x2cf, 0x5, 0x6c, 0x37, 0x2, 0x2ce, 0x2cc, 
    0x3, 0x2, 0x2, 0x2, 0x2cf, 0x2d2, 0x3, 0x2, 0x2, 0x2, 0x2d0, 0x2ce, 
    0x3, 0x2, 0x2, 0x2, 0x2d0, 0x2d1, 0x3, 0x2, 0x2, 0x2, 0x2d1, 0x2d4, 
    0x3, 0x2, 0x2, 0x2, 0x2d2, 0x2d0, 0x3, 0x2, 0x2, 0x2, 0x2d3, 0x2cb, 
    0x3, 0x2, 0x2, 0x2, 0x2d3, 0x2d4, 0x3, 0x2, 0x2, 0x2, 0x2d4, 0x2d6, 
    0x3, 0x2, 0x2, 0x2, 0x2d5, 0x2d7, 0x7, 0x46, 0x2, 0x2, 0x2d6, 0x2d5, 
    0x3, 0x2, 0x2, 0x2, 0x2d6, 0x2d7, 0x3, 0x2, 0x2, 0x2, 0x2d7, 0x2d8, 
    0x3, 0x2, 0x2, 0x2, 0x2d8, 0x2d9, 0x7, 0x42, 0x2, 0x2, 0x2d9, 0x6f, 
    0x3, 0x2, 0x2, 0x2, 0x2da, 0x2db, 0x7, 0x6c, 0x2, 0x2, 0x2db, 0x2dc, 
    0x7, 0x1e, 0x2, 0x2, 0x2dc, 0x2dd, 0x7, 0x72, 0x2, 0x2, 0x2dd, 0x2de, 
    0x5, 0x72, 0x3a, 0x2, 0x2de, 0x71, 0x3, 0x2, 0x2, 0x2, 0x2df, 0x2e3, 
    0x7, 0x41, 0x2, 0x2, 0x2e0, 0x2e2, 0x5, 0x74, 0x3b, 0x2, 0x2e1, 0x2e0, 
    0x3, 0x2, 0x2, 0x2, 0x2e2, 0x2e5, 0x3, 0x2, 0x2, 0x2, 0x2e3, 0x2e1, 
    0x3, 0x2, 0x2, 0x2, 0x2e3, 0x2e4, 0x3, 0x2, 0x2, 0x2, 0x2e4, 0x2e6, 
    0x3, 0x2, 0x2, 0x2, 0x2e5, 0x2e3, 0x3, 0x2, 0x2, 0x2, 0x2e6, 0x2e7, 
    0x7, 0x42, 0x2, 0x2, 0x2e7, 0x73, 0x3, 0x2, 0x2, 0x2, 0x2e8, 0x2ea, 
    0x5, 0xa, 0x6, 0x2, 0x2e9, 0x2e8, 0x3, 0x2, 0x2, 0x2, 0x2ea, 0x2ed, 
    0x3, 0x2, 0x2, 0x2, 0x2eb, 0x2e9, 0x3, 0x2, 0x2, 0x2, 0x2eb, 0x2ec, 
    0x3, 0x2, 0x2, 0x2, 0x2ec, 0x2ee, 0x3, 0x2, 0x2, 0x2, 0x2ed, 0x2eb, 
    0x3, 0x2, 0x2, 0x2, 0x2ee, 0x2f1, 0x5, 0x76, 0x3c, 0x2, 0x2ef, 0x2f1, 
    0x7, 0x45, 0x2, 0x2, 0x2f0, 0x2eb, 0x3, 0x2, 0x2, 0x2, 0x2f0, 0x2ef, 
    0x3, 0x2, 0x2, 0x2, 0x2f1, 0x75, 0x3, 0x2, 0x2, 0x2, 0x2f2, 0x2f3, 0x5, 
    0xc6, 0x64, 0x2, 0x2f3, 0x2f4, 0x5, 0x78, 0x3d, 0x2, 0x2f4, 0x2f5, 0x7, 
    0x45, 0x2, 0x2, 0x2f5, 0x307, 0x3, 0x2, 0x2, 0x2, 0x2f6, 0x2f8, 0x5, 
    0x10, 0x9, 0x2, 0x2f7, 0x2f9, 0x7, 0x45, 0x2, 0x2, 0x2f8, 0x2f7, 0x3, 
    0x2, 0x2, 0x2, 0x2f8, 0x2f9, 0x3, 0x2, 0x2, 0x2, 0x2f9, 0x307, 0x3, 
    0x2, 0x2, 0x2, 0x2fa, 0x2fc, 0x5, 0x20, 0x11, 0x2, 0x2fb, 0x2fd, 0x7, 
    0x45, 0x2, 0x2, 0x2fc, 0x2fb, 0x3, 0x2, 0x2, 0x2, 0x2fc, 0x2fd, 0x3, 
    0x2, 0x2, 0x2, 0x2fd, 0x307, 0x3, 0x2, 0x2, 0x2, 0x2fe, 0x300, 0x5, 
    0x18, 0xd, 0x2, 0x2ff, 0x301, 0x7, 0x45, 0x2, 0x2, 0x300, 0x2ff, 0x3, 
    0x2, 0x2, 0x2, 0x300, 0x301, 0x3, 0x2, 0x2, 0x2, 0x301, 0x307, 0x3, 
    0x2, 0x2, 0x2, 0x302, 0x304, 0x5, 0x70, 0x39, 0x2, 0x303, 0x305, 0x7, 
    0x45, 0x2, 0x2, 0x304, 0x303, 0x3, 0x2, 0x2, 0x2, 0x304, 0x305, 0x3, 
    0x2, 0x2, 0x2, 0x305, 0x307, 0x3, 0x2, 0x2, 0x2, 0x306, 0x2f2, 0x3, 
    0x2, 0x2, 0x2, 0x306, 0x2f6, 0x3, 0x2, 0x2, 0x2, 0x306, 0x2fa, 0x3, 
    0x2, 0x2, 0x2, 0x306, 0x2fe, 0x3, 0x2, 0x2, 0x2, 0x306, 0x302, 0x3, 
    0x2, 0x2, 0x2, 0x307, 0x77, 0x3, 0x2, 0x2, 0x2, 0x308, 0x30b, 0x5, 0x7a, 
    0x3e, 0x2, 0x309, 0x30b, 0x5, 0x7c, 0x3f, 0x2, 0x30a, 0x308, 0x3, 0x2, 
    0x2, 0x2, 0x30a, 0x309, 0x3, 0x2, 0x2, 0x2, 0x30b, 0x79, 0x3, 0x2, 0x2, 
    0x2, 0x30c, 0x30d, 0x7, 0x72, 0x2, 0x2, 0x30d, 0x30e, 0x7, 0x3f, 0x2, 
    0x2, 0x30e, 0x310, 0x7, 0x40, 0x2, 0x2, 0x30f, 0x311, 0x5, 0x7e, 0x40, 
    0x2, 0x310, 0x30f, 0x3, 0x2, 0x2, 0x2, 0x310, 0x311, 0x3, 0x2, 0x2, 
    0x2, 0x311, 0x7b, 0x3, 0x2, 0x2, 0x2, 0x312, 0x313, 0x5, 0x46, 0x24, 
    0x2, 0x313, 0x7d, 0x3, 0x2, 0x2, 0x2, 0x314, 0x315, 0x7, 0xe, 0x2, 0x2, 
    0x315, 0x316, 0x5, 0x6c, 0x37, 0x2, 0x316, 0x7f, 0x3, 0x2, 0x2, 0x2, 
    0x317, 0x31b, 0x7, 0x41, 0x2, 0x2, 0x318, 0x31a, 0x5, 0x82, 0x42, 0x2, 
    0x319, 0x318, 0x3, 0x2, 0x2, 0x2, 0x31a, 0x31d, 0x3, 0x2, 0x2, 0x2, 
    0x31b, 0x319, 0x3, 0x2, 0x2, 0x2, 0x31b, 0x31c, 0x3, 0x2, 0x2, 0x2, 
    0x31c, 0x31e, 0x3, 0x2, 0x2, 0x2, 0x31d, 0x31b, 0x3, 0x2, 0x2, 0x2, 
    0x31e, 0x31f, 0x7, 0x42, 0x2, 0x2, 0x31f, 0x81, 0x3, 0x2, 0x2, 0x2, 
    0x320, 0x321, 0x5, 0x84, 0x43, 0x2, 0x321, 0x322, 0x7, 0x45, 0x2, 0x2, 
    0x322, 0x326, 0x3, 0x2, 0x2, 0x2, 0x323, 0x326, 0x5, 0x88, 0x45, 0x2, 
    0x324, 0x326, 0x5, 0x86, 0x44, 0x2, 0x325, 0x320, 0x3, 0x2, 0x2, 0x2, 
    0x325, 0x323, 0x3, 0x2, 0x2, 0x2, 0x325, 0x324, 0x3, 0x2, 0x2, 0x2, 
    0x326, 0x83, 0x3, 0x2, 0x2, 0x2, 0x327, 0x329, 0x5, 0xe, 0x8, 0x2, 0x328, 
    0x327, 0x3, 0x2, 0x2, 0x2, 0x329, 0x32c, 0x3, 0x2, 0x2, 0x2, 0x32a, 
    0x328, 0x3, 0x2, 0x2, 0x2, 0x32a, 0x32b, 0x3, 0x2, 0x2, 0x2, 0x32b, 
    0x32d, 0x3, 0x2, 0x2, 0x2, 0x32c, 0x32a, 0x3, 0x2, 0x2, 0x2, 0x32d, 
    0x32e, 0x5, 0xc6, 0x64, 0x2, 0x32e, 0x32f, 0x5, 0x46, 0x24, 0x2, 0x32f, 
    0x85, 0x3, 0x2, 0x2, 0x2, 0x330, 0x332, 0x5, 0xc, 0x7, 0x2, 0x331, 0x330, 
    0x3, 0x2, 0x2, 0x2, 0x332, 0x335, 0x3, 0x2, 0x2, 0x2, 0x333, 0x331, 
    0x3, 0x2, 0x2, 0x2, 0x333, 0x334, 0x3, 0x2, 0x2, 0x2, 0x334, 0x338, 
    0x3, 0x2, 0x2, 0x2, 0x335, 0x333, 0x3, 0x2, 0x2, 0x2, 0x336, 0x339, 
    0x5, 0x10, 0x9, 0x2, 0x337, 0x339, 0x5, 0x20, 0x11, 0x2, 0x338, 0x336, 
    0x3, 0x2, 0x2, 0x2, 0x338, 0x337, 0x3, 0x2, 0x2, 0x2, 0x339, 0x33c, 
    0x3, 0x2, 0x2, 0x2, 0x33a, 0x33c, 0x7, 0x45, 0x2, 0x2, 0x33b, 0x333, 
    0x3, 0x2, 0x2, 0x2, 0x33b, 0x33a, 0x3, 0x2, 0x2, 0x2, 0x33c, 0x87, 0x3, 
    0x2, 0x2, 0x2, 0x33d, 0x3a6, 0x5, 0x80, 0x41, 0x2, 0x33e, 0x33f, 0x7, 
    0x4, 0x2, 0x2, 0x33f, 0x342, 0x5, 0xa6, 0x54, 0x2, 0x340, 0x341, 0x7, 
    0x4e, 0x2, 0x2, 0x341, 0x343, 0x5, 0xa6, 0x54, 0x2, 0x342, 0x340, 0x3, 
    0x2, 0x2, 0x2, 0x342, 0x343, 0x3, 0x2, 0x2, 0x2, 0x343, 0x344, 0x3, 
    0x2, 0x2, 0x2, 0x344, 0x345, 0x7, 0x45, 0x2, 0x2, 0x345, 0x3a6, 0x3, 
    0x2, 0x2, 0x2, 0x346, 0x347, 0x7, 0x18, 0x2, 0x2, 0x347, 0x348, 0x5, 
    0xa0, 0x51, 0x2, 0x348, 0x34b, 0x5, 0x88, 0x45, 0x2, 0x349, 0x34a, 0x7, 
    0x11, 0x2, 0x2, 0x34a, 0x34c, 0x5, 0x88, 0x45, 0x2, 0x34b, 0x349, 0x3, 
    0x2, 0x2, 0x2, 0x34b, 0x34c, 0x3, 0x2, 0x2, 0x2, 0x34c, 0x3a6, 0x3, 
    0x2, 0x2, 0x2, 0x34d, 0x34e, 0x7, 0x17, 0x2, 0x2, 0x34e, 0x34f, 0x7, 
    0x3f, 0x2, 0x2, 0x34f, 0x350, 0x5, 0x9a, 0x4e, 0x2, 0x350, 0x351, 0x7, 
    0x40, 0x2, 0x2, 0x351, 0x352, 0x5, 0x88, 0x45, 0x2, 0x352, 0x3a6, 0x3, 
    0x2, 0x2, 0x2, 0x353, 0x354, 0x7, 0x34, 0x2, 0x2, 0x354, 0x355, 0x5, 
    0xa0, 0x51, 0x2, 0x355, 0x356, 0x5, 0x88, 0x45, 0x2, 0x356, 0x3a6, 0x3, 
    0x2, 0x2, 0x2, 0x357, 0x358, 0x7, 0xf, 0x2, 0x2, 0x358, 0x359, 0x5, 
    0x88, 0x45, 0x2, 0x359, 0x35a, 0x7, 0x34, 0x2, 0x2, 0x35a, 0x35b, 0x5, 
    0xa0, 0x51, 0x2, 0x35b, 0x35c, 0x7, 0x45, 0x2, 0x2, 0x35c, 0x3a6, 0x3, 
    0x2, 0x2, 0x2, 0x35d, 0x35e, 0x7, 0x31, 0x2, 0x2, 0x35e, 0x368, 0x5, 
    0x80, 0x41, 0x2, 0x35f, 0x361, 0x5, 0x8a, 0x46, 0x2, 0x360, 0x35f, 0x3, 
    0x2, 0x2, 0x2, 0x361, 0x362, 0x3, 0x2, 0x2, 0x2, 0x362, 0x360, 0x3, 
    0x2, 0x2, 0x2, 0x362, 0x363, 0x3, 0x2, 0x2, 0x2, 0x363, 0x365, 0x3, 
    0x2, 0x2, 0x2, 0x364, 0x366, 0x5, 0x8e, 0x48, 0x2, 0x365, 0x364, 0x3, 
    0x2, 0x2, 0x2, 0x365, 0x366, 0x3, 0x2, 0x2, 0x2, 0x366, 0x369, 0x3, 
    0x2, 0x2, 0x2, 0x367, 0x369, 0x5, 0x8e, 0x48, 0x2, 0x368, 0x360, 0x3, 
    0x2, 0x2, 0x2, 0x368, 0x367, 0x3, 0x2, 0x2, 0x2, 0x369, 0x3a6, 0x3, 
    0x2, 0x2, 0x2, 0x36a, 0x36b, 0x7, 0x31, 0x2, 0x2, 0x36b, 0x36c, 0x5, 
    0x90, 0x49, 0x2, 0x36c, 0x370, 0x5, 0x80, 0x41, 0x2, 0x36d, 0x36f, 0x5, 
    0x8a, 0x46, 0x2, 0x36e, 0x36d, 0x3, 0x2, 0x2, 0x2, 0x36f, 0x372, 0x3, 
    0x2, 0x2, 0x2, 0x370, 0x36e, 0x3, 0x2, 0x2, 0x2, 0x370, 0x371, 0x3, 
    0x2, 0x2, 0x2, 0x371, 0x374, 0x3, 0x2, 0x2, 0x2, 0x372, 0x370, 0x3, 
    0x2, 0x2, 0x2, 0x373, 0x375, 0x5, 0x8e, 0x48, 0x2, 0x374, 0x373, 0x3, 
    0x2, 0x2, 0x2, 0x374, 0x375, 0x3, 0x2, 0x2, 0x2, 0x375, 0x3a6, 0x3, 
    0x2, 0x2, 0x2, 0x376, 0x377, 0x7, 0x2b, 0x2, 0x2, 0x377, 0x378, 0x5, 
    0xa0, 0x51, 0x2, 0x378, 0x37c, 0x7, 0x41, 0x2, 0x2, 0x379, 0x37b, 0x5, 
    0x96, 0x4c, 0x2, 0x37a, 0x379, 0x3, 0x2, 0x2, 0x2, 0x37b, 0x37e, 0x3, 
    0x2, 0x2, 0x2, 0x37c, 0x37a, 0x3, 0x2, 0x2, 0x2, 0x37c, 0x37d, 0x3, 
    0x2, 0x2, 0x2, 0x37d, 0x382, 0x3, 0x2, 0x2, 0x2, 0x37e, 0x37c, 0x3, 
    0x2, 0x2, 0x2, 0x37f, 0x381, 0x5, 0x98, 0x4d, 0x2, 0x380, 0x37f, 0x3, 
    0x2, 0x2, 0x2, 0x381, 0x384, 0x3, 0x2, 0x2, 0x2, 0x382, 0x380, 0x3, 
    0x2, 0x2, 0x2, 0x382, 0x383, 0x3, 0x2, 0x2, 0x2, 0x383, 0x385, 0x3, 
    0x2, 0x2, 0x2, 0x384, 0x382, 0x3, 0x2, 0x2, 0x2, 0x385, 0x386, 0x7, 
    0x42, 0x2, 0x2, 0x386, 0x3a6, 0x3, 0x2, 0x2, 0x2, 0x387, 0x388, 0x7, 
    0x2c, 0x2, 0x2, 0x388, 0x389, 0x5, 0xa0, 0x51, 0x2, 0x389, 0x38a, 0x5, 
    0x80, 0x41, 0x2, 0x38a, 0x3a6, 0x3, 0x2, 0x2, 0x2, 0x38b, 0x38d, 0x7, 
    0x26, 0x2, 0x2, 0x38c, 0x38e, 0x5, 0xa6, 0x54, 0x2, 0x38d, 0x38c, 0x3, 
    0x2, 0x2, 0x2, 0x38d, 0x38e, 0x3, 0x2, 0x2, 0x2, 0x38e, 0x38f, 0x3, 
    0x2, 0x2, 0x2, 0x38f, 0x3a6, 0x7, 0x45, 0x2, 0x2, 0x390, 0x391, 0x7, 
    0x2e, 0x2, 0x2, 0x391, 0x392, 0x5, 0xa6, 0x54, 0x2, 0x392, 0x393, 0x7, 
    0x45, 0x2, 0x2, 0x393, 0x3a6, 0x3, 0x2, 0x2, 0x2, 0x394, 0x396, 0x7, 
    0x6, 0x2, 0x2, 0x395, 0x397, 0x7, 0x72, 0x2, 0x2, 0x396, 0x395, 0x3, 
    0x2, 0x2, 0x2, 0x396, 0x397, 0x3, 0x2, 0x2, 0x2, 0x397, 0x398, 0x3, 
    0x2, 0x2, 0x2, 0x398, 0x3a6, 0x7, 0x45, 0x2, 0x2, 0x399, 0x39b, 0x7, 
    0xd, 0x2, 0x2, 0x39a, 0x39c, 0x7, 0x72, 0x2, 0x2, 0x39b, 0x39a, 0x3, 
    0x2, 0x2, 0x2, 0x39b, 0x39c, 0x3, 0x2, 0x2, 0x2, 0x39c, 0x39d, 0x3, 
    0x2, 0x2, 0x2, 0x39d, 0x3a6, 0x7, 0x45, 0x2, 0x2, 0x39e, 0x3a6, 0x7, 
    0x45, 0x2, 0x2, 0x39f, 0x3a0, 0x5, 0xa6, 0x54, 0x2, 0x3a0, 0x3a1, 0x7, 
    0x45, 0x2, 0x2, 0x3a1, 0x3a6, 0x3, 0x2, 0x2, 0x2, 0x3a2, 0x3a3, 0x7, 
    0x72, 0x2, 0x2, 0x3a3, 0x3a4, 0x7, 0x4e, 0x2, 0x2, 0x3a4, 0x3a6, 0x5, 
    0x88, 0x45, 0x2, 0x3a5, 0x33d, 0x3, 0x2, 0x2, 0x2, 0x3a5, 0x33e, 0x3, 
    0x2, 0x2, 0x2, 0x3a5, 0x346, 0x3, 0x2, 0x2, 0x2, 0x3a5, 0x34d, 0x3, 
    0x2, 0x2, 0x2, 0x3a5, 0x353, 0x3, 0x2, 0x2, 0x2, 0x3a5, 0x357, 0x3, 
    0x2, 0x2, 0x2, 0x3a5, 0x35d, 0x3, 0x2, 0x2, 0x2, 0x3a5, 0x36a, 0x3, 
    0x2, 0x2, 0x2, 0x3a5, 0x376, 0x3, 0x2, 0x2, 0x2, 0x3a5, 0x387, 0x3, 
    0x2, 0x2, 0x2, 0x3a5, 0x38b, 0x3, 0x2, 0x2, 0x2, 0x3a5, 0x390, 0x3, 
    0x2, 0x2, 0x2, 0x3a5, 0x394, 0x3, 0x2, 0x2, 0x2, 0x3a5, 0x399, 0x3, 
    0x2, 0x2, 0x2, 0x3a5, 0x39e, 0x3, 0x2, 0x2, 0x2, 0x3a5, 0x39f, 0x3, 
    0x2, 0x2, 0x2, 0x3a5, 0x3a2, 0x3, 0x2, 0x2, 0x2, 0x3a6, 0x89, 0x3, 0x2, 
    0x2, 0x2, 0x3a7, 0x3a8, 0x7, 0x9, 0x2, 0x2, 0x3a8, 0x3ac, 0x7, 0x3f, 
    0x2, 0x2, 0x3a9, 0x3ab, 0x5, 0xe, 0x8, 0x2, 0x3aa, 0x3a9, 0x3, 0x2, 
    0x2, 0x2, 0x3ab, 0x3ae, 0x3, 0x2, 0x2, 0x2, 0x3ac, 0x3aa, 0x3, 0x2, 
    0x2, 0x2, 0x3ac, 0x3ad, 0x3, 0x2, 0x2, 0x2, 0x3ad, 0x3af, 0x3, 0x2, 
    0x2, 0x2, 0x3ae, 0x3ac, 0x3, 0x2, 0x2, 0x2, 0x3af, 0x3b0, 0x5, 0x8c, 
    0x47, 0x2, 0x3b0, 0x3b1, 0x7, 0x72, 0x2, 0x2, 0x3b1, 0x3b2, 0x7, 0x40, 
    0x2, 0x2, 0x3b2, 0x3b3, 0x5, 0x80, 0x41, 0x2, 0x3b3, 0x8b, 0x3, 0x2, 
    0x2, 0x2, 0x3b4, 0x3b9, 0x5, 0x5e, 0x30, 0x2, 0x3b5, 0x3b6, 0x7, 0x5c, 
    0x2, 0x2, 0x3b6, 0x3b8, 0x5, 0x5e, 0x30, 0x2, 0x3b7, 0x3b5, 0x3, 0x2, 
    0x2, 0x2, 0x3b8, 0x3bb, 0x3, 0x2, 0x2, 0x2, 0x3b9, 0x3b7, 0x3, 0x2, 
    0x2, 0x2, 0x3b9, 0x3ba, 0x3, 0x2, 0x2, 0x2, 0x3ba, 0x8d, 0x3, 0x2, 0x2, 
    0x2, 0x3bb, 0x3b9, 0x3, 0x2, 0x2, 0x2, 0x3bc, 0x3bd, 0x7, 0x15, 0x2, 
    0x2, 0x3bd, 0x3be, 0x5, 0x80, 0x41, 0x2, 0x3be, 0x8f, 0x3, 0x2, 0x2, 
    0x2, 0x3bf, 0x3c0, 0x7, 0x3f, 0x2, 0x2, 0x3c0, 0x3c2, 0x5, 0x92, 0x4a, 
    0x2, 0x3c1, 0x3c3, 0x7, 0x45, 0x2, 0x2, 0x3c2, 0x3c1, 0x3, 0x2, 0x2, 
    0x2, 0x3c2, 0x3c3, 0x3, 0x2, 0x2, 0x2, 0x3c3, 0x3c4, 0x3, 0x2, 0x2, 
    0x2, 0x3c4, 0x3c5, 0x7, 0x40, 0x2, 0x2, 0x3c5, 0x91, 0x3, 0x2, 0x2, 
    0x2, 0x3c6, 0x3cb, 0x5, 0x94, 0x4b, 0x2, 0x3c7, 0x3c8, 0x7, 0x45, 0x2, 
    0x2, 0x3c8, 0x3ca, 0x5, 0x94, 0x4b, 0x2, 0x3c9, 0x3c7, 0x3, 0x2, 0x2, 
    0x2, 0x3ca, 0x3cd, 0x3, 0x2, 0x2, 0x2, 0x3cb, 0x3c9, 0x3, 0x2, 0x2, 
    0x2, 0x3cb, 0x3cc, 0x3, 0x2, 0x2, 0x2, 0x3cc, 0x93, 0x3, 0x2, 0x2, 0x2, 
    0x3cd, 0x3cb, 0x3, 0x2, 0x2, 0x2, 0x3ce, 0x3d0, 0x5, 0xe, 0x8, 0x2, 
    0x3cf, 0x3ce, 0x3, 0x2, 0x2, 0x2, 0x3d0, 0x3d3, 0x3, 0x2, 0x2, 0x2, 
    0x3d1, 0x3cf, 0x3, 0x2, 0x2, 0x2, 0x3d1, 0x3d2, 0x3, 0x2, 0x2, 0x2, 
    0x3d2, 0x3d4, 0x3, 0x2, 0x2, 0x2, 0x3d3, 0x3d1, 0x3, 0x2, 0x2, 0x2, 
    0x3d4, 0x3d5, 0x5, 0x50, 0x29, 0x2, 0x3d5, 0x3d6, 0x5, 0x4a, 0x26, 0x2, 
    0x3d6, 0x3d7, 0x7, 0x48, 0x2, 0x2, 0x3d7, 0x3d8, 0x5, 0xa6, 0x54, 0x2, 
    0x3d8, 0x95, 0x3, 0x2, 0x2, 0x2, 0x3d9, 0x3db, 0x5, 0x98, 0x4d, 0x2, 
    0x3da, 0x3d9, 0x3, 0x2, 0x2, 0x2, 0x3db, 0x3dc, 0x3, 0x2, 0x2, 0x2, 
    0x3dc, 0x3da, 0x3, 0x2, 0x2, 0x2, 0x3dc, 0x3dd, 0x3, 0x2, 0x2, 0x2, 
    0x3dd, 0x3df, 0x3, 0x2, 0x2, 0x2, 0x3de, 0x3e0, 0x5, 0x82, 0x42, 0x2, 
    0x3df, 0x3de, 0x3, 0x2, 0x2, 0x2, 0x3e0, 0x3e1, 0x3, 0x2, 0x2, 0x2, 
    0x3e1, 0x3df, 0x3, 0x2, 0x2, 0x2, 0x3e1, 0x3e2, 0x3, 0x2, 0x2, 0x2, 
    0x3e2, 0x97, 0x3, 0x2, 0x2, 0x2, 0x3e3, 0x3e6, 0x7, 0x8, 0x2, 0x2, 0x3e4, 
    0x3e7, 0x5, 0xa6, 0x54, 0x2, 0x3e5, 0x3e7, 0x7, 0x72, 0x2, 0x2, 0x3e6, 
    0x3e4, 0x3, 0x2, 0x2, 0x2, 0x3e6, 0x3e5, 0x3, 0x2, 0x2, 0x2, 0x3e7, 
    0x3e8, 0x3, 0x2, 0x2, 0x2, 0x3e8, 0x3ec, 0x7, 0x4e, 0x2, 0x2, 0x3e9, 
    0x3ea, 0x7, 0xe, 0x2, 0x2, 0x3ea, 0x3ec, 0x7, 0x4e, 0x2, 0x2, 0x3eb, 
    0x3e3, 0x3, 0x2, 0x2, 0x2, 0x3eb, 0x3e9, 0x3, 0x2, 0x2, 0x2, 0x3ec, 
    0x99, 0x3, 0x2, 0x2, 0x2, 0x3ed, 0x3fa, 0x5, 0x9e, 0x50, 0x2, 0x3ee, 
    0x3f0, 0x5, 0x9c, 0x4f, 0x2, 0x3ef, 0x3ee, 0x3, 0x2, 0x2, 0x2, 0x3ef, 
    0x3f0, 0x3, 0x2, 0x2, 0x2, 0x3f0, 0x3f1, 0x3, 0x2, 0x2, 0x2, 0x3f1, 
    0x3f3, 0x7, 0x45, 0x2, 0x2, 0x3f2, 0x3f4, 0x5, 0xa6, 0x54, 0x2, 0x3f3, 
    0x3f2, 0x3, 0x2, 0x2, 0x2, 0x3f3, 0x3f4, 0x3, 0x2, 0x2, 0x2, 0x3f4, 
    0x3f5, 0x3, 0x2, 0x2, 0x2, 0x3f5, 0x3f7, 0x7, 0x45, 0x2, 0x2, 0x3f6, 
    0x3f8, 0x5, 0xa2, 0x52, 0x2, 0x3f7, 0x3f6, 0x3, 0x2, 0x2, 0x2, 0x3f7, 
    0x3f8, 0x3, 0x2, 0x2, 0x2, 0x3f8, 0x3fa, 0x3, 0x2, 0x2, 0x2, 0x3f9, 
    0x3ed, 0x3, 0x2, 0x2, 0x2, 0x3f9, 0x3ef, 0x3, 0x2, 0x2, 0x2, 0x3fa, 
    0x9b, 0x3, 0x2, 0x2, 0x2, 0x3fb, 0x3fe, 0x5, 0x84, 0x43, 0x2, 0x3fc, 
    0x3fe, 0x5, 0xa2, 0x52, 0x2, 0x3fd, 0x3fb, 0x3, 0x2, 0x2, 0x2, 0x3fd, 
    0x3fc, 0x3, 0x2, 0x2, 0x2, 0x3fe, 0x9d, 0x3, 0x2, 0x2, 0x2, 0x3ff, 0x401, 
    0x5, 0xe, 0x8, 0x2, 0x400, 0x3ff, 0x3, 0x2, 0x2, 0x2, 0x401, 0x404, 
    0x3, 0x2, 0x2, 0x2, 0x402, 0x400, 0x3, 0x2, 0x2, 0x2, 0x402, 0x403, 
    0x3, 0x2, 0x2, 0x2, 0x403, 0x405, 0x3, 0x2, 0x2, 0x2, 0x404, 0x402, 
    0x3, 0x2, 0x2, 0x2, 0x405, 0x406, 0x5, 0xc6, 0x64, 0x2, 0x406, 0x407, 
    0x5, 0x4a, 0x26, 0x2, 0x407, 0x408, 0x7, 0x4e, 0x2, 0x2, 0x408, 0x409, 
    0x5, 0xa6, 0x54, 0x2, 0x409, 0x9f, 0x3, 0x2, 0x2, 0x2, 0x40a, 0x40b, 
    0x7, 0x3f, 0x2, 0x2, 0x40b, 0x40c, 0x5, 0xa6, 0x54, 0x2, 0x40c, 0x40d, 
    0x7, 0x40, 0x2, 0x2, 0x40d, 0xa1, 0x3, 0x2, 0x2, 0x2, 0x40e, 0x413, 
    0x5, 0xa6, 0x54, 0x2, 0x40f, 0x410, 0x7, 0x46, 0x2, 0x2, 0x410, 0x412, 
    0x5, 0xa6, 0x54, 0x2, 0x411, 0x40f, 0x3, 0x2, 0x2, 0x2, 0x412, 0x415, 
    0x3, 0x2, 0x2, 0x2, 0x413, 0x411, 0x3, 0x2, 0x2, 0x2, 0x413, 0x414, 
    0x3, 0x2, 0x2, 0x2, 0x414, 0xa3, 0x3, 0x2, 0x2, 0x2, 0x415, 0x413, 0x3, 
    0x2, 0x2, 0x2, 0x416, 0x417, 0x7, 0x72, 0x2, 0x2, 0x417, 0x419, 0x7, 
    0x3f, 0x2, 0x2, 0x418, 0x41a, 0x5, 0xa2, 0x52, 0x2, 0x419, 0x418, 0x3, 
    0x2, 0x2, 0x2, 0x419, 0x41a, 0x3, 0x2, 0x2, 0x2, 0x41a, 0x41b, 0x3, 
    0x2, 0x2, 0x2, 0x41b, 0x429, 0x7, 0x40, 0x2, 0x2, 0x41c, 0x41d, 0x7, 
    0x2d, 0x2, 0x2, 0x41d, 0x41f, 0x7, 0x3f, 0x2, 0x2, 0x41e, 0x420, 0x5, 
    0xa2, 0x52, 0x2, 0x41f, 0x41e, 0x3, 0x2, 0x2, 0x2, 0x41f, 0x420, 0x3, 
    0x2, 0x2, 0x2, 0x420, 0x421, 0x3, 0x2, 0x2, 0x2, 0x421, 0x429, 0x7, 
    0x40, 0x2, 0x2, 0x422, 0x423, 0x7, 0x2a, 0x2, 0x2, 0x423, 0x425, 0x7, 
    0x3f, 0x2, 0x2, 0x424, 0x426, 0x5, 0xa2, 0x52, 0x2, 0x425, 0x424, 0x3, 
    0x2, 0x2, 0x2, 0x425, 0x426, 0x3, 0x2, 0x2, 0x2, 0x426, 0x427, 0x3, 
    0x2, 0x2, 0x2, 0x427, 0x429, 0x7, 0x40, 0x2, 0x2, 0x428, 0x416, 0x3, 
    0x2, 0x2, 0x2, 0x428, 0x41c, 0x3, 0x2, 0x2, 0x2, 0x428, 0x422, 0x3, 
    0x2, 0x2, 0x2, 0x429, 0xa5, 0x3, 0x2, 0x2, 0x2, 0x42a, 0x42b, 0x8, 0x54, 
    0x1, 0x2, 0x42b, 0x44a, 0x5, 0xae, 0x58, 0x2, 0x42c, 0x44a, 0x5, 0xa4, 
    0x53, 0x2, 0x42d, 0x42e, 0x7, 0x21, 0x2, 0x2, 0x42e, 0x44a, 0x5, 0xb2, 
    0x5a, 0x2, 0x42f, 0x430, 0x7, 0x3f, 0x2, 0x2, 0x430, 0x431, 0x5, 0xc6, 
    0x64, 0x2, 0x431, 0x432, 0x7, 0x40, 0x2, 0x2, 0x432, 0x433, 0x5, 0xa6, 
    0x54, 0x17, 0x433, 0x44a, 0x3, 0x2, 0x2, 0x2, 0x434, 0x435, 0x9, 0x5, 
    0x2, 0x2, 0x435, 0x44a, 0x5, 0xa6, 0x54, 0x15, 0x436, 0x437, 0x9, 0x6, 
    0x2, 0x2, 0x437, 0x44a, 0x5, 0xa6, 0x54, 0x14, 0x438, 0x44a, 0x5, 0xa8, 
    0x55, 0x2, 0x439, 0x43a, 0x5, 0xc6, 0x64, 0x2, 0x43a, 0x440, 0x7, 0x6b, 
    0x2, 0x2, 0x43b, 0x43d, 0x5, 0xca, 0x66, 0x2, 0x43c, 0x43b, 0x3, 0x2, 
    0x2, 0x2, 0x43c, 0x43d, 0x3, 0x2, 0x2, 0x2, 0x43d, 0x43e, 0x3, 0x2, 
    0x2, 0x2, 0x43e, 0x441, 0x7, 0x72, 0x2, 0x2, 0x43f, 0x441, 0x7, 0x21, 
    0x2, 0x2, 0x440, 0x43c, 0x3, 0x2, 0x2, 0x2, 0x440, 0x43f, 0x3, 0x2, 
    0x2, 0x2, 0x441, 0x44a, 0x3, 0x2, 0x2, 0x2, 0x442, 0x443, 0x5, 0xb0, 
    0x59, 0x2, 0x443, 0x445, 0x7, 0x6b, 0x2, 0x2, 0x444, 0x446, 0x5, 0xca, 
    0x66, 0x2, 0x445, 0x444, 0x3, 0x2, 0x2, 0x2, 0x445, 0x446, 0x3, 0x2, 
    0x2, 0x2, 0x446, 0x447, 0x3, 0x2, 0x2, 0x2, 0x447, 0x448, 0x7, 0x21, 
    0x2, 0x2, 0x448, 0x44a, 0x3, 0x2, 0x2, 0x2, 0x449, 0x42a, 0x3, 0x2, 
    0x2, 0x2, 0x449, 0x42c, 0x3, 0x2, 0x2, 0x2, 0x449, 0x42d, 0x3, 0x2, 
    0x2, 0x2, 0x449, 0x42f, 0x3, 0x2, 0x2, 0x2, 0x449, 0x434, 0x3, 0x2, 
    0x2, 0x2, 0x449, 0x436, 0x3, 0x2, 0x2, 0x2, 0x449, 0x438, 0x3, 0x2, 
    0x2, 0x2, 0x449, 0x439, 0x3, 0x2, 0x2, 0x2, 0x449, 0x442, 0x3, 0x2, 
    0x2, 0x2, 0x44a, 0x49b, 0x3, 0x2, 0x2, 0x2, 0x44b, 0x44c, 0xc, 0x13, 
    0x2, 0x2, 0x44c, 0x44d, 0x9, 0x7, 0x2, 0x2, 0x44d, 0x49a, 0x5, 0xa6, 
    0x54, 0x14, 0x44e, 0x44f, 0xc, 0x12, 0x2, 0x2, 0x44f, 0x450, 0x9, 0x8, 
    0x2, 0x2, 0x450, 0x49a, 0x5, 0xa6, 0x54, 0x13, 0x451, 0x459, 0xc, 0x11, 
    0x2, 0x2, 0x452, 0x453, 0x7, 0x4a, 0x2, 0x2, 0x453, 0x45a, 0x7, 0x4a, 
    0x2, 0x2, 0x454, 0x455, 0x7, 0x49, 0x2, 0x2, 0x455, 0x456, 0x7, 0x49, 
    0x2, 0x2, 0x456, 0x45a, 0x7, 0x49, 0x2, 0x2, 0x457, 0x458, 0x7, 0x49, 
    0x2, 0x2, 0x458, 0x45a, 0x7, 0x49, 0x2, 0x2, 0x459, 0x452, 0x3, 0x2, 
    0x2, 0x2, 0x459, 0x454, 0x3, 0x2, 0x2, 0x2, 0x459, 0x457, 0x3, 0x2, 
    0x2, 0x2, 0x45a, 0x45b, 0x3, 0x2, 0x2, 0x2, 0x45b, 0x49a, 0x5, 0xa6, 
    0x54, 0x12, 0x45c, 0x45d, 0xc, 0x10, 0x2, 0x2, 0x45d, 0x45e, 0x9, 0x9, 
    0x2, 0x2, 0x45e, 0x49a, 0x5, 0xa6, 0x54, 0x11, 0x45f, 0x460, 0xc, 0xe, 
    0x2, 0x2, 0x460, 0x461, 0x9, 0xa, 0x2, 0x2, 0x461, 0x49a, 0x5, 0xa6, 
    0x54, 0xf, 0x462, 0x463, 0xc, 0xd, 0x2, 0x2, 0x463, 0x464, 0x7, 0x5b, 
    0x2, 0x2, 0x464, 0x49a, 0x5, 0xa6, 0x54, 0xe, 0x465, 0x466, 0xc, 0xc, 
    0x2, 0x2, 0x466, 0x467, 0x7, 0x5d, 0x2, 0x2, 0x467, 0x49a, 0x5, 0xa6, 
    0x54, 0xd, 0x468, 0x469, 0xc, 0xb, 0x2, 0x2, 0x469, 0x46a, 0x7, 0x5c, 
    0x2, 0x2, 0x46a, 0x49a, 0x5, 0xa6, 0x54, 0xc, 0x46b, 0x46c, 0xc, 0xa, 
    0x2, 0x2, 0x46c, 0x46d, 0x7, 0x53, 0x2, 0x2, 0x46d, 0x49a, 0x5, 0xa6, 
    0x54, 0xb, 0x46e, 0x46f, 0xc, 0x9, 0x2, 0x2, 0x46f, 0x470, 0x7, 0x54, 
    0x2, 0x2, 0x470, 0x49a, 0x5, 0xa6, 0x54, 0xa, 0x471, 0x472, 0xc, 0x8, 
    0x2, 0x2, 0x472, 0x473, 0x7, 0x4d, 0x2, 0x2, 0x473, 0x474, 0x5, 0xa6, 
    0x54, 0x2, 0x474, 0x475, 0x7, 0x4e, 0x2, 0x2, 0x475, 0x476, 0x5, 0xa6, 
    0x54, 0x9, 0x476, 0x49a, 0x3, 0x2, 0x2, 0x2, 0x477, 0x478, 0xc, 0x7, 
    0x2, 0x2, 0x478, 0x479, 0x9, 0xb, 0x2, 0x2, 0x479, 0x49a, 0x5, 0xa6, 
    0x54, 0x7, 0x47a, 0x47b, 0xc, 0x1b, 0x2, 0x2, 0x47b, 0x487, 0x7, 0x47, 
    0x2, 0x2, 0x47c, 0x488, 0x7, 0x72, 0x2, 0x2, 0x47d, 0x488, 0x5, 0xa4, 
    0x53, 0x2, 0x47e, 0x488, 0x7, 0x2d, 0x2, 0x2, 0x47f, 0x481, 0x7, 0x21, 
    0x2, 0x2, 0x480, 0x482, 0x5, 0xc2, 0x62, 0x2, 0x481, 0x480, 0x3, 0x2, 
    0x2, 0x2, 0x481, 0x482, 0x3, 0x2, 0x2, 0x2, 0x482, 0x483, 0x3, 0x2, 
    0x2, 0x2, 0x483, 0x488, 0x5, 0xb6, 0x5c, 0x2, 0x484, 0x485, 0x7, 0x2a, 
    0x2, 0x2, 0x485, 0x488, 0x5, 0xcc, 0x67, 0x2, 0x486, 0x488, 0x5, 0xbc, 
    0x5f, 0x2, 0x487, 0x47c, 0x3, 0x2, 0x2, 0x2, 0x487, 0x47d, 0x3, 0x2, 
    0x2, 0x2, 0x487, 0x47e, 0x3, 0x2, 0x2, 0x2, 0x487, 0x47f, 0x3, 0x2, 
    0x2, 0x2, 0x487, 0x484, 0x3, 0x2, 0x2, 0x2, 0x487, 0x486, 0x3, 0x2, 
    0x2, 0x2, 0x488, 0x49a, 0x3, 0x2, 0x2, 0x2, 0x489, 0x48a, 0xc, 0x1a, 
    0x2, 0x2, 0x48a, 0x48b, 0x7, 0x43, 0x2, 0x2, 0x48b, 0x48c, 0x5, 0xa6, 
    0x54, 0x2, 0x48c, 0x48d, 0x7, 0x44, 0x2, 0x2, 0x48d, 0x49a, 0x3, 0x2, 
    0x2, 0x2, 0x48e, 0x48f, 0xc, 0x16, 0x2, 0x2, 0x48f, 0x49a, 0x9, 0xc, 
    0x2, 0x2, 0x490, 0x491, 0xc, 0xf, 0x2, 0x2, 0x491, 0x492, 0x7, 0x1c, 
    0x2, 0x2, 0x492, 0x49a, 0x5, 0xc6, 0x64, 0x2, 0x493, 0x494, 0xc, 0x5, 
    0x2, 0x2, 0x494, 0x496, 0x7, 0x6b, 0x2, 0x2, 0x495, 0x497, 0x5, 0xca, 
    0x66, 0x2, 0x496, 0x495, 0x3, 0x2, 0x2, 0x2, 0x496, 0x497, 0x3, 0x2, 
    0x2, 0x2, 0x497, 0x498, 0x3, 0x2, 0x2, 0x2, 0x498, 0x49a, 0x7, 0x72, 
    0x2, 0x2, 0x499, 0x44b, 0x3, 0x2, 0x2, 0x2, 0x499, 0x44e, 0x3, 0x2, 
    0x2, 0x2, 0x499, 0x451, 0x3, 0x2, 0x2, 0x2, 0x499, 0x45c, 0x3, 0x2, 
    0x2, 0x2, 0x499, 0x45f, 0x3, 0x2, 0x2, 0x2, 0x499, 0x462, 0x3, 0x2, 
    0x2, 0x2, 0x499, 0x465, 0x3, 0x2, 0x2, 0x2, 0x499, 0x468, 0x3, 0x2, 
    0x2, 0x2, 0x499, 0x46b, 0x3, 0x2, 0x2, 0x2, 0x499, 0x46e, 0x3, 0x2, 
    0x2, 0x2, 0x499, 0x471, 0x3, 0x2, 0x2, 0x2, 0x499, 0x477, 0x3, 0x2, 
    0x2, 0x2, 0x499, 0x47a, 0x3, 0x2, 0x2, 0x2, 0x499, 0x489, 0x3, 0x2, 
    0x2, 0x2, 0x499, 0x48e, 0x3, 0x2, 0x2, 0x2, 0x499, 0x490, 0x3, 0x2, 
    0x2, 0x2, 0x499, 0x493, 0x3, 0x2, 0x2, 0x2, 0x49a, 0x49d, 0x3, 0x2, 
    0x2, 0x2, 0x49b, 0x499, 0x3, 0x2, 0x2, 0x2, 0x49b, 0x49c, 0x3, 0x2, 
    0x2, 0x2, 0x49c, 0xa7, 0x3, 0x2, 0x2, 0x2, 0x49d, 0x49b, 0x3, 0x2, 0x2, 
    0x2, 0x49e, 0x49f, 0x5, 0xaa, 0x56, 0x2, 0x49f, 0x4a0, 0x7, 0x6a, 0x2, 
    0x2, 0x4a0, 0x4a1, 0x5, 0xac, 0x57, 0x2, 0x4a1, 0xa9, 0x3, 0x2, 0x2, 
    0x2, 0x4a2, 0x4b3, 0x7, 0x72, 0x2, 0x2, 0x4a3, 0x4a5, 0x7, 0x3f, 0x2, 
    0x2, 0x4a4, 0x4a6, 0x5, 0x58, 0x2d, 0x2, 0x4a5, 0x4a4, 0x3, 0x2, 0x2, 
    0x2, 0x4a5, 0x4a6, 0x3, 0x2, 0x2, 0x2, 0x4a6, 0x4a7, 0x3, 0x2, 0x2, 
    0x2, 0x4a7, 0x4b3, 0x7, 0x40, 0x2, 0x2, 0x4a8, 0x4a9, 0x7, 0x3f, 0x2, 
    0x2, 0x4a9, 0x4ae, 0x7, 0x72, 0x2, 0x2, 0x4aa, 0x4ab, 0x7, 0x46, 0x2, 
    0x2, 0x4ab, 0x4ad, 0x7, 0x72, 0x2, 0x2, 0x4ac, 0x4aa, 0x3, 0x2, 0x2, 
    0x2, 0x4ad, 0x4b0, 0x3, 0x2, 0x2, 0x2, 0x4ae, 0x4ac, 0x3, 0x2, 0x2, 
    0x2, 0x4ae, 0x4af, 0x3, 0x2, 0x2, 0x2, 0x4af, 0x4b1, 0x3, 0x2, 0x2, 
    0x2, 0x4b0, 0x4ae, 0x3, 0x2, 0x2, 0x2, 0x4b1, 0x4b3, 0x7, 0x40, 0x2, 
    0x2, 0x4b2, 0x4a2, 0x3, 0x2, 0x2, 0x2, 0x4b2, 0x4a3, 0x3, 0x2, 0x2, 
    0x2, 0x4b2, 0x4a8, 0x3, 0x2, 0x2, 0x2, 0x4b3, 0xab, 0x3, 0x2, 0x2, 0x2, 
    0x4b4, 0x4b7, 0x5, 0xa6, 0x54, 0x2, 0x4b5, 0x4b7, 0x5, 0x80, 0x41, 0x2, 
    0x4b6, 0x4b4, 0x3, 0x2, 0x2, 0x2, 0x4b6, 0x4b5, 0x3, 0x2, 0x2, 0x2, 
    0x4b7, 0xad, 0x3, 0x2, 0x2, 0x2, 0x4b8, 0x4b9, 0x7, 0x3f, 0x2, 0x2, 
    0x4b9, 0x4ba, 0x5, 0xa6, 0x54, 0x2, 0x4ba, 0x4bb, 0x7, 0x40, 0x2, 0x2, 
    0x4bb, 0x4cb, 0x3, 0x2, 0x2, 0x2, 0x4bc, 0x4cb, 0x7, 0x2d, 0x2, 0x2, 
    0x4bd, 0x4cb, 0x7, 0x2a, 0x2, 0x2, 0x4be, 0x4cb, 0x5, 0x60, 0x31, 0x2, 
    0x4bf, 0x4cb, 0x7, 0x72, 0x2, 0x2, 0x4c0, 0x4c1, 0x5, 0x2e, 0x18, 0x2, 
    0x4c1, 0x4c2, 0x7, 0x47, 0x2, 0x2, 0x4c2, 0x4c3, 0x7, 0xb, 0x2, 0x2, 
    0x4c3, 0x4cb, 0x3, 0x2, 0x2, 0x2, 0x4c4, 0x4c8, 0x5, 0xc2, 0x62, 0x2, 
    0x4c5, 0x4c9, 0x5, 0xce, 0x68, 0x2, 0x4c6, 0x4c7, 0x7, 0x2d, 0x2, 0x2, 
    0x4c7, 0x4c9, 0x5, 0xd0, 0x69, 0x2, 0x4c8, 0x4c5, 0x3, 0x2, 0x2, 0x2, 
    0x4c8, 0x4c6, 0x3, 0x2, 0x2, 0x2, 0x4c9, 0x4cb, 0x3, 0x2, 0x2, 0x2, 
    0x4ca, 0x4b8, 0x3, 0x2, 0x2, 0x2, 0x4ca, 0x4bc, 0x3, 0x2, 0x2, 0x2, 
    0x4ca, 0x4bd, 0x3, 0x2, 0x2, 0x2, 0x4ca, 0x4be, 0x3, 0x2, 0x2, 0x2, 
    0x4ca, 0x4bf, 0x3, 0x2, 0x2, 0x2, 0x4ca, 0x4c0, 0x3, 0x2, 0x2, 0x2, 
    0x4ca, 0x4c4, 0x3, 0x2, 0x2, 0x2, 0x4cb, 0xaf, 0x3, 0x2, 0x2, 0x2, 0x4cc, 
    0x4cd, 0x5, 0x50, 0x29, 0x2, 0x4cd, 0x4ce, 0x7, 0x47, 0x2, 0x2, 0x4ce, 
    0x4d0, 0x3, 0x2, 0x2, 0x2, 0x4cf, 0x4cc, 0x3, 0x2, 0x2, 0x2, 0x4cf, 
    0x4d0, 0x3, 0x2, 0x2, 0x2, 0x4d0, 0x4d4, 0x3, 0x2, 0x2, 0x2, 0x4d1, 
    0x4d3, 0x5, 0x66, 0x34, 0x2, 0x4d2, 0x4d1, 0x3, 0x2, 0x2, 0x2, 0x4d3, 
    0x4d6, 0x3, 0x2, 0x2, 0x2, 0x4d4, 0x4d2, 0x3, 0x2, 0x2, 0x2, 0x4d4, 
    0x4d5, 0x3, 0x2, 0x2, 0x2, 0x4d5, 0x4d7, 0x3, 0x2, 0x2, 0x2, 0x4d6, 
    0x4d4, 0x3, 0x2, 0x2, 0x2, 0x4d7, 0x4d9, 0x7, 0x72, 0x2, 0x2, 0x4d8, 
    0x4da, 0x5, 0xca, 0x66, 0x2, 0x4d9, 0x4d8, 0x3, 0x2, 0x2, 0x2, 0x4d9, 
    0x4da, 0x3, 0x2, 0x2, 0x2, 0x4da, 0xb1, 0x3, 0x2, 0x2, 0x2, 0x4db, 0x4dc, 
    0x5, 0xc2, 0x62, 0x2, 0x4dc, 0x4dd, 0x5, 0xb4, 0x5b, 0x2, 0x4dd, 0x4de, 
    0x5, 0xba, 0x5e, 0x2, 0x4de, 0x4e5, 0x3, 0x2, 0x2, 0x2, 0x4df, 0x4e2, 
    0x5, 0xb4, 0x5b, 0x2, 0x4e0, 0x4e3, 0x5, 0xb8, 0x5d, 0x2, 0x4e1, 0x4e3, 
    0x5, 0xba, 0x5e, 0x2, 0x4e2, 0x4e0, 0x3, 0x2, 0x2, 0x2, 0x4e2, 0x4e1, 
    0x3, 0x2, 0x2, 0x2, 0x4e3, 0x4e5, 0x3, 0x2, 0x2, 0x2, 0x4e4, 0x4db, 
    0x3, 0x2, 0x2, 0x2, 0x4e4, 0x4df, 0x3, 0x2, 0x2, 0x2, 0x4e5, 0xb3, 0x3, 
    0x2, 0x2, 0x2, 0x4e6, 0x4e8, 0x7, 0x72, 0x2, 0x2, 0x4e7, 0x4e9, 0x5, 
    0xbe, 0x60, 0x2, 0x4e8, 0x4e7, 0x3, 0x2, 0x2, 0x2, 0x4e8, 0x4e9, 0x3, 
    0x2, 0x2, 0x2, 0x4e9, 0x4f1, 0x3, 0x2, 0x2, 0x2, 0x4ea, 0x4eb, 0x7, 
    0x47, 0x2, 0x2, 0x4eb, 0x4ed, 0x7, 0x72, 0x2, 0x2, 0x4ec, 0x4ee, 0x5, 
    0xbe, 0x60, 0x2, 0x4ed, 0x4ec, 0x3, 0x2, 0x2, 0x2, 0x4ed, 0x4ee, 0x3, 
    0x2, 0x2, 0x2, 0x4ee, 0x4f0, 0x3, 0x2, 0x2, 0x2, 0x4ef, 0x4ea, 0x3, 
    0x2, 0x2, 0x2, 0x4f0, 0x4f3, 0x3, 0x2, 0x2, 0x2, 0x4f1, 0x4ef, 0x3, 
    0x2, 0x2, 0x2, 0x4f1, 0x4f2, 0x3, 0x2, 0x2, 0x2, 0x4f2, 0x4f6, 0x3, 
    0x2, 0x2, 0x2, 0x4f3, 0x4f1, 0x3, 0x2, 0x2, 0x2, 0x4f4, 0x4f6, 0x5, 
    0xc8, 0x65, 0x2, 0x4f5, 0x4e6, 0x3, 0x2, 0x2, 0x2, 0x4f5, 0x4f4, 0x3, 
    0x2, 0x2, 0x2, 0x4f6, 0xb5, 0x3, 0x2, 0x2, 0x2, 0x4f7, 0x4f9, 0x7, 0x72, 
    0x2, 0x2, 0x4f8, 0x4fa, 0x5, 0xc0, 0x61, 0x2, 0x4f9, 0x4f8, 0x3, 0x2, 
    0x2, 0x2, 0x4f9, 0x4fa, 0x3, 0x2, 0x2, 0x2, 0x4fa, 0x4fb, 0x3, 0x2, 
    0x2, 0x2, 0x4fb, 0x4fc, 0x5, 0xba, 0x5e, 0x2, 0x4fc, 0xb7, 0x3, 0x2, 
    0x2, 0x2, 0x4fd, 0x519, 0x7, 0x43, 0x2, 0x2, 0x4fe, 0x503, 0x7, 0x44, 
    0x2, 0x2, 0x4ff, 0x500, 0x7, 0x43, 0x2, 0x2, 0x500, 0x502, 0x7, 0x44, 
    0x2, 0x2, 0x501, 0x4ff, 0x3, 0x2, 0x2, 0x2, 0x502, 0x505, 0x3, 0x2, 
    0x2, 0x2, 0x503, 0x501, 0x3, 0x2, 0x2, 0x2, 0x503, 0x504, 0x3, 0x2, 
    0x2, 0x2, 0x504, 0x506, 0x3, 0x2, 0x2, 0x2, 0x505, 0x503, 0x3, 0x2, 
    0x2, 0x2, 0x506, 0x51a, 0x5, 0x4e, 0x28, 0x2, 0x507, 0x508, 0x5, 0xa6, 
    0x54, 0x2, 0x508, 0x50f, 0x7, 0x44, 0x2, 0x2, 0x509, 0x50a, 0x7, 0x43, 
    0x2, 0x2, 0x50a, 0x50b, 0x5, 0xa6, 0x54, 0x2, 0x50b, 0x50c, 0x7, 0x44, 
    0x2, 0x2, 0x50c, 0x50e, 0x3, 0x2, 0x2, 0x2, 0x50d, 0x509, 0x3, 0x2, 
    0x2, 0x2, 0x50e, 0x511, 0x3, 0x2, 0x2, 0x2, 0x50f, 0x50d, 0x3, 0x2, 
    0x2, 0x2, 0x50f, 0x510, 0x3, 0x2, 0x2, 0x2, 0x510, 0x516, 0x3, 0x2, 
    0x2, 0x2, 0x511, 0x50f, 0x3, 0x2, 0x2, 0x2, 0x512, 0x513, 0x7, 0x43, 
    0x2, 0x2, 0x513, 0x515, 0x7, 0x44, 0x2, 0x2, 0x514, 0x512, 0x3, 0x2, 
    0x2, 0x2, 0x515, 0x518, 0x3, 0x2, 0x2, 0x2, 0x516, 0x514, 0x3, 0x2, 
    0x2, 0x2, 0x516, 0x517, 0x3, 0x2, 0x2, 0x2, 0x517, 0x51a, 0x3, 0x2, 
    0x2, 0x2, 0x518, 0x516, 0x3, 0x2, 0x2, 0x2, 0x519, 0x4fe, 0x3, 0x2, 
    0x2, 0x2, 0x519, 0x507, 0x3, 0x2, 0x2, 0x2, 0x51a, 0xb9, 0x3, 0x2, 0x2, 
    0x2, 0x51b, 0x51d, 0x5, 0xd0, 0x69, 0x2, 0x51c, 0x51e, 0x5, 0x22, 0x12, 
    0x2, 0x51d, 0x51c, 0x3, 0x2, 0x2, 0x2, 0x51d, 0x51e, 0x3, 0x2, 0x2, 
    0x2, 0x51e, 0xbb, 0x3, 0x2, 0x2, 0x2, 0x51f, 0x520, 0x5, 0xc2, 0x62, 
    0x2, 0x520, 0x521, 0x5, 0xce, 0x68, 0x2, 0x521, 0xbd, 0x3, 0x2, 0x2, 
    0x2, 0x522, 0x523, 0x7, 0x4a, 0x2, 0x2, 0x523, 0x526, 0x7, 0x49, 0x2, 
    0x2, 0x524, 0x526, 0x5, 0xca, 0x66, 0x2, 0x525, 0x522, 0x3, 0x2, 0x2, 
    0x2, 0x525, 0x524, 0x3, 0x2, 0x2, 0x2, 0x526, 0xbf, 0x3, 0x2, 0x2, 0x2, 
    0x527, 0x528, 0x7, 0x4a, 0x2, 0x2, 0x528, 0x52b, 0x7, 0x49, 0x2, 0x2, 
    0x529, 0x52b, 0x5, 0xc2, 0x62, 0x2, 0x52a, 0x527, 0x3, 0x2, 0x2, 0x2, 
    0x52a, 0x529, 0x3, 0x2, 0x2, 0x2, 0x52b, 0xc1, 0x3, 0x2, 0x2, 0x2, 0x52c, 
    0x52d, 0x7, 0x4a, 0x2, 0x2, 0x52d, 0x52e, 0x5, 0xc4, 0x63, 0x2, 0x52e, 
    0x52f, 0x7, 0x49, 0x2, 0x2, 0x52f, 0xc3, 0x3, 0x2, 0x2, 0x2, 0x530, 
    0x535, 0x5, 0xc6, 0x64, 0x2, 0x531, 0x532, 0x7, 0x46, 0x2, 0x2, 0x532, 
    0x534, 0x5, 0xc6, 0x64, 0x2, 0x533, 0x531, 0x3, 0x2, 0x2, 0x2, 0x534, 
    0x537, 0x3, 0x2, 0x2, 0x2, 0x535, 0x533, 0x3, 0x2, 0x2, 0x2, 0x535, 
    0x536, 0x3, 0x2, 0x2, 0x2, 0x536, 0xc5, 0x3, 0x2, 0x2, 0x2, 0x537, 0x535, 
    0x3, 0x2, 0x2, 0x2, 0x538, 0x53a, 0x5, 0x66, 0x34, 0x2, 0x539, 0x538, 
    0x3, 0x2, 0x2, 0x2, 0x539, 0x53a, 0x3, 0x2, 0x2, 0x2, 0x53a, 0x53d, 
    0x3, 0x2, 0x2, 0x2, 0x53b, 0x53e, 0x5, 0x50, 0x29, 0x2, 0x53c, 0x53e, 
    0x5, 0xc8, 0x65, 0x2, 0x53d, 0x53b, 0x3, 0x2, 0x2, 0x2, 0x53d, 0x53c, 
    0x3, 0x2, 0x2, 0x2, 0x53e, 0x543, 0x3, 0x2, 0x2, 0x2, 0x53f, 0x540, 
    0x7, 0x43, 0x2, 0x2, 0x540, 0x542, 0x7, 0x44, 0x2, 0x2, 0x541, 0x53f, 
    0x3, 0x2, 0x2, 0x2, 0x542, 0x545, 0x3, 0x2, 0x2, 0x2, 0x543, 0x541, 
    0x3, 0x2, 0x2, 0x2, 0x543, 0x544, 0x3, 0x2, 0x2, 0x2, 0x544, 0xc7, 0x3, 
    0x2, 0x2, 0x2, 0x545, 0x543, 0x3, 0x2, 0x2, 0x2, 0x546, 0x547, 0x9, 
    0xd, 0x2, 0x2, 0x547, 0xc9, 0x3, 0x2, 0x2, 0x2, 0x548, 0x549, 0x7, 0x4a, 
    0x2, 0x2, 0x549, 0x54e, 0x5, 0x52, 0x2a, 0x2, 0x54a, 0x54b, 0x7, 0x46, 
    0x2, 0x2, 0x54b, 0x54d, 0x5, 0x52, 0x2a, 0x2, 0x54c, 0x54a, 0x3, 0x2, 
    0x2, 0x2, 0x54d, 0x550, 0x3, 0x2, 0x2, 0x2, 0x54e, 0x54c, 0x3, 0x2, 
    0x2, 0x2, 0x54e, 0x54f, 0x3, 0x2, 0x2, 0x2, 0x54f, 0x551, 0x3, 0x2, 
    0x2, 0x2, 0x550, 0x54e, 0x3, 0x2, 0x2, 0x2, 0x551, 0x552, 0x7, 0x49, 
    0x2, 0x2, 0x552, 0xcb, 0x3, 0x2, 0x2, 0x2, 0x553, 0x55a, 0x5, 0xd0, 
    0x69, 0x2, 0x554, 0x555, 0x7, 0x47, 0x2, 0x2, 0x555, 0x557, 0x7, 0x72, 
    0x2, 0x2, 0x556, 0x558, 0x5, 0xd0, 0x69, 0x2, 0x557, 0x556, 0x3, 0x2, 
    0x2, 0x2, 0x557, 0x558, 0x3, 0x2, 0x2, 0x2, 0x558, 0x55a, 0x3, 0x2, 
    0x2, 0x2, 0x559, 0x553, 0x3, 0x2, 0x2, 0x2, 0x559, 0x554, 0x3, 0x2, 
    0x2, 0x2, 0x55a, 0xcd, 0x3, 0x2, 0x2, 0x2, 0x55b, 0x55c, 0x7, 0x2a, 
    0x2, 0x2, 0x55c, 0x560, 0x5, 0xcc, 0x67, 0x2, 0x55d, 0x55e, 0x7, 0x72, 
    0x2, 0x2, 0x55e, 0x560, 0x5, 0xd0, 0x69, 0x2, 0x55f, 0x55b, 0x3, 0x2, 
    0x2, 0x2, 0x55f, 0x55d, 0x3, 0x2, 0x2, 0x2, 0x560, 0xcf, 0x3, 0x2, 0x2, 
    0x2, 0x561, 0x563, 0x7, 0x3f, 0x2, 0x2, 0x562, 0x564, 0x5, 0xa2, 0x52, 
    0x2, 0x563, 0x562, 0x3, 0x2, 0x2, 0x2, 0x563, 0x564, 0x3, 0x2, 0x2, 
    0x2, 0x564, 0x565, 0x3, 0x2, 0x2, 0x2, 0x565, 0x566, 0x7, 0x40, 0x2, 
    0x2, 0x566, 0xd1, 0x3, 0x2, 0x2, 0x2, 0xad, 0xd3, 0xd8, 0xde, 0xe6, 
    0xef, 0xf4, 0xfb, 0x102, 0x105, 0x10c, 0x116, 0x11a, 0x11f, 0x123, 0x127, 
    0x131, 0x139, 0x13f, 0x146, 0x14d, 0x151, 0x154, 0x157, 0x160, 0x166, 
    0x16b, 0x16e, 0x174, 0x17a, 0x17e, 0x186, 0x18f, 0x196, 0x19c, 0x1a0, 
    0x1ab, 0x1b4, 0x1b9, 0x1bf, 0x1c3, 0x1cf, 0x1da, 0x1df, 0x1e8, 0x1f0, 
    0x1fa, 0x203, 0x20b, 0x210, 0x218, 0x21d, 0x227, 0x231, 0x237, 0x23e, 
    0x243, 0x24b, 0x24f, 0x251, 0x257, 0x25c, 0x260, 0x267, 0x269, 0x270, 
    0x275, 0x27e, 0x283, 0x286, 0x28b, 0x294, 0x2a0, 0x2a9, 0x2b4, 0x2b7, 
    0x2be, 0x2c8, 0x2d0, 0x2d3, 0x2d6, 0x2e3, 0x2eb, 0x2f0, 0x2f8, 0x2fc, 
    0x300, 0x304, 0x306, 0x30a, 0x310, 0x31b, 0x325, 0x32a, 0x333, 0x338, 
    0x33b, 0x342, 0x34b, 0x362, 0x365, 0x368, 0x370, 0x374, 0x37c, 0x382, 
    0x38d, 0x396, 0x39b, 0x3a5, 0x3ac, 0x3b9, 0x3c2, 0x3cb, 0x3d1, 0x3dc, 
    0x3e1, 0x3e6, 0x3eb, 0x3ef, 0x3f3, 0x3f7, 0x3f9, 0x3fd, 0x402, 0x413, 
    0x419, 0x41f, 0x425, 0x428, 0x43c, 0x440, 0x445, 0x449, 0x459, 0x481, 
    0x487, 0x496, 0x499, 0x49b, 0x4a5, 0x4ae, 0x4b2, 0x4b6, 0x4c8, 0x4ca, 
    0x4cf, 0x4d4, 0x4d9, 0x4e2, 0x4e4, 0x4e8, 0x4ed, 0x4f1, 0x4f5, 0x4f9, 
    0x503, 0x50f, 0x516, 0x519, 0x51d, 0x525, 0x52a, 0x535, 0x539, 0x53d, 
    0x543, 0x54e, 0x557, 0x559, 0x55f, 0x563, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

JavaParser::Initializer JavaParser::_init;
