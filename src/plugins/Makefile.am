
noinst_LTLIBRARIES=libplugins.la

libplugins_la_SOURCES=plugins.cpp
libplugins_la_CPPFLAGS=-I{top_srcdir}/src

if HAS_LIBGIT2
libplugins_la_SOURCES+=gitplugin.cpp
endif

