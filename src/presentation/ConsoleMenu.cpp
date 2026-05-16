#include "presentation/ConsoleMenu.h"

#include <iostream>

namespace finance {
namespace presentation {

void ConsoleMenu::showTitle() const {
    std::cout << "\n==========================================\n";
    std::cout << "       CPP FINANCIAL CALCULATOR\n";
    std::cout << "==========================================\n";
}

void ConsoleMenu::showOptions() const {
    std::cout << "1. Interes simple\n";
    std::cout << "2. Interes compuesto\n";
    std::cout << "3. Valor futuro\n";
    std::cout << "4. Valor presente\n";
    std::cout << "5. Conversion TEA a TEM\n";
    std::cout << "6. Conversion TEM a TEA\n";
    std::cout << "7. Conversion TEA a tasa periodica\n";
    std::cout << "8. Cuota fija de prestamo\n";
    std::cout << "9. Ver historial\n";
    std::cout << "0. Salir\n";
}

}  // namespace presentation
}  // namespace finance
