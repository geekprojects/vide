#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([Vide], [0.1], [ian@geekprojects.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])
AC_CONFIG_SRCDIR([include/vide/vide.h])
AC_CONFIG_HEADERS([include/vide/config.h])

# Checks for programs.
AM_PROG_AR
AC_PROG_CXX
AC_PROG_CC
AC_LANG([C++])
AC_PROG_MAKE_SET
AC_PROG_LIBTOOL
AC_PROG_RANLIB
PKG_PROG_PKG_CONFIG

AC_CANONICAL_HOST

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([wchar.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT8_T

AC_CONFIG_MACRO_DIR([m4])

# Checks for library functions.
AC_CHECK_FUNCS([iswprint memset])

AC_SEARCH_LIBS([fsw_init_library], [fswatch])

AC_ARG_WITH([clang], [Build with Clang from specified directory], [LLVM_PREFIX=$withval])

OLDLIBS="$LIBS"
if test "x$LLVM_PREFIX" != "x"; then
    LIBS="$LIBS -L$LLVM_PREFIX/lib"
fi

AC_SEARCH_LIBS([clang_createIndex], [clang], [LIBCLANG="true" ], [ LIBCLANG="false"])
AM_CONDITIONAL([HAS_LIBCLANG], [test x$LIBCLANG = xtrue])
LIBS="$OLDLIBS"

if test x$LIBCLANG = xtrue; then
    if test "x$LLVM_PREFIX" != "x"; then
        LIBS="$LIBS -L$LLVM_PREFIX/lib"
        CPPFLAGS="$CPPFLAGS -I$LLVM_PREFIX/include"
    fi
    AC_DEFINE(HAS_LIBCLANG, 1, [libclang])
    LIBS="$LIBS -lclang"
fi

AX_CXX_CHECK_LIB(antlr4-runtime, [antlr4::RuntimeMetaData::getRuntimeVersion()], [
    HAS_LIBANTLR4=yes
    AC_DEFINE(HAS_LIBANTLR4, 1, [libantlr4-runtime])
    LIBS="$LIBS -lantlr4-runtime"
])
AM_CONDITIONAL([HAS_LIBANTLR4], [test "x$HAS_LIBANTLR4" = "xyes"])

AC_SEARCH_LIBS([git_libgit2_init], [git2], [LIBGIT2="true" ], [ LIBGIT2="false"])
AM_CONDITIONAL([HAS_LIBGIT2], [test x$LIBGIT2 = xtrue])

PKG_CHECK_MODULES(libfrontier, libfrontier >= 1)
CPPFLAGS="$CPPFLAGS $libfrontier_CFLAGS"
LIBS="$LIBS $libfrontier_LIBS"

PKG_CHECK_MODULES(yamlcpp, yaml-cpp >= 0.6)
LIBS="$LIBS $yamlcpp_LIBS"
CPPFLAGS="$CPPFLAGS $yamlcpp_CFLAGS"

PKG_CHECK_MODULES(libpcre32, libpcre32 >= 8.0)
LIBS="$LIBS $libpcre32_LIBS"
CPPFLAGS="$CPPFLAGS $libpcr32_CFLAGS"

CPPFLAGS="-g $CPPFLAGS -Wall -Werror -std=c++14"

CPPFLAGS="-O0 -g $CPPFLAGS -Wall -Werror -O0  -fsanitize=address -fno-omit-frame-pointer -fsanitize-address-use-after-scope "
LDFLAGS="$LDFLAGS -fsanitize=address "

case $host_os in
    darwin*)
        LDFLAGS+=-all_load
        ;;
esac

AC_CONFIG_FILES([
    Makefile
    include/Makefile
    include/vide/Makefile
    src/Makefile
    src/libvide-core/Makefile
    src/libvide-core/editor/Makefile
    src/libvide-core/project/Makefile
    src/libvide-core/buildtools/Makefile
    src/libvide-core/filetypes/Makefile
    src/libvide-core/interfaces/Makefile
    src/libvide-core/interfaces/vi/Makefile
    src/plugins/Makefile
    src/plugins/filetypes/Makefile
    src/plugins/filetypes/cxx/Makefile
    src/plugins/filetypes/java/Makefile
    src/plugins/git/Makefile
    src/vide/Makefile
    src/vide/views/Makefile
    src/turbovide/Makefile
    src/videtool/Makefile
    tests/Makefile
])
AC_OUTPUT
