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
	//	Iteracja przez wszystkie wierzcho³ki.
	for (size_t i = 0; i < vertexNumber; i++)
	{
		this->edges[i] = nullptr;
	}

	Edge* edge = nullptr;
	size_t dataNumber = 3 * edgeNumber;
	size_t currentIndex = 0;

	while (currentIndex < dataNumber)
	{
		//	Pozyskanie krawêdzi z tablicy.
		//auto test = data[currentIndex];
		edge = this->edges[data[currentIndex]];
		//	Sprawdzenie czy istniej¹ jakiekolwiek krawêdzie.
		if (edge == nullptr)
		{
			//	Stworzenie nowej krawêdzi.
			this->edges[data[currentIndex]] = new Edge(data[currentIndex], data[currentIndex + 1], data[currentIndex + 2]);
			currentIndex += 3;
			continue;
		}
		//	Znalezienie ostatniej istniej¹cej krawêdzi.
		while (edge->next != nullptr)
		{
			edge = edge->next;
		}
		//	Stworzenie nowej krawêdzi.
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
		//	Stworzenie tymczasowej krawêdzi bez zawartoœci w celu usprawnienia usuwania listy.
		Edge* edgeToDelete = nullptr;
		//	Pêtla wykonuj¹ca siê od pierwszego do ostatniego wierzcho³ka.
		for (size_t i = 0; i < this->vertexNumber; i++)
		{
			//	Pozyskanie pierwszej krawêdzi.
			edgeToDelete = this->edges[i];
			//	Sprawdzenie czy krawêdŸ ma zawartoœæ.
			if (edgeToDelete == nullptr)
			{
				continue;
			}
			//	Iteracja przez wszystkie przechowywane krawêdzie.
			while (edgeToDelete->next != nullptr)
			{
				//	Usuniêcie krawêdzi.
				edgeToDelete = edgeToDelete->next;
				delete edgeToDelete->previous;
			}
			delete edgeToDelete;
		}
		//	Usuniêcie tablicy przechowuj¹cej krawêdzie.
		delete[] this->edges;
	}
}

//	Wyœwietlanie.
void NeighborhoodList::print()
{
	Edge* edge = nullptr;
	//	Iteracja przez wszystkie wierzcho³ki.
	for (size_t i = 0; i < this->vertexNumber; i++)
	{
		cout << i << " --> ";
		//	Pozyskanie krawêdzi.
		edge = this->edges[i];
		//	Sprawdzenie czy krawêdŸ istnieje.
		if (edge == nullptr)
		{
			cout << std::endl;
			continue;
		}

		while (edge != nullptr)
		{
			//	Wyœwietlenie krawêdzi.
			cout << "  " << edge->destination << '[' << "  " << edge->value << "] | ";
			edge = edge->next;
		}

		cout << endl;
	}
}

//	Pozyskanie liczby wierzcho³ków.
size_t NeighborhoodList::getVertexNumber()
{
	return this->vertexNumber;
}

//	Pozyskanie liczby krawêdzi.
Edge** NeighborhoodList::getEdges()
{
	return this->edges;
}