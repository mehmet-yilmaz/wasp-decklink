#ifndef _HELLO_DTO_HPP_
#define _HELLO_DTO_HPP_

#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/Types.hpp>

namespace Wasp
{

#include OATPP_CODEGEN_BEGIN(DTO)
    /**
     *  Data Transfer Object. Object containing fields only.
     *  Used in API for serialization/deserialization and validation
     */
    class HelloDto : public oatpp::DTO
    {
        DTO_INIT(HelloDto, DTO)
        DTO_FIELD(String, userAgent, "user-agent");
        DTO_FIELD(String, message);
        DTO_FIELD(String, server);
    };

#include OATPP_CODEGEN_END(DTO)
}
#endif /* _HELLO_DTO_HPP_ */