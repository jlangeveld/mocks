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

#include "BasicTemplateImpl.hpp"
#include "Mocker.hpp"
#include "StructList.hpp"
#include "StructParser.hpp"

#include <fstream>
#include <string>

#include <boost/foreach.hpp>

#include <loki/SafeFormat.h>

using Loki::Printf;
using Loki::SPrintf;

using std::ofstream;
using std::pair;
using std::string;

// members

void StructList::collectMockers( StructParser& sp, Structure& mock )
{
	while ( sp.findSection() )
	{
		while ( sp.findMocker() )
		{
			Mocker& theMocker = mock.createMocker( sp.getType(), sp.getName(), sp.getConst() );
			while ( sp.findParameter() )
			{
	 			theMocker.addParam( sp.getType(), sp.getName() );
			}
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

Structure& StructList::getStructure( const std::string& pName )
{
	MapType::iterator pos = parsedStructs.find( pName );
	if ( pos == parsedStructs.end() )
	{
		string message;
		SPrintf( message, "[StructList] Internal error: Couldn't find structure '%s'." ) ( pName );
		throw std::runtime_error( message );
	}
	return pos->second;
}


void StructList::outputAllMockObjects()
{
	BasicTemplateImpl tplObject( "/home/jeroenl/templates/mocks/MockObject.hpp.tpl" );
	BOOST_FOREACH( const StructRef& ref, allMocks )
	{
		string filename;
		SPrintf( filename, ".mocks/%s" ) ( ref.stripGeneratorNamespace() );
		Printf( "Output '%s'.\n" ) ( filename );

		ofstream file( filename.c_str() );
		file << ref.outputMockObject( tplObject.str(), this );
		file.close();
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
	StructRef newRef( pMockName, pRefID );
	allMocks.push_back( newRef );
//	infoList.push( newRef );
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
