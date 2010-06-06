/**
*** @file
*** @brief "$Id$"
**/

#ifndef __PARENTLOOPER_HPP__
#define __PARENTLOOPER_HPP__

#include "BasicTemplate.hpp"
#include "StructRef.hpp"

#include <string>
#include <vector>

class ParentLooper
: public OutputLoopHandler
{
	typedef std::vector< StructRef > ParentContainerType;
	typedef ParentContainerType::const_iterator ParentIteratorType;

public:

	ParentLooper( BasicTemplate& pTpl, const ParentContainerType& pContainer );
	virtual ~ParentLooper();

	virtual bool next();
	virtual void output();

protected:
private:

	BasicTemplate& mTpl;

	ParentIteratorType mCurrent;
	const ParentIteratorType mEnd;

};

#endif
