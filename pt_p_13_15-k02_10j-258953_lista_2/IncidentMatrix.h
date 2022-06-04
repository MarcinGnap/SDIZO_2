#pragma once

#include "CellType.h"
#include <iostream>
#include <iomanip>

class IncidentMatrix
{
public:
	IncidentMatrix(size_t edgeNumber, size_t vertexNumber, size_t* data);
	~IncidentMatrix();
	void print(std::ostream& out);
	size_t getVertexNumber();
	size_t getEdgeNumber();
	CellType** getMatrix();
	size_t* getValues();

private:
	size_t vertexNumber;
	size_t edgeNumber;
	size_t* edgeValues;
	CellType** matrixHandler;
};