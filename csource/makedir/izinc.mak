################################
# alg. make-file
################################

ifeq ($(CVSDIR),)
SPACE=$(subst x, ,x)
TMPHOME=/$(subst $(SPACE),/,$(strip $(subst /, ,$(HOME))))
include $(TMPHOME)/$(word 1, $(subst /, , $(subst $(TMPHOME)/,,$(PWD))))/csource/makedir/basedirinc.mak
endif

include $(MAKEDIR)/izcolors.mak

################################
# HOST dependant stuff
################################

ifeq ( "$(HOST_SPECIFIC_DEFINE)", "" )

ifneq ("$(HOSTNAME)" , "izdevelop.amg.local")
HOST_SPECIFIC_DEFINE=
else
HOST_SPECIFIC_DEFINE=-DDEVELOP
endif

endif

ifeq ("$(MAKECMDGOALS)","debug")
DEBUGFLAGS=-g
else
DEBUGFLAGS=
endif

ifeq ("$(MAKECMDGOALS)","profile")
PROFILEFLAG=-pg
else
PROFILEFLAG=
endif

ifeq ( "$(MAKECMDGOALS)", "alldebug" )
DEBUGFLAGS=-ggdb
LINKSTRIP=
PROFILEFLAG=-pg
GPROF_FLAGS=-fprofile-arcs -ftest-coverage
endif

ifeq ($(tpl_src),)
TPLDIR= tpl/
else
TPLDIR= $(tpl_src)
endif

ifeq ($(img_src),)
IMGDIR= img/
else
IMGDIR= $(img_src)
endif

ifeq ($(script_src),)
SCRIPTDIR= script/
else
SCRIPTDIR= $(script_src)
endif

ifeq ($(cron_src),)
CRONDIR= cron/
else
CRONDIR= $(cron_src)
endif

ifeq ($(conf_src),)
CONFDIR= conf/
else
CONFDIR= $(conf_src)
endif

ifeq ($(style_src),)
STYLEDIR= style/
else
STYLEDIR= $(style_src)
endif

INSTALLDIR= install/

ifeq ($(html_src),)
HTMLDIR= html/
else
HTMLDIR= $(html_src)
endif

ifeq ($(xml_src),)
XMLDIR= xml/
else
XMLDIR= $(xml_src)
endif

ifeq ($(xsd_src),)
XSDDIR= xsd/
else
XSDDIR= $(xsd_src)
endif

ifeq ($(wsdl_src),)
WSDLDIR= wsdl/
else
WSDLDIR= $(wsdl_src)
endif

ifeq ($(elmstd_src),)
ELMSTDDIR= elm/std/
else
ELMSTDDIR= $(elmstd_src)
endif

ifeq ($(elmxml_src),)
ELMXMLDIR= elm/xml/
else
ELMXMLDIR= $(elmxml_src)
endif

ifeq ($(elmimg_src),)
ELMIMGDIR= elm/img/
else
ELMIMGDIR= $(elmimg_src)
endif

ifeq ($(elmdec_src),)
ELMDECDIR= elm/dec/
else
ELMDECDIR= $(elmdec_src)
endif

ifeq ($(elmshow_src),)
ELMSHOWDIR= elm/show/
else
ELMSHOWDIR= $(elmshow_src)
endif

tpl_files = $(subst $(TPLDIR)CVS, ,$(wildcard $(TPLDIR)*.tpl))
img_files = $(subst $(IMGDIR)CVS, ,$(wildcard $(IMGDIR)*))
script_files = $(subst $(SCRIPTDIR)CVS, ,$(wildcard $(SCRIPTDIR)*$(script_ext)))
cron_files = $(subst $(CRONDIR)CVS, ,$(wildcard $(CRONDIR)*$(cron_ext)))
conf_files = $(subst $(CONFDIR)CVS, ,$(wildcard $(CONFDIR)*$(conf_ext)))
style_files = $(subst $(STYLEDIR)CVS, ,$(wildcard $(STYLEDIR)*$(style_ext)))
html_files= $(subst $(HTMLDIR)CVS, ,$(wildcard $(HTMLDIR)*))
xml_files= $(subst $(XMLDIR)CVS, ,$(wildcard $(XMLDIR)*))
xsd_files= $(subst $(XSDDIR)CVS, ,$(wildcard $(XSDDIR)*))
wsdl_files= $(subst $(WSDLDIR)CVS, ,$(wildcard $(WSDLDIR)*))

elmstd_files= $(subst $(ELMSTDDIR)CVS, ,$(wildcard $(ELMSTDDIR)*.tpl))
elmxml_files= $(subst $(ELMXMLDIR)CVS, ,$(wildcard $(ELMXMLDIR)*.tpl))
elmimg_files= $(subst $(ELMIMGDIR)CVS, ,$(wildcard $(ELMIMGDIR)*))
elmdec_files= $(subst $(ELMDECDIR)CVS, ,$(wildcard $(ELMDECDIR)*.tpl))
elmshow_files= $(subst $(ELMSHOWDIR)CVS, ,$(wildcard $(ELMSHOWDIR)*.tpl))

tpl: .tpl
img: .img
script: .script
cron: .cron
conf: .conf
style: .style
html: .html
xml: .xml
xsd: .xsd
wsdl: .wsdl

elmstd: .elmstd
elmxml: .elmxml
elmimg: .elmimg
elmdec: .elmdec
elmshow: .elmshow
elm: .elm

ifeq ($(tardir_prefix),)

