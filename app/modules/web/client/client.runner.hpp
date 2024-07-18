#ifndef _WEB_CLIENT_RUNNER_HPP_
#define _WEB_CLIENT_RUNNER_HPP_

#include <shared.hpp>
#include <core/materials/runner.hpp>
#include <oatpp/network/tcp/client/ConnectionProvider.hpp>

namespace Wasp
{
    class WebClientRunner : public Runner
    {
        WebClientRunner(const Wasp::Types::TName &name) : Runner(name){

                                                          };
        virtual ~WebClientRunner() override{};
        virtual void init() override
        {
            this->m_initialized = true;
        };
        virtual void run() override
        {
            this->m_running = true;
        };
    };
};

#endif // !_WEB_CLIENT_RUNNER_HPP_
