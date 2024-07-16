#ifndef ___WASP_LOGGER_INTERFACE_HPP___
#define ___WASP_LOGGER_INTERFACE_HPP___

#include <shared.hpp>

namespace Wasp
{
    namespace Logger
    {
        struct I_LOGGER
        {
            virtual void log(const char *message, const int level) = 0;
            virtual void log(const std::string &message, const int level) = 0;
            virtual void debug(const char *message, const int level) = 0;
            virtual void debug(const std::string &message, const int level) = 0;
            virtual void error(const char *message, const int level) = 0;
            virtual void error(const std::string &message, const int level) = 0;
        };
    };
};

#endif // !___WASP_LOGGER_INTERFACE_HPP___
