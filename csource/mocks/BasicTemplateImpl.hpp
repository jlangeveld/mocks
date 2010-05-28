/**
*** @file
*** @brief "$Id$"
**/

#include "BasicTemplate.hpp"

#include <string>

#ifndef __BASICTEMPLATEIMPL_HPP__
#define __BASICTEMPLATEIMPL_HPP__

class BasicTemplateImpl
: public BasicTemplate
{
public:
	BasicTemplateImpl();
	BasicTemplateImpl( const std::string& pFilename );

	virtual bool replace( const std::string& pMacro, const std::string&  pReplacement );
	virtual bool replaceFirst( const std::string& pMacro, const std::string&  pReplacement );
	virtual bool replaceIf( const std::string&  pMacro, bool pValue );
	virtual void replaceLoop( const std::string&  pMacro, OutputLoopHandler& pHandler );
	virtual void replaceFile( const std::string&  pMacro, const std::string&  pFilename );

	virtual std::string str() const;
	virtual void setStr( std::string pStr );

private:
	std::string mStr;
};

#endif
