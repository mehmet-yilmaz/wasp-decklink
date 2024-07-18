#ifndef _WEBSOCKET_SERVER_NAMESPACE_HPP_
#define _WEBSOCKET_SERVER_NAMESPACE_HPP_

#include <oatpp/oatpp-websocket/AsyncConnectionHandler.hpp>
#include <shared.hpp>
#include <web/server/websocket/websocket-server.application.hpp>
#include <utils/logger/console.logger.hpp>
#include <utils/generator/name.generator.hpp>
#include <web/server/websocket/websocket-server.connection.hpp>

namespace Wasp
{
    class WSServerNamespace : public oatpp::websocket::AsyncConnectionHandler::SocketInstanceListener
    {
    private:
    public:
        std::atomic<v_int32> m_connectionIdCounter;
        std::unordered_map<oatpp::String, std::shared_ptr<WSServerApplication>> m_applications;
        std::mutex m_applicationsMutex;

    public:
        WSServerNamespace() : m_connectionIdCounter(0)
        {
            getOrCreateApplication("root");
        };

        v_int32 obtainNewConnectionId()
        {
            return m_connectionIdCounter++;
        };

        std::shared_ptr<WSServerApplication> getOrCreateApplication(const oatpp::String &applicationName)
        {
            std::lock_guard<std::mutex> lock(m_applicationsMutex);
            std::shared_ptr<WSServerApplication> &application = m_applications[applicationName];
            if (!application)
            {
                application = std::make_shared<WSServerApplication>(applicationName);
            }
            return application;
        };

    public:
        /**
         *  Called when socket is created
         */
        void onAfterCreate_NonBlocking(const std::shared_ptr<AsyncWebSocket> &socket, const std::shared_ptr<const ParameterMap> &params) override
        {
            Wasp::Logger::ConsoleLogger::STATIC_LOG("Websocket Connection Attempt!");

            if (params && params->size())
            {
                Wasp::Logger::ConsoleLogger::STATIC_LOG(("Number of parameters: " + std::to_string(params->size())).c_str());
                for (const auto param : *params)
                {
                    Wasp::Logger::ConsoleLogger::STATIC_LOG(("Websocket Connection Parameter: " + *param.first + ": " + *param.second).c_str());
                };
                auto ns = params->find("ns")->second;
                auto appName = params->find("app")->second;
                auto connName = params->find("conn")->second;
                auto application = getOrCreateApplication(appName);

                auto connection = std::make_shared<WSServerConnection>(socket, application, connName, obtainNewConnectionId());
                socket->setListener(connection);
                connection->sendMessage("You have successfully connected, your id: " + connection->uuid());

                application->addConnection(connection);
                application->sendMessage(connName + " joined " + appName);
            }
            else
            {
                auto application = getOrCreateApplication("root");
                auto connection = std::make_shared<WSServerConnection>(socket, application, Wasp::Generators::NameGenerator::generate("WS-Connection"), obtainNewConnectionId());
                socket->setListener(connection);
                connection->sendMessage("You have successfully connected, your id: " + connection->uuid());
            }
        };

        /**
         *  Called before socket instance is destroyed.
         */
        void onBeforeDestroy_NonBlocking(const std::shared_ptr<AsyncWebSocket> &socket) override
        {
            auto connection = std::static_pointer_cast<WSServerConnection>(socket->getListener());
            if (connection)
            {
                auto connName = connection->getName();
                auto application = connection->getApplication();
                if (application)
                {
                    application->removeConnectionById(connection->uuid());
                    application->sendMessage(connName + " left the room");
                }
            }

            /* Remove circle `std::shared_ptr` dependencies */
            socket->setListener(nullptr);
        };
    };
};

#endif // !_WEBSOCKET_NAMESPACE_HPP_