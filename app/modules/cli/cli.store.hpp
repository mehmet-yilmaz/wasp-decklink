// #ifndef _CLI_STORE_HPP_
// #define _CLI_STORE_HPP_

// #include <base.store.hpp>

// namespace Wasp
// {

//     struct ICliState : Base::State
//     {
//         ~ICliState() override{};
//     };

//     class CliStore : public Base::Store
//     {
//     public:
//         CliStore(const std::string &name) : Base::Store(name)
//         {
//             this->log("Constructing...");
//         };
//         virtual ~CliStore() override{};
//         virtual void init() override
//         {
//             this->log("Initializing...");
//         };
//         virtual void start() override
//         {
//             this->log("Starting...");
//         };
//         virtual void stop() override
//         {
//             this->log("Stopping...");
//         };
//         virtual Base::State getState() override
//         {
//             return *this->state.get();
//         };
//         ICliState CLI_INITIALIZED()
//         {
//             this->log("Initialized");
//             return *this->state.get();
//         };

//     private:
//         std::shared_ptr<ICliState> state;
//     };
// };

// #endif // !_CLI_STORE_HPP_