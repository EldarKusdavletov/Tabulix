/**
 * @file row.cpp
 * @brief Implementation of the Row class
 */

#include "tabulix/core/row.hpp"
#include <stdexcept>

namespace tabulix {

Row::Row(const std::vector<std::string>& cells) {
    for (const auto& cell : cells) {
        addCell(cell);
    }
}

Row::Row(std::initializer_list<std::string> cells) {
    for (const auto& cell : cells) {
        addCell(cell);
    }
}

Row& Row::addCell(const std::string& value) {
    m_cells.emplace_back(value);
    return *this;
}

Row& Row::addCell(const Cell& cell) {
    m_cells.push_back(cell);
    return *this;
}

size_t Row::size() const noexcept {
    return m_cells.size();
}

const Cell& Row::at(size_t index) const {
    return m_cells.at(index);
}

Cell& Row::at(size_t index) {
    return m_cells.at(index);
}

const Cell& Row::operator[](size_t index) const {
    return at(index);
}

Cell& Row::operator[](size_t index) {
    return at(index);
}

const std::vector<Cell>& Row::cells() const noexcept {
    return m_cells;
}

} // namespace tabulix
