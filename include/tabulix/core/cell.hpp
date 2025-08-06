/**
 * @file cell.hpp
 * @brief Definition of the Cell class
 */

#ifndef TABULIX_CORE_CELL_HPP
#define TABULIX_CORE_CELL_HPP

#include <string>
#include <optional>
#include "../styling/alignment.hpp"

namespace tabulix {

/**
 * @class Cell
 * @brief Represents a cell in a table
 */
class Cell {
public:
    /**
     * @brief Default constructor
     */
    Cell() = default;

    /**
     * @brief Constructor with value
     * @param value Cell content
     */
    explicit Cell(std::string value);

    /**
     * @brief Get the cell content
     * @return Cell content
     */
    [[nodiscard]] const std::string& value() const noexcept;

    /**
     * @brief Set the cell content
     * @param value New cell content
     * @return Reference to this cell for method chaining
     */
    Cell& setValue(std::string value);

    /**
     * @brief Get the cell alignment
     * @return Cell alignment or std::nullopt if not set
     */
    [[nodiscard]] std::optional<Alignment> alignment() const noexcept;

    /**
     * @brief Set the cell alignment
     * @param alignment New cell alignment
     * @return Reference to this cell for method chaining
     */
    Cell& setAlignment(Alignment alignment);

    /**
     * @brief Reset the cell alignment to default
     * @return Reference to this cell for method chaining
     */
    Cell& resetAlignment() noexcept;

    /**
     * @brief Get the cell width
     * @return Width of the cell content in characters
     */
    [[nodiscard]] size_t width() const;

private:
    std::string m_value;
    std::optional<Alignment> m_alignment;
};

} // namespace tabulix

#endif // TABULIX_CORE_CELL_HPP
