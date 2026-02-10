# ECE 250 Data Structures

A study repository for understanding and practicing data structures and algorithms in C++ for ECE 250 at the University of Waterloo.

## Usage

Build and run a specific data structure:

```zsh
make TARGET=<directory> run
```

For example:

```zsh
make TARGET=stack run
```

To clean build artifacts:

```zsh
make clean
```

## Project Structure

Each data structure lives in its own directory with:
- A header file (`.h`) containing the implementation
- A `main.cpp` with tests

Tests use a lightweight custom framework (`testing/test.h`) with assertion macros like `ASSERT_TRUE`, `ASSERT_EQ`, and `ASSERT_THROW`.
