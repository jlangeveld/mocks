/**
*** @file
*** @brief "$Id$"
**/

#ifndef __STRUCTURE_HPP__
#define __STRUCTURE_HPP__

// #include "Mocker.hpp"
#include "Parent.hpp"

#include <string>
#include <vector>

class Structure
{
public:
	Structure( const std::string& pName );

	void addParent( const std::string& pName, const std::string& pRefID, const std::string& pVisibility );

private:
	const std::string mName;
	std::vector< Parent > mParentRefIDs;

};

#endif