ifneq ($(override_chgrp_name),)
ifeq ($(override_chgrp_name),<null>)
chgrp_name =
else
chgrp_name = $(override_chgrp_name)
endif
else
chgrp_name = intrazis
endif

ifneq ($(override_chgrp_name_alt),)
ifeq ($(override_chgrp_name_alt),<null>)
chgrp_name_alt =
else
chgrp_name_alt = $(override_chgrp_name_alt)
endif
else
chgrp_name_alt = intrazis
endif

ifneq ($(chgrp_name),)
chgrp_option = -g $(chgrp_name)
endif

.tpl: $(tpl_files)
ifneq ($(tpl_dir),)
ifneq ($(tpl_files),)
	@printf "$c---- Install Template $< ----$e"
	izinstall -d $(chgrp_option) -m 775 $(tardir_prefix)$(tpl_dir)
	izinstall $(chgrp_option) -m 775 $^ $(tardir_prefix)$(tpl_dir)
endif
endif

tpl_alt: $(tpl_files)
ifneq ($(tpl_dir_alt),)
ifneq ($(tpl_files),)
	@printf "$c---- Install Template $< ----$e"
	@izinstall -d $(chgrp_option) -m 775 $(tardir_prefix)$(tpl_dir)
	@izinstall $(chgrp_option) -m 775 $^ $(tardir_prefix)$(tpl_dir_alt)
endif
endif

.img: $(img_files)
ifneq ($(img_dir),)
ifneq ($(img_files),)
	@printf "$c---- Install Image $< ----$e"
	@izinstall -d $(chgrp_option) -m 775 $(tardir_prefix)$(img_dir)
	@izinstall $(chgrp_option) -m 775 $^ $(tardir_prefix)$(img_dir)
endif
endif

img_alt: $(img_files)
ifneq ($(img_dir_alt),)
ifneq ($(img_files),)
	@printf "$c---- Install Image $< ----$e"
	@izinstall -d $(chgrp_option) -m 775 $(tardir_prefix)$(img_dir_alt)
	@izinstall $(chgrp_option) -m 775 $^ $(tardir_prefix)$(img_dir_alt)
endif
endif

.script: $(script_files)
ifneq ($(script_dir),)
ifneq ($(script_files),)
	@printf "$c---- Install Script $< ----$e"
	@if test ! -d $(tardir_prefix)$(script_dir); then mkdir -p $(tardir_prefix)$(script_dir); fi
	@cp -r -f $^ $(tardir_prefix)$(script_dir)
	@if test ! -z $(chgrp_name); then chgrp -R $(chgrp_name) $(subst $(SCRIPTDIR), $(tardir_prefix)$(script_dir)/, $^); fi
endif
endif

script_alt: $(script_files)
ifneq ($(script_dir_alt),)
ifneq ($(script_files),)
	@printf "$c---- Install Script $< ----$e"
	@izinstall -d $(chgrp_option) -m 775 $(tardir_prefix)$(script_dir_alt)
	@izinstall $(chgrp_option) -m 775 $^ $(tardir_prefix)$(script_dir_alt)
endif
endif

.cron: $(cron_files)
ifneq ($(cron_dir),)
ifneq ($(cron_files),)
	@printf "$c---- Install Cron-files $< ----$e"
	@if test ! -d $(tardir_prefix)$(cron_dir); then mkdir -p $(tardir_prefix)$(cron_dir); fi
	@cp -r -f $^ $(tardir_prefix)$(cron_dir)
	@if test ! -z $(chgrp_name); then chgrp -R $(chgrp_name) $(subst $(CRONDIR), $(tardir_prefix)$(cron_dir)/, $^); fi
endif
endif

cron_alt: $(cron_files)
ifneq ($(cron_dir_alt),)
ifneq ($(cron_files),)
	@printf "$c---- Install cron $< ----$e"
	@izinstall -d $(chgrp_option) -m 775 $(tardir_prefix)$(cron_dir_alt)
	@izinstall $(chgrp_option) -m 775 $^ $(tardir_prefix)$(cron_dir_alt)
endif
endif

.conf: $(conf_files)
ifneq ($(conf_dir),)
ifneq ($(conf_files),)
	@printf "$c---- Install Conf-files $< ----$e"
	@if test ! -d $(tardir_prefix)$(conf_dir); then mkdir -p $(tardir_prefix)$(conf_dir); fi
	@cp -r -f $^ $(tardir_prefix)$(conf_dir)
	@if test ! -z $(chgrp_name); then chgrp -R $(chgrp_name) $(subst $(CONFDIR), $(tardir_prefix)$(conf_dir)/, $^); fi
endif
endif

conf_alt: $(conf_files)
ifneq ($(conf_dir_alt),)
ifneq ($(conf_files),)
	@printf "$c---- Install conf $< ----$e"
	@izinstall -d $(chgrp_option) -m 775 $(tardir_prefix)$(conf_dir_alt)
	@izinstall $(chgrp_option) -m 775 $^ $(tardir_prefix)$(conf_dir_alt)
endif
endif

.style: $(style_files)
ifneq ($(style_dir),)
ifneq ($(style_files),)
	@printf "$c---- Install Style $< ----$e"
	@izinstall -d $(chgrp_option) -m 775 $(tardir_prefix)$(style_dir)
	@izinstall $(chgrp_option) -m 775 $^ $(tardir_prefix)$(style_dir)
endif
endif

