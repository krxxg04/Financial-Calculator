#include "domain/value_objects/InterestRate.h"

#include <cmath>

#include "domain/exceptions/ValidationException.h"

namespace finance {
namespace domain {
namespace value_objects {

InterestRate::InterestRate(double rate) : rate_(rate) {
    if (!std::isfinite(rate_)) {
        throw exceptions::ValidationException("La tasa debe ser un numero valido.");
    }
    if (rate_ <= -1.0) {
        throw exceptions::ValidationException("La tasa debe ser mayor a -100%.");
    }
}

InterestRate InterestRate::fromPercentage(double percent) { return InterestRate(percent / 100.0); }

double InterestRate::rate() const { return rate_; }

double InterestRate::asPercentage() const { return rate_ * 100.0; }

}  // namespace value_objects
}  // namespace domain
}  // namespace finance
