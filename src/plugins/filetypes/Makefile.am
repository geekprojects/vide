
SUBDIRS=

if HAS_LIBANTLR4
SUBDIRS+=java
endif

if HAS_LIBCLANG
SUBDIRS+=cxx
endif

noinst_LTLIBRARIES=libfiletypes.la

libfiletypes_la_SOURCES=
libfiletypes_la_LIBADD=

if HAS_LIBANTLR4
libfiletypes_la_LIBADD+=java/libjava.la
endif
if HAS_LIBCLANG
libfiletypes_la_LIBADD+=cxx/libcxx.la
endif

