/**
*** @file
*** @brief "$Id$"
**/

#include "SettingsParser.hpp"
#include "Structure.hpp"
#include "StructList.hpp"
#include "StructParser.hpp"

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <boost/foreach.hpp>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <boost/algorithm/string/erase.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <loki/SafeFormat.h>
#include <tinyxml/tinyxml.h>

using boost::erase_last;
using boost::filesystem::create_symlink;
using boost::filesystem::exists;
using boost::filesystem::is_symlink;
using boost::filesystem::path;
using boost::is_any_of;
using boost::program_options::options_description;
using boost::program_options::variables_map;
using boost::program_options::store;
using boost::program_options::parse_command_line;
using boost::program_options::notify;
using boost::algorithm::split;
using boost::trim;

using Loki::Printf;
using Loki::SPrintf;

using std::cin;
using std::cout;
using std::map;
using std::string;
using std::vector;

void create_symlinks( const boost::program_options::variables_map& pVMap )
{
	typedef vector< string > splitVector_type;

	const bool verbose = pVMap.count( "verbose" );
	if ( verbose )
	{
		Printf( "Creating symlinks:\n" );
	}
	else
	{
		Printf( "Creating symlinks...\n" );
	}

	string line;
	splitVector_type splitObject;
	splitVector_type splitVector;
	while ( getline( cin, line ) )
	{
		split( splitObject, line, is_any_of( ":\\" ) );
		if ( verbose )
		{
			Printf( "[%d] '%s'\n" ) ( splitObject.size() ) ( line );
		}
		if ( splitObject.size() > 2 )
		{
			split( splitVector, splitObject.at( 1 ), is_any_of( " " ) );
		}
		else
		{
			split( splitVector, splitObject.at( 0 ), is_any_of( " " ) );
		}

		BOOST_FOREACH( path bfsFile, splitVector )
		{
			if ( !bfsFile.string().empty() )
			{
				string fileName, linkName;
				SPrintf( fileName, "../%s" ) ( bfsFile.relative_path().string() );
				SPrintf( linkName, "%s/%s" ) ( ".mocks_doxy" ) ( bfsFile.filename() );
				if ( !is_symlink( linkName ) )
				{
					if ( verbose )
					{
						Printf( "... '%s' <-- '%s'\n" ) ( fileName ) ( linkName );
					}
					create_symlink( fileName, linkName );
				}
			}
		}
	}
}

int main( int argc, char** argv )
try
{
	options_description desc( "Allowed options" );
	desc.add_options()
		( "help,h", "Produce help message" )
		( "link,l", "Create and populate subdir '.mocks_doxy' for doxygen to parse" )
		( "verbose,V", "Show each created symlink (for testing purposes...)" );

	variables_map vm;
	store( parse_command_line( argc, argv, desc ), vm );
	notify( vm );

	if ( vm.count( "help" ) )
	{
		Printf( "%s usage:\n" ) ( argv[0] );
		cout << desc << "\n";
		return 1;
	}

	if ( vm.count( "link" ) )
	{
		create_symlinks( vm );
		return 0;
	}

	SettingsParser setp;
	StructList allStructs;

	while ( setp.findMock() )
	{
		allStructs.push( setp.mockName(), setp.mockRefID() );
	}
	allStructs.parseAll();
	allStructs.outputAllMockObjects();

	return 0;
}

catch ( const std::runtime_error& pEx )
{
	Printf( "\n\n** RUNTIME EXCEPTION **\n%s\n\n" ) ( pEx.what() );
}

catch ( const std::exception& pEx )
{
	Printf( "\n\n** EXCEPTION **\n%s\n\n" ) ( pEx.what() );
}
