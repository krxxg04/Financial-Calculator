cmake_minimum_required(VERSION 3.16)

project(cpp-financial-calculator VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENABLE_TESTS "Build tests" ON)

set(SOURCES
    src/main.cpp
    src/domain/entities/CalculationResult.cpp
    src/domain/value_objects/Money.cpp
    src/domain/value_objects/InterestRate.cpp
    src/domain/value_objects/Period.cpp
    src/domain/services/FinancialCalculatorService.cpp
    src/application/use_cases/FinancialCalculationUseCase.cpp
    src/infrastructure/persistence/FileHistoryRepository.cpp
    src/infrastructure/utils/InputValidator.cpp
    src/presentation/ConsoleMenu.cpp
    src/presentation/ConsoleApp.cpp
)

add_executable(cpp-financial-calculator ${SOURCES})
target_include_directories(cpp-financial-calculator PRIVATE src)

if(ENABLE_TESTS)
    enable_testing()
    add_executable(financial_calculator_tests
        tests/FinancialCalculatorTests.cpp
        src/domain/entities/CalculationResult.cpp
        src/domain/value_objects/Money.cpp
        src/domain/value_objects/InterestRate.cpp
        src/domain/value_objects/Period.cpp
        src/domain/services/FinancialCalculatorService.cpp
        src/application/use_cases/FinancialCalculationUseCase.cpp
    )
    target_include_directories(financial_calculator_tests PRIVATE src)
    add_test(NAME financial_calculator_tests COMMAND financial_calculator_tests)
endif()
