/**
*** @file
*** @brief "$Id$"
**/

#ifndef __STRUCTLISTER_HPP__
#define __STRUCTLISTER_HPP__

#include <string>

#include <tinyxml/tinyxml.h>

class StructLister
: public TiXmlVisitor
{
	size_t mIndentSize;
	std::string mIndentStr;

	void dedent();
	void indent();

	void visitAttribute( const TiXmlAttribute* pAttribute );
	bool containsSimpleText( const TiXmlElement& pElement );

public:
	StructLister();
	virtual ~StructLister();

	virtual bool VisitEnter( const TiXmlElement& pElement, const TiXmlAttribute* pAttribute );
	virtual bool VisitExit( const TiXmlElement& pElement );
	virtual bool Visit( const TiXmlText& pText );

// 	virtual bool VisitEnter( const TiXmlDocument& /*doc*/ )			{ return true; }
// 	virtual bool VisitExit( const TiXmlDocument& /*doc*/ )			{ return true; }
// 	virtual bool Visit( const TiXmlDeclaration& /*declaration*/ )	{ return true; }
// 	virtual bool Visit( const TiXmlComment& /*comment*/ )			{ return true; }
// 	virtual bool Visit( const TiXmlUnknown& /*unknown*/ )			{ return true; }
};

#endif
