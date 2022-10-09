# Table tennis game (TT-game)
It's a table tennis–themed twitch arcade sports video game - [Pong game](https://en.wikipedia.org/wiki/Pong) on C language for terminal Linux.

## Libraries for dynamic version
- [`ncurses`](https://en.wikipedia.org/wiki/Ncurses) - for real-time mode 
- [`time`](https://www.tutorialspoint.com/c_standard_library/time_h.htm) - for the delay between cards in microseconds
- [`stdio`](https://www.tutorialspoint.com/c_standard_library/stdio_h.htm) - for other primitive actions (e. g. printf())

## Compilation
Go to the TT-game folder and enter in the terminal:
```
$ make
```
Run dynamic version TT_game in the terminal:
```
$ ./TT_game
```
Run step by step version TT_game in the terminal:
```
$ ./TT_game_step_by_step
```
## Gameplay
### General
To move the left racket, use the keys `'A'` and `'Z'` ('a' and 'z'), for the right - `'K'` and `'M'` ('k' and 'm'). To exit the game, you need to press `'Esc'` or wait for one of the players to win.

With standard settings, the game ends when one of the players scores 15 points.

### For step by step version
To skip step press `'Space'`, to enter next move press `'Enter'`

### For dynamic version
> Since only one input stream is used, when holding the control keys of the racket or when pressing intensively, the racket can move for some time by "inertia".

### Gif from original Atari game "Pong"
![pong_gif](https://github.com/GorokhovSemyon/TT_game/blob/develop/materials/pong-video-game.gif)

