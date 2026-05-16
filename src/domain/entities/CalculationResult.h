#pragma once

#include <string>

namespace finance {
namespace domain {
namespace entities {

class CalculationResult {
public:
    CalculationResult(std::string operation, std::string inputSummary, std::string outputSummary, std::string timestamp = "");

    const std::string& operation() const;
    const std::string& inputSummary() const;
    const std::string& outputSummary() const;
    const std::string& timestamp() const;

    std::string toDisplayString() const;
    static std::string currentTimestamp();

private:
    std::string operation_;
    std::string inputSummary_;
    std::string outputSummary_;
    std::string timestamp_;
};

}  // namespace entities
}  // namespace domain
}  // namespace finance
