################################
# alg. make-file
################################
CP = nice -5 g++ -Os -s $(extra_defines)
LINK = nice -5 g++ -s
COMP_FLAGS = $(extra_compiler_flags)

ifeq ($(override_path_libraries),)
path_libraries = $(HOME)/test/libcc /usr/local/lib
else
path_libraries = $(override_path_libraries)
endif

ifeq ($(override_libraries),)
#libraries = -lmysqlclient -lcgicc -lIzCgi -lIzCGIBase -lIzInit -lTemplate -lCGIBase -lToolbox -lIzCore -lMySQL -lLockedLog -lStringEx -lActionFactory -lLoki -lCmdLine -lboost_regex -lMatrix -lMapEx -lXSort
libraries = -lgSOAP
else
libraries = $(override_libraries)
endif

ifeq ($(override_path_includes),)
path_includes = -I$(HOME)/test/includecc/ -I/usr/include/mysql/ -I/usr/include/loki -I/usr/include/boost 
else
path_includes = $(override_path_includes)
endif

VPATH = $(extra_path_libraries_pre) $(path_libraries) $(extra_path_libraries)
LIBS = $(extra_libraries_pre) $(libraries) $(extra_libraries)
INCLUDE = $(extra_path_includes_pre) $(path_includes) $(extra_path_includes)

include $(MAKEDIR)/izcolors.mak

DEF=-c -felide-constructors -O -Wall
DEPDEF=-MM

DEBUGFLAGS=
#-g voor meelinken debug informatie

OBJDIR= ./obj/
TPLDIR= ./tpl/
IMGDIR= ./img/
WSDLDIR= ./wsdl/

wsdlparser    = wsdl2h
gsoapcompiler = soapcpp2
csoapclient   = soapC.cpp,soapClient.cpp
csoapserver   = soapC.cpp,soapServer.cpp
#cfiles        = $(soapapp).cpp soapC.cpp soapClient.cpp 
cfiles        = $(soapapp).cpp soapC.cpp soapServer.cpp 
#$(wildcard *.cpp)

objects = $(addprefix $(OBJDIR),$(patsubst %.cpp,%.o,$(cfiles)))
deps = $(addprefix $(OBJDIR),$(patsubst %.cpp,%.dep,$(cfiles)))
tpls = $(wildcard $(TPLDIR)*.tpl)
imgs = $(wildcard $(IMGDIR)*.tpl)

DEPEND = $(OBJDIR)make.depend

headers = $(wildcard *.hpp)

localoutfile=$(OBJDIR)$(outfile)

$(localoutfile):$(objects) $(LIBS)
	@printf "$c---- Link $@ ----$e"
	$(LINK) $+ -o $@

depend: $(deps)
	@printf "$l---- Make depend $@ ----$e"
	cat $(OBJDIR)*.dep > $(DEPEND)

$(OBJDIR)%.dep:$(cfiles)
	@if test ! -d $(OBJDIR); then mkdir -p $(OBJDIR); fi
	$(CP) -M $(notdir $(patsubst %.dep,%.cpp,$@)) -MT $(patsubst %.dep,%.o,$@) $(INCLUDE) > $@

$(DEPEND): $(deps)
	@printf "$l---- Make depend $@ ----$e"
	cat $(OBJDIR)*.dep > $(DEPEND)

.PHONY: clean doxy rebuild
clean:
	@printf "$c---- Clean $< ----$e"
	rm -f $(localoutfile) $(OBJDIR)*.o *.bak

cleandep:
	@rm -f $(OBJDIR)*.dep make.depend

doxy:
	doxygen .doxygen.config

rebuild: clean depend $(localoutfile)

#install: .install
install: $(localoutfile) script tpl img html xml xsd
	@printf "$c---- Install $< ----$e"
	@if test ! -d $(dir $(final_target)); then mkdir -p $(dir $(final_target)); fi
	@cp -f $(localoutfile) $(final_target)
	@if test ! -z $(chgrp_name); then chgrp -R $(chgrp_name) $(final_target); fi

install_alt: $(localoutfile) tpl_alt img_alt script_alt html_alt xml_alt xsd_alt
	@printf "$c---- Install $< ----$e"
	@if test ! -d $(dir $(final_target_alt)); then mkdir -p $(dir $(final_target_alt)); fi
	@cp -f $(localoutfile) $(final_target_alt)
	@if test ! -z $(chgrp_name_alt); then chgrp -R $(chgrp_name_alt) $(final_target_alt); fi

release: install

release_alt: install_alt

test: $(localoutfile)
	@printf "$c----Remote Install $< ----$e"
	scp  $(localoutfile) $(USER)@izontwikkel.antonius.net:$(final_target)

izdevelop: $(localoutfile)
	@printf "$c----Remote Install $< ----$e"
	scp  $(localoutfile) $(USER)@izdevelop.amg.local:$(final_target)

izmestest: $(localoutfile)
	@printf "$c----Remote Install $< ----$e"
	scp  $(localoutfile) $(USER)@izmestest.mesos.nl:$(final_target)

#$(objects): $(cfiles)
#,soapC.cpp,soapClient.cpp
#    then printf "$r---- ERROR geen typemap.h file ----$e \n "

