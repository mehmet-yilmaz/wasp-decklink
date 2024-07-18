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
            Wasp::Logger::ConsoleLogger::STATIC_LOG(("Total Number of Web Components: " + std::to_string(oatpp::base::Environment::getObjectsCount())).c_str());
            Wasp::Logger::ConsoleLogger::STATIC_LOG(("Total number of created Web Objects: " + std::to_string(oatpp::base::Environment::getObjectsCreated())).c_str());
            oatpp::base::Environment::destroy();
        };
        virtual void init() override
        {
            this->m_initialized = true;
        };
        virtual void run() override
        {
            this->m_running = true;
            // this->reset();
        };
        virtual void reset() override
        {
            this->m_running = false;
            this->m_initialized = false;
        };
        WebRunner(const Wasp::Types::TName &name) : Runner(name)
        {
            this->m_initialized = false;
            this->m_running = false;
            oatpp::base::Environment::init();
            Wasp::Logger::ConsoleLogger::STATIC_LOG("OATPP Initialized!");
        };
    };
};
#endif // !_WEB_RUNNER_HPP_