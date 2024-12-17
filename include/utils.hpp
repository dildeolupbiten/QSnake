#ifndef UTILS_HPP
#define UTILS_HPP

#include "snake.hpp"
#include "agent.hpp"

void init_random();

int randrange(const int min, const int max);

double uniform(const double min, const double max);

int max_index(Agent *agent, Snake *snake, size_t key);

void choose_action(Agent *agent, Snake *snake, const double epsilon);

int penalty_for_obstacle_collision(Snake *snake);

int bonus_for_target_collision(Snake *snake);

int penalty_for_dangerous_action(Snake *snake);

int get_reward(Snake *snake);

double q_algorithm(
    const double current_q,
    const double max_next_q,
    const int reward,
    const double learning_rate,
    const double discount_factor
);

void update_q_value(
    Agent *agent,
    Snake *snake,
    const size_t current_key,
    const size_t next_key,
    const int reward,
    const double learning_rate,
    const double discount_factor
);

void train_snake(
    Agent *agent,
    Snake *snake,
    const double learning_rate,
    const double discount_factor,
    const double epsilon,
    const int episodes,
    const int play,
    const double sleep
);

#endif // UTILS_HPP