style_alt: $(style_files)
ifneq ($(style_dir_alt),)
ifneq ($(style_files),)
	@printf "$c---- Install Style $< ----$e"
	@izinstall -d $(chgrp_option) -m 775 $(tardir_prefix)$(style_dir_alt)
	@izinstall $(chgrp_option) -m 775 $^ $(tardir_prefix)$(style_dir_alt)
endif
endif

.html: $(html_files)
ifneq ($(html_dir),)
ifneq ($(html_files),)
	@printf "$c---- Install Html Document $< ----$e"
	@izinstall -d $(chgrp_option) -m 775 $(tardir_prefix)$(html_dir)
	@izinstall -p $(chgrp_option) -m 775 $^ $(tardir_prefix)$(html_dir)
endif
endif

html_alt: $(html_files)
ifneq ($(html_dir_alt),)
ifneq ($(html_files),)
	@printf "$c---- Install Html Document $< ----$e"
	@izinstall -d $(chgrp_option) -m 775 $(tardir_prefix)$(html_dir_alt)
	@izinstall -p $(chgrp_option) -m 775 $^ $(tardir_prefix)$(html_dir_alt)
endif
endif

.xml: $(xml_files)
ifneq ($(xml_dir),)
ifneq ($(xml_files),)
	@printf "$c---- Install Xml Document $< ----$e"
	@izinstall -d $(chgrp_option) -m 775 $(tardir_prefix)$(xml_dir)
	@izinstall $(chgrp_option) -m 775 $^ $(tardir_prefix)$(xml_dir)
endif
endif

xml_alt: $(xml_files)
ifneq ($(xml_dir_alt),)
ifneq ($(xml_files),)
	@printf "$c---- Install Xml Document $< ----$e"
	@izinstall -d $(chgrp_option) -m 775 $(tardir_prefix)$(xml_dir_alt)
	@izinstall $(chgrp_option) -m 775 $^ $(tardir_prefix)$(xml_dir_alt)
endif
endif

.xsd: $(xsd_files)
ifneq ($(xsd_dir),)
ifneq ($(xsd_files),)
	@printf "$c---- Install Xsd Document $< ----$e"
	@izinstall -d $(chgrp_option) -m 775 $(tardir_prefix)$(xsd_dir)
	@izinstall $(chgrp_option) -m 775 $^ $(tardir_prefix)$(xsd_dir)
endif
endif

xsd_alt: $(xsd_files)
ifneq ($(xsd_dir_alt),)
ifneq ($(xsd_files),)
	@printf "$c---- Install Xsd Document $< ----$e"
	@izinstall -d $(chgrp_option) -m 775 $(tardir_prefix)$(xsd_dir_alt)
	@izinstall $(chgrp_option) -m 775 $^ $(tardir_prefix)$(xsd_dir_alt)
endif
endif

.wsdl: $(wsdl_files)
ifneq ($(wsdl_dir),)
ifneq ($(wsdl_files),)
	@printf "$c---- Install Wsdl Document $< ----$e"
	@izinstall -d $(chgrp_option) -m 775 $(tardir_prefix)$(wsdl_dir)
	@izinstall $(chgrp_option) -m 775 $^ $(tardir_prefix)$(wsdl_dir)
endif
endif

wsdl_alt: $(wsdl_files)
ifneq ($(wsdl_dir_alt),)
ifneq ($(wsdl_files),)
	@printf "$c---- Install Wsdl Document $< ----$e"
	@izinstall -d $(chgrp_option) -m 775 $(tardir_prefix)$(wsdl_dir_alt)
	@izinstall $(chgrp_option) -m 775 $^ $(tardir_prefix)$(wsdl_dir_alt)
endif
endif

.elmstd: $(elmstd_files)
ifneq ($(elmstd_dir),)
ifneq ($(elmstd_files),)
	@printf "$c---- Install element types std $< ----$e"
	@izinstall -d $(chgrp_option) -m 775 $(tardir_prefix)$(elmstd_dir)
	@izinstall $(chgrp_option) -m 775 $^ $(tardir_prefix)$(elmstd_dir)
	@echo "" >> $(tardir_prefix)$(INSTALLDIR)elm.sql
	@chmod 666 $(tardir_prefix)$(INSTALLDIR)elm.sql
	@chgrp -R $(chgrp_name) $(tardir_prefix)$(INSTALLDIR)elm.sql
	$(shell /home/intrazis/tool/status_elementen.sh $(PWD)/$(INSTALLDIR)elm.sql )
endif
endif

elmstd_alt: $(elmstd_files)
ifneq ($(elmstd_dir_alt),)
ifneq ($(elmstd_files),)
	@printf "$c---- Install element types std $< ----$e"
	@izinstall -d $(chgrp_option) -m 775 $(tardir_prefix)$(elmstd_dir_alt)
	@izinstall $(chgrp_option) -m 775 $^ $(tardir_prefix)$(elmstd_dir_alt)
endif
endif

.elmxml: $(elmxml_files)
ifneq ($(elmxml_dir),)
ifneq ($(elmxml_files),)
	@printf "$c---- Install element types xml $< ----$e"
	@izinstall -d $(chgrp_option) -m 775 $(tardir_prefix)$(elmxml_dir)
	@izinstall $(chgrp_option) -m 775 $^ $(tardir_prefix)$(elmxml_dir)
endif
endif

