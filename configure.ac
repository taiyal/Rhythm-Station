# Initialization
AC_INIT([Rhythm-Station], [git], [shakeshoda+rstation@gmail.com], [], [http://github.com/shakesoda/Rhythm-Station])
AM_INIT_AUTOMAKE([foreign no-define -Wall])
AM_SILENT_RULES([yes])

# Tools to use
AC_PROG_CXX
AC_PROG_CC

# Config files to generate
AC_CONFIG_FILES([
	Makefile
])

PKG_CHECK_MODULES([DEPENDENCIES],[gl glew libglfw libpng14 openal freealut vorbisfile lua],[],[
	AC_MSG_ERROR([All dependencies were not fulfilled: $DEPENDENCIES_PKG_ERRORS])
])

AC_CHECK_HEADER([zlib.h],[],[
	AC_MSG_ERROR([All dependencies were not fulfilled: zlib was not found.])	
])

AC_OUTPUT
