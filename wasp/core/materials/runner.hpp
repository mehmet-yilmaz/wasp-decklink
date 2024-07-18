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
        virtual void reset() = 0;
        std::atomic_bool &initialized()
        {
            return this->m_initialized;
        };
        std::atomic_bool &running()
        {
            return this->m_running;
        };

    protected:
        Runner(const Wasp::Types::TName &name_ = Wasp::Generators::NameGenerator::generate(" Runner")) : NamedElement(name_)
        {
            Wasp::Logger::ConsoleLogger::STATIC_LOG((this->name() + " Constructed!").c_str());
        };
        std::atomic_bool m_running{false};
        std::atomic_bool m_initialized{false};
    };

};

#endif // !___WASP_RUNNER_HPP___
