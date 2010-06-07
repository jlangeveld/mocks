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

#include "BasicTemplateImpl.hpp"
#include "StructList.hpp"
#include "StructRef.hpp"

#include <boost/algorithm/string/replace.hpp>

using boost::replace_first_copy;

// *tors

/**
 ** Default constructor.
 **
 ** @par        26-03-2010, jeroenl
 ** Eerste versie.
 ***************/
StructRef::StructRef( const std::string& pName, const std::string& pRefID, const std::string& pVisibility )
: mName( pName )
, mRefID( pRefID )
, mVisibility( pVisibility )
{}

// members

std::string StructRef::outputMockObject( const std::string& pTpl, StructList* pStructHolder ) const
{
	BasicTemplateImpl tpl;
	tpl.setStr( pTpl );

	Structure& mock = pStructHolder->getStructure( mName );
	mock.outputName( tpl );
	mock.outputParents( tpl );
//	mock.outputMockers( tpl );

	return tpl.str();
}

void StructRef::outputName( BasicTemplate& pTpl ) const
{
	pTpl.replace( "STRUCTREF_NAME", mName );
	pTpl.replace( "STRUCTREF_VISIBILITY", mVisibility );
}

std::string StructRef::stripGeneratorNamespace() const
{
	return replace_first_copy( mName, "mock_generator_settings::", "" );
}
