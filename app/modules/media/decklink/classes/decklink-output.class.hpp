#ifndef ___WASP_MEDIA_DECKLINK_OUTPUT_CLASS_HPP___
#define ___WASP_MEDIA_DECKLINK_OUTPUT_CLASS_HPP___

#include <DeckLinkAPI.h>

namespace Wasp
{
    class DecklinkOutput : public IDeckLinkVideoOutputCallback, public IDeckLinkAudioOutputCallback
    {
    public:
    private:
    protected:
    }
};

#endif // !___WASP_MEDIA_DECKLINK_OUTPUT_CLASS_HPP___