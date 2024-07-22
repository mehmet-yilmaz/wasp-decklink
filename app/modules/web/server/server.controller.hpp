#ifndef _WEB_SERVER_CONTROLLER_HPP_
#define _WEB_SERVER_CONTROLLER_HPP_

#include <oatpp/web/server/api/ApiController.hpp>
#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/macro/component.hpp>
#include <web/server/data/hello.dto.hpp>
#include <web/server/data/message.dto.hpp>
#include <web/server/server.service.hpp>
namespace Wasp
{

#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen

    class WebServerController : public oatpp::web::server::api::ApiController
    {
    private:
        typedef WebServerController __ControllerType;

    public:
        WebServerController(OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, objectMapper))
            : oatpp::web::server::api::ApiController(objectMapper)
        {
            this->setErrorHandler(nullptr);
        };

        /**
         *  Inject @objectMapper component here as default parameter
         *  Do not return bare Controllable* object! use shared_ptr!
         */
        static std::shared_ptr<WebServerController> createShared(OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>,
                                                                                 objectMapper))
        {
            return std::shared_ptr<WebServerController>(new WebServerController(objectMapper));
        }

        /**
         *  Echo body endpoint Coroutine. Mapped to "/body/string".
         *  Returns body received in the request
         */
        ENDPOINT_ASYNC("GET", "/body/string", EchoStringBody)
        {

            /**
             *  Coroutine entrypoint act()
             *  returns Action (what to do next)
             */
            ENDPOINT_ASYNC_INIT(EchoStringBody)

            Action act() override
            {
                /* return Action to start child coroutine to read body */
                return request->readBodyToStringAsync().callbackTo(&EchoStringBody::returnResponse);
            };

            Action
            returnResponse(const oatpp::String &body)
            {
                /* return Action to return created OutgoingResponse */
                return _return(controller->createResponse(Status::CODE_200, body));
            };
        };

        /**
         *  Echo body endpoint Coroutine. Mapped to "/body/dto".
         *  Deserialize DTO reveived, and return same DTO
         *  Returns body as MessageDto received in the request
         */
        ENDPOINT_ASYNC("GET", "/body/dto", EchoDtoBody)
        {

            ENDPOINT_ASYNC_INIT(EchoDtoBody)

            Action act() override
            {
                return request->readBodyToDtoAsync<oatpp::Object<MessageDto>>(controller->getDefaultObjectMapper()).callbackTo(&EchoDtoBody::returnResponse);
            };

            Action returnResponse(const oatpp::Object<MessageDto> &body)
            {
                return _return(controller->createDtoResponse(Status::CODE_200, body));
            };
        };

    protected:
    };
#include OATPP_CODEGEN_END(ApiController) //<-- End codegen
};

#endif // !_WEB_SERVER_CONTROLLER_HPP_
