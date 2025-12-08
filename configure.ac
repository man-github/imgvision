AC_PREREQ([2.69])
AC_INIT([imgvision], [1.0], [support@example.com])

AC_CONFIG_MACRO_DIRS([m4])

AM_INIT_AUTOMAKE([-Wall foreign subdir-objects])
AC_CONFIG_SRCDIR([src/img_lib.cpp])
AC_CONFIG_HEADERS([config.h])

AC_PROG_CC
AC_PROG_CXX
AM_PROG_AR
LT_INIT

# ------------------------------------------------------------
# pkg-config
# ------------------------------------------------------------
PKG_PROG_PKG_CONFIG

# ------------------------------------------------------------
# Tesseract OCR dependency
# ------------------------------------------------------------
PKG_CHECK_MODULES([TESSERACT], [tesseract], [],
  [AC_MSG_ERROR([Tesseract library not found])])
CPPFLAGS="$CPPFLAGS $TESSERACT_CFLAGS"
LDFLAGS="$LDFLAGS $TESSERACT_LIBS"

# ------------------------------------------------------------
# OpenCV dependency
# ------------------------------------------------------------
PKG_CHECK_MODULES([OPENCV], [opencv4], [],
  [AC_MSG_ERROR([OpenCV4 not found])])
CPPFLAGS="$CPPFLAGS $OPENCV_CFLAGS"
LDFLAGS="$LDFLAGS $OPENCV_LIBS"

# ------------------------------------------------------------
# Darknet: Custom include/library paths
# ------------------------------------------------------------

AC_ARG_WITH([darknet-includes],
    AS_HELP_STRING([--with-darknet-includes=DIR],
                   [Path to darknet include directory]),
    [DNET_INC=$withval],
    [DNET_INC=""])

AC_ARG_WITH([darknet-libs],
    AS_HELP_STRING([--with-darknet-libs=DIR],
                   [Path to darknet library directory]),
    [DNET_LIB=$withval],
    [DNET_LIB=""])

if test "x$DNET_INC" = "x"; then
    AC_MSG_ERROR([Missing --with-darknet-includes=DIR])
fi

if test ! -f "$DNET_INC/yolo_v2_class.hpp"; then
    AC_MSG_ERROR([yolo_v2_class.hpp not found in $DNET_INC])
fi

if test "x$DNET_LIB" = "x"; then
    AC_MSG_ERROR([Missing --with-darknet-libs=DIR])
fi

if test ! -f "$DNET_LIB/libdarknet.so"; then
    AC_MSG_ERROR([libdarknet.so not found in $DNET_LIB])
fi

AC_MSG_RESULT([Using Darknet includes: $DNET_INC])
AC_MSG_RESULT([Using Darknet libs: $DNET_LIB])

CPPFLAGS="$CPPFLAGS -I$DNET_INC"
LDFLAGS="$LDFLAGS -L$DNET_LIB -ldarknet"

AC_SUBST(DNET_INC)
AC_SUBST(DNET_LIB)

# ------------------------------------------------------------
# Output files
# ------------------------------------------------------------
AC_CONFIG_FILES([
    Makefile
    include/Makefile
    src/Makefile
    examples/Makefile
    imgvision.pc
])

AC_OUTPUT
