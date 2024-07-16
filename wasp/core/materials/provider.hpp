#ifndef ___WASP_PROVIDER_HPP___
#define ___WASP_PROVIDER_HPP___

#include <core/elements/named.element.hpp>
#include <core/elements/uuid.element.hpp>

namespace Wasp
{
    class Provider : public NamedElement, public UUIDElement
    {
    protected:
        Provider(const Wasp::Types::TName name_) : NamedElement(name_){};
    };
};

#endif // !___WASP_PROVIDER_HPP___
