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
#include <vector>

class Mocker
{
	struct Parameter
	{
		std::string type;
		std::string name;

		Parameter( const std::string& pType, const std::string& pName );
	};


public:
	Mocker( const std::string& pType, const std::string& pName, const std::string& pConst );

	void addParam( const std::string& pType, const std::string& pName );

protected:
private:
	const std::string mType;
	const std::string mName;
	const std::string mConst;
	std::vector< Mocker::Parameter > mParameters;

};

#endif
