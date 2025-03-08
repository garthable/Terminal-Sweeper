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

/**
 * @brief Width of expert game of minesweeper
 * 
 */
#define MSWP_EXPERT_WIDTH 30
/**
 * @brief Height of expert game of minesweeper
 * 
 */
#define MSWP_EXPERT_HEIGHT 16
/**
 * @brief Bomb count of expert game of minesweeper
 * 
 */
#define MSWP_EXPERT_BOMB_COUNT 99

/**
 * @brief Width of intermediate game of minesweeper
 * 
 */
#define MSWP_INTERMEDIATE_WIDTH 16
/**
 * @brief Height of intermediate game of minesweeper
 * 
 */
#define MSWP_INTERMEDIATE_HEIGHT 16
/**
 * @brief Bomb count of intermediate game of minesweeper
 * 
 */
#define MSWP_INTERMEDIATE_BOMB_COUNT 40

/**
 * @brief Width of beginner game of minesweeper
 * 
 */
#define MSWP_BEGINNER_WIDTH 9
/**
 * @brief Height of beginner game of minesweeper
 * 
 */
#define MSWP_BEGINNER_HEIGHT 9
/**
 * @brief Bomb count of beginner game of minesweeper
 * 
 */
#define MSWP_BEGINNER_BOMB_COUNT 10