# Definieer de huidige cvs-directory. Dit is altijd een directe subdir van $(HOME).

ifeq ($(SPACE),)
	SPACE=$(subst x, ,x)
endif

BUILD_DIR_NAME=build

SPACED_PWD=$(strip $(subst /, , $(PWD)))
SPACED_HOME=$(strip $(subst /, ,$(HOME)))
WORDS_IN_CVSDIR=$(words $(SPACED_HOME) extra)

ifeq ($(CVSDIR),)
	CVSDIR=/$(subst $(SPACE),/,$(wordlist 1,$(WORDS_IN_CVSDIR),$(SPACED_PWD)))
endif

# Definieer de directory waar alle aanvullende make-includes staan.
ifeq ($(MAKEDIR),)
	MAKEDIR=$(CVSDIR)/csource/makedir
endif

# Definieer de directory waar de headers en libs geplaatst worden.
ifeq ($(BASEDIR),)
	BASEDIR=$(CVSDIR)/$(BUILD_DIR_NAME)
endif

ifeq ($(BUILDREF),)
	SPACED_CURDIR=$(subst /, , $(CURDIR))
	FIRST_WORD_OF_BUILDREF=$(words $(SPACED_HOME) extra extra)

	CD_WORDS=$(wordlist $(FIRST_WORD_OF_BUILDREF), $(words $(SPACED_CURDIR)), $(SPACED_CURDIR))
	CD_PUNTJES=$(patsubst %,..,$(CD_WORDS))
	BUILDREF=$(subst $(SPACE),/,$(CD_PUNTJES) $(BUILD_DIR_NAME))
endif

# Voor test-driven-development: definieer de naam van de applicatie-lib.
testlibfile=$(OBJDIR)libTest.a
