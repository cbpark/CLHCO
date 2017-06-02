AM_CXXFLAGS = -std=c++11

if DEBUG
AM_CXXFLAGS += -DDEBUG -O0 -Wall -Wextra -pedantic
endif

if USE_ROOT
AM_CXXFLAGS += $(ROOTCFLAGS)
endif

lib_LTLIBRARIES      = libCLHCO.la
libCLHCO_la_SOURCES  = event.cc kinematics.cc lhco.cc object.cc parser.cc \
	particle.cc
if USE_ROOT
libCLHCO_la_LIBADD   = -L$(ROOTLIBDIR) $(ROOTLIBS)
endif

pkginclude_HEADERS = event.h kinematics.h lhco.h object.h parser.h particle.h

if DEBUG
noinst_bindir = $(top_builddir)
noinst_bin_PROGRAMS = test_parse test_render

test_parse_SOURCES = test_parse.cc
test_parse_LDADD   = libCLHCO.la

test_render_SOURCES = test_render.cc
test_render_LDADD   = libCLHCO.la

if USE_ROOT
test_parse_LDADD += -L$(ROOTLIBDIR) $(ROOTLIBS)
test_render_LDADD += -L$(ROOTLIBDIR) $(ROOTLIBS)
endif
endif
