/**
*** @file
*** @brief "$Id$"
**/

#ifndef __INTERFACE_HPP__
#define __INTERFACE_HPP__

namespace interface
{

struct Interface
{
	virtual void doit() const = 0;
	virtual void done( int pStatus ) const = 0;
	virtual void fetch( int& pOutput ) = 0;
};

}

#endif
