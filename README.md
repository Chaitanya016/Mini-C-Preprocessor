# Mini C Preprocessor in C

## Overview
This project implements a simplified version of the C preprocessor. It simulates some of the operations performed by the C compiler during the preprocessing stage before actual compilation.

The project is developed entirely in C using file handling, string manipulation, and modular programming techniques.

---

## Features

- Macro substitution using `#define`
- Function-like macro substitution
- Header file inclusion using `#include`
- Nested header file inclusion
- Comment removal
- Source code transformation before compilation
- Multi-file project structure
- Makefile support

---

## Technologies Used

- C Programming
- File Handling
- String Manipulation
- Dynamic Memory Management
- Multi-file Programming
- Makefile
- Git & GitHub

---

## Project Structure

```
mini-c-preprocessor/
│
├── src/
├── include/
├── input/
├── output/
├── Makefile
├── README.md
└── .gitignore
```

---

## How to Build

```bash
make
```

---

## How to Run

```bash
./exe input.c
```

or

```bash
./a.out input.c
```

(depending on your executable name)

---

## Supported Preprocessor Directives

| Directive | Supported |
|-----------|------------|
| #define | Yes |
| Macro with Arguments | Yes |
| #include | Yes |
| Nested Header Files | Yes |
| Comment Removal | Yes |

---

## Example

### Input

```c
#define PI 3.14
#define SQR(x) ((x)*(x))

#include "header.h"

// sample comment

int main()
{
    printf("%f", PI);
    printf("%d", SQR(5));
}
```

### Output

```c
int main()
{
    printf("%f", 3.14);
    printf("%d", ((5)*(5)));
}
```

---

## Learning Outcomes

- Understanding the C compilation process
- Working with preprocessor directives
- File parsing and transformation
- Macro expansion techniques
- Modular programming and Makefiles
- Git and GitHub workflow

---

## Author

Chaitanya Sai Parimi

ECE Graduate | Embedded Systems & Systems Programming

This repository contains my modified and improved version of the original Mini C Preprocessor project.