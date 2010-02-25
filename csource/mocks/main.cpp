/**
*** @file
*** @brief "$Id$"
**/

#include "IndexParser.hpp"
#include "Interface.hpp"
#include "Otherface.hpp"

#include <string>

#include <loki/SafeFormat.h>
#include <tinyxml/tinyxml.h>

using Loki::Printf;
using std::string;

int main( int argc, char** argv )
{
	typedef std::vector< Structure >::const_iterator Iter;

	TiXmlDocument doc( "./xml/index.xml" );
	doc.LoadFile();

	IndexParser parser;
	parser.parseDocument( doc );

	Printf( "\nOverzicht structuren:\n" );
	Iter end = parser.mParsedStructures.end();
	for ( Iter i = parser.mParsedStructures.begin(); i != end; ++i )
	{
		Printf( "%s %s;\n" ) ( i->getType() ) ( i->getName() );
	}
}
