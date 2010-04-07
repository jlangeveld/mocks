/**
*** @file
*** @brief "$Id$"
**/

#ifndef __STRUCTPARSER_HPP__
#define __STRUCTPARSER_HPP__

#include "XmlParser.hpp"

class StructParser
	: public XmlParser
{

public:

	StructParser( const std::string& pRefID );
	~StructParser();

	bool findParent();
	bool findMocker();

	std::string getName();
	std::string getRefID();
	std::string getVisibility();

protected:
private:
	TiXmlElement* mCompoundDefElement;

	TiXmlElement* findNextParent( TiXmlElement* element );

};

#endif