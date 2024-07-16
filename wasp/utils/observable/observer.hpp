#ifndef ___WASP_OBSERVABLE_OBSERVER_HPP___
#define ___WASP_OBSERVABLE_OBSERVER_HPP___

#include <utils/observable/interfaces/observer.interface.hpp>
#include <utils/generator/uuid.generator.hpp>
#include <utils/logger/console.logger.hpp>

namespace Wasp
{
    namespace Observable
    {
        template <typename T>
        class Observer : public I_Observer<T>, public Wasp::UUIDElement
        {
        public:
            // Observer(): {};
            virtual void on(T value) override
            {
                Wasp::Logger::ConsoleLogger::STATIC_LOG((this->uuid() + " Observer On fired!").c_str());
            };
            std::unique_ptr<const std::function<void(const T &)>> onCreate;
            std::unique_ptr<const std::function<void(const T &)>> onSubscribe;
            std::unique_ptr<const std::function<void(const T &)>> onNext;
            std::unique_ptr<const std::function<void(const T &)>> onDone;
            std::unique_ptr<const std::function<void(const T &)>> onUnsubscribe;
        };
    };
};

#endif // !___WASP_OBSERVABLE_OBSERVER_HPP___