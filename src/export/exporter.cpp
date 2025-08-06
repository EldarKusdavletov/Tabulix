/**
 * @file exporter.cpp
 * @brief Implementation of the Exporter class and derived exporters
 */

#include "tabulix/export/exporter.hpp"
#include <sstream>
#include <fstream>
#include <stdexcept>

namespace tabulix {

bool Exporter::toFile(const Table& table, const std::string& filename) const {
    try {
        std::ofstream file(filename);
        if (!file.is_open()) {
            return false;
        }
        file << toString(table);
        return !file.bad();
    } catch (...) {
        return false;
    }
}

std::unique_ptr<Exporter> Exporter::create(ExportFormat format) {
    switch (format) {
        case ExportFormat::TEXT:
            return std::make_unique<TextExporter>();
        case ExportFormat::MARKDOWN:
            return std::make_unique<MarkdownExporter>();
        case ExportFormat::HTML:
            return std::make_unique<HtmlExporter>();
        case ExportFormat::CSV:
            return std::make_unique<CsvExporter>();
        case ExportFormat::JSON:
            return std::make_unique<JsonExporter>();
        default:
            throw std::invalid_argument("Unknown export format");
    }
}

// TextExporter implementation
std::string TextExporter::toString(const Table& table) const {
    return table.str();
}

// MarkdownExporter implementation
std::string MarkdownExporter::toString(const Table& table) const {
    if (table.empty()) {
        return "";
    }

    const size_t columns = table.columnCount();
    std::stringstream ss;

    // Create a temporary table with Markdown theme
    Table mdTable = table;
    mdTable.setTheme(Theme::MARKDOWN);

    return mdTable.str();
}

// HtmlExporter implementation
std::string HtmlExporter::toString(const Table& table) const {
    if (table.empty()) {
        return "<table></table>";
    }

    std::stringstream ss;
    ss << "<table>\n";

    const size_t columns = table.columnCount();

    // TODO: Implement HTML table generation
    // This is a placeholder implementation

    ss << "</table>";
    return ss.str();
}

// CsvExporter implementation
CsvExporter::CsvExporter(char delimiter) : m_delimiter(delimiter) {
}

std::string CsvExporter::toString(const Table& table) const {
    if (table.empty()) {
        return "";
    }

    // TODO: Implement CSV export
    // This is a placeholder implementation

    return "";
}

// JsonExporter implementation
std::string JsonExporter::toString(const Table& table) const {
    if (table.empty()) {
        return "[]";
    }

    // TODO: Implement JSON export
    // This is a placeholder implementation

    return "[]";
}

} // namespace tabulix
