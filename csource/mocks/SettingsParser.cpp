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
	while ( element != 0 && KIND_NAMESPACE != element->Attribute( ATTRIB_KIND.c_str() ) )
	{
		element = element->NextSiblingElement( TAG_COMPOUND );
	}

	return element;
}

TiXmlElement* SettingsParser::findNextMock( TiXmlElement* current )
{
	if ( current == 0 )
	{
		current = this->findNamespace( mDoc.RootElement()->FirstChildElement( TAG_COMPOUNDDEF ) );
		return current->FirstChildElement( TAG_MOCK );
	}

	return current->NextSiblingElement( TAG_MOCK );
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
	return mCurrent->Attribute( ATTRIB_REFID.c_str() );
}
