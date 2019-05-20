
SUBDIRS=views

bin_PROGRAMS=vide

vide_SOURCES=main.cpp videapp.cpp welcomewindow.cpp editortipwindow.cpp videwindow.cpp projectwindow.cpp settingswindow.cpp

vide_CPPFLAGS=-I${top_srcdir}/include
vide_LDADD=../libvide-core/libvide-core.la ../plugins/libvide-plugins.la views/libviews.la

