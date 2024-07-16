#ifndef ___WASP_TIME_GENERATOR_HPP___
#define ___WASP_TIME_GENERATOR_HPP___

#include <shared.hpp>

namespace Wasp
{
    namespace Generators
    {
        namespace Timestamp
        {
            char *generate()
            {
                const auto now = std::chrono::system_clock::now();
                const std::time_t ts = std::chrono::system_clock::to_time_t(now);
                return strtok(std::ctime(&ts), "\n");
            };
            // std::time_t generate() {
            //     const auto now = std::chrono::system_clock::now();
            //     return std::chrono::system_clock::to_time_t(now);
            // };
            // std::string generate()  {
            //     std::stringstream ss{};
            //     auto t = std::time(nullptr);
            //     auto tm = *std::localtime(&t);
            //     ss << std::put_time(&tm, "%Y-%m-%dT%H:%M:%S.%z%Z");
            //     return ss.str();
            // };
        };
    };
};

#endif //  ___WASP_TIME_GENERATOR_HPP___