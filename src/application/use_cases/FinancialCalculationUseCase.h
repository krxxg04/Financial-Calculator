#pragma once

#include <string>
#include <vector>

#include "application/dto/CalculationInputDTO.h"
#include "application/dto/RateConversionInputDTO.h"
#include "domain/entities/CalculationResult.h"
#include "domain/services/FinancialCalculatorService.h"
#include "domain/services/HistoryRepository.h"

namespace finance {
namespace application {
namespace use_cases {

class FinancialCalculationUseCase {
public:
    explicit FinancialCalculationUseCase(domain::services::HistoryRepository& historyRepository);

    domain::entities::CalculationResult executeSimpleInterest(const dto::CalculationInputDTO& input);
    domain::entities::CalculationResult executeCompoundInterest(const dto::CalculationInputDTO& input);
    domain::entities::CalculationResult executeFutureValue(const dto::CalculationInputDTO& input);
    domain::entities::CalculationResult executePresentValue(const dto::CalculationInputDTO& input);
    domain::entities::CalculationResult executeTeaToTem(double teaPercent);
    domain::entities::CalculationResult executeTemToTea(double temPercent);
    domain::entities::CalculationResult executeTeaToPeriodic(const dto::RateConversionInputDTO& input);
    domain::entities::CalculationResult executeFixedInstallment(const dto::CalculationInputDTO& input);

    std::vector<domain::entities::CalculationResult> getHistory() const;

private:
    domain::entities::CalculationResult saveResult(const std::string& operation,
                                                   const std::string& inputSummary,
                                                   const std::string& outputSummary);
    static std::string toMoneyText(double value);
    static std::string toPercentText(double value);
    static std::string toNumberText(double value, int precision = 6);

    domain::services::FinancialCalculatorService calculatorService_;
    domain::services::HistoryRepository& historyRepository_;
};

}  // namespace use_cases
}  // namespace application
}  // namespace finance
