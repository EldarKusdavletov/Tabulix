/**
 * @file basic_example.cpp
 * @brief Basic example of using the Tabulix library
 */

#include <tabulix/tabulix.hpp>
#include <iostream>
#include <vector>

int main() {
    // Create a table
    tabulix::Table table;

    // Add headers
    table.addHeader({"Name", "Age", "City"});

    // Add rows
    table.addRow({"Alice", "28", "New York"});
    table.addRow({"Bob", "32", "London"});
    table.addRow({"Charlie", "45", "Tokyo"});

    // Set column alignments
    table.setColumnAlignment(0, tabulix::Alignment::LEFT);
    table.setColumnAlignment(1, tabulix::Alignment::RIGHT);
    table.setColumnAlignment(2, tabulix::Alignment::CENTER);

    // Try different themes
    std::cout << "Simple theme:\n";
    table.setTheme(tabulix::Theme::SIMPLE);
    std::cout << table << "\n";

    std::cout << "Unicode single-line theme:\n";
    table.setTheme(tabulix::Theme::UNICODE_SINGLE);
    std::cout << table << "\n";

    std::cout << "Unicode double-line theme:\n";
    table.setTheme(tabulix::Theme::UNICODE_DOUBLE);
    std::cout << table << "\n";

    std::cout << "Markdown theme:\n";
    table.setTheme(tabulix::Theme::MARKDOWN);
    std::cout << table << "\n";

    return 0;
}
