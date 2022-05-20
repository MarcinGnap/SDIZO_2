#pragma once
#include "array.h"

class ArrayofArrays
{
public:
	int iAASize;
	Array *newAArray = nullptr;

	ArrayofArrays();
	~ArrayofArrays();

	void pushAA(Array);
	void pushMidAA(int, Array);
	void popAA();
	void clearAllAArray();
};