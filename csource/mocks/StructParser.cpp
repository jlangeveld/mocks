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

namespace
{

bool isStaticOrNonVirtual( TiXmlElement* pCurrent )
{
	return ( pCurrent &&
		( *( pCurrent->Attribute( ATTRIB_STATIC ) ) == YES
		|| *( pCurrent->Attribute( ATTRIB_VIRTUAL ) ) == VIRTUAL_NON ) );
}

}

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
, mParamElement( 0 )
, mSectionElement( 0 )
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

bool StructParser::parsingParam()
{
	return ( mParamElement != 0 );
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
			? mSectionElement->FirstChildElement( TAG_MEMBER )
			: pCurrent->NextSiblingElement( TAG_MEMBER ) );
	}
	while ( isStaticOrNonVirtual( pCurrent ) );
	return pCurrent;
}

TiXmlElement* StructParser::findNextParameter( TiXmlElement* pCurrent )
{
	return ( pCurrent == 0
		? mCurrent->FirstChildElement( TAG_PARAM )
		: pCurrent->NextSiblingElement( TAG_PARAM ) );
}

TiXmlElement* StructParser::findNextParent( TiXmlElement* pCurrent )
{
	return ( pCurrent == 0
		? mCompoundDefElement->FirstChildElement( TAG_PARENT )
		: pCurrent->NextSiblingElement( TAG_PARENT ) );
}

TiXmlElement* StructParser::findNextSection( TiXmlElement* pCurrent )
{
	return ( pCurrent == 0
		? mCompoundDefElement->FirstChildElement( TAG_SECTION )
		: pCurrent->NextSiblingElement( TAG_SECTION ) );
}

bool StructParser::findParameter()
{
	mParamElement = this->findNextParameter( mParamElement );
	return ( mParamElement != 0 );
}

bool StructParser::findParent()
{
	mCurrent = this->findNextParent( mCurrent );
	return ( mCurrent != 0 );
}

bool StructParser::findSection()
{
	mSectionElement = this->findNextSection( mSectionElement );
	return ( mSectionElement != 0 );
}

std::string StructParser::getArgList()
{
	return this->getTextFor( TAG_ARGLIST );
}

std::string StructParser::getConst()
{
	const string constValue = mCurrent->Attribute( ATTRIB_CONST.c_str() );
	return ( constValue == "yes" ? "const" : "" );
}

std::string StructParser::getKind()
{
	return ( mSectionElement == 0
		? mCurrent->Attribute( ATTRIB_KIND.c_str() )
		: mSectionElement->Attribute( ATTRIB_KIND.c_str() ) );
}

std::string StructParser::getName()
{
	if ( parsingParam() )
	{
		return this->getTextFor( TAG_PARAMNAME, mParamElement );
	}
	else if ( currentIsMember() )
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
	if ( parsingParam() )
	{
		return this->getTextFor( TAG_TYPE, mParamElement );
	}
	return this->getTextFor( TAG_TYPE );
}

std::string StructParser::getVisibility()
{
	return mCurrent->Attribute( ATTRIB_VISIBILITY.c_str() );
}
