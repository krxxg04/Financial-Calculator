#include "presentation/ConsoleApp.h"

#include <iostream>

#include "application/dto/CalculationInputDTO.h"
#include "application/dto/RateConversionInputDTO.h"
#include "infrastructure/utils/InputValidator.h"

namespace finance::presentation {

ConsoleApp::ConsoleApp(application::use_cases::FinancialCalculationUseCase& useCase) : useCase_(useCase) {}

void ConsoleApp::run() {
    bool running = true;

    while (running) {
        menu_.showTitle();
        menu_.showOptions();

        const int option = infrastructure::utils::InputValidator::readIntInRange("Selecciona una opcion: ", 0, 9);
        std::cout << '\n';

        try {
            switch (option) {
                case 1:
                    handleSimpleInterest();
                    break;
                case 2:
                    handleCompoundInterest();
                    break;
                case 3:
                    handleFutureValue();
                    break;
                case 4:
                    handlePresentValue();
                    break;
                case 5:
                    handleTeaToTem();
                    break;
                case 6:
                    handleTemToTea();
                    break;
                case 7:
                    handleTeaToPeriodic();
                    break;
                case 8:
                    handleFixedInstallment();
                    break;
                case 9:
                    handleHistory();
                    break;
                case 0:
                    running = false;
                    std::cout << "Hasta luego.\n";
                    break;
                default:
                    std::cout << "Opcion invalida.\n";
                    break;
            }
        } catch (const std::exception& ex) {
            std::cout << "No se pudo completar la operacion: " << ex.what() << '\n';
        }

        if (running) {
            std::cout << "\nPresiona Enter para continuar...";
            std::string temp;
            std::getline(std::cin, temp);
        }
    }
}

void ConsoleApp::handleSimpleInterest() {
    application::dto::CalculationInputDTO input;
    input.amount = infrastructure::utils::InputValidator::readPositiveDouble("Capital: ");
    input.ratePercent = infrastructure::utils::InputValidator::readDouble("Tasa (%): ");
    input.periods = infrastructure::utils::InputValidator::readPositiveInt("Periodos: ");

    printResult(useCase_.executeSimpleInterest(input));
}

void ConsoleApp::handleCompoundInterest() {
    application::dto::CalculationInputDTO input;
    input.amount = infrastructure::utils::InputValidator::readPositiveDouble("Capital: ");
    input.ratePercent = infrastructure::utils::InputValidator::readDouble("Tasa (%): ");
    input.periods = infrastructure::utils::InputValidator::readPositiveInt("Periodos: ");

    printResult(useCase_.executeCompoundInterest(input));
}

void ConsoleApp::handleFutureValue() {
    application::dto::CalculationInputDTO input;
    input.amount = infrastructure::utils::InputValidator::readPositiveDouble("Valor presente (VP): ");
    input.ratePercent = infrastructure::utils::InputValidator::readDouble("Tasa (%): ");
    input.periods = infrastructure::utils::InputValidator::readPositiveInt("Periodos: ");

    printResult(useCase_.executeFutureValue(input));
}

void ConsoleApp::handlePresentValue() {
    application::dto::CalculationInputDTO input;
    input.amount = infrastructure::utils::InputValidator::readPositiveDouble("Valor futuro (VF): ");
    input.ratePercent = infrastructure::utils::InputValidator::readDouble("Tasa (%): ");
    input.periods = infrastructure::utils::InputValidator::readPositiveInt("Periodos: ");

    printResult(useCase_.executePresentValue(input));
}

void ConsoleApp::handleTeaToTem() {
    const double teaPercent = infrastructure::utils::InputValidator::readDouble("TEA (%): ");
    printResult(useCase_.executeTeaToTem(teaPercent));
}

void ConsoleApp::handleTemToTea() {
    const double temPercent = infrastructure::utils::InputValidator::readDouble("TEM (%): ");
    printResult(useCase_.executeTemToTea(temPercent));
}

void ConsoleApp::handleTeaToPeriodic() {
    application::dto::RateConversionInputDTO input;
    input.ratePercent = infrastructure::utils::InputValidator::readDouble("TEA (%): ");
    input.periodsPerYear = infrastructure::utils::InputValidator::readPositiveInt("Periodos por anio: ");

    printResult(useCase_.executeTeaToPeriodic(input));
}

void ConsoleApp::handleFixedInstallment() {
    application::dto::CalculationInputDTO input;
    input.amount = infrastructure::utils::InputValidator::readPositiveDouble("Monto del prestamo (P): ");
    input.ratePercent = infrastructure::utils::InputValidator::readDouble("Tasa periodica (%): ");
    input.periods = infrastructure::utils::InputValidator::readPositiveInt("Numero de cuotas (n): ");

    printResult(useCase_.executeFixedInstallment(input));
}

void ConsoleApp::handleHistory() {
    const auto history = useCase_.getHistory();
    if (history.empty()) {
        std::cout << "No hay calculos registrados.\n";
        return;
    }

    std::cout << "Historial de calculos:\n";
    for (const auto& item : history) {
        std::cout << "- " << item.toDisplayString() << '\n';
    }
}

void ConsoleApp::printResult(const domain::entities::CalculationResult& result) {
    std::cout << "Resultado: " << result.outputSummary() << '\n';
}

}  // namespace finance::presentation
