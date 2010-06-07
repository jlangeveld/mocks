/**
*** @file
*** @brief "$Id$"
**/

#ifndef __STRUCTREF_HPP__
#define __STRUCTREF_HPP__

#include "BasicTemplate.hpp"

#include <string>

struct StructList;
struct Structure;

class StructRef
{
public:
	StructRef( const std::string& pName, const std::string& pRefID, const std::string& pVisibility = "" );

	std::string outputMockObject( const std::string& pTpl, StructList* pStructHolder ) const;
	void outputName( BasicTemplate& pTpl ) const;
	std::string stripGeneratorNamespace() const;

protected:
private:
	std::string mName;
	std::string mRefID;
	std::string mVisibility;


};

#endif
