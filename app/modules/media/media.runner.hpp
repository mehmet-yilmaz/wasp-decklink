#ifndef ___WASP_MEDIA_RUNNER_HPP___
#define ___WASP_MEDIA_RUNNER_HPP___

#include <core/materials/runner.hpp>

namespace Wasp
{
    class MediaRunner : public Runner
    {
    public:
        MediaRunner(const Wasp::Types::TName &name) : Runner(name)
        {
            this->m_running = false;
            this->m_initialized = false;
        };
        virtual ~MediaRunner() override {};
        virtual void init() override
        {
            this->m_initialized = true;
        };
        virtual void run() override
        {
            this->m_running = true;
        };
        virtual void reset() override
        {
            this->m_running = false;
            this->m_initialized = false;
        };

    private:
    protected:
    };

    namespace Bootstrap
    {
        const auto mediaRunner = std::make_shared<Wasp::MediaRunner>("MediaRunner");
    };
};

#endif // !___WASP_MEDIA_RUNNER_HPP___