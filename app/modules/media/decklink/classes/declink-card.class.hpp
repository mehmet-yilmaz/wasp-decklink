#ifndef ___WASP_MEDIA_DECKLINK_CLASS_HPP___
#define ___WASP_MEDIA_DECKLINK_CLASS_HPP___

#include <DeckLinkAPI.h>
#include <shared.hpp>

namespace Wasp
{
    namespace Decklink
    {
        class Card
        {
        public:
            Card(IDeckLink *decklink, const int &no) : m_decklink{decklink}, m_cardno{no}
            {
                if (this->m_decklink->GetModelName(&this->m_modelname) == S_OK)
                    Wasp::Logger::ConsoleLogger::STATIC_LOG(std::string("Decklink Card: " + std::to_string(this->m_cardno) + " Has initialized with model name: " + std::string(this->m_modelname)).c_str());
                if (this->m_decklink->GetDisplayName(&this->m_displayname) == S_OK)
                    Wasp::Logger::ConsoleLogger::STATIC_LOG(std::string("Decklink Card: " + std::to_string(this->m_cardno) + " Has initialized with  display name: " + std::string(this->m_displayname)).c_str());

                if (this->m_decklink->QueryInterface(IID_IDeckLinkConfiguration, (void **)&this->m_configuration) == S_OK)
                    Wasp::Logger::ConsoleLogger::STATIC_LOG(std::string("Decklink Configuration Successfully Created for Card: " + std::to_string(this->m_cardno)).c_str());
                if (this->m_decklink->QueryInterface(IID_IDeckLinkProfileManager, (void **)&this->m_profile_manager) == S_OK)
                    Wasp::Logger::ConsoleLogger::STATIC_LOG(std::string("Decklink Profile Manager Successfully Created for Card: " + std::to_string(this->m_cardno)).c_str());
                if (this->m_decklink->QueryInterface(IID_IDeckLinkOutput, (void **)&this->m_output) == S_OK)
                    Wasp::Logger::ConsoleLogger::STATIC_LOG(std::string("Decklink Output Successfully Created for Card: " + std::to_string(this->m_cardno)).c_str());
                if (this->m_decklink->QueryInterface(IID_IDeckLinkInput, (void **)&this->m_input) == S_OK)
                    Wasp::Logger::ConsoleLogger::STATIC_LOG(std::string("Decklink Input Successfully Created for Card: " + std::to_string(this->m_cardno)).c_str());
            };
            ~Card()
            {
                if (this->m_configuration)
                    this->m_configuration->Release();
                if (this->m_profile)
                    this->m_profile->Release();
                // if (this->m_decklink)
                //     this->m_decklink->();
            };
            const std::string displayName()
            {
                return std::string(this->m_displayname);
            };

            const std::string modelName()
            {
                return std::string(this->m_modelname);
            };

        private:
            IDeckLink *m_decklink{nullptr};
            IDeckLinkConfiguration *m_configuration{nullptr};
            IDeckLinkProfile *m_profile{nullptr};
            IDeckLinkProfileManager *m_profile_manager{nullptr};
            IDeckLinkOutput *m_output{nullptr};
            IDeckLinkInput *m_input{nullptr};
            const char *m_modelname{NULL};
            const char *m_displayname{NULL};
            const int m_cardno{NULL};
            const char *m_configuration_name{nullptr};

        protected:
        };
    }
};

#endif // !___WASP_MEDIA_DECKLINK_CLASS_HPP___