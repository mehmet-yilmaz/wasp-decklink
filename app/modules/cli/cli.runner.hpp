#ifndef _CLI_RUNNER_HPP_
#define _CLI_RUNNER_HPP_

#include <core/materials/runner.hpp>
#include <cli/cli.service.hpp>
#include <cli/cli.subjects.hpp>

namespace Wasp
{
    class CliRunner : public Runner
    {
    public:
        virtual void init() override
        {
            this->cliService->isModuleOn = true;
            this->m_initialized = true;
        };
        virtual void run() override
        {
            this->m_running = true;
            char command;
            while (this->cliService->isModuleOn)
            {
                // this->clear();
                // this->printMenu();
                // std::cout << "Please Enter Your Command: ";
                // std::cin >> command;
                // this->cliService->readCommand(command);
                this->cliService->acceptCommand();
            };
            this->reset();
        };

        virtual void reset() override
        {
            this->m_running = false;
            this->m_initialized = false;
        };
        CliRunner(const Wasp::Types::TName &name_, const std::shared_ptr<CliService> &cliService_) : Runner(name_), cliService(cliService_) {};
        ~CliRunner() {};

    private:
        const std::shared_ptr<CliService> &cliService;
    };
};

#endif // !_CLI_RUNNER_HPP_