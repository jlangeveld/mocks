###################
# Algemene make-file
###################

ifeq ($(CVSDIR),)
SPACE=$(subst x, ,x)
TMPHOME=/$(subst $(SPACE),/,$(strip $(subst /, ,$(HOME))))
include $(TMPHOME)/$(word 1, $(subst /, , $(subst $(TMPHOME)/,,$(PWD))))/csource/makedir/basedirinc.mak
endif

LD=nice -n5 ld
DEBUGFLAGS=  #-g voor meelinken debug informatie

include $(MAKEDIR)/izcolors.mak

linkername=$(patsubst %.a,%.so,$(outfile))


soname=$(linkername).$(majorversion)
realname=$(soname).$(minorversion)


OBJDIR= ./obj/
cfiles = $(wildcard *.cpp)
objects = $(addprefix $(OBJDIR),$(patsubst %.cpp,%.o,$(cfiles)))
deps = $(addprefix $(OBJDIR),$(patsubst %.cpp,%.dep,$(cfiles)))
DEPEND = $(OBJDIR)make.depend

ifneq ($(MAKECMDGOALS),apptar)
tardir_prefix =
else
tardir_prefix = $(BASEDIR)
endif

install: release

apptar: release
	@echo "apptar:" > $(BASEDIR)/Makefile
	@echo "	tar -czvf apptar.tgz ./home" >> $(BASEDIR)/Makefile
	@chown :intrazis $(BASEDIR)/home -R
	@echo "Call make in" $(BASEDIR)

install_alt: release_alt
release: tpl img script cron conf style html xml xsd
release_alt: tpl_alt img_alt script_alt cron_alt conf_alt style_alt html_alt xml_alt xsd_alt

include $(MAKEDIR)/izinc.mak
