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

// Memberfunctions

//void
//BasicTemplateImpl::init( void )
//{
//	mStr = "";
//	mStr.reserve( 1000 );
//	_lmacro = "$";
//	_rmacro = "$";
//	_ifmacro = "IF";
//	_elsemacro = "ELSE";
//	_fimacro = "FI";
//	_loopmacro = "LOOP";
//	_loopenummacro = "ENUMLOOP";
//	_poolenummacro = "ENUMPOOL";
//	_enummacro = "ENUM";
//	_loopvarmacro = "LVAR";
//	_poolmacro = "POOL";
//	_headermacro = "HEADER";
//	_headervarmacro = "HVAR";
//	_redaehmacro = "REDAEH";
//	_filemacro = "FILE";
//	_errormessage = "";
//}

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
//	Printf( "### Replacing '%s' with '%s'.\n" ) ( macro ) ( pReplacement );

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
	string s, t;

	const std::string macroloop = getMacroName( "LOOP", pMacro );
	const std::string macropool = getMacroName( "POOL", pMacro );

	unsigned int i, j;
	unsigned int eind = 0, start;

	int _lenloop = macroloop.length();
	int _lenpool = macropool.length();

	unsigned int idx = 0;
	vector<string> loop_replacements;
	vector<string> loop_insertions;
	string bckp;

	long lTplSize = mStr.size();
	if ( lTplSize <= 40000 )
	{
		mStr.reserve( 40000 );
	}
	else
	{
		mStr.reserve( lTplSize * 2 );
	}

	// vind begin eerste loop-macro met naam pMacro
	i = mStr.find( macroloop );
	while ( i != string::npos )
	{ // zijn er nog loop-macro's?

		// vind einde loop-macro
		j = mStr.find( macropool, i );
		if ( j == string::npos )
		{	// wel loop maar geen pool
			return ;
		}
		t = getMacroName( "LOOPNEXT" + ToStr( ++idx ) );

		/* bepaal het te herhalen stuk */
		string repeat = mStr.substr( i + _lenloop, j - i - _lenloop );
		loop_replacements.push_back( repeat );

		/* schrijf eerste link voor te vervangen stuk macro */
		mStr.replace( i, j - i + _lenpool, t );

		// vind begin volgende loop-macro
		i = mStr.find( macroloop, i );
	}

	// creer de vector
	i = idx;
	while ( i > 0 )
	{
		loop_insertions.insert( loop_insertions.begin(), "" );
		i--;
	}

	// De template is leuk, maar kunnen we niet zo aan het BO voeren. Daarom moeten we een nieuwe,
	// tijdelijke template maken die alleen de gedeelten binnen de macro's bevat.
	bckp = mStr;

	do
	{
		i = idx;

		mStr = "";

		while ( i > 0 )
		{
			mStr += loop_replacements[ i - 1 ] + getMacroName( "POOLNEXT" + ToStr( i ) );
			i--;
		}
		// Laat het business object los op de tijdelijke template.
		pHandler.output();

		// Parse de tijdelijke template.
		i = idx;
		start = 0;
		while ( i > 0 )
		{
			string poolmacro = getMacroName( "POOLNEXT" + ToStr( i ) );
			eind = mStr.find( poolmacro, start );
			if ( eind != string::npos )
			{
				// voeg de tekst aan het einde toe
				loop_insertions[ i - 1 ].append( mStr.substr( start, eind - start ) );
			}
			start = eind + poolmacro.length();
			i--;
		}
	}
	while ( pHandler.next() );

	// Herstel de originele template
	mStr = bckp;


	// Vervang de stukken uit de originele template met de geparste stukken.
	i = idx;
	while ( i > 0 )
	{
		t = "LOOPNEXT" + ToStr( i );
		// Ja, hier wordt de macro "POOLNEXT" in plaats van "LOOPNEXT" gebruikt, als
		// work-around voor de replace functie.
		s = loop_insertions[ i - 1 ];
		replace( t, s );
		i--;
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
