#ifndef _WASP_RUNNABLE_INTERFACE_HPP
#define _WASP_RUNNABLE_INTERFACE_HPP

#include <shared.hpp>

namespace Wasp
{
    struct I_Runnable
    {
        virtual void run() = 0;
        virtual std::atomic_bool &isRunning() = 0;
    };
};

#endif // !_WASP_RUNNABLE_INTERFACE_HPP