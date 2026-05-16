#pragma once

#include <vector>

#include "domain/entities/CalculationResult.h"

namespace finance {
namespace domain {
namespace services {

class HistoryRepository {
public:
    virtual ~HistoryRepository() = default;

    virtual void save(const entities::CalculationResult& result) = 0;
    virtual std::vector<entities::CalculationResult> loadAll() const = 0;
};

}  // namespace services
}  // namespace domain
}  // namespace finance
