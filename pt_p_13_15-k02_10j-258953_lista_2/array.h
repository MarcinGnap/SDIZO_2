#pragma once
class Array
{
public:
	int iTSize;
	int *newArray = nullptr;
	
	Array();
	~Array();

	void push();
	void pop();
	void clearAllArray();

};