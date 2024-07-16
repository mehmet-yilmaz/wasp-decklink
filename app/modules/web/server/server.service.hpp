#ifndef _WEB_SERVER_SERVICE_HPP_
#define _WEB_SERVER_SERVICE_HPP_

#include <shared.hpp>
#include <core/materials/service.hpp>

namespace Wasp
{

    class WebServerService : public Service
    {
    public:
        WebServerService(const Wasp::Types::TName &name_) : Service(name_){};
        virtual ~WebServerService() override{};
        virtual void init() override {};
        virtual void run() override {};
        void stop_module() {
        };
        void onHello()
        {
            Wasp::Logger::ConsoleLogger::STATIC_LOG("HELLO ENDPOINT CALLED!");
        };
    };

    namespace Bootstrap
    {
        const auto webServerService = std::make_shared<Wasp::WebServerService>("Web Server Service");
    };

};

#endif // !_WEB_SERVER_SERVICE_HPP_
