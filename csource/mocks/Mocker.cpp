/**
*** @file
*** @brief "$Id$"
**/
/**
*** @file
*** @brief "$Id$"
**/

/**
 ** @class      Mocker
 **
 **
 **
 ** @par        25-04-2010, jeroenl
 ** Eerste versie.
 ***************/

#include "BasicTemplateImpl.hpp"
#include "Mocker.hpp"

#include <loki/SafeFormat.h>

using Loki::Printf;

// *tors

/**
 ** Default constructor.
 **
 ** @par        25-04-2010, jeroenl
 ** Eerste versie.
 ***************/
Mocker::Mocker( const std::string& pType, const std::string& pName, const std::string& pConst )
: mType( pType )
, mName( pName )
, mConst( pConst )
{
	Printf( "  - Added mocker '%s %s %s'\n" ) ( mType ) ( mName ) ( mConst );
}

Mocker::Parameter::Parameter( const std::string& pType, const std::string& pName )
: mType( pType )
, mName( pName )
{
	Printf( "    - Added parameter '%s %s'\n" ) ( mType ) ( mName );
}

// members
void Mocker::addParam( const std::string& pType, const std::string& pName )
{
	mParameters.push_back( Mocker::Parameter( pType, pName ) );
}

void Mocker::outputHeader( BasicTemplate& pTpl ) const
{
	BasicTemplateImpl tplHeader( "/home/jeroenl/templates/mocks/MockerHeader.tpl" );
	tplHeader.replace( "TYPE", mType );
	tplHeader.replace( "NAME", mName );
	tplHeader.replace( "CONST", mConst );

	pTpl.replace( "MOCKER_HEADER", tplHeader.str() );
}

void Mocker::outputImpl( BasicTemplate& pTpl ) const
{

}
