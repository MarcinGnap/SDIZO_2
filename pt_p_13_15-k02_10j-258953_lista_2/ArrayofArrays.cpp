#include "ArrayofArrays.h"

#include <iostream>

using namespace std;

ArrayofArrays::ArrayofArrays()
{
	iAASize = 0;
	newAArray = new Array[iAASize];
}

ArrayofArrays::~ArrayofArrays()
{
	
}

void ArrayofArrays::pushAA(Array aAPushElement)
{
	auto tempAArray = new Array[iAASize + 1];

	tempAArray[iAASize] = aAPushElement;
	if (iAASize != 0)
	{
		for (int i = 0; i < iAASize; i++)
		{
			tempAArray[i] = newAArray[i];
		}
	}
	delete[] newAArray;
	newAArray = tempAArray;
	tempAArray = nullptr;
	iAASize++;
}

void ArrayofArrays::pushMidAA(int iAPushPosition, Array aAPushValue)
{
	if (iAPushPosition >= 0 && iAPushPosition <= iAASize)
	{
		auto tempAArray = new Array[iAASize + 1];
		tempAArray[iAPushPosition] = aAPushValue;
		for (int i = 0; i < iAPushPosition; i++)
		{
			tempAArray[i] = newAArray[i];
		}
		for (int i = iAPushPosition + 1; i < iAASize + 1; i++)
		{
			tempAArray[i] = newAArray[i - 1];
		}
		delete[] newAArray;
		newAArray = tempAArray;
		tempAArray = nullptr;
		iAASize++;
	}
}

void ArrayofArrays::popAA()
{
	if (iAASize != 0)
	{
		auto tempAArray = new Array[iAASize - 1];

		for (int i = 0; i < iAASize - 1; i++)
		{
			tempAArray[i] = newAArray[i];
		}
		delete[] newAArray;
		newAArray = tempAArray;
		tempAArray = nullptr;
		iAASize--;
	}
}

void ArrayofArrays::clearAllAArray()
{
	if (iAASize != 0)
	{
		delete[] this->newAArray;
		this->newAArray = nullptr;
		this->iAASize = 0;
	}
}