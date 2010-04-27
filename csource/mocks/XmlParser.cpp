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
: mCurrent( 0 )
{}

XmlParser::XmlParser( const std::string& pFilename )
: mDoc( pFilename )
, mCurrent( 0 )
{
	Printf( "+ Parsing file '%s'.\n" ) ( pFilename );
	mDoc.LoadFile();
	if ( mDoc.Error() )
	{
		Printf( "Error while loading the document: '%s'.\n" ) ( mDoc.ErrorDesc() );
	}
}

// members

std::string getTextFor( const std::string& pTagname )
{
	return this->getTextFor( pTagname, mCurrent );
}

std::string getTextFor( const std::string& pTagname, TiXmlElement* pElement )
{
	TiXmlElement *nameElem = pElement->FirstChildElement( pTagname );
	return nameElem->GetText();
}

std::string XmlParser::findName( TiXmlElement* pElement )
{
	return getTextFor( TAG_NAME, pElement );
}
