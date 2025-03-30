#pragma once

#include "mine_sweeper_tile.hpp"

/**
 * @brief Global tile constants used for creating boards. 
 */
namespace mswptileconsts
{
inline constexpr mswp::Tile V0 = mswp::Tile(0, mswp::Tile::VISIBLE);
inline constexpr mswp::Tile V1 = mswp::Tile(1, mswp::Tile::VISIBLE);
inline constexpr mswp::Tile V2 = mswp::Tile(2, mswp::Tile::VISIBLE);
inline constexpr mswp::Tile V3 = mswp::Tile(3, mswp::Tile::VISIBLE);
inline constexpr mswp::Tile V4 = mswp::Tile(4, mswp::Tile::VISIBLE);
inline constexpr mswp::Tile V5 = mswp::Tile(5, mswp::Tile::VISIBLE);
inline constexpr mswp::Tile V6 = mswp::Tile(6, mswp::Tile::VISIBLE);
inline constexpr mswp::Tile V7 = mswp::Tile(7, mswp::Tile::VISIBLE);
inline constexpr mswp::Tile V8 = mswp::Tile(8, mswp::Tile::VISIBLE);

inline constexpr mswp::Tile H0 = mswp::Tile(0, mswp::Tile::HIDDEN);
inline constexpr mswp::Tile H1 = mswp::Tile(1, mswp::Tile::HIDDEN);
inline constexpr mswp::Tile H2 = mswp::Tile(2, mswp::Tile::HIDDEN);
inline constexpr mswp::Tile H3 = mswp::Tile(3, mswp::Tile::HIDDEN);
inline constexpr mswp::Tile H4 = mswp::Tile(4, mswp::Tile::HIDDEN);
inline constexpr mswp::Tile H5 = mswp::Tile(5, mswp::Tile::HIDDEN);
inline constexpr mswp::Tile H6 = mswp::Tile(6, mswp::Tile::HIDDEN);
inline constexpr mswp::Tile H7 = mswp::Tile(7, mswp::Tile::HIDDEN);
inline constexpr mswp::Tile H8 = mswp::Tile(8, mswp::Tile::HIDDEN);

inline constexpr mswp::Tile F0 = mswp::Tile(0, mswp::Tile::FLAGGED);
inline constexpr mswp::Tile F1 = mswp::Tile(1, mswp::Tile::FLAGGED);
inline constexpr mswp::Tile F2 = mswp::Tile(2, mswp::Tile::FLAGGED);
inline constexpr mswp::Tile F3 = mswp::Tile(3, mswp::Tile::FLAGGED);
inline constexpr mswp::Tile F4 = mswp::Tile(4, mswp::Tile::FLAGGED);
inline constexpr mswp::Tile F5 = mswp::Tile(5, mswp::Tile::FLAGGED);
inline constexpr mswp::Tile F6 = mswp::Tile(6, mswp::Tile::FLAGGED);
inline constexpr mswp::Tile F7 = mswp::Tile(7, mswp::Tile::FLAGGED);
inline constexpr mswp::Tile F8 = mswp::Tile(8, mswp::Tile::FLAGGED);

inline constexpr mswp::Tile FB = mswp::Tile(0, mswp::Tile::FLAGGED | mswp::Tile::BOMB);

inline constexpr mswp::Tile B0 = mswp::Tile(0, mswp::Tile::BOMB);
inline constexpr mswp::Tile B1 = mswp::Tile(1, mswp::Tile::BOMB);
inline constexpr mswp::Tile B2 = mswp::Tile(2, mswp::Tile::BOMB);
inline constexpr mswp::Tile B3 = mswp::Tile(3, mswp::Tile::BOMB);
inline constexpr mswp::Tile B4 = mswp::Tile(4, mswp::Tile::BOMB);
inline constexpr mswp::Tile B5 = mswp::Tile(5, mswp::Tile::BOMB);
inline constexpr mswp::Tile B6 = mswp::Tile(6, mswp::Tile::BOMB);
inline constexpr mswp::Tile B7 = mswp::Tile(7, mswp::Tile::BOMB);
inline constexpr mswp::Tile B8 = mswp::Tile(8, mswp::Tile::BOMB);
} // mswpalias end