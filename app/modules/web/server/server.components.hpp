#ifndef ___WASP_OATPP_WEB_SERVER_COMPONENT_HPP___
#define ___WASP_OATPP_WEB_SERVER_COMPONENT_HPP___

#include <oatpp/web/server/AsyncHttpConnectionHandler.hpp>
#include <oatpp/web/server/HttpRouter.hpp>
#include <oatpp/network/tcp/server/ConnectionProvider.hpp>
#include <oatpp/network/tcp/client/ConnectionProvider.hpp>
#include <oatpp/network/ConnectionProvider.hpp>
#include <oatpp/core/macro/component.hpp>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>

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
        ("http", []
         {
            OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router); // get Router component
            OATPP_COMPONENT(std::shared_ptr<oatpp::async::Executor>, executor); // get Async executor component
            return oatpp::web::server::AsyncHttpConnectionHandler::createShared(router, executor); }());

        OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::tcp::client::ConnectionProvider>, clientConnectionProvider)
        ([]
         { return oatpp::network::tcp::client::ConnectionProvider::createShared({"localhost", 8000, oatpp::network::Address::IP_4}); }());

    private:
    }; // Class WebServerComponent
} // namespace Wasp

#endif // !___WASP_OATPP_WEB_SERVER_COMPONENT_HPP___
