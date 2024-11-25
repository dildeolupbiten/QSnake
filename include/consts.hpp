#ifndef CONSTS_HPP
#define CONSTS_HPP

#define BLACK "\033[30m\u25A0\033[0m"
#define WHITE "\033[37m\u25A0\033[0m"
#define RED "\033[31m\u25A0\033[0m"
#define BLUE "\033[34m\u25A0\033[0m"
#define CLEAR "\033[2J"
#define MOVE_CURSOR_TO_TOP "\x1B[H"

typedef struct {
    int x;
    int y;
} Position;

extern const Position ACTIONS[4];

#endif // CONSTS_HPP
