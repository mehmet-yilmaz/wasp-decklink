#ifndef _WEB_MODULE_HPP_
#define _WEB_MODULE_HPP_

#include <shared.hpp>
#include <web/web.runner.hpp>
#include <core/materials/module.hpp>
#include <web/server/server.module.hpp>

namespace Wasp
{
    namespace Bootstrap
    {
        const auto webRunner = std::make_shared<Wasp::WebRunner>("Web Runner");

        const std::map<const std::string, std::shared_ptr<Wasp::Runner>> webRunners{
            std::make_pair<const std::string, const std::shared_ptr<Wasp::Runner> &>(webRunner->uuid(), webRunner)};
        const std::map<const std::string, std::shared_ptr<Wasp::Module>> webImports{
            std::make_pair<const std::string, const std::shared_ptr<Wasp::Module> &>(webServerModule->uuid(), webServerModule)};

        const auto webModule = std::make_shared<Wasp::Module>(
            "WEB Module",
            webImports,
            webRunners,
            LOG_LEVEL);
    };
};

#endif // !_WEB_MODULE_HPP_
