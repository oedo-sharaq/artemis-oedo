# target
LIBNAME = liboedo

VPATH = hist cat coin command converter cont decoder mwdc plastic ppac scaler gate sh04

#OBJ += TChargeValidateProcessor.o
#OBJ += TTimeValidator.o
OBJ += TTinaProcessor.o
OBJ += TTinaData.o
OBJ += TDaliProcessor.o
OBJ += TDaliData.o
#OBJ += TModuleDecoderA3100.o
#OBJ += TModuleDecoderSIS3301.o
#OBJ += TSimpleDataMappingProcessor.o
OBJ += TIonChamberProcessor.o
OBJ += TS1IonChamberProcessor.o
#OBJ += TPPACAnodeTimingProcessor.o
OBJ += TSingleTOFProcessor.o
OBJ += TTOF2BetaProcessor.o
#OBJ += TCmdSave.o
#OBJ += TCmdPrint.o
#OBJ += TPPACProcessorQTC.o
#OBJ += TBrhoReconstructProcessor.o
OBJ += TPIDSingleSectionProcessor.o
#OBJ += TCmdPadZoom.o
OBJ += TRawDataTriggeredList.o
OBJ += TModuleDecoderA3100FreeRunTSI.o
OBJ += TTimingChargeTriggeredListMappingProcessor.o
OBJ += TTimingAverageProcessor.o

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
INCLUDE += -I../share/src
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



CXXFLAGS = -O2 -Wall -Wextra -I. $(INCLUDE) `artemis-config --cflags`  -fPIC `root-config --cflags`  -g
LDFLAGS = `artemis-config --libs`  -L../share/src -luser `root-config --libs` -lTreePlayer

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

$(DICTSRC): $(HDR) linkdef_user.h
	rootcint -f $@ -c -p -O2 -Wall -I. $(INCLUDE) `artemis-config --cflags` $^

$(OBJDIR)/%.o: %.cc
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f  $(DEPDIR)/*.d $(OBJDIR)/*.o $(LIBNAME).$(SOEXT) $(DICTOBJ) $(DICTSRC) $(DICTHDR)
	rmdir $(OBJDIR) $(DEPDIR)
