#pragma once

namespace finance {
namespace application {
namespace dto {

struct RateConversionInputDTO {
    double ratePercent{0.0};
    int periodsPerYear{12};
};

}  // namespace dto
}  // namespace application
}  // namespace finance
