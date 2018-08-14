#ifndef NODE_H
#define NODE_H

#include "Definitions.h"

class Node
{
public:
	Node(vector3 xCoord, vector3 yCoord, vector3 zCoord, int i);
	~Node();

	void feedNodes(std::vector<Node> v);

	std::vector<Node> getNeighbors();
	std::vector<Node> findNeighbors(); 

	bool isTraversable();
	void setTraversable(bool b);
	
	int getIndex();

	vector3 getX();
	vector3 getY();
	vector3 getZ();

	int getF();
	int getG();
	int getH();

	void setF();
	void setG();
	void setH();

private:
	std::vector<Node> allNodes;

	std::vector<Node> neighbors;

	bool traversable;

	int index;

	vector3 x;
	vector3 y;
	vector3 z;

	int f;
	int g;
	int h;


};


/*
	To Use Node Class:
	1. Have a list of positions
	2. Create new Nodes on these positions
	3. Add the new Nodes to a list of Nodes
	4. Call feedNodes on each Node and pass in the Node list
	5. Call findNeighbors on each Node

	See AppClass.cpp for A* algorithm
*/


#endif NODE_H