# QSnake

`QSnake` is a Snake game written in C++ programming language, based on the [Q-Learning](https://en.wikipedia.org/wiki/Q-learning) algorithm. It is a fun and educational project that demonstrates how reinforcement learning, specifically Q-learning, can be applied to a classic game like Snake. The game’s AI learns to play Snake by interacting with the environment, receiving rewards for its actions, and improving over time.

## Install

To install and run the game, follow these steps:

### 1. Clone the repository:

```commandline
git clone https://github.com/yourusername/QSnake.git
```

### 2. Compile the game:

```commandline
cd QSnake
make
```

### 3. Run the game:

```commandline
./QSnake
```

## Requirements

- C++11 or later
- make
- A terminal emulator

## Gameplay

The game utilizes the Q-Learning algorithm, a type of reinforcement learning. The agent (the snake) takes actions based on the environment (the grid), receives rewards (such as points or penalties), and updates its knowledge over time in a Q-table.

### 1. Train snake

The agent (snake) interacts with the environment, exploring actions and learning over time. Here is an example of how the snake acts after training:

![output](https://github.com/user-attachments/assets/deecca94-550b-4037-aa45-219c28fb7736)

#### 1.1. Choose action

   There are 4 basic actions in the snake game. The snake does a random action during the exploration phase. Exploration rate is set with the `epsilon` parameter. By default `epsilon` is equal to `.0001` which means that `.01 %` of the actions will be selected randomly and `99.99 %` will be selected based on the action with highest `q value`.


   | Actions  | x  | y  |
   |----------|----|----|
   | UP       | -1 | 0  |
   | RIGHT    | 0  | 1  |
   | DOWN     | 1  | 0  |
   | LEFT     | 0  | -1 |

#### 1.2. State representation for each action

In this program, the state that occurs after each action of the snake is represented with two qualities. Though, action-based states can be represented also with more or less qualities. An optimal state representation should contain the information about the environment, the body itself, the consequences of the actions taken by the snake and shoulp support the snake's learning to eat foods without colliding its body or the walls.
   
##### 1.2.1. Direction state

The `direction state` is a one-dimensional array representing the types of collisions for each action type. The collision types could be encoded differently. The important thing here is to distinguish between collision types and assign a number to each collision type in terms of the consequences of the actions.

   | Directions | No collision | Target collision | Body Collision | Wall Collision |
   |------------|--------------|------------------|----------------|----------------|
   | UP         | 0            | 1                | -1             | -1             |
   | RIGHT      | 0            | 1                | -1             | -1             |
   | DOWN       | 0            | 1                | -1             | -1             |
   | LEFT       | 0            | 1                | -1             | -1             |

   
##### 1.2.2. Distance state

The `distance state` is a representative point of the distance between the head of the snake and the target. If the distance is positive, it is represented with `1`, if negative, with `-1`, if there's no difference, it's represented with `0`.

   | Δd | Δd < 0 | Δd = 0 | Δd > 0 | 
   |----|--------|--------|--------|
   | x  | -1     | 0      | 1      |
   | y  | -1     | 0      | 1      |


##### 1.2.3. State key

The State key is created by hashing `6` integer values: `4` related to the `direction state` and `2` related to the `distance state`. Below you see a state representation of an `action`.

  | State Key           | UP | RIGHT | DOWN | LEFT | Δdx | Δdy |
  |---------------------|----|-------|------|------|-----|-----|
  | 3005401531224964638 | 0  | 1     | -1   | 0    | 1   | -1  |

#### 1.3. Get reward

   Rewards are determined arbitrarily and may be decreased or increased:

  | No collision | Target collision | Body collision | Wall collision |
  |--------------|------------------|----------------|----------------|
  | 0            | 100              | -50            | -50            |

#### 1.4. Update q value

Q values are updated according to the Bellmann equation.

![formula](https://github.com/user-attachments/assets/e727e229-3334-410d-a0d0-1f55a0fa0597)

#### 1.5. Save and load q values

The `agent.dat` file is used to store the `Q-table` generated by the Q-learning algorithm. This file keeps track of the agent's learning progress and allows the snake to continue learning or resume its training from the point where it left off.

## Licence

This project is licensed under the GNU General Public License v3.0 - see the LICENSE file for details.
