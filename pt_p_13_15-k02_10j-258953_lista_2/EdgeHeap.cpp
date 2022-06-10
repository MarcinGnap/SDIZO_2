#include "EdgeHeap.h"

#include <iostream>

using namespace std;

EdgeHeap::EdgeHeap(bool bClear)
: bClear(bClear), stEHSize(0), root(nullptr)
{

}

EdgeHeap::~EdgeHeap()
{
	//	Sprawdzenie czy rozmiar nie jest r�wny 0.
	if (this->stEHSize == 0)
	{
		return;
	}

	//	Sprawdzenie czy flaga obs�uguj�ca czysczenie jest ustawiona.
	if (this->bClear)
	{
		//	Usuni�cie kraw�dzi.
		for (size_t i = 0; i < this->stEHSize; i++)
		{
			delete this->root[i];
		}
	}
	//	Usuni�cie korzenia.
	delete[] this->root;
}

void EdgeHeap::push(Edge* edge)
{
	//	Sprawdzenie czy rozmiar jest r�wny 0.
	if (this->stEHSize == 0)
	{
		//	Stworzenie nowego korzenia.
		this->stEHSize++;
		this->root = new Edge *[this->stEHSize];
		this->root[0] = edge;
		return;
	}
	//	Skopiwanie istniej�cych kraw�dzi.
	Edge** tempEdge = new Edge *[this->stEHSize + 1];
	for (size_t i = 0; i < this->stEHSize; i++)
	{
		tempEdge[i] = this->root[i];
	}
	//	Usuni�cie starego korzenia i przypisanie korzeniowi nowego adresu.
	delete[] this->root;
	this->root = tempEdge;
	this->root[stEHSize] = edge;
	this->stEHSize++;
	//	Naprawa kopca.
	HeapifyUp();
}

Edge* EdgeHeap::pop()
{
	//	Sprawdzenie czy rozmiar jest r�wny 0;
	if (this->stEHSize == 0)
	{
		return nullptr;
	}
	//	Wybranie pierwszeego elementu kopca (kraw�dzi).
	Edge* edgeToReturn = this->root[0];
	//	Sprawdzenie czy rozmiar kopca jest r�wny 1.
	if (this->stEHSize == 1)
	{
		//	Usuni�cie korzenia.
		this->stEHSize--;
		delete[] this->root;
		this->root = nullptr;
		//	Zwr�cenie kraw�dzi.
		return edgeToReturn;
	}
	//	Przeniesienie ostatniego elementu kopca do korzenia.
	this->root[0] = this->root[this->stEHSize - 1];
	this->stEHSize--;
	//	Stworzenie tymczasowej zmiennej.
	Edge** tempEdge = new Edge *[this->stEHSize];
	//	Skopiowanie istniej�cych kraw�dzi.
	for (size_t i = 0; i < this->stEHSize; i++)
	{
		tempEdge[i] = this->root[i];
	}
	//	Usuni�cie warto�ci przypisanej do poprzedniego korzenia.
	delete[] this->root;
	this->root = tempEdge;
	//	Naprawienie kopca.
	this->HeapifyDown();
	//	Swr�cenie kraw�dzi.
	return edgeToReturn;
}

bool EdgeHeap::empty()
{
	if (this->stEHSize == 0)
	{
		return true;
	}

	return false;
}

void EdgeHeap::print()
{
	for (size_t i = 0; i < this->stEHSize; i++)
	{
		std::cout << this->root[i]->origin << ' ' << this->root[i]->destination << ' ' << this->root[i]->value << std::endl;
	}
}

void EdgeHeap::HeapifyUp()
{
	int i = this->stEHSize - 1;
	int parent = (i - 1) / 2;
	Edge* tempEdge = nullptr;

	while (this->root[parent]->value > this->root[i]->value)
	{
		tempEdge = root[parent];

		this->root[parent] = this->root[i];
		this->root[i] = tempEdge;

		i = parent;
		parent = (i - 1) / 2;
	}
}

void EdgeHeap::HeapifyDown()
{
	int i = 0;
	int j = 2 * i + 1;
	Edge* tempEdge = nullptr;

	while (j < this->stEHSize)
	{
		if (j + 1 < this->stEHSize && this->root[j]->value > this->root[j + 1]->value)
		{
			j += 1;
		}

		if (this->root[i]->value <= this->root[j]->value)
		{
			break;
		}

		tempEdge = this->root[i];
		this->root[i] = this->root[j];
		this->root[j] = tempEdge;
		i = j;
		j = 2 * i + 1;
	}
}