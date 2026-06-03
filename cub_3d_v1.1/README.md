
# Cub3D

This project has been created as part of the 42 curriculum by *jadelgad*, *alemonto*.

## Description

Cub3D is a 3D raycasting project implemented in C as part of the 42 curriculum. The goal is to build a simple first-person renderer (similar in spirit to Wolfenstein 3D)
that parses a map file, performs raycasting to render walls and sprites, and allows the user to navigate a 2D map with a 3D-like view.
This project emphasizes low-level graphics programming, math for projections, resource management, and handling user input in C.

## Features

- Raycasting-based 3D projection of a 2D map
- Texture mapping for walls
- Basic sprite rendering
- Player movement and view rotation
- Map parsing from `.cub` files
- Simple collision handling

## Instructions

Prerequisites
- A C compiler (gcc or clang)
- make
- The MiniLibX library (minilibx) or an equivalent. Use the macOS version of MiniLibX on macOS, or the Linux port (mlx_linux) on Linux.
- You must rename the minilibx library to "minilibx" to be able to compile with the current Makefile.

Build
1. Open a terminal in the repository root.
2. Run:

```
make
```

This produces the executable.

Run
```
./Cub3D <path/to/map.cub>
```

Example:
```
./Cub3D maps/example.cub
```

Notes
- Make sure MiniLibX is installed and the Makefile links against the correct library for your platform.
- The program expects correctly formatted `.cub` maps. See the `maps/` directory for examples and format.

## Map format:

A `.cub` file must contains:
- Texture file paths for north/south/east/west wall faces
- Floor and ceiling colors
- The map layout using characters (e.g., '1' = wall, '0' = empty, 'N/S/E/W' = player start and orientation)
Refer to the project specification or example maps in the repository for exact format and ordering rules.

## Controls

Movement
- W / ↑ : move forward
- S / ↓ : move backward
- A : strafe left
- D : strafe right

Rotation
- ← : rotate left
- → : rotate right

Other
- ESC or window close: exit

## Troubleshooting

- If the window fails to open or you get linker errors, verify the MiniLibX path and library flags in the Makefile.
- If rendering is incorrect, check that your `.cub` file is well-formed and that texture paths are valid and accessible.

## Resources

Helpful references for raycasting and low-level graphics:
- YouTube videos about raycasting (3DSage).
- Lode Vandevenne's raycasting tutorial — https://lodev.org/cgtutor/raycasting.html
- MiniLibX documentation and community examples
- C standard library documentation (man pages)

AI usage
- 
- AI assistant (ChatGPT, Copilot, Gemini...) was used to draft and format this README, also to structure the project(make a roadmap for implementation, etc..).
- To understand the main topics of the project such as raycasting and maths formulas like Pitagoras. 
- No AI was used to implement, modify, or debug the project's source code or core algorithms;
- All code were made by the project contributors listed above.

## Additional notes

- The bonus parts we completed are  the minimap, sprites and the colisions with walls.

