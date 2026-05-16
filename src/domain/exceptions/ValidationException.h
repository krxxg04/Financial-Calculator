#pragma once

#include <string>

#include "domain/exceptions/DomainException.h"

namespace finance::domain::exceptions {

class ValidationException : public DomainException {
public:
    explicit ValidationException(const std::string& message) : DomainException(message) {}
};

}  // namespace finance::domain::exceptions
