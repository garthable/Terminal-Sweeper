# Mine Sweeper Solver Prototype
This is currently a project that im working on for fun and to gain experience with C++. The goal of this project is to create an algorithm that can solve mine sweeper on expert difficulty 45% of the time as fast as possible. Currently it can solve 42.66% of expert games with seeds 0-9999 in 55 seconds meaning it can solve the average game from this set in 5.5 milliseconds.
## Planned Fixes and Improvements in rewrite:
- I will reimplement being able to actually play the game in the rewrite.
- In my rewrite I have already improved this algorithm by implementing a minesweeper strategy shown in this [article](https://minesweepergame.com/strategy/patterns.php) which results in less calls to an expensive function.
- Part of the reason for the poor solve time is that I overassign heap memory in frequently called functions. In my rewrite im pooling all heap memory used frequently to improve runtime.
- The reason why im not hitting the 45% win rate at the moment is because when my algorithm guesses it is only takes bomb probability and whether or not it borders a corner or edge into account. In my rewrite I plan on implementing an algorithm that will factor in both bomb probability and reguess probability. This will allow for a better guessing process and will hopefully increase the winrate. If I find that Im not able to discover the reguess probability I will likely improve on my prior design.
- Currently this program is only single threaded, in my next implementation I plan on having threads that handle user inputs to give the user control over the program while it runs.
- I plan on swapping my terminal UI with a GUI. Currently im planning on using the ImGui for the library.
- The readability in this is rather poor so in my rewrite ive taken time to make sure variables and functions are correctly named and to describe functions and classes bettter in the header files.
## How to compile and run
1. Navigate to the root of the repository
2. Type "make" into the console
3. Type ./build/runner into the console
4. The program should now be running, if you received an error make sure your current directory is either the root of the repository or is the build directory.
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
ASCII key for how minesweeper game is displayed:
- '@': Flagged
- '\#': Unknown
- ' ': No adjacent bombs
- 'n' where n is an integer between 1 and 8: the adjacent bomb count
- 'X' A detonated bomb

## Terminal Grabs:
Relevant info about these grabs:
c x y: This refers to the coordinates of where the last click was.
XY Coordinates:
X = 0 refers the left of the screen, Y = 0 refers to the top of the screen

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
Mine Sweeper Solver is liscenced under the MIT License, see [LICENCE.txt](https://github.com/garthable/Mine-Sweeper-Solver/blob/main/LICENSE.txt) for more information
