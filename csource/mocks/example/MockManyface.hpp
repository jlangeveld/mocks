/**
*** @file
*** @brief "$Id$"
**/

#ifndef __MOCKINTERFACE_HPP__
#define __MOCKINTERFACE_HPP__

#include "./interface/Interface.hpp"
#include "./interface/Otherface.hpp"

//#define MOCK Interface
#include <MyMock.hpp>

#ifndef MOCK
namespace mock_generator_settings
{

struct MockManyface
: public interface::Interface
, protected interface::Otherface
{};

}
#endif

#endif