elmxml_alt: $(elmxml_files)
ifneq ($(elmxml_dir_alt),)
ifneq ($(elmxml_files),)
	@printf "$c---- Install element types xml $< ----$e"
	@izinstall -d $(chgrp_option) -m 775 $(tardir_prefix)$(elmxml_dir_alt)
	@izinstall $(chgrp_option) -m 775 $^ $(tardir_prefix)$(elmxml_dir_alt)
endif
endif

.elmimg: $(elmimg_files)
ifneq ($(elmimg_dir),)
ifneq ($(elmimg_files),)
	@printf "$c---- Install element types img $< ----$e"
	@izinstall -d $(chgrp_option) -m 775 $(tardir_prefix)$(elmimg_dir)
	@izinstall $(chgrp_option) -m 775 $^ $(tardir_prefix)$(elmimg_dir)
endif
endif

elmimg_alt: $(elmimg_files)
ifneq ($(elmimg_dir_alt),)
ifneq ($(elmimg_files),)
	@printf "$c---- Install element types img $< ----$e"
	@izinstall -d $(chgrp_option) -m 775 $(tardir_prefix)$(elmimg_dir_alt)
	@izinstall $(chgrp_option) -m 775 $^ $(tardir_prefix)$(elmimg_dir_alt)
endif
endif

.elmdec: $(elmdec_files)
ifneq ($(elmdec_dir),)
ifneq ($(elmdec_files),)
	@printf "$c---- Install element types decursus $< ----$e"
	@izinstall -d $(chgrp_option) -m 775 $(tardir_prefix)$(elmdec_dir)
	@izinstall $(chgrp_option) -m 775 $^ $(tardir_prefix)$(elmdec_dir)
endif
endif

elmdec_alt: $(elmdec_files)
ifneq ($(elmdec_dir_alt),)
ifneq ($(elmdec_files),)
	@printf "$c---- Install element types decursus $< ----$e"
	@izinstall -d $(chgrp_option) -m 775 $(tardir_prefix)$(elmdec_dir_alt)
	@izinstall $(chgrp_option) -m 775 $^ $(tardir_prefix)$(elmdec_dir_alt)
endif
endif

.elmshow: $(elmshow_files)
ifneq ($(elmshow_dir),)
ifneq ($(elmshow_files),)
	@printf "$c---- Install element types show $< ----$e"
	@izinstall -d $(chgrp_option) -m 775 $(tardir_prefix)$(elmshow_dir)
	@izinstall $(chgrp_option) -m 775 $^ $(tardir_prefix)$(elmshow_dir)
	@echo "" >> $(tardir_prefix)$(INSTALLDIR)elm.sql
	@chmod 666 $(tardir_prefix)$(INSTALLDIR)elm.sql
	@chgrp -R $(chgrp_name) $(tardir_prefix)$(INSTALLDIR)elm.sql
	$(shell /home/intrazis/tool/status_elementen.sh $(PWD)/$(INSTALLDIR)elm.sql )
endif
endif

elmshow_alt: $(elmshow_files)
ifneq ($(elmshow_dir_alt),)
ifneq ($(elmshow_files),)
	@printf "$c---- Install element types show $< ----$e"
	@izinstall -d $(chgrp_option) -m 775 $(tardir_prefix)$(elmshow_dir_alt)
	@izinstall $(chgrp_option) -m 775 $^ $(tardir_prefix)$(elmshow_dir_alt)
endif
endif


else
	@printf "$c----- APPTAR in progress... -----$e"
ifneq ($(override_chgrp_name),)
ifeq ($(override_chgrp_name),<null>)
chgrp_name =
else
chgrp_name = $(override_chgrp_name)
endif
else
chgrp_name = intrazis
endif

ifneq ($(override_chgrp_name_alt),)
ifeq ($(override_chgrp_name_alt),<null>)
chgrp_name_alt =
else
chgrp_name_alt = $(override_chgrp_name_alt)
endif
else
chgrp_name_alt = intrazis
endif

.tpl: $(tpl_files)
ifneq ($(tpl_dir),)
ifneq ($(tpl_files),)
	@printf "$c---- Install Template $< ----$e"
	@if test ! -d $(tardir_prefix)$(tpl_dir); then mkdir -p $(tardir_prefix)$(tpl_dir); fi
	@cp -f $^ $(tardir_prefix)$(tpl_dir)
#	@chgrp -R intrazis  $(subst $(TPLDIR),$(tardir_prefix)$(tpl_dir)/,$^)
	@if test ! -z $(chgrp_name); then chgrp -R $(chgrp_name) $(subst $(TPLDIR),$(tardir_prefix)$(tpl_dir)/,$^); fi
endif
endif

tpl_alt: $(tpl_files)
ifneq ($(tpl_dir_alt),)
ifneq ($(tpl_files),)
	@printf "$c---- Install Template $< ----$e"
	@if test ! -d $(tardir_prefix)$(tpl_dir_alt); then mkdir -p $(tardir_prefix)$(tpl_dir_alt); fi
	@cp -f $^ $(tardir_prefix)$(tpl_dir_alt)
#	@chgrp -R intrazis  $(subst $(TPLDIR),$(tardir_prefix)$(tpl_dir_alt)/,$^)
	@if test ! -z $(chgrp_name_alt); then chgrp -R $(chgrp_name_alt) $(subst $(TPLDIR),$(tardir_prefix)$(tpl_dir_alt)/,$^); fi
endif
endif

