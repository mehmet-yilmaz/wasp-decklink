#ifndef ___WASP_OBSERVABLE_SUBJECT_HPP___
#define ___WASP_OBSERVABLE_SUBJECT_HPP___

#include <shared.hpp>
#include <utils/observable/interfaces/subject.interface.hpp>
#include <utils/observable/observer.hpp>
#include <utils/generator/uuid.generator.hpp>
namespace Wasp
{
    namespace Observable
    {
        template <typename T>
        class Subject : public I_Subject<T>
        {
        public:
            const std::string id{Wasp::Generators::Uuid::generate()};

            virtual const std::shared_ptr<Observer<T>> subscribe(const std::function<void(const T &)> &onNext) override
            {
                const auto observer = std::make_shared<Observer<T>>();
                observer->onNext = std::make_unique<const std::function<void(const T &)>>(std::move(onNext));
                this->observers[observer->uuid()] = observer;
                return observer;
            };

            virtual void unsubscribe(const std::string &observer_id) override
            {
                this->observers.erase(observer_id);
            };

            virtual void next(const T &val) override
            {
                this->value = val;
                for (const auto &row : this->observers)
                {
                    if (*row.second->onNext)
                    {
                        (*row.second->onNext)(this->value);
                    };
                }
            };

            virtual void done(const T &val) override
            {
                this->value = val;
                for (const auto &row : this->observers)
                {
                    if ((row.second) && (*row.second->onDone))
                    {
                        (*row.second->onDone)(this->value);
                    }
                }
            };

            ~Subject(){
                // Wasp::Logger::ConsoleLogger::STATIC_LOG
                // ("Subject Destructor!");
                // this->done(this->value);
            };

            Subject(){};
            Subject(const T &val) : value(val){};

        private:
            T value;
            std::map<const std::string, std::shared_ptr<Observer<T>>> observers{};
        };
    };
};

#endif // !___WASP_OBSERVABLE_SUBJECT_HPP___