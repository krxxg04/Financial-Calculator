#include <cassert>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "application/dto/CalculationInputDTO.h"
#include "application/dto/RateConversionInputDTO.h"
#include "application/use_cases/FinancialCalculationUseCase.h"
#include "domain/services/HistoryRepository.h"

namespace {

class InMemoryHistoryRepository : public finance::domain::services::HistoryRepository {
public:
    void save(const finance::domain::entities::CalculationResult& result) override { results_.push_back(result); }

    std::vector<finance::domain::entities::CalculationResult> loadAll() const override { return results_; }

private:
    std::vector<finance::domain::entities::CalculationResult> results_;
};

bool near(double lhs, double rhs, double eps = 1e-6) { return std::fabs(lhs - rhs) <= eps; }

double extractLastNumber(const std::string& text) {
    const auto pos = text.find_last_of("0123456789");
    if (pos == std::string::npos) {
        throw std::runtime_error("No se encontro numero en el texto.");
    }

    auto start = text.find_last_of("= ", pos);
    if (start == std::string::npos) {
        start = 0;
    } else {
        start += 1;
    }

    std::string token = text.substr(start);
    token.erase(0, token.find_first_of("0123456789-"));
    while (!token.empty() && (token.back() == '%' || token.back() == ' ')) {
        token.pop_back();
    }
    return std::stod(token);
}

void testSimpleInterest() {
    InMemoryHistoryRepository repository;
    finance::application::use_cases::FinancialCalculationUseCase useCase(repository);

    finance::application::dto::CalculationInputDTO input{1000.0, 10.0, 2};
    const auto result = useCase.executeSimpleInterest(input);

    const double finalAmount = extractLastNumber(result.outputSummary());
    assert(near(finalAmount, 1200.0, 1e-3));
}

void testTeaToTem() {
    InMemoryHistoryRepository repository;
    finance::application::use_cases::FinancialCalculationUseCase useCase(repository);

    const auto result = useCase.executeTeaToTem(12.0);
    const double temPercent = extractLastNumber(result.outputSummary());
    assert(near(temPercent, 0.948879, 1e-3));
}

void testFixedInstallment() {
    InMemoryHistoryRepository repository;
    finance::application::use_cases::FinancialCalculationUseCase useCase(repository);

    finance::application::dto::CalculationInputDTO input{10000.0, 1.0, 12};
    const auto result = useCase.executeFixedInstallment(input);

    const double installment = extractLastNumber(result.outputSummary());
    assert(near(installment, 888.49, 0.2));
}

void testHistoryStored() {
    InMemoryHistoryRepository repository;
    finance::application::use_cases::FinancialCalculationUseCase useCase(repository);

    useCase.executeTemToTea(1.0);
    const auto history = useCase.getHistory();
    assert(history.size() == 1);
}

}  // namespace

int main() {
    testSimpleInterest();
    testTeaToTem();
    testFixedInstallment();
    testHistoryStored();

    std::cout << "Todos los tests pasaron correctamente.\n";
    return 0;
}