.img: $(img_files)
ifneq ($(img_dir),)
ifneq ($(img_files),)
	@printf "$c---- Install Image $< ----$e"
	@if test ! -d $(tardir_prefix)$(img_dir); then mkdir -p $(tardir_prefix)$(img_dir); fi
	@cp -f $^ $(tardir_prefix)$(img_dir)
#	@chgrp -R intrazis  $(subst $(IMGDIR), $(tardir_prefix)$(img_dir)/, $^)
	@if test ! -z $(chgrp_name); then chgrp -R $(chgrp_name) $(subst $(IMGDIR), $(tardir_prefix)$(img_dir)/, $^); fi
endif
endif

img_alt: $(img_files)
ifneq ($(img_dir_alt),)
ifneq ($(img_files),)
	@printf "$c---- Install Image $< ----$e"
	@if test ! -d $(tardir_prefix)$(img_dir_alt); then mkdir -p $(tardir_prefix)$(img_dir_alt); fi
	@cp -f $^ $(img_dir_alt)
#	@chgrp -R intrazis  $(subst $(IMGDIR), $(tardir_prefix)$(img_dir_alt)/, $^)
	@if test ! -z $(chgrp_name_alt); then chgrp -R $(chgrp_name_alt) $(subst $(IMGDIR), $(tardir_prefix)$(img_dir_alt)/, $^); fi
endif
endif

.script: $(script_files)
ifneq ($(script_dir),)
ifneq ($(script_files),)
	@printf "$c---- Install Script $< ----$e"
	@if test ! -d $(tardir_prefix)$(script_dir); then mkdir -p $(tardir_prefix)$(script_dir); fi
	@cp -r -f $^ $(tardir_prefix)$(script_dir)
#	@chgrp -R intrazis  $(subst $(SCRIPTDIR), $(tardir_prefix)$(script_dir)/, $^)
	@if test ! -z $(chgrp_name); then chgrp -R $(chgrp_name) $(subst $(SCRIPTDIR), $(tardir_prefix)$(script_dir)/, $^); fi
endif
endif

script_alt: $(script_files)
ifneq ($(script_dir_alt),)
ifneq ($(script_files),)
	@printf "$c---- Install Script $< ----$e"
	@if test ! -d $(tardir_prefix)$(script_dir_alt); then mkdir -p $(tardir_prefix)$(script_dir_alt); fi
	@cp -f $^ $(tardir_prefix)$(script_dir_alt)
#	@chgrp -R intrazis  $(subst $(SCRIPTDIR), $(script_dir_alt)/, $^)
	@if test ! -z $(chgrp_name_alt); then chgrp -R $(chgrp_name_alt) $(subst $(SCRIPTDIR), $(tardir_prefix)$(script_dir_alt)/, $^); fi
endif
endif

.cron: $(cron_files)
ifneq ($(cron_dir),)
ifneq ($(cron_files),)
	@printf "$c---- Install cron $< ----$e"
	@if test ! -d $(tardir_prefix)$(cron_dir); then mkdir -p $(tardir_prefix)$(cron_dir); fi
	@cp -r -f $^ $(tardir_prefix)$(cron_dir)
#	@chgrp -R intrazis  $(subst $(CRONDIR), $(tardir_prefix)$(cron_dir)/, $^)
	@if test ! -z $(chgrp_name); then chgrp -R $(chgrp_name) $(subst $(CRONDIR), $(tardir_prefix)$(cron_dir)/, $^); fi
endif
endif

cron_alt: $(cron_files)
ifneq ($(cron_dir_alt),)
ifneq ($(cron_files),)
	@printf "$c---- Install cron $< ----$e"
	@if test ! -d $(tardir_prefix)$(cron_dir_alt); then mkdir -p $(tardir_prefix)$(cron_dir_alt); fi
	@cp -f $^ $(tardir_prefix)$(cron_dir_alt)
#	@chgrp -R intrazis  $(subst $(CRONDIR), $(cron_dir_alt)/, $^)
	@if test ! -z $(chgrp_name_alt); then chgrp -R $(chgrp_name_alt) $(subst $(CRONDIR), $(tardir_prefix)$(cron_dir_alt)/, $^); fi
endif
endif

.style: $(style_files)
ifneq ($(style_dir),)
ifneq ($(style_files),)
	@printf "$c---- Install Style $< ----$e"
	@if test ! -d $(tardir_prefix)$(style_dir); then mkdir -p $(tardir_prefix)$(style_dir); fi
	@cp -f $^ $(tardir_prefix)$(style_dir)
#	@chgrp -R intrazis  $(subst $(STYLEDIR), $(tardir_prefix)$(style_dir)/, $^)
	@if test ! -z $(chgrp_name); then chgrp -R $(chgrp_name) $(subst $(STYLEDIR), $(tardir_prefix)$(style_dir)/, $^); fi
endif
endif

style_alt: $(style_files)
ifneq ($(style_dir_alt),)
ifneq ($(style_files),)
	@printf "$c---- Install Style $< ----$e"
	@if test ! -d $(tardir_prefix)$(style_dir_alt); then mkdir -p $(tardir_prefix)$(style_dir_alt); fi
	@cp -f $^ $(tardir_prefix)$(style_dir_alt)
#	@chgrp -R intrazis  $(subst $(STYLEDIR), $(style_dir_alt)/, $^)
	@if test ! -z $(chgrp_name_alt); then chgrp -R $(chgrp_name_alt) $(subst $(STYLEDIR), $(tardir_prefix)$(style_dir_alt)/, $^); fi
endif
endif

