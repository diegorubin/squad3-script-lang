# Temporariamente removido por causa do ubuntu:
# https://www.mail-archive.com/debian-bugs-dist@lists.debian.org/msg1232579.html
# https://stackoverflow.com/questions/18839857/deps-po-no-such-file-or-directory-compiler-error
# AUTOMAKE_OPTIONS = subdir-objects 

# Configuracao do binario de tests
# Este binario ira agrupar todos os testes unitarios
TESTS = lexer parser tree sqd3_types vtable
check_PROGRAMS = lexer parser tree sqd3_types vtable

lexer_SOURCES = lexer.c

parser_SOURCES = parser.c

sqd3_types_SOURCES = sqd3_types.c

tree_SOURCES = tree.c

vtable_SOURCES = vtable.c

ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

lexer_CFLAGS = -I/usr/include \
               -I$(includedir)

lexer_LDADD = ${LEXER_LIBS} \
              ../src/lexer.o \
              -lcheck -lsubunit -lm -lrt -lpthread

parser_CFLAGS = -I/usr/include \
                -I$(includedir)

parser_LDADD = ${PARSER_LIBS} \
               ../src/lexer.o \
               ../src/parser.o \
               ../src/sqd3_types.o \
               ../src/tree.o \
               ../src/vtable.o \
               -lcheck -lsubunit -lm -lrt -lpthread

sqd3_types_CFLAGS = -I/usr/include \
                    -I$(includedir)

sqd3_types_LDADD = ${SQD3_TYPES_LIBS} \
                   ../src/sqd3_types.o \
                   ../src/vtable.o \
                   -lcheck -lsubunit -lm -lrt -lpthread

tree_CFLAGS = -I/usr/include \
               -I$(includedir)

tree_LDADD = ${TREE_LIBS} \
              ../src/tree.o \
              ../src/sqd3_types.o \
              ../src/vtable.o \
              -lcheck -lsubunit -lm -lrt -lpthread

vtable_CFLAGS = -I/usr/include \
                -I$(includedir)

vtable_LDADD = ${VTABLE_LIBS} \
               ../src/vtable.o \
               ../src/sqd3_types.o \
               -lcheck -lsubunit -lm -lrt -lpthread
