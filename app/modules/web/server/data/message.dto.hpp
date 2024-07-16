#ifndef _MESSAGE_DTO_HPP_
#define _MESSAGE_DTO_HPP_

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

namespace Wasp
{

#include OATPP_CODEGEN_BEGIN(DTO)
    /**
     *  Data Transfer Object. Object containing fields only.
     *  Used in API for serialization/deserialization and validation
     */
    class MessageDto : public oatpp::DTO
    {

        DTO_INIT(MessageDto, DTO)

        DTO_FIELD(Int32, statusCode);
        DTO_FIELD(String, message);
    };

#include OATPP_CODEGEN_END(DTO)
};
#endif /* _MESSAGE_DTO_HPP_ */