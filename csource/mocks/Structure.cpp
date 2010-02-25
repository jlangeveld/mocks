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

#include <loki/SafeFormat.h>

using Loki::Printf;

// members

const std::string& Structure::getType() const
{
	return mType;
}

const std::string& Structure::getName() const
{
	return mName;
}

void Structure::reset( const std::string& pKind )
{
	if ( "struct" == pKind || "class" == pKind )
	{
		mType = pKind;
	}
	else
	{
		mType.clear();
	}

	mName.clear();
}

void Structure::setName( const std::string& pName )
{
	mName = pName;
}
