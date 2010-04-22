/**
*** @file
*** @brief "$Id$"
**/

#ifndef __PARENT_HPP__
#define __PARENT_HPP__

#include <string>

struct Parent
{
	std::string name;
	std::string refID;
	std::string visibility;

	Parent( const std::string& pName, const std::string& pRefID, const std::string& pVisibility );
};

#endif
