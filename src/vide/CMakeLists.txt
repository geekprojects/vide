
add_executable(vide
    videapp.cpp
    editortipwindow.cpp
    settingswindow.cpp
    welcomewindow.cpp
    videwindow.cpp
    main.cpp
    projectwindow.cpp
    views/projectview.cpp
    views/tasksview.cpp
    views/editorview.cpp
    views/structureview.cpp
)

include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/src/vide)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_definitions(-Wno-class-memaccess)
    target_link_options(vide PUBLIC "LINKER:--no-as-needed")
endif()

target_link_libraries(vide PUBLIC vide-core vide-plugins ${libfrontier_LDFLAGS})

