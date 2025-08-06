/**
 * @file advanced_example.cpp
 * @brief Advanced example of using the Tabulix library
 */

#include <tabulix/tabulix.hpp>
#include <iostream>
#include <vector>
#include <string>

int main() {
    // Create a table with student data
    tabulix::Table students;

    // Add headers with alignment
    students.addHeader({"ID", "Student", "Grade", "Percentage", "Status"});
    students.setColumnAlignment(0, tabulix::Alignment::CENTER);
    students.setColumnAlignment(1, tabulix::Alignment::LEFT);
    students.setColumnAlignment(2, tabulix::Alignment::CENTER);
    students.setColumnAlignment(3, tabulix::Alignment::RIGHT);
    students.setColumnAlignment(4, tabulix::Alignment::CENTER);

    // Add rows
    students.addRow({"1", "John Smith", "A", "95.2%", "PASS"});
    students.addRow({"2", "Emily Johnson", "B+", "87.5%", "PASS"});
    students.addRow({"3", "Michael Brown", "C", "75.0%", "PASS"});
    students.addRow({"4", "Jessica Davis", "F", "32.5%", "FAIL"});
    students.addRow({"5", "Christopher Wilson", "A-", "91.0%", "PASS"});

    // Set theme
    students.setTheme(tabulix::Theme::UNICODE_DOUBLE);

    // Print the table
    std::cout << "Student Grades Report" << std::endl;
    std::cout << students << std::endl;

    // Export to different formats
    std::unique_ptr<tabulix::Exporter> mdExporter = tabulix::Exporter::create(tabulix::ExportFormat::MARKDOWN);
    std::cout << "\nMarkdown Export:\n" << mdExporter->toString(students) << std::endl;

    // Table with nested content
    tabulix::Table nested;
    nested.addHeader({"Category", "Details", "Comments"});

    // Add rows with multiline content
    nested.addRow({"Fruits", "Apple\nBanana\nOrange", "Fresh and organic"});
    nested.addRow({"Vegetables", "Carrot\nBroccoli\nSpinach", "Locally sourced"});
    nested.addRow({"Grains", "Rice\nWheat\nOats", "Whole grain options available"});

    // Set theme
    nested.setTheme(tabulix::Theme::GRID);

    // Print the nested table
    std::cout << "\nTable with Multiline Content:\n" << nested << std::endl;

    return 0;
}
