#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#include <common.hpp>

namespace Wasp
{
    namespace Utils
    {
        static std::time_t timestamp = std::time(nullptr);
        const std::string get_timestamp()
        {
            std::stringstream timecode{};
            auto t = std::time(nullptr);
            auto tm = *std::localtime(&t);
            timecode << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
            return timecode.str();
        };

        const std::string generate_uuid()
        {
            try
            {
                auto _uuid = boost::uuids::random_generator()();
                const std::string uuid{boost::uuids::to_string(_uuid)};
                return uuid;
            }
            catch (...)
            {
                std::cout << "HH" << std::endl;
                return NULL;
            }
        };

        const char *generate_c_uuid()
        {
            boost::uuids::uuid _uuid = boost::uuids::random_generator()();
            const std::string id{boost::uuids::to_string(_uuid)};
            const char *uuid = id.c_str();
            return uuid;
        };

        bool isExist(const std::string &path)
        {
            struct stat buffer;
            return (stat(name.c_str(), &buffer) == 0);
        }
    }
}

#endif // !__UTILS_HPP__