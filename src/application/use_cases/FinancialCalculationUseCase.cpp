#include "application/use_cases/FinancialCalculationUseCase.h"

#include <iomanip>
#include <sstream>

namespace finance {
namespace application {
namespace use_cases {

namespace {
using domain::value_objects::InterestRate;
using domain::value_objects::Money;
using domain::value_objects::Period;
}  // namespace

FinancialCalculationUseCase::FinancialCalculationUseCase(domain::services::HistoryRepository& historyRepository)
    : historyRepository_(historyRepository) {}

domain::entities::CalculationResult FinancialCalculationUseCase::executeSimpleInterest(const dto::CalculationInputDTO& input) {
    const Money capital(input.amount);
    const InterestRate rate = InterestRate::fromPercentage(input.ratePercent);
    const Period periods(input.periods);

    const auto data = calculatorService_.calculateSimpleInterest(capital, rate, periods);
    const std::string inputs =
        "Capital=" + toMoneyText(input.amount) + ", Tasa=" + toPercentText(input.ratePercent) + ", Periodos=" + std::to_string(input.periods);
    const std::string outputs =
        "Interes=" + toMoneyText(data.interest.amount()) + ", Monto final=" + toMoneyText(data.finalAmount.amount());

    return saveResult("Interes simple", inputs, outputs);
}

domain::entities::CalculationResult FinancialCalculationUseCase::executeCompoundInterest(const dto::CalculationInputDTO& input) {
    const Money capital(input.amount);
    const InterestRate rate = InterestRate::fromPercentage(input.ratePercent);
    const Period periods(input.periods);

    const auto data = calculatorService_.calculateCompoundInterest(capital, rate, periods);
    const std::string inputs =
        "Capital=" + toMoneyText(input.amount) + ", Tasa=" + toPercentText(input.ratePercent) + ", Periodos=" + std::to_string(input.periods);
    const std::string outputs =
        "Interes=" + toMoneyText(data.interest.amount()) + ", Monto final=" + toMoneyText(data.finalAmount.amount());

    return saveResult("Interes compuesto", inputs, outputs);
}

domain::entities::CalculationResult FinancialCalculationUseCase::executeFutureValue(const dto::CalculationInputDTO& input) {
    const Money presentValue(input.amount);
    const InterestRate rate = InterestRate::fromPercentage(input.ratePercent);
    const Period periods(input.periods);

    const Money futureValue = calculatorService_.calculateFutureValue(presentValue, rate, periods);
    const std::string inputs = "VP=" + toMoneyText(input.amount) + ", Tasa=" + toPercentText(input.ratePercent) +
                               ", Periodos=" + std::to_string(input.periods);
    const std::string outputs = "VF=" + toMoneyText(futureValue.amount());

    return saveResult("Valor futuro", inputs, outputs);
}

domain::entities::CalculationResult FinancialCalculationUseCase::executePresentValue(const dto::CalculationInputDTO& input) {
    const Money futureValue(input.amount);
    const InterestRate rate = InterestRate::fromPercentage(input.ratePercent);
    const Period periods(input.periods);

    const Money presentValue = calculatorService_.calculatePresentValue(futureValue, rate, periods);
    const std::string inputs = "VF=" + toMoneyText(input.amount) + ", Tasa=" + toPercentText(input.ratePercent) +
                               ", Periodos=" + std::to_string(input.periods);
    const std::string outputs = "VP=" + toMoneyText(presentValue.amount());

    return saveResult("Valor presente", inputs, outputs);
}

domain::entities::CalculationResult FinancialCalculationUseCase::executeTeaToTem(double teaPercent) {
    const InterestRate tea = InterestRate::fromPercentage(teaPercent);
    const InterestRate tem = calculatorService_.convertTeaToTem(tea);

    const std::string inputs = "TEA=" + toPercentText(teaPercent);
    const std::string outputs = "TEM=" + toPercentText(tem.asPercentage());

    return saveResult("Conversion TEA a TEM", inputs, outputs);
}

domain::entities::CalculationResult FinancialCalculationUseCase::executeTemToTea(double temPercent) {
    const InterestRate tem = InterestRate::fromPercentage(temPercent);
    const InterestRate tea = calculatorService_.convertTemToTea(tem);

    const std::string inputs = "TEM=" + toPercentText(temPercent);
    const std::string outputs = "TEA=" + toPercentText(tea.asPercentage());

    return saveResult("Conversion TEM a TEA", inputs, outputs);
}

domain::entities::CalculationResult FinancialCalculationUseCase::executeTeaToPeriodic(const dto::RateConversionInputDTO& input) {
    const InterestRate tea = InterestRate::fromPercentage(input.ratePercent);
    const InterestRate periodicRate = calculatorService_.convertTeaToPeriodic(tea, input.periodsPerYear);

    const std::string inputs = "TEA=" + toPercentText(input.ratePercent) + ", Periodos por anio=" + std::to_string(input.periodsPerYear);
    const std::string outputs = "Tasa periodica=" + toPercentText(periodicRate.asPercentage());

    return saveResult("Conversion TEA a tasa periodica", inputs, outputs);
}

domain::entities::CalculationResult FinancialCalculationUseCase::executeFixedInstallment(const dto::CalculationInputDTO& input) {
    const Money principal(input.amount);
    const InterestRate periodicRate = InterestRate::fromPercentage(input.ratePercent);
    const Period periods(input.periods);

    const Money installment = calculatorService_.calculateFixedInstallment(principal, periodicRate, periods);
    const std::string inputs =
        "Prestamo=" + toMoneyText(input.amount) + ", Tasa=" + toPercentText(input.ratePercent) + ", Cuotas=" + std::to_string(input.periods);
    const std::string outputs = "Cuota fija=" + toMoneyText(installment.amount());

    return saveResult("Cuota fija de prestamo", inputs, outputs);
}

std::vector<domain::entities::CalculationResult> FinancialCalculationUseCase::getHistory() const {
    return historyRepository_.loadAll();
}

domain::entities::CalculationResult FinancialCalculationUseCase::saveResult(const std::string& operation,
                                                                            const std::string& inputSummary,
                                                                            const std::string& outputSummary) {
    domain::entities::CalculationResult result(operation, inputSummary, outputSummary);
    historyRepository_.save(result);
    return result;
}

std::string FinancialCalculationUseCase::toMoneyText(double value) {
    return "S/ " + toNumberText(value, 2);
}

std::string FinancialCalculationUseCase::toPercentText(double value) {
    return toNumberText(value, 6) + "%";
}

std::string FinancialCalculationUseCase::toNumberText(double value, int precision) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(precision) << value;
    return oss.str();
}

}  // namespace use_cases
}  // namespace application
}  // namespace finance
