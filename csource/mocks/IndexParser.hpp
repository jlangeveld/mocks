/**
*** @file
*** @brief "$Id$"
**/

#ifndef __INDEXPARSER_HPP__
#define __INDEXPARSER_HPP__

#include "StructLister.hpp"
#include "Structure.hpp"

#include <string>
#include <vector>

#include <tinyxml/tinyxml.h>

class IndexParser
: public TiXmlVisitor
{
public:
	mutable std::vector< Structure > mParsedStructures;

	IndexParser();
	~IndexParser();

	void parseDocument( TiXmlDocument& pIndex );

	virtual bool VisitEnter( const TiXmlElement& pElement, const TiXmlAttribute* pAttribute );
	virtual bool VisitExit( const TiXmlElement& pElement );
	virtual bool Visit( const TiXmlText& pText );

private:
	Structure mCurrentStructure;
	StructLister mLister;

	void enterElement( const TiXmlElement& pElement, const TiXmlAttribute* pAttribute );
	void parseCompoundElement( const TiXmlElement& pElement, const TiXmlAttribute* pAttribute );
	void parseNameElement( const TiXmlElement& pElement, const TiXmlAttribute* pAttribute );

};

#endif
