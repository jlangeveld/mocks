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
	virtual ~Interface() = 0;
	virtual void doit() const = 0;
	virtual void done( int pStatus ) const = 0;
};

}

#endif
