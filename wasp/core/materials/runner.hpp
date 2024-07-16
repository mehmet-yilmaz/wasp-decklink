#ifndef ___WASP_RUNNER_HPP___
#define ___WASP_RUNNER_HPP___

#include <shared.hpp>
#include <core/interfaces/runnable.interface.hpp>
#include <core/elements/named.element.hpp>
#include <core/elements/uuid.element.hpp>
#include <core/interfaces/initializable.interface.hpp>
#include <utils/generator/name.generator.hpp>

namespace Wasp
{

    class Runner : public I_Runnable,
                   public I_Initializable,
                   public UUIDElement,
                   public NamedElement
    {
    public:
        virtual ~Runner() = default;
        virtual void init() = 0;
        virtual void run() = 0;
        std::atomic_bool &isInitialized()
        {
            return this->initialized;
        };
        std::atomic_bool &isRunning()
        {
            return this->running;
        };

    protected:
        Runner(const Wasp::Types::TName &name_ = Wasp::Generators::NameGenerator::generate(" Runner")) : NamedElement(name_)
        {
            Wasp::Logger::ConsoleLogger::STATIC_LOG((this->name() + " Constructed!").c_str());
        };
        std::atomic_bool running{false};
        std::atomic_bool initialized{false};
    };

};

#endif // !___WASP_RUNNER_HPP___
