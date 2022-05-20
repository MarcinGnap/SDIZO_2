#pragma once
class array
{
public:
	int iTSize;
	int *newArray = nullptr;
	
	array();
	~array();

	void push();
	void pop();
	void clearAllArray();

};