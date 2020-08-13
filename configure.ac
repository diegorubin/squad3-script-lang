# Quem quiser pode adicionar o email aqui, neste array
# Isso pode ser usado para compor o help do binario
AC_INIT([sqd3],[0.0.1],[rubin.diego@gmail.com])

# Diretorio do projeto
AC_CONFIG_SRCDIR([src])

# Usando automake para gerar os makefiles
AM_INIT_AUTOMAKE

# Iremos utilizar o gcc
AC_PROG_CC

# Diretiva para criar o comando make install
AC_PROG_INSTALL

# Configuracao para habilitar geracao do so
AC_CONFIG_MACRO_DIR([m4])
AM_PROG_LIBTOOL

# Se for utilizado alguma dependencia, ela pode ser adicionada aqui.
# Essa verificacao acontece durante a execucao do comando ./configure
# Para realizar essa checagem, o comando pkg-config e utilizado.
# PKG_CHECK_MODULES([sqd3],[])

AC_CONFIG_FILES([
    Makefile
    src/Makefile
    lib/Makefile
    tests/Makefile
])

# Configuracao para habilitar geracao do so

AC_ENABLE_SHARED
AC_DISABLE_STATIC
LT_INIT

AC_OUTPUT()
