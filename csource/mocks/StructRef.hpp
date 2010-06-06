/**
*** @file
*** @brief "$Id$"
**/

#ifndef __STRUCTREF_HPP__
#define __STRUCTREF_HPP__

#include "BasicTemplate.hpp"

#include <string>

struct StructRef
{
	std::string name;
	std::string refID;
	std::string visibility;

	StructRef( const std::string& pName, const std::string& pRefID, const std::string& pVisibility );

	void outputName( BasicTemplate& pTpl ) const;
};

#endif
