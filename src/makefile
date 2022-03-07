# target
LIBNAME = libribf141

OBJ += TModuleDecoderAMTTDC.o
OBJ += TDaliData.o
OBJ += TDaliProcessor.o
OBJ += TReplaceIDProcessor.o
OBJ += TTimingAverageProcessor.o

CXX=$(shell artemis-config --cxx)
UNAME = $(shell uname)
ifeq ($(UNAME),Darwin)
SOFLAG = -Wl,-undefined -Wl,dynamic_lookup -dynamiclib
SOEXT = so
else
SOFLAG = -shared -Wl,-soname,$(LIBNAME).so
SOEXT = so
endif

TARGET = $(LIBNAME).$(SOEXT)

# local include directories
INCLUDE = $(addprefix -I../share/src/, $(VPATH))
INCLUDE += -I../share/src -I${ART_SHARE_DIR}/include
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

ARTEMIS_HOME ?= /opt/local


ifeq ($(CXX),icpc)
CXXFLAGS = -O2 -Wall -I. $(INCLUDE) `artemis-config --cflags` -fPIC `root-config --cflags` -qopenmp
# CXXFLAGS += -g 
DICTCXXFLAGS = -O2 -Wall -I. $(INCLUDE) `artemis-config --cflags`  #`root-config --cflags` 
LDFLAGS = `artemis-config --libs`  -L../share/src -L${ART_SHARE_DIR}/lib -luser `root-config --libs` -lTreePlayer -lGeom  -qopenmp
else
ifeq ($(CXX),mpiicpc)
CXXFLAGS = -O2 -Wall -I. $(INCLUDE) `artemis-config --cflags` -fPIC `root-config --cflags` -qopenmp -DHAVE_MPI_H -DUSE_MPI
# CXXFLAGS += -g n
DICTCXXFLAGS = -O2 -Wall -I. $(INCLUDE) `artemis-config --cflags`  #`root-config --cflags` 
LDFLAGS = `artemis-config --libs`  -L../share/src -L${ART_SHARE_DIR}/lib -luser `root-config --libs` -lTreePlayer -lGeom  -qopenmp
else
CXXFLAGS = -O2 -Wall -I. $(INCLUDE) `artemis-config --cflags` -fPIC `root-config --cflags` 
CXXFLAGS += -g 
DICTCXXFLAGS = -O2 -Wall -I. $(INCLUDE) `artemis-config --cflags` 
LDFLAGS = `artemis-config --libs`  -L../share/src -L${ART_SHARE_DIR}/lib -luser `root-config --libs` -lTreePlayer -lGeom
endif
endif


CXXFLAGS += -g
all: $(TARGET)
.PHONY: all clean

$(TARGET): $(OBJECTS) $(DICTOBJ)
	@echo `uname`
	$(CXX) $(SOFLAG) -o $@ $^ $(LDFLAGS)

-include $(DEPENDS)

$(DEPDIR)/%.d: %.cc
	@mkdir -p $(DEPDIR)
	$(CXX) -M $(CXXFLAGS) $^ > $@
	@mv -f $@ $@.tmp
	@sed -e 's|.*:|$(OBJDIR)/$*.o:|' < $@.tmp > $@
	@sed -e 's/.*://' -e 's/\\$$//' < $@.tmp | fmt -1 | \
	sed -e 's/^ *//' -e 's/$$/:/' >> $@
	@rm -f $@.tmp

$(DICTSRC): $(HDR) linkdef_user.h
	rootcint -f $@ -c $(DICTCXXFLAGS) $^

$(OBJDIR)/%.o: %.cc
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f  $(DEPDIR)/*.d $(OBJDIR)/*.o $(LIBNAME).$(SOEXT) $(DICTOBJ) $(DICTSRC) $(DICTHDR)
	rmdir $(OBJDIR) $(DEPDIR)
