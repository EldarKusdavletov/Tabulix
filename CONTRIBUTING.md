# Contributing to Tabulix

Thank you for considering contributing to Tabulix! This document outlines the process for contributing to the project.

## Code of Conduct

By participating in this project, you agree to maintain a respectful and inclusive environment for everyone.

## How to Contribute

### Reporting Bugs

Bugs should be reported through the issue tracker. When reporting a bug, please include:

- A clear and descriptive title
- Steps to reproduce the issue
- Expected behavior
- Actual behavior
- Any relevant code or error messages
- Your environment (compiler, OS, etc.)

### Suggesting Enhancements

Feature requests and suggestions are welcome. Please use the issue tracker and include:

- A clear and descriptive title
- A detailed description of the proposed feature
- Any relevant examples or use cases

### Pull Requests

1. Fork the repository
2. Create a new branch for your changes
3. Make your changes
4. Add or update tests as needed
5. Ensure all tests pass
6. Submit a pull request

#### Pull Request Guidelines

- Follow the existing code style
- Write clear, descriptive commit messages
- Include tests for new features or bug fixes
- Update documentation as needed
- Ensure all CI checks pass

## Development Setup

### Prerequisites

- C++26 compatible compiler (GCC 14+, Clang 18+, MSVC 19.38+)
- CMake 3.20 or higher
- Git

### Build Instructions

```bash
# Clone the repository
git clone https://github.com/username/tabulix.git
cd tabulix

# Create a build directory
mkdir build && cd build

# Configure and build
cmake ..
make

# Run tests
ctest
```

## Coding Standards

- Use modern C++ features (C++26)
- Follow the existing code style
- Use meaningful variable and function names
- Add comments for complex logic
- Write comprehensive unit tests

## License

By contributing to Tabulix, you agree that your contributions will be licensed under the project's License.
