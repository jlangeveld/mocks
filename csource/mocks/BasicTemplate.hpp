/**
*** @file
*** @brief "$Id$"
**/

#ifndef __BASICTEMPLATE_HPP__
#define __BASICTEMPLATE_HPP__

#include <string>

struct OutputLoopHandler
{
	virtual bool next() = 0;
	virtual void output() = 0;
};

struct BasicTemplate
{
	virtual bool replace( const std::string& pMacro, const std::string&  pReplacement ) = 0;
	virtual bool replaceFirst( const std::string& pMacro, const std::string&  pReplacement ) = 0;
	virtual bool replaceIf( const std::string&  pMacro, bool pValue ) = 0;
	virtual void replaceLoop( const std::string&  pMacro, OutputLoopHandler& pHandler ) = 0;
	virtual void replaceFile( const std::string&  pMacro, const std::string&  pFilename ) = 0;

	virtual std::string str() const = 0;
	virtual void setStr( std::string pStr ) = 0;
};

#endif
