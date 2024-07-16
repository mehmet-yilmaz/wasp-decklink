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
            this->initialized = true;
        };
        virtual void run() override
        {
            this->running = true;
            char command;
            while (this->running)
            {
                // this->clear();
                this->printMenu();
                std::cout << "Please Enter Your Command: ";
                std::cin >> command;
                this->running = this->cliService->readCommand(command);
            };
        };
        CliRunner(const Wasp::Types::TName &name_, const std::shared_ptr<CliService> &cliService_) : Runner(name_), cliService(cliService_){};
        ~CliRunner(){};

    private:
        const std::shared_ptr<CliService> &cliService;
        void clear()
        {
            system("clear");
        };
        void printMenu()
        {
            std::cout << "--- CMD ----------- PROCCESS -----------" << std::endl;
            std::cout << "     A  -     ADD " << std::endl;
            std::cout << "     B  -     BRING" << std::endl;
            std::cout << "     Q  -     QUIT" << std::endl;
        };
    };
};

#endif // !_CLI_RUNNER_HPP_