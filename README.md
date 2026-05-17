# README.md

# Tetris

A fully playable Tetris clone built in modern C++ using SDL2. This project was created as a deep dive into game development, object-oriented programming, modular software design, and low-level rendering/event handling.

The goal of this project was not just to recreate Tetris, but to understand how games are structured internally — from rendering and input handling to collision systems, board logic, and piece management.

## Features

* Classic Tetris gameplay
* Piece movement and rotation
* Collision detection
* Line clearing system
* Board/grid management
* Keyboard controls
* SDL2-based rendering pipeline
* Modular OOP-based architecture
* Clean separation of game systems
* Cross-platform build support using CMake

---

## Tech Stack

### Language

* C++

### Libraries

* SDL2
* SDL2_image

### Build System

* CMake

---

## Why I Built This

This project started as a way to learn game development from scratch using C++.

Instead of using a game engine like Unity or Unreal Engine, I wanted to understand how games actually work internally. That led me to SDL2 — a low-level multimedia library used for rendering, input handling, textures, timing, and game loops.

At the beginning, even displaying a simple window felt difficult. Understanding event loops, rendering pipelines, keyboard handling, linking libraries, asset management, and CMake configuration took a lot of experimentation and debugging.

Over time, the project evolved into a much larger learning experience involving:

* Object-Oriented Programming
* Modular software architecture
* Memory management
* Game loops and timing
* Grid-based game logic
* Collision systems
* Rendering pipelines
* Input systems
* Build systems using CMake
* Debugging linker/compiler issues

This project helped bridge the gap between writing small C++ programs and building an actual interactive software project.

---

## Project Structure

```bash
.
├── build/
├── include/
│   ├── board.h
│   ├── definitions.h
│   ├── game.h
│   ├── piece.h
│   └── textureManager.h
├── src/
│   ├── board.cpp
│   ├── game.cpp
│   ├── main.cpp
│   ├── piece.cpp
│   └── textureManager.cpp
├── assets/
├── CMakeLists.txt
└── README.md
```

---

## Architecture Overview

### Game Class

Responsible for:

* Initializing SDL2
* Creating the window and renderer
* Managing the game loop
* Handling updates and rendering
* Cleaning resources

### Board Class

Responsible for:

* Managing the game grid
* Storing locked pieces
* Clearing completed rows
* Collision detection
* Board rendering

### Piece Class

Responsible for:

* Tetromino generation
* Rotation logic
* Movement logic
* Piece rendering
* Piece placement

### Texture Manager

Handles:

* Loading textures
* Rendering assets
* SDL texture abstraction

---

## Concepts Implemented

### Object-Oriented Programming

The project heavily focuses on OOP principles:

* Encapsulation
* Separation of concerns
* Class-based architecture
* Reusable systems
* Modular design

Each game system was separated into its own class to keep the code maintainable and scalable.

---

## SDL2 Usage

SDL2 was used for:

* Window creation
* Rendering
* Keyboard input
* Event handling
* Timing/game loop management
* Texture rendering

Learning SDL2 was one of the hardest and most rewarding parts of this project.

Understanding how rendering works frame-by-frame and how event-driven systems work gave me a much better understanding of how games are structured internally.

---

## Controls

| Key         | Action       |
| ----------- | ------------ |
| Left Arrow  | Move Left    |
| Right Arrow | Move Right   |
| Down Arrow  | Move Down    |
| Up Arrow    | Rotate Piece |

---

## How to Run

## Prerequisites

Install:

* C++ compiler (g++)
* CMake
* SDL2
* SDL2_image

### Ubuntu/Debian

```bash
    cd tetris
    chmod +x install.sh
    ./install.sh
```

---

## Clone the Repository

```bash
git clone https://github.com/ka1rav6/tetris.git
cd tetris
```

---

## Build the Project

```bash
mkdir build
cd build
cmake ..
make
```

---

## Run the Game

```bash
./app
```

---

## Challenges Faced

Some of the biggest challenges during development were:

* Understanding SDL2 setup and linking
* Handling rendering correctly
* Managing game loops
* Implementing rotation logic
* Collision detection
* Organizing large codebases
* Fixing linker/compiler errors
* Learning CMake properly
* Designing maintainable architecture

A lot of time was spent debugging issues that initially felt impossible to solve.

But that process ended up teaching me the most.

---

## What I Learned

This project taught me:

* Real-world C++ development
* Game architecture and development
* SDL2 fundamentals
* Build systems and dependencies
* Writing modular code
* Designing scalable systems
* Problem solving and debugging
* Structuring larger projects
* Event-driven programming

Most importantly, it taught me how to approach difficult technical problems step-by-step.

---

## Future Improvements

Potential future additions:

* Hold piece functionality
* Sound effects
* Better animations
* Difficulty scaling
* Save high scores
* Pause menu
* Multiplayer support

---

## Repository

GitHub Repository:

[https://github.com/ka1rav6/tetris](https://github.com/ka1rav6/tetris)

---

## Acknowledgements

Special thanks to:

* SDL2 Documentation
* Open-source game development resources
* The C++ community


