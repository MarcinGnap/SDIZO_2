#include "EdgeHeap.h"

#include <iostream>

using namespace std;

EdgeHeap::EdgeHeap(bool bClear)
: bClear(bClear), stEHSize(0), root(nullptr)
{

}

EdgeHeap::~EdgeHeap()
{
	if (this->stEHSize == 0)
	{
		return;
	}

	if (this->bClear)
	{
		for (size_t i = 0; i < this->stEHSize; i++)
		{
			delete this->root[i];
		}
	}
	delete[] this->root;
}

void EdgeHeap::push(Edge* edge)
{
	if (this->stEHSize == 0)
	{
		this->stEHSize++;
		this->root = new Edge *[this->stEHSize];
		this->root[0] = edge;
		return;
	}
	Edge** tempEdge = new Edge *[this->stEHSize + 1];

	for (size_t i = 0; i < this->stEHSize; i++)
	{
		tempEdge[i] = this->root[i];
	}
	delete[] this->root;
	this->root = tempEdge;
	this->root[stEHSize] = edge;
	this->stEHSize++;

	HeapifyUp();
}

Edge* EdgeHeap::pop()
{
	if (this->stEHSize == 0)
	{
		return nullptr;
	}

	Edge* edgeToReturn = this->root[0];

	if (this->stEHSize == 1)
	{
		this->stEHSize--;
		delete[] this->root;
		this->root = nullptr;

		return edgeToReturn;
	}
	this->root[0] = this->root[this->stEHSize - 1];
	this->stEHSize--;

	Edge** tempEdge = new Edge *[this->stEHSize];

	for (size_t i = 0; i < this->stEHSize; i++)
	{
		tempEdge[i] = this->root[i];
	}
	delete[] this->root;
	this->root = tempEdge;

	this->HeapifyDown();

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