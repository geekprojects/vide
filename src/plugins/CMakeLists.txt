
add_library(vide-plugins SHARED 
    filetypes/cxx/cxxfiletypemanager.cpp
    filetypes/cxx/cxxtokeniser.cpp
    filetypes/java/JavaLexer.cpp
    filetypes/java/JavaParser.cpp
    filetypes/java/JavaParserBaseListener.cpp
    filetypes/java/JavaParserListener.cpp
    filetypes/java/javafiletypemanager.cpp
    filetypes/java/javatokeniser.cpp
    git/gitplugin.cpp
)

add_definitions(-Wno-error=attributes)

include_directories(${clang_INCLUDE} ${ANTLR4_INCLUDE})
target_link_libraries(vide-plugins vide-core ${clang_LIBRARY} ${ANTLR4_LIBRARY} ${git2_LIBRARY})

