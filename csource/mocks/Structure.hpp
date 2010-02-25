/**
*** @file
*** @brief "$Id$"
**/

#ifndef __STRUCTURE_HPP__
#define __STRUCTURE_HPP__

#include <string>

class Structure
{
	mutable std::string mType;
	mutable std::string mName;

public:

	const std::string& getType() const;
	const std::string& getName() const;

	void reset( const std::string& pKind );
	void setName( const std::string& pName );
};

#endif
