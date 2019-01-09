#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([Vide], [0.1], [ian@geekprojects.com])
AM_INIT_AUTOMAKE([-Wall -Werror])
AC_CONFIG_SRCDIR([src/vide.h])
AC_CONFIG_HEADERS([src/config.h])

# Checks for programs.
AM_PROG_AR
AC_PROG_CXX
AC_PROG_CC
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

AC_SEARCH_LIBS([git_libgit2_init], [git2], [LIBGIT2="true" ], [ LIBGIT2="false"])
AM_CONDITIONAL([HAS_LIBGIT2], [test x$LIBGIT2 = xtrue])

PKG_CHECK_MODULES(libfrontier, libfrontier >= 1)
CPPFLAGS="$CPPFLAGS $libfrontier_CFLAGS"
LIBS="$LIBS $libfrontier_LIBS"

PKG_CHECK_MODULES(yamlcpp, yaml-cpp >= 0.6)
LIBS="$LIBS $yamlcpp_LIBS"
CPPFLAGS="$CPPFLAGS $yamlcpp_CFLAGS"

CPPFLAGS="-g $CPPFLAGS -Wall -Werror"

#CPPFLAGS="-O0 -g $CPPFLAGS -Wall -Werror -O0  -fsanitize=address -fno-omit-frame-pointer -fsanitize-address-use-after-scope "
#LDFLAGS="$LDFLAGS -fsanitize=address "

case $host_os in
    darwin*)
        LDFLAGS+=-all_load
        ;;
esac

AC_CONFIG_FILES([
    Makefile
    src/Makefile
    src/editor/Makefile
    src/project/Makefile
    src/filetypes/Makefile
    src/filetypes/cxx/Makefile
    src/buildtools/Makefile
    src/ui/Makefile
    src/ui/views/Makefile
    src/interfaces/Makefile
    src/interfaces/vi/Makefile
    src/plugins/Makefile
])
AC_OUTPUT
