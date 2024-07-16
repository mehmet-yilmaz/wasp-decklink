#ifndef _WEB_SERVICE_HPP
#define _WEB_SERVICE_HPP

#include <common.hpp>
#include <base.service.hpp>
namespace Wasp
{
    class WebService : public Base::Service
    {
    public:
        WebService(const std::string &name) : Base::Service(name)
        {
            this->log("Constructing...");
        };
        ~WebService(){};
        virtual void init() override
        {
            this->log("Initializing...");
            this->initialized = true;
        };
        virtual void start() override
        {
            this->log("Starting...");
            this->running = true;
        };
        virtual void stop() override
        {
            this->log("Stopping...");
        };
    };
};
#endif // !_WEB_SERVICE_HPP