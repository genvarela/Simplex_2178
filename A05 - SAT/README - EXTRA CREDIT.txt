Notes:
I attempted the extra credit portion of the assignment 
to draw the separating planes as they were being tested.

First I set up flags using the eSATresults enum, which
are set as the test is performed. There is a getter for
the current status of the flag.

When the tests are being done on the objects, I made it
so that a magenta plane appears when one of the first 
three tests triggers, and a yellow on the second three.

If you would like to see attempts at making this happen
you can check the region "Old Code" in AppClass.cpp.

I have not yet figured out how to position the plane
such that it visually reflects the separating axis, 
and also am having the problem where only one side 
of the plane will render (invisible on the other side).

