/**
*** @file
*** @brief "$Id$"
**/

#include "BasicTemplate.hpp"

#include <string>
#include <vector>

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

	void appendLoopChunks( const std::vector< std::string >& pResults, std::vector< std::size_t >& pCurrentLoopChunk );
	bool appendNoLoopChunk( const std::string& noLoopChunks, std::size_t& currentNoLoopChunk, std::size_t& prevNoLoopChunk );
	void computeLoopChunks( const std::string& pMacro, std::string& pNoLoopChunks, std::string& pLoopChunks );


};

#endif
