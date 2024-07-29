#ifndef ___WASP_NETWORK_MODULE_HPP___
#define ___WASP_NETWORK_MODULE_HPP___

#include <core/materials/module.hpp>
#include <network/network.runner.hpp>
#include <network/network.service.hpp>

namespace Wasp
{
    namespace Bootstrap
    {

        // Imports
        const std::map<const std::string, std::shared_ptr<Wasp::Module>> networkImports{};

        // Runners
        const std::map<const std::string, std::shared_ptr<Wasp::Runner>> networkRunners{
            std::make_pair<const std::string, const std::shared_ptr<Wasp::Runner> &>(networkRunner->uuid() + "." + networkRunner->name(), networkRunner)};

        const auto networkModule = std::make_shared<Wasp::Module>("NetworkModule", networkImports, networkRunners, LOG_LEVEL);
    }
}

#endif // !___WASP_NETWORK_MODULE_HPP___
