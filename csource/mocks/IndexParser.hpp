/**
*** @file
*** @brief "$Id$"
**/

#ifndef __INDEXPARSER_HPP__
#define __INDEXPARSER_HPP__

#include "Structure.hpp"
#include "XmlParser.hpp"

#include <vector>

class TiXmlDocument;

class IndexParser
	: public XmlParser
{
public:
	IndexParser();
	~IndexParser();

	Structure findStructure( TiXmlDocument& pIndex );
	Structure findStructure( const Structure& pPreviousStructure );

private:
	Structure findNextStructure( TiXmlElement* pElement );
};

#endif
