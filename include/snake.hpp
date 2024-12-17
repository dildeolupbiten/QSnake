#ifndef SNAKE_HPP
#define SNAKE_HPP

#include "consts.hpp"
#include <array>
#include <vector>

class Snake {
public:
    Snake(const int width, const int height);
    ~Snake() = default;
    const int width;
    const int height;
    int done;
    int action;
    size_t key;
    std::array<int, 4> directions;
    std::vector<int> grid;
    std::vector<Position> body;
    Position target;
    Position distance;
    void set_target();
    void set_distance();
    void set_directions();
    int flood_fill(int x, int y, int visited[]);
    int is_safe_move(int x, int y);
    void reset();
    void print_grid();
    void increase_body();
    void decrease_body();
};

#endif // SNAKE_HPP
