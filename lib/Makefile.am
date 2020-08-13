AUTOMAKE_OPTIONS = subdir-objects 

ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

lib_LTLIBRARIES = libsqd3.la
libsqd3_la_SOURCES = ../src/lexer.c \
               		   ../src/parser.c \
               		   ../src/sqd3_types.c \
               		   ../src/tree.c \
               		   ../src/vtable.c \
               		   ../src/builtin_functions.c \
               		   ../src/debug.c

libsqd3_la_LDFLAGS = -module -avoid-version -export-dynamic
