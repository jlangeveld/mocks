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
	class Parameter
	{
	public:
		Parameter( const std::string& pType, const std::string& pName );

	protected:
	private:
		std::string mType;
		std::string mName;
	};


public:
	Mocker( const std::string& pType, const std::string& pName, const std::string& pConst );

	void addParam( const std::string& pType, const std::string& pName );

protected:
private:
	std::string mType;
	std::string mName;
	std::string mConst;
	std::vector< Mocker::Parameter > mParameters;

};

#endif
