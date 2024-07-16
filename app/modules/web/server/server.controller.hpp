#ifndef _WEB_SERVER_CONTROLLER_HPP_
#define _WEB_SEREVER_CONTROLLER_HPP_

#include <oatpp/web/server/api/ApiController.hpp>
#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/macro/component.hpp>
#include <web/server/data/message.dto.hpp>
#include <web/server/data/hello.dto.hpp>
#include <web/server/server.service.hpp>
#include <oatpp/oatpp-websocket/Handshaker.hpp>

namespace Wasp
{

#include OATPP_CODEGEN_BEGIN(ApiController)

    class WebServerController : public oatpp::web::server::api::ApiController
    {
    private:
        typedef WebServerController __ControllerType;
        OATPP_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, websocketConnectionHandler, "websocket");

    public:
        WebServerController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
            : oatpp::web::server::api::ApiController(objectMapper){};

        /**
         *  Inject @objectMapper component here as default parameter
         *  Do not return bare Controllable* object! use shared_ptr!
         */
        static std::shared_ptr<WebServerController> createShared(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>,
                                                                                 objectMapper))
        {
            return std::shared_ptr<WebServerController>(new WebServerController(objectMapper));
        }

        /**
         *  Hello World endpoint Coroutine mapped to the "/" (root)
         */
        ENDPOINT_ASYNC("GET", "/", Root){

            ENDPOINT_ASYNC_INIT(Root)

            /**
             *  Coroutine entrypoint act()
             *  returns Action (what to do next)
             */
            Action act() override{
                auto dto = HelloDto::createShared();
        Wasp::Bootstrap::webServerService->onHello();
        dto->message = "Hello Async!";
        dto->server = Header::Value::SERVER;
        dto->userAgent = request->getHeader(Header::USER_AGENT);
        return _return(controller->createDtoResponse(Status::CODE_200, dto));
    }
};
/**
 *  Echo body endpoint Coroutine. Mapped to "/body/string".
 *  Returns body received in the request
 */
ENDPOINT_ASYNC("GET", "/body/string", EchoStringBody){

    ENDPOINT_ASYNC_INIT(EchoStringBody)

        Action act() override{
            /* return Action to start child coroutine to read body */
            return request->readBodyToStringAsync().callbackTo(&EchoStringBody::returnResponse);
}

Action returnResponse(const oatpp::String &body)
{
    /* return Action to return created OutgoingResponse */
    return _return(controller->createResponse(Status::CODE_200, body));
}
}
;

/**
 *  Echo body endpoint Coroutine. Mapped to "/body/dto".
 *  Deserialize DTO reveived, and return same DTO
 *  Returns body as MessageDto received in the request
 */
ENDPOINT_ASYNC("GET", "/body/dto", EchoDtoBody){

    ENDPOINT_ASYNC_INIT(EchoDtoBody)

        Action act() override{
            return request->readBodyToDtoAsync<oatpp::Object<MessageDto>>(controller->getDefaultObjectMapper()).callbackTo(&EchoDtoBody::returnResponse);
}

Action returnResponse(const oatpp::Object<MessageDto> &body)
{
    return _return(controller->createDtoResponse(Status::CODE_200, body));
}
}
;

ENDPOINT_ASYNC("GET", "ws", WS){

    ENDPOINT_ASYNC_INIT(WS)

        Action act() override{
            Wasp::Logger::ConsoleLogger::STATIC_LOG("WS Get Request on controller!");
auto response = oatpp::websocket::Handshaker::serversideHandshake(request->getHeaders(), controller->websocketConnectionHandler);
return _return(response);
}
}
;

ENDPOINT_ASYNC("GET", "ws/{namespace}/{app}/*", WSApp){

    ENDPOINT_ASYNC_INIT(WSApp)

        Action act() override{

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
}
}
;

protected:
}
;
#include OATPP_CODEGEN_BEGIN(ApiController) //<-- End codegen
}
;

#endif // !_WEB_SERVER_CONTROLLER_HPP_
