#ifndef ___WASP_OBSERVABLE_OBSERVER_INTERFACE_HPP___
#define ___WASP_OBSERVABLE_OBSERVER_INTERFACE_HPP___

#include <shared.hpp>

namespace Wasp
{
    namespace Observable
    {
        template <typename T>
        class I_Observer
        {
        public:
            virtual void on(T value) = 0;
        };
    };
};

#endif // !___WASP_OBSERVABLE_OBSERVER_INTERFACE_HPP___
