#pragma once

namespace finance::application::dto {

struct CalculationInputDTO {
    double amount{0.0};
    double ratePercent{0.0};
    int periods{1};
};

}  // namespace finance::application::dto
