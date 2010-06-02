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

#include <boost/algorithm/string/replace.hpp>
#include <boost/foreach.hpp>

#include <loki/SafeFormat.h>

using Loki::Printf;
using Loki::SPrintf;

using boost::replace_first_copy;
using std::ofstream;
using std::pair;
using std::string;

namespace
{

std::string stripGeneratorNamespace( const std::string& pName )
{
	return replace_first_copy( pName, "mock_generator_settings::", "" );
}

}

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
	BOOST_FOREACH( string name, allMocks )
	{
		string filename;
		SPrintf( filename, ".mocks/%s" ) ( stripGeneratorNamespace( name ) );
		Printf( "Output '%s'.\n" ) ( filename );

		ofstream file( filename.c_str() );
		file << this->outputMockObject( tplObject.str(), name );
		file.close();
	}
}

std::string StructList::outputMockObject( const std::string& pTpl, const std::string& pName )
{
	BasicTemplateImpl tpl;
	tpl.setStr( pTpl );

	Structure& mock = this->getStructure( pName );
	mock.outputName( tpl );
	mock.outputParents( tpl );
	mock.outputMockers( tpl );

	return tpl.str();
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
