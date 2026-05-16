#pragma once

#include <vector>

#include "domain/entities/CalculationResult.h"

namespace finance::domain::services {

class HistoryRepository {
public:
    virtual ~HistoryRepository() = default;

    virtual void save(const entities::CalculationResult& result) = 0;
    [[nodiscard]] virtual std::vector<entities::CalculationResult> loadAll() const = 0;
};

}  // namespace finance::domain::services
