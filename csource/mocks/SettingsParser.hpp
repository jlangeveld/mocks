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

	std::string mockName() const;
	std::string mockRefID() const;

protected:
private:
	TiXmlElement* findNamespace( TiXmlElement* pElement );
	TiXmlElement* findNextMock( TiXmlElement* current );
};

#endif
