#ifndef ___WASP_STORE_HPP___
#define ___WASP_STORE_HPP___

#include <core/interfaces/initializable.interface.hpp>
#include <core/interfaces/runnable.interface.hpp>
#include <core/materials/provider.hpp>
#include <types/name.type.hpp>
#include <shared.hpp>

namespace Wasp
{
    class Store : public I_Initializable,
                  public I_Runnable,
                  public Provider
    {
    public:
        virtual ~Store() = default;
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
        Store(const Wasp::Types::TName &name) : Provider(name)
        {
            Wasp::Logger::ConsoleLogger::STATIC_LOG((this->name() + " Contructed!").c_str());
        };
        std::atomic_bool initialized{false};
        std::atomic_bool running{false};
    };
};

#endif // !___WASP_STORE_HPP___
