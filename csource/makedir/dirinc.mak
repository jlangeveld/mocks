ifeq ($(CVSDIR),)
SPACE=$(subst x, ,x)
TMPHOME=/$(subst $(SPACE),/,$(strip $(subst /, ,$(HOME))))
include $(TMPHOME)/$(word 1, $(subst /, , $(subst $(TMPHOME)/,,$(PWD))))/csource/makedir/basedirinc.mak
endif

ifneq ($(MAKECMDGOALS),)
	TGT = $(MAKECMDGOALS)
else
	TGT = TGT
endif

include $(MAKEDIR)/izcolors.mak

$(TGT): $(makedirs)
	@echo

# Start make recursief in de genoemde subdirectory, update CURRENT_MAKE_DIR op basis daarvan;
# maar sla elke naam over de verwijst naar een directory die niet bestaat.
%: SUBDIRNAME=$(patsubst %.mak,%,$@)
%:
	@if test -d $(SUBDIRNAME) ; then \
		$(MAKE) $(MAKECMDGOALS) -C $(SUBDIRNAME) $(MFLAGS); \
	else \
		echo "$l---- Skipping $(SUBDIRNAME) ----$e"; \
	fi

