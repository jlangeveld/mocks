/**
*** @file
*** @brief "$Id$"
**/

/**
 ** @class      StructRef
 **
 **
 **
 ** @par        26-03-2010, jeroenl
 ** Eerste versie.
 ** @par        06-06-2010, jeroenl
 ** Parent Hernoemd naar StructRef.
 ***************/

#include "StructRef.hpp"

// *tors

/**
 ** Default constructor.
 **
 ** @par        26-03-2010, jeroenl
 ** Eerste versie.
 ***************/
StructRef::StructRef( const std::string& pName, const std::string& pRefID, const std::string& pVisibility )
: name( pName )
, refID( pRefID )
, visibility( pVisibility )
{}

// members

void StructRef::outputName( BasicTemplate& pTpl ) const
{
	pTpl.replace( "StructRef_NAME", this->name );
}
