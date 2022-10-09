all: pong pong_bonus

rebuild: clean all

pong: src/pong.c
	gcc -o TT_game_step_by_step src/pong.c

pong_bonus: src/pong_bonus.c
	gcc -o TT_game src/pong_bonus.c -lncurses

clean:
	rm -rf TT_game*
