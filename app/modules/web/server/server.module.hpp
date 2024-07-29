#ifndef _WEB_SERVER_MODULE_HPP_
#define _WEB_SERVER_MODULE_HPP_

#include <core/materials/module.hpp>
#include <core/materials/runner.hpp>
#include <shared.hpp>
#include <web/server/server.runner.hpp>

namespace Wasp
{
    namespace Bootstrap
    {
        const auto webServerRunner = std::make_shared<Wasp::WebServerRunner>("Web Server Runner");
        const std::map<const std::string, std::shared_ptr<Wasp::Module>> webServerImports{};
        const std::map<const std::string, std::shared_ptr<Wasp::Runner>> webServerRunners{
            std::make_pair<const std::string, const std::shared_ptr<Wasp::Runner> &>(webServerRunner->uuid() + "." + webServerRunner->name(), webServerRunner)};

        const auto webServerModule = std::make_shared<Wasp::Module>(
            "WEB Server Module",
            webServerImports,
            webServerRunners,
            LOG_LEVEL);
    };
};

#endif // !_WEB_SERVER_MODULE_HPP_
