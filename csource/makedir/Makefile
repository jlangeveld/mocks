######################################
# voorbeeld makefile
######################################

# zorgt dat de macro's CVSDIR, MAKEDIR, BASEDIR en testlibfile bekend zijn.
SPACE=$(subst x, ,x)
TMPHOME=/$(subst $(SPACE),/,$(strip $(subst /, ,$(HOME))))
include $(TMPHOME)/$(word 1, $(subst /, , $(subst $(TMPHOME)/,,$(PWD))))/csource/makedir/basedirinc.mak

@echo test

# geef locale cgi naam op
outfile=...

# geef uiteindelijke doel bestand van cgi
final_target=/home/httpd/cgi-bin/...

# en evt. een alternatief
final_target_alt=...

# geef locatie voor templates op
tpl_dir=/home/httpd/html/templates/...

# en evt. een alternatief
tpl_dir_alt=...

# geef locatie voor images op
img_dir=/home/httpd/html/images/...

# en evt. een alternatief
img_dir_alt=...

xml_dir=
xml_dir_alt=
xsd_dir=
xsd_dir_alt=

elmstd_dir=
elmxml_dir=
elmimg_dir=
elmdec_dir=
elmshow_dir=

# de locatie voor de scripts
script_dir=/home/httpd/javascript/...

# en evt. een alternatief
script_dir_alt=...

# de locatie voor de cron-scripts
cron_dir=/home/intrazis/cron/...

# en evt. een alternatief
cron_dir_alt=...

# de locatie voor de stylesheets
style_dir=/home/httpd/style/...

# en evt. een alternatief
style_dir_alt=...

# wil je zelf het pad naar de libs opgegeven ? doe dat dan hier
override_path_libraries=

# hebben we libs op een ander pad die voorrang krijgen ? geef dan hier op
extra_libraries_pre=

# hebben we additionele libs op een ander pad ? geef dan hier op
extra_libraries=

# wil je zelf de libs opgegeven ? doe dat dan hier
override_libraries=

# hebben we extra libs die voor de standaard libs moeten worden gelinkt ? geef dan hier op
extra_libraries_pre=

# hebben we extra libs die na de standaard libs moeten worden gelinkt ? geef dan hier op
extra_libraries=

# wil je zelf het pad naar de includes opgegeven ? doe dat dan hier
override_includes=

# hebben we includes op een ander pad die voorrang krijgen ? geef dan hier op
extra_includes_pre=

# hebben we additionele includes op een ander pad ? geef dan hier op
extra_includes=

# moeten we nog extra compiler flags opgegeven ? doe dat dan hier
extra_compiler_flags=

majorversion=1
minorversion=0

include $(subst !,/,$(subst !/,!,$(dir $(subst csource,/,$(subst /,!,$(PWD))))))csource/makedir/izcgiinc.mak