.html: $(html_files)
ifneq ($(html_dir),)
ifneq ($(html_files),)
	@printf "$c---- Install Html Document $< ----$e"
	@if test ! -d $(tardir_prefix)$(html_dir); then mkdir -p $(tardir_prefix)$(html_dir); fi
	@cp -f $^ $(tardir_prefix)$(html_dir)
#	@chgrp -R intrazis  $(subst $(HTMLDIR), $(tardir_prefix)$(html_dir)/, $^)
	@if test ! -z $(chgrp_name); then chgrp -R $(chgrp_name) $(subst $(HTMLDIR), $(tardir_prefix)$(html_dir)/, $^); fi
endif
endif

html_alt: $(html_files)
ifneq ($(html_dir_alt),)
ifneq ($(html_files),)
	@printf "$c---- Install Html Document $< ----$e"
	@if test ! -d $(tardir_prefix)$(html_dir_alt); then mkdir -p $(tardir_prefix)$(html_dir_alt); fi
	@cp -f $^ $(tardir_prefix)$(html_dir_alt)
#	@chgrp -R intrazis  $(subst $(HTMLDIR), $(tardir_prefix)$(html_dir_alt)/, $^)
	@if test ! -z $(chgrp_name_alt); then chgrp -R $(chgrp_name_alt) $(subst $(HTMLDIR), $(tardir_prefix)$(html_dir_alt)/, $^); fi
endif
endif

.xml: $(xml_files)
ifneq ($(xml_dir),)
ifneq ($(xml_files),)
	@printf "$c---- Install Xml Document $< ----$e"
	@if test ! -d $(tardir_prefix)$(xml_dir); then mkdir -p $(tardir_prefix)$(xml_dir); fi
	@cp -f $^ $(tardir_prefix)$(xml_dir)
#	@chgrp -R intrazis  $(subst $(XMLDIR), $(tardir_prefix)$(xml_dir)/, $^)
	@if test ! -z $(chgrp_name); then chgrp -R $(chgrp_name) $(subst $(XMLDIR), $(tardir_prefix)$(xml_dir)/, $^); fi
endif
endif

xml_alt: $(xml_files)
ifneq ($(xml_dir_alt),)
ifneq ($(xml_files),)
	@printf "$c---- Install Xml Document $< ----$e"
	@if test ! -d $(tardir_prefix)$(xml_dir_alt); then mkdir -p $(tardir_prefix)$(xml_dir_alt); fi
	@cp -f $^ $(tardir_prefix)$(xml_dir_alt)
#	@chgrp -R intrazis  $(subst $(XMLDIR), $(tardir_prefix)$(xml_dir_alt)/, $^)
	@if test ! -z $(chgrp_name_alt); then chgrp -R $(chgrp_name_alt) $(subst $(XMLDIR), $(tardir_prefix)$(xml_dir_alt)/, $^); fi
endif
endif

.xsd: $(xsd_files)
ifneq ($(xsd_dir),)
ifneq ($(xsd_files),)
	@printf "$c---- Install Xsd Document $< ----$e"
	@if test ! -d $(tardir_prefix)$(xsd_dir); then mkdir -p $(tardir_prefix)$(xsd_dir); fi
	@cp -f $^ $(tardir_prefix)$(xsd_dir)
#	@chgrp -R intrazis  $(subst $(XSDDIR), $(tardir_prefix)$(xsd_dir)/, $^)
	@if test ! -z $(chgrp_name); then chgrp -R $(chgrp_name) $(subst $(XSDDIR), $(tardir_prefix)$(xsd_dir)/, $^); fi
endif
endif

xsd_alt: $(xsd_files)
ifneq ($(xsd_dir_alt),)
ifneq ($(xsd_files),)
	@printf "$c---- Install Xsd Document $< ----$e"
	@if test ! -d $(tardir_prefix)$(xsd_dir_alt); then mkdir -p $(tardir_prefix)$(xsd_dir_alt); fi
	@cp -f $^ $(tardir_prefix)$(xsd_dir_alt)
#	@chgrp -R intrazis  $(subst $(XSDDIR), $(tardir_prefix)$(xsd_dir_alt)/, $^)
	@if test ! -z $(chgrp_name_alt); then chgrp -R $(chgrp_name_alt) $(subst $(XSDDIR), $(tardir_prefix)$(xsd_dir_alt)/, $^); fi
endif
endif

.wsdl: $(wsdl_files)
ifneq ($(wsdl_dir),)
ifneq ($(wsdl_files),)
	@printf "$c---- Install Wsdl Document $< ----$e"
	@if test ! -d $(wsdl_dir); then mkdir -p $(wsdl_dir); fi
	@cp -f $^ $(wsdl_dir)
#	@chgrp -R intrazis  $(subst $(WSDLDIR), $(wsdl_dir)/, $^)
	@if test ! -z $(chgrp_name); then chgrp -R $(chgrp_name) $(subst $(WSDLDIR), $(wsdl_dir)/, $^); fi
endif
endif

wsdl_alt: $(wsdl_files)
ifneq ($(wsdl_dir_alt),)
ifneq ($(wsdl_files),)
	@printf "$c---- Install Wsdl Document $< ----$e"
	@if test ! -d $(wsdl_dir_alt); then mkdir -p $(wsdl_dir_alt); fi
	@cp -f $^ $(wsdl_dir_alt)
