/**
 * @file tabulix.hpp
 * @brief Main header file for the Tabulix library
 * @author Eldar Kusdavletov
 * @date 2025
 *
 * Tabulix is a high-performance, C++26-compatible library designed to make
 * working with tables effortless and expressive.
 */

#ifndef TABULIX_TABULIX_HPP
#define TABULIX_TABULIX_HPP

#include "core/table.hpp"
#include "core/cell.hpp"
#include "core/row.hpp"
#include "styling/theme.hpp"
#include "styling/border.hpp"
#include "styling/alignment.hpp"
#include "export/exporter.hpp"

/**
 * @namespace tabulix
 * @brief Main namespace for the Tabulix library
 */
namespace tabulix {

/**
 * @brief Library version information
 */
struct Version {
    static constexpr int major = 0;
    static constexpr int minor = 1;
    static constexpr int patch = 0;
    static constexpr const char* string = "0.1.0";
};

} // namespace tabulix

#endif // TABULIX_TABULIX_HPP
