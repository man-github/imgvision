# Include imgvision headers
AM_CPPFLAGS = -I$(top_srcdir)/include

bin_PROGRAMS = example
example_SOURCES = example.cpp

# Link using libtool
example_LDADD = \
    $(top_builddir)/src/libimgvision.la \
    $(TESSERACT_LIBS) \
    $(OPENCV_LIBS) \
    -ldarknet

# Allow shared linking
example_LDFLAGS = -no-undefined
