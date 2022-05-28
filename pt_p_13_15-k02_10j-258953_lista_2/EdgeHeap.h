#pragma once

#include "Edge.h"

class EdgeHeap
{
public:
	EdgeHeap(bool bClear = true);
	~EdgeHeap();
	void push(Edge* edge);
	Edge* pop();
	bool empty();
	void print();

private:
	bool bClear;
	size_t stEHSize;
	Edge** root;

	void HeapifyUp();
	void HeapifyDown();
};