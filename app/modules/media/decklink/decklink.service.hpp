#ifndef ___WASP_MEDIA_DECKLINK_SERVICE_HPP___
#define ___WASP_MEDIA_DECKLINK_SERVICE_HPP___

#include <core/materials/service.hpp>
#include <media/decklink/declink-card.class.hpp>
#include <DeckLinkAPI.h>

namespace Wasp
{
    class DecklinkService : public Wasp::Service
    {
    public:
        DecklinkService(const Wasp::Types::TName &name) : Wasp::Service(name) {};
        virtual ~DecklinkService() override {};
        virtual void init() override
        {
            this->m_decklinkIterator = std::shared_ptr<IDeckLinkIterator>(CreateDeckLinkIteratorInstance());
            if (this->m_decklinkIterator)
            {
                Wasp::Logger::ConsoleLogger::STATIC_LOG("DeckLink Iterator Created!");
                IDeckLink *decklink;
                while (this->m_decklinkIterator->Next(&decklink) == S_OK)
                {
                    std::shared_ptr<Wasp::Decklink::Card> card = std::make_shared<Wasp::Decklink::Card>(decklink, ++this->decklinkCounter);
                    if (card)
                    {
                        this->m_decklinkCards[card->displayName()] = std::move(card);
                    }
                    // this->m_decklinkCards.push_back(std::make_shared<Wasp::Decklink::Card>(decklink, ++this->decklinkCounter));
                }
            }
            else
            {
                Wasp::Logger::ConsoleLogger::STATIC_LOG("DeckLink Iterator Could Not Ganied!");
            }
        };
        virtual void run() override {};

        const std::vector<std::string> getCardList()
        {
            std::vector<std::string> cards;
            for (const auto &card : this->m_decklinkCards)
            {
                cards.push_back(card.second->displayName());
            }
            return cards;
        };

    private:
        std::map<const std::string, std::shared_ptr<Wasp::Decklink::Card>> m_decklinkCards;
        int decklinkCounter{0};
        std::shared_ptr<IDeckLinkIterator> m_decklinkIterator;

    protected:
    };
    namespace Bootstrap
    {
        const auto decklinkService = std::make_shared<Wasp::DecklinkService>("DecklinkService");
    };
};

#endif // !___WASP_MEDIA_DECKLINK_SERVICE_HPP___