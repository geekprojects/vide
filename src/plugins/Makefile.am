
SUBDIRS=filetypes
if HAS_LIBGIT2
SUBDIRS+=git
endif

lib_LTLIBRARIES=libvide-plugins.la

libvide_plugins_la_SOURCES=
libvide_plugins_la_CPPFLAGS=-I${top_srcdir}/src
libvide_plugins_la_LIBADD=filetypes/libfiletypes.la

if HAS_LIBGIT2
libvide_plugins_la_LIBADD+=git/libgitplugin.la
endif

