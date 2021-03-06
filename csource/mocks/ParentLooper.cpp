/**
*** @file
*** @brief "$Id$"
**/

/**
 ** @class      ParentLooper
 **
 **
 **
 ** @par        02-06-2010, jeroenl
 ** Eerste versie.
 ***************/

#include "ParentLooper.hpp"

#include <loki/SafeFormat.h>

using Loki::Printf;

// *tors

/**
 ** Default constructor.
 **
 ** @par        02-06-2010, jeroenl
 ** Eerste versie.
 ***************/
ParentLooper::ParentLooper( BasicTemplate& pTpl, const ParentContainerType& pContainer )
: mTpl( pTpl )
, mCurrent( pContainer.begin() )
, mEnd( pContainer.end() )
{}

/** Default destructor.
 **
 ** @par        02-06-2010, jeroenl
 ** Eerste versie.
 ***************/
ParentLooper::~ParentLooper()
{}

// members

bool ParentLooper::next()
{
	if ( mCurrent == mEnd )
	{
		return false;
	}
	return ( ++mCurrent != mEnd );
}

void ParentLooper::output()
{
	if ( mCurrent == mEnd )
	{
		return;
	}

	mCurrent->outputName( mTpl );
}
