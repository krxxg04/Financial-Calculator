#include "infrastructure/utils/InputValidator.h"

#include <iostream>
#include <stdexcept>
#include <string>

namespace finance::infrastructure::utils {

namespace {

std::string trimCopy(const std::string& text) {
    const std::size_t begin = text.find_first_not_of(" \t\n\r");
    if (begin == std::string::npos) {
        return "";
    }

    const std::size_t end = text.find_last_not_of(" \t\n\r");
    return text.substr(begin, end - begin + 1);
}

}  // namespace

double InputValidator::readDouble(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        std::string input;
        if (!std::getline(std::cin, input)) {
            throw std::runtime_error("No se pudo leer la entrada del usuario.");
        }

        double value = 0.0;
        if (tryParseDouble(input, value)) {
            return value;
        }

        std::cout << "Entrada invalida. Intenta nuevamente.\n";
    }
}

double InputValidator::readPositiveDouble(const std::string& prompt, bool allowZero) {
    while (true) {
        const double value = readDouble(prompt);
        if ((allowZero && value >= 0.0) || (!allowZero && value > 0.0)) {
            return value;
        }

        std::cout << "El valor debe ser " << (allowZero ? "mayor o igual a 0.\n" : "mayor que 0.\n");
    }
}

int InputValidator::readPositiveInt(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        std::string input;
        if (!std::getline(std::cin, input)) {
            throw std::runtime_error("No se pudo leer la entrada del usuario.");
        }

        int value = 0;
        if (tryParseInt(input, value) && value > 0) {
            return value;
        }

        std::cout << "Ingresa un entero mayor que 0.\n";
    }
}

int InputValidator::readIntInRange(const std::string& prompt, int min, int max) {
    while (true) {
        std::cout << prompt;
        std::string input;
        if (!std::getline(std::cin, input)) {
            throw std::runtime_error("No se pudo leer la entrada del usuario.");
        }

        int value = 0;
        if (tryParseInt(input, value) && value >= min && value <= max) {
            return value;
        }

        std::cout << "Ingresa un entero entre " << min << " y " << max << ".\n";
    }
}

bool InputValidator::tryParseDouble(const std::string& text, double& value) {
    try {
        const std::string normalized = trimCopy(text);
        if (normalized.empty()) {
            return false;
        }

        std::size_t processed = 0;
        value = std::stod(normalized, &processed);
        return processed == normalized.size();
    } catch (...) {
        return false;
    }
}

bool InputValidator::tryParseInt(const std::string& text, int& value) {
    try {
        const std::string normalized = trimCopy(text);
        if (normalized.empty()) {
            return false;
        }

        std::size_t processed = 0;
        value = std::stoi(normalized, &processed);
        return processed == normalized.size();
    } catch (...) {
        return false;
    }
}

}  // namespace finance::infrastructure::utils
