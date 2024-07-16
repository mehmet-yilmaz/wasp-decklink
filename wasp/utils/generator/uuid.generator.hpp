#ifndef ___WASP_UUID_GENERATOR_HPP___
#define ___WASP_UUID_GENERATOR_HPP___

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>
#include <shared.hpp>

namespace Wasp
{
    namespace Generators
    {
        namespace Uuid
        {
            std::string generate()
            {
                std::stringstream temp;
                boost::uuids::uuid uuid = boost::uuids::random_generator()();
                temp << uuid;
                return temp.str();
            };
        };
    };
};

#endif // !___WASP_UUID_GENERATOR_HPP___
