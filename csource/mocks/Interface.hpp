/**
*** @file
*** @brief "$Id$"
**/

#ifndef __INTERFACE_HPP__
#define __INTERFACE_HPP__

struct Interface
{
	virtual ~Interface() = 0;
	virtual void doit() const = 0;
};

#endif
