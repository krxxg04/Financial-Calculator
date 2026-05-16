#pragma once

#include "domain/value_objects/InterestRate.h"
#include "domain/value_objects/Money.h"
#include "domain/value_objects/Period.h"

namespace finance::domain::services {

struct SimpleInterestData {
    value_objects::Money interest;
    value_objects::Money finalAmount;
};

struct CompoundInterestData {
    value_objects::Money interest;
    value_objects::Money finalAmount;
};

class FinancialCalculatorService {
public:
    [[nodiscard]] SimpleInterestData calculateSimpleInterest(const value_objects::Money& capital,
                                                             const value_objects::InterestRate& rate,
                                                             const value_objects::Period& periods) const;

    [[nodiscard]] CompoundInterestData calculateCompoundInterest(const value_objects::Money& capital,
                                                                 const value_objects::InterestRate& rate,
                                                                 const value_objects::Period& periods) const;

    [[nodiscard]] value_objects::Money calculateFutureValue(const value_objects::Money& presentValue,
                                                            const value_objects::InterestRate& rate,
                                                            const value_objects::Period& periods) const;

    [[nodiscard]] value_objects::Money calculatePresentValue(const value_objects::Money& futureValue,
                                                             const value_objects::InterestRate& rate,
                                                             const value_objects::Period& periods) const;

    [[nodiscard]] value_objects::InterestRate convertTeaToTem(const value_objects::InterestRate& tea) const;
    [[nodiscard]] value_objects::InterestRate convertTemToTea(const value_objects::InterestRate& tem) const;
    [[nodiscard]] value_objects::InterestRate convertTeaToPeriodic(const value_objects::InterestRate& tea, int periodsPerYear) const;

    [[nodiscard]] value_objects::Money calculateFixedInstallment(const value_objects::Money& principal,
                                                                 const value_objects::InterestRate& periodicRate,
                                                                 const value_objects::Period& periods) const;
};

}  // namespace finance::domain::services
