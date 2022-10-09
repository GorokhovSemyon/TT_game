#include <stdio.h>
#include <ncurses.h>
#include <time.h>


#define LEFT_PLAYER_ID 'L'
#define RIGHT_PLAYER_ID 'R'
#define UNKNOWN_PLAYER_ID 'U'

#define SYMBOL_BORDER '='
#define SYMBOL_MIDDLE '|'
#define SYMBOL_LEFT_PAD '|'
#define SYMBOL_RIGHT_PAD '|'
#define SYMBOL_BALL '@'
#define SYMBOL_EMPTY_FIELD ' '

#define FIELD_WIDTH 80
#define FIELD_HIDTH 25
#define FIELD_MIDDLE 40

#define PAD_SIZE 3
#define LEFT_PAD_X 0
#define RIGHT_PAD_X 79
#define PAD_Y 12

#define WINNER_POINT 15
#define START_POINT 0

#define KEY_LEFT_UP 'a'
#define KEY_LEFT_UP_UPPER 'A'
#define KEY_LEFT_DOWN 'z'
#define KEY_LEFT_DOWN_UPPER 'Z'
#define KEY_RIGHT_UP 'k'
#define KEY_RIGHT_UP_UPPER 'K'
#define KEY_RIGHT_DOWN 'm'
#define KEY_RIGHT_DOWN_UPPER 'M'
#define KEY_SKIP_STEP ' '
#define KEY_END_GAME 27

#define BALL_START_X 10
#define BALL_START_Y 55
#define BALL_START_DELTA 1

#define POINT_HORIZONTAL_POSITION 37
#define POINT_VERTICAL_POSITION 2
#define POINT_STRING_WIDTH 7

int isBorderY(int y);
int isOutOfFiled(int x);
int isBall(int x, int y, int ball_x, int ball_y);
int isLeftPad(int x, int y, int left_pad_y);
int isRightPad(int x, int y, int right_pad_y);
int isAnyPad(int x, int y, int left_pad_y, int right_pad_y);
char getMatchWinner(int ball_x);
char getGameWinner(int left_player_point, int right_player_point);
int isValidKey(char c);
void drawBorderWithPoints(int left_player_point, int right_player_point);
void drawFirstPlayerCongrats();
void drawSecondPlayerCongrats();
void drawGreeting();

int main() {
    int left_pad_y = PAD_Y;
    int right_pad_y = PAD_Y;

    int ball_x = BALL_START_X;
    int ball_y = BALL_START_Y;

    int ball_dx = BALL_START_DELTA;
    int ball_dy = BALL_START_DELTA;

    int left_player_point = START_POINT;
    int right_player_point = START_POINT;
    char key = KEY_SKIP_STEP;

    drawGreeting();

    initscr();
    nodelay(stdscr, TRUE);
    noecho();

    do {
        ball_x += ball_dx;
        ball_y += ball_dy;

        switch (key) {
            case KEY_LEFT_UP:
            case KEY_LEFT_UP_UPPER:
                if (left_pad_y != 1) --left_pad_y;
                break;
            case KEY_LEFT_DOWN:
            case KEY_LEFT_DOWN_UPPER:
                if (left_pad_y != FIELD_HIDTH - PAD_SIZE - 1) ++left_pad_y;
                break;
            case KEY_RIGHT_UP:
            case KEY_RIGHT_UP_UPPER:
                if (right_pad_y != 1) --right_pad_y;
                break;
            case KEY_RIGHT_DOWN:
            case KEY_RIGHT_DOWN_UPPER:
                if (right_pad_y != FIELD_HIDTH - PAD_SIZE - 1) ++right_pad_y;
                break;
            case KEY_SKIP_STEP:
            default:
                break;
        }

        if (isBorderY(ball_x)) {
            ball_dx = 0 - ball_dx;
            ball_x += ball_dx;
        }

        if (isAnyPad(ball_y, ball_x, left_pad_y, right_pad_y)) {
            ball_dy = 0 - ball_dy;
            ball_y += ball_dy;
        }

        if (isOutOfFiled(ball_y)) {
            getMatchWinner(ball_y) == LEFT_PLAYER_ID ? right_player_point++ : left_player_point++;
            ball_x = BALL_START_X;
            ball_y = BALL_START_Y;
            ball_dx = BALL_START_DELTA;
            ball_dy = BALL_START_DELTA;
        }

        for (int y = 0; y < FIELD_HIDTH; y++) {
            if (y == 0) {
                drawBorderWithPoints(left_player_point, right_player_point);
                continue;
            }

            for (int x = 0; x < FIELD_WIDTH; x++) {
                if (isBorderY(y)) {
                    printw("%c", SYMBOL_BORDER);
                } else {
                    if (isBall(x, y, ball_x, ball_y)) {
                        printw("%c", SYMBOL_BALL);
                    } else if (x == FIELD_MIDDLE) {
                        printw("%c", SYMBOL_MIDDLE);
                    } else if (isLeftPad(x, y, left_pad_y)) {
                        printw("%c", SYMBOL_LEFT_PAD);
                    } else if (isRightPad(x, y, right_pad_y)) {
                        printw("%c", SYMBOL_RIGHT_PAD);
                    } else {
                        printw("%c", SYMBOL_EMPTY_FIELD);
                    }
                }
            }
            printw("\n");
        }

        refresh();
        clear();
        nanosleep((const struct timespec[]){{0, 90000000L}}, NULL);
    } while (
        (key = getch()) != KEY_END_GAME
        && getGameWinner(left_player_point, right_player_point) == UNKNOWN_PLAYER_ID);

     endwin();

    char winner = getGameWinner(left_player_point, right_player_point);
    if (winner != UNKNOWN_PLAYER_ID) {
        winner == LEFT_PLAYER_ID ? drawFirstPlayerCongrats() : drawSecondPlayerCongrats();
    }
    return 0;
}

