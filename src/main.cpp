#include "../include/utils.hpp"

int main() {
    init_random();
    double learning_rate = .1;
    double discount_factor = .9;
    double epsilon = .0001;
    int episodes = 1;
    int width = 10;
    int height = 10;
    int play = 1; // will play the game 1 time.
    double sleep = .01;
    std::array<int, 3> rewards = {100, -30, 0};
    Agent *agent = new Agent();
    agent -> load("agent.dat");
    Snake *snake = new Snake(width, height);
    train_snake(
        agent,
        snake,
        learning_rate,
        discount_factor,
        epsilon,
        episodes,
        play,
        sleep,
        rewards
    );
    // agent -> save("agent.dat");
    return 0;
}
