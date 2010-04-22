################################
# alg. make-file
################################

ifeq ($(CVSDIR),)
SPACE=$(subst x, ,x)
TMPHOME=/$(subst $(SPACE),/,$(strip $(subst /, ,$(HOME))))
include $(TMPHOME)/$(word 1, $(subst /, , $(subst $(TMPHOME)/,,$(PWD))))/csource/makedir/basedirinc.mak
endif

include $(MAKEDIR)/izextern.mak

all: mocks $(localoutfile)

ifeq ($(MAKECMDGOALS),debug)
DOEDEBUG = debug
endif

ifdef DOEDEBUG
DEBUGFLAGS=-g
LINKSTRIP=
else
DEBUGFLAGS=
LINKSTRIP=-s
endif

ifeq ($(OPTIMIZE),)
OPTIMIZE=-Os
endif

ifeq ($(MAKECMDGOALS),profile)
PROFILEFLAG=-pg
DEBUGFLAGS=-g
LINKSTRIP=
OPTIMIZE=-O0
else
PROFILEFLAG=
endif

VPATH = $(extra_path_libraries_pre) $(path_libraries) $(extra_path_libraries)
LIBS = $(extra_libraries_pre) $(libraries) $(extra_libraries)
INCLUDE = $(extra_path_includes_pre) $(path_includes) $(extra_path_includes)

include $(MAKEDIR)/izcolors.mak

OBJDIR= ./obj/
TPLDIR= ./tpl/
IMGDIR= ./img/
WSDLDIR= ./wsdl/
ELMDIR= ./elm/

mock_files := $(shell grep -l MOCK *.?pp)
headers = $(wildcard *.hpp)
cfiles = $(wildcard *.cpp)
objects = $(addprefix $(OBJDIR),$(patsubst %.cpp,%.o,$(cfiles)))
deps = $(addprefix $(OBJDIR),$(patsubst %.cpp,%.dep,$(cfiles)))
tpls = $(wildcard $(TPLDIR)*.tpl)
imgs = $(wildcard $(IMGDIR)*.tpl)

DEPEND = $(OBJDIR)make.depend

localoutfile=$(OBJDIR)$(outfile)

$(localoutfile):mocks $(objects) $(LIBS)
	@printf "$c---- Link $@ ----$e"
	@$(LINK) $(LINK_FLAGS) $(PROFILEFLAG) $+ -o $@

no_mocks_msg:
	@echo "-- NO MOCKS"

updir: updir_msg
	$(MAKE) -C ..

updir_msg:
	@echo "-- updir"

MOCKDIR=.mocks
MOCKDIR_DOXY_SRC=.mocks_doxy
MOCKDIR_DOXY_DEST=.mocks_xml

ifneq ($(mock_files),)
mocks: mocks_doxy mocks_xml mocks_build mocks_clean
else
mocks: no_mocks_msg
endif

mocks_clean:
	@echo "-- mocks_clean"
	rm -rf $(MOCKDIR)
	rm -rf $(MOCKDIR_DOXY_SRC)
	rm -rf $(MOCKDIR_DOXY_DEST)

mocks_mkdir:
	@echo "-- mocks_mkdir"
	mkdir -p $(MOCKDIR)
	mkdir -p $(MOCKDIR_DOXY_SRC)

mocks_doxy: updir mocks_clean mocks_mkdir
	@echo "Generate dependencies for $(mock_files)"
	$(CP) -D MOCK_RUN -M -MM $(mock_files) $(INCLUDE) | ../obj/mocks --link

mocks_xml:
	@echo "-- mocks_xml"
	doxygen MOCKS.doxy

mocks_build:
	../obj/mocks

show_Basedir:
	@printf "\n"
	@printf "BASEDIR: $(BASEDIR)\n"
	@printf "boost: $(boost_includes)\n"
	@printf "Libs: $(LIBS)\n"

depend: $(deps)
	@printf "$l---- Make depend ----$e"
	@cat $(OBJDIR)*.dep > $(DEPEND)

$(OBJDIR)%.dep:%.cpp
	@if test ! -d $(OBJDIR); then mkdir -p $(OBJDIR); fi
	@$(CP) $(COMP_FLAGS) $(HOST_SPECIFIC_DEFINE) -M $(notdir $(patsubst %.dep,%.cpp,$@)) -MT $(patsubst %.dep,%.o,$@) $(INCLUDE) > $@

