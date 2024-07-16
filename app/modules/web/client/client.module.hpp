#ifndef _WEB_CLIENT_MODULE_HPP_
#define _WEB_CLIENT_MODULE_HPP_

#include <shared.hpp>
#include <core/materials/module.hpp>
#include <core/materials/runner.hpp>
#include <web/client/client.runner.hpp>

namespace Wasp
{
    namespace Bootstrap
    {
        const auto webClientRunner = std::make_shared<Wasp::WebClientRunner>("Web-Client Runner");
        const std::map<const std::string, std::shared_ptr<Wasp::Module> &> webClientImports{};
        const std::map<const std::string, std::shared_ptr<Wasp::Runner>> webClientRunners{
            std::make_pair<const std::string, const std::shared_ptr<Wasp::Runner> &>(webClientRunner->uuid(), webClientRunner)};
        const auto clientModule = std::make_shared<Wasp::Module>(
            "Web Client Module",
            webClientImports,
            webClientRunners,
            LOG_LEVEL);
    };
};

#endif // !_WEB_CLIENT_MODULE_HPP_