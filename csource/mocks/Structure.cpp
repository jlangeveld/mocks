/**
*** @file
*** @brief "$Id$"
**/

/**
 ** @class      Structure
 **
 **
 **
 ** @par        24-02-2010, j.langeveld
 ** Eerste versie.
 ***************/

#include "Structure.hpp"

// *tors

Structure::Structure()
	: element( 0 )
{}

Structure::Structure( TiXmlElement* pElement, const std::string& pType, const std::string& pName )
	: element( pElement )
	, type( pType )
	, name( pName )
{}
