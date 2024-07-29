#ifndef ___WASP_SYSTEM_MODULE_HPP___
#define ___WASP_SYSTEM_MODULE_HPP___

#include <core/materials/module.hpp>
#include <system/system.runner.hpp>
#include <system/network/network.module.hpp>

namespace Wasp
{
    namespace Bootstrap
    {
        // Imports
        std::map<const std::string, std::shared_ptr<Wasp::Module>> systemImports{
            std::make_pair<const std::string, const std::shared_ptr<Wasp::Module> &>(networkModule->uuid() + "." + networkModule->name(), networkModule)};

        // Runners
        std::map<const std::string, std::shared_ptr<Wasp::Runner>> systemRunners{
            std::make_pair<const std::string, const std::shared_ptr<Wasp::Runner> &>(systemRunner->uuid() + "." + systemRunner->name(), systemRunner)};

        const auto systemModule = std::make_shared<Wasp::Module>("SystemModule", systemImports, systemRunners, LOG_LEVEL);
    };
};

#endif // !___WASP_SYSTEM_MODULE_HPP___