/**
*** @file
*** @brief "$Id$"
**/

#ifndef __MYMOCK_HPP__
#define __MYMOCK_HPP__

#include <Stringize.hpp>
#define MOCK_CAT( a,b ) a##b
#define MOCK_NS_HELPER( subject ) namespace mock_generator_settings { struct MOCK_CAT( Mock,subject ) : public subject {}; }
#define MOCK_INCLUDE_HELPER( subject ) STRINGIZE( MOCK_CAT( .mocks/Mock,subject ).hpp )

#endif

#ifdef MOCK

#ifdef MOCK_RUN
MOCK_NS_HELPER( MOCK )
#else
#include MOCK_INCLUDE_HELPER( MOCK )
#endif

#undef MOCK
#undef MOCK_HIDE_PROTECTED
#endif
