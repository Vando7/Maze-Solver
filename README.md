# Maze-Solver
Read an image of a maze in the .ppm image format, encoded in ASCII and output a solved version of it.

# Usage
In the command line with a single parameter for the image path.
The parameter must be in quotes, for example:
```
 Maze_solver.exe "E:\Stuff and stuff\maze.ppm"
```

# Maze image requirements.
- Must be encoded in ASCII
- Must not have **any** comments inside it.
- Has to have at least one green pixel and blue pixel which represent the start and end respectively.
- The start and end have to be in pure colors, as in **(  0,255,  0)** for green and **(  0,  0,255)** for blue.

