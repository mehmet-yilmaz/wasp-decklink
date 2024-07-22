#ifndef __WASP_OATPP_API_COMPONENTS_HPP__
#define __WASP_OATPP_API_COMPONENTS_HPP__

#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include <oatpp/core/macro/component.hpp>

namespace Wasp
{
    class ApiComponent
    {
    public:
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
    };
}

#endif // !__WASP_OATPP_API_COMPONENTS_HPP__