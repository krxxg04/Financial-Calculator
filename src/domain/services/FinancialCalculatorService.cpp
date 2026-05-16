#include "domain/services/FinancialCalculatorService.h"

#include <cmath>

#include "domain/exceptions/ValidationException.h"

namespace finance::domain::services {

SimpleInterestData FinancialCalculatorService::calculateSimpleInterest(const value_objects::Money& capital,
                                                                       const value_objects::InterestRate& rate,
                                                                       const value_objects::Period& periods) const {
    const double interest = capital.amount() * rate.rate() * static_cast<double>(periods.value());
    const double finalAmount = capital.amount() + interest;
    return {value_objects::Money(interest), value_objects::Money(finalAmount)};
}

CompoundInterestData FinancialCalculatorService::calculateCompoundInterest(const value_objects::Money& capital,
                                                                           const value_objects::InterestRate& rate,
                                                                           const value_objects::Period& periods) const {
    const double factor = std::pow(1.0 + rate.rate(), static_cast<double>(periods.value()));
    const double finalAmount = capital.amount() * factor;
    const double interest = finalAmount - capital.amount();
    return {value_objects::Money(interest), value_objects::Money(finalAmount)};
}

value_objects::Money FinancialCalculatorService::calculateFutureValue(const value_objects::Money& presentValue,
                                                                      const value_objects::InterestRate& rate,
                                                                      const value_objects::Period& periods) const {
    const double factor = std::pow(1.0 + rate.rate(), static_cast<double>(periods.value()));
    return value_objects::Money(presentValue.amount() * factor);
}

value_objects::Money FinancialCalculatorService::calculatePresentValue(const value_objects::Money& futureValue,
                                                                       const value_objects::InterestRate& rate,
                                                                       const value_objects::Period& periods) const {
    const double factor = std::pow(1.0 + rate.rate(), static_cast<double>(periods.value()));
    if (factor == 0.0) {
        throw exceptions::ValidationException("No se puede dividir entre cero para calcular valor presente.");
    }
    return value_objects::Money(futureValue.amount() / factor);
}

value_objects::InterestRate FinancialCalculatorService::convertTeaToTem(const value_objects::InterestRate& tea) const {
    const double tem = std::pow(1.0 + tea.rate(), 1.0 / 12.0) - 1.0;
    return value_objects::InterestRate(tem);
}

value_objects::InterestRate FinancialCalculatorService::convertTemToTea(const value_objects::InterestRate& tem) const {
    const double tea = std::pow(1.0 + tem.rate(), 12.0) - 1.0;
    return value_objects::InterestRate(tea);
}

value_objects::InterestRate FinancialCalculatorService::convertTeaToPeriodic(const value_objects::InterestRate& tea,
                                                                              int periodsPerYear) const {
    if (periodsPerYear <= 0) {
        throw exceptions::ValidationException("Los periodos por anio deben ser mayores a cero.");
    }
    const double periodicRate = std::pow(1.0 + tea.rate(), 1.0 / static_cast<double>(periodsPerYear)) - 1.0;
    return value_objects::InterestRate(periodicRate);
}

value_objects::Money FinancialCalculatorService::calculateFixedInstallment(const value_objects::Money& principal,
                                                                           const value_objects::InterestRate& periodicRate,
                                                                           const value_objects::Period& periods) const {
    const double i = periodicRate.rate();
    const double n = static_cast<double>(periods.value());

    if (i == 0.0) {
        return value_objects::Money(principal.amount() / n);
    }

    const double factor = std::pow(1.0 + i, n);
    const double denominator = factor - 1.0;
    if (denominator == 0.0) {
        throw exceptions::ValidationException("No se puede calcular cuota fija con denominador cero.");
    }

    const double installment = principal.amount() * ((i * factor) / denominator);
    return value_objects::Money(installment);
}

}  // namespace finance::domain::services
