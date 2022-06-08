#pragma once

#include "Edge.h"

class NeighborhoodList
{
public:
	NeighborhoodList();
	NeighborhoodList(size_t edgeNumber, size_t vertexNumber, size_t* data);
	~NeighborhoodList();
	void print();
	size_t getVertexNumber();
	Edge** getEdges();

private:
	Edge** edges;
	size_t edgeNumber;
	size_t vertexNumber;
};