/**
 * @file alignment.hpp
 * @brief Definition of the Alignment enum
 */

#ifndef TABULIX_STYLING_ALIGNMENT_HPP
#define TABULIX_STYLING_ALIGNMENT_HPP

namespace tabulix {

/**
 * @enum Alignment
 * @brief Text alignment options for cells
 */
enum class Alignment {
    LEFT,   ///< Left alignment
    CENTER, ///< Center alignment
    RIGHT,   ///< Right alignment
};

} // namespace tabulix

#endif // TABULIX_STYLING_ALIGNMENT_HPP
