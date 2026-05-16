#include "domain/value_objects/Money.h"

#include <cmath>

#include "domain/exceptions/ValidationException.h"

namespace finance {
namespace domain {
namespace value_objects {

Money::Money(double amount) : amount_(amount) {
    if (!std::isfinite(amount_)) {
        throw exceptions::ValidationException("El monto debe ser un numero valido.");
    }
    if (amount_ < 0.0) {
        throw exceptions::ValidationException("El monto no puede ser negativo.");
    }
}

double Money::amount() const { return amount_; }

}  // namespace value_objects
}  // namespace domain
}  // namespace finance
