# cpp-financial-calculator

Calculadora financiera de consola en C++17, con arquitectura inspirada en Domain-Driven Design (DDD) y separación por capas:

- `domain`
- `application`
- `infrastructure`
- `presentation`

Incluye cálculos de interés, valor del dinero en el tiempo, conversiones de tasas, cuota fija de préstamo e historial persistido en archivo.

## Funcionalidades

1. Interés simple  
   - `I = C * i * n`
   - `M = C + I`
2. Interés compuesto  
   - `M = C * (1 + i)^n`
   - `I = M - C`
3. Valor futuro  
   - `VF = VP * (1 + i)^n`
4. Valor presente  
   - `VP = VF / (1 + i)^n`
5. Conversión TEA a TEM  
   - `TEM = (1 + TEA)^(1/12) - 1`
6. Conversión TEM a TEA  
   - `TEA = (1 + TEM)^12 - 1`
7. Conversión TEA a tasa periódica  
   - `i_p = (1 + TEA)^(1/m) - 1`
8. Cálculo de cuota fija de préstamo  
   - `R = P * [i(1+i)^n] / [(1+i)^n - 1]`
9. Historial de cálculos guardado en `history.log`

## Estructura del proyecto

```text
src/
├── main.cpp
├── domain/
│   ├── entities/
│   ├── value_objects/
│   ├── services/
│   └── exceptions/
├── application/
│   ├── use_cases/
│   └── dto/
├── infrastructure/
│   ├── persistence/
│   └── utils/
└── presentation/
```

## Requisitos

- C++17 o superior
- CMake 3.16 o superior
- Compilador compatible (`g++`, `clang++` o MSVC)

## Compilación y ejecución

```bash
cmake -S . -B build
cmake --build build
./build/cpp-financial-calculator
```

En Windows con Visual Studio, el ejecutable suele quedar en:

```text
build/Debug/cpp-financial-calculator.exe
```

## Tests básicos

El proyecto incluye pruebas simples sin librerías externas, usando `assert` y `CTest`.

```bash
ctest --test-dir build --output-on-failure
```

También puedes ejecutar directamente:

```bash
./build/financial_calculator_tests
```

## Principios aplicados

- Programación orientada a objetos (POO).
- Principios SOLID (responsabilidades separadas por capa y por clase).
- Validación de entradas y manejo de errores.
- Persistencia desacoplada vía interfaz `HistoryRepository` y adaptación `FileHistoryRepository`.
