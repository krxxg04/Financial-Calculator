#include "domain/entities/CalculationResult.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <utility>

namespace finance {
namespace domain {
namespace entities {

CalculationResult::CalculationResult(std::string operation, std::string inputSummary, std::string outputSummary, std::string timestamp)
    : operation_(std::move(operation)),
      inputSummary_(std::move(inputSummary)),
      outputSummary_(std::move(outputSummary)),
      timestamp_(timestamp.empty() ? currentTimestamp() : std::move(timestamp)) {}

const std::string& CalculationResult::operation() const { return operation_; }

const std::string& CalculationResult::inputSummary() const { return inputSummary_; }

const std::string& CalculationResult::outputSummary() const { return outputSummary_; }

const std::string& CalculationResult::timestamp() const { return timestamp_; }

std::string CalculationResult::toDisplayString() const {
    std::ostringstream oss;
    oss << "[" << timestamp_ << "] " << operation_ << " | " << inputSummary_ << " | " << outputSummary_;
    return oss.str();
}

std::string CalculationResult::currentTimestamp() {
    const auto now = std::chrono::system_clock::now();
    const auto time = std::chrono::system_clock::to_time_t(now);

    std::tm localTime{};
#if defined(_WIN32)
    localtime_s(&localTime, &time);
#else
    localtime_r(&time, &localTime);
#endif

    std::ostringstream oss;
    oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

}  // namespace entities
}  // namespace domain
}  // namespace finance
