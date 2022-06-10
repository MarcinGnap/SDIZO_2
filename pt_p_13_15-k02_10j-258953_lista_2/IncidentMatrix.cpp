#include "IncidentMatrix.h"

using namespace std;

IncidentMatrix::IncidentMatrix()
{

}

//	Kontruktor.
IncidentMatrix::IncidentMatrix(size_t edgeNumber, size_t vertexNumber, size_t* data)
{
	//	Deklaracja zmiennych.
	this->vertexNumber = vertexNumber;
	this->edgeNumber = edgeNumber;
	this->edgeValues = new size_t[edgeNumber];
	this->matrixHandler = new CellType*[vertexNumber];
	//	Iteracja przez wszystkie wierzcho³ki.
	for (size_t i = 0; i < vertexNumber; i++)
	{
		//	Stworzenie nowej tablicy.
		this->matrixHandler[i] = new CellType[edgeNumber];
		//	Wype³nienie tablicy pustymi komórkami.
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
		//	Odczytanie danych z wejœcia.
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

	cout << std::endl << "v    ";

	for (size_t i = 0; i < this->edgeNumber; i++)
	{
		cout << setw(2) << this->edgeValues[i] << " | ";
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
			cout << setw(2) << int(this->matrixHandler[i][j]) << " | ";
		}
		cout << endl;
	}
	cout << endl;
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