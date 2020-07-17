
add_library(vide-core SHARED 
    utils.cpp
    vide.cpp
    re.cpp
    plugins.cpp
    buildtools/makefile.cpp
    buildtools/buildtool.cpp
    buildtools/gnu.cpp
    project/module.cpp
    project/project.cpp
    project/entry.cpp
    project/file.cpp
    project/index.cpp
    filetypes/filetypemanager.cpp
    filetypes/tokeniser.cpp
    editor/buffer.cpp
    editor/editor.cpp
    interfaces/vi/visual.cpp
    interfaces/vi/commands.cpp
    interfaces/vi/excommands.cpp
    interfaces/vi/search.cpp
    interfaces/vi/vi.cpp
    interfaces/interface.cpp
)

add_definitions(-DDATADIR=${DATADIR})

target_link_libraries(vide-core ${yamlcpp_LDFLAGS} ${pcre_LDFLAGS} ${FSW_LIBRARY} ${frontier_LDFLAGS})

