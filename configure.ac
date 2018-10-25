#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([FULL-PACKAGE-NAME], [VERSION], [BUG-REPORT-ADDRESS])
AM_INIT_AUTOMAKE([-Wall -Werror])
AC_CONFIG_SRCDIR([src/editor.h])
AC_CONFIG_HEADERS([src/config.h])

# Checks for programs.
AM_PROG_AR
AC_PROG_CXX
AC_PROG_CC
AC_PROG_MAKE_SET
AC_PROG_LIBTOOL
AC_PROG_RANLIB
PKG_PROG_PKG_CONFIG

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

PKG_CHECK_MODULES(libfrontier, libfrontier >= 1)
CPPFLAGS="$CPPFLAGS $libfrontier_CFLAGS"
LIBS="$LIBS $libfrontier_LIBS"

CPPFLAGS="$CPPFLAGS"
CPPFLAGS="-O0 -g $CPPFLAGS -Wall -Werror -O0"

AC_CONFIG_FILES([
    Makefile
    src/Makefile
    src/cxx/Makefile
    src/ui/Makefile
    src/ui/views/Makefile
    src/vi/Makefile
])
AC_OUTPUT
