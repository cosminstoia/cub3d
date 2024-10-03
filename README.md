# cub3D

## Overview

**Cub3D** is a project from the 42 school curriculum that introduces you to **raycasting** and basic **3D rendering**. The objective is to create a simple 3D game engine similar to **Wolfenstein 3D**. Using **raycasting**, the program renders a first-person view from a 2D map. The project emphasizes working with graphics, handling player movement, and managing textures and sprites.

## Features

- **Raycasting-based 3D rendering**: First-person perspective using 2D raycasting.
- **Player movement**: Allows movement and viewing in all directions.
- **Textures**: Textured walls for visual appeal.
- **Basic collision detection**: Prevents walking through walls.
- **Mini-map** (optional): A 2D overhead representation of the game world.

## Project Requirements

To meet the requirements, Cub3D must follow these rules:

- **Raycasting** is used for a 3D view based on a 2D map.
- The game runs on **macOS** using the **MiniLibX** library.
- The player can move forward, backward, and rotate.
- Wall distance affects their size in the display.
- **Textured walls** are required.
- A map must define the player's starting position.
- The map must be enclosed by walls (no leaks).
- Written in **C** and adheres to 42's coding standards.

### Additional Rules:

- **No external libraries** other than MiniLibX.
- Proper **memory management** and **error handling**.

## Controls

| Key           | Action               |
| ------------- | -------------------- |
| `W`           | Move forward         |
| `S`           | Move backward        |
| `A`           | Strafe left          |
| `D`           | Strafe right         |
| `Left Arrow`  | Rotate left          |
| `Right Arrow` | Rotate right         |
| `ESC`         | Quit the game        |

## Map Structure

Maps are defined in `.cub` files, which describe the layout using specific characters.
In the `.cub` file, you also define the textures for the walls and colors for the floor and ceiling:

### Example:

```
NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture

F 220,100,0
C 225,30,0

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
