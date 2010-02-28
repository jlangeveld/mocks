/**
*** @file
*** @brief "$Id$"
**/

#ifndef __OTHERFACE_HPP__
#define __OTHERFACE_HPP__

#include <string>

namespace interface
{

struct Otherface
{
	virtual void build( const std::string& pValue ) = 0;
};

}

#endif
