#pragma once

namespace finance {
namespace application {
namespace dto {

struct CalculationInputDTO {
    double amount{0.0};
    double ratePercent{0.0};
    int periods{1};
};

}  // namespace dto
}  // namespace application
}  // namespace finance
