/**
*** @file
*** @brief "$Id$"
**/

#ifndef __STRUCTLIST_HPP__
#define __STRUCTLIST_HPP__

#include "./Structure.hpp"

#include <map>
#include <queue>
#include <string>
#include <utility>
#include <vector>

class StructParser;

class StructList
{
public:
	typedef std::map< std::string, Structure > MapType;
	typedef std::pair< std::string, std::string > InfoType;

	void parseAll();
	void push( const std::string& pMockName, const std::string& pRefID );

private:
	MapType parsedStructs;
	std::queue< InfoType > infoList;
	std::vector< std::string > allMocks;

	void collectMockers( StructParser& sp, Structure& mock );
	void collectParents( StructParser& sp, Structure& mock );
	void parseStruct( const InfoType& pStructInfo );
	Structure& storeAndTakeReference( const InfoType& pStructInfo );
};

#endif
