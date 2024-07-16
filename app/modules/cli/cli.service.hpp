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
            this->initialized = true;
        };
        virtual void run() override
        {
            this->running = true;
        };
        virtual ~CliService() override{};
        void quit()
        {
            quitSubject->next(true);
        };
        const bool readCommand(const char &command)
        {
            switch (command)
            {
            case 'Q':
                this->quit();
                return false;
            case 'A':
                this->add();
                return true;
            default:
                return true;
            };
        };
        void add()
        {
            addSubject->next(1);
            Wasp::Logger::ConsoleLogger::STATIC_LOG("CLI Service Add...");
        };
        CliService(const Wasp::Types::TName &name) : Service(name){};

    private:
    };

    // CLI Service Global Initialization!
    namespace Bootstrap
    {
        const auto cliService = std::make_shared<Wasp::CliService>("CLI Service");
    };
};

#endif // !_APP_SERVICE_HPP_
