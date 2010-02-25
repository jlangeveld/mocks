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

#include <map>
#include <string>

#include <loki/SafeFormat.h>

using Loki::Printf;
using std::string;

namespace
{

typedef std::map< std::string, std::string > AttributeMap;

struct ElementParser
{

	ElementParser();
	~ElementParser();

};

void parseAttribute( const TiXmlAttribute* pAttribute, AttributeMap& pAttribs )
{
	if ( !pAttribute )
	{
		return;
	}
	pAttribs[ pAttribute->Name() ] = pAttribute->Value();
	parseAttribute( pAttribute->Next(), pAttribs );
}

}

// *tors

/**
 ** Default constructor.
 **
 ** @par        23-02-2010, j.langeveld
 ** Eerste versie.
 ***************/
IndexParser::IndexParser()
{
}

/** Default destructor.
 **
 ** @par        23-02-2010, j.langeveld
 ** Eerste versie.
 ***************/
IndexParser::~IndexParser()
{}

// members

void IndexParser::enterElement( const TiXmlElement& pElement, const TiXmlAttribute* pAttribute )
{
	const string elemValue = pElement.Value();
}

void IndexParser::parseDocument( TiXmlDocument& pIndex )
{
	pIndex.Accept( this );
}

void IndexParser::parseCompoundElement( const TiXmlElement& pElement, const TiXmlAttribute* pAttribute )
{
	AttributeMap attribs;
	parseAttribute( pAttribute, attribs );
	mCurrentStructure.reset( attribs[ "kind" ] );
}

void IndexParser::parseNameElement( const TiXmlElement& pElement, const TiXmlAttribute* pAttribute )
{
// 	mCurrentStructure.setName(  )
}

bool IndexParser::VisitEnter( const TiXmlElement& pElement, const TiXmlAttribute* pAttribute )
{
	this->enterElement( pElement, pAttribute );

	const string elemValue = pElement.Value();

// 	parseCompoundElement( pElement, pAttribute );
// 	parseNameElement( pElement, pAttribute );

	if ( !mCurrentStructure.getType().empty() )
	{
		Printf( "--- %s %s ---" ) ( mCurrentStructure.getType() ) ( mCurrentStructure.getName() );
	}
	return mLister.VisitEnter( pElement, pAttribute );
}

bool IndexParser::VisitExit( const TiXmlElement& pElement )
{
	if ( !mCurrentStructure.getType().empty() )
	{
		Printf( "--- %s %s ---" ) ( mCurrentStructure.getType() ) ( mCurrentStructure.getName() );
		mParsedStructures.push_back( mCurrentStructure );
	}
	return mLister.VisitExit( pElement );
}

bool IndexParser::Visit( const TiXmlText& pText )
{
	return mLister.Visit( pText );
}
