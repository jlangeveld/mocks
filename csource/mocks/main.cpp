/**
*** @file
*** @brief "$Id$"
**/

#include "SettingsParser.hpp"
#include "interface/Interface.hpp"
#include "BasicOtherface.hpp"

#include <boost/foreach.hpp>
#include <loki/SafeFormat.h>
#include <tinyxml/tinyxml.h>

using Loki::Printf;

void parseParent( const std::string& pFilename )
{

}

int main( int argc, char** argv )
{
	SettingsParser setp;
	while ( setp.findMock() )
	{
		Printf( "mock '%s'\n" ) ( setp.mockName() );
		MemberCollector col;
//		MockParser mp( i );
//		parseParent( mp.parent, col );
	}
}
