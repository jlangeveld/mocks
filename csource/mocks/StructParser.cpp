/**
*** @file
*** @brief "$Id$"
**/

/**
 ** @class      StructParser
 **
 **
 **
 ** @par        23-03-2010, jeroenl
 ** Eerste versie.
 ***************/

#include "StructParser.hpp"
#include "tagnames.hpp"

#include <utility>

#include <loki/SafeFormat.h>

using Loki::Printf;
using std::make_pair;

// *tors

/**
 ** Default constructor.
 **
 ** @par        23-03-2010, jeroenl
 ** Eerste versie.
 ***************/
StructParser::StructParser( const std::string& pRefID )
: XmlParser( XMLPATH + pRefID + ".xml" )
, mCompoundDefElement( mDoc.RootElement()->FirstChildElement() )
{}

/** Default destructor.
 **
 ** @par        23-03-2010, jeroenl
 ** Eerste versie.
 ***************/
StructParser::~StructParser()
{}

// members

bool StructParser::findMocker()
{
	mCurrent = this->findNextMocker( mCurrent );
	return ( mCurrent != 0 );
}

TiXmlElement* StructParser::findNextMocker( TiXmlElement* pCurrent )
{
	do
	{
		pCurrent = ( pCurrent == 0
			? mCompoundDefElement->FirstChildElement( TAG_MEMBER )
			: pCurrent->NextSiblingElement( TAG_MEMBER ) );
	}
	while ( pCurrent && ( pCurrent->Attribute( ATTRIB_STATIC ) == YES || pCurrent->Attribute( ATTRIB_VIRTUAL ) == VIRTUAL_NON ) );
	return pCurrent;
}

TiXmlElement* StructParser::findNextParent( TiXmlElement* pCurrent )
{
	if ( pCurrent == 0 )
	{
		return mCompoundDefElement->FirstChildElement( PARENT_TAG );
	}

	return pCurrent->NextSiblingElement( PARENT_TAG );
}

bool StructParser::findParent()
{
	mCurrent = this->findNextParent( mCurrent );
	return ( mCurrent != 0 );
}

std::string StructParser::getName()
{
	return mCurrent->GetText();
}

std::string StructParser::getRefID()
{
	return mCurrent->Attribute( REFID_ATTRIB.c_str() );
}

std::string StructParser::getVisibility()
{
	return mCurrent->Attribute( VISIBILITY_ATTRIB.c_str() );
}