#	@chgrp -R intrazis  $(subst $(WSDLDIR), $(wsdl_dir_alt)/, $^)
	@if test ! -z $(chgrp_name_alt); then chgrp -R $(chgrp_name_alt) $(subst $(WSDLDIR), $(wsdl_dir_alt)/, $^); fi
endif
endif


.elmstd: $(elmstd_files)
ifneq ($(elmstd_dir),)
ifneq ($(elmstd_files),)
	@printf "$c---- Install element types std $< ----$e"
	@if test ! -d $(tardir_prefix)$(elmstd_dir); then mkdir -p $(tardir_prefix)$(elmstd_dir); fi
	@if test ! -d $(tardir_prefix)$(INSTALLDIR); then mkdir -p $(tardir_prefix)$(INSTALLDIR); fi
	@cp -f $^ $(tardir_prefix)$(elmstd_dir)
#	@chgrp -R intrazis  $(subst $(ELMSTDDIR), $(tardir_prefix)$(elmstd_dir)/, $^)
	@if test ! -z $(chgrp_name); then chgrp -R $(chgrp_name) $(subst $(ELMSTDDIR), $(tardir_prefix)$(elmstd_dir)/, $^); fi
	@if test ! -z $(chgrp_name); then chgrp -R $(chgrp_name) $(subst $(INSTALLDIR), $(tardir_prefix)$(INSTALLDIR)/, $^); fi
	@echo "" >> $(tardir_prefix)$(INSTALLDIR)elm.sql
#	@chmod 777 $(tardir_prefix)$(INSTALLDIR)
	@chmod 666 $(tardir_prefix)$(INSTALLDIR)elm.sql
	@chgrp -R $(chgrp_name) $(tardir_prefix)$(INSTALLDIR)elm.sql
	$(shell /home/intrazis/tool/status_elementen.sh $(PWD)/$(INSTALLDIR)elm.sql )
endif
endif

elmstd_alt: $(elmstd_files)
ifneq ($(elmstd_dir_alt),)
ifneq ($(elmstd_files),)
	@printf "$c---- Install element types std $< ----$e"
	@if test ! -d $(tardir_prefix)$(elmstd_dir_alt); then mkdir -p $(tardir_prefix)$(elmstd_dir_alt); fi
	@cp -f $^ $(tardir_prefix)$(elmstd_dir_alt)
#	@chgrp -R intrazis  $(subst $(ELMSTDDIR), $(tardir_prefix)$(elmstd_dir_alt)/, $^)
	@if test ! -z $(chgrp_name); then chgrp -R $(chgrp_name) $(subst $(ELMSTDDIR), $(tardir_prefix)$(elmstd_dir_alt)/, $^); fi
endif
endif

.elmxml: $(elmxml_files)
ifneq ($(elmxml_dir),)
ifneq ($(elmxml_files),)
	@printf "$c---- Install element types xml $< ----$e"
	@if test ! -d $(tardir_prefix)$(elmxml_dir); then mkdir -p $(tardir_prefix)$(elmxml_dir); fi
	@cp -f $^ $(tardir_prefix)$(elmxml_dir)
#	@chgrp -R intrazis  $(subst $(ELMXMLDIR), $(tardir_prefix)$(elmxml_dir)/, $^)
	@if test ! -z $(chgrp_name); then chgrp -R $(chgrp_name) $(subst $(ELMXMLDIR), $(tardir_prefix)$(elmxml_dir)/, $^); fi
endif
endif

elmxml_alt: $(elmxml_files)
ifneq ($(elmxml_dir_alt),)
ifneq ($(elmxml_files),)
	@printf "$c---- Install element types xml $< ----$e"
	@if test ! -d $(tardir_prefix)$(elmxml_dir_alt); then mkdir -p $(tardir_prefix)$(elmxml_dir_alt); fi
	@cp -f $^ $(tardir_prefix)$(elmxml_dir_alt)
#	@chgrp -R intrazis  $(subst $(ELMXMLDIR), $(tardir_prefix)$(elmxml_dir_alt)/, $^)
	@if test ! -z $(chgrp_name); then chgrp -R $(chgrp_name) $(subst $(ELMXMLDIR), $(tardir_prefix)$(elmxml_dir_alt)/, $^); fi
endif
endif

.elmimg: $(elmimg_files)
ifneq ($(elmimg_dir),)
ifneq ($(elmimg_files),)
	@printf "$c---- Install element types img $< ----$e"
	@if test ! -d $(tardir_prefix)$(elmimg_dir); then mkdir -p $(tardir_prefix)$(elmimg_dir); fi
	@cp -f $^ $(tardir_prefix)$(elmimg_dir)
#	@chgrp -R intrazis  $(subst $(ELMIMGDIR), $(tardir_prefix)$(elmimg_dir)/, $^)
	@if test ! -z $(chgrp_name); then chgrp -R $(chgrp_name) $(subst $(ELMIMGDIR), $(tardir_prefix)$(elmimg_dir)/, $^); fi
endif
endif

elmimg_alt: $(elmimg_files)
ifneq ($(elmimg_dir_alt),)
ifneq ($(elmimg_files),)
	@printf "$c---- Install element types img $< ----$e"
	@if test ! -d $(tardir_prefix)$(elmimg_dir_alt); then mkdir -p $(tardir_prefix)$(elmimg_dir_alt); fi
	@cp -f $^ $(tardir_prefix)$(elmimg_dir_alt)
