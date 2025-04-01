import MineSweeper as ms
import time
import ctypes

def main():
    board = ms.MineSweeper(30, 16, 99)
    solver = ms.MineSweeperSolver(board)
    clicks = ms.ActionArray()
    flags = ms.ActionArray()

    while True:
        solver.update(board.tile_string())
        ms.recommended_actions(solver, clicks, flags)
        if (clicks.size() == 0 and flags.size() == 0) or board.game_state() == ms.GameState.WON or board.game_state() == ms.GameState.LOST:
            break
        ms.use_action_arrays(clicks, flags, board)

        print(board)

    

if __name__ == "__main__":
    main()