/**
*** @file
*** @brief "$Id$"
**/

#ifndef __STRUCTURE_HPP__
#define __STRUCTURE_HPP__

#include <string>

class TiXmlElement;

struct Structure
{
	TiXmlElement* element;
	std::string type;
	std::string name;

	Structure();
	Structure( TiXmlElement* pElement, const std::string& pType, const std::string& pName );
};

#endif
