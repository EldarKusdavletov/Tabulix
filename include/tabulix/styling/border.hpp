/**
 * @file border.hpp
 * @brief Definition of the Border class
 */

#ifndef TABULIX_STYLING_BORDER_HPP
#define TABULIX_STYLING_BORDER_HPP

#include <string>

namespace tabulix {

/**
 * @class Border
 * @brief Defines the border style for a table
 */
class Border {
public:
    /**
     * @brief Default constructor
     */
    Border();

    /**
     * @brief Constructor with all border characters
     * @param horizontal Horizontal line character
     * @param vertical Vertical line character
     * @param topLeft Top left corner character
     * @param topRight Top right corner character
     * @param bottomLeft Bottom left corner character
     * @param bottomRight Bottom right corner character
     * @param topIntersection Top intersection character
     * @param bottomIntersection Bottom intersection character
     * @param leftIntersection Left intersection character
     * @param rightIntersection Right intersection character
     * @param crossIntersection Cross intersection character
     */
    Border(
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
    );

    /**
     * @brief Get the horizontal line character
     * @return Horizontal line character
     */
    [[nodiscard]] const std::string& horizontal() const noexcept;

    /**
     * @brief Get the vertical line character
     * @return Vertical line character
     */
    [[nodiscard]] const std::string& vertical() const noexcept;

    /**
     * @brief Get the top left corner character
     * @return Top left corner character
     */
    [[nodiscard]] const std::string& topLeft() const noexcept;

    /**
     * @brief Get the top right corner character
     * @return Top right corner character
     */
    [[nodiscard]] const std::string& topRight() const noexcept;

    /**
     * @brief Get the bottom left corner character
     * @return Bottom left corner character
     */
    [[nodiscard]] const std::string& bottomLeft() const noexcept;

    /**
     * @brief Get the bottom right corner character
     * @return Bottom right corner character
     */
    [[nodiscard]] const std::string& bottomRight() const noexcept;

    /**
     * @brief Get the top intersection character
     * @return Top intersection character
     */
    [[nodiscard]] const std::string& topIntersection() const noexcept;

    /**
     * @brief Get the bottom intersection character
     * @return Bottom intersection character
     */
    [[nodiscard]] const std::string& bottomIntersection() const noexcept;

    /**
     * @brief Get the left intersection character
     * @return Left intersection character
     */
    [[nodiscard]] const std::string& leftIntersection() const noexcept;

    /**
     * @brief Get the right intersection character
     * @return Right intersection character
     */
    [[nodiscard]] const std::string& rightIntersection() const noexcept;

    /**
     * @brief Get the cross intersection character
     * @return Cross intersection character
     */
    [[nodiscard]] const std::string& crossIntersection() const noexcept;

    /**
     * @brief Check if borders are enabled
     * @return true if borders are enabled, false otherwise
     */
    [[nodiscard]] bool enabled() const noexcept;

    /**
     * @brief Create a border with Unicode single-line characters
     * @return Border with Unicode single-line characters
     */
    static Border unicodeSingle();

    /**
     * @brief Create a border with Unicode double-line characters
     * @return Border with Unicode double-line characters
     */
    static Border unicodeDouble();

    /**
     * @brief Create a border with ASCII characters
     * @return Border with ASCII characters
     */
    static Border ascii();

    /**
     * @brief Create a border with no visible characters
     * @return Border with empty characters
     */
    static Border none();

private:
    std::string m_horizontal;
    std::string m_vertical;
    std::string m_topLeft;
    std::string m_topRight;
    std::string m_bottomLeft;
    std::string m_bottomRight;
    std::string m_topIntersection;
    std::string m_bottomIntersection;
    std::string m_leftIntersection;
    std::string m_rightIntersection;
    std::string m_crossIntersection;
};

} // namespace tabulix

#endif // TABULIX_STYLING_BORDER_HPP
