#ifndef _WEB_SOCKET_SERVER_SERVICE_HPP_
#define _WEB_SOCKET_SERVER_SERVICE_HPP_

#include <core/materials/service.hpp>

namespace Wasp
{
    class WSServerService : public Service
    {
    public:
        virtual void init() override {};
        virtual void run() override {};
        WSServerService(const Wasp::Types::TName &name) : Service(name){};

    private:
    };

    namespace Bootstrap
    {
        const auto wsserverService = std::make_shared<Wasp::WSServerService>("WEBSOCKET SERVICE");
    };
};

#endif // !_WEB_SOCKET_SERVER_SERVICE_HPP_
