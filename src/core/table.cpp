/**
 * @file table.cpp
 * @brief Implementation of the Table class
 */

#include "tabulix/core/table.hpp"
#include "tabulix/styling/theme.hpp"
#include <algorithm>
#include <numeric>
#include <stdexcept>

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

std::vector<size_t> Table::calculateColumnWidths() const {
    const size_t columns = columnCount();
    if (columns == 0) return {};

    std::vector<size_t> widths(columns, 0);

    // Check header widths
    if (m_header.has_value()) {
        for (size_t i = 0; i < m_header->size() && i < columns; ++i) {
            widths[i] = std::max(widths[i], m_header->at(i).width());
        }
    }

    // Check data row widths
    for (const auto& row : m_rows) {
        for (size_t i = 0; i < row.size() && i < columns; ++i) {
            widths[i] = std::max(widths[i], row.at(i).width());
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
            return text;
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
        if (hasBorder) {
            result += m_border.vertical();
        }

        for (size_t i = 0; i < columns; ++i) {
            const auto& cell = i < m_header->size() ? m_header->at(i) : Cell("");
            Alignment align = cell.alignment().value_or(
                i < m_columnAlignments.size() ? m_columnAlignments[i] : Alignment::LEFT
            );

            result += " " + padCell(cell.value(), columnWidths[i], align) + " ";

            if (hasBorder && i < columns - 1) {
                result += m_border.vertical();
            }
        }

        if (hasBorder) {
            result += m_border.vertical();
        }
        result += "\n";

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

        if (hasBorder) {
            result += m_border.vertical();
        }

        for (size_t i = 0; i < columns; ++i) {
            const auto& cell = i < row.size() ? row.at(i) : Cell("");
            Alignment align = cell.alignment().value_or(
                i < m_columnAlignments.size() ? m_columnAlignments[i] : Alignment::LEFT
            );

            result += " " + padCell(cell.value(), columnWidths[i], align) + " ";

            if (hasBorder && i < columns - 1) {
                result += m_border.vertical();
            }
        }

        if (hasBorder) {
            result += m_border.vertical();
        }
        result += "\n";

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
