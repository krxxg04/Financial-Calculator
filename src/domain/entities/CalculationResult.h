#pragma once

#include <string>

namespace finance::domain::entities {

class CalculationResult {
public:
    CalculationResult(std::string operation, std::string inputSummary, std::string outputSummary, std::string timestamp = "");

    [[nodiscard]] const std::string& operation() const;
    [[nodiscard]] const std::string& inputSummary() const;
    [[nodiscard]] const std::string& outputSummary() const;
    [[nodiscard]] const std::string& timestamp() const;

    [[nodiscard]] std::string toDisplayString() const;
    static std::string currentTimestamp();

private:
    std::string operation_;
    std::string inputSummary_;
    std::string outputSummary_;
    std::string timestamp_;
};

}  // namespace finance::domain::entities
