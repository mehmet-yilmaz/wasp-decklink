#ifndef ___WASP_SYSTEM_NETWORK_NETPLAN_SERVICE_HPP___
#define ___WASP_SYSTEM_NETWORK_NETPLAN_SERVICE_HPP___

#define NETPLAN_CONFIGURATION_FILE_NAME "000-wasp-configuration"
#define NETPLAN_DBUS_BUS_NAME "io.netplan.Netplan"
#define NETPLAN_DBUS_ROOT_PATH "/io/netplan/Netplan"
#define NETPLAN_DBUS_GET_CONFIG_PATH_METHOD_INTERFACE "io.netplan.Netplan"
#define NETPLAN_DBUS_GET_CONFIG_PATH_METHOD_NAME "Config"
#define NETPLAN_DBUS_GET_CONFIG_METHOD_INTERFACE "io.netplan.Netplan.Config"
#define NETPLAN_DBUS_GET_CONFIG_METHOD_NAME "Get"
#define NETPLAN_DBUS_SET_CONFIG_METHOD_INTERFACE "io.netplan.Netplan.Config"
#define NETPLAN_DBUS_SET_CONFIG_METHOD_NAME "Set"
#define NETPLAN_DBUS_TRY_CONFIG_METHOD_INTERFACE "io.netplan.Netplan.Config"
#define NETPLAN_DBUS_TRY_CONFIG_METHOD_NAME "Try"
#define NETPLAN_DBUS_APPLY_CONFIG_METHOD_INTERFACE "io.netplan.Netplan.Config"
#define NETPLAN_DBUS_APPLY_CONFIG_METHOD_NAME "Apply"
#define NETPLAN_DBUS_CANCEL_CONFIG_METHOD_INTERFACE "io.netplan.Netplan.Config"
#define NETPLAN_DBUS_CANCEL_CONFIG_METHOD_NAME "Cancel"

#include <core/materials/service.hpp>
#include <dbus-cxx-2.0/dbus-cxx.h>
#include <dbus-cxx-2.0/dbus-cxx/connection.h>
#include <dbus-cxx-2.0/dbus-cxx/dispatcher.h>
#include <dbus-cxx-2.0/dbus-cxx/objectproxy.h>
#include <dbus-cxx-2.0/dbus-cxx/methodproxybase.h>
#include <dbus-cxx-2.0/dbus-cxx/path.h>
namespace Wasp
{
    class NetplanService : public Wasp::Service
    {
    public:
        NetplanService(const Wasp::Types::TName &name) : Wasp::Service(name) {};
        virtual ~NetplanService() override {};
        virtual void init() override
        {
            try
            {
                this->dispatcher = DBus::StandaloneDispatcher::create();
                this->connection = this->dispatcher->create_connection(DBus::BusType::SYSTEM);
                this->object = this->connection->create_object_proxy(NETPLAN_DBUS_BUS_NAME, NETPLAN_DBUS_ROOT_PATH);
            }
            catch (DBus::Error &err)
            {
                this->handleDBusError(err);
            };
            this->configurationPath.clear();
            this->m_initialized = true;
        };
        virtual void run() override
        {
            this->m_running = true;
        };
        const std::string getConfigPath()
        {
            if (this->configurationPath.empty())
            {
                try
                {
                    this->object->set_path(NETPLAN_DBUS_ROOT_PATH);
                    DBus::MethodProxy<DBus::Path()> &configProxy = *(this->object->create_method<DBus::Path()>(NETPLAN_DBUS_GET_CONFIG_PATH_METHOD_INTERFACE, NETPLAN_DBUS_GET_CONFIG_PATH_METHOD_NAME));
                    this->configurationPath = configProxy();
                }
                catch (DBus::Error &err)
                {
                    this->handleDBusError(err);
                }
            }
            Wasp::Logger::ConsoleLogger::STATIC_LOG(std::string("Configuration Path: " + this->configurationPath).c_str());
            return this->configurationPath;
        };
        const std::string getConfiguration()
        {
            try
            {
                if (!this->connection->is_connected())
                {
                    throw new DBus::ErrorDisconnected();
                }

                const std::string configPath = this->getConfigPath();
                this->object->set_path(configPath);
                DBus::MethodProxy<std::string()> &methodProxy = *(object->create_method<std::string()>(NETPLAN_DBUS_GET_CONFIG_METHOD_INTERFACE, NETPLAN_DBUS_GET_CONFIG_METHOD_NAME));
                const std::string configuration = methodProxy();
                return configuration;
            }
            catch (DBus::Error &err)
            {
                this->handleDBusError(err);
            }
        };
        bool setConfiguration(const std::string destination, const std::string configuration)
        {
            try
            {
                if (!this->connection->is_connected())
                {
                    throw new DBus::ErrorDisconnected();
                }
                const std::string configurationPath = this->getConfigPath();
                this->object->set_path(configurationPath);
                DBus::MethodProxy<bool(std::string, std::string)> &methodProxy = *(object->create_method<bool(std::string, std::string)>(NETPLAN_DBUS_SET_CONFIG_METHOD_INTERFACE, NETPLAN_DBUS_SET_CONFIG_METHOD_NAME));
                std::string config = destination + "=" + configuration;
                const bool result = methodProxy(config, NETPLAN_CONFIGURATION_FILE_NAME);
                if (result)
                    Wasp::Logger::ConsoleLogger::STATIC_LOG(std::string("Configuration " + config + " has successfully setted to: " + this->configurationPath).c_str());
                else
                    Wasp::Logger::ConsoleLogger::STATIC_LOG(std::string("Configuration " + config + " Could not applied to: " + this->configurationPath).c_str());
                return result;
            }
            catch (DBus::Error &err)
            {
                this->handleDBusError(err);
            };
        };

