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

all: mocks $(localoutfile)

updir:
	$(MAKE) -C ..

include $(MAKEDIR)/izcgiinc.mak

MOCKDIR=.mocks
MOCKDIR_DOXY_SRC=.mocks_doxy
MOCKDIR_DOXY_DEST=.mocks_xml

mock_files := $(shell grep -l mock_generator_settings *.?pp)

ifneq ($(mock_files),)
mocks: mocks_doxy mocks_xml mocks_build mocks_clean
else
mocks:
endif

mocks_clean:
	rm -rf $(MOCKDIR)
	rm -rf $(MOCKDIR_DOXY_SRC)
	rm -rf $(MOCKDIR_DOXY_DEST)

mocks_mkdir:
	mkdir -p $(MOCKDIR)
	mkdir -p $(MOCKDIR_DOXY_SRC)

mocks_doxy: updir mocks_clean mocks_mkdir
	@echo "Generate dependencies for $(mock_files)"
	$(CP) -D MOCK_RUN -M -MM $(mock_files) $(INCLUDE) | ../obj/mocks --link

mocks_xml:
	doxygen MOCKS.doxy

mocks_build:
	../obj/mocks
