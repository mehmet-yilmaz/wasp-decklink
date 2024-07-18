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
        std::atomic_bool &initialized()
        {
            return this->m_initialized;
        };
        std::atomic_bool &running()
        {
            return this->m_running;
        };

    protected:
        Controller(const Wasp::Types::TName &name = Wasp::Generators::NameGenerator::generate("CONTROLLER ")) : NamedElement(name)
        {
            Wasp::Logger::ConsoleLogger::STATIC_LOG((this->name() + " Constructed!").c_str());
        };
        std::atomic_bool m_initialized{false};
        std::atomic_bool m_running{false};
    };
};

#endif // !___WASP_CONTROLLER_HPP___