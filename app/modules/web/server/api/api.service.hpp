#ifndef ___WASP_API_SERVICE_HPP___
#define ___WASP_API_SERVICE_HPP___

#include <core/materials/service.hpp>

namespace Wasp
{
    class ApiService : public Wasp::Service
    {
    public:
        ApiService(const Wasp::Types::TName &name) : Wasp::Service(name){};
        virtual ~ApiService() override{};
        virtual void init() override {};
        virtual void run() override {};
        std::string onHello(const std::string &source)
        {
            Wasp::Logger::ConsoleLogger::STATIC_LOG(("Hello Endpoint Visited From: " + source).c_str());
            return "Hello From API Service...";
        };
    };

    namespace Bootstrap
    {
        const auto apiService = std::make_shared<Wasp::ApiService>("ApiService");
    }
}

#endif // !___WASP_API_SERVICE_HPP___
