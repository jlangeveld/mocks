/**
*** @file
*** @brief "$Id$"
**/

#ifndef __OTHERFACE_HPP__
#define __OTHERFACE_HPP__

#include <string>

namespace interface
{

class Otherface
{
public:
//	virtual ~Otherface() = 0;
	virtual void build( const std::string& pValue ) = 0;

protected:
	virtual int count( const std::string& pName, bool& pMulti ) = 0;

};

}

#endif
