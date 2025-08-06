/**
 * @file cell.cpp
 * @brief Implementation of the Cell class
 */

#include "tabulix/core/cell.hpp"
#include <algorithm>

namespace tabulix {

Cell::Cell(std::string value) : m_value(std::move(value)) {
}

const std::string& Cell::value() const noexcept {
    return m_value;
}

Cell& Cell::setValue(std::string value) {
    m_value = std::move(value);
    return *this;
}

std::optional<Alignment> Cell::alignment() const noexcept {
    return m_alignment;
}

Cell& Cell::setAlignment(Alignment alignment) {
    m_alignment = alignment;
    return *this;
}

Cell& Cell::resetAlignment() noexcept {
    m_alignment.reset();
    return *this;
}

size_t Cell::width() const {
    // Count visible width (handle multiline content)
    if (m_value.empty()) {
        return 0;
    }

    size_t maxWidth = 0;
    size_t currentWidth = 0;

    for (char c : m_value) {
        if (c == '\n') {
            maxWidth = std::max(maxWidth, currentWidth);
            currentWidth = 0;
        } else {
            currentWidth++;
        }
    }

    return std::max(maxWidth, currentWidth);
}

} // namespace tabulix
