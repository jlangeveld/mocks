/**
*** @file
*** @brief "$Id$"
**/

/**
 ** @class      XmlParser
 **
 **
 **
 ** @par        27-02-2010, jeroenl
 ** Eerste versie.
 ***************/

#include "XmlParser.hpp"

#include <loki/SafeFormat.h>
#include <tinyxml/tinyxml.h>

using Loki::Printf;

// * tors

XmlParser::XmlParser()
{}

XmlParser::XmlParser( const std::string& pFilename )
: mDoc( pFilename )
{
	mDoc.LoadFile();
	if ( mDoc.Error() )
	{
		Printf( "Fout bij het laden van het document: '%s'" ) ( mDoc.ErrorDesc() );
	}
}

// members

std::string XmlParser::findName( TiXmlElement* pElement )
{
	TiXmlElement *nameElem = pElement->FirstChildElement( "name" );
	return nameElem->GetText();
}
