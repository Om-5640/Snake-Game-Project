# ***Snake Game***


## Introduction
Welcome to the Snake Game! This project is a fun and engaging game where players control a snake to collect food while avoiding obstacles and itself. The game supports different difficulty levels and introduces teleportation portals to add a unique twist.
## Features
- **Adjustable Difficulty Levels**: Choose between Easy, Medium, and Hard modes, affecting the snake's speed.
- **Dynamic Obstacles**: Players can opt to enable obstacles that make the game more challenging.
- **Teleportation Portals**: A unique feature where two portals allow the snake to teleport between them.
- **Real-time User Input Handling**: Move the snake in real-time using keyboard inputs.
- **Randomized Food Placement**: The food appears in different locations upon consumption.
- **Classic Collision Detection**: The game ends if the snake collides with the wall, itself, or obstacles.
## Installation & Execution
### Prerequisites:

- A C++ compiler (such as **g++** or **MSVC**)
- A terminal or command prompt

### Compilation:

Use the following command to compile the program:
```bash
g++ snake_game.cpp -o snake_game
```
### Running the Game:

After compiling, execute the game:
```bash
./snake_game
```
## Controls

- **W** - Move Up
- **A** - Move Left
- **S** - Move Down
- **D** - Move Right
- **X** - Quit the Game
## Game Mechanics

- The game starts with the snake in the center of the screen.
- The snake moves in the selected direction and grows upon consuming food.
- If obstacles are enabled, the snake must avoid them.
- If portals are enabled, stepping into one teleports the snake to the other.
- The game ends if the snake collides with itself, the walls, or an obstacle.
## Unique Feature: Data Structure Analysis

This game leverages several data structures to maintain smooth gameplay:

### **1. Vector (`std::vector`)**

- **Snake Representation**: The snake’s body is stored as a vector of pairs (`std::vector<std::pair<int, int>>`). Each element represents a coordinate (x, y), allowing easy addition and removal of segments.
- **Obstacles & Portals**: Obstacles and portals are stored in separate vectors, ensuring efficient lookup and updates.

### **2. Enum (`enum Direction`)**

- Used to define movement directions (`STOP`, `LEFT`, `RIGHT`, `UP`, `DOWN`), improving readability and reducing magic numbers in the code.

### **3. Pair (`std::pair<int, int>`)**

- A simple yet powerful structure used for **storing coordinates** of snake segments, food, obstacles, and portals.

### **4. Looping & Conditionals**

- A `while` loop drives the game, updating the game state, handling user input, and rendering the frame continuously.
- `if-else` conditions check for collisions, food consumption, and interactions with obstacles and portals.

By using **vectors and pairs**, the game ensures **dynamic memory management, efficient snake growth, and fast collision detection**, making it both robust and scalable.

## Future Enhancements

- **Multiplayer Mode**: Adding support for two players controlling separate snakes.
- **Power-ups**: Introducing temporary speed boosts or extra points.
- **Leaderboard**: A scoring system to track and display the highest scores.
## Conclusion

This Snake Game combines classic gameplay with modern coding principles. With the addition of obstacles, portals, and structured object management, it stands out as a well-designed C++ console application. Try it out and enjoy the game!
### **Author**: Rushiraj Navar ,Om Pandya and Het Lathiya
