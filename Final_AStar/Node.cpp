#include "Node.h"

Node::Node(vector3 xCoord, vector3 yCoord, vector3 zCoord, int i)
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


Node::~Node()
{
}

//Put in the list of all the nodes.
void Node::feedNodes(std::vector<Node> v)
{
	for(int i = 0; i < v.size(); i++)
	{
		allNodes.push_back(v[i]);
	}
}

//Returns the current set of neighbors. If none have been calculated yet, call findNeighbors().
std::vector<Node> Node::getNeighbors()
{
	return neighbors;
}

//Clears the current set of neighbors, then calculates new ones.
std::vector<Node> Node::findNeighbors()
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
	if (allNodes[oneUp].traversable && oneUp >= 0)
	{
		neighbors.push_back(allNodes[oneUp]);
	}

	int oneDown = index + 10;
	if (allNodes[oneDown].traversable && oneDown <= 59)
	{
		neighbors.push_back(allNodes[oneDown]);
	}

	int oneLeft = index - 1;
	if (allNodes[oneLeft].traversable && oneLeft %10 != 0)
	{
		neighbors.push_back(allNodes[oneLeft]);
	}

	int oneRight = index - 1;
	if (allNodes[oneRight].traversable && oneRight % 10 != 0)
	{
		neighbors.push_back(allNodes[oneRight]);
	}

	return neighbors;
}
