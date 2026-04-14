*This project has been created as part of the 42 curriculum by jaime.*

## Description

**cub3D** is a 3D graphical maze renderer inspired by [Wolfenstein 3D](https://en.wikipedia.org/wiki/Wolfenstein_3D) (Id Software, 1992), widely considered the first true first-person shooter. The program uses **ray-casting** to create a real-time, first-person perspective view of a maze defined in a `.cub` scene file.

The project renders textured walls (different textures for each cardinal direction), configurable floor and ceiling colors, and supports smooth player movement and camera rotation through the maze.

### Features

- Real-time ray-casting engine using the DDA (Digital Differential Analyzer) algorithm
- Four distinct wall textures based on cardinal orientation (N, S, E, W)
- Configurable floor and ceiling RGB colors
- Smooth movement with WASD keys and camera rotation with arrow keys
- Robust `.cub` scene file parser with comprehensive error handling
- Clean exit via ESC key or window close button
- No memory leaks — all heap allocations properly freed

## Instructions

### Prerequisites

- A Linux system with X11 (Xlib and Xext)
- `cc` (gcc/clang), `make`

### Compilation

```bash
make        # Compile the project
make clean  # Remove object files
make fclean # Remove object files and binary
make re     # Full recompile
```

### Execution

```bash
./cub3D maps/map.cub
```

The program takes a single argument: a `.cub` scene description file.

### Map file format

The `.cub` file must contain:
- Texture paths for each wall direction: `NO`, `SO`, `WE`, `EA`
- Floor and ceiling colors: `F R,G,B` and `C R,G,B` (values 0–255)
- A map composed of `0` (empty), `1` (wall), and one player spawn (`N`/`S`/`E`/`W`)
- The map must be fully enclosed by walls

Example:
```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 135,206,235

111111
100101
101001
1100N1
111111
```

### Controls

| Key | Action |
|-----|--------|
| W | Move forward |
| S | Move backward |
| A | Strafe left |
| D | Strafe right |
| ← | Rotate camera left |
| → | Rotate camera right |
| ESC | Quit |

## Resources

### References

- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html) — the primary reference for the DDA raycasting algorithm used in this project
- [42 miniLibX documentation](https://harm-smits.github.io/42docs/libs/minilibx) — miniLibX API reference
- [Wolfenstein 3D source code](https://github.com/id-Software/wolf3d) — original game source for historical context

### AI Usage

AI tools (Claude by Anthropic) were used during development for:
- **Code structure planning**: helping design the modular file layout and deciding how to split parsing, rendering, and input handling
- **Debugging assistance**: identifying issues in map validation edge cases and DDA implementation details
- **Norm compliance**: ensuring all files respect the 42 coding standard (max 5 functions/file, max 25 lines/function)

All generated code was reviewed, understood, and adapted manually. The raycasting algorithm, parser logic, and memory management were verified through manual testing and peer review.
