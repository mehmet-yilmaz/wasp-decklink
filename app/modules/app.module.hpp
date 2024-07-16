#ifndef _APP_MODULE_HPP_
#define _APP_MODULE_HPP_

#include <core/materials/module.hpp>
#include <core/materials/runner.hpp>
#include <shared.hpp>
#include <cli/cli.module.hpp>
#include <web/web.module.hpp>

namespace Wasp
{
    // APP Module Global Initialization
    namespace Bootstrap
    {
        // Imports
        const std::map<const std::string, std::shared_ptr<Wasp::Module>> appImports{
            std::make_pair<const std::string, const std::shared_ptr<Wasp::Module> &>(cliModule->uuid(), cliModule),
            std::make_pair<const std::string, const std::shared_ptr<Wasp::Module> &>(webModule->uuid(), webModule)};
        // Runners
        const std::map<const std::string, std::shared_ptr<Wasp::Runner>> appRunners{};

        const auto App = std::make_shared<Wasp::Module>(
            "APP Module",
            appImports,
            appRunners,
            LOG_LEVEL);
    };
};
#endif // !_APP_MODULE_HPP_
