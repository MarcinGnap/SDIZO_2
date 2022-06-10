#include "NeighborhoodList.h"

#include <iostream>

using namespace std;

NeighborhoodList::NeighborhoodList()
{

}

//	Konstruktor
NeighborhoodList::NeighborhoodList(size_t edgeNumber, size_t vertexNumber, size_t* data)
{
	//	Deklaracja zmiennych.
	this->edgeNumber = edgeNumber;
	this->vertexNumber = vertexNumber;	
	this->edges = new Edge*[vertexNumber];
	//	Iteracja przez wszystkie wierzcho�ki.
	for (size_t i = 0; i < vertexNumber; i++)
	{
		this->edges[i] = nullptr;
	}

	Edge* edge = nullptr;
	size_t dataNumber = 3 * edgeNumber;
	size_t currentIndex = 0;

	while (currentIndex < dataNumber)
	{
		//	Pozyskanie kraw�dzi z tablicy.
		//auto test = data[currentIndex];
		edge = this->edges[data[currentIndex]];
		//	Sprawdzenie czy istniej� jakiekolwiek kraw�dzie.
		if (edge == nullptr)
		{
			//	Stworzenie nowej kraw�dzi.
			this->edges[data[currentIndex]] = new Edge(data[currentIndex], data[currentIndex + 1], data[currentIndex + 2]);
			currentIndex += 3;
			continue;
		}
		//	Znalezienie ostatniej istniej�cej kraw�dzi.
		while (edge->next != nullptr)
		{
			edge = edge->next;
		}
		//	Stworzenie nowej kraw�dzi.
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
		//	Stworzenie tymczasowej kraw�dzi bez zawarto�ci w celu usprawnienia usuwania listy.
		Edge* edgeToDelete = nullptr;
		//	P�tla wykonuj�ca si� od pierwszego do ostatniego wierzcho�ka.
		for (size_t i = 0; i < this->vertexNumber; i++)
		{
			//	Pozyskanie pierwszej kraw�dzi.
			edgeToDelete = this->edges[i];
			//	Sprawdzenie czy kraw�d� ma zawarto��.
			if (edgeToDelete == nullptr)
			{
				continue;
			}
			//	Iteracja przez wszystkie przechowywane kraw�dzie.
			while (edgeToDelete->next != nullptr)
			{
				//	Usuni�cie kraw�dzi.
				edgeToDelete = edgeToDelete->next;
				delete edgeToDelete->previous;
			}
			delete edgeToDelete;
		}
		//	Usuni�cie tablicy przechowuj�cej kraw�dzie.
		delete[] this->edges;
	}
}

//	Wy�wietlanie.
void NeighborhoodList::print()
{
	Edge* edge = nullptr;
	//	Iteracja przez wszystkie wierzcho�ki.
	for (size_t i = 0; i < this->vertexNumber; i++)
	{
		cout << i << " --> ";
		//	Pozyskanie kraw�dzi.
		edge = this->edges[i];
		//	Sprawdzenie czy kraw�d� istnieje.
		if (edge == nullptr)
		{
			cout << std::endl;
			continue;
		}

		while (edge != nullptr)
		{
			//	Wy�wietlenie kraw�dzi.
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