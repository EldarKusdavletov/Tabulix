/**
 * @file row.hpp
 * @brief Definition of the Row class
 */

#ifndef TABULIX_CORE_ROW_HPP
#define TABULIX_CORE_ROW_HPP

#include <vector>
#include <string>
#include "cell.hpp"

namespace tabulix {

/**
 * @class Row
 * @brief Represents a row in a table
 */
class Row {
public:
    /**
     * @brief Default constructor
     */
    Row() = default;

    /**
     * @brief Constructor with cells
     * @param cells Vector of cell values
     */
    explicit Row(const std::vector<std::string>& cells);

    /**
     * @brief Constructor with cells
     * @param cells Initializer list of cell values
     */
    Row(std::initializer_list<std::string> cells);

    /**
     * @brief Add a cell to the row
     * @param value Cell value
     * @return Reference to this row for method chaining
     */
    Row& addCell(const std::string& value);

    /**
     * @brief Add a cell to the row
     * @param cell Cell object
     * @return Reference to this row for method chaining
     */
    Row& addCell(const Cell& cell);

    /**
     * @brief Get the number of cells in the row
     * @return Number of cells
     */
    [[nodiscard]] size_t size() const noexcept;

    /**
     * @brief Get a cell by index
     * @param index Cell index (0-based)
     * @return Reference to the cell
     * @throws std::out_of_range if index is out of bounds
     */
    [[nodiscard]] const Cell& at(size_t index) const;

    /**
     * @brief Get a cell by index
     * @param index Cell index (0-based)
     * @return Reference to the cell
     * @throws std::out_of_range if index is out of bounds
     */
    Cell& at(size_t index);

    /**
     * @brief Array subscript operator
     * @param index Cell index (0-based)
     * @return Reference to the cell
     * @throws std::out_of_range if index is out of bounds
     */
    [[nodiscard]] const Cell& operator[](size_t index) const;

    /**
     * @brief Array subscript operator
     * @param index Cell index (0-based)
     * @return Reference to the cell
     * @throws std::out_of_range if index is out of bounds
     */
    Cell& operator[](size_t index);

    /**
     * @brief Get all cells in the row
     * @return Vector of cells
     */
    [[nodiscard]] const std::vector<Cell>& cells() const noexcept;

private:
    std::vector<Cell> m_cells;
};

} // namespace tabulix

#endif // TABULIX_CORE_ROW_HPP
