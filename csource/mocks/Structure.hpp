/**
*** @file
*** @brief "$Id$"
**/

#ifndef __STRUCTURE_HPP__
#define __STRUCTURE_HPP__

#include "BasicTemplate.hpp"
#include "Mocker.hpp"
#include "StructRef.hpp"

#include <string>
#include <vector>

class Structure
{
public:
	typedef std::vector< StructRef > ParentContainerType;
	typedef std::vector< Mocker > MockerContainerType;

	Structure( const std::string& pName );

	void addParent( const std::string& pName, const std::string& pRefID, const std::string& pVisibility );
	Mocker& createMocker( const std::string& pType, const std::string& pName, const std::string& pConst );

	void outputMockers( BasicTemplate& pTpl );
	void outputName( BasicTemplate& pTpl ) const;
	void outputParents( BasicTemplate& pTpl );

private:
	const std::string mName;
	ParentContainerType mParentRefIDs;
	MockerContainerType mMockers;

	ParentContainerType::const_iterator mCurrentParent;
};

#endif
