# Avoid config.h leaking into 3rd-party headers
AM_CPPFLAGS = -U HAVE_CONFIG_H

# Build libimgvision as a libtool shared library
lib_LTLIBRARIES = libimgvision.la

libimgvision_la_SOURCES = \
    api_context.cpp \
    backend_ocr.cpp \
    backend_yolo.cpp \
    img_lib.cpp \
    internal.h

# Build shared object with versioning
libimgvision_la_LDFLAGS = -version-info 1:0:0 -no-undefined

# External library dependencies
libimgvision_la_LIBADD = \
    $(TESSERACT_LIBS) \
    $(OPENCV_LIBS) \
    -ldarknet
