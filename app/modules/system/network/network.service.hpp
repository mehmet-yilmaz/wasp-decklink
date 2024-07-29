#ifndef ___WASP_NETWORK_MODULE_SERVICE_HPP___
#define ___WASP_NETWORK_MODULE_SERVICE_HPP___

#include <core/materials/service.hpp>
#include <system/network/netplan.service.hpp>

namespace Wasp
{
    class NetworkService : public Service
    {
    public:
        NetworkService(const Wasp::Types::TName &name) : Wasp::Service(name) {};
        ~NetworkService() override {};
        virtual void init() override
        {
            Wasp::Bootstrap::netplanService->init();
        };
        virtual void run() override
        {
            this->m_running = true;
        };
        const std::string getConfiguration()
        {
            return Wasp::Bootstrap::netplanService->getConfiguration();
        };
        const std::string getConfigurationPath()
        {
            return Wasp::Bootstrap::netplanService->getConfigPath();
        };
        const bool setConfigurationPath(const std::string &destination, const std::string &configuration)
        {
            return Wasp::Bootstrap::netplanService->setConfiguration(destination, configuration);
        };
        const bool cancelConfigurationPath()
        {
            return Wasp::Bootstrap::netplanService->cancelConfiguration();
        };
        const bool tryConfigurationPath(const uint32_t &timeout)
        {
            return Wasp::Bootstrap::netplanService->tryConfiguration(timeout);
        };
        const bool applyConfigurationPath()
        {
            return Wasp::Bootstrap::netplanService->applyConfiguration();
        };
        const std::map<std::string, std::string> listInterfacesNames()
        {
            struct if_nameindex *if_nidxs, *intf;
            std::map<std::string, std::string> interfaces;
            struct if_nameindex *it_if;
            if_nidxs = if_nameindex();
            if (if_nidxs != nullptr)
            {
                for (it_if = if_nidxs; it_if->if_index != 0 || it_if->if_name != NULL; it_if++)
                {
                    interfaces[it_if->if_name] = it_if->if_name;
                    printf("\tNetwork Interface: %s \t\t Address: %s\n", it_if->if_name, it_if->if_name);
                }
            }

            return interfaces;
        };

        const std::map<std::string, std::string> listInterfaces()
        {
            std::map<std::string, std::string> interfaces;
            struct ifaddrs *ifaddr{nullptr}, *ifa{nullptr};
            int family{NULL};
            int s{NULL};
            char host[NI_MAXHOST];

            if (getifaddrs(&ifaddr) > -1)
            {
                for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
                {
                    if (ifa->ifa_addr == NULL)
                        continue;

                    s = getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in), host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
                    if (s == 0)
                    {
                        if (ifa->ifa_addr->sa_family == AF_INET)
                        {
                            interfaces[ifa->ifa_name] = host;
                            printf("\tNetwork Interface: %s \t\t Address: %s\n", ifa->ifa_name, host);
                        }
                    }
                }
            }

            if (ifaddr)
                freeifaddrs(ifaddr);
            return interfaces;
        };

    private:
    protected:
    };

    namespace Bootstrap
    {
        const auto networkService = std::make_shared<Wasp::NetworkService>("NetworkService");
    };
};

#endif // !___WASP_NETWORK_MODULE_SERVICE_HPP___