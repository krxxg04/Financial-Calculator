# cpp-financial-calculator

Calculadora financiera de consola en C++17, con arquitectura inspirada en Domain-Driven Design (DDD) y separacion por capas:

- `domain`
- `application`
- `infrastructure`
- `presentation`

Incluye calculos de interes, valor del dinero en el tiempo, conversiones de tasas, cuota fija de prestamo e historial persistido en archivo.

## Funcionalidades

1. Interes simple  
   - `I = C * i * n`
   - `M = C + I`
2. Interes compuesto  
   - `M = C * (1 + i)^n`
   - `I = M - C`
3. Valor futuro  
   - `VF = VP * (1 + i)^n`
4. Valor presente  
   - `VP = VF / (1 + i)^n`
5. Conversion TEA a TEM  
   - `TEM = (1 + TEA)^(1/12) - 1`
6. Conversion TEM a TEA  
   - `TEA = (1 + TEM)^12 - 1`
7. Conversion TEA a tasa periodica  
   - `i_p = (1 + TEA)^(1/m) - 1`
8. Calculo de cuota fija de prestamo  
   - `R = P * [i(1+i)^n] / [(1+i)^n - 1]`
9. Historial de calculos guardado en `history.log`

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

El proyecto incluye pruebas simples sin librerias externas, usando `assert` y `CTest`.

```bash
ctest --test-dir build --output-on-failure
```

También puedes ejecutar directamente:

```bash
./build/financial_calculator_tests
```

## Principios aplicados

- Programacion orientada a objetos (POO).
- Principios SOLID (responsabilidades separadas por capa y por clase).
- Validacion de entradas y manejo de errores.
- Persistencia desacoplada via interfaz `HistoryRepository` y adaptacion `FileHistoryRepository`.
