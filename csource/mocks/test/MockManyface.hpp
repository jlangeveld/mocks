/**
*** @file
*** @brief "$Id$"
**/

#ifndef __MOCKINTERFACE_HPP__
#define __MOCKINTERFACE_HPP__

#include "./interface/Interface.hpp"
#include "./interface/Otherface.hpp"

namespace mock_generator_settings
{

struct MockManyface
: public interface::Interface
, protected interface::Otherface
{};

}

#endif
