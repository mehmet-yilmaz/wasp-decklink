#ifndef _WEB_SERVER_RUNNER_HPP_
#define _WEB_SERVER_RUNNER_HPP_

#include <shared.hpp>
#include <core/materials/runner.hpp>
#include <oatpp/network/Server.hpp>
#include <web/server/server.components.hpp>
#include <web/server/server.controller.hpp>
#include <cli/cli.subjects.hpp>

namespace Wasp
{
    class WebServerRunner : public Runner
    {
    private:
        WebServerComponent *components;
        // std::shared_ptr<oatpp::web::server::HttpRouter> router;

        /* create server */
        oatpp::network::Server *server;

        void stopServer()
        {
            if (this->server && this->server->getStatus() != this->server->STATUS_DONE)
            {
                Wasp::Logger::ConsoleLogger::STATIC_LOG(("Total Number of Web Components: " + std::to_string(oatpp::base::Environment::getObjectsCount())).c_str());
                Wasp::Logger::ConsoleLogger::STATIC_LOG(("Total number of created Web Objects: " + std::to_string(oatpp::base::Environment::getObjectsCreated())).c_str());
                this->server->stop();
            }
        };

    public:
        ~WebServerRunner()
        {

            this->stopServer();

            // Wasp::Logger::ConsoleLogger::STATIC_LOG
            // ("Web Environment Destroying...");
            // oatpp::base::Environment::destroy();
            // Wasp::Logger::ConsoleLogger::STATIC_LOG
            // ("Web Environment Destroyed!!");
        };
        virtual void init() override
        {

            this->initialized = true;
            // oatpp::base::Environment::init();
            this->components = new WebServerComponent();
            // this->router = std::make_shared<oatpp::web::server::HttpRouter>();

            /* Get router component */
            OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);

            /* Create MyController and add all of its endpoints to router */
            router->addController(WebServerController::createShared());

            this->server = new oatpp::network::Server(this->components->serverConnectionProvider.getObject(), this->components->serverConnectionHandler.getObject());

            const auto &quitter = quitSubject->subscribe([&](const bool &value)
                                                         {
                if(value) {
                    Wasp::Logger::ConsoleLogger::STATIC_LOG("Quitter Has Been Triggered!!");
                    this->stopServer();
                } });
        };
        virtual void run() override
        {
            this->running = true;

            OATPP_LOGD("Server", "Running on port %s...", this->components->serverConnectionProvider.getObject()->getProperty("port").toString()->c_str());
            this->server->run();
        };
        WebServerRunner(const Wasp::Types::TName &name_) : Runner(name_)
        {
            this->initialized = false;
            this->running = false;
        };
    };
};
#endif // !_WEB_SERVER_RUNNER_HPP_