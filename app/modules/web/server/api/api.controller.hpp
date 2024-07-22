#ifndef ___WASP_OATPP_WEB_SERVER_API_CONTROLLER_HPP___
#define ___WASP_OATPP_WEB_SERVER_API_CONTROLLER_HPP___

#include <oatpp/web/server/api/ApiController.hpp>
#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/macro/component.hpp>
#include <web/server/data/hello.dto.hpp>
#include <web/server/data/message.dto.hpp>
#include <web/server/api/api.service.hpp>
namespace Wasp
{
#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen
    class WaspApiController : public oatpp::web::server::api::ApiController
    {
    private:
        typedef WaspApiController __ControllerType;

    public:
        WaspApiController(OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, objectMapper))
            : oatpp::web::server::api::ApiController(objectMapper)
        {
            this->setErrorHandler(nullptr);
        };
        static std::shared_ptr<WaspApiController> createShared(OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>,
                                                                               objectMapper))
        {
            return std::shared_ptr<WaspApiController>(new WaspApiController(objectMapper));
        };

        ENDPOINT_ASYNC("GET", "/api/v1/", ApiRoot)
        {
            ENDPOINT_ASYNC_INIT(ApiRoot)
            Action act() override
            {
                auto dto = Wasp::HelloDto::createShared();
                dto->message = Wasp::Bootstrap::apiService->onHello(request->getHeader(Header::USER_AGENT));
                dto->server = Header::Value::SERVER;
                dto->userAgent = request->getHeader(Header::USER_AGENT);
                Wasp::Logger::ConsoleLogger::STATIC_LOG(dto->message->c_str());
                Wasp::Logger::ConsoleLogger::STATIC_LOG(dto->server->c_str());
                Wasp::Logger::ConsoleLogger::STATIC_LOG(dto->userAgent->c_str());

                return _return(this->controller->createDtoResponse(Status::CODE_200, dto));
            };
        };
    };
#include OATPP_CODEGEN_END(ApiController) //<-- End codegen
}

#endif // !___WASP_OATPP_WEB_SERVER_API_CONTROLLER_HPP___