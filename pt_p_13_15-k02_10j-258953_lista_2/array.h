#pragma once
class Array
{
public:
	int iASize;
	int *newArray = nullptr;
	
	Array();
	~Array();

	void pushFront(int);
	void pushEnd(int);
	void pushMid(int, int);
	void popFront();
	void popEnd();
	void popMiddleIndex(int);
	bool popMiddleValue(int);
	void clearAllArray();
};