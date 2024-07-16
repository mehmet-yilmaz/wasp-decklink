#ifndef ___WASP_NAME_GENERATOR_HPP___
#define ___WASP_NAME_GENERATOR_HPP___

#include <name.type.hpp>

namespace Wasp
{
    namespace Generators
    {
        class NameGenerator
        {
        public:
            static Wasp::Types::TName generate(const char *type = "UNKNOWN")
            {
                std::string name = std::string(type) + "-" + std::to_string(get_count());
                return name;
            };

        private:
            static int get_count()
            {
                static int m_counter = 0;
                return m_counter++;
            };
        };
    };
};

#endif // !___WASP_NAME_GENERATOR_HPP___
