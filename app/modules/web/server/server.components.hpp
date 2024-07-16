#ifndef ___WASP_OATPP_WEB_SERVER_COMPONENT_HPP___
#define ___WASP_OATPP_WEB_SERVER_COMPONENT_HPP___

#include <oatpp/web/server/AsyncHttpConnectionHandler.hpp>
#include <oatpp/web/server/HttpRouter.hpp>
#include <oatpp/network/tcp/server/ConnectionProvider.hpp>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include <oatpp/core/macro/component.hpp>

#include <oatpp/oatpp-websocket/AsyncWebSocket.hpp>
#include <oatpp/oatpp-websocket/AsyncConnectionHandler.hpp>
#include <web/server/websocket/websocket-server.namespace.hpp>

namespace Wasp
{
    class WebServerComponent
    {
    public:
        /**
         * Create Async Executor
         */
        OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::async::Executor>, executor)
        ([]
         { return std::make_shared<oatpp::async::Executor>(
               9 /* Data-Processing threads */,
               2 /* I/O threads */,
               1 /* Timer threads */
           ); }());

        /**
         *  Create ConnectionProvider component which listens on the port
         */
        OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, serverConnectionProvider)
        ([]
         {
            /* non_blocking connections should be used with AsyncHttpConnectionHandler for AsyncIO */
            return oatpp::network::tcp::server::ConnectionProvider::createShared({"0.0.0.0", 8000, oatpp::network::Address::IP_4}); }());

        /**
         *  Create Router component
         */
        OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, httpRouter)
        ([]
         { return oatpp::web::server::HttpRouter::createShared(); }());

        /**
         *  Create ConnectionHandler component which uses Router component to route requests
         */
        OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, serverConnectionHandler)
        ([]
         {
            OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router); // get Router component
            OATPP_COMPONENT(std::shared_ptr<oatpp::async::Executor>, executor); // get Async executor component
            return oatpp::web::server::AsyncHttpConnectionHandler::createShared(router, executor); }());

        /**
         *  Create ObjectMapper component to serialize/deserialize DTOs in Contoller's API
         */
        OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, apiObjectMapper)
        ([]
         {
            auto serializerConfig = oatpp::parser::json::mapping::Serializer::Config::createShared();
            auto deserializerConfig = oatpp::parser::json::mapping::Deserializer::Config::createShared();
            deserializerConfig->allowUnknownFields = false;
            auto objectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared(serializerConfig, deserializerConfig);
            return objectMapper; }());

        /**
         *  Create websocket connection handler
         */

        OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, websocketConnectionHandler)
        ("websocket", []
         {
        OATPP_COMPONENT(std::shared_ptr<oatpp::async::Executor>, executor);
        auto connectionHandler = oatpp::websocket::AsyncConnectionHandler::createShared(executor);
        connectionHandler->setSocketInstanceListener(std::make_shared<WSServerNamespace>());
        return connectionHandler; }());
    };
} // namespace Wasp

#endif // !___WASP_OATPP_WEB_SERVER_COMPONENT_HPP___
