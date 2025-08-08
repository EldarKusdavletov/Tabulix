/**
 * @file border.cpp
 * @brief Implementation of the Border class
 */

#include "tabulix/styling/border.hpp"

namespace tabulix {

Border::Border()
    : m_horizontal("-")
    , m_vertical("|")
    , m_topLeft("+")
    , m_topRight("+")
    , m_bottomLeft("+")
    , m_bottomRight("+")
    , m_topIntersection("+")
    , m_bottomIntersection("+")
    , m_leftIntersection("+")
    , m_rightIntersection("+")
    , m_crossIntersection("+") {
}

Border::Border(
    std::string horizontal,
    std::string vertical,
    std::string topLeft,
    std::string topRight,
    std::string bottomLeft,
    std::string bottomRight,
    std::string topIntersection,
    std::string bottomIntersection,
    std::string leftIntersection,
    std::string rightIntersection,
    std::string crossIntersection
)
    : m_horizontal(std::move(horizontal))
    , m_vertical(std::move(vertical))
    , m_topLeft(std::move(topLeft))
    , m_topRight(std::move(topRight))
    , m_bottomLeft(std::move(bottomLeft))
    , m_bottomRight(std::move(bottomRight))
    , m_topIntersection(std::move(topIntersection))
    , m_bottomIntersection(std::move(bottomIntersection))
    , m_leftIntersection(std::move(leftIntersection))
    , m_rightIntersection(std::move(rightIntersection))
    , m_crossIntersection(std::move(crossIntersection)) {
}

const std::string& Border::horizontal() const noexcept {
    return m_horizontal;
}

const std::string& Border::vertical() const noexcept {
    return m_vertical;
}

const std::string& Border::topLeft() const noexcept {
    return m_topLeft;
}

const std::string& Border::topRight() const noexcept {
    return m_topRight;
}

const std::string& Border::bottomLeft() const noexcept {
    return m_bottomLeft;
}

const std::string& Border::bottomRight() const noexcept {
    return m_bottomRight;
}

const std::string& Border::topIntersection() const noexcept {
    return m_topIntersection;
}

const std::string& Border::bottomIntersection() const noexcept {
    return m_bottomIntersection;
}

const std::string& Border::leftIntersection() const noexcept {
    return m_leftIntersection;
}

const std::string& Border::rightIntersection() const noexcept {
    return m_rightIntersection;
}

const std::string& Border::crossIntersection() const noexcept {
    return m_crossIntersection;
}

bool Border::enabled() const noexcept {
    // Border is disabled if all characters are empty
    return !m_horizontal.empty() || !m_vertical.empty();
}

Border Border::none() {
    return {"", "", "", "", "", "", "", "", "", "", ""};
}

Border Border::ascii() {
    return {"-", "|", "+", "+", "+", "+", "+", "+", "+", "+", "+"};
}

Border Border::unicodeSingle() {
    return {"─", "│", "┌", "┐", "└", "┘", "┬", "┴", "├", "┤", "┼"};
}

Border Border::unicodeDouble() {
    return {"═", "║", "╔", "╗", "╚", "╝", "╦", "╩", "╠", "╣", "╬"};
}

} // namespace tabulix
