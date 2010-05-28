/**
*** @file
*** @brief "$Id$"
**/

#ifndef __STRUCTURE_HPP__
#define __STRUCTURE_HPP__

#include "BasicTemplate.hpp"
#include "Parent.hpp"

#include <string>
#include <vector>

class Structure
: public OutputLoopHandler
{
public:

	Structure( const std::string& pName );

	void addParent( const std::string& pName, const std::string& pRefID, const std::string& pVisibility );

	virtual bool next();
	virtual void output();

	void outputMockers( BasicTemplate& pTpl );
	void outputName( BasicTemplate& pTpl ) const;
	void outputParents( BasicTemplate& pTpl );

private:
	typedef std::vector< Parent > ParentContainerType;

	const std::string mName;
	ParentContainerType mParentRefIDs;

	BasicTemplate* mTpl;
	ParentContainerType::const_iterator mCurrentParent;
};

#endif
