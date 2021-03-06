/**
*** @file
*** @brief "$Id$"
**/

#ifndef __XMLPARSER_HPP__
#define __XMLPARSER_HPP__

#include <string>

#include <tinyxml/tinyxml.h>

class XmlParser
{

public:
	XmlParser();
	XmlParser( const std::string& pFilename );

	std::string findName( TiXmlElement* pElement );

protected:
	TiXmlDocument mDoc;
	TiXmlElement* mCurrent;

	std::string getTextFor( const std::string& pTagname );
	std::string getTextFor( const std::string& pTagname, TiXmlElement* pElement );
};

#endif