$(HOME)/test/includecc/typemap.h:
	@if test ! -e $(HOME)/test/includecc/typemap.h; \
   then printf "$r---- ERROR geen typemap.h file ----$e \n "; \
   else printf "$c typemap.h gevonden  $(wsdlfile) "; fi 

$(WSDLDIR)$(wsdlfile):
	@if test ! -e $(WSDLDIR)$(wsdlfile); \
   then printf "$r---- ERROR geen WSDL file ----$e \n "; \
   else printf "$c---- WSDL file gevonden: $(wsdlfile) ----$e"; fi

/usr/bin/$(wsdlparser):
	@if test ! -e /usr/bin/$(wsdlparser); \
   then printf "$r---- ERROR geen WSDL parser gevonden ----$e \n "; \
   else printf "$c---- WSDL parser gevonden: /usr/bin/$(wsdlparser) ----$e"; fi 

$(soapapp).hpp: $(WSDLDIR)$(wsdlfile) $(HOME)/test/includecc/typemap.h /usr/bin/$(wsdlparser) $(WSDLDIR)$(wsdlfile) /usr/bin/$(wsdlparser)
	@printf "$c---- WSDL parsing ----$e"
	@if test ! -e /usr/bin/$(wsdlparser); \
	then $(wsdlparser) -t $(HOME)/test/includecc/typemap.h -o $(soapapp).hpp $(WSDLDIR)$(wsdlfile) ; \
	else printf "$c---- skipping ----$e"; fi


$(gsoapcompiler):
	@if test ! -e /usr/bin/$(gsoapcompiler); \
   then printf "$r---- ERROR geen gSOAP compiler gevonden ----$e \n "; \
   else printf "$c---- gSOAP compiler gevonden: /usr/bin/$(gsoapcompiler) ----$e"; fi

soapC.cpp:$(soapapp).hpp
	@printf "$c---- Genereer gSoap files mbv gSOAP compiler ----$e"
#	@if test ! -f /usr/bin/$(gsoapcompiler); then $(error ); fi
	$(gsoapcompiler) -I$(HOME)/test/includecc/ $(soapapp).hpp

$(OBJDIR)soapC.o:soapC.cpp
	@printf "$c---- Compile $< ----$e"
	@if test ! -d $(OBJDIR); then mkdir -p $(OBJDIR); fi
	@$(CP) -M $(notdir $(patsubst %.o,soapC.cpp,$@)) -MT $@ $(INCLUDE) > $(patsubst %.o,%.dep,$@)
	@$(CP) $(COMP_FLAGS) -o $@ -c -felide-constructors -O -Wall $(DEBUGFLAGS) $< $(INCLUDE)

#$(OBJDIR)soapClient.o:soapClient.cpp
#	@printf "$c---- Compile $< ----$e"
#	@if test ! -d $(OBJDIR); then mkdir -p $(OBJDIR); fi
#	@$(CP) -M $(notdir $(patsubst %.o,soapClient.cpp,$@)) -MT $@ $(INCLUDE) > $(patsubst %.o,%.dep,$@)
#	@$(CP) $(COMP_FLAGS) -o $@ -c -felide-constructors -O -Wall $(DEBUGFLAGS) $< $(INCLUDE)

$(OBJDIR)soapServer.o:soapServer.cpp
	@printf "$c---- Compile $< ----$e"
	@if test ! -d $(OBJDIR); then mkdir -p $(OBJDIR); fi
	@$(CP) -M $(notdir $(patsubst %.o,soapServer.cpp,$@)) -MT $@ $(INCLUDE) > $(patsubst %.o,%.dep,$@)
	@$(CP) $(COMP_FLAGS) -o $@ -c -felide-constructors -O -Wall $(DEBUGFLAGS) $< $(INCLUDE)

$(OBJDIR)$(soapapp).o:$(soapapp).cpp
	@printf "$c---- Compile $< ----$e"
	@if test ! -d $(OBJDIR); then mkdir -p $(OBJDIR); fi
	@$(CP) -M $(notdir $(patsubst %.o,$(soapapp).cpp,$@)) -MT $@ $(INCLUDE) > $(patsubst %.o,%.dep,$@)
	@$(CP) $(COMP_FLAGS) -o $@ -c -felide-constructors -O -Wall $(DEBUGFLAGS) $< $(INCLUDE)

#$(OBJDIR)%.o:%.cpp
#	@printf "$c---- Compile $< ----$e"
#	@if test ! -d $(OBJDIR); then mkdir -p $(OBJDIR); fi
#	@$(CP) -M $(notdir $(patsubst %.o,%.cpp,$@)) -MT $@ $(INCLUDE) > $(patsubst %.o,%.dep,$@)
#	@$(CP) $(COMP_FLAGS) -o $@ -c -felide-constructors -O -Wall $(DEBUGFLAGS) $< $(INCLUDE)

ifneq ($(MAKECMDGOALS),install)
ifneq ($(MAKECMDGOALS),tpl)
ifneq ($(MAKECMDGOALS),img)
include $(DEPEND)
endif
endif
endif

ifneq ($(mak_dir),)
include $(mak_dir)/izinc.mak
else
include $(subst !,/,$(subst !/,!,$(dir $(subst csource,/,$(subst /,!,$(PWD))))))csource/makedir/izinc.mak
endif
