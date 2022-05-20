#include "Array.h"

#include <iostream>
#include <stdlib.h>

using namespace std;

Array::Array()
{
	iASize = 0;
	newArray = new int[iASize];
}

Array::~Array()
{

}

void Array::push(int iAPushElement)
{
	auto tempArray = new int[iASize + 1];

	tempArray[iASize] = iAPushElement;
	if (iASize != 0)
	{
		for (int i = 0; i < iASize; i++)
		{
			tempArray[i] = newArray[i];
		}
	}
	delete[] newArray;
	newArray = tempArray;
	tempArray = nullptr;
	iASize++;
}

void Array::pushMid(int iAPushPosition, int iAPushValue)
{
	if (iAPushPosition >= 0 && iAPushPosition <= iASize)
	{
		auto tempArray = new int[iASize + 1];
		tempArray[iAPushPosition] = iAPushValue;
		for (int i = 0; i < iAPushPosition; i++)
		{
			tempArray[i] = newArray[i];
		}
		for (int i = iAPushPosition + 1; i < iASize + 1; i++)
		{
			tempArray[i] = newArray[i - 1];
		}
		delete[] newArray;
		newArray = tempArray;
		tempArray = nullptr;
		iASize++;
	}
}

void Array::pop()
{
	if (iASize != 0)
	{
		auto tempArray = new int[iASize - 1];

		for (int i = 0; i < iASize - 1; i++)
		{
			tempArray[i] = newArray[i];
		}
		delete[] newArray;
		newArray = tempArray;
		tempArray = nullptr;
		iASize--;
	}
}

void Array::clearAllArray()
{
	if (iASize != 0)
	{
		delete[] this->newArray;
		this->newArray = nullptr;
		this->iASize = 0;
	}
}