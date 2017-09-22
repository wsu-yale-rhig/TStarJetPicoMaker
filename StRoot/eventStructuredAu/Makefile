DEPENDROOT    = $(shell [ -n "${ROOTSYS}" ] && echo ${ROOTSYS} || echo "ROOTSYS_NOTSET" )

include ./Makefile.arch

MODULE	      = TStarJetPico

MODDICTSBASE  = $(MODULE)RootDict
MODDICTS      = $(MODDICTSBASE).$(SrcSuf)
MODDICTO      = $(MODDICTSBASE).$(ObjSuf)

LINKDEFFILE   = $(MODULE)LinkDef.h
SRCTMP        = $(wildcard $(MODULE)*.h)
SRCTMP        += $(wildcard TStarJetVector*.h)
SRCTMP        += $(wildcard TStarJetReader*.h)
SRCTMPC       = $(patsubst $(MODDICTSBASE).h,,$(SRCTMP))
MODHEADERS    = $(patsubst $(MODULE)LinkDef.h,,$(SRCTMPC))

MODSRCS	      = $(patsubst %.h,%.$(SrcSuf),$(MODHEADERS)) \
		$(MODDICTS)

MODO          = $(patsubst %.h,%.$(ObjSuf),$(MODHEADERS)) \
                $(MODDICTO)

MODSO         = lib$(MODULE).$(DllSuf)

# uncomment for debug info in the library
# CXXFLAGS     += -g

ifeq ($(PLATFORM),win32)
MODLIB        = lib$(MODULE).lib
else
MODLIB        = $(shell pwd)/$(MODSO)
endif

OBJS          = $(MODO)

# # suppress warnings during dictionary creation
CXXFLAGS		+= -Wno-return-type-c-linkage -Wno-undefined-bool-conversion


.SUFFIXES: .$(SrcSuf) .$(ObjSuf) .$(DllSuf)

all:            $(MODSO)

$(MODSO):	$(MODO)
ifeq ($(ARCH),aix)
		/usr/ibmcxx/bin/makeC++SharedLib $(OutPutOpt) $@ $(LIBS) -p 0 $^
else
ifeq ($(ARCH),aix5)
		/usr/vacpp/bin/makeC++SharedLib $(OutPutOpt) $@ $(LIBS) -p 0 $^
else
ifeq ($(PLATFORM),macosx)
# We need to make both the .dylib and the .so
		$(LD) $(SOFLAGS) $^ $(OutPutOpt) $@
ifneq ($(subst $(MACOSX_MINOR),,1234),1234)
ifeq ($(MACOSX_MINOR),4)
		ln -sf $@ $(subst .$(DllSuf),.so,$@)
else
		$(LD) -m64 -bundle -undefined $(UNDEFOPT) $(LDFLAGS) $^ \
		   $(OutPutOpt) $(subst .$(DllSuf),.so,$@)
endif
endif
else
ifeq ($(PLATFORM),win32)
		bindexplib $* $^ > $*.def
		lib -nologo -MACHINE:IX86 $^ -def:$*.def \
		   $(OutPutOpt)$(MODLIB)
		$(LD) $(SOFLAGS) $(LDFLAGS) $^ $*.exp $(LIBS) \
		   $(OutPutOpt)$@
		$(MT_DLL)
else
		$(LD) $(SOFLAGS) $(LDFLAGS) $^ $(OutPutOpt) $@ $(EXPLLINKLIBS)
endif
endif
endif
endif
		@echo "$@ done"

clean:
		@rm -f $(OBJS) $(MODSO) $(MODDICTS) $(MODDICTSBASE).h core

distclean:      clean
		-@mv -f linearIO.root linearIO.roott
		@rm -f $(MODSO) $(MODLIB) *Dict.* *.def *.exp \
		   *.root *.ps *.so *.lib *.dll *.d *.log .def so_locations

.SUFFIXES: .$(SrcSuf)

$(MODDICTS): $(MODHEADERS) $(LINKDEFFILE)
	@echo "[i] Generating dictionary $@..."
	@rootcint -f $@ -c $^

.$(SrcSuf).$(ObjSuf):
	$(CXX)  $(CXXFLAGS) -c $<
