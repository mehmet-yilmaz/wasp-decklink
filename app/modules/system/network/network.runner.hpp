#ifndef ___WASP_NETWORK_MODULE_RUNNER_HPP___
#define ___WASP_NETWORK_MODULE_RUNNER_HPP___

#include <core/materials/runner.hpp>
#include <network/network.service.hpp>

namespace Wasp
{
    class NetworkRunner : public Runner
    {
    public:
        NetworkRunner(const Wasp::Types::TName &name, const std::shared_ptr<Wasp::NetworkService> &networkService) : Wasp::Runner(name), networkService(networkService) {};
        virtual void init() override
        {
            this->m_initialized = true;
            this->networkService->init();
            this->networkService->listInterfaces();
        };
        virtual void run() override
        {
            this->m_running = true;
        }
        virtual void reset() override
        {
            this->m_initialized = false;
            this->m_running = false;
        };

    private:
        const std::shared_ptr<Wasp::NetworkService> networkService;

    protected:
    };

    namespace Bootstrap
    {
        const auto networkRunner = std::make_shared<Wasp::NetworkRunner>("NetworkRunner", networkService);
    };
}

#endif // !___WASP_NETWORK_MODULE_RUNNER_HPP___