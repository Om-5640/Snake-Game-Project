
# 🎮 Advanced Tetris Game 🧱


An enhanced Tetris game built in C++ for the Windows console. This project takes the classic Tetris experience to the next level with modern features such as ghost piece preview, next piece preview, colored blocks using emoji, flickerless rendering, sound effects, and more—all while preserving smooth gameplay and a clean, fixed grid.

## 📚 Table of Contents

- [✨ Features](#features)
- [💾 Installation](#installation)
- [🎮 Usage](#usage)
- [🧩 Tetromino Shapes](#tetromino-shapes)
- [🎮 Controls](#controls)
- [👥 Credits](#credits)

## ✨ Features

- **👻 Ghost Piece Preview:**\
  A dim "shadow" of the current tetromino shows exactly where it will land when dropped.

- **🔮 Next Piece Preview:**\
  A dedicated preview box displays the upcoming tetromino, allowing you to plan ahead.

- **🔁 Restart Functionality:**\
  After a game over, press **R** to restart the game or **ESC** to exit.

- **🎨 Colored Blocks Using Emojis:**\
  Each tetromino is rendered in a distinct color using emoji symbols (e.g., 🟦, 🟨, 🟪, etc.).

- **🌑 Dark Background for Empty Cells:**\
  A dark ANSI background is applied to empty grid cells, enhancing contrast with the colored blocks.

- **🔊 Sound Effects:**\
  Beep sounds indicate actions such as moving, rotating, hard dropping, clearing lines, leveling up, and game over.

- **📊 Score and Level Display:**\
  The game continuously updates and displays your current score and level.

## 💾 Installation

1. **Requirements:**

   - 🪟 Windows operating system
   - 🛠️ A C++ compiler (e.g., g++, MSVC)
   - 🧱 Windows console with UTF‑8 support and an emoji-capable font (e.g., "Segoe UI Emoji")

2. **Steps:**

   - 📂 Clone this repository or download the source files.
   - 💻 Open a terminal in the project directory.
   - 🧾 Compile the code. For example, with g++:
     ```bash
     g++ -o TetrisGame main.cpp -std=c++11 -static
     ```
   - ▶️ Run the generated executable:
     ```bash
     ./TetrisGame
     ```

## 🎮 Usage

- **Movement:**\
  Use the arrow keys to move left/right, rotate (up arrow), or soft-drop (down arrow).

- **Hard Drop:**\
  Press the **Spacebar** to instantly drop the active tetromino.

- **Restart/Exit:**\
  When the game is over, press **R** to restart or **ESC** to exit the game.

- **Ghost & Next Piece Preview:**\
  Watch the ghost piece on the grid to see the landing position, and check the next piece preview box to plan your moves.

## 🧩 Tetromino Shapes

Here are the standard 7 tetrominoes used in the game:

- **I** (🟦): `{{1, 1, 1, 1}}`
- **O** (🟨): `{{1, 1}, {1, 1}}`
- **T** (🟪): `{{0, 1, 0}, {1, 1, 1}}`
- **S** (🟩): `{{0, 1, 1}, {1, 1, 0}}`
- **Z** (🟥): `{{1, 1, 0}, {0, 1, 1}}`
- **J** (🟫): `{{1, 0, 0}, {1, 1, 1}}`
- **L** (🟧): `{{0, 0, 1}, {1, 1, 1}}`

## 🎮 Controls

| Action                    | Key           |
| ------------------------- | ------------- |
| Move Left                 | ⬅️  Arrow Key |
| Move Right                | ➡️  Arrow Key |
| Rotate                    | ⬆️  Arrow Key |
| Soft Drop                 | ⬇️  Arrow Key |
| Hard Drop                 | Spacebar      |
| Restart (After Game Over) | R or r        |
| Exit Game                 | ESC           |

## 👥 Credits

- **Developer:** 
  1. Om Pandya
  2. Het Lathiya 
  3. Rushiraj Navar

