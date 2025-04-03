# Sudoku Game in C++

![Sudoku Menu](Screenshot%202025-04-03%20at%2010.19.08 PM.png)

A terminal-based Sudoku game implemented in C++ with multiple difficulty levels and user authentication.

## Features

- 🎮 Three difficulty levels: Easy, Moderate, and Hard
- 🔐 User authentication (Sign Up/Log In)
- ⏱️ Timed gameplay
- 🎨 Colorful terminal interface
- 🖥️ Cross-platform support (Unix/Windows)
- 🕹️ Keyboard-controlled cursor navigation

## Screenshots

**Login Screen**  
![Login Screen](Screenshot%202025-04-03%20at%2010.18.51 PM.png)

**Main Menu**  
![Main Menu](Screenshot%202025-04-03%20at%2010.19.08 PM.png)

**Difficulty Selection**  
![Difficulty Selection](Screenshot%202025-04-03%20at%2010.19.17 PM.png)

**Gameplay**  
![Gameplay](Screenshot%202025-04-03%20at%2010.19.26 PM.png)

## Installation

### Prerequisites
- C++ compiler (g++ or equivalent)
- Make (optional)

### Building from Source
```bash
git clone https://github.com/yourusername/sudoku-game.git
cd sudoku-game
make  # or compile manually: g++ game.cpp clui.cpp functions.cpp -o sudoku
./sudoku
