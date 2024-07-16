#ifndef _APP_STORE_HPP_
#define _APP_STORE_HPP_
#include "../../base/base.store.hpp"

namespace Wasp
{
    struct IAppState : Base::State
    {
        ~IAppState() override{};
        bool isInitialized = false;
        bool isStarted = false;
        bool isStopped = false;
        bool isProccessing = false;
        bool isFailed = false;
        std::string errorMessage = "";
    };

    class AppStore : public Base::Store
    {
    public:
        AppStore(const std::string &name) : Base::Store(name)
        {
            this->log("Constructing...");
        };
        virtual ~AppStore() override{};
        virtual void start() override
        {
            this->log("Starting...");
        };
        virtual void stop() override
        {
            this->log("Stopping...");
        };
        virtual void init() override
        {

            this->log("Initializing...");
            this->state = std::make_shared<IAppState>();
            this->state->isInitialized = true;
        };
        virtual Base::State getState() override
        {
            return *this->state.get();
        };
        IAppState APP_INITIALIZED()
        {
            this->state->isInitialized = true;
            this->log("[STORE] - APP Initialized!");
            return *this->state.get();
        };
        IAppState APP_NOT_INITIALIZED()
        {
            this->state->isInitialized = false;
            return *this->state.get();
        };
        IAppState APP_STARTED()
        {
            this->state->isStarted = true;
            this->state->isStopped = false;
            return *this->state.get();
        };
        IAppState APP_STOPPED()
        {
            this->state->isStarted = false;
            this->state->isStopped = true;
            return *this->state.get();
        };
        IAppState APP_FAILED(std::string &errMessage)
        {
            this->state->isFailed = true;
            this->state->errorMessage = errMessage;
            return *this->state.get();
        };
        IAppState APP_FAIL_HANDLE()
        {
            this->state->isFailed = false;
            this->state->errorMessage = "";
            return *this->state.get();
        };

    private:
        std::shared_ptr<IAppState> state;
    };
};
#endif // !_APP_STORE_HPP_