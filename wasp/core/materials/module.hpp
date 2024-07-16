#ifndef ___WASP_MODULE_HPP___
#define ___WASP_MODULE_HPP___

#include <core/elements/named.element.hpp>
#include <utils/logger/console.logger.hpp>
#include <core/materials/runner.hpp>
#include <core/interfaces/initializable.interface.hpp>
#include <core/interfaces/runnable.interface.hpp>
#include <shared.hpp>

namespace Wasp
{
    class Module : public I_Initializable,
                   public I_Runnable,
                   public NamedElement,
                   public UUIDElement
    {
    public:
        virtual ~Module()
        {
            this->logger->debug((this->name() + " is destructing..."), 5);
        };
        virtual void init() override
        {
            this->logger->debug((this->name() + " Initializing..."), 5);

            this->init_map(this->imports);
            this->init_map(this->runners);

            this->initialized = true;
        };
        virtual void run() override
        {
            this->logger->debug((this->name() + " running..."), 5);
            this->running = true;
            this->run_map(this->runners);
            this->run_map(this->imports);
            this->join_threads();
        };
        std::atomic_bool &isInitialized()
        {
            return this->initialized;
        };
        std::atomic_bool &isRunning()
        {
            return this->running;
        };
        std::unique_ptr<Logger::ConsoleLogger> logger;
        Module(
            const Wasp::Types::TName name_,
            const std::map<const std::string, std::shared_ptr<Module>> &imports_,
            const std::map<const std::string, std::shared_ptr<Runner>> &runners_,
            const int log_level = 3) : NamedElement(name_),
                                       imports{std::move(imports_)},
                                       runners{std::move(runners_)},
                                       logger(std::make_unique<Logger::ConsoleLogger>(name_, log_level))
        {
            this->logger->debug(this->name() + " Constructed", 5);
        };

    protected:
        std::map<const std::string, std::thread> threads{};
        std::atomic_bool initialized{false};
        std::atomic_bool running{false};
        const std::map<const std::string, std::shared_ptr<Module>> &imports;
        const std::map<const std::string, std::shared_ptr<Runner>> &runners;

        //
        template <typename T, std::enable_if_t<std::is_base_of<I_Initializable, T>::value, bool> = true>
        void init_map(const std::map<const std::string, std::shared_ptr<T>> &initables)
        {
            for (auto const &initable : initables)
            {
                this->logger->debug(initable.first + " Initializing...", 5);
                if (!initable.second->isInitialized())
                {
                    initable.second->init();
                    this->logger->log(initable.first + " initialized!", 5);
                }
            }
        };

        template <typename T, std::enable_if_t<std::is_base_of<I_Runnable, T>::value, bool> = true>
        void run_map(const std::map<const std::string, std::shared_ptr<T>> &runnables)
        {
            for (auto const &runnable : runnables)
            {
                if (!runnable.second->isRunning())
                {
                    this->threads[runnable.first] = std::thread(&I_Runnable::run, runnable.second);
                    this->logger->log(runnable.first + " runner has been threaded!", 5);
                }
            };
        }

        void join_threads()
        {
            for (auto &thread : this->threads)
            {
                if (thread.second.joinable())
                {
                    this->logger->log(thread.first + " Thread has been joining!", 5);
                    thread.second.join();
                    this->logger->log(thread.first + " Thread has been Detached!!!", 5);
                }
            };
        };
    };
};

#endif // !___WASP_MODULE_HPP___
