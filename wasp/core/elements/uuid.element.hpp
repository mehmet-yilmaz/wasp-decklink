#ifndef ___WASP_UUID_ELEMENT___
#define ___WASP_UUID_ELEMENT___

#include <utils/generator/uuid.generator.hpp>

namespace Wasp
{
    class UUIDElement
    {
    public:
        const std::string uuid()
        {
            return this->m_uuid;
        };

    private:
        const std::string m_uuid{Generators::Uuid::generate()};
    };
};

#endif // !___WASP_UUID_ELEMENT___
