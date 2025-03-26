#pragma once

#include "mine_sweeper_solver.hpp"

/**
 * @brief Global tile constants used for creating solver boards. 
 */
namespace slvrtileconsts
{
inline constexpr slvr::Tile HIDD = slvr::Tile(NAN, -1, -1);

inline constexpr slvr::Tile BOMB = slvr::Tile(1, -1, -1);

inline constexpr slvr::Tile B0H0 = slvr::Tile(0, 0, 0);

inline constexpr slvr::Tile B1H0 = slvr::Tile(0, 1, 0);
inline constexpr slvr::Tile B1H1 = slvr::Tile(0, 1, 1);
inline constexpr slvr::Tile B1H2 = slvr::Tile(0, 1, 2);
inline constexpr slvr::Tile B1H3 = slvr::Tile(0, 1, 3);
inline constexpr slvr::Tile B1H4 = slvr::Tile(0, 1, 4);
inline constexpr slvr::Tile B1H5 = slvr::Tile(0, 1, 5);
inline constexpr slvr::Tile B1H6 = slvr::Tile(0, 1, 6);
inline constexpr slvr::Tile B1H7 = slvr::Tile(0, 1, 7);
inline constexpr slvr::Tile B1H8 = slvr::Tile(0, 1, 8);

inline constexpr slvr::Tile B2H0 = slvr::Tile(0, 2, 0);
inline constexpr slvr::Tile B2H1 = slvr::Tile(0, 2, 1);
inline constexpr slvr::Tile B2H2 = slvr::Tile(0, 2, 2);
inline constexpr slvr::Tile B2H3 = slvr::Tile(0, 2, 3);
inline constexpr slvr::Tile B2H4 = slvr::Tile(0, 2, 4);
inline constexpr slvr::Tile B2H5 = slvr::Tile(0, 2, 5);
inline constexpr slvr::Tile B2H6 = slvr::Tile(0, 2, 6);
inline constexpr slvr::Tile B2H7 = slvr::Tile(0, 2, 7);
inline constexpr slvr::Tile B2H8 = slvr::Tile(0, 2, 8);

inline constexpr slvr::Tile B3H0 = slvr::Tile(0, 3, 0);
inline constexpr slvr::Tile B3H1 = slvr::Tile(0, 3, 1);
inline constexpr slvr::Tile B3H2 = slvr::Tile(0, 3, 2);
inline constexpr slvr::Tile B3H3 = slvr::Tile(0, 3, 3);
inline constexpr slvr::Tile B3H4 = slvr::Tile(0, 3, 4);
inline constexpr slvr::Tile B3H5 = slvr::Tile(0, 3, 5);
inline constexpr slvr::Tile B3H6 = slvr::Tile(0, 3, 6);
inline constexpr slvr::Tile B3H7 = slvr::Tile(0, 3, 7);
inline constexpr slvr::Tile B3H8 = slvr::Tile(0, 3, 8);

inline constexpr slvr::Tile B4H0 = slvr::Tile(0, 4, 0);
inline constexpr slvr::Tile B4H1 = slvr::Tile(0, 4, 1);
inline constexpr slvr::Tile B4H2 = slvr::Tile(0, 4, 2);
inline constexpr slvr::Tile B4H3 = slvr::Tile(0, 4, 3);
inline constexpr slvr::Tile B4H4 = slvr::Tile(0, 4, 4);
inline constexpr slvr::Tile B4H5 = slvr::Tile(0, 4, 5);
inline constexpr slvr::Tile B4H6 = slvr::Tile(0, 4, 6);
inline constexpr slvr::Tile B4H7 = slvr::Tile(0, 4, 7);
inline constexpr slvr::Tile B4H8 = slvr::Tile(0, 4, 8);

inline constexpr slvr::Tile B5H0 = slvr::Tile(0, 5, 0);
inline constexpr slvr::Tile B5H1 = slvr::Tile(0, 5, 1);
inline constexpr slvr::Tile B5H2 = slvr::Tile(0, 5, 2);
inline constexpr slvr::Tile B5H3 = slvr::Tile(0, 5, 3);
inline constexpr slvr::Tile B5H4 = slvr::Tile(0, 5, 4);
inline constexpr slvr::Tile B5H5 = slvr::Tile(0, 5, 5);
inline constexpr slvr::Tile B5H6 = slvr::Tile(0, 5, 6);
inline constexpr slvr::Tile B5H7 = slvr::Tile(0, 5, 7);
inline constexpr slvr::Tile B5H8 = slvr::Tile(0, 5, 8);

inline constexpr slvr::Tile B6H0 = slvr::Tile(0, 6, 0);
inline constexpr slvr::Tile B6H1 = slvr::Tile(0, 6, 1);
inline constexpr slvr::Tile B6H2 = slvr::Tile(0, 6, 2);
inline constexpr slvr::Tile B6H3 = slvr::Tile(0, 6, 3);
inline constexpr slvr::Tile B6H4 = slvr::Tile(0, 6, 4);
inline constexpr slvr::Tile B6H5 = slvr::Tile(0, 6, 5);
inline constexpr slvr::Tile B6H6 = slvr::Tile(0, 6, 6);
inline constexpr slvr::Tile B6H7 = slvr::Tile(0, 6, 7);
inline constexpr slvr::Tile B6H8 = slvr::Tile(0, 6, 8);

inline constexpr slvr::Tile B7H0 = slvr::Tile(0, 7, 0);
inline constexpr slvr::Tile B7H1 = slvr::Tile(0, 7, 1);
inline constexpr slvr::Tile B7H2 = slvr::Tile(0, 7, 2);
inline constexpr slvr::Tile B7H3 = slvr::Tile(0, 7, 3);
inline constexpr slvr::Tile B7H4 = slvr::Tile(0, 7, 4);
inline constexpr slvr::Tile B7H5 = slvr::Tile(0, 7, 5);
inline constexpr slvr::Tile B7H6 = slvr::Tile(0, 7, 6);
inline constexpr slvr::Tile B7H7 = slvr::Tile(0, 7, 7);
inline constexpr slvr::Tile B7H8 = slvr::Tile(0, 7, 8);

inline constexpr slvr::Tile B8H0 = slvr::Tile(0, 8, 0);
inline constexpr slvr::Tile B8H1 = slvr::Tile(0, 8, 1);
inline constexpr slvr::Tile B8H2 = slvr::Tile(0, 8, 2);
inline constexpr slvr::Tile B8H3 = slvr::Tile(0, 8, 3);
inline constexpr slvr::Tile B8H4 = slvr::Tile(0, 8, 4);
inline constexpr slvr::Tile B8H5 = slvr::Tile(0, 8, 5);
inline constexpr slvr::Tile B8H6 = slvr::Tile(0, 8, 6);
inline constexpr slvr::Tile B8H7 = slvr::Tile(0, 8, 7);
inline constexpr slvr::Tile B8H8 = slvr::Tile(0, 8, 8);

} // slvralias end