int isBorderY(int y) {
    return y == 0 || y == FIELD_HIDTH - 1 ? 1 : 0;
}

int isOutOfFiled(int x) {
    return x == 0 || x == FIELD_WIDTH - 1 ? 1 : 0;
}

int isBall(int x, int y, int ball_x, int ball_y) {
    return x == ball_y && y == ball_x ? 1 : 0;
}

int isLeftPad(int x, int y, int left_pad_y) {
    return x == LEFT_PAD_X && y >= left_pad_y && y < left_pad_y + PAD_SIZE ? 1 : 0;
}

int isRightPad(int x, int y, int right_pad_y) {
    return x == RIGHT_PAD_X && y >= right_pad_y && y < right_pad_y + PAD_SIZE;
}

int isAnyPad(int x, int y, int left_pad_y, int right_pad_y) {
    return isLeftPad(x, y, left_pad_y) == 1 || isRightPad(x, y, right_pad_y) == 1 ? 1 : 0;
}

char getMatchWinner(int ball_x) {
    return ball_x == 0 ? LEFT_PLAYER_ID : RIGHT_PLAYER_ID;
}

char getGameWinner(int left_player_point, int right_player_point) {
    if (WINNER_POINT == left_player_point) {
        return LEFT_PLAYER_ID;
    } else if (WINNER_POINT == right_player_point) {
        return RIGHT_PLAYER_ID;
    } else {
        return UNKNOWN_PLAYER_ID;
    }
}

void drawGreeting() {
    printf("================================================================================\n");
    printf("                          Welcome to the game pong!                             \n");
    printf("            The left racket is controlled by pressing the keys:                 \n");
    printf("                             a - up, z - down.                                  \n");
    printf("            The right racket is controlled by pressing the keys:                \n");
    printf("                             k - up, m - down.                                  \n");
    printf("                The score of the game is kept up to 21 points                   \n");
    printf("                         To end the game, click '.'                             \n");
    printf("                      To skip a turn, click Space bar                           \n");
    printf("                     (To start the game, click Enter)                           \n");
    printf("                                 Good luck!                                     \n");
    printf("================================================================================\n");
    getchar();
}

void drawFirstPlayerCongrats() {
    printf("================================================================================\n");
    printf("                                                                                \n");
    printf("                 Congratulations, the left player win!                          \n");
    printf("                                                                                \n");
    printf("================================================================================\n");
}


void drawSecondPlayerCongrats() {
    printf("================================================================================\n");
    printf("                                                                                \n");
    printf("                 Congratulations, the right player win!                         \n");
    printf("                                                                                \n");
    printf("================================================================================\n");
}

void drawBorderWithPoints(int left_player_point, int right_player_point) {
    left_player_point >= 10 ? printw("%d", left_player_point) : printw("%d ", left_player_point);
    for (int i = 0; i < FIELD_WIDTH - 4; i++) {
        printw("%c", SYMBOL_BORDER);
    }
    right_player_point >= 10 ? printw("%d\n", right_player_point) : printw(" %d\n", right_player_point);
}
