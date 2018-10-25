
SUBDIRS=ui vi

if HAS_LIBCLANG
SUBDIRS+=cxx
endif

bin_PROGRAMS=vide

vide_SOURCES=buffer.cpp filetypemanager.cpp main.cpp tokeniser.cpp vide.cpp editor.cpp interface.cpp project.cpp utils.cpp

vide_LDADD=ui/libui.la vi/libvi.la
if HAS_LIBCLANG
vide_LDADD+=cxx/libcxx.la
endif

