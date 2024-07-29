#ifndef ___WASP_MEDIA_MODULE_HPP___
#define ___WASP_MEDIA_MODULE_HPP___

#include <core/materials/module.hpp>
#include <media/media.runner.hpp>
#include <media/decklink/decklink.module.hpp>

namespace Wasp
{
    namespace Bootstrap
    {
        const std::map<const std::string, std::shared_ptr<Wasp::Runner>> mediaRunners{
            std::make_pair<const std::string, const std::shared_ptr<Wasp::Runner> &>(Wasp::Bootstrap::mediaRunner->uuid() + "." + Wasp::Bootstrap::mediaRunner->name(), Wasp::Bootstrap::mediaRunner)};
        const std::map<const std::string, std::shared_ptr<Wasp::Module>> mediaImports{
            std::make_pair<const std::string, const std::shared_ptr<Wasp::Module> &>(Wasp::Bootstrap::decklinkModule->uuid() + "." + Wasp::Bootstrap::decklinkModule->name(), Wasp::Bootstrap::decklinkModule)};
        const auto mediaModule = std::make_shared<Wasp::Module>(
            "MediaModule",
            mediaImports,
            mediaRunners,
            LOG_LEVEL);
    };
};

#endif // !___WASP_MEDIA_MODULE_HPP___
