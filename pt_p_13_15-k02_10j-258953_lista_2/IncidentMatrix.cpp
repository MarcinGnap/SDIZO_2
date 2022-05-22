#include "IncidentMatrix.h"

using namespace std;

//	Kontruktor.
IncidentMatrix::IncidentMatrix(size_t edgeNumber, size_t vertexNumber, size_t* data)
{
	this->vertexNumber = vertexNumber;											//	Liczba wierzcho³ków.
	this->edgeNumber = edgeNumber;												//	Liczba krawêdzi.
	this->edgeValues = new size_t[edgeNumber];									//	Tablica przechowuj¹ca wagi krawêdzi.
	this->matrixHandler = new CellType*[vertexNumber];							//	Macierz.

	for (size_t i = 0; i < vertexNumber; i++)									//	Tworzenie dwuwymiarowej tablicy wype³nionej zerami.
	{
		this->matrixHandler[i] = new CellType[edgeNumber];

		for (size_t j = 0; j < edgeNumber; j++)
		{
			this->matrixHandler[i][j] = CellType::empty;
		}
	}
	
	//	Wype³nianie danych w macierzy za pomoc¹ danych przes³anych ze struktury.
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

//	Destruktor.
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

//	Wyœwietlenie macierzy.
void IncidentMatrix::print()
{

	cout << std::endl << "v  ";

	for (size_t i = 0; i < this->edgeNumber; i++)
	{
		cout << std::setw(2) << this->edgeValues[i] << " | ";
	}

	cout << endl << endl << "      ";

	for (size_t i = 0; i < this->edgeNumber; i++)
	{
		cout << i << "    ";
	}
	cout << endl;
	for (size_t i = 0; i < this->edgeNumber; i++)
	{
		cout << "-----";
	}

	cout << "----" << endl;

	for (size_t i = 0; i < this->vertexNumber; i++)
	{
		cout << " " << i << " | ";
		for (size_t j = 0; j < this->edgeNumber; j++)
		{
			cout << std::setw(2) << int(this->matrixHandler[i][j]) << " | ";
		}
		cout << std::endl;
	}
	cout << std::endl;
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