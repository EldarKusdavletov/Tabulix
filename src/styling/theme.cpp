/**
 * @file theme.cpp
 * @brief Implementation of theme-related functions
 */

#include "tabulix/styling/theme.hpp"
#include "tabulix/styling/border.hpp"

namespace tabulix {

Border getBorderForTheme(Theme theme) {
    switch (theme) {
        case Theme::NONE:
            return Border::none();

        case Theme::SIMPLE:
            return Border::ascii();

        case Theme::GRID:
            return Border(
                "-", "|", "+", "+", "+", "+", "+", "+", "+", "+", "+"
            );

        case Theme::UNICODE_SINGLE:
            return Border::unicodeSingle();

        case Theme::UNICODE_DOUBLE:
            return Border::unicodeDouble();

        case Theme::MARKDOWN:
            return Border(
                "-", "|", "|", "|", "|", "|", "|", "|", "|", "|", "|"
            );

        case Theme::MINIMAL:
            return Border(
                "─", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "
            );

        case Theme::COMPACT:
            return Border(
                "-", "|", "+", "+", "+", "+", "+", "+", "+", "+", "+"
            );

        case Theme::DOTTED:
            return Border(
                "···", "·", "·", "·", "·", "·", "·", "·", "·", "·", "·"
            );

        case Theme::DASHED:
            return Border(
                "---", "|", "+", "+", "+", "+", "+", "+", "+", "+", "+"
            );

        case Theme::FANCY:
            return Border(
                "═", "║", "╔", "╗", "╚", "╝", "╦", "╩", "╠", "╣", "╬"
            );

        default:
            return Border::ascii();
    }
}

} // namespace tabulix
