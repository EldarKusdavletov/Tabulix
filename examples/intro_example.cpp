/**
 * @file intro_example.cpp
 * @brief Intro example of using the Tabulix library
 */

#include <tabulix/tabulix.hpp>
#include <iostream>

int main() {
    // Create a table
    tabulix::Table table;

    // Add headers
    table.addHeader({"Left Aligned", "Center Aligned", "Right Aligned"});

    // Set column alignments
    table.setColumnAlignment(0, tabulix::Alignment::LEFT);
    table.setColumnAlignment(1, tabulix::Alignment::CENTER);
    table.setColumnAlignment(2, tabulix::Alignment::RIGHT);

    // Add rows
    table.addRow({"Tabulix", "Dynamic Library", "for C++26"});
    table.addRow({"Simple", "Elegant", "Fast"});

    table.setTheme(tabulix::Theme::NONE);
    std::cout << table << "\n";

    // Try different themes

    std::cout << "Grid theme:\n";
    table.setTheme(tabulix::Theme::GRID);
    std::cout << table << "\n";

    std::cout << "Markdown theme:\n";
    table.setTheme(tabulix::Theme::MARKDOWN);
    std::cout << table << "\n";

    std::cout << "Custom theme:\n";
    table.setBorder({"1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B"});
    std::cout << table << "\n";

    return 0;
}
