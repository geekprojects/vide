
SUBDIRS=

check_LTLIBRARIES = libgtest.la
libgtest_la_SOURCES = googletest/googletest/src/gtest-all.cc googletest/googlemock/src/gmock-all.cc
libgtest_la_CPPFLAGS = -I$(top_srcdir)/tests/googletest/googletest/include -I$(top_srcdir)/tests/googletest/googletest -I$(top_srcdir)/tests/googletest/googlemock -I$(top_srcdir)/tests/googletest/googlemock/include
libgtest_la_LDFLAGS = -pthread

noinst_PROGRAMS=vide_test

vide_test_SOURCES=main.cpp testBuffer.cpp testEditor.cpp
vide_test_LDADD=../src/libvide-core/libvide-core.la libgtest.la
#vide_test_LDFLAGS=-framework Cocoa -framework AppKit -fsanitize=address
vide_test_LDFLAGS=-framework Cocoa -framework AppKit
vide_test_CPPFLAGS=-I${top_srcdir}/include -I$(top_srcdir)/tests//googletest/googletest/include

test: all
	cd ..; tests/vide_test

