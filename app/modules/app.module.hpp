#ifndef _APP_MODULE_HPP_
#define _APP_MODULE_HPP_

#include <core/materials/module.hpp>
#include <core/materials/runner.hpp>
#include <shared.hpp>
#include <cli/cli.module.hpp>
#include <web/web.module.hpp>
#include <system/system.module.hpp>
#include <media/media.module.hpp>

namespace Wasp
{
    // APP Module Global Initialization
    namespace Bootstrap
    {
        // Imports
        const std::map<const std::string, std::shared_ptr<Wasp::Module>> appImports{
            std::make_pair<const std::string, const std::shared_ptr<Wasp::Module> &>(cliModule->uuid() + "." + cliModule->name(), cliModule),
            std::make_pair<const std::string, const std::shared_ptr<Wasp::Module> &>(webModule->uuid() + "." + webModule->name(), webModule),
            std::make_pair<const std::string, const std::shared_ptr<Wasp::Module> &>(systemModule->uuid() + "." + systemModule->name(), systemModule),
            std::make_pair<const std::string, const std::shared_ptr<Wasp::Module> &>(mediaModule->uuid() + "." + mediaModule->name(), mediaModule)};
        // Runners
        const std::map<const std::string, std::shared_ptr<Wasp::Runner>> appRunners{};

        const auto App = std::make_shared<Wasp::Module>(
            "APPModule",
            appImports,
            appRunners,
            LOG_LEVEL);
    };
};
#endif // !_APP_MODULE_HPP_
