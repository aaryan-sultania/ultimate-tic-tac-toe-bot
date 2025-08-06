# ultimate-tic-tac-toe-bot
A bot to play Ultimate Tic Tac Toe using the Monte Carlo Tree Search Algorithm.
## Compiling
On Linux, run ```g++ main.cpp mcts.cpp game.cpp -o main``` to compile the program and ```./main``` to run it.
## Usage
```Usage: [number of sumulations per move] [-S | -vsX |  -vsO]```
Use ```-S``` to have the bot play itself.
Use ```-vsX``` to have the bot play against the user with the first move.
Use ```-vsO``` to have the bot play against the user with the second move.
