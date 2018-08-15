#include "Node.h"

//Constructor 1: Takes floats for custom position
Node::Node(float xCoord, float yCoord, float zCoord, int i)
{
	//allNodes;

	//neighbors;

	//Nodes are traversable by default.
	traversable = true;

	//Nodes store their own indices.
	index = i;

	x = xCoord;
	y = yCoord;
	z = zCoord;

	f = 0;
	g = 0;
	h = 0;
}

//Constructor 2: Takes a position vector
Node::Node(vector3 position, int i)
{
	//Nodes are traversable by default.
	traversable = true;

	//Nodes store their own indices.
	index = i;

	x = position[0];
	y = position[1];
	z = position[2];

	f = 0;
	g = 0;
	h = 0;
}


Node::~Node()
{
}


/*
//Put in the list of all the nodes.
void Node::feedNodes(std::vector<Node> v)
{
	for(int i = 0; i < v.size(); i++)
	{
		allNodes.push_back(v[i]);
	}
}
*/

//Returns the current set of neighbors. If none have been calculated yet, call findNeighbors().
std::vector<Node> Node::getNeighbors()
{
	return neighbors;
}

//Clears the current set of neighbors, then calculates new ones.
std::vector<Node> Node::findNeighbors(std::vector<Node> allN)
{
	//In case there were neighbors calculated already
	neighbors.clear();

	//Calculations:
	//Since the grid is a 1D array of points, arranged 10x6:
	//Where i is the current index:
	//Up is i - 10, but may not be < 0
	//Down is i + 10, but may not be > 59
	//Left is i - 1, %10 may not be 0 (ends in digit 0)
	//Right is i + 1, %10 may not be 9 (ends in digit 9)

	//Calculate up
	int oneUp = index - 10;
	if (allN[oneUp].traversable && oneUp >= 0)
	{
		neighbors.push_back(allN[oneUp]);
	}

	int oneDown = index + 10;
	if (allN[oneDown].traversable && oneDown <= 59)
	{
		neighbors.push_back(allN[oneDown]);
	}

	int oneLeft = index - 1;
	if (allN[oneLeft].traversable && oneLeft %10 != 0)
	{
		neighbors.push_back(allN[oneLeft]);
	}

	int oneRight = index - 1;
	if (allN[oneRight].traversable && oneRight % 10 != 0)
	{
		neighbors.push_back(allN[oneRight]);
	}

	return neighbors;
}

//Gets the distance between two Nodes
int Node::getDistance(Node other)
{ 
	//**STILL NEED**
	return 0;
}

bool Node::isTraversable()
{
	return traversable;
}

void Node::setTraversable(bool b)
{
	traversable = b;
}

int Node::getIndex()
{
	return index;
}

float Node::getX()
{
	return x;
}

float Node::getY()
{
	return y;
}

float Node::getZ()
{
	return z;
}

int Node::getF()
{
	return f;
}

int Node::getG()
{
	return g;
}

int Node::getH()
{
	return h;
}

void Node::setF(int newF)
{
	f = newF;
}

void Node::setG(int newG)
{
	g = newG;
}

void Node::setH(int newH)
{
	h = newH;
}
