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

const std::string COMPOUND_TAG = "compound";
const std::string COMPOUNDDEF_TAG = "compounddef";
const std::string TAG_MEMBER = "memberdef";
const std::string MOCK_TAG = "innerclass";
const std::string PARENT_TAG = "basecompoundref";
const std::string SECTION_TAG = "sectiondef";

const std::string ATTRIB_CONST = "const";
const std::string KIND_ATTRIB = "kind";
const std::string NAMESPACE_ATTRIB = "namespace";
const std::string REFID_ATTRIB = "refid";
const std::string ATTRIB_STATIC = "static";
const std::string ATTRIB_VIRTUAL = "virt";
const std::string ATTRIB_VISIBILITY = "prot";

const std::string KIND_FUNCTION = "function";
const std::string KIND_NAMESPACE = "namespace";

const std::string VIRTUAL_NON = "non-virtual";
const std::string VIRTUAL_IMPLEMENTED = "virtual";
const std::string VIRTUAL_PURE = "pure-virtual";

#endif
