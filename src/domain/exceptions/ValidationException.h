#pragma once

#include <string>

#include "domain/exceptions/DomainException.h"

namespace finance {
namespace domain {
namespace exceptions {

class ValidationException : public DomainException {
public:
    explicit ValidationException(const std::string& message) : DomainException(message) {}
};

}  // namespace exceptions
}  // namespace domain
}  // namespace finance
