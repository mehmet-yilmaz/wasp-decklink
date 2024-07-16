#ifndef _CLI_SUBJECTS_HPP_
#define _CLI_SUBJECTS_HPP_

#include <shared.hpp>
#include <utils/observable/subject.hpp>

namespace Wasp
{
    const auto addSubject = std::make_shared<Wasp::Observable::Subject<int>>();
    const auto quitSubject = std::make_shared<Wasp::Observable::Subject<bool>>();
};

#endif // !_CLI_SUBJECTS_HPP_