#include "Reader.h"

using namespace std;

Reader::Reader(string basePath)
	: basePath(basePath) {}

IncidentMatrix* Reader::readMatrixGraph(string fileName)
{
	size_t edgeNumber, vertexNumber;
	size_t* data;

	tie(edgeNumber, vertexNumber, data) = this->readData(fileName);

	if (data == nullptr)
	{
		return nullptr;
	}

	IncidentMatrix* matrix = new IncidentMatrix(edgeNumber, vertexNumber, data);

	delete[] data;

	return matrix;
}

NeighborhoodList* Reader::readListGraph(string fileName)
{
	size_t edgeNumber, vertexNumber;
	size_t* data;

	tie(edgeNumber, vertexNumber, data) = this->readData(fileName);

	if (data == nullptr)
	{
		return nullptr;
	}

	NeighborhoodList* list = new NeighborhoodList(edgeNumber, vertexNumber, data);

	delete[] data;

	return list;
}

tuple<size_t, size_t, size_t*> Reader::readData(string fileName)
{
	ifstream file(this->basePath + fileName);

	if (file.fail())
	{
		return make_tuple(-1, -1, nullptr);
	}

	size_t edgeNumber, vertexNumber;

	file >> edgeNumber >> vertexNumber;

	size_t dataSize = edgeNumber * 3;
	size_t* data = new size_t[dataSize];

	for (size_t i = 0; i < dataSize; i++)
	{
		file >> data[i];
	}

	return make_tuple(edgeNumber, vertexNumber, data);
}