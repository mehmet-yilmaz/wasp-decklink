#ifndef ___WASP_OATPP_SYSTEM_NETWORK_API_CONTROLLER_HPP___
#define ___WASP_OATPP_SYSTEM_NETWORK_API_CONTROLLER_HPP___

#include <oatpp/web/server/api/ApiController.hpp>
#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/macro/component.hpp>
#include <network/network.service.hpp>
namespace Wasp
{
#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen
    class NetworkController : public oatpp::web::server::api::ApiController
    {
    private:
        typedef NetworkController __ControllerType;

    public:
        NetworkController(OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, objectMapper))
            : oatpp::web::server::api::ApiController(objectMapper)
        {
            this->setErrorHandler(nullptr);
        };
        static std::shared_ptr<NetworkController> createShared(OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>,
                                                                               objectMapper))
        {
            return std::shared_ptr<NetworkController>(new NetworkController(objectMapper));
        };

        ENDPOINT_ASYNC("GET", "/api/v1/system/network/interfacenames", networkInterfacesNames)
        {
            ENDPOINT_ASYNC_INIT(networkInterfacesNames)
            Action act() override
            {
                const std::map<std::string, std::string> interfaces = Wasp::Bootstrap::networkService->listInterfacesNames();
                auto res_vector = std::make_shared<oatpp::UnorderedMap<oatpp::String, oatpp::String>>()->createShared();
                for (const auto iface : interfaces)
                {
                    res_vector[iface.first] = iface.second;
                    //(std::make_pair<oatpp::String, oatpp::String>(iface.first, iface.second));
                }
                return _return(this->controller->createDtoResponse(Status::CODE_200, res_vector));
            };
        };

        ENDPOINT_ASYNC("GET", "/api/v1/system/network/interfaces", networkInterfaces)
        {
            ENDPOINT_ASYNC_INIT(networkInterfaces)
            Action act() override
            {
                const std::map<std::string, std::string> interfaces = Wasp::Bootstrap::networkService->listInterfaces();
                auto res_vector = std::make_shared<oatpp::UnorderedMap<oatpp::String, oatpp::String>>()->createShared();
                for (const auto iface : interfaces)
                {
                    res_vector[iface.first] = iface.second;
                    //(std::make_pair<oatpp::String, oatpp::String>(iface.first, iface.second));
                }
                return _return(this->controller->createDtoResponse(Status::CODE_200, res_vector));
            };
        };

        ENDPOINT_ASYNC("GET", "/api/v1/system/network/configuration/path", networkConfigurationPath)
        {
            ENDPOINT_ASYNC_INIT(networkConfigurationPath)
            Action act() override
            {
                const std::string response = Wasp::Bootstrap::networkService->getConfigurationPath();
                return _return(this->controller->createResponse(Status::CODE_200, response));
            };
        };
        ENDPOINT_ASYNC("GET", "/api/v1/system/network/configuration", networkConfiguration)
        {
            ENDPOINT_ASYNC_INIT(networkConfiguration)
            Action act() override
            {
                const std::string response = Wasp::Bootstrap::networkService->getConfiguration();
                return _return(this->controller->createResponse(Status::CODE_200, response));
            };
        };
        ENDPOINT_ASYNC("GET", "/api/v1/system/network/configuration/set", networkSetConfiguration)
        {
            ENDPOINT_ASYNC_INIT(networkSetConfiguration)
            Action act() override
            {
                const std::string destination = request->getQueryParameter("destination");
                const std::string configuration = request->getQueryParameter("configuration");
                const bool result = Wasp::Bootstrap::networkService->setConfigurationPath(destination, configuration);
                const oatpp::Boolean response = result;
                return _return(this->controller->createDtoResponse(Status::CODE_200, response));
            };
        };

        ENDPOINT_ASYNC("GET", "/api/v1/system/network/configuration/cancel", networkCancelConfiguration)
        {
            ENDPOINT_ASYNC_INIT(networkCancelConfiguration)
            Action act() override
            {
                const bool result = Wasp::Bootstrap::networkService->cancelConfigurationPath();
                const oatpp::Boolean response = result;
                return _return(this->controller->createDtoResponse(Status::CODE_200, response));
            };
        };

        ENDPOINT_ASYNC("GET", "/api/v1/system/network/configuration/try", networkTryConfiguration)
        {
            ENDPOINT_ASYNC_INIT(networkTryConfiguration)
            Action act() override
            {
                const uint32_t timeout = static_cast<uint32_t>(std::stoul(request->getQueryParameter("timeout")));
                const bool result = Wasp::Bootstrap::networkService->tryConfigurationPath(timeout);
                const oatpp::Boolean response = result;
                return _return(this->controller->createDtoResponse(Status::CODE_200, response));
            };
        };

        ENDPOINT_ASYNC("GET", "/api/v1/system/network/configuration/apply", networkApplyConfiguration)
        {
            ENDPOINT_ASYNC_INIT(networkApplyConfiguration)
            Action act() override
            {
                const bool result = Wasp::Bootstrap::networkService->applyConfigurationPath();
                const oatpp::Boolean response = result;
                return _return(this->controller->createDtoResponse(Status::CODE_200, response));
            };
        };
    };
#include OATPP_CODEGEN_END(ApiController) //<-- End codegen
}

#endif // !___WASP_OATPP_SYSTEM_NETWORK_API_CONTROLLER_HPP___