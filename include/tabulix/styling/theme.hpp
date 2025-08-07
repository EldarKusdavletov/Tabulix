/**
 * @file theme.hpp
 * @brief Definition of the Theme enum and related functions
 */

#ifndef TABULIX_STYLING_THEME_HPP
#define TABULIX_STYLING_THEME_HPP

#include "border.hpp"

namespace tabulix {

/**
 * @enum Theme
 * @brief Predefined table themes
 */
enum class Theme {
    NONE,           ///< No borders or separators
    GRID,           ///< Full ASCII grid
    UNICODE_SINGLE, ///< Unicode single-line borders
    UNICODE_DOUBLE, ///< Unicode double-line borders
    MARKDOWN,       ///< Markdown-style table
    MINIMAL,        ///< Minimal borders
    DOTTED,         ///< Dotted borders
    FANCY,           ///< Fancy decorative borders
};

/**
 * @brief Get a border style for a theme
 * @param theme Theme to convert
 * @return Border style corresponding to the theme
 */
Border getBorderForTheme(Theme theme);

} // namespace tabulix

#endif // TABULIX_STYLING_THEME_HPP
