######################################
# makefile for: Accorderingsoverzicht
######################################

# zorgt dat de macro's CVSDIR, MAKEDIR, BASEDIR en testlibfile bekend zijn.
SPACE=$(subst x, ,x)
TMPHOME=/$(subst $(SPACE),/,$(strip $(subst /, ,$(HOME))))
include $(TMPHOME)/$(word 1, $(subst /, , $(subst $(TMPHOME)/,,$(PWD))))/csource/makedir/basedirinc.mak

outfile=testmocks

# hebben we nog extra libs nodig ? geef dan hier op
# extra_libraries_pre=
# extra_libraries=
# extra_defines=
#override_libraries=
no_libraries=a

#majorversion=1
#minorversion=0

include $(MAKEDIR)/izcgiinc.mak

