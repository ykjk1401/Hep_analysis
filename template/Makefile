#####################################
# Makefile (for Linux x86_64)       #
#  for bellelib>b20070307_1108      #
#  by S.Nishida	 (update: 07/03/27) #
#####################################

# Generated automatically from Makefile.in by configure.
#+
# File: Makefile.in
# Description : Makefile Template for fsim_analysis
#-

#---------------------------------------------------------------
# 1. User Specifications
#      MODULE1   : module name (shared object file)
#      OBJS1     : additonal obj files
#      DEPFILES1 : additonal files on which $(MODULE1) depends
#      LIBS1     : libraries in addition to $(LIBS)
#---------------------------------------------------------------
MODULE1 = userana.so
OBJS1 =
DEPFILES1 =
LIBS1 = $(LIBS)

MODULE2 =
OBJS2 =
DEPFILES2 =
LIBS2 = $(LIBS)

MODULE3 =
OBJS3 =
DEPFILES3 =
LIBS3 = $(LIBS)

MODULE4 =
OBJS4 =
DEPFILES4 =
LIBS4 = $(LIBS)

MODULE5 =
OBJS5 =
DEPFILES5 =
LIBS5 = $(LIBS)

LIBS = -L$(MY_RUN_DIR)/lib/so -L$(MY_RUN_DIR)/lib -L$(BELLE_RUN_DIR)/lib/so \
	-ltuple -lip

#---------------------------------------------------------------
# 2. System Specifications
#    --- Do not change without knowledge
#---------------------------------------------------------------

# Compiler Setup with machine dependence

FC =
CC = gcc
CXX = c++

DEFS = -DHAVE_LIBCURSES=1 -DHAVE_LIBREADLINE=1 -DHAVE_POSTGRES=1 -DHAVE_LIBCURSES=1 -DHAVE_LIBTERMCAP=1 -DHAVE_LIBHISTORY=1 -DHAVE_LIBREADLINE=1 -DHAVE_HISTORY=1 -DHAVE_LIBBSD=1 -DHAVE_LIBM=1 -DHAVE_LIBDL=1 -DHAVE_LIBNSL=1 -DHAVE_LIBCRYPT=1 -DHAVE_LIBNSL=1 -DHAVE_LIBDL=1 -DHAVE_LIBCRYPT=1  -DCERNLIB_TYPE
CPPFLAGS =
DEPCPPFLAGS = -MM

FFLAGS = -O -g -DBELLE_TARGET_H=\"belle-x86_64-unknown-linux-gnu-g++.h\"
CFLAGS = -O -g -DBELLE_TARGET_H=\"belle-x86_64-unknown-linux-gnu-g++.h\"
CXXFLAGS = -g -DHEP_SHORT_NAMES -DBELLE_SHORT_NAMES -DDSTXX_NOINLINE -DBELLE_TARGET_H=\"belle-x86_64-unknown-linux-gnu-g++.h\" -fPIC
SOFLAGS = -shared -Wl,-export-dynamic
LDFLAGS =

SYSLIB = -lcrypt

CLHEPLIB = -lbelleCLHEP

# Include directories

INCLUDES_C = $(MY_TOP_DIR)/include $(BELLE_TOP_DIR)/include
INCLUDES_FORTRAN = $(BELLE_TOP_DIR)/inc

# Dependence description

include $(BELLE_RUN_DIR)/src/config/Makefile.panther

COMPILE_FCPP := $(FC) -c $(PANTHER_FMACROS) $(INCLUDES_FORTRAN:%=-I%) $(CPPFLAGS) $(FFLAGS)
COMPILE_FC := $(FC) -c $(INCLUDES_FORTRAN:%=-I%) $(FFLAGS)
COMPILE_CC := $(CC) -c $(PANTHER_CMACROS) $(INCLUDES_C:%=-I%) $(CPPFLAGS) $(CFLAGS)
COMPILE_CXX := $(CXX) -c $(PANTHER_CMACROS) $(INCLUDES_C:%=-I%) $(CPPFLAGS) $(CXXFLAGS)

LINK_FCPP := $(FC)
LINK_FC := $(FC)
LINK_CC := $(CC)
LINK_CXX := $(CXX)

DEPEND_FCPP :=  -M $(DEFS) $(PANTHER_FMACROS) $(INCLUDES_FORTRAN:%=-I%) $(CPPFLAGS) $(FFLAGS)
DEPEND_CC := $(CC) $(DEPCPPFLAGS) $(DEFS) $(PANTHER_CMACROS) $(INCLUDES_C:%=-I%) $(CPPFLAGS) $(CFLAGS)
DEPEND_CXX := $(CXX) $(DEPCPPFLAGS) $(DEFS) $(PANTHER_CMACROS) $(INCLUDES_C:%=-I%) $(CPPFLAGS) $(CXXFLAGS)

LINUX_G77_BUG = @LINUX_G77_BUG@

%.o:%.c
	$(COMPILE_CC) $<

