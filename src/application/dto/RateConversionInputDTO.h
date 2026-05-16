#pragma once

namespace finance::application::dto {

struct RateConversionInputDTO {
    double ratePercent{0.0};
    int periodsPerYear{12};
};

}  // namespace finance::application::dto
