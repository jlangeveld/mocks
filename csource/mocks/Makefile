######################################
# makefile for: Accorderingsoverzicht
######################################

# zorgt dat de macro's CVSDIR, MAKEDIR, BASEDIR en testlibfile bekend zijn.
SPACE=$(subst x, ,x)
TMPHOME=/$(subst $(SPACE),/,$(strip $(subst /, ,$(HOME))))
include $(TMPHOME)/$(word 1, $(subst /, , $(subst $(TMPHOME)/,,$(PWD))))/csource/makedir/basedirinc.mak

outfile=mocks
final_target=./mocks

# hebben we nog extra libs nodig ? geef dan hier op
# extra_libraries_pre=
# extra_libraries=
# extra_defines=
override_libraries=-ltinyxml-2_5_3 -lloki-0_1_7

majorversion=1
minorversion=0

include $(MAKEDIR)/izcgiinc.mak

MOCKDIR=.mocks
MOCK_FILES = $(wildcard Mock*.hpp)
MOCKS=$(addprefix $(MOCKDIR)/,$(patsubst Mock%.hpp,%.hpp,$(MOCK_FILES)))


#mocks: $(MOCKDIR) $(MOCKDIR)/Interface.hpp mock_xml
mocks: clean_mocks $(MOCKDIR) $(MOCKS) mock_xml

clean_mocks:
	rm -rf $(MOCKDIR) mock_xml

mock_xml:
	doxygen

$(MOCKDIR):
	mkdir -p $(MOCKDIR)

$(MOCKDIR)/%.hpp:Mock%.hpp
	gcc -E -P $< -o $@