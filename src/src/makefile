# target
LIBNAME = libsrppac

# subdirectories
VPATH = 

# object to be compiled should be listed without directory
# main
OBJ =
OBJ+= TSRPPACPlaneData.o
OBJ+= TSRPPACParameter.o
OBJ+= TSRPPACPlaneProcessor.o
OBJ+= TSRPPACPlaneDqdxProcessor.o
OBJ+= TSRPPACPlaneSideDqdxProcessor.o
OBJ+= TSRPPACCalibrationProcessor.o
OBJ+= TSRPPACPlaneCalibrationTask.o
#OBJ+= TGSRPPACConfig.o
OBJ+= TGSRPPACCalibration.o

# check architecture
#include $(ROOTSYS)/etc/root/Makefile.arch

UNAME = $(shell uname)
ifeq ($(UNAME),Darwin)
SOEXT = dylib
#SOEXT = so
SOFLAG = -Wl,-undefined -Wl,dynamic_lookup -dynamiclib -install_name @rpath/$(LIBNAME).$(SOEXT)
#SOFLAG = -dynamiclib
#SOFLAG = -Wl,-undefined -Wl,dynamic_lookup -install_name \
#	$(WORKDIR)/processors/$(LIBNAME).dylib -dynamiclib
else
SOFLAG = -shared -Wl,-soname,$(LIBNAME).so
SOEXT = so
endif

TARGET = $(LIBNAME).$(SOEXT)

# local include directories
INCLUDE = -I/opt/local/artemis_share/include

# depends
DEPDIR = .deps
DEPENDS = $(addprefix $(DEPDIR)/, $(notdir $(OBJ:.o=.d)))
# object
OBJDIR = .objects
OBJECTS = $(addprefix $(OBJDIR)/, $(OBJ))

HDR = $(OBJ:.o=.h)

DICTSRC = $(LIBNAME)_dict.cc
DICTOBJ = $(DICTSRC:.cc=.o)
DICTHDR = $(DICTSRC:.cc=.h)

CXX = $(shell artemis-config --cxx)

WARNING = -Wall -Wextra

CXXFLAGS = -O2 $(WARNING) -I. $(INCLUDE) `artemis-config --cflags`  -fPIC `root-config --cflags` -g
LDFLAGS = -L$(HOME)/local/lib `artemis-config --libs` `root-config --libs` -lTreePlayer -L/opt/local/artemis_share/lib -luser


all: $(TARGET)
.PHONY: all clean

$(TARGET): $(OBJECTS) $(DICTOBJ)
	@echo `uname`
	$(CXX) $(SOFLAG) -o $@ $^ $(LDFLAGS)

-include $(DEPENDS)

$(DEPDIR)/%.d: %.cc
	@mkdir -p $(DEPDIR)
	g++ -M $(CXXFLAGS) $^ > $@
	@mv -f $@ $@.tmp
	@sed -e 's|.*:|$(OBJDIR)/$*.o:|' < $@.tmp > $@
	@sed -e 's/.*://' -e 's/\\$$//' < $@.tmp | fmt -1 | \
	sed -e 's/^ *//' -e 's/$$/:/' >> $@
	@rm -f $@.tmp

$(DICTSRC): $(HDR) linkdef_srppac.h
	rootcint -f $@ -c -I. $(INCLUDE) `artemis-config --cflags`  -I$(ROOTSYS)/include $^

$(OBJDIR)/%.o: %.cc
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f  $(DEPDIR)/*.d $(OBJDIR)/*.o $(LIBNAME).$(SOEXT) $(DICTOBJ) $(DICTSRC) $(DICTHDR)
	rmdir $(OBJDIR) $(DEPDIR)
