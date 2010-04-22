/**
*** @file
*** @brief "$Id$"
**/

/**
 ** @class      IndexParser
 **
 **
 **
 ** @par        23-02-2010, j.langeveld
 ** Eerste versie.
 ***************/

#include "IndexParser.hpp"
#include "tagnames.hpp"

#include <map>
#include <string>

#include <loki/SafeFormat.h>
#include <tinyxml/tinyxml.h>

using Loki::Printf;
using std::string;

// *tors

/**
 ** Default constructor.
 **
 ** @par        23-02-2010, j.langeveld
 ** Eerste versie.
 ***************/
IndexParser::IndexParser()
{}

/** Default destructor.
 **
 ** @par        23-02-2010, j.langeveld
 ** Eerste versie.
 ***************/
IndexParser::~IndexParser()
{}

// members

Structure IndexParser::findNextStructure( TiXmlElement* pElement )
{
	if ( pElement == 0 )
	{
		return Structure();
	}

	const string kind = pElement->Attribute( "kind" );
	if ( kind != "class" && kind != "struct" )
	{
		const string name = this->findName( pElement );
		mIgnorelist.push_back( name );
		Printf( "Ignoring %s '%s'\n" ) ( kind ) ( name );
		return this->findNextStructure( pElement->NextSiblingElement( COMPOUND_TAG ) );
	}

	const string structName = this->findName( pElement );
	return Structure( pElement->NextSiblingElement( COMPOUND_TAG ), kind, structName );
}

Structure IndexParser::findStructure( TiXmlDocument& pIndex )
{
	TiXmlElement* elem = pIndex.RootElement()->FirstChildElement( COMPOUND_TAG );
	return findNextStructure( elem );
}

Structure IndexParser::findStructure( const Structure& pPreviousStructure )
{
	return this->findNextStructure( pPreviousStructure.element );
}
