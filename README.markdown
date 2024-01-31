# Minesweeper Solver Prototype
This is a casual project that I'm currently working on to gain experience with C++. The goal of this project is to create an algorithm to solve Minesweeper on expert difficulty 45% of the time as fast as possible. Currently it can solve 42.66% of expert games with seeds 0-9999 in 55 seconds making the average game from this set solvable in 5.5 millisecs.
## Planned Fixes and Improvements in rewrite:
- I will implement realtime minesweeper play in the rewrite.
- I plan to optimize my algorithm further by using this technique [article](https://minesweepergame.com/strategy/patterns.php) reducing the amount of calls to find all solutions which is NP.
- A way to optimize this algorithm greatly would be to use memory pooling reducing the amount of heap memory that needs to be assigned. This is something I plan to do.
- I can increase the win rate by finding the reguess chance of each unknown tile when guessing and use that to decrease the amount of guesses.
- Inorder to give the user greater control over the program I will multithread my program allowing for inputs while its running.
- I plan on swapping my terminal UI with a GUI making it more user friendly.
- I will improve the readability of this code by choosing better names for variables and functions. I will also add explanations for what functions do.
## How it works
- A class called "mineMap" emulates the actual Minesweeper game
- A class called "solver" receives the game state through a string.
- The solver class will then search for any tiles that have the same number of adjacent bombs as adjacent unknown tiles. If this is true all adjacent unknown tiles will be flagged.
- The solver class will then search for any tiles that have the same number of adjacent bombs as adjacent flagged tiles. If this is true all adjacent unknown tiles will be clicked.
- If neither of these are true the solver class will group the tiles together into distinct groups and send these to the "probabilityFinder" class and check for every single possible arrangement of bombs within these groups.
- If there is a possibility that the bombs in these groups can surpass the amount of bombs left the algorithm will combine these solutions and exclude combinations that surpass the amount of bombs left.
- Using these solutions the algorithm then calculates the probability of each tile being a bomb. Any tiles that have a 100% chance of being a bomb are flagged and any that have a 0% chance of being a bomb are clicked.
- If there are no obvious tile choices the algorithm will then find the bomb with the lowest probability of being a bomb and click it. If theres a tie between probabilities the algorithm will use whether or not the tile is a corner/edge as a tie breaker.
- This cycle will be repeated every iteration.
## How to compile and run
1. Navigate to the root directory of the repository
2. Type "make" into the console
    - If you get an error from this make sure you are using a linux based terminal and that you have "make" installed.
3. Type ./build/runner into the console
    - If you received an error make sure your current directory is either the root of the repository or is the build directory.
4. The program should now be running.
## How to use
When booting up the program in terminal you will be greeted by 3 options:
```
Type "w" to watch minesweeper algorithm
Type "t" to test minesweeper algorithm
Type "q" to quit
```
- Typing w will allow you to watch the minesweeper algorithm solve a map with the selected difficulty and seed.
- Typing t will run the minesweeper algorithm on seeds 0-(run_amount-1) on the selected difficulty and tell you the time taken and the win rate.
- Typing q will exit the program.
## Settings
Settings can be set in the settings file found in the doc directory.
- run_amount specifies how many times the algorithm is run when testing preformance and win rate. 
- difficulty has three different settings:
    - Beginner: 9x9 board, 10 bombs
    - Intermediate: 16x16 board, 40 bombs
    - Expert  30x16 board, 99 bombs
- difficulty is used when testing and when running a seed to watch.
- seed is a setting used for watching the algorithm, it is not used for testing. If you set it to "r" it will set the seed equal to time, if its set to a number thats the seed it will use.
- wait_time is the sleep time in nanoseconds between iterations which is used when watching the algorithm not for testing.

## Terminal Grabs:
Info about coordinates and what "c x y" means:
- c x y: This refers to the coordinates of where the last click was.
- x = 0 refers the left of the screen, y = 0 refers to the top of the screen

ASCII key for how minesweeper game is displayed:
- '@': Flagged
- '\#': Unknown
- ' ': No adjacent bombs
- 'n' where n is an integer between 1 and 8: the adjacent bomb count
- 'X' A detonated bomb

Example of solved game:
```
c 29 15
iteration: 292
seed 1706645208
guesses: 0
Flags: 0
    1 @ @ 2 1 1 1 1   1 @ 2 1 1   1 1 2 1 2 2 @ @ 1 1 1 1   
    1 2 3 @ 1 1 @ 2 1 1 1 2 @ 3 2 2 @ 3 @ 3 @ 4 3 2 1 @ 3 2 
        2 2 2 2 3 @ 1     1 2 @ @ 2 1 3 @ 3 1 2 @ 2 2 2 @ @ 
1 1 1 1 2 @ 1 1 @ 2 1     1 3 4 3 1   1 1 2 2 3 3 @ 1 1 2 2 
2 @ 1 1 @ 2 1 1 2 2 2 1 1 1 @ @ 2 1 1 1 1 1 @ @ 4 2 2 1 1   
@ 2 2 2 3 3 2 1 1 @ 2 @ 1 1 2 3 @ 1 1 @ 2 2 4 @ @ 1 1 @ 1   
1 1 2 @ 3 @ @ 1 1 1 2 2 2 1 1 2 2 1 2 2 3 @ 2 2 2 1 2 2 3 1 
    2 @ 4 3 3 2 1 2 1 2 @ 1 1 @ 3 3 4 @ 4 2 2       1 @ 2 @ 
1 2 3 2 3 @ 2 1 @ 3 @ 3 1 1 1 2 @ @ @ @ 3 @ 1 1 2 2 2 1 3 2 
1 @ @ 2 2 @ 2 1 1 3 @ 3 1   1 3 5 5 4 2 2 1 1 1 @ @ 2 1 2 @ 
1 3 @ 2 1 1 1   1 2 3 @ 1 1 2 @ @ @ 2 1       1 2 2 2 @ 3 2 
  1 1 1     1 2 3 @ 2 1 1 2 @ 5 4 3 @ 1     1 1 1 1 2 4 @ 2 
  1 1 1   1 2 @ @ 3 2 1 1 2 @ @ 1 1 1 1 1 1 2 @ 1 1 @ 3 @ 2 
  1 @ 1   1 @ 4 @ 3 2 @ 2 2 3 3 2 1   1 2 @ 2 2 3 4 4 4 2 1 
1 2 3 2 1 1 2 3 3 @ 2 1 2 @ 1 1 @ 1   1 @ 3 3 3 @ @ @ @ 2 1 
1 @ 2 @ 1   1 @ 2 1 1   1 1 1 1 1 1   1 1 2 @ @ 4 @ @ 4 @ 1 
Solved!
```
Example of lost game:
```
iteration: 194
seed 1706646306
guesses: 3
Flags: 2
    1 @ 1         1 1 1 1 1 2 1 1   1 @ 2 1 1 2 @ 2 1 @ 1   
    1 2 2 1       2 @ 2 1 @ 3 @ 4 2 2 1 3 @ 2 2 @ 2 1 1 1   
1 1   1 @ 2 1     2 @ 3 2 1 3 @ @ @ 2   2 @ 2 2 2 2         
@ 3 2 2 3 @ 1     1 2 @ 3 2 2 3 @ @ 2   1 2 2 2 @ 1   1 1 1 
@ @ 2 @ 2 1 1     1 2 3 @ @ 2 3 4 3 1     1 @ 2 1 1 1 2 @ 1 
@ 3 3 2 2     1 1 2 @ 2 2 3 3 @ @ 1 1 1 1 1 1 1     1 @ 4 3 
2 2 3 @ 2     1 @ 2 1 1   1 @ 3 3 3 3 @ 2 1         1 2 @ @ 
1 @ 4 @ 2     1 1 1       1 1 1 1 @ @ 3 @ 2 2 2 2 2 1 2 3 X 
3 4 @ 3 3 2 1         1 1 1   1 2 3 2 2 2 @ 2 @ @ 3 @ 2 3 # 
@ @ 3 2 @ @ 2 1 2 2 2 2 @ 1 1 3 @ 3 1 1 2 2 3 3 @ 3 1 2 @ @ 
3 @ 3 2 3 @ 3 2 @ @ 2 @ 3 2 1 @ @ 4 @ 1 2 @ 4 3 2 1 1 2 3 2 
2 4 @ 2 1 2 @ 2 2 2 2 2 @ 1 1 3 @ 3 2 2 4 @ @ @ 3 2 4 @ 2   
# # @ 4 1 2 1 1       1 1 1   1 1 1 1 @ 3 @ @ @ 4 @ @ @ 3 1 
1 3 @ 3 @ 2 1 1                 1 1 2 1 2 2 3 3 4 @ 6 4 3 @ 
1 2 1 2 1 3 @ 3 1 1 2 2 1       1 @ 1         1 @ 3 @ @ 2 1 
@ 1       2 @ @ 1 1 @ @ 1       1 1 1         1 1 2 2 2 1   
Explode at 29 7
```
Example of test results on expert set to 10000 runs:
```
######################################################
Total Games: 10000

Wins:        4266
Losses:      5734

Win Rate:    42.66%

######################################################
Time Taken:         46 secs
Time Taken per run: 4.6 millisecs per run

######################################################
```
## License
Minesweeper Solver is liscenced under the MIT License, see [LICENCE.txt](https://github.com/garthable/Mine-Sweeper-Solver/blob/main/LICENSE.txt) for more information
