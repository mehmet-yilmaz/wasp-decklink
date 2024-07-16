#ifndef _WEB_RUNNER_HPP_
#define _WEB_RUNNER_HPP_

#include <shared.hpp>
#include <core/materials/runner.hpp>
#include <oatpp/network/Server.hpp>
#include <cli/cli.subjects.hpp>

namespace Wasp
{
    class WebRunner : public Runner
    {
    private:
    public:
        ~WebRunner()
        {
            oatpp::base::Environment::destroy();
        };
        virtual void init() override
        {
            this->initialized = true;
        };
        virtual void run() override
        {
            this->running = true;
        };
        WebRunner(const Wasp::Types::TName &name_) : Runner(name_)
        {
            this->initialized = false;
            this->running = false;
            oatpp::base::Environment::init();
        };
    };
};
#endif // !_WEB_RUNNER_HPP_