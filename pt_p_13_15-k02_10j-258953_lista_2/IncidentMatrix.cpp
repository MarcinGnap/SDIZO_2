#include "IncidentMatrix.h"

IncidentMatrix::IncidentMatrix(size_t edgeNumber, size_t vertexNumber, size_t* data)
{
	this->vertexNumber = vertexNumber;
	this->edgeNumber = edgeNumber;
	this->edgeValues = new size_t[edgeNumber];
	this->matrixHandler = new CellType*[vertexNumber];

	for (size_t i = 0; i < vertexNumber; i++)
	{
		this->matrixHandler[i] = new CellType[edgeNumber];

		for (size_t j = 0; j < edgeNumber; j++)
		{
			this->matrixHandler[i][j] = CellType::empty;
		}
	}

	int dataIndex = 0;
	int valueIndex = 0;
	for (size_t i = 0; i < edgeNumber; i++)
	{
		auto value = data[dataIndex];
		this->matrixHandler[data[dataIndex]][i] = CellType::origin;
		dataIndex++;
		this->matrixHandler[data[dataIndex]][i] = CellType::destination;
		dataIndex++;
		this->edgeValues[valueIndex] = data[dataIndex];
		dataIndex++;
		valueIndex++;
	}
}

IncidentMatrix::~IncidentMatrix()
{
	if (matrixHandler != nullptr)
	{
		for (size_t i = 0; i < this->vertexNumber; i++)
		{
			delete[] this->matrixHandler[i];
		}
		delete[] this->matrixHandler;
	}
}

void IncidentMatrix::print(std::ostream& out)
{
	out << "    ";

	for (size_t i = 0; i < this->edgeNumber; i++)
	{
		out << i << "    ";
	}

	out << std::endl << std::endl;

	for (size_t i = 0; i < this->vertexNumber; i++)
	{
		out << i << "  ";
		for (size_t j = 0; j < this->edgeNumber; j++)
		{
			out << std::setw(2) << int(this->matrixHandler[i][j]) << " | ";
		}
		out << std::endl;
	}

	out << std::endl << "v  ";

	for (size_t i = 0; i < this->edgeNumber; i++)
	{
		out << std::setw(2) << this->edgeValues[i] << " | ";
	}

	out << std::endl;
}

size_t IncidentMatrix::getVertexNumber()
{
	return this->vertexNumber;
}

size_t IncidentMatrix::getEdgeNumber()
{
	return this->edgeNumber;
}

CellType** IncidentMatrix::getMatrix()
{
	return this->matrixHandler;
}

size_t* IncidentMatrix::getValues()
{
	return this->edgeValues;
}