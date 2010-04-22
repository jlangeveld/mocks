/**
*** @file
*** @brief "$Id$"
**/

#ifndef __TAGNAMES_HPP__
#define __TAGNAMES_HPP__

#include <string>

const std::string MOCK_OBJECT_PREFIX = "mock_generator_settings::";
const std::string XMLPATH = "./.mocks_xml/";

const std::string YES = "yes";
const std::string NO = "no";

const std::string TAG_COMPOUND = "compound";
const std::string TAG_COMPOUNDDEF = "compounddef";
const std::string TAG_MEMBER = "memberdef";
const std::string TAG_MOCK = "innerclass";
const std::string TAG_PARENT = "basecompoundref";
const std::string TAG_SECTION = "sectiondef";

const std::string ATTRIB_CONST = "const";
const std::string ATTRIB_KIND = "kind";
const std::string ATTRIB_NAMESPACE = "namespace";
const std::string ATTRIB_REFID = "refid";
const std::string ATTRIB_STATIC = "static";
const std::string ATTRIB_VIRTUAL = "virt";
const std::string ATTRIB_VISIBILITY = "prot";

const std::string KIND_FUNCTION = "function";
const std::string KIND_NAMESPACE = "namespace";

const std::string VIRTUAL_NON = "non-virtual";
const std::string VIRTUAL_IMPLEMENTED = "virtual";
const std::string VIRTUAL_PURE = "pure-virtual";

#endif
