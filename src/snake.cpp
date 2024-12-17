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
        if (
            0 > x || x >= height || 0 > y || y >= width ||
            grid[width * x + y]
        ) {
            directions[i] = -2;
        } else if (!is_safe_action(x, y)) {
            directions[i] = -1;
        } else if (x == target.x && y == target.y) {
            directions[i] = 2;
        } else {
            directions[i] = 0;
        }
    }
}

int Snake::flood_fill(int x, int y, int visited[]) {
    if (
        x < 0 || x >= height || y < 0 || y >= width ||
        grid[x * width + y] || visited[x * width + y]
    )
        return 0;
    visited[x * width + y] = 1;
    int size = 1;
    size += flood_fill(x + 1, y, visited);
    size += flood_fill(x - 1, y, visited);
    size += flood_fill(x, y + 1, visited);
    size += flood_fill(x, y - 1, visited);
    return size;
}

int Snake::is_safe_action(int x, int y) {
    int visited[height * width] = {0};
    return flood_fill(x, y, visited) > body.size();
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
