/**
*** @file
*** @brief "$Id$"
**/

/**
 ** @class      StructList
 **
 **
 **
 ** @par        25-03-2010, jeroenl
 ** Eerste versie.
 ***************/

#include "StructList.hpp"
#include "StructParser.hpp"

#include <string>

#include <loki/SafeFormat.h>

using Loki::Printf;
//using Loki::SPrintf;

using std::pair;
using std::string;

// members

void StructList::collectMockers( StructParser& sp, Structure& mock )
{
	while ( sp.findMocker() )
	{
		Mocker theMocker( sp.getType(), sp.getName(), sp.getConst() );
		while ( sp.findParameter() )
		{
			Mocker::Parameter param( sp.getType(), sp.getName() );
		}
	}
}

void StructList::collectParents( StructParser& sp, Structure& mock )
{
	while ( sp.findParent() )
	{
		const string name = sp.getName();
		const string refid = sp.getRefID();
		const string visibility = sp.getVisibility();

		mock.addParent( name, refid, visibility );
		infoList.push( make_pair( name, refid ) );
	}
}

void StructList::parseAll()
{
	while ( !infoList.empty() )
	{
		const InfoType& info = infoList.front();
		if ( parsedStructs.find( info.first ) == parsedStructs.end() )
		{
			this->parseStruct( info );
		}
		infoList.pop();
		Printf( "%d Structures to go...\n" ) ( infoList.size() );
	}
}

void StructList::parseStruct( const StructList::InfoType& pStructInfo )
{
	Structure& mock = this->storeAndTakeReference( pStructInfo );
	StructParser sp( pStructInfo.second );

	this->collectParents( sp, mock );
	this->collectMockers( sp, mock );
}

void StructList::push( const std::string& pMockName, const std::string& pRefID )
{
	allMocks.push_back( pMockName );
	infoList.push( make_pair( pMockName, pRefID ) );
}

Structure& StructList::storeAndTakeReference( const StructList::InfoType& pStructInfo )
{
	return parsedStructs.insert(
		make_pair(
			pStructInfo.first,
			Structure( pStructInfo.first )
			)
		).first->second;
}
