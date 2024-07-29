#ifndef _CLI_SERVICE_HPP_
#define _CLI_SERVICE_HPP_

#include <core/materials/service.hpp>
#include <core/materials/module.hpp>
#include <types/name.type.hpp>
#include <shared.hpp>
#include <cli.subjects.hpp>

namespace Wasp
{
    class CliService : public Service
    {
    public:
        virtual void init() override
        {
            this->m_initialized = true;
        };
        virtual void run() override
        {
            this->m_running = true;
        };
        virtual ~CliService() override {};
        void quit()
        {
            quitSubject->next(true);
            this->isModuleOn = false;
        };
        void acceptCommand()
        {
            // struct timeval timeout
            // {
            //     5, 0
            // };
            // fd_set fds;
            // FD_ZERO(&fds);
            // FD_SET(STDIN_FILENO, &fds);
            // // this->clear();
            // this->printMenu();
            // char command = select(1, &fds, NULL, NULL, &timeout);
            // this->readCommand(command);
            this->printMenu();
            char command;
            std::cin >> command;
            this->readCommand(command);
        };

        void add()
        {
            addSubject->next(1);
            Wasp::Logger::ConsoleLogger::STATIC_LOG("CLI Service Add...");
        };
        CliService(const Wasp::Types::TName &name) : Service(name) {};
        std::atomic_bool isModuleOn{false};

    private:
        void clear()
        {
            system("clear");
        };
        void printMenu()
        {
            printf("\tCMD \t\t PROCCESS\n");
            printf("-------------------------------\n");
            printf("\t A \t\t ADD\n");
            printf("\t B \t\t BRING\n");
            printf("\t Q \t\t QUIT\n");
            printf("\t Please Enter Your Command: ");
        };
        void readCommand(const char &command)
        {
            switch (command)
            {
            case 'Q':
                this->quit();
                break;
            case 'A':
                this->add();
                break;
            default:
                break;
            };
        };
    };

    // CLI Service Global Initialization!
    namespace Bootstrap
    {
        const auto cliService = std::make_shared<Wasp::CliService>("CLI Service");
    };
};

#endif // !_APP_SERVICE_HPP_
