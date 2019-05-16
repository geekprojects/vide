
SUBDIRS=
if HAS_LIBCLANG
SUBDIRS+=cxx
endif

noinst_LTLIBRARIES=libfiletypes.la

libfiletypes_la_SOURCES=
if HAS_LIBCLANG
libfiletypes_la_LIBADD=cxx/libcxx.la
endif