        bool tryConfiguration(uint32_t timeout)
        {
            try
            {
                if (!this->connection->is_connected())
                {
                    throw new DBus::ErrorDisconnected();
                }
                const std::string configurationPath = this->getConfigPath();
                this->object->set_path(configurationPath);
                DBus::MethodProxy<bool(uint32_t)> &methodProxy = *(object->create_method<bool(uint32_t)>(NETPLAN_DBUS_TRY_CONFIG_METHOD_INTERFACE, NETPLAN_DBUS_TRY_CONFIG_METHOD_NAME));
                const bool result = methodProxy(timeout);
                return result;
            }
            catch (DBus::Error &err)
            {
                this->handleDBusError(err);
            };
        };
        bool applyConfiguration()
        {
            try
            {
                if (!this->connection->is_connected())
                {
                    throw new DBus::ErrorDisconnected();
                }
                const std::string configurationPath = this->getConfigPath();
                this->object->set_path(configurationPath);
                DBus::MethodProxy<bool()> &methodProxy = *(object->create_method<bool()>(NETPLAN_DBUS_APPLY_CONFIG_METHOD_INTERFACE, NETPLAN_DBUS_APPLY_CONFIG_METHOD_NAME));
                const bool result = methodProxy();
                if (result)
                    Wasp::Logger::ConsoleLogger::STATIC_LOG(std::string("Configuration " + this->configurationPath + " has successfully applied!").c_str());
                else
                    Wasp::Logger::ConsoleLogger::STATIC_LOG(std::string("Configuration " + this->configurationPath + " Could not applied").c_str());
                this->configurationPath.clear();
                return result;
            }
            catch (DBus::Error &err)
            {
                this->handleDBusError(err);
            };
        };

        bool cancelConfiguration()
        {
            try
            {
                if (!this->connection->is_connected())
                {
                    throw new DBus::ErrorDisconnected();
                }
                const std::string configurationPath = this->getConfigPath();
                this->object->set_path(configurationPath);
                DBus::MethodProxy<bool()> &methodProxy = *(object->create_method<bool()>(NETPLAN_DBUS_CANCEL_CONFIG_METHOD_INTERFACE, NETPLAN_DBUS_CANCEL_CONFIG_METHOD_NAME));
                const bool result = methodProxy();
                this->configurationPath.clear();
                return result;
            }
            catch (DBus::Error &err)
            {
                this->handleDBusError(err);
            };
        };

    private:
        std::shared_ptr<DBus::Dispatcher> dispatcher{nullptr};
        std::shared_ptr<DBus::Connection> connection{nullptr};
        std::shared_ptr<DBus::ObjectProxy> object{nullptr};
        std::string configurationPath{NULL};
        void handleDBusError(DBus::Error err)
        {
            Wasp::Logger::ConsoleLogger::STATIC_LOG("DBUS FAILED");
            Wasp::Logger::ConsoleLogger::STATIC_LOG(std::string("\n\tName: " + err.name() + "\n\tWhat: " + err.what() + "\n\tMessage:" + err.message()).c_str());
            if (err.message() == "This config was invalidated by another config object")
                this->configurationPath.clear();
        };

    protected:
    };
    namespace Bootstrap
    {
        const auto netplanService = std::make_shared<Wasp::NetplanService>("NetplanService");
    };
};

#endif // !___WASP_SYSTEM_NETWORK_NETPLAN_SERVICE_HPP___