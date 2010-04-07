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
#include "tagnames.hpp"

#include <boost/algorithm/string/erase.hpp>
#include <loki/SafeFormat.h>

using boost::erase_first_copy;
using Loki::Printf;

// *tors

Structure::Structure( const std::string& pName )
	: mName( erase_first_copy( pName, MOCK_OBJECT_PREFIX ) )
{
	Printf( "Created struct '%s'\n" ) ( mName );
}

// members

void Structure::addParent( const std::string& pName, const std::string& pRefID, const std::string& pVisibility )
{
	mParentRefIDs.push_back( Parent( pName, pRefID, pVisibility ) );
	Printf( "  Added %s parent '%s' (refid '%s')\n" ) ( pVisibility ) ( pName ) ( pRefID );
}
