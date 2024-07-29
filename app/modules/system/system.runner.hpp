#ifndef ___WASP_SYSTEM_RUNNER_HPP___
#define ___WASP_SYSTEM_RUNNER_HPP___

#include <core/materials/runner.hpp>

namespace Wasp
{
    class SystemRunner : public Wasp::Runner
    {
    public:
        SystemRunner(const Wasp::Types::TName &name) : Wasp::Runner(name) {};
        virtual ~SystemRunner() override {};
        virtual void init() override {};
        virtual void run() override {};
        virtual void reset() override {};

    private:
    protected:
    };

    namespace Bootstrap
    {
        const auto systemRunner = std::make_shared<Wasp::SystemRunner>("SystemRunner");
    };
};

#endif // !___WASP_SYSTEM_RUNNER_HPP___
