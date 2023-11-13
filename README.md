# Asteroids

Asteroids recreation as my final project for the C++ course.

## Features

- Smooth spaceship controls for rotation and thrust
- Dynamic camera that adjusts to window resizing
- Ability to shoot bullets to destroy asteroids (WIP)
- Collision detection (soon™)
- Score tracking (soon™)
- Menu (maybe soon? dont know yet)

## Getting Started

### Prerequisites

- C++17 compatible compiler
- Vcpkg
- [threepp](https://github.com/markaren/threepp) - A C++ 3D graphics library for OpenGL

### Installation

1. Clone the repository:
   ```sh
   git clone https://github.com/Joranikus/Asteroids.git

2. Compile game

3. Run game

### Game Controls

- "A" - Rotate the spaceship to the left.
- "D" - Rotate the spaceship to the right.
- "W" - Apply thrust to move forward.
- "S" - Apply thrust to move backward.
- "SPACE" - Fire a bullet.

## Project Structure

- "MovementHandler" - An virtual class base class for objects that require movement.
- "SpriteInitializer" - Generates and manges sprites.
- "SpaceshipKeyListener" - Handles keyboard inputs for controlling the spaceship.
- "Spaceship" - Manages spaceship logic.
- "Bullet" - Creates bullet.