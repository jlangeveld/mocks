/**
*** @file
*** @brief "$Id$"
**/

#ifndef __MOCKOTHERFACE_HPP__
#define __MOCKOTHERFACE_HPP__

#include "BasicOtherface.hpp"

//#define MOCK Otherface
#include <MyMock.hpp>

#ifndef MOCK
namespace mock_generator_settings
{

struct MockOtherface
: public BasicOtherface
{};

}
#endif

#endif
