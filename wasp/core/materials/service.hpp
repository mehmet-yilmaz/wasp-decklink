#ifndef ___WASP_SERVICE_HPP___
#define ___WASP_SERVICE_HPP___

#include <core/interfaces/initializable.interface.hpp>
#include <core/interfaces/runnable.interface.hpp>
#include <core/materials/provider.hpp>
#include <types/name.type.hpp>
#include <shared.hpp>

namespace Wasp
{
    class Service : public I_Initializable,
                    public I_Runnable,
                    public Provider
    {
    public:
        virtual ~Service() = default;
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
        Service(const Wasp::Types::TName &name) : Provider(name)
        {
            Wasp::Logger::ConsoleLogger::STATIC_LOG((this->name() + " Contructed!").c_str());
        };
        std::atomic_bool m_initialized{false};
        std::atomic_bool m_running{false};
    };
};

#endif // !___WASP_SERVICE_HPP___
