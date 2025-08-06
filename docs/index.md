# Tabulix Documentation

Welcome to the Tabulix documentation. This library provides a high-performance, C++26-compatible solution for creating and formatting tables.

## Table of Contents

- [Getting Started](#getting-started)
- [Core Concepts](#core-concepts)
- [API Reference](#api-reference)
- [Examples](#examples)
- [Styling](#styling)
- [Exporters](#exporters)
- [Performance](#performance)
- [Contributing](#contributing)

## Getting Started

### Installation

Tabulix can be integrated into your project using CMake:

```bash
git clone https://github.com/username/tabulix.git
cd tabulix
mkdir build && cd build
cmake ..
make
make install
```

Or simply include the headers in your project for header-only usage.

### Basic Usage

```cpp
#include <tabulix/tabulix.hpp>
#include <iostream>

int main() {
    // Create a table
    tabulix::Table table;

    // Add headers
    table.addHeader({"Name", "Age", "City"});

    // Add rows
    table.addRow({"Alice", "28", "New York"});
    table.addRow({"Bob", "32", "London"});

    // Apply a theme
    table.setTheme(tabulix::Theme::UNICODE_SINGLE);

    // Print the table
    std::cout << table << std::endl;

    return 0;
}
```

## Core Concepts

Tabulix is built around these primary concepts:

- **Table**: The main container for your data
- **Row**: A collection of cells that form a horizontal line in the table
- **Cell**: An individual data element within the table
- **Theme**: Predefined styling for the entire table
- **Border**: Configuration for how table borders are displayed
- **Alignment**: Text alignment within cells (left, center, right)

## API Reference

For detailed API documentation, see:

- [Table Class](api/table.md)
- [Row Class](api/row.md)
- [Cell Class](api/cell.md)
- [Theme Enum](api/theme.md)
- [Border Class](api/border.md)
- [Alignment Enum](api/alignment.md)
- [Exporter Classes](api/exporter.md)

## Examples

See the [examples](../examples) directory for more examples of using Tabulix.

## Styling

Tabulix provides multiple ways to style your tables:

### Themes

```cpp
table.setTheme(tabulix::Theme::UNICODE_DOUBLE);
```

Available themes:
- `NONE`: No borders or separators
- `SIMPLE`: Simple ASCII borders (default)
- `GRID`: Full ASCII grid
- `UNICODE_SINGLE`: Unicode single-line borders
- `UNICODE_DOUBLE`: Unicode double-line borders
- `MARKDOWN`: Markdown-style table
- `MINIMAL`: Minimal borders
- `COMPACT`: Compact style with minimal spacing
- `DOTTED`: Dotted borders
- `DASHED`: Dashed borders
- `FANCY`: Fancy decorative borders

### Custom Borders

```cpp
tabulix::Border customBorder("-", "|", "+", "+", "+", "+", "+", "+", "+", "+", "+");
table.setBorder(customBorder);
```

### Alignment

```cpp
table.setColumnAlignment(0, tabulix::Alignment::LEFT);
table.setColumnAlignment(1, tabulix::Alignment::CENTER);
table.setColumnAlignment(2, tabulix::Alignment::RIGHT);
```

## Exporters

Tabulix supports exporting tables to different formats:

```cpp
// Create an exporter
std::unique_ptr<tabulix::Exporter> exporter = tabulix::Exporter::create(tabulix::ExportFormat::MARKDOWN);

// Export to string
std::string markdown = exporter->toString(table);

// Export to file
exporter->toFile(table, "output.md");
```

Supported formats:
- `TEXT`: Plain text (default table rendering)
- `MARKDOWN`: Markdown table format
- `HTML`: HTML table
- `CSV`: Comma-separated values
- `JSON`: JSON array format

## Performance

Tabulix is designed with performance in mind:

- Minimal memory allocations
- Efficient string handling
- Optimized rendering algorithms
- No external dependencies

## Contributing

Contributions are welcome! See [CONTRIBUTING.md](../CONTRIBUTING.md) for guidelines.
