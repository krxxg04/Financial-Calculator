#pragma once

#include "application/use_cases/FinancialCalculationUseCase.h"
#include "domain/entities/CalculationResult.h"
#include "presentation/ConsoleMenu.h"

namespace finance::presentation {

class ConsoleApp {
public:
    explicit ConsoleApp(application::use_cases::FinancialCalculationUseCase& useCase);

    void run();

private:
    void handleSimpleInterest();
    void handleCompoundInterest();
    void handleFutureValue();
    void handlePresentValue();
    void handleTeaToTem();
    void handleTemToTea();
    void handleTeaToPeriodic();
    void handleFixedInstallment();
    void handleHistory();

    static void printResult(const domain::entities::CalculationResult& result);

    application::use_cases::FinancialCalculationUseCase& useCase_;
    ConsoleMenu menu_;
};

}  // namespace finance::presentation
