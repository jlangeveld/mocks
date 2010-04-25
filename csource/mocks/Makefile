######################################
# makefile for: Accorderingsoverzicht
######################################

# zorgt dat de macro's CVSDIR, MAKEDIR, BASEDIR en testlibfile bekend zijn.
SPACE=$(subst x, ,x)
TMPHOME=/$(subst $(SPACE),/,$(strip $(subst /, ,$(HOME))))
include $(TMPHOME)/$(word 1, $(subst /, , $(subst $(TMPHOME)/,,$(PWD))))/csource/makedir/basedirinc.mak

outfile=mocks
final_target=~/bin/mocks

# hebben we nog extra libs nodig ? geef dan hier op
# extra_libraries_pre=
# extra_libraries=
# extra_defines=
extra_libraries= -lboost_filesystem-$(IZ_BOOST_VERSION) -lboost_program_options-$(IZ_BOOST_VERSION) -lboost_system-$(IZ_BOOST_VERSION)
override_libraries=-ltinyxml-2_5_3 -lloki-0_1_7

majorversion=1
minorversion=0

include $(MAKEDIR)/izcgiinc.mak
