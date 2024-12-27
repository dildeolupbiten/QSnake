#include "../include/agent.hpp"
#include <fstream>
#include <iostream>
#include <functional>

size_t Agent::get_key(Snake *snake) {
    snake -> set_distance();
    snake -> set_directions();
    std::array<int, 6> state;
    for (int i = 0; i < 4; i++) { state[i] = snake -> directions[i]; }
    state[4] = snake -> distance.x;
    state[5] = snake -> distance.y;
    size_t key = 0;
    for (int i = 0; i < 6; i++) {
        key ^= std::hash<int>{}(state[i]) +
            0x9e3779b9 + (key << 6) + (key >> 2);
    }
    return key;
}

void Agent::init_key(const size_t& key) {
    if (table.find(key) == table.end()) {
        table[key] = std::array<double, 4>();
    }
}

void Agent::save(const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }
    for (const auto& entry : table) {
        file.write(
            reinterpret_cast<const char*>(&entry.first),
            sizeof(size_t)
        );
        file.write(
            reinterpret_cast<const char*>(entry.second.data()),
            sizeof(double) * 4
        );
    }
    file.close();
}

void Agent::load(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }
    while (file.peek() != EOF) {
        size_t key;
        std::array<double, 4> value;
        file.read(
            reinterpret_cast<char*>(&key),
            sizeof(size_t)
        );
        file.read(
            reinterpret_cast<char*>(value.data()),
            sizeof(double) * 4
        );
        table[key] = value;
    }
    file.close();
}
