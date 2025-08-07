/**
 * @file table.hpp
 * @brief Definition of the Table class
 */

#ifndef TABULIX_CORE_TABLE_HPP
#define TABULIX_CORE_TABLE_HPP

#include <vector>
#include <string>
#include <ostream>
#include <optional>
#include <concepts>
#include <format>
#include <ranges>

#include "row.hpp"
#include "../styling/theme.hpp"
#include "../styling/border.hpp"
#include "../styling/alignment.hpp"

namespace tabulix {

/**
 * @class Table
 * @brief Main class for creating and formatting tables
 */
class Table {
public:
    /**
     * @brief Default constructor
     */
    Table() = default;

    /**
     * @brief Constructor with headers
     * @param headers Vector of header strings
     */
    explicit Table(const std::vector<std::string>& headers);

    /**
     * @brief Constructor with headers
     * @param headers Initializer list of header strings
     */
    Table(std::initializer_list<std::string> headers);

    /**
     * @brief Add a header row to the table
     * @param headers Vector of header strings
     * @return Reference to this table for method chaining
     */
    Table& addHeader(const std::vector<std::string>& headers);

    /**
     * @brief Add a header row to the table
     * @param headers Initializer list of header strings
     * @return Reference to this table for method chaining
     */
    Table& addHeader(std::initializer_list<std::string> headers);

    /**
     * @brief Add a row to the table
     * @param cells Vector of cell values
     * @return Reference to this table for method chaining
     */
    template <typename T>
    requires std::convertible_to<T, std::string>
    Table& addRow(const std::vector<T>& cells);

    /**
     * @brief Add a row to the table
     * @param cells Initializer list of cell values
     * @return Reference to this table for method chaining
     */
    template <typename T>
    requires std::convertible_to<T, std::string>
    Table& addRow(std::initializer_list<T> cells);

    /**
     * @brief Add a pre-constructed Row to the table
     * @param row Row object to add
     * @return Reference to this table for method chaining
     */
    Table& addRow(const Row& row);

    /**
     * @brief Set the theme for the table
     * @param theme Theme to apply
     * @return Reference to this table for method chaining
     */
    Table& setTheme(Theme theme);

    /**
     * @brief Set custom border style
     * @param border Border style to apply
     * @return Reference to this table for method chaining
     */
    Table& setBorder(const Border& border);

    /**
     * @brief Set alignment for a specific column
     * @param columnIndex Index of the column (0-based)
     * @param alignment Alignment to apply
     * @return Reference to this table for method chaining
     */
    Table& setColumnAlignment(size_t columnIndex, Alignment alignment);

    /**
     * @brief Set the width for a specific column
     * @param columnIndex Index of the column (0-based)
     * @param width Width in characters, or std::nullopt for auto-sizing
     * @return Reference to this table for method chaining
     */
    Table& setColumnWidth(size_t columnIndex, std::optional<size_t> width);

    /**
     * @brief Get the number of rows in the table (including header)
     * @return Number of rows
     */
    [[nodiscard]] size_t rowCount() const noexcept;

    /**
     * @brief Get the number of columns in the table
     * @return Number of columns
     */
    [[nodiscard]] size_t columnCount() const noexcept;

    /**
     * @brief Check if the table is empty (has no rows)
     * @return true if empty, false otherwise
     */
    [[nodiscard]] bool empty() const noexcept;

    /**
     * @brief Clear all rows from the table
     * @return Reference to this table for method chaining
     */
    Table& clear() noexcept;

    /**
     * @brief Get a string representation of the table
     * @return Formatted table as string
     */
    [[nodiscard]] std::string str() const;

    /**
     * @brief Output stream operator overload
     * @param os Output stream
     * @param table Table to output
     * @return Reference to the output stream
     */
    friend std::ostream& operator<<(std::ostream& os, const Table& table);

private:
    std::optional<Row> m_header;
    std::vector<Row> m_rows;
    Theme m_theme = Theme::GRID;
    Border m_border = getBorderForTheme(m_theme);
    std::vector<Alignment> m_columnAlignments;
    std::vector<std::optional<size_t>> m_columnWidths;

    /**
     * @brief Calculate the column widths based on content
     * @return Vector of column widths
     */
    [[nodiscard]] std::vector<size_t> calculateColumnWidths() const;

    /**
     * @brief Render the table to a string
     * @return Formatted table string
     */
    [[nodiscard]] std::string render() const;
};

// Template implementation
template <typename T>
requires std::convertible_to<T, std::string>
Table& Table::addRow(const std::vector<T>& cells) {
    Row row;
    for (const auto& cell : cells) {
        row.addCell(std::string(cell));
    }
    return addRow(row);
}

template <typename T>
requires std::convertible_to<T, std::string>
Table& Table::addRow(std::initializer_list<T> cells) {
    Row row;
    for (const auto& cell : cells) {
        row.addCell(std::string(cell));
    }
    return addRow(row);
}

} // namespace tabulix

#endif // TABULIX_CORE_TABLE_HPP
