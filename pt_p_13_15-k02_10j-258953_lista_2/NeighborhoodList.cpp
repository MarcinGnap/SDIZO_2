#include "NeighborhoodList.h"

#include <iostream>

using namespace std;

//	Konstruktor
NeighborhoodList::NeighborhoodList(size_t edgeNumber, size_t vertexNumber, size_t* data)
{
	this->edgeNumber = edgeNumber;							//	Liczba krawêdzi.
	this->vertexNumber = vertexNumber;						//	Liczba wierzcho³ków.
	this->edges = new Edge*[vertexNumber];					//	Tablica przechowuj¹ca krawêdzie.

	for (size_t i = 0; i < vertexNumber; i++)				//	Wyzerowanie tablicy.
	{
		this->edges[i] = nullptr;
	}

	Edge* edge = nullptr;									//	Stworzenie krawêdzi.
	size_t dataNumber = 3 * edgeNumber;						//	Iloœæ przechowywanych liczb.
	size_t currentIndex = 0;

	while (currentIndex < dataNumber)						//	Pêtla wykonuj¹ca siê dopóki nie skoñcz¹ siê dane w podanej tablicy.
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
		Edge* edgeToDelete = nullptr;
		for (size_t i = 0; i < this->vertexNumber; i++)
		{
			edgeToDelete = this->edges[i];

			if (edgeToDelete == nullptr)
			{
				continue;
			}

			while (edgeToDelete->next != nullptr)
			{
				edgeToDelete = edgeToDelete->next;
				delete edgeToDelete->previous;
			}
			delete edgeToDelete;
		}
		delete[] this->edges;
	}
}

//	Wyœwietlanie.
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