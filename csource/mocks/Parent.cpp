/**
*** @file
*** @brief "$Id$"
**/

/**
 ** @class      Parent
 **
 **
 **
 ** @par        26-03-2010, jeroenl
 ** Eerste versie.
 ***************/

#include "Parent.hpp"

// *tors

/**
 ** Default constructor.
 **
 ** @par        26-03-2010, jeroenl
 ** Eerste versie.
 ***************/
Parent::Parent( const std::string& pName, const std::string& pRefID, const std::string& pVisibility )
: name( pName )
, refID( pRefID )
, visibility( pVisibility )
{}
