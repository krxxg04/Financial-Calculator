#include <iostream>

#include "application/use_cases/FinancialCalculationUseCase.h"
#include "infrastructure/persistence/FileHistoryRepository.h"
#include "presentation/ConsoleApp.h"

int main() {
    try {
        finance::infrastructure::persistence::FileHistoryRepository historyRepository("history.log");
        finance::application::use_cases::FinancialCalculationUseCase useCase(historyRepository);
        finance::presentation::ConsoleApp app(useCase);
        app.run();
    } catch (const std::exception& ex) {
        std::cerr << "Error fatal: " << ex.what() << '\n';
        return 1;
    }

    return 0;
}
