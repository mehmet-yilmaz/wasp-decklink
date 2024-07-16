#ifndef ___WASP_OBSERVABLE_SUBJECT_INTERFACE_HPP___
#define ___WASP_OBSERVABLE_SUBJECT_INTERFACE_HPP___

#include <shared.hpp>
#include <utils/observable/observer.hpp>

namespace Wasp
{
    namespace Observable
    {
        template <typename T>
        class I_Subject
        {
        public:
            virtual const std::shared_ptr<Observer<T>> subscribe(const std::function<void(const T &)> &onNext) = 0;
            virtual void next(const T &value) = 0;
            virtual void done(const T &value) = 0;
            virtual void unsubscribe(const std::string &observer_id) = 0;
        };
    };
};

#endif // !___WASP_OBSERVABLE_SUBJECT_INTERFACE_HPP___