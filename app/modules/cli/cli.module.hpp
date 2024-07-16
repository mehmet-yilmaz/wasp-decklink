#ifndef _CLI_MODULE_HPP_
#define _CLI_MODULE_HPP_

#include <shared.hpp>
#include <app.service.hpp>
#include <cli/cli.service.hpp>
#include <core/materials/module.hpp>
#include <cli/cli.runner.hpp>

namespace Wasp
{
    // CLI Module Global Initialization!
    namespace Bootstrap
    {
        // const auto cliController = std::make_shared<Wasp::CliController>("CLI Controller", cliService);
        const auto cliRunner = std::make_shared<Wasp::CliRunner>("CLI Runner", cliService);
        const std::map<const std::string, std::shared_ptr<Wasp::Module>> cliImports{};
        const std::map<const std::string, std::shared_ptr<Wasp::Runner>> cliRunners{
            std::make_pair<const std::string, const std::shared_ptr<Wasp::Runner> &>(cliRunner->uuid(), cliRunner)};
        const auto cliModule = std::make_shared<Wasp::Module>(
            "CLI Module",
            cliImports,
            cliRunners,
            LOG_LEVEL);
    };
};

#endif // !_CLI_MODULE_HPP_