#ifndef ___WASP_MEDIA_DECKLINK_RUNNER_HPP___
#define ___WASP_MEDIA_DECKLINK_RUNNER_HPP___

#include <core/materials/runner.hpp>
#include <media/decklink/decklink.service.hpp>
#include <DeckLinkAPI.h>

namespace Wasp
{
    class DecklinkRunner : public Wasp::Runner
    {
    public:
        DecklinkRunner(const Wasp::Types::TName &name, std::shared_ptr<Wasp::DecklinkService> service) : Wasp::Runner(name), m_decklinkService{service}
        {
            this->m_initialized = false;
            this->m_running = false;
        };
        virtual ~DecklinkRunner() override {};
        virtual void init() override
        {
            this->m_initialized = true;
            this->m_decklinkService->init();
        };
        virtual void run() override { this->m_running = true; };
        virtual void reset() override
        {
            this->m_running = false;
            this->m_initialized = false;
        };

    private:
        const std::shared_ptr<Wasp::DecklinkService> m_decklinkService;

    protected:
    };
    namespace Bootstrap
    {
        const auto decklinkRunner = std::make_shared<Wasp::DecklinkRunner>("DecklinkRunner", decklinkService);
    };
};
#endif // !___WASP_MEDIA_DECKLINK_RUNNER_HPP___