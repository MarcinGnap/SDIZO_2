#pragma once
class Array
{
public:
	int iASize;
	int *newArray = nullptr;
	
	Array();
	~Array();

	void push(int);
	void pushMid(int, int);
	void pop();
	void clearAllArray();
};