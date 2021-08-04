# Maze-Solver
Find and draw a path between two points in a maze using either A* or Dijkstra.

The **Start** and **End** are indicated with a **Green** and a **Blue** pixel respectively.

Written in C++ using Code::Blocks and gcc compiler. To build open the C::B project file (.cbp) in Code::Blocks and build.

# Example
### Unsolved maze.
![alt text](https://i.imgur.com/tLLtRSq.png) 
### Solved maze.
![alt text](https://i.imgur.com/jtrl3oO.png)


## Usage
First, you must have an image meeting the requirements below.

Then you run the program in the command line with a single parameter.
The parameter should be the path to the image in quotes.
```
 Maze_solver.exe "E:\Stuff and stuff\maze.ppm" 1
```
Where 1 is for A* and 2 is for Dijkstra.

## Maze image requirements.
- Must be a .ppm file encoded in ASCII.
- Must not have **any** comments inside it.
- Has to have at least one green pixel **(  0,255,  0)** and one blue pixel **(  0,  0,255)** which represent the start and end respectively.
