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

 #include "ParentLooper.hpp"
#include "Structure.hpp"
#include "tagnames.hpp"

#include <boost/algorithm/string/case_conv.hpp>
#include <boost/algorithm/string/erase.hpp>
#include <loki/SafeFormat.h>

using boost::erase_first_copy;
using boost::to_upper_copy;
using Loki::Printf;

// *tors

Structure::Structure( const std::string& pName )
	: mName( erase_first_copy( pName, MOCK_OBJECT_PREFIX ) )
	, mCurrentParent( mParentRefIDs.end() )
{
	Printf( "( Created struct '%s' )\n" ) ( mName );
}

// members

void Structure::addParent( const std::string& pName, const std::string& pRefID, const std::string& pVisibility )
{
	mParentRefIDs.push_back( Parent( pName, pRefID, pVisibility ) );
	Printf( "  - Added %s parent '%s' (refid '%s')\n" ) ( pVisibility ) ( pName ) ( pRefID );
}

Mocker& Structure::createMocker( const std::string& pType, const std::string& pName, const std::string& pConst )
{
	mMockers.push_back( Mocker( pType, pName, pConst ) );
	return mMockers.back();
}

void Structure::outputMockers( BasicTemplate& pTpl )
{
//	HIER
}

void Structure::outputName( BasicTemplate& pTpl ) const
{
	pTpl.replace( "MOCKOBJECT", mName );
	pTpl.replace( "MOCKOBJECT_UPPER", to_upper_copy( mName ) );
}

void Structure::outputParents( BasicTemplate& pTpl )
{
	ParentLooper looper( pTpl, mParentRefIDs );
	pTpl.replaceLoop( "PARENTS", looper );
}
