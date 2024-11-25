#ifndef AGENT_HPP
#define AGENT_HPP

#include "snake.hpp"
#include <map>
#include <string>

class Agent {
public:
    Agent() = default;
    ~Agent() = default;
    std::map<size_t, std::array<double, 4>> table;
    size_t get_key(Snake *snake);
    void init_key(const size_t& key);
    void save(const std::string& filename);
    void load(const std::string& filename);
};

#endif // AGENT_HPP
