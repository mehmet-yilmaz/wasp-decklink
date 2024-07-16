#ifndef ___WASP_CONSOLE_LOGGER_HPP___
#define ___WASP_CONSOLE_LOGGER_HPP___

#include <logger.interface.hpp>
#include <utils/generator/timstamp.generator.hpp>
#include <name.type.hpp>

namespace Wasp
{
    namespace Logger
    {
        class ConsoleLogger : public I_LOGGER
        {
        public:
            static void STATIC_LOG(const char *message)
            {
                std::cout << "[LOG-STATIC] - [" << Wasp::Generators::Timestamp::generate() << "] - " << message << std::endl;
            };
            virtual void log(const char *message, const int level = 3) override
            {
                console_log("LOG", message, level);
            };
            virtual void log(const std::string &message, const int level = 3) override
            {
                console_log("LOG", message, level);
            };
            virtual void debug(const char *message, const int level = 3) override
            {
                console_log("DEBUG", message, level);
            };
            virtual void debug(const std::string &message, const int level = 3) override
            {
                console_log("DEBUG", message, level);
            };
            virtual void error(const char *message, const int level = 3) override
            {
                console_log("ERROR", message, level);
            };
            virtual void error(const std::string &message, const int level = 3) override
            {
                console_log("ERROR", message, level);
            };
            ConsoleLogger(const Wasp::Types::TName parent, const int level = 3) : m_parent(parent), m_level(level)
            {
                this->debug("Logger Constructed - Logger Type: Console");
            };

        private:
            const int m_level;
            const Wasp::Types::TName m_parent;
            void console_log(const char *type, const char *message, const int &level)
            {
                if (m_level >= level)
                    std::cout << "[" << type << "] [" << Wasp::Generators::Timestamp::generate() << "] [" << this->m_parent << "] [" << level << "] - " << message << std::endl;
            };
            void console_log(const char *type, const std::string &message, const int &level)
            {
                if (m_level >= level)
                    std::cout << "[" << type << "] [" << Wasp::Generators::Timestamp::generate() << "] [" << this->m_parent << "] [" << level << "] - " << message << std::endl;
            };
        };
    };
};

#endif // !___WASP_CONSOLE_LOGGER_HPP___
