#ifndef ___WASP_OATPP_MEDIA_API_CONTROLLER_HPP___
#define ___WASP_OATPP_MEDIA_API_CONTROLLER_HPP___

#include <oatpp/web/server/api/ApiController.hpp>
#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/macro/component.hpp>
#include <media/decklink/decklink.service.hpp>
namespace Wasp
{
#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen
    class MediaController : public oatpp::web::server::api::ApiController
    {
    private:
        typedef MediaController __ControllerType;

    public:
        MediaController(OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, objectMapper))
            : oatpp::web::server::api::ApiController(objectMapper)
        {
            this->setErrorHandler(nullptr);
        };
        static std::shared_ptr<MediaController> createShared(OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>,
                                                                             objectMapper))
        {
            return std::shared_ptr<MediaController>(new MediaController(objectMapper));
        };

        ENDPOINT_ASYNC("GET", "/api/v1/media/decklink/cards", DecklinkCards)
        {
            ENDPOINT_ASYNC_INIT(DecklinkCards)
            Action act() override
            {
                const std::vector<std::string> cards = Wasp::Bootstrap::decklinkService->getCardList();
                auto res_vector = std::make_shared<oatpp::Vector<oatpp::String>>()->createShared();
                for (const auto &card : cards)
                {
                    res_vector->push_back(card);
                }
                return _return(this->controller->createDtoResponse(Status::CODE_200, res_vector));
            };
        };
    };
#include OATPP_CODEGEN_END(ApiController) //<-- End codegen
}

#endif // !___WASP_OATPP_MEDIA_API_CONTROLLER_HPP___