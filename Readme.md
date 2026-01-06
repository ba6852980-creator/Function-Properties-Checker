# Function Properties Checker

A comprehensive C++ console application for analyzing mathematical functions and their properties in discrete mathematics.

## Overview

This interactive program allows users to define functions between finite sets and analyze various mathematical properties including injectivity, surjectivity, and bijectivity. It features a colorful text-based user interface with detailed explanations and step-by-step verification of function properties.

## Features

### Core Functionality
- **Define Custom Functions**: Create functions with custom domain and codomain sets
- **Function Display**: View complete function details including domain, codomain, range, and mappings
- **Property Checking**:
  - Injective (One-to-One) verification
  - Surjective (Onto) verification
  - Bijective property analysis
- **Inverse Function**: Calculate and verify inverse functions for bijective mappings
- **Function Composition**: Compose two functions (f ∘ g) with validation
- **Complete Analysis**: View all properties in a comprehensive summary table
- **Demo Examples**: Pre-loaded examples demonstrating different function types

### User Interface
- Colorful console interface with boundary drawing
- Centered, formatted output with color-coded results
- Step-by-step explanations with mathematical definitions
- Input validation ensuring mappings stay within codomain
- Clear error messages and violation reporting

## Installation

### Requirements
- Windows OS (uses Windows.h for console manipulation)
- C++ compiler with C++11 or later (MinGW, Visual Studio, etc.)
- Console with UTF-8 support for ASCII art display

### Compilation

Using g++:
```bash
g++ dm3.cpp -o FunctionChecker.exe
```

Using Visual Studio:
1. Create a new C++ Console Application project
2. Add `dm3.cpp` to the project
3. Build and run

## Main Menu Options

1. **Enter a new function** - Define domain, codomain, and mappings
2. **Display the function** - View complete function details
3. **Check if Injective (One-to-One)** - Verify one-to-one property
4. **Check if Surjective (Onto)** - Verify onto property
5. **Check if Bijective** - Verify both properties
6. **Find Inverse Function** - Calculate inverse (if bijective)
7. **Composition of Functions** - Compose two functions
8. **Check All Properties** - Complete analysis summary
9. **Run Example Demo** - Pre-loaded example functions
10. **Exit** - Close the application

## Usage Example

```
1. Select option [1] to define a new function
2. Enter domain size: 3
3. Enter domain elements: 1, 2, 3
4. Enter codomain size: 3
5. Enter codomain elements: 4, 5, 6
6. Define mappings:
   f(1) = 5
   f(2) = 4
   f(3) = 6
7. Use option [8] to check all properties
```

## Demo Examples

The program includes four built-in demonstrations:

### 1. Injective but NOT Surjective
- **Domain**: {1, 2, 3}
- **Codomain**: {4, 5, 6, 7}
- **Mapping**: 1→4, 2→5, 3→6
- Element 7 in codomain is not mapped

### 2. Surjective but NOT Injective
- **Domain**: {1, 2, 3, 4}
- **Codomain**: {5, 6, 7}
- **Mapping**: 1→5, 2→5, 3→6, 4→7
- Elements 1 and 2 both map to 5

### 3. Bijective Function
- **Domain**: {1, 2, 3}
- **Codomain**: {4, 5, 6}
- **Mapping**: 1→5, 2→4, 3→6
- Perfect one-to-one correspondence

### 4. Neither Injective nor Surjective
- **Domain**: {1, 2, 3}
- **Codomain**: {4, 5, 6, 7}
- **Mapping**: 1→4, 2→4, 3→5
- Multiple elements map to 4, and elements 6 and 7 are unmapped

## Mathematical Definitions

### Injective (One-to-One)
A function f: A → B is **injective** if different elements in A map to different elements in B.

**Formal Definition**: f(a₁) = f(a₂) implies a₁ = a₂

**Example**: f(1) = 4, f(2) = 5, f(3) = 6 is injective

### Surjective (Onto)
A function f: A → B is **surjective** if every element in B is mapped to by at least one element in A.

**Formal Definition**: Range(f) = Codomain(B)

**Example**: With codomain {4, 5, 6}, if all three values are hit, the function is surjective

### Bijective
A function is **bijective** if it is both injective AND surjective.

**Important**: Only bijective functions have inverse functions

### Function Composition
For functions f: A → B and g: C → D, the composition **(f ∘ g)(x) = f(g(x))** is valid only if:
- Range(g) ⊆ Domain(f)

## Technical Details

### Data Structures
```cpp
const int MAX = 50;              // Maximum elements
int domainA[MAX];                // Domain set A
int codomainB[MAX];              // Codomain set B
int mapping[MAX];                // Function mapping f: A → B
int domainSize, codomainSize;    // Set sizes
```

### Key Functions
- `inputFunction()` - Define new function with validation
- `checkInjective()` - Verify one-to-one property
- `checkSurjective()` - Verify onto property
- `checkBijective()` - Verify both properties
- `findInverse()` - Calculate inverse function
- `composeFunctions()` - Compose two functions
- `checkAllProperties()` - Complete analysis

### Console Features
- Custom cursor positioning with `gotoxy(x, y)`
- Color-coded output using Windows console attributes
- Dynamic boundary drawing based on console size
- Hidden cursor during output for cleaner display

## Color Coding

| Color | Code | Usage |
|-------|------|-------|
| Cyan | 11 | Borders and separators |
| Yellow | 14 | Section headers and prompts |
| White | 15 | Important titles |
| Green | 10 | Success messages and positive results |
| Red | 12 | Error messages and violations |
| Gray | 7 | Standard text |

## Limitations

- Maximum 50 elements per set
- Windows-only (uses Windows.h for console manipulation)
- Finite sets only (no support for infinite domains)
- Integer elements only

## Educational Purpose

This project was developed as a **Discrete Mathematics course project** to demonstrate:
- Practical applications of function theory
- Set operations and mathematical property verification
- Interactive educational software development
- Algorithm implementation for mathematical concepts

## Future Enhancements

Potential improvements could include:
- Support for real number sets
- Graphical visualization of functions
- Export results to file
- Cross-platform compatibility (Linux/Mac)
- Support for multiple function comparisons
- Function arithmetic operations

## Developers

**Created by:**
- Muhammad Bilal Arshad
- Ali Sher

## License

This project is developed for educational purposes as part of a Discrete Mathematics course.

## Contributing

This is an educational project. Suggestions and improvements are welcome for learning purposes.

---

**Note**: This program uses Windows-specific console functions. For cross-platform compatibility, consider using libraries like ncurses (Linux) or implementing platform-independent console handling.