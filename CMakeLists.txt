cmake_minimum_required(VERSION 3.10)

include(CheckSymbolExists)
include(CheckIncludeFile)

project(vide VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

SET(FLAGS_COMMON "-Wall -Werror")
SET(CMAKE_C_FLAGS "${FLAGS_COMMON}")
SET(CMAKE_CXX_FLAGS "${FLAGS_COMMON}")
SET(CMAKE_C_FLAGS_DEBUG "${FLAGS_COMMON} -O0 -g  -fsanitize=address -fsanitize-address-use-after-scope -fno-omit-frame-pointer")
SET(CMAKE_CXX_FLAGS_DEBUG "${FLAGS_COMMON} -O0 -g -fsanitize=address -fsanitize-address-use-after-scope -fno-omit-frame-pointer")
SET(CMAKE_C_FLAGS_RELEASE "${FLAGS_COMMON} -O3")
SET(CMAKE_CXX_FLAGS_RELEASE "${FLAGS_COMMON} -O3")



find_package(PkgConfig REQUIRED)
find_package(Doxygen COMPONENTS dot)

# Common requirements
#pkg_check_modules(libgeek REQUIRED libgeek)
pkg_check_modules(frontier REQUIRED libfrontier)
pkg_check_modules(yamlcpp REQUIRED yaml-cpp)
pkg_check_modules(pcre REQUIRED libpcre32)

find_library(FSW_LIBRARY NAMES fswatch )
find_library(git2_LIBRARY NAMES git2 )


# Clang
find_path(clang_INCLUDE clang-c/Index.h HINTS ${CLANG}/include)
find_library(clang_LIBRARY NAMES clang HINTS ${CLANG}/lib)
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(clang DEFAULT_MSG clang_LIBRARY clang_INCLUDE)
mark_as_advanced(clang_INCLUDE clang_LIBRARY)

find_library(ANTLR4_LIBRARY NAMES antlr4-runtime )
find_path(antlr4_INCLUDE_BASE NAMES antlr4-runtime/antlr4-runtime.h)
if(antlr4_INCLUDE_BASE)
    set(ANTLR4_INCLUDE ${antlr4_INCLUDE_BASE}/antlr4-runtime)
endif()

add_definitions(${frontier_CFLAGS} ${yamlcpp_CFLAGS} ${pcre_CFLAGS})

include_directories(${CMAKE_SOURCE_DIR}/include)

add_subdirectory(src/libvide-core)
add_subdirectory(src/plugins)
add_subdirectory(src/vide)
add_subdirectory(tests)

set(DATADIR ${CMAKE_INSTALL_PREFIX}/share/vide)
install(DIRECTORY data/ DESTINATION ${DATADIR})


