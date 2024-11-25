#include "../include/utils.hpp"
#include <chrono>
#include <thread>
#include <random>
#include <iostream>
#include <algorithm>

std::mt19937 gen;

void init_random() {
    std::random_device rd;
    gen.seed(rd());
}

int randrange(const int min, const int max) {
    std::uniform_int_distribution<int> dist(min, max - 1);
    return dist(gen);
}

double uniform(const double min, const double max) {
    std::uniform_real_distribution<double> dist(min, max);
    return dist(gen);
}

int max_index(Agent *agent, Snake *snake, size_t key) {
    std::array<double, 4> values = agent -> table[key];
    auto it = std::max_element(values.begin(), values.end());
    return std::distance(values.begin(), it);
}

void choose_action(Agent *agent, Snake *snake, const double epsilon) {
    if (uniform(0, 1) < epsilon) {
        snake -> action = randrange(0, 4);
        snake -> key = agent -> get_key(snake);
        agent -> init_key(snake -> key);
    } else {
        snake -> key = agent -> get_key(snake);
        agent -> init_key(snake -> key);
        snake -> action = max_index(agent, snake, snake -> key);
    }
}

int penalty_for_obstacle_collision(
    Snake *snake,
    const std::array<int, 3>& rewards
) {
    if (snake -> directions[snake -> action] == -1) {
        snake -> done = 1;
        return rewards[1];
    }
    return rewards[2];
}

int reward_for_target_collision(
    Snake *snake,
    const std::array<int, 3>& rewards
) {
    snake -> increase_body();
    if (snake -> directions[snake -> action] == 1) {
        snake -> set_target();
        return rewards[0];
    }
    snake -> decrease_body();
    return rewards[2];
}

int get_reward(Snake *snake, const std::array<int, 3>& rewards) {
    int reward = 0;
    reward += penalty_for_obstacle_collision(snake, rewards);
    if (snake -> done) { return reward; }
    reward += reward_for_target_collision(snake, rewards);
    return reward;
}

double q_algorithm(
    const double current_q,
    const double max_next_q,
    const int reward,
    const double learning_rate,
    const double discount_factor
) {
    double next_q = reward + discount_factor * max_next_q;
    return (1 - learning_rate) * current_q + learning_rate * next_q;
}

void update_q_value(
    Agent *agent,
    Snake *snake,
    const size_t current_key,
    const size_t next_key,
    const int reward,
    const double learning_rate,
    const double discount_factor
) {
    double current_q = agent -> table[current_key][snake -> action];
    int max_next_q_index = max_index(agent, snake, next_key);
    double max_next_q = agent -> table[next_key][max_next_q_index];
    double new_q = q_algorithm(
        current_q,
        max_next_q,
        reward,
        learning_rate,
        discount_factor
    );
    agent -> table[current_key][snake -> action] = new_q;
}

void train_snake(
    Agent *agent,
    Snake *snake,
    const double learning_rate,
    const double discount_factor,
    const double epsilon,
    const int episodes,
    const int play,
    const std::array<int, 3>& rewards
) {
    double avg_size = 0;
    std::cout << CLEAR;
    for (long episode = 0; episode < episodes; episode++) {
        snake -> reset();
        if (episode >= episodes - 10) { std::cout << CLEAR; }
        while (!snake -> done) {
            choose_action(agent, snake, epsilon);
            size_t previous_key = snake -> key;
            int reward = get_reward(snake, rewards);
            size_t current_key = agent -> get_key(snake);
            update_q_value(
                agent,
                snake,
                previous_key,
                current_key,
                reward,
                learning_rate,
                discount_factor
            );
            if (play && episode >= episodes - 10) {
                snake -> print_grid();
                std::this_thread::sleep_for(std::chrono::microseconds(100000));
            }
        }
        if (play && episode >= episodes - 10) { continue; }
        avg_size += ((double)snake -> body.size() - avg_size) / (episode + 1);
        std::cout << "Episode: " << episode << " " << "Avg. Size: " <<
                     avg_size <<  " " << std::endl;
    }
}
