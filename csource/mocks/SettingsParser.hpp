/**
*** @file
*** @brief "$Id$"
**/

#ifndef __SETTINGSPARSER_HPP__
#define __SETTINGSPARSER_HPP__

#include "XmlParser.hpp"
#include <tinyxml/tinyxml.h>

class SettingsParser
: public XmlParser
{

public:

	SettingsParser();
	~SettingsParser();

	bool findMock();

	std::string mockName();

protected:
private:
	TiXmlElement* mCurrent;

	TiXmlElement* findNamespace( TiXmlElement* pElement );
	TiXmlElement* findNextMock( TiXmlElement* current );
};

#endif