#	@chgrp -R intrazis  $(subst $(ELMIMGDIR), $(tardir_prefix)$(elmimg_dir_alt)/, $^)
	@if test ! -z $(chgrp_name); then chgrp -R $(chgrp_name) $(subst $(ELMIMGDIR), $(tardir_prefix)$(elmimg_dir_alt)/, $^); fi
endif
endif

.elmdec: $(elmdec_files)
ifneq ($(elmdec_dir),)
ifneq ($(elmdec_files),)
	@printf "$c---- Install element types decursus $< ----$e"
	@if test ! -d $(tardir_prefix)$(elmdec_dir); then mkdir -p $(tardir_prefix)$(elmdec_dir); fi
	@cp -f $^ $(tardir_prefix)$(elmdec_dir)
#	@chgrp -R intrazis  $(subst $(ELMDECDIR), $(tardir_prefix)$(elmdec_dir)/, $^)
	@if test ! -z $(chgrp_name); then chgrp -R $(chgrp_name) $(subst $(ELMDECDIR), $(tardir_prefix)$(elmdec_dir)/, $^); fi
endif
endif

elmdec_alt: $(elmdec_files)
ifneq ($(elmdec_dir_alt),)
ifneq ($(elmdec_files),)
	@printf "$c---- Install element types decursus $< ----$e"
	@if test ! -d $(tardir_prefix)$(elmdec_dir_alt); then mkdir -p $(tardir_prefix)$(elmdec_dir_alt); fi
	@cp -f $^ $(tardir_prefix)$(elmdec_dir_alt)
#	@chgrp -R intrazis  $(subst $(ELMDECDIR), $(tardir_prefix)$(elmdec_dir_alt)/, $^)
	@if test ! -z $(chgrp_name); then chgrp -R $(chgrp_name) $(subst $(ELMDECDIR), $(tardir_prefix)$(elmdec_dir_alt)/, $^); fi
endif
endif

.elmshow: $(elmshow_files)
ifneq ($(elmshow_dir),)
ifneq ($(elmshow_files),)
	@printf "$c---- Install element types show $< ----$e"
	@if test ! -d $(tardir_prefix)$(elmshow_dir); then mkdir -p $(tardir_prefix)$(elmshow_dir); fi
	@if test ! -d $(tardir_prefix)$(INSTALLDIR); then mkdir -p $(tardir_prefix)$(INSTALLDIR); fi
	@cp -f $^ $(tardir_prefix)$(elmshow_dir)
#	@chgrp -R intrazis  $(subst $(ELMSHOWDIR), $(tardir_prefix)$(elmshow_dir)/, $^)
	@if test ! -z $(chgrp_name); then chgrp -R $(chgrp_name) $(subst $(ELMSHOWDIR), $(tardir_prefix)$(elmshow_dir)/, $^); fi
	@if test ! -z $(chgrp_name); then chgrp -R $(chgrp_name) $(subst $(INSTALLDIR), $(tardir_prefix)$(INSTALLDIR)/, $^); fi
	@echo "" >> $(tardir_prefix)$(INSTALLDIR)elm.sql
#	@chmod 777 $(tardir_prefix)$(INSTALLDIR)
	@chmod 666 $(tardir_prefix)$(INSTALLDIR)elm.sql
	@chgrp -R $(chgrp_name) $(tardir_prefix)$(INSTALLDIR)elm.sql
	$(shell /home/intrazis/tool/status_elementen.sh $(PWD)/$(INSTALLDIR)elm.sql )
endif
endif

elmshow_alt: $(elmshow_files)
ifneq ($(elmshow_dir_alt),)
ifneq ($(elmshow_files),)
	@printf "$c---- Install element types show $< ----$e"
	@if test ! -d $(tardir_prefix)$(elmshow_dir_alt); then mkdir -p $(tardir_prefix)$(elmshow_dir_alt); fi
	@cp -f $^ $(tardir_prefix)$(elmshow_dir_alt)
#	@chgrp -R intrazis  $(subst $(ELMSHOWDIR), $(tardir_prefix)$(elmshow_dir_alt)/, $^)
	@if test ! -z $(chgrp_name); then chgrp -R $(chgrp_name) $(subst $(ELMSHOWDIR), $(tardir_prefix)$(elmshow_dir_alt)/, $^); fi
endif
endif

endif


compile_hdr: $( headers )
	@printf "$c----- headers stylen -----$e"
	iz_pre_commit $(headers)
	@printf "$c----- headers kopieren naar ./hdr_compile en hernoemen -----$e"
	@mkdir -p hdr_compile
	@rm -f hdr_compile/*
	@cp -l $(subst !,/,$(subst !/,!,$(dir $(subst csource,/,$(subst /,!,$(PWD))))))csource/makedir/Makefile.compile_hdr hdr_compile/Makefile
	@cp -l $(wildcard *.hpp) $(wildcard *.h) hdr_compile
	@printf "$c----- headers hernoemen en compileren in ./hdr_compile -----$e"
	@$(MAKE) -C hdr_compile prepare_headers
	@$(MAKE) -C hdr_compile compile
	@printf "$c----- alles ok! ./hdr_compile weggooien  -----$e"
	@rm -rf hdr_compile

clean_hdr_compile:
	@rm -rf hdr_compile

pre_commit: $(headers) $(cfiles)
	@printf "$c---- Style $? ----$e"
	iz_pre_commit $?

%.ii:%.cpp
	@printf "$c---- Preprocess $< ----$e"
	$(CP) -o $@ -E $(HOST_SPECIFIC_DEFINE) $< $(INCLUDE)
