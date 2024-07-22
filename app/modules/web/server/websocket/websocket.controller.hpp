#ifndef ___WASP_OATPP_WEB_SERVER_WEBSOCKET_CONTROLLER_HPP___
#define ___WASP_OATPP_WEB_SERVER_WEBSOCKET_CONTROLLER_HPP___

#include <shared.hpp>
#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/macro/component.hpp>
#include <oatpp/web/server/api/ApiController.hpp>
#include <oatpp/oatpp-websocket/Handshaker.hpp>

namespace Wasp
{
#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen
    class WebsocketController : public oatpp::web::server::api::ApiController
    {
    private:
        typedef WebsocketController __ControllerType;
        OATPP_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, websocketConnectionHandler, "websocket");

    public:
        WebsocketController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
            : oatpp::web::server::api::ApiController(objectMapper)
        {
            this->setErrorHandler(nullptr);
        };

        /**
         *  Inject @objectMapper component here as default parameter
         *  Do not return bare Controllable* object! use shared_ptr!
         */
        static std::shared_ptr<WebsocketController> createShared(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>,
                                                                                 objectMapper))
        {
            return std::shared_ptr<WebsocketController>(new WebsocketController(objectMapper));
        };
        ENDPOINT_ASYNC("GET", "ws", WS)
        {

            ENDPOINT_ASYNC_INIT(WS)

            Action act() override
            {
                Wasp::Logger::ConsoleLogger::STATIC_LOG("WS Get Request on controller!");
                auto response = oatpp::websocket::Handshaker::serversideHandshake(request->getHeaders(), controller->websocketConnectionHandler);
                return _return(response);
            };
        };

        ENDPOINT_ASYNC("GET", "ws/{namespace}/{app}/*", WSApp)
        {
            ENDPOINT_ASYNC_INIT(WSApp)
            Action act() override
            {
                auto ns = request->getPathVariable("namespace");
                auto app = request->getPathVariable("app");
                auto conn = request->getQueryParameter("name");

                // OATPP_ASSERT_HTTP(conn, Status::CODE_400, "No name specified.");
                if (!conn)
                    conn = Wasp::Generators::NameGenerator::generate("WS-Connection");

                /* Websocket handshake */
                auto response = oatpp::websocket::Handshaker::serversideHandshake(request->getHeaders(), controller->websocketConnectionHandler);

                auto parameters = std::make_shared<oatpp::network::ConnectionHandler::ParameterMap>();

                (*parameters)["ns"] = ns;
                (*parameters)["app"] = app;
                (*parameters)["conn"] = conn;

                /* Set connection upgrade params */
                response->setConnectionUpgradeParameters(parameters);

                return _return(response);
            };
        };
    };
#include OATPP_CODEGEN_END(ApiController) //<- End Codegen
}

#endif //!___WASP_OATPP_WEB_SERVER_WEBSOCKET_CONTROLLER_HPP___
