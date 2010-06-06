/**
*** @file
*** @brief "$Id$"
**/

#include "BasicTemplateImpl.hpp"
#include "ToStr.hpp"

#include <vector>
#include <boost/scoped_ptr.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <loki/SafeFormat.h>

using boost::scoped_ptr;
using boost::replace_all;
using Loki::Printf;
using Loki::SPrintf;
using std::string;
using std::vector;

namespace
{
const char SEP = '\0';

const std::string getMacroName( const std::string& pType, const std::string& pName )
{
	string result;
	SPrintf( result, "$%s%s$" ) ( pType ) ( pName );
	return result;
}

const std::string getMacroName( const std::string& pName )
{
	string result;
	SPrintf( result, "$%s$" ) ( pName );
	return result;
}

std::string read( const std::string& pFilename )
{
	string result;
	FILE * infile = fopen( pFilename.c_str(), "rb" );
	if ( !infile )
	{
		SPrintf( result, "File couldn't be opened: '%s'" ) ( pFilename );
		return result;
	}

	/* bepaal grootte */
	fseek( infile, 0, SEEK_END );
	const std::size_t size = ftell( infile );
	rewind( infile );

	/* alloc buffer voor gehele file */
	typedef char Byte;
	scoped_ptr< Byte > buf( new Byte[ size ] );
	if( !buf.get() )
	{
		SPrintf( result, "Error while allocating memory for the read-buffer" );
		fclose( infile );
		return result;
	}

	const size_t read = fread( buf.get(), sizeof( Byte ), size, infile );
	if ( read != size ) {}
	fclose( infile );

	result.assign( buf.get(), size );
	return result;
}

}

// *tors

BasicTemplateImpl::BasicTemplateImpl()
{}

BasicTemplateImpl::BasicTemplateImpl( const std::string& pFilename )
: mStr( read( pFilename ) )
{}

// members

void BasicTemplateImpl::appendLoopChunks( const std::vector< std::string >& pResults, std::vector< std::size_t >& pCurrentLoopChunk )
{
	for( size_t i = 0 ; i < pResults.size(); ++i )
	{
		const string& result = pResults.at( i );
		size_t& currentLoopChunk = pCurrentLoopChunk.at( i );
		const size_t nextChunk = result.find( SEP, currentLoopChunk );

		string message;
		message.append( result, currentLoopChunk, nextChunk - currentLoopChunk );
		mStr.append( result, currentLoopChunk, nextChunk - currentLoopChunk );
		currentLoopChunk = nextChunk + 1;
	}
}

bool BasicTemplateImpl::appendNoLoopChunk( const std::string& noLoopChunks, std::size_t& currentNoLoopChunk, std::size_t& prevNoLoopChunk )
{
	currentNoLoopChunk = noLoopChunks.find( SEP, prevNoLoopChunk );
	if ( currentNoLoopChunk == string::npos )
	{
		mStr.append( noLoopChunks, prevNoLoopChunk, string::npos );
		return false;
	}

	size_t noLoopChunkSize = currentNoLoopChunk - prevNoLoopChunk;
	string message;
	message.append( noLoopChunks, prevNoLoopChunk, noLoopChunkSize );
	mStr.append( noLoopChunks, prevNoLoopChunk, noLoopChunkSize );
	prevNoLoopChunk = currentNoLoopChunk + 1;

	return true;
}

void BasicTemplateImpl::computeLoopChunks( const std::string& pMacro, std::string& pNoLoopChunks, std::string& pLoopChunks )
{
	const std::string macroLoop = getMacroName( "LOOP", pMacro );
	const std::string macroPool = getMacroName( "POOL", pMacro );

	size_t posLoop = mStr.find( macroLoop );
	if ( posLoop == string::npos )
	{
		return;
	}

	size_t begin, posPool;
	size_t prevLoop = 0;
	do
	{
		posPool = mStr.find( macroPool, posLoop );
		if ( posPool == string::npos )
		{
			string message;
			SPrintf( message, "Found '%s' at index %d, but found no matching '%s'." ) ( macroLoop ) ( posLoop ) ( macroPool );
			throw std::runtime_error( message );
		}

		if ( !pNoLoopChunks.empty() )
		{
			pNoLoopChunks += SEP;
		}
		pNoLoopChunks.append( mStr, prevLoop, posLoop - prevLoop );

		if ( !pLoopChunks.empty() )
		{
			pLoopChunks += SEP;
		}
		begin = posLoop + macroLoop.size();
		pLoopChunks.append( mStr, begin, posPool - begin );

		prevLoop = posPool + macroPool.size();
		posLoop = mStr.find( macroLoop, posPool );
	}
	while ( posLoop != string::npos );

	pNoLoopChunks += SEP;
	begin = posPool + macroPool.size();
	if ( begin != mStr.size() )
	{
		pNoLoopChunks.append( mStr, begin, mStr.size() - begin );
	}
	else
	{
		pNoLoopChunks.append( "" );
	}
}

