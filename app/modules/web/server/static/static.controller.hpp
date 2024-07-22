#ifndef ___WASP_OATPP_WEB_STATIC_CONTROLLER_HPP___
#define ___WASP_OATPP_WEB_STATIC_CONTROLLER_HPP___

#include <web/server/static/static.service.hpp>
#include <oatpp/web/server/api/ApiController.hpp>
#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/macro/component.hpp>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>

namespace Wasp
{
#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen
    class StaticController : public oatpp::web::server::api::ApiController
    {
    private:
        typedef StaticController __ControllerType;

    public:
        StaticController(OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, objectMapper))
            : oatpp::web::server::api::ApiController(objectMapper)
        {
            this->setErrorHandler(nullptr);
        };
        static std::shared_ptr<StaticController> createShared(OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>,
                                                                              objectMapper))
        {
            return std::shared_ptr<StaticController>(new StaticController(objectMapper));
        };

        /*
        Static Wildcard Endpoint.
        This endpoint using for single page application hosting.
        Requested path would be search in the static folder and responsed in case of found.
        Otherwise, always responding with the configured index file.
        */
        // PS: If you need a specific static path you can define your endpoint and the use getFile method from the static.service

        ENDPOINT_ASYNC("GET", "*", Wildcard)
        {
            ENDPOINT_ASYNC_INIT(Wildcard)
            Action act() override
            {
                // Get the target file
                std::string path = request->getPathTail();
                if (path.empty())
                    path = "index";
                Wasp::Logger::ConsoleLogger::STATIC_LOG(std::string("Requested Path: " + request->getPathTail()).c_str());
                auto filename = Wasp::Bootstrap::staticService->getWildFile(path);
                auto file = oatpp::String::loadFromFile(filename.first.c_str());
                OATPP_ASSERT_HTTP(file.get() != nullptr, Status::CODE_404, "File not found");
                auto res = this->controller->createResponse(Status::CODE_200, file);
                res->putHeader(Header::CONTENT_TYPE, filename.second);
                Wasp::Logger::ConsoleLogger::STATIC_LOG(std::string("Responsed with Filename: " + filename.first + " - Content Type: " + filename.second).c_str());
                return _return(res);
            };
        };
    };
#include OATPP_CODEGEN_END(ApiController) //<- End Codegen
}

#endif // !___WASP_OATPP_WEB_STATIC_CONTROLLER_HPP___
