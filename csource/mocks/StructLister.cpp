/**
*** @file
*** @brief "$Id$"
**/

#include "StructLister.hpp"

#include <loki/SafeFormat.h>

using Loki::Printf;
using std::string;

// *tors

StructLister::StructLister()
: mIndentSize( 0 )
{}

StructLister::~StructLister()
{}

// members

bool StructLister::containsSimpleText( const TiXmlElement& pElement )
{
	return ( pElement.FirstChild()->ToText() && pElement.LastChild() == pElement.FirstChild() );
}

void StructLister::dedent()
{
	--mIndentSize;
	mIndentStr = string( mIndentSize, ' ' );
}

void StructLister::indent()
{
	++mIndentSize;
	mIndentStr = string( mIndentSize, ' ' );
}

void StructLister::visitAttribute( const TiXmlAttribute* pAttribute )
{
	if ( !pAttribute )
	{
		return;
	}
	Printf( " %s='%s'" ) ( pAttribute->Name() ) ( pAttribute->Value() );
	this->visitAttribute( pAttribute->Next() );
}

bool StructLister::VisitEnter( const TiXmlElement& pElement, const TiXmlAttribute* pAttribute )
{
	Printf( "%s<%s" ) ( mIndentStr ) ( pElement.Value() );
	this->visitAttribute( pAttribute );

	if ( pElement.FirstChild() )
	{
		if ( this->containsSimpleText( pElement ) )
		{
			Printf( ">" );
		}
		else
		{
			Printf( ">\n" );
			this->indent();
		}
	}
	else
	{
		Printf( " />\n" );
	}

	return true;
}

bool StructLister::VisitExit( const TiXmlElement& pElement )
{
	if ( pElement.FirstChild() )
	{
		if ( this->containsSimpleText( pElement ) )
		{
			Printf( "</%s>\n" ) ( pElement.Value() );
		}
		else
		{
			this->dedent();
			Printf( "%s</%s>\n" ) ( mIndentStr ) ( pElement.Value() );
		}
	}

	return true;
}

bool StructLister::Visit( const TiXmlText& pText )
{
	Printf( pText.Value() );
	return true;
}

// 	virtual bool VisitEnter( const TiXmlDocument& /*doc*/ )			{ return true; }
// 	virtual bool VisitExit( const TiXmlDocument& /*doc*/ )			{ return true; }
// 	virtual bool Visit( const TiXmlDeclaration& /*declaration*/ )	{ return true; }
// 	virtual bool Visit( const TiXmlComment& /*comment*/ )			{ return true; }
// 	virtual bool Visit( const TiXmlUnknown& /*unknown*/ )			{ return true; }
