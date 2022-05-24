#include "NeighborhoodList.h"

#include <iostream>

using namespace std;

//	Konstruktor
NeighborhoodList::NeighborhoodList(size_t edgeNumber, size_t vertexNumber, size_t* data)
{
	this->edgeNumber = edgeNumber;							//	Liczba kraw�dzi.
	this->vertexNumber = vertexNumber;						//	Liczba wierzcho�k�w.
	this->edges = new Edge*[vertexNumber];					//	Tablica przechowuj�ca kraw�dzie.

	for (size_t i = 0; i < vertexNumber; i++)				//	Wyzerowanie tablicy.
	{
		this->edges[i] = nullptr;
	}

	Edge* edge = nullptr;									//	Stworzenie kraw�dzi.
	size_t dataNumber = 3 * edgeNumber;						//	Ilo�� przechowywanych liczb.
	size_t currentIndex = 0;								//	Pomocnicza zmienna wykorzystywana w p�tli.

	while (currentIndex < dataNumber)						//	P�tla wykonuj�ca si� dop�ki nie sko�cz� si� dane w podanej tablicy.
	{
		auto test = data[currentIndex];
		edge = this->edges[data[currentIndex]];

		if (edge == nullptr)
		{
			this->edges[data[currentIndex]] = new Edge(data[currentIndex], data[currentIndex + 1], data[currentIndex + 2]);
			currentIndex += 3;
			continue;
		}

		while (edge->next != nullptr)
		{
			edge = edge->next;
		}

		edge->next = new Edge(data[currentIndex], data[currentIndex + 1], data[currentIndex + 2]);
		edge->next->previous = edge;
		currentIndex += 3;
	}
}

//	Destruktor.
NeighborhoodList::~NeighborhoodList()
{
	if (this->edges != nullptr)
	{
		Edge* edgeToDelete = nullptr;									//	Stworzenie tymczasowej kraw�dzi bez zawarto�ci w celu usprawnienia usuwania listy.
		for (size_t i = 0; i < this->vertexNumber; i++)					//	P�tla wykonuj�ca si� od pierwszego do ostatniego wierzcho�ka.
		{
			edgeToDelete = this->edges[i];								//	Przypisujemy aktualnie usuwan� kraw�d� do tymczasowej zmiennej.

			if (edgeToDelete == nullptr)								//	Je�li kraw�d� nie ma zawarto�ci to p�tla zostaje przerwana.
			{
				continue;
			}

			while (edgeToDelete->next != nullptr)						//	Je�li jest kolejna kraw�d� do usuni�cia p�tla si� wykona.
			{
				edgeToDelete = edgeToDelete->next;
				delete edgeToDelete->previous;
			}
			delete edgeToDelete;
		}
		delete[] this->edges;
	}
}

//	Wy�wietlanie.
void NeighborhoodList::print()
{
	Edge* edge = nullptr;

	for (size_t i = 0; i < this->vertexNumber; i++)
	{
		cout << i << " --> ";

		edge = this->edges[i];

		if (edge == nullptr)
		{
			cout << std::endl;
			continue;
		}

		while (edge != nullptr)
		{
			cout << "  " << edge->destination << '[' << "  " << edge->value << "] | ";
			edge = edge->next;
		}

		cout << endl;
	}
}

//	Pozyskanie liczby wierzcho�k�w.
size_t NeighborhoodList::getVertexNumber()
{
	return this->vertexNumber;
}

//	Pozyskanie liczby kraw�dzi.
Edge** NeighborhoodList::getEdges()
{
	return this->edges;
}