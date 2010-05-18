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

	bool findMocker();
	bool findParameter();
	bool findParent();
	bool findSection();

	std::string getArgList();
	std::string getConst();
	std::string getKind();
	std::string getName();
	std::string getRefID();
	std::string getType();
	std::string getVisibility();

protected:
private:
	TiXmlElement* mCompoundDefElement;
	TiXmlElement* mParamElement;
	TiXmlElement* mSectionElement;

	bool currentIsMember();
	TiXmlElement* findNextMocker( TiXmlElement* pCurrent );
	TiXmlElement* findNextParameter( TiXmlElement* element );
	TiXmlElement* findNextParent( TiXmlElement* element );
	TiXmlElement* findNextSection( TiXmlElement* element );
	bool parsingParam();

};

#endif
