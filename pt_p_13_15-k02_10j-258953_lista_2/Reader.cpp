#include "Reader.h"

#include <iostream>
#include <fstream>

using namespace std;

IncidentMatrix* Reader::readMatrix(string sFileName)
{
	size_t stEdgeNumber;
	size_t stVertexNumber;
	size_t* stData;

	ifstream file(sFileName);

	file >> stEdgeNumber >> stVertexNumber;

	stData = new size_t[stEdgeNumber * 3];

	for (size_t i = 0; i < stEdgeNumber; i++)
	{
		file >> stData[i];
	}
	IncidentMatrix* imMatrix = new IncidentMatrix(stEdgeNumber, stVertexNumber, stData);
	delete[] stData;
	return imMatrix;
}

NeighborhoodList* Reader::readList(string sFileName)
{
	size_t stEdgeNumber;
	size_t stVertexNumber;
	size_t* stData;

	ifstream file(sFileName);

	file >> stEdgeNumber >> stVertexNumber;

	stData = new size_t[stEdgeNumber * 3];

	for (size_t i = 0; i < stEdgeNumber; i++)
	{
		file >> stData[i];
	}
	NeighborhoodList* nlList = new NeighborhoodList(stEdgeNumber, stVertexNumber, stData);
	delete[] stData;
	return nlList;
}