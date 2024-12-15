#include "../include/utils.hpp"
#include <iostream>
#include <algorithm>

Snake::Snake(const int width, const int height)
    : width(width), height(height), grid(std::vector<int>(width * height)) {}

void Snake::set_target() {
    int x = randrange(0, height);
    int y = randrange(0, width);
    while (grid[width * x + y]) {
        x = randrange(0, height);
        y = randrange(0, width);
    }
    target.x = x;
    target.y = y;
}

void Snake::set_distance() {
    int x = body[0].x - target.x;
    int y = body[0].y - target.y;
    if (x) { x = x > 0 ? 1 : -1; }
    if (y) { y = y > 0 ? 1 : -1; }
    distance = (Position){x, y};
}

void Snake::set_directions() {
    for (int i = 0; i < 4; i++) {
        int x = body[0].x + ACTIONS[i].x;
        int y = body[0].y + ACTIONS[i].y;
        if (x == target.x && y == target.y) {
            directions[i] = 1;
        } else if (
            0 > x || x >= height || 0 > y || y >= width ||
            grid[width * x + y]
        ) {
            directions[i] = -1;
        } else {
            directions[i] = 0;
        }
    }
}

void Snake::reset() {
    std::fill(grid.begin(), grid.end(), 0);
    body = {};
    done = 0;
    action = 0;
    int x = randrange(0, height);
    int y = randrange(0, width);
    body.push_back((Position){x, y});
    grid[width * x + y] = 1;
    set_target();
}

void Snake::print_grid() {
    std::cout << MOVE_CURSOR_TO_TOP;
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            std::cout << (
                grid[width * row + col] ? RED :
                row == target.x && col == target.y
                ? BLUE : BLACK
            ) << (col + 1 == width ? "\n" : " ");
        }
    }
    std::cout << "Size: " << body.size() << "\n";
}

void Snake::increase_body() {
    int size = (int)body.size();
    if (size >= width * height) {
        done = 1;
        return;
    }
    int x = body[0].x + ACTIONS[action].x;
    int y = body[0].y + ACTIONS[action].y;
    body.insert(body.begin(), (Position){x, y});
    grid[width * x + y] = 1;
}

void Snake::decrease_body() {
    int size = (int)body.size();
    int x = body[size - 1].x;
    int y = body[size - 1].y;
    grid[width * x + y] = 0;
    body.pop_back();
}
