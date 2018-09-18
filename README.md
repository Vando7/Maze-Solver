# Maze-Solver
Find the shortest path between two points in a maze.

# Usage
First, you must have an image meeting the requirements below.

Then you run the program in the command line with a single parameter.
The parameter should be the path to the image in quotes.
```
 Maze_solver.exe "E:\Stuff and stuff\maze.ppm"
```

# Maze image requirements.
- Must be encoded in ASCII
- Must not have **any** comments inside it.
- Has to have at least one green pixel and blue pixel which represent the start and end respectively.
- The start and end have to be in pure colors, as in **(  0,255,  0)** for green and **(  0,  0,255)** for blue.

# How it works.
Let's say we have a 128x64 image of a maze that meets the requirements.

-Now the program makes a 128 by 64 grid of __short ints__ with 0 as the black pixels and 1 as the white pixels. If we encounter a white pixel, we give it an ID and assign its X and Y coordinates to that ID.

-Next we make a graph. The number of vertices in the graph is equal to the number of white pixels and each ID of a white pixel is also the ID of that pixel's corresponding vertex in the graph.

-For every two adjacent white pixels add an edge between them.

-At this point we have loaded the maze logically into memory.

-Run dijkstra's algorithm to find the shortest path from Green to Blue.

-Write the path into the grid.

-Output the grid back to a .ppm file
