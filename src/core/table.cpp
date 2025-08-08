/**
 * @file table.cpp
 * @brief Implementation of the Table class
 */

#include "tabulix/core/table.hpp"
#include "tabulix/styling/theme.hpp"
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <sstream>

namespace tabulix {

Table::Table(const std::vector<std::string>& headers) {
    addHeader(headers);
}

Table::Table(std::initializer_list<std::string> headers) {
    addHeader(headers);
}

Table& Table::addHeader(const std::vector<std::string>& headers) {
    Row row;
    for (const auto& header : headers) {
        row.addCell(header);
    }
    m_header = row;

    // Ensure column alignments and widths are initialized
    if (m_columnAlignments.size() < row.size()) {
        m_columnAlignments.resize(row.size(), Alignment::LEFT);
    }
    if (m_columnWidths.size() < row.size()) {
        m_columnWidths.resize(row.size(), std::nullopt);
    }

    return *this;
}

Table& Table::addHeader(std::initializer_list<std::string> headers) {
    return addHeader(std::vector<std::string>(headers));
}

Table& Table::addRow(const Row& row) {
    m_rows.push_back(row);

    // Ensure column alignments and widths are initialized if this is the first row
    if (m_columnAlignments.empty()) {
        m_columnAlignments.resize(row.size(), Alignment::LEFT);
    }
    if (m_columnWidths.empty()) {
        m_columnWidths.resize(row.size(), std::nullopt);
    }

    return *this;
}

Table& Table::setTheme(Theme theme) {
    m_theme = theme;
    m_border = getBorderForTheme(theme);
    return *this;
}

Table& Table::setBorder(const Border& border) {
    m_border = border;
    return *this;
}

Table& Table::setColumnAlignment(size_t columnIndex, Alignment alignment) {
    if (columnIndex >= m_columnAlignments.size()) {
        m_columnAlignments.resize(columnIndex + 1, Alignment::LEFT);
    }
    m_columnAlignments[columnIndex] = alignment;
    return *this;
}

Table& Table::setColumnWidth(size_t columnIndex, std::optional<size_t> width) {
    if (columnIndex >= m_columnWidths.size()) {
        m_columnWidths.resize(columnIndex + 1, std::nullopt);
    }
    m_columnWidths[columnIndex] = width;
    return *this;
}

size_t Table::rowCount() const noexcept {
    return m_rows.size() + (m_header.has_value() ? 1 : 0);
}

size_t Table::columnCount() const noexcept {
    if (m_header.has_value()) {
        return m_header->size();
    }
    if (!m_rows.empty()) {
        return m_rows[0].size();
    }
    return 0;
}

bool Table::empty() const noexcept {
    return m_rows.empty() && !m_header.has_value();
}

Table& Table::clear() noexcept {
    m_rows.clear();
    m_header.reset();
    return *this;
}

std::string Table::str() const {
    return render();
}

std::ostream& operator<<(std::ostream& os, const Table& table) {
    return os << table.str();
}

// Helper function to split text by newlines
std::vector<std::string> Table::splitLines(const std::string& text) const {
    std::vector<std::string> lines;
    std::stringstream ss(text);
    std::string line;

    while (std::getline(ss, line)) {
        lines.push_back(line);
    }

    // Handle case where text doesn't end with newline or is empty
    if (lines.empty()) {
        lines.push_back(text);
    }

    return lines;
}

// Helper function to get maximum line width in a multiline text
size_t Table::getMaxLineWidth(const std::string& text) const {
    const auto lines = splitLines(text);
    size_t maxWidth = 0;
    for (const auto& line : lines) {
        maxWidth = std::max(maxWidth, line.size());
    }
    return maxWidth;
}

std::vector<size_t> Table::calculateColumnWidths() const {
    const size_t columns = columnCount();
    if (columns == 0) return {};

    std::vector<size_t> widths(columns, 0);

    // Check header widths (considering multiline content)
    if (m_header.has_value()) {
        for (size_t i = 0; i < m_header->size() && i < columns; ++i) {
            const std::string cellValue = m_header->at(i).value();
            widths[i] = std::max(widths[i], getMaxLineWidth(cellValue));
        }
    }

    // Check data row widths (considering multiline content)
    for (const auto& row : m_rows) {
        for (size_t i = 0; i < row.size() && i < columns; ++i) {
            const std::string cellValue = row.at(i).value();
            widths[i] = std::max(widths[i], getMaxLineWidth(cellValue));
        }
    }

    // Apply user-defined column widths
    for (size_t i = 0; i < m_columnWidths.size() && i < columns; ++i) {
        if (m_columnWidths[i].has_value()) {
            widths[i] = m_columnWidths[i].value();
        }
    }

    return widths;
}

std::string Table::render() const {
    if (empty()) {
        return "";
    }

    const auto columnWidths = calculateColumnWidths();
    const size_t columns = columnWidths.size();
    const bool hasBorder = m_border.enabled();

    std::string result;

    // Helper for padding cells according to alignment
    auto padCell = [&](const std::string& text, size_t width, Alignment align) -> std::string {
        if (text.size() >= width) {
            return text.substr(0, width); // Truncate if too long
        }

        switch (align) {
            case Alignment::RIGHT: {
                return std::string(width - text.size(), ' ') + text;
            }
            case Alignment::CENTER: {
                size_t leftPad = (width - text.size()) / 2;
                size_t rightPad = width - text.size() - leftPad;
                return std::string(leftPad, ' ') + text + std::string(rightPad, ' ');
            }
            case Alignment::LEFT:
            default: {
                return text + std::string(width - text.size(), ' ');
            }
        }
    };

    // Helper to render a multi-line row
    auto renderMultilineRow = [&](const Row& row) -> std::string {
        std::string rowResult;

        // Split all cells in the row into lines
        std::vector<std::vector<std::string>> cellLines(columns);
        size_t maxLines = 0;

        for (size_t i = 0; i < columns; ++i) {
            const auto& cell = i < row.size() ? row.at(i) : Cell("");
            cellLines[i] = splitLines(cell.value());
            maxLines = std::max(maxLines, cellLines[i].size());
        }

        // Ensure all cells have the same number of lines (pad with empty strings)
        for (auto& lines : cellLines) {
            while (lines.size() < maxLines) {
                lines.emplace_back("");
            }
        }

        // Render each line of the row
        for (size_t lineIdx = 0; lineIdx < maxLines; ++lineIdx) {
            if (hasBorder) {
                rowResult += m_border.vertical();
            }

            for (size_t i = 0; i < columns; ++i) {
                const auto& cell = i < row.size() ? row.at(i) : Cell("");
                Alignment align = cell.alignment().value_or(
                    i < m_columnAlignments.size() ? m_columnAlignments[i] : Alignment::LEFT
                                                           );

                const std::string& lineText = cellLines[i][lineIdx];
                rowResult += " " + padCell(lineText, columnWidths[i], align) + " ";

                if (hasBorder && i < columns - 1) {
                    rowResult += m_border.vertical();
                }
            }

            if (hasBorder) {
                rowResult += m_border.vertical();
            }
            rowResult += "\n";
        }

        return rowResult;
    };

    // Render top border
    if (hasBorder) {
        result += m_border.topLeft();
        for (size_t i = 0; i < columns; ++i) {
            result += std::string(columnWidths[i] + 2, m_border.horizontal()[0]);
            if (i < columns - 1) {
                result += m_border.topIntersection();
            }
        }
        result += m_border.topRight() + "\n";
    }

    // Render header
    if (m_header.has_value()) {
        result += renderMultilineRow(*m_header);

        // Render header separator
        if (hasBorder) {
            result += m_border.leftIntersection();
            for (size_t i = 0; i < columns; ++i) {
                result += std::string(columnWidths[i] + 2, m_border.horizontal()[0]);
                if (i < columns - 1) {
                    result += m_border.crossIntersection();
                }
            }
            result += m_border.rightIntersection() + "\n";
        }
    }

    // Render data rows
    for (size_t rowIdx = 0; rowIdx < m_rows.size(); ++rowIdx) {
        const auto& row = m_rows[rowIdx];
        result += renderMultilineRow(row);

        // Add row separator if not the last row
        if (hasBorder && rowIdx < m_rows.size() - 1) {
            result += m_border.leftIntersection();
            for (size_t i = 0; i < columns; ++i) {
                result += std::string(columnWidths[i] + 2, m_border.horizontal()[0]);
                if (i < columns - 1) {
                    result += m_border.crossIntersection();
                }
            }
            result += m_border.rightIntersection() + "\n";
        }
    }

    // Render bottom border
    if (hasBorder) {
        result += m_border.bottomLeft();
        for (size_t i = 0; i < columns; ++i) {
            result += std::string(columnWidths[i] + 2, m_border.horizontal()[0]);
            if (i < columns - 1) {
                result += m_border.bottomIntersection();
            }
        }
        result += m_border.bottomRight() + "\n";
    }

    return result;
}

} // namespace tabulix
