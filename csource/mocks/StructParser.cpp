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

#include <string>
#include <utility>

#include <loki/SafeFormat.h>

using Loki::Printf;
using std::make_pair;
using std::string;

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

bool StructParser::currentIsMember()
{
	const string tagname = mCurrent->Value();
	return ( tagname == TAG_MEMBER );
}

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
	while ( pCurrent && ( *( pCurrent->Attribute( ATTRIB_STATIC ) ) == YES || *( pCurrent->Attribute( ATTRIB_VIRTUAL ) ) == VIRTUAL_NON ) );
	return pCurrent;
}

TiXmlElement* StructParser::findNextParent( TiXmlElement* pCurrent )
{
	if ( pCurrent == 0 )
	{
		return mCompoundDefElement->FirstChildElement( TAG_PARENT );
	}

	return pCurrent->NextSiblingElement( TAG_PARENT );
}

bool StructParser::findParent()
{
	mCurrent = this->findNextParent( mCurrent );
	return ( mCurrent != 0 );
}

std::string StructParser::getConst()
{
	const string constValue = mCurrent->Attribute( ATTRIB_CONST.c_str() );
	return ( constValue == "yes" ? "const" : "" );
}

std::string StructParser::getName()
{
	if ( currentIsMember() )
	{
		return this->getTextFor( TAG_NAME );
	}
	return mCurrent->GetText();
}

std::string StructParser::getRefID()
{
	return mCurrent->Attribute( ATTRIB_REFID.c_str() );
}

std::string StructParser::getType()
{
	return this->getTextFor( TAG_TYPE );
}

std::string StructParser::getVisibility()
{
	return mCurrent->Attribute( ATTRIB_VISIBILITY.c_str() );
}
