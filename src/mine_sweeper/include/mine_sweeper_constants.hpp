#pragma once

/**
 * @brief Max width of the minesweeper grid
 */
#define MSWP_MAX_WIDTH 30
/**
 * @brief Max height of the minesweeper grid
 */
#define MSWP_MAX_HEIGHT 16
/**
 * @brief Max tiles of the minesweeper grid
 */
#define MSWP_MAX_TILES MSWP_MAX_WIDTH*MSWP_MAX_HEIGHT

#define MSWP_EXPERT_WIDTH 30
#define MSWP_EXPERT_HEIGHT 16
#define MSWP_EXPERT_BOMB_COUNT 99

#define MSWP_INTERMEDIATE_WIDTH 16
#define MSWP_INTERMEDIATE_HEIGHT 16
#define MSWP_INTERMEDIATE_BOMB_COUNT 40

#define MSWP_BEGINNER_WIDTH 9
#define MSWP_BEGINNER_HEIGHT 9
#define MSWP_BEGINNER_BOMB_COUNT 10