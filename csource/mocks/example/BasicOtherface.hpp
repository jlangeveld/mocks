/**
*** @file
*** @brief "$Id$"
**/

#ifndef __BASICOTHERFACE_HPP__
#define __BASICOTHERFACE_HPP__

#include "interface/Otherface.hpp"
#include <string>

class BasicOtherface
: public interface::Otherface
{

public:

	static size_t GetCount();

	BasicOtherface();
	~BasicOtherface();

	bool go( const std::string& pValue );
	virtual void build( const std::string& pValue );

protected:
private:

};

#endif
