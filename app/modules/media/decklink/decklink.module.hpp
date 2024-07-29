#ifndef ___WASP_MEDIA_DECKLINK_MODULE_HPP___
#define ___WASP_MEDIA_DECKLINK_MODULE_HPP___

#include <core/materials/module.hpp>
#include <media/decklink/decklink.runner.hpp>

namespace Wasp
{
    namespace Bootstrap
    {
        const std::map<const std::string, std::shared_ptr<Wasp::Runner>> decklinkRunners{
            std::make_pair<const std::string, const std::shared_ptr<Wasp::Runner> &>(Wasp::Bootstrap::decklinkRunner->uuid() + "." + Wasp::Bootstrap::decklinkRunner->name(), Wasp::Bootstrap::decklinkRunner)};
        const std::map<const std::string, std::shared_ptr<Wasp::Module>> decklinkImports{};
        const auto decklinkModule = std::make_shared<Wasp::Module>(
            "DecklinkModule",
            decklinkImports,
            decklinkRunners,
            LOG_LEVEL);
    };
};
#endif // !___WASP_MEDIA_DECKLINK_MODULE_HPP___