$(DEPEND): $(deps)
	@printf "$l---- Make depend ----$e"
	@cat $(OBJDIR)*.dep > $(DEPEND)

.PHONY: clean doxy rebuild install
clean: clean_hdr_compile
	@printf "$c---- Clean $< ----$e"
	@rm -f $(localoutfile) $(OBJDIR)*.o *.bak *.iz_org

cleandep:
	@rm -f $(OBJDIR)*.dep make.depend

doxy:
	doxygen .doxygen.config

rebuild: clean depend $(localoutfile)

debug: clean depend $(localoutfile)

oldprofile: clean depend $(localoutfile)

profile: $(localoutfile)

install: $(localoutfile) script cron conf style tpl img html xml xsd elmstd elmxml elmimg elmdec elmshow
	@printf "$c---- Install $< ----$e"
	@izinstall -d $(dir $(final_target))
	@izinstall $(chgrp_option) -m 775 $(localoutfile) $(final_target)

install_alt: $(localoutfile) tpl_alt img_alt script_alt cron_alt conf_alt style_alt html_alt xml_alt xsd_alt elmstd_alt elmxml_alt elmimg_alt elmdec_alt elmshow_alt
	@printf "$c---- Install $< ----$e"
	@izinstall -d $(dir $(final_target))
	@izinstall $(chgrp_option) -m 775 $(localoutfile) $(final_target)


applib : $(objects) tpl
	@printf "$l---- Maak applib ----$e"
	@rm -f $(testlibfile)
	@nice -n5 ar q $(testlibfile) $(objects)


release: install

release_alt: install_alt


izontwikkel: $(localoutfile)
	@printf "$c----Remote Install $< ----$e"
	scp  $(localoutfile) $(USER)@izontwikkel.antonius.net:$(final_target)

izdevelop: $(localoutfile)
	@printf "$c----Remote Install $< ----$e"
	scp  $(localoutfile) $(USER)@izdevelop.amg.local:$(final_target)

izmestest: $(localoutfile)
	@printf "$c----Remote Install $< ----$e"
	scp  $(localoutfile) $(USER)@izmestest.mesos.nl:$(final_target)


ifneq ($(MAKECMDGOALS),apptar)
tardir_prefix =
else
tardir_prefix = $(BASEDIR)
tarname = $(notdir $(PWD))
endif
new_tgt = $(tardir_prefix)$(final_target)
apptar:  $(localoutfile) script cron style tpl img html xml xsd elmstd elmxml elmimg elmdec elmshow
	@if test ! -d $(dir $(new_tgt)); then mkdir -p $(dir $(new_tgt)); fi
	@printf "$c---- Local copy $< ----$e"
	@cp -f $(localoutfile) $(new_tgt)
	@echo "apptar:" > $(BASEDIR)/Makefile
	@echo "	tar -czvf $(tarname).tgz ./home" >> $(BASEDIR)/Makefile
	@chown :intrazis $(BASEDIR)/home -R
	@echo "Call make in" $(BASEDIR)



#$(objects): $(cfiles)

$(OBJDIR)%.o:%.cpp
	@printf "$c---- Compile $< ----$e"
	@if test ! -d $(OBJDIR); then mkdir -p $(OBJDIR); fi
	@$(CP) $(COMP_FLAGS) $(HOST_SPECIFIC_DEFINE) -M $(notdir $(patsubst %.o,%.cpp,$@)) -MT $@ $(INCLUDE) > $(patsubst %.o,%.dep,$@)
	@$(CP) -o $@ $(COMP_FLAGS) $(HOST_SPECIFIC_DEFINE) $< $(INCLUDE)

doetest: applib
	@printf "$c---- test compileren en starten ----$e"
	@$(MAKE) -C test
	@test/obj/tddRun

cleanall: clean
	@$(MAKE) clean -C test

ifneq ($(MAKECMDGOALS),install)
ifneq ($(MAKECMDGOALS),tpl)
ifneq ($(MAKECMDGOALS),img)
ifneq ($(MAKECMDGOALS),elmstd)
ifneq ($(MAKECMDGOALS),elmxml)
ifneq ($(MAKECMDGOALS),elmimg)
ifneq ($(MAKECMDGOALS),elmdec)
ifneq ($(MAKECMDGOALS),elmshow)
include $(DEPEND)
endif
endif
endif
endif
endif
endif
endif
endif

include $(MAKEDIR)/izinc.mak
