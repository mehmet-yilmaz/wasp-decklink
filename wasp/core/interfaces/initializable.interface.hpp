#ifndef _WASP_INITIALIZABLE_INTERFACE_HPP
#define _WASP_INITIALIZABLE_INTERFACE_HPP

#include <shared.hpp>

namespace Wasp
{
    struct I_Initializable
    {
        virtual void init() = 0;
        virtual std::atomic_bool &initialized() = 0;
    };
};

#endif // !_WASP_INITIALIZABLE_INTERFACE_HPP