/*
bool BasicTemplateImpl::replace( const std::map< std::string, std::string >& pMacro )
{
	if ( mStr.empty() )
	{
		return true;
	}

	// onze eigen split string is sneller dan boost tokenizer
	vector<string> macroLijst = general::string_ex::splitString( mStr, '$' ) ;
	mStr.clear();

	bool previousWasMacro = true;
	size_t max = macroLijst.size();
	vervangIter zoek;
	for ( size_t i = 0; i < max; ++i )
	{
		if ( !macroLijst[ i ].empty()	&& ( ( zoek = pMacro.find( macroLijst[ i ] ) ) != pMacro.end() ) )
		{
			mStr += zoek->second;
			previousWasMacro = true;
		}
		else
		{
			mStr += ( !previousWasMacro ? "$" : "" ) + macroLijst[ i ];
			previousWasMacro = false;
		}
	}

	return true;
}
*/

bool BasicTemplateImpl::replace( const std::string& pMacro, const std::string& pReplacement )
{
	const string macro = getMacroName( pMacro );
//	Printf( " ### Replacing '%s' with '%s'.\n" ) ( macro ) ( pReplacement );

	if ( mStr.find( macro ) == string::npos )
	{
		return false;
	}

	replace_all( mStr, macro, pReplacement );
	return true;
}

bool BasicTemplateImpl::replaceFirst( const std::string& pMacro, const std::string& pReplacement )
{
	const string macro = getMacroName( pMacro );
	const size_t pos = mStr.find( macro );
	if ( pos != string::npos )
	{
		mStr.replace( pos, macro.size(), pReplacement );
		return true;
	}
	return false;
}

bool BasicTemplateImpl::replaceIf( const std::string& pMacro, bool pValue )
{
	bool replaced = false;
	string str;

	str.reserve( mStr.size() ); /* kan alleen kleiner worden */

	char * ref = ( char * ) mStr.c_str();
	char * buf = ( char * ) str.c_str();

	const std::string ifStr = getMacroName( "IF", pMacro );
	const std::string elseStr = getMacroName( "ELSE", pMacro );
	const std::string fiStr = getMacroName( "FI", pMacro );

	char * keyIf = ( char * ) ifStr.c_str();
	char * keyElse = ( char * ) elseStr.c_str();
	char * keyFi = ( char * ) fiStr.c_str();
	char * posIf;
	char * posElse;
	char * posFi;
	int lenKeyIf = ifStr.length();
	int lenKeyFi = fiStr.length();
	int lenKeyElse = elseStr.length();

	posIf = strstr( ref, keyIf );
	int len;
	buf[ 0 ] = 0;

	while ( posIf != NULL )
	{
		len = ( posIf - ref );
		strncat( buf, ref, len ); /* voorloop tot 1e if */

		ref = posIf + lenKeyIf;
		posElse = strstr( ref, keyElse );
		posFi = strstr( ref, keyFi );
		if ( posFi != NULL )
		{
			replaced = true;
			/* ook Else? */
			if ( posElse != NULL )
			{
				/* else voor fi? */
				if ( posElse < posFi )
				{
					if ( pValue )
					{
						/* if tak afdrukken */
						len = ( posElse - ref );
						strncat( buf, ref, len );
					}
					else
					{
						/* else tak afdrukken */
						ref = ( posElse + lenKeyElse );
						len = ( posFi - ref );
						strncat( buf, ref, len );
					}
				}
				else
				{
					len = ( posFi - ref );
					if ( pValue )
					{
						strncat( buf, ref, len );
					}
				}
			}
			else
			{
				len = ( posFi - ref );
				if ( pValue )
				{
					strncat( buf, ref, len );
				}
			}
			ref = posFi + lenKeyFi; /* na de FI verder gaan */
		}
		else
		{
			/* geen matching FI, retourneer origineel */
			strcat( buf, keyIf );
		}
		posIf = strstr( ref, keyIf );
	}
	strcat( buf, ref );

	mStr = string( buf );

	return replaced;

}

void BasicTemplateImpl::replaceLoop( const string & pMacro, OutputLoopHandler& pHandler )
{
	if ( mStr.empty() )
	{
		return;
	}

	string noLoopChunks, loopChunks;
	this->computeLoopChunks( pMacro, noLoopChunks, loopChunks );

	vector< string > results;
	do
	{
		mStr = loopChunks;
		pHandler.output();
		results.push_back( mStr );
	}
	while ( pHandler.next() );

	size_t currentNoLoopChunk = 0, prevNoLoopChunk = 0;
	vector< size_t > currentLoopChunk( results.size(), 0 );
	mStr.clear();

	while ( this->appendNoLoopChunk( noLoopChunks, currentNoLoopChunk, prevNoLoopChunk ) )
	{
		this->appendLoopChunks( results, currentLoopChunk );
	}
}

void BasicTemplateImpl::replaceFile( const std::string& pMacro, const std::string& pFilename )
{
	this->replace( pMacro, read( pFilename ) );
}

void BasicTemplateImpl::setStr( std::string pStr )
{
	mStr.swap( pStr );
}

std::string BasicTemplateImpl::str() const
{
	return mStr;
}
