# cpp-assign

A C++20 helper analogous to structured bindings to transparently assign values from pairs and tuples to already existing variables

Example:

    std::tuple<int, float, std::string> create_tuple();
    std::pair<int, float> create_pair();
    
    int a;
    float b;
    std::string c;

    assign(a,b,c) = create_tuple();
    assign(a,b) = create_pair();

## Rationale

cpp-assign fills a gap in the C++ Standard Library by providing a modern, intuitive way to assign elements from std::pair and std::tuple to existing variables. Key advantages include:
* Complements Structured Bindings: Structured bindings (C++17) create new variables, whereas cpp-assign updates existing ones.
* Improves on std::tie: Unlike std::tie (C++11), which has a non-intuitive name, requires initialized variables, and lacks robust support for rvalues and move semantics, cpp-assign offers a cleaner syntax and stronger type safety.
* C++20 Features: Leverages concepts (`tuple_like`, `assignable_from`) for compile-time checks, ensuring size and type compatibility.
* Lightweight: Zero runtime overhead after optimization, with minimal compile-time cost.


## Installation

cpp-assign is a header-only library. To use it:

1. Copy the `assign.h` file into your project’s include directory.
2. Include the header in your source files:
   ```cpp
   #include "assign.h"
3. Compile with a C++20-compliant compiler (e.g., GCC 10+, Clang 10+, MSVC 2019+) using the -std=c++20 flag.

## Requirements

- C++20 or later (concepts, fold expressions, index sequences).
- Supported compilers: GCC 10+, Clang 10+, MSVC 2019+ (with `/std:c++20`).
- Standard library headers: `<tuple>`, `<utility>`, `<type_traits>`, `<concepts>`.

## Performance

`cpp-assign` is designed to be lightweight:
- **Runtime**: Zero overhead after compiler optimization (`-O2`), equivalent to manual assignments.
- **Compile-Time**: Minimal overhead from template instantiation, acceptable for most projects.
- **Code Size**: Comparable to direct assignments, with slight increases for template instantiations.

The library uses modern C++20 features to ensure efficiency while maintaining type safety.
## Comparisons to structured bindings
Structured bindings, introduced in C++17, provide a concise syntax for unpacking tuple-like objects (e.g., std::tuple, std::pair, structs) into new variables or references. While powerful, they differ significantly from cpp-assign in their purpose and capabilities.

### Purpose
**Structured Bindings**: Create new variables (or bind references) to hold the elements of a tuple-like object. Example:

    auto [a, b, c] = std::make_tuple(42, 3.14f, std::string("hello"));
    // a, b, c are new variables (or references if auto& is used)

**cpp-assign**: Assigns tuple-like elements to existing variables, updating their values without declaring new ones. Example:

    int a;
    float b;
    std::string c;
    assign(a, b, c) = std::make_tuple(42, 3.14f, std::string("hello"));
    // a, b, c are updated

### Use Case
**Structured Bindings**: Ideal for creating new variables in a single line, especially in modern C++ where immutability or local scope is preferred. Commonly used in range-based for loops or when unpacking function return values.

**cpp-assign**: Suited for updating pre-existing variables, such as class members, function-scoped variables with specific lifetimes, or variables that cannot be redeclared.

### Syntax
**Structured Bindings**: Concise and intuitive (`auto [a, b] = pair;`), but requires new variable declarations.

**cpp-assign**: `assign(a, b) = pair;` mirrors structured bindings’ style while targeting existing variables.

### Type Safety
**Structured Bindings**: Type-safe, with compile-time checks for size and type compatibility.

**cpp-assign**: Equally type-safe, using C++20 concepts (`tuple_like`, `assignable_from`) to ensure size matching and assignability, with clear error messages.

### Limitations
**Structured Bindings**: Cannot assign to existing variables, leading to verbose workarounds (e.g., manual assignments or std::tie).

**cpp-assign**: Requires C++20 and a header inclusion, slightly increasing compile-time complexity compared to the built-in structured bindings.

### When to Choose
Use **structured bindings** when you need new variables or references for tuple-like unpacking.

Use **cpp-assign** when you need to update existing variables with a clean, type-safe syntax.

## Comparison to std::tie
std::tie, introduced in C++11, allows assigning std::tuple elements to existing variables by creating a tuple of references. While it serves a similar purpose to cpp-assign, it has significant limitations that cpp-assign addresses.

### Purpose
**std::tie**: Creates a `std::tuple` of references to existing variables and assigns tuple elements to them. Example:

    int a;
    float b;
    std::string c;
    std::tie(a, b, c) = std::make_tuple(42, 3.14f, std::string("hello"));

**cpp-assign**: Assigns elements from std::tuple or std::pair to existing variables with a more intuitive syntax. Example:

    assign(a, b, c) = std::make_tuple(42, 3.14f, std::string("hello"));

### Syntax
**std::tie**: Less intuitive, as `std::tie(a, b, c) = tuple;` suggests binding rather than assignment, and the name “tie” is not descriptive of its purpose.

**cpp-assign**: More natural (`assign(a, b, c) = tuple;`), resembling structured bindings and clearly indicating assignment.

### Supported Types
**std::tie**: Only works with std::tuple, requiring explicit conversion for std::pair (e.g., `std::tie(a, b) = std::make_tuple(pair.first, pair.second);`).

**cpp-assign**: Natively supports both `std::tuple` and `std::pair`, with potential for custom tuple-like types via `std::tuple_size` and `std::get`.

### Move Semantics and Rvalues:
**std::tie**: Limited support for rvalues, as it always creates lvalue references. This can lead to unnecessary copies or prevent moves. Example:

    std::tie(a, b, c) = std::make_tuple(42, 3.14f, std::string("hello")); // Copies std::string

**cpp-assign**: Supports rvalues and move semantics efficiently, as the `operator=` takes a `const Tup&` (and could be extended for `Tup&&`), minimizing copies.

### Initialization Requirements:
**std::tie**: Requires variables to be initialized, or it results in undefined behavior (e.g., assigning to an uninitialized std::string causes issues).

**cpp-assign**: No such requirement, as it performs direct assignments, safely updating uninitialized variables if they support assignment.

### Type Safety
**std::tie**: Less robust, with minimal compile-time checks. Type mismatches or size mismatches may lead to subtle errors or undefined behavior.

**cpp-assign**: Uses C++20 concepts to enforce size matching and type assignability, providing clear compile-time errors.

### When to Choose
Use **std::tie** in pre-C++20 codebases or for simple tuple assignments where its limitations are acceptable.

Use **cpp-assign** for modern C++20 projects, especially when working with std::pair, needing move semantics, or requiring strong type safety and intuitive syntax.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Contributing

Contributions are welcome! To contribute:

1. Fork the repository.
2. Create a feature branch (`git checkout -b feature/your-feature`).
3. Commit your changes (`git commit -m "Add your feature"`).
4. Push to the branch (`git push origin feature/your-feature`).
5. Open a pull request.

Please include tests and documentation for new features. For standardisation proposals, contact the maintainer.
