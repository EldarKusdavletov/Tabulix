# Table Class

The `Table` class is the main container for tabular data in Tabulix.

## Overview

```cpp
namespace tabulix {
class Table {
    // ...
};
}
```

The `Table` class provides methods for adding headers and rows, styling the table, and rendering it to a string.

## Constructors

```cpp
// Default constructor
Table();

// Constructor with headers (vector)
Table(const std::vector<std::string>& headers);

// Constructor with headers (initializer list)
Table(std::initializer_list<std::string> headers);
```

## Adding Content

```cpp
// Add a header row from a vector
Table& addHeader(const std::vector<std::string>& headers);

// Add a header row from an initializer list
Table& addHeader(std::initializer_list<std::string> headers);

// Add a data row from a vector
template <typename T>
requires std::convertible_to<T, std::string>
Table& addRow(const std::vector<T>& cells);

// Add a data row from an initializer list
template <typename T>
requires std::convertible_to<T, std::string>
Table& addRow(std::initializer_list<T> cells);

// Add a pre-constructed Row
Table& addRow(const Row& row);
```

## Styling

```cpp
// Set the theme
Table& setTheme(Theme theme);

// Set custom border style
Table& setBorder(const Border& border);

// Set alignment for a specific column
Table& setColumnAlignment(size_t columnIndex, Alignment alignment);

// Set the width for a specific column
Table& setColumnWidth(size_t columnIndex, std::optional<size_t> width);
```

## Querying

```cpp
// Get the number of rows (including header)
[[nodiscard]] size_t rowCount() const noexcept;

// Get the number of columns
[[nodiscard]] size_t columnCount() const noexcept;

// Check if the table is empty
[[nodiscard]] bool empty() const noexcept;

// Clear all rows from the table
Table& clear() noexcept;
```

## Rendering

```cpp
// Get a string representation of the table
[[nodiscard]] std::string str() const;

// Output stream operator
friend std::ostream& operator<<(std::ostream& os, const Table& table);
```

## Example Usage

```cpp
#include <tabulix/tabulix.hpp>
#include <iostream>

int main() {
    // Create a table with headers
    tabulix::Table table({"Name", "Age", "City"});

    // Add rows
    table.addRow({"Alice", "28", "New York"});
    table.addRow({"Bob", "32", "London"});

    // Style the table
    table.setTheme(tabulix::Theme::UNICODE_SINGLE);
    table.setColumnAlignment(1, tabulix::Alignment::RIGHT);

    // Print the table
    std::cout << table << std::endl;

    return 0;
}
```
