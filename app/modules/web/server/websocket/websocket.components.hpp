#ifndef __WASP_OATPP_WEBSOCKET_COMPONENTS_HPP__
#define __WASP_OATPP_WEBSOCKET_COMPONENTS_HPP__

#include <oatpp/oatpp-websocket/AsyncWebSocket.hpp>
#include <oatpp/oatpp-websocket/AsyncConnectionHandler.hpp>
#include <web/server/websocket/websocket.namespace.hpp>

namespace Wasp
{
    class WSComponents
    {
    public:
        /**
         *  Create websocket connection handler
         */

        OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, websocketConnectionHandler)
        ("websocket", []
         {
        OATPP_COMPONENT(std::shared_ptr<oatpp::async::Executor>, executor);
        auto connectionHandler = oatpp::websocket::AsyncConnectionHandler::createShared(executor);
        connectionHandler->setSocketInstanceListener(std::make_shared<WSNamespace>());
        return connectionHandler; }());
    };
}

#endif //!__WASP_OATPP_WEBSOCKET_COMPONENTS_HPP__