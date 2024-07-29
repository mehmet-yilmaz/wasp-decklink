#ifndef _WEB_SERVER_RUNNER_HPP_
#define _WEB_SERVER_RUNNER_HPP_

#include <shared.hpp>
#include <core/materials/runner.hpp>
#include <oatpp/network/Server.hpp>
#include <web/server/server.components.hpp>
#include <web/server/server.controller.hpp>
#include <web/server/websocket/websocket.controller.hpp>
#include <web/server/websocket/websocket.components.hpp>
#include <web/server/api/api.component.hpp>
#include <web/server/api/api.controller.hpp>
#include <system/network/network.controller.hpp>
#include <media/media.controller.hpp>
#include <web/server/static/static.controller.hpp>
#include <cli/cli.subjects.hpp>

namespace Wasp
{
    class WebServerRunner : public Runner
    {
    private:
        std::unique_ptr<WebServerComponent> serverComponents;
        std::unique_ptr<ApiComponent> apiComponents;
        std::unique_ptr<WSComponents> wsComponents;
        std::shared_ptr<oatpp::network::Server> server;
        std::atomic_bool run_server{true};
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
            this->serverComponents = std::make_unique<WebServerComponent>();
            this->apiComponents = std::make_unique<ApiComponent>();
            this->wsComponents = std::make_unique<WSComponents>();

            /* Get router component */
            OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);
            /* Create MyController and add all of its endpoints to router */
            router->addController(WebServerController::createShared());
            router->addController(WebsocketController::createShared());
            router->addController(WaspApiController::createShared());
            router->addController(NetworkController::createShared());
            router->addController(MediaController::createShared());
            router->addController(StaticController::createShared());

            router->logRouterMappings();

            /* Get connection handler component */
            OATPP_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, connectionHandler, "http");

            /* Get connection provider component */
            OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider);

            this->server = oatpp::network::Server::createShared(connectionProvider, connectionHandler);

            const auto &quitter = quitSubject->subscribe([&](const bool &value)
                                                         {
                if(value) {
                    Wasp::Logger::ConsoleLogger::STATIC_LOG("Quitter Has Been Triggered!!");
                    this->run_server = false;
                } });

            this->m_initialized = true;
        };
        virtual void run() override
        {
            this->m_running = true;

            OATPP_LOGD("Server", "Running on port %s...", this->serverComponents->serverConnectionProvider.getObject()->getProperty("port").toString()->c_str());
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

            this->wsComponents.reset();
            this->apiComponents.reset();
            this->serverComponents.reset(); // Clear all components to prevent leakage

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