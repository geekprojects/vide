SUBDIRS=editor project buildtools filetypes interfaces

lib_LTLIBRARIES=libvide-core.la

libvide_core_la_SOURCES=vide.cpp plugins.cpp re.cpp utils.cpp
libvide_core_la_LIBADD=editor/libeditor.la project/libproject.la
libvide_core_la_CPPFLAGS=-I${top_srcdir}/include

