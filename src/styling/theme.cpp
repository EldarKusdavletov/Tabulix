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

        case Theme::GRID:
            return Border::ascii();

        case Theme::UNICODE_SINGLE:
            return Border::unicodeSingle();

        case Theme::UNICODE_DOUBLE:
            return Border::unicodeDouble();

        case Theme::MARKDOWN:
            return {"-", "|", "|", "|", "|", "|", "|", "|", "|", "|", "|"};

        case Theme::MINIMAL:
            return {"-", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "};

        case Theme::DOTTED:
            return {"·", "·", "·", "·", "·", "·", "·", "·", "·", "·", "·"};

        case Theme::FANCY:
            return {"═", "║", "╔", "╗", "╚", "╝", "╦", "╩", "╠", "╣", "╬"};

        default:
            return Border::ascii();
    }
}

} // namespace tabulix
