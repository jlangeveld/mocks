/**
*** @file
*** @brief "$Id$"
**/

/**
 ** @class      SettingsParser
 **
 **
 **
 ** @par        28-02-2010, jeroenl
 ** Eerste versie.
 ***************/

#include "SettingsParser.hpp"
#include "tagnames.hpp"

#include <loki/SafeFormat.h>

using Loki::Printf;

// *tors

/**
 ** Default constructor.
 **
 ** @par        28-02-2010, jeroenl
 ** Eerste versie.
 ***************/
SettingsParser::SettingsParser()
: XmlParser( XMLPATH + "namespacemock__generator__settings.xml" )
{}

/** Default destructor.
 **
 ** @par        28-02-2010, jeroenl
 ** Eerste versie.
 ***************/
SettingsParser::~SettingsParser()
{}

// members

TiXmlElement* SettingsParser::findNamespace( TiXmlElement* element )
{
	while ( element != 0 && NAMESPACE_ATTRIB != element->Attribute( KIND_ATTRIB.c_str() ) )
	{
		element = element->NextSiblingElement( COMPOUND_TAG );
	}

	return element;
}

TiXmlElement* SettingsParser::findNextMock( TiXmlElement* current )
{
	if ( current == 0 )
	{
		current = this->findNamespace( mDoc.RootElement()->FirstChildElement( COMPOUNDDEF_TAG ) );
		return current->FirstChildElement( MOCK_TAG );
	}

	return current->NextSiblingElement( MOCK_TAG );
}

bool SettingsParser::findMock()
{
	mCurrent = this->findNextMock( mCurrent );
	return ( mCurrent != 0 );
}

std::string SettingsParser::mockName() const
{
	return mCurrent->GetText();
}

std::string SettingsParser::mockRefID() const
{
	return mCurrent->Attribute( REFID_ATTRIB.c_str() );
}
