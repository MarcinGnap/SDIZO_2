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
	newArray = nullptr;
}

void Array::pushFront(int iAPushFront)
{
	int iATempSize = iASize + 1;
	auto tempArray = new int[iASize + 1];

	tempArray[0] = iAPushFront;
	if (iASize != 0)
	{
		for (int i = iATempSize; i >= 1; i--)
		{
			tempArray[i] = newArray[i - 1];
		}
	}
	delete[] newArray;
	newArray = tempArray;
	tempArray = nullptr;
	iASize++;
}

void Array::pushEnd(int iAPushElement)
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

void Array::popFront()
{
	if (iASize != 0)
	{
		auto tempArray = new int[iASize - 1];

		for (int i = iASize - 1; i >= 0; i--)
		{
			tempArray[i] = newArray[i + 1];
		}
		delete[] newArray;
		newArray = tempArray;
		tempArray = nullptr;
		iASize--;
	}
}

void Array::popEnd()
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

void Array::popMiddleIndex(int iAPopIndex)
{
	if (iAPopIndex >= 0 && iAPopIndex < iASize)
	{
		auto tempArray = new int[iASize - 1];

		for (int i = 0; i < iAPopIndex; i++)
		{
			tempArray[i] = newArray[i];
		}
		for (int i = iAPopIndex; i < iASize; i++)
		{
			tempArray[i] = newArray[i + 1];
		}
		delete[] newArray;
		newArray = tempArray;
		tempArray = nullptr;
		iASize--;
	}
}

bool Array::popMiddleValue(int iAPopValue)
{
	if (iASize != 0)
	{
		for (int i = 0; i < iASize; i++)
		{
			if (iAPopValue == newArray[i])
			{
				auto tempArray = new int[iASize - 1];
				for (int j = 0; j < i; j++)
				{
					tempArray[j] = newArray[j];
				}
				for (int j = i; j < iASize; j++)
				{
					tempArray[j] = newArray[j + 1];
				}
				delete[] newArray;
				newArray = tempArray;
				tempArray = nullptr;
				iASize--;

				return true;
			}
		}
	}
	return false;
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