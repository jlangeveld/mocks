/**
*** @file
*** @brief "$Id$"
**/

#ifndef __STRUCTURE_HPP__
#define __STRUCTURE_HPP__

#include "BasicTemplate.hpp"
#include "Mocker.hpp"
#include "Parent.hpp"

#include <string>
#include <vector>

class Structure
: public OutputLoopHandler
{
public:
	typedef std::vector< Parent > ParentContainerType;
	typedef std::vector< Mocker > MockerContainerType;

	Structure( const std::string& pName );

	void addParent( const std::string& pName, const std::string& pRefID, const std::string& pVisibility );
	Mocker& createMocker( const std::string& pType, const std::string& pName, const std::string& pConst );

	virtual bool next();
	virtual void output();

	void outputMockers( BasicTemplate& pTpl );
	void outputName( BasicTemplate& pTpl ) const;
	void outputParents( BasicTemplate& pTpl );

private:
	typedef std::vector< Parent > ParentContainerType;
	typedef std::vector< Mocker > MockerContainerType;

	const std::string mName;
	ParentContainerType mParentRefIDs;
	MockerContainerType mMockers;

	BasicTemplate* mTpl;
	ParentContainerType::const_iterator mCurrentParent;
};

#endif