%.d:%.c
	$(SHELL) -ec '$(DEPEND_CC) $< | sed -e "s/$*.o[ :]*/$@ &/g" -e 's/\.[12][0-9][0-9][0-9][0-9][0-9][0-9][0-9][a-z]\.h/.tdf/g' > $@'

%.o:%.cc
	$(COMPILE_CXX) $<

%.d:%.cc
	$(SHELL) -ec '$(DEPEND_CXX) $< | sed -e "s/$*.o[ :]*/$@ &/g" -e 's/\.[12][0-9][0-9][0-9][0-9][0-9][0-9][0-9][a-z]\.h/.tdf/g'> $@'


%.o:%.F
	$(COMPILE_FCPP) $<

%.d:%.F
	$(SHELL) -ec '$(DEPEND_FCPP) $< | sed $(LINUX_G77_BUG) -e "s/$*.o[ :]*/$@ &/g" -e 's/\.[12][0-9][0-9][0-9][0-9][0-9][0-9][0-9][a-z]\.inc/.tdf/g'> $@'


# CERNLIB
ifeq "$(CERN)/$(CERN_LEVEL)" "/"
  CERNLIB_LIB_DIR = /belle/cern/2001/lib
else
  CERNLIB_LIB_DIR = $(CERN)/$(CERN_LEVEL)/lib
endif

# Dependencies
all::	$(MODULE1) $(MODULE2) $(MODULE3) $(MODULE4) $(MODULE5)

1::	$(MODULE1)
2::	$(MODULE2)
3::	$(MODULE3)
4::	$(MODULE4)
5::	$(MODULE5)

# $(MODULE1:%.so=%.o) $(OBJS1): $(MODULE1:%.so=%.cc) $(DEPFILES1)
# $(MODULE2:%.so=%.o) $(OBJS2): $(MODULE2:%.so=%.cc) $(DEPFILES2)
# $(MODULE3:%.so=%.o) $(OBJS3): $(MODULE3:%.so=%.cc) $(DEPFILES3)
# $(MODULE4:%.so=%.o) $(OBJS4): $(MODULE4:%.so=%.cc) $(DEPFILES4)
# $(MODULE5:%.so=%.o) $(OBJS5): $(MODULE5:%.so=%.cc) $(DEPFILES5)
$(MODULE1:%.so=%.o) $(OBJS1): $(DEPFILES1)
$(MODULE2:%.so=%.o) $(OBJS2): $(DEPFILES2)
$(MODULE3:%.so=%.o) $(OBJS3): $(DEPFILES3)
$(MODULE4:%.so=%.o) $(OBJS4): $(DEPFILES4)
$(MODULE5:%.so=%.o) $(OBJS5): $(DEPFILES5)

$(MODULE1): $(MODULE1:%.so=%.o) $(OBJS1) $(DEPFILES1)
	$(LINK_CXX) -o $(MODULE1) $(SOFLAGS) $(MODULE1:%.so=%.o) \
	$(OBJS1) $(LIBS1) $(CLHEPLIB) $(CERNLIB) $(SYSLIB)

$(MODULE2): $(MODULE2:%.so=%.o) $(OBJS2) $(DEPFILES2)
	$(LINK_CXX) -o $(MODULE2) $(SOFLAGS) $(MODULE2:%.so=%.o) \
	$(OBJS2) $(LIBS2) $(CLHEPLIB) $(CERNLIB) $(SYSLIB)

$(MODULE3): $(MODULE3:%.so=%.o) $(OBJS3) $(DEPFILES3)
	$(LINK_CXX) -o $(MODULE3) $(SOFLAGS) $(MODULE3:%.so=%.o) \
	$(OBJS3) $(LIBS3) $(CLHEPLIB) $(CERNLIB) $(SYSLIB)

$(MODULE4): $(MODULE4:%.so=%.o) $(OBJS4) $(DEPFILES4)
	$(LINK_CXX) -o $(MODULE4) $(SOFLAGS) $(MODULE4:%.so=%.o) \
	$(OBJS4) $(LIBS4) $(CLHEPLIB) $(CERNLIB) $(SYSLIB)

$(MODULE5): $(MODULE5:%.so=%.o) $(OBJS5) $(DEPFILES5)
	$(LINK_CXX) -o $(MODULE5) $(SOFLAGS) $(MODULE5:%.so=%.o) \
	$(OBJS5) $(LIBS5) $(CLHEPLIB) $(CERNLIB) $(SYSLIB)

clean::
	rm -f $(MODULE1) $(MODULE1:%.so=%.o) $(OBJS1) \
		$(MODULE2) $(MODULE2:%.so=%.o) $(OBJS2) \
		$(MODULE3) $(MODULE3:%.so=%.o) $(OBJS3) \
		$(MODULE4) $(MODULE4:%.so=%.o) $(OBJS4) \
		$(MODULE5) $(MODULE5:%.so=%.o) $(OBJS5) \
		*~ fort.* fpda_pid.* test.hbk core core.* temp.*
