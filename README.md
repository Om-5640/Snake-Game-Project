# 404 Not Found

# Snake Game with Portals

## 📌 Overview

This is a **Snake Game** built in **C++** that features obstacles and an optional **portal teleportation system**. The game allows the player to navigate the snake, eat food to grow, and avoid crashing into obstacles or itself. If portals are enabled, the snake can teleport between two portal points on the grid.

## 🎮 How to Play

- Use the **arrow keys** or **W, A, S, D** to move the snake.
- Eat food to grow and increase your score.
- Avoid hitting the walls, obstacles, or yourself.
- **Optional:** If portals are enabled, stepping into one will teleport the snake to the other portal.

## 🛠️ Setup & Compilation

### Windows

1. **Ensure you have a C++ compiler** (MinGW or MSVC).
2. Open **Command Prompt** and navigate to the folder containing `snake_game.cpp`.
3. Compile the game using:
   ```sh
   g++ snake_game.cpp -o snake_game.exe
   ```
4. Run the game:
   ```sh
   snake_game.exe
   ```

## 🔧 Features

- **Customizable Grid Size**: Set the width and height of the game.
- **Difficulty Levels**: Easy, Medium, and Hard speeds.
- **Obstacles**: Randomly placed barriers to increase challenge.
- **Teleportation Portals**: Optional feature that allows teleporting between two points.
- **Food Types**:
  - `F` (Normal Food) → +10 points
  - `S` (Special Food) → +30 points
  - `M` (Mega Food) → +50 points
- **Game Over Screen**: Displays the current and highest score.

## 🏆 Scoring System

| Food Type       | Points | Snake Growth |
| --------------- | ------ | ------------ |
| **F** (Normal)  | +10    | 1 Segment    |
| **S** (Special) | +30    | 3 Segments   |
| **M** (Mega)    | +50    | 5 Segments   |

## 🔄 Restarting the Game

- When the game is over, press **'r'** to restart.
- Press any other key to **exit**.

## ❌ Losing Conditions

- Hitting the **walls**.
- Running into **obstacles**.
- Colliding with **your own body**.

## 👥 Developers & Group Number

- **Developers**:

- Om Pandya(202401136)

- Het Lathiya (202401104)

- Rushiraj Navar (202401127)

- **Group Number**: 2

