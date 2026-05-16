#include "domain/value_objects/Period.h"

#include "domain/exceptions/ValidationException.h"

namespace finance {
namespace domain {
namespace value_objects {

Period::Period(int value) : value_(value) {
    if (value_ <= 0) {
        throw exceptions::ValidationException("El periodo debe ser mayor que cero.");
    }
}

int Period::value() const { return value_; }

}  // namespace value_objects
}  // namespace domain
}  // namespace finance
