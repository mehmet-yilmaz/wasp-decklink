#ifndef _WEB_SERVER_RUNNER_HPP_
#define _WEB_SERVER_RUNNER_HPP_

#include <shared.hpp>
#include <core/materials/runner.hpp>
#include <oatpp/network/Server.hpp>
#include <web/server/server.components.hpp>
#include <web/server/server.controller.hpp>
#include <web/server/websocket/websocket-server.components.hpp>
#include <cli/cli.subjects.hpp>

namespace Wasp
{
    class WebServerRunner : public Runner
    {
    private:
        std::unique_ptr<WebServerComponent> components;
        std::unique_ptr<WSServerComponents> wsComponents;
        // = std::make_shared<WebServerComponent>();
        std::shared_ptr<oatpp::network::Server> server;
        std::atomic_bool run_server{true};
        // oatpp::network::Server *server;
        std::function<bool()> isRun = [&]()
        {
            return this->run_server.load();
        };

    public:
        ~WebServerRunner()
        {
            Wasp::Logger::ConsoleLogger::STATIC_LOG("WebServer Runner Deconstructing...");
        };

        virtual void init() override
        {
            this->components = std::make_unique<WebServerComponent>();
            this->wsComponents = std::make_unique<WSServerComponents>();
            /* Get router component */
            OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);
            /* Create MyController and add all of its endpoints to router */
            router->addController(WebServerController::createShared());

            /* Get connection handler component */
            OATPP_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, connectionHandler, "http");

            /* Get connection provider component */
            OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider);

            this->server = oatpp::network::Server::createShared(connectionProvider, connectionHandler);

            const auto &quitter = quitSubject->subscribe([&](const bool &value)
                                                         {
                if(value) {
                    Wasp::Logger::ConsoleLogger::STATIC_LOG("Quitter Has Been Triggered!!");
                    // this->stopServer();
                    this->run_server = false;
                } });

            this->m_initialized = true;
        };
        virtual void run() override
        {
            this->m_running = true;

            OATPP_LOGD("Server", "Running on port %s...", this->components->serverConnectionProvider.getObject()->getProperty("port").toString()->c_str());
            this->server->run(this->isRun);
            this->reset();
        };
        virtual void reset() override
        {
            /* Server has been stopped and the webserver runner returning to the default state */
            this->m_running = false;
            /* Get connection provider component */
            OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider);
            connectionProvider->stop(); // Do not more provide connections to the stopped server

            /* Get connection handler component */
            OATPP_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, connectionHandler, "http");
            connectionHandler->stop(); // Do not more accept connections which there is no running server to handle them

            OATPP_COMPONENT(std::shared_ptr<oatpp::async::Executor>, executor); // get executor
            executor->waitTasksFinished();
            executor->stop(); // wait all the coroutines;
            executor->join(); // joint executor threads.

            this->components.reset(); // Clear all components to prevent leakage
            this->wsComponents.reset();

            this->m_initialized = false;
        };
        WebServerRunner(const Wasp::Types::TName &name) : Runner(name)
        {
            this->m_initialized = false;
            this->m_running = false;
        };
    };
};
#endif // !_WEB_SERVER_RUNNER_HPP_