################################
# GCC version
################################
CP = g++
LINK = g++
#CP = nice -5 g++44
#LINK = nice -5 g++44

ifeq ($(override_path_includes),)
path_includes = -I./ -I$(BUILDREF)/includecc/ -I/usr/include/mysql/ $(loki_include) $(boost_include) $(extra_includes) $(botan_include) $(mockpp_include) $(tinyxml_include) $(izsane_include) $(curl_include) $(cgicc_include)
else
path_includes = $(override_path_includes)
endif

# Vlaggetje -Os compileert sneller dan -O2 en levert een kleinere binary op.
# -O3 levert een enorme vertraging op en de binaries zijn bijna 2 x zo groot.
COMP_FLAGS = $(extra_defines) $(OPTIMIZE) -c -felide-constructors -Wall $(DEBUGFLAGS) $(PROFILEFLAG) $(extra_compiler_flags)
LINK_FLAGS = $(LINKSTRIP) $(extra_linker_flags)

ifeq ($(no_libraries),)
ifeq ($(override_path_libraries),)
path_libraries = $(BASEDIR)/libcc /usr/local/lib /usr/lib64/mysql
else
path_libraries = $(override_path_libraries)
endif
else
path_libraries=
endif

ifeq ($(no_libraries),)
ifeq ($(override_libraries),)
libraries = -lHandtekening -lHttp -lMyTest -lIzToolbox -lIzCgi -lIzCGIBase -lIzKoppelBase -lTemplate -lIzCore -lCGIBase -lMySQL -lActionFactory -lIzActionFactory -lMatrix -lXSort -lStateMachine -lMail -lsocket -lNaslag $(libCrypt) -lLockedLog -lFileManager -lLoglib -lIzInit -lMapEx -lXorB64 -lIniFile -lStringEx -lToolbox -lIzCommandline -lCmdLine $(boost_lib) $(botan_lib) $(mockpp_lib) $(tinyxml_lib) $(loki_lib) $(curl_lib) $(cgicc_lib) -lmysqlclient
else
libraries = $(override_libraries)
endif
else
libraries=
endif

################################
# BOOST version
################################
ifeq ("$(IZ_BOOST_VERSION)","")
IZ_BOOST_VERSION=1_42
endif

# alleen de gebruikte libs worden meegelinkt; er zijn er nog (veel) meer...
boost_lib=-lboost_filesystem-$(IZ_BOOST_VERSION) -lboost_regex-$(IZ_BOOST_VERSION) -lboost_system-$(IZ_BOOST_VERSION)
boost_include=-I/usr/local/include/boost-$(IZ_BOOST_VERSION)

#####
# BOTAN version
#####
ifeq ("$(IZ_BOTAN_VERSION)","")
#IZ_BOTAN_VERSION=OFF
IZ_BOTAN_VERSION=1_8_8
endif
ifeq ("$(IZ_BOTAN_VERSION)","OFF")
libCrypt=
botan_include=
botan_lib=
else
libCrypt=-lCrypt
botan_include=-I/usr/local/include/botan-$(IZ_BOTAN_VERSION)
botan_lib=-lbotan-$(IZ_BOTAN_VERSION)
endif

#####
# CGICC version
#####
ifeq ("$(IZ_CGICC_VERSION)","")
IZ_CGICC_VERSION=3_2_9
endif
cgicc_include=-I/usr/local/include/cgicc-$(IZ_CGICC_VERSION)
cgicc_lib=-lcgicc-$(IZ_CGICC_VERSION)

#####
# CURL version
#####
ifeq ("$(IZ_CURL_VERSION)","")
IZ_CURL_VERSION=7_19_7
endif
curl_include=-I/usr/local/include/curl-$(IZ_CURL_VERSION)
curl_lib=-lcurl-$(IZ_CURL_VERSION)

#####
# LOKI version
#####
ifeq ("$(IZ_LOKI_VERSION)","")
IZ_LOKI_VERSION=0_1_7
endif
loki_include=-I/usr/local/include/loki-$(IZ_LOKI_VERSION)
loki_lib=-lloki-$(IZ_LOKI_VERSION)

#####
# MOCKPP version
#####
ifeq ("$(IZ_MOCKPP_VERSION)","")
IZ_MOCKPP_VERSION=1_16_6
endif
mockpp_include=-I/usr/local/include/mockpp-$(IZ_MOCKPP_VERSION)
ifneq ("$(USE_MOCKPP)","")
mockpp_lib=-lmockpp-$(IZ_MOCKPP_VERSION)
else
mockpp_lib=
endif

#####
# TinyXML
#####
ifeq ("$(IZ_TINYXML_VERSION)","")
IZ_TINYXML_VERSION=2_5_3
endif
tinyxml_include=-I/usr/local/include/tinyxml-$(IZ_TINYXML_VERSION)/
tinyxml_lib=-ltinyxml-$(IZ_TINYXML_VERSION)

#####
# IzSane (== sane met IZ-patches)
#####
ifeq ("$(IZ_SANE_VERSION)","")
IZ_SANE_VERSION=1_0_20
endif
izsane_include=-I/usr/local/include/izsane-$(IZ_SANE_VERSION)/
izsane_lib=-lizsane-$(IZ_SANE_VERSION)

#####
# OpenLDAP
#####
ifeq ("$(IZ_OPENLDAP_VERSION)","")
IZ_OPENLDAP_VERSION=2_4_19
endif
izopenldap_include=-I/usr/local/include/open-ldap-$(IZ_OPENLDAP_VERSION)/
izopenldap_lib=-lldap-$(IZ_OPENLDAP_VERSION) -lldap_r-$(IZ_OPENLDAP_VERSION) -llber-$(IZ_OPENLDAP_VERSION)
