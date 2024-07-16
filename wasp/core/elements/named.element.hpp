#ifndef ___WASP_NAMED_ELEMENT_HPP___
#define ___WASP_NAMED_ELEMENT_HPP___

#include <shared.hpp>
#include <types/name.type.hpp>
#include <utils/generator/name.generator.hpp>
#include <utils/logger/console.logger.hpp>

namespace Wasp
{
    class NamedElement
    {
    public:
        virtual const Wasp::Types::TName name()
        {
            return this->name_;
        };
        virtual const Wasp::Types::TName name(const Wasp::Types::TName caller)
        {
            std::cout << "Named Element " << this->name_ << "'s name has been called by: " << caller << std::endl;
            return this->name_;
        };

    protected:
        NamedElement(const Wasp::Types::TName name) : name_(name != "" ? name : Wasp::Generators::NameGenerator::generate()){};
        const Wasp::Types::TName name_;
    };
};

#endif // !___WASP_NAMED_ELEMENT_HPP___
