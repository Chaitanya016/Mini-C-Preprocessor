# Mini C Preprocessor

A modular C-based preprocessor that performs basic source-code preprocessing operations such as comment removal, header-file inclusion, and macro expansion.

This repository is a modified and improved version of an existing Mini C Preprocessor implementation. The improvements focus on reliability, memory safety, build quality, portability, and testing.

---

## Overview

The project implements a simplified version of some operations performed by the C preprocessor before compilation.

The preprocessor takes a C source file as input and generates a .i file containing the transformed source.


## Processing Flow

```text
C Source File
     |
     v
Read Source File
     |
     v
Remove Comments
     |
     v
Header Inclusion
     |
     v
Macro Processing
     |
     v
Generate .i File
```


## Features
- Single-line comment removal using //
- Multi-line comment removal using /* ... */
- System header inclusion using #include <...>
- User-defined header inclusion
- Nested header inclusion
- Object-like macro expansion
- Function-like macro processing
- Generation of preprocessed .i output
- Modular C implementation
- Makefile-based build system
- Compiler warnings enabled with -Wall -Wextra
- Debug build support with -g
- AddressSanitizer-based memory debugging
- Improved input-file and error handling
- Improved memory management
- macOS-compatible system header handling



## Project Structure

```text
Mini-C-Preprocessor/
├── main.c
├── header.h
├── headerFile_Inclusion.c
├── removeComments.c
├── replaceMacro.c
├── makefile
├── README.md
└── .gitignore
```


# Module Description
| File | Responsibility |
|---|---|
| `main.c` | Program entry point, file handling, and preprocessing workflow |
| `removeComments.c` | Removes single-line and multi-line comments |
| `headerFile_Inclusion.c` | Processes system and user-defined header inclusion |
| `replaceMacro.c` | Performs macro expansion and replacement |
| `header.h` | Shared declarations and required headers |
| `makefile` | Build and cleanup automation |
| `README.md` | Project documentation |


# Requirements
- GCC or Clang
- Make
- macOS
- Standard C development environment
The current implementation includes macOS SDK header handling for system includes.

## Build

Clone the repository:

```bash
git clone https://github.com/Chaitanya016/Mini-C-Preprocessor.git
cd Mini-C-Preprocessor
```

Build the project:

```bash
make
```

This generates:

```text
my_preprocessor
```

To clean the generated build files:

```bash
make clean
```
## Usage

Run the preprocessor by passing a C source file:

```bash
./my_preprocessor input.c
```

### Example

```bash
./my_preprocessor test.c
```

The program generates a preprocessed output file:

```text
test.i
```

You can inspect the output using:

```bash
cat test.i
```
# Example:
./my_preprocessor test.c

The program generates a preprocessed output file:
test.i

You can inspect the output using:
cat test.i

### Input

```c
#include <stdio.h>

#define VALUE 100

int main()
{
    // Single-line comment

    /*
       Multi-line comment
    */

    printf("%d\n", VALUE);

    return 0;
}
```

### Output

After preprocessing, the relevant source becomes:

```c
int main()
{
    printf("%d\n", 100);

    return 0;
}
```
System header contents may also appear in the generated `.i` file because the implementation performs header inclusion.




## Improvements Made

This repository started from an existing Mini C Preprocessor implementation. The following improvements were made during development.

- **Standardized `main()`**
  - Changed the non-standard `void main()` to `int main()`.
  - Added appropriate return codes.

- **Improved Input File Handling**
  - Changed input-file opening from append mode to read mode:
    ```c
    fopen(argv[1], "r");
    ```
  - Prevents a missing input file from being unintentionally created.

- **Improved Output File Handling**
  - The `.i` file is now created only after successful input-file validation.

- **Corrected `fgetc()` and EOF Handling**
  - Changed character variables used with `fgetc()` from `char` to `int` so that `EOF` can be handled correctly.

- **Improved Makefile**
  - Added `-Wall -Wextra -g`.
  - Added object-file dependencies.
  - Added a `clean` target.

- **Fixed Compiler Warnings**
  - Investigated and resolved warnings involving unused variables, uninitialized variables, and type mismatches.
  - The project now builds without compiler warnings.

- **Fixed Memory Management**
  - Used AddressSanitizer to identify a double-free involving memory shared between `main()` and the macro replacement module.
  - Removed the duplicate deallocation after tracing ownership of the allocated buffer.

- **Improved Portability**
  - The original implementation used `/usr/include/` for system headers.
  - The header inclusion logic was adapted for the macOS SDK environment.

# Testing
The project was tested for:
- Single-line comment removal
- Multi-line comment removal
- Macro replacement
- System header inclusion
- Missing input-file handling
- Clean compilation with -Wall -Wextra
- Memory safety using AddressSanitizer

### AddressSanitizer

Memory debugging was performed using:

```bash
gcc -Wall -Wextra -g -fsanitize=address \
    -fno-omit-frame-pointer \
    main.c headerFile_Inclusion.c removeComments.c replaceMacro.c \
    -o my_preprocessor_asan
```

The comment-removal and macro-expansion test cases completed without AddressSanitizer errors.


# Technologies Used
- C
- GCC / Clang
- Make
- File I/O
- Dynamic memory allocation
- String processing
- C preprocessor concepts
- AddressSanitizer
- Git
- GitHub


# Future Improvements
- Make system-header paths configurable
- Add support for #ifdef, #ifndef, #if, and #endif
- Improve function-like macro parsing
- Add automated test cases
- Add GitHub Actions CI
- Improve error reporting
- Support configurable include directories
- Improve Linux/macOS portability


# Author
Chaitanya Sai Parimi
ECE Graduate | Embedded Systems & Systems Programming
This repository is a modified and improved version of an existing Mini C Preprocessor implementation.