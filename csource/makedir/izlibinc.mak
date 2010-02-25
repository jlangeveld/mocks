#############################
# Algemene Library make-file
#############################

ifndef OPTIMIZE
OPTIMIZE=-Os
endif

ifeq ($(CVSDIR),)
SPACE=$(subst x, ,x)
TMPHOME=/$(subst $(SPACE),/,$(strip $(subst /, ,$(HOME))))
include $(TMPHOME)/$(word 1, $(subst /, , $(subst $(TMPHOME)/,,$(PWD))))/csource/makedir/basedirinc.mak
endif

include $(MAKEDIR)/izextern.mak
include $(MAKEDIR)/izcolors.mak

linkername=$(patsubst %.a,%.so,$(outfile))

INCLUDE=$(extra_path_includes_pre) $(path_includes) $(extra_path_includes)
soname=$(linkername).$(majorversion)
realname=$(soname).$(minorversion)
localoutfile=$(OBJDIR)$(outfile)

.PHONY: clean doxy rebuild install
OBJDIR= ./obj/
cfiles = $(wildcard *.cpp)
objects = $(addprefix $(OBJDIR),$(patsubst %.cpp,%.o,$(cfiles)))
deps = $(addprefix $(OBJDIR),$(patsubst %.cpp,%.dep,$(cfiles)))
DEPEND = $(OBJDIR)make.depend

headers = $(wildcard *.hpp) $(wildcard *.h)

lib : $(objects)
	@printf "$l---- Maak library $(localoutfile) ----$e"
	@rm -f $(localoutfile)
	@nice -n5 ar q $(localoutfile) $(objects)

all: lib

depend: $(deps)
	@printf "$l---- Make depend ----$e"
	@cat $(OBJDIR)*.dep > $(DEPEND)

release: tpl img script style html xml xsd
release_alt: tpl_alt img_alt script_alt style_alt html_alt xml_alt xsd_alt


$(OBJDIR)%.dep:%.cpp
	@if test ! -d $(OBJDIR); then mkdir -p $(OBJDIR); fi
	$(CP) -M $(notdir $(patsubst %.dep,%.cpp,$@)) -MT $(patsubst %.dep,%.o,$@) $(INCLUDE) > $@

$(DEPEND): $(deps)
	@printf "$l---- Make depend ----$e"
	@cat $(OBJDIR)*.dep > $(DEPEND)

intrazis:	$(headers)
	@printf "$i---- Installing $^----$e"
	cp -pf $(headers) /home/intrazis/includecc/
	if test -e $(localoutfile); then cp -pf $(localoutfile) /home/intrazis/libcc/; fi

install: $(headers)
	@printf "$i---- Installing $^ ----$e"
	@if test ! -d $(BASEDIR); then mkdir -p $(BASEDIR); fi
	@if test ! -d $(BASEDIR)/includecc/; then mkdir -p $(BASEDIR)/includecc/; fi
	@if test ! -d $(BASEDIR)/libcc/; then mkdir -p $(BASEDIR)/libcc/; fi
ifneq ($(strip $(headers)),)
	@ln -f $(headers) $(BASEDIR)/includecc/;
endif
	@if test -e $(localoutfile); then ln -f $(localoutfile) $(BASEDIR)/libcc/; fi

update:	$(headers)
	@printf "$i---- Updating ----$e"
	@if test ! -d $(BASEDIR); then mkdir -p $(BASEDIR); fi
	@if test ! -d $(BASEDIR)/includecc/; then mkdir -p $(BASEDIR)/includecc/; fi
	@if test ! -d $(BASEDIR)/libcc/; then mkdir -p $(BASEDIR)/libcc/; fi
ifneq ($(strip $(headers)),)
	@ln -f $(headers) $(BASEDIR)/includecc/;
endif
	@if test -e $(localoutfile); then ln -f $(localoutfile) $(BASEDIR)/libcc/; fi

$(realname): lib

full: clean depend lib

debug: clean lib

profile: clean lib

test: $(objects)
	@printf "$l** copy test files **$e"
	cp $(localoutfile) $(headers) test

clean: clean_hdr_compile
	@printf "$l** cleaning up output files **$e"
	@rm -f *.bak *.orig $(localoutfile) $(linkername) $(realname) $(soname) $(OBJDIR)*.o $(OBJDIR)*.dep

cleandep:
	@rm -f $(OBJDIR)*.dep make.depend

#$(OBJDIR)*.dep

doetest: lib
	@ln -fs $(outfile) $(testlibfile)
	@printf "$c---- test compileren en starten ----$e"
	@$(MAKE) -C test
	@test/obj/tddRun

cleanall: clean
	@$(MAKE) clean -C test

$(OBJDIR)%.o:%.cpp
	@printf "$c---- Compile $< ----$e"
	@if test ! -d $(OBJDIR); then mkdir -p $(OBJDIR); fi
	$(CP) -M $(notdir $(patsubst %.o,%.cpp,$@)) -MT $@ $(INCLUDE) > $(patsubst %.o,%.dep,$@)
	$(CP) $(COMP_FLAGS) $(HOST_SPECIFIC_DEFINE) -o $@ -c $< $(INCLUDE)

%.o:%.cpp
	@printf "$c---- Compile $< ----$e"
	@if test ! -d $(OBJDIR); then mkdir -p $(OBJDIR); fi
	@$(CP) -M $(notdir $(patsubst %.o,%.cpp,$@)) -MT $@ $(INCLUDE) > $(patsubst %.o,%.dep,$@)
	@$(CP) $(COMP_FLAGS) $(HOST_SPECIFIC_DEFINE) -o $@ -c $< $(INCLUDE)

ifneq ($(MAKECMDGOALS),release)
ifneq ($(MAKECMDGOALS),install)
ifneq ($(MAKECMDGOALS),tpl)
ifneq ($(MAKECMDGOALS),img)
include $(DEPEND)
endif
endif
endif
endif

include $(MAKEDIR)/izinc.mak
