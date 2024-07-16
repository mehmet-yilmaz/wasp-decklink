#ifndef ___WASP_CONTROLLER_HPP___
#define ___WASP_CONTROLLER_HPP___

#include <core/materials/provider.hpp>
#include <core/elements/named.element.hpp>
#include <core/elements/uuid.element.hpp>
#include <utils/generator/name.generator.hpp>
#include <core/interfaces/initializable.interface.hpp>
#include <core/interfaces/runnable.interface.hpp>

namespace Wasp
{
    class Controller : public I_Initializable,
                       public I_Runnable,
                       public NamedElement,
                       public UUIDElement
    {
    public:
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
        Controller(const Wasp::Types::TName &name = Wasp::Generators::NameGenerator::generate("CONTROLLER ")) : NamedElement(name)
        {
            Wasp::Logger::ConsoleLogger::STATIC_LOG((this->name() + " Constructed!").c_str());
        };
        std::atomic_bool initialized{false};
        std::atomic_bool running{false};
    };
};

#endif // !___WASP_CONTROLLER_HPP___