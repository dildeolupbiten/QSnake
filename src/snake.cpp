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
    distance = (Position){
        (body[0].x > target.x) - (body[0].x < target.x),
        (body[0].y > target.y) - (body[0].y < target.y)
    };
}

void Snake::set_directions() {
    for (int i = 0; i < 4; i++) {
        int x = body[0].x + ACTIONS[i].x;
        int y = body[0].y + ACTIONS[i].y;
        if (is_collision(x, y)) { directions[i] = -2; }
        else if (!is_safe_action(x, y)) { directions[i] = -1; }
        else if (x == target.x && y == target.y) { directions[i] = 2; }
        else { directions[i] = 0; }
    }
}

int Snake::flood_fill(const int x, const int y, const int i, int visited[]) {
    if (is_collision(x, y) || visited[x * width + y]) { return 0; }
    visited[x * width + y] = 1;
    int size = 1;
    for (auto& action : ACTIONS) {
        bool has_tail = false;
        Position tail;
        if (i > 1) {
            has_tail = true;
            tail = body[i];
            grid[tail.x * width + tail.y] = 0;
        }
        size += flood_fill(x + action.x, y + action.y, i - 1, visited);
        if (has_tail) { grid[tail.x * width + tail.y] = 1; }
    }
    return size;
}

int Snake::is_safe_action(const int x, const int y) {
    int visited[height * width] = {0};
    int size = body.size();
    return flood_fill(x, y, size - 1, visited) > size;
}

int Snake::is_out_of_bounds(const int x, const int y) {
    return 0 > x || x >= height || 0 > y || y >= width;
}

int Snake::is_collision(const int x, const int y) {
    if (is_out_of_bounds(x, y)) { return 1; }
    return grid[width * x + y] == 1;
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
    Position tail = body.back();
    grid[tail.x * width + tail.y] = 0;
    body.pop_back();
}
