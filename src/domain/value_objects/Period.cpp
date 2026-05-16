#include "domain/value_objects/Period.h"

#include "domain/exceptions/ValidationException.h"

namespace finance::domain::value_objects {

Period::Period(int value) : value_(value) {
    if (value_ <= 0) {
        throw exceptions::ValidationException("El periodo debe ser mayor que cero.");
    }
}

int Period::value() const { return value_; }

}  // namespace finance::domain::value_objects
