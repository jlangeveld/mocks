/**
*** @file
*** @brief "$Id$"
**/

#include "IndexParser.hpp"
#include "Interface.hpp"
#include "Otherface.hpp"
#include "StructureParser.hpp"

#include <string>

#include <boost/foreach.hpp>
#include <boost/algorithm/string/join.hpp>
#include <loki/SafeFormat.h>
#include <tinyxml/tinyxml.h>

using Loki::Printf;
using std::string;

void printValues( const std::vector< std::string >& pValues )
{
	BOOST_FOREACH( string i, pValues )
	{
		Printf( " %s\n" ) ( i );
	}
}

void parseStructure( const Structure& pStruct )
{
	StructureParser sp( pStruct );
	sp.parseStruct();
	Printf( " virtuals: '%s'\n" ) ( boost::join( sp.virtualMembers, "," ) );
}

int main( int argc, char** argv )
{
	typedef std::vector< Structure >::const_iterator Iter;

	TiXmlDocument doc( "./xml/index.xml" );
	doc.LoadFile();

	IndexParser parser;
	Structure theStruct = parser.findStructure( doc );
	while ( theStruct.element )
	{
		Printf( "type %s name %s;\n" ) ( theStruct.type ) ( theStruct.name );
		parseStructure( theStruct );
		theStruct = parser.findStructure( theStruct );
	}
}
