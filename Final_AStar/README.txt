References:

- A* Pseudocode from: https://medium.com/@nicholas.w.swift/easy-a-star-pathfinding-7e6689c7f7b2

Notes:

For this project I used C12_LERP as the base.
It should be dropped directly into a Simplex 
I changed it so that there is no skybox, just a black background, and it defaults to
an orthographic view on Z. 

I have edited it so that rather than a cone traveling between arbitrary points in space,
it is a sphere traveling between hardcoded "grid" sections. The squares are cubes, but they
look like squares in a grid in orthographic view.

The positions are hardcoded because my loops to populate the grid would break the program,
but then I liked the idea of commenting out grid sections to create obstacles.

After I changed the graphics, I tried to figure out a way to turn the list of Stops into
Nodes, but then realized there just wasn't enough stored information on one of the Stops. 
From this point I tried to make a Node class.

The node class calculates its 4 nearest neighbors. It is meant to be used in tandem with
the A* algorithm within AppClass.cpp, but this is not implemented.