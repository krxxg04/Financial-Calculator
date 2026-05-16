#pragma once

#include <string>
#include <vector>

#include "domain/services/HistoryRepository.h"

namespace finance {
namespace infrastructure {
namespace persistence {

class FileHistoryRepository : public domain::services::HistoryRepository {
public:
    explicit FileHistoryRepository(std::string filePath);

    void save(const domain::entities::CalculationResult& result) override;
    std::vector<domain::entities::CalculationResult> loadAll() const override;

private:
    static std::string sanitizeField(const std::string& text);
    static std::vector<std::string> split(const std::string& line, char separator);

    std::string filePath_;
};

}  // namespace persistence
}  // namespace infrastructure
}  // namespace finance
