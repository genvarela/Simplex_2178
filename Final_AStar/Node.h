#ifndef NODE_H
#define NODE_H

#include "Definitions.h"

class Node
{
public:
	Node(float xCoord, float yCoord, float zCoord, int i);
	Node(vector3 position, int i);
	~Node();

	//void feedNodes(std::vector<Node> v);

	std::vector<Node> getNeighbors();
	std::vector<Node> findNeighbors(std::vector<Node> allN);

	int getDistance(Node other);

	bool isTraversable();
	void setTraversable(bool b);
	
	int getIndex();

	float getX();
	float getY();
	float getZ();

	int getF();
	int getG();
	int getH();

	void setF(int newF);
	void setG(int newG);
	void setH(int newH);

private:
	//std::vector<Node> allNodes;

	std::vector<Node> neighbors;

	bool traversable;

	int index;

	float x;
	float y;
	float z;

	int f;
	int g;
	int h;


};


/*
	To Use Node Class:
	1. Have a list of positions
	2. Create new Nodes on these positions
	3. Call findNeighbors on each Node

	See AppClass.cpp for A* algorithm
*/


#endif NODE_H