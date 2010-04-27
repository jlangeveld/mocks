/**
*** @file
*** @brief "$Id$"
**/

/**
*** @file
*** @brief "$Id$"
**/

#ifndef __MOCKER_HPP__
#define __MOCKER_HPP__

#include <string>

class Mocker
{

public:

	Mocker( const std::string& pType, const std::string& pName, const std::string& pConst );
	~Mocker();

protected:
private:
	const std::string mType;
	const std::string mName;
	const std::string mConst;

};

#endif
