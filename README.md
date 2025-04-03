# Sudoku Game in C++


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
![Login Screen](/images/login.png)

**Main Menu**  
![Main Menu](/images/menu.png)

**Difficulty Selection**  
![Difficulty Selection](/images/dif.png)

**Gameplay**  
![Gameplay](/images/game.png)

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
