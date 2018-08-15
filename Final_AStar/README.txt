References:

- A* Pseudocode from: https://medium.com/@nicholas.w.swift/easy-a-star-pathfinding-7e6689c7f7b2
- Linear Search from: https://www.geeksforgeeks.org/linear-search/
- Vector Containers from: https://en.cppreference.com/w/cpp/container/vector

Notes:

For this project I used C12_LERP as the base.
It should be put into a Simplex solution and added as a project to work.
I changed it so that there is no skybox, just a black background, and it defaults to
an orthographic view on Z. 

When I started the assignment, I worked from graphics down. As I got further into it,
I realized that the graphics I made did not have enough information to do the algorithm,
so I restarted from the other end (the data structures).

This is why the "grid" that gets drawn does not actually display what my algorithm is
doing- because they are not connected.

Originally I started trying to make a quad-drawing method but this didn't work out,
so instead I used cubes in orthographic view to make my "grid." I had to hardcode
these positions because my loops to create them were breaking the program.

I liked the idea of commenting out hardcoded positions in order to create obstacles,
so I tried to keep this idea when I initialized my list of Nodes. However, when I 
was developing my Node class, it made more sense to just have a boolean that decided
whether it was an obstacle or not, so I will have to remake my loops.

I worked mostly in AppClass.cpp and on the Node.cpp and Node.h.

The pathing algorithm is not finished yet, and I also could not bridge the gap between
the graphical grid and the structural nodes. Missing things are commented.
