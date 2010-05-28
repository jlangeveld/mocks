/**
*** @file
*** @brief "$Id$"
**/

#ifndef __TOSTR_HPP__
#define __TOSTR_HPP__

#include <sstream>

template <typename T>
std::string ToStr( T p )
{
	std::ostringstream ost;
	ost << p;
	return ost.str();
}

#